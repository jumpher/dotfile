// Generated from player/lua/stats.lua

"-- Display some stats.\n"
"--\n"
"-- Please consult the readme for information about usage and configuration:\n"
"-- https://github.com/Argon-/mpv-stats\n"
"--\n"
"-- Please note: not every property is always available and therefore not always\n"
"-- visible.\n"
"\n"
"local mp = require 'mp'\n"
"local options = require 'mp.options'\n"
"local utils = require 'mp.utils'\n"
"\n"
"-- Options\n"
"local o = {\n"
"    -- Default key bindings\n"
"    key_oneshot = \"i\",\n"
"    key_toggle = \"I\",\n"
"    key_page_1 = \"1\",\n"
"    key_page_2 = \"2\",\n"
"    key_page_3 = \"3\",\n"
"    key_page_4 = \"4\",\n"
"    -- For pages which support scrolling\n"
"    key_scroll_up = \"UP\",\n"
"    key_scroll_down = \"DOWN\",\n"
"    scroll_lines = 1,\n"
"\n"
"    duration = 4,\n"
"    redraw_delay = 1,                -- acts as duration in the toggling case\n"
"    ass_formatting = true,\n"
"    persistent_overlay = false,      -- whether the stats can be overwritten by other output\n"
"    print_perfdata_passes = false,   -- when true, print the full information about all passes\n"
"    filter_params_max_length = 100,  -- a filter list longer than this many characters will be shown one filter per line instead\n"
"    debug = false,\n"
"\n"
"    -- Graph options and style\n"
"    plot_perfdata = true,\n"
"    plot_vsync_ratio = true,\n"
"    plot_vsync_jitter = true,\n"
"    skip_frames = 5,\n"
"    global_max = true,\n"
"    flush_graph_data = true,         -- clear data buffers when toggling\n"
"    plot_bg_border_color = \"0000FF\",\n"
"    plot_bg_color = \"262626\",\n"
"    plot_color = \"FFFFFF\",\n"
"\n"
"    -- Text style\n"
"    font = \"sans\",\n"
"    font_mono = \"monospace\",   -- monospaced digits are sufficient\n"
"    font_size = 8,\n"
"    font_color = \"FFFFFF\",\n"
"    border_size = 0.8,\n"
"    border_color = \"262626\",\n"
"    shadow_x_offset = 0.0,\n"
"    shadow_y_offset = 0.0,\n"
"    shadow_color = \"000000\",\n"
"    alpha = \"11\",\n"
"\n"
"    -- Custom header for ASS tags to style the text output.\n"
"    -- Specifying this will ignore the text style values above and just\n"
"    -- use this string instead.\n"
"    custom_header = \"\",\n"
"\n"
"    -- Text formatting\n"
"    -- With ASS\n"
"    ass_nl = \"\\\\N\",\n"
"    ass_indent = \"\\\\h\\\\h\\\\h\\\\h\\\\h\",\n"
"    ass_prefix_sep = \"\\\\h\\\\h\",\n"
"    ass_b1 = \"{\\\\b1}\",\n"
"    ass_b0 = \"{\\\\b0}\",\n"
"    ass_it1 = \"{\\\\i1}\",\n"
"    ass_it0 = \"{\\\\i0}\",\n"
"    -- Without ASS\n"
"    no_ass_nl = \"\\n\",\n"
"    no_ass_indent = \"\\t\",\n"
"    no_ass_prefix_sep = \" \",\n"
"    no_ass_b1 = \"\\027[1m\",\n"
"    no_ass_b0 = \"\\027[0m\",\n"
"    no_ass_it1 = \"\\027[3m\",\n"
"    no_ass_it0 = \"\\027[0m\",\n"
"}\n"
"options.read_options(o)\n"
"\n"
"local format = string.format\n"
"local max = math.max\n"
"local min = math.min\n"
"\n"
"-- Function used to record performance data\n"
"local recorder = nil\n"
"-- Timer used for redrawing (toggling) and clearing the screen (oneshot)\n"
"local display_timer = nil\n"
"-- Timer used to update cache stats.\n"
"local cache_recorder_timer = nil\n"
"-- Current page and <page key>:<page function> mappings\n"
"local curr_page = o.key_page_1\n"
"local pages = {}\n"
"local scroll_bound = false\n"
"-- Save these sequences locally as we'll need them a lot\n"
"local ass_start = mp.get_property_osd(\"osd-ass-cc/0\")\n"
"local ass_stop = mp.get_property_osd(\"osd-ass-cc/1\")\n"
"-- Ring buffers for the values used to construct a graph.\n"
"-- .pos denotes the current position, .len the buffer length\n"
"-- .max is the max value in the corresponding buffer\n"
"local vsratio_buf, vsjitter_buf\n"
"local function init_buffers()\n"
"    vsratio_buf = {0, pos = 1, len = 50, max = 0}\n"
"    vsjitter_buf = {0, pos = 1, len = 50, max = 0}\n"
"end\n"
"local cache_ahead_buf, cache_speed_buf\n"
"local perf_buffers = {}\n"
"-- Save all properties known to this version of mpv\n"
"local property_list = {}\n"
"for p in string.gmatch(mp.get_property(\"property-list\"), \"([^,]+)\") do property_list[p] = true end\n"
"-- Mapping of properties to their deprecated names\n"
"local property_aliases = {\n"
"    [\"decoder-frame-drop-count\"] = \"drop-frame-count\",\n"
"    [\"frame-drop-count\"] = \"vo-drop-frame-count\",\n"
"    [\"container-fps\"] = \"fps\",\n"
"}\n"
"\n"
"local function graph_add_value(graph, value)\n"
"    graph.pos = (graph.pos % graph.len) + 1\n"
"    graph[graph.pos] = value\n"
"    graph.max = max(graph.max, value)\n"
"end\n"
"\n"
"-- Return deprecated name for the given property\n"
"local function compat(p)\n"
"    while not property_list[p] and property_aliases[p] do\n"
"        p = property_aliases[p]\n"
"    end\n"
"    return p\n"
"end\n"
"\n"
"\n"
"local function set_ASS(b)\n"
"    if not o.use_ass or o.persistent_overlay then\n"
"        return \"\"\n"
"    end\n"
"    return b and ass_start or ass_stop\n"
"end\n"
"\n"
"\n"
"local function no_ASS(t)\n"
"    return set_ASS(false) .. t .. set_ASS(true)\n"
"end\n"
"\n"
"\n"
"local function b(t)\n"
"    return o.b1 .. t .. o.b0\n"
"end\n"
"\n"
"\n"
"local function it(t)\n"
"    return o.it1 .. t .. o.it0\n"
"end\n"
"\n"
"\n"
"local function text_style()\n"
"    if not o.use_ass then\n"
"        return \"\"\n"
"    end\n"
"    if o.custom_header and o.custom_header ~= \"\" then\n"
"        return set_ASS(true) .. o.custom_header\n"
"    else\n"
"        return format(\"%s{\\\\r}{\\\\an7}{\\\\fs%d}{\\\\fn%s}{\\\\bord%f}{\\\\3c&H%s&}\" ..\n"
"                      \"{\\\\1c&H%s&}{\\\\alpha&H%s&}{\\\\xshad%f}{\\\\yshad%f}{\\\\4c&H%s&}\",\n"
"                      set_ASS(true), o.font_size, o.font, o.border_size,\n"
"                      o.border_color, o.font_color, o.alpha, o.shadow_x_offset,\n"
"                      o.shadow_y_offset, o.shadow_color)\n"
"    end\n"
"end\n"
"\n"
"\n"
"local function has_vo_window()\n"
"    return mp.get_property(\"vo-configured\") == \"yes\"\n"
"end\n"
"\n"
"\n"
"-- Generate a graph from the given values.\n"
"-- Returns an ASS formatted vector drawing as string.\n"
"--\n"
"-- values: Array/table of numbers representing the data. Used like a ring buffer\n"
"--         it will get iterated backwards \140len\140 times starting at position \140i\140.\n"
"-- i     : Index of the latest data value in \140values\140.\n"
"-- len   : The length/amount of numbers in \140values\140.\n"
"-- v_max : The maximum number in \140values\140. It is used to scale all data\n"
"--         values to a range of 0 to \140v_max\140.\n"
"-- v_avg : The average number in \140values\140. It is used to try and center graphs\n"
"--         if possible. May be left as nil\n"
"-- scale : A value that will be multiplied with all data values.\n"
"-- x_tics: Horizontal width multiplier for the steps\n"
"local function generate_graph(values, i, len, v_max, v_avg, scale, x_tics)\n"
"    -- Check if at least one value exists\n"
"    if not values[i] then\n"
"        return \"\"\n"
"    end\n"
"\n"
"    local x_max = (len - 1) * x_tics\n"
"    local y_offset = o.border_size\n"
"    local y_max = o.font_size * 0.66\n"
"    local x = 0\n"
"\n"
"    -- try and center the graph if possible, but avoid going above \140scale\140\n"
"    if v_avg then\n"
"        scale = min(scale, v_max / (2 * v_avg))\n"
"    end\n"
"\n"
"    local s = {format(\"m 0 0 n %f %f l \", x, y_max - (y_max * values[i] / v_max * scale))}\n"
"    i = ((i - 2) % len) + 1\n"
"\n"
"    for p = 1, len - 1 do\n"
"        if values[i] then\n"
"            x = x - x_tics\n"
"            s[#s+1] = format(\"%f %f \", x, y_max - (y_max * values[i] / v_max * scale))\n"
"        end\n"
"        i = ((i - 2) % len) + 1\n"
"    end\n"
"\n"
"    s[#s+1] = format(\"%f %f %f %f\", x, y_max, 0, y_max)\n"
"\n"
"    local bg_box = format(\"{\\\\bord0.5}{\\\\3c&H%s&}{\\\\1c&H%s&}m 0 %f l %f %f %f 0 0 0\",\n"
"                          o.plot_bg_border_color, o.plot_bg_color, y_max, x_max, y_max, x_max)\n"
"    return format(\"%s{\\\\r}{\\\\pbo%f}{\\\\shad0}{\\\\alpha&H00}{\\\\p1}%s{\\\\p0}{\\\\bord0}{\\\\1c&H%s}{\\\\p1}%s{\\\\p0}%s\",\n"
"                  o.prefix_sep, y_offset, bg_box, o.plot_color, table.concat(s), text_style())\n"
"end\n"
"\n"
"\n"
"local function append(s, str, attr)\n"
"    if not str then\n"
"        return false\n"
"    end\n"
"    attr.prefix_sep = attr.prefix_sep or o.prefix_sep\n"
"    attr.indent = attr.indent or o.indent\n"
"    attr.nl = attr.nl or o.nl\n"
"    attr.suffix = attr.suffix or \"\"\n"
"    attr.prefix = attr.prefix or \"\"\n"
"    attr.no_prefix_markup = attr.no_prefix_markup or false\n"
"    attr.prefix = attr.no_prefix_markup and attr.prefix or b(attr.prefix)\n"
"    s[#s+1] = format(\"%s%s%s%s%s%s\", attr.nl, attr.indent,\n"
"                     attr.prefix, attr.prefix_sep, no_ASS(str), attr.suffix)\n"
"    return true\n"
"end\n"
"\n"
"\n"
"-- Format and append a property.\n"
"-- A property whose value is either \140nil\140 or empty (hereafter called \"invalid\")\n"
"-- is skipped and not appended.\n"
"-- Returns \140false\140 in case nothing was appended, otherwise \140true\140.\n"
"--\n"
"-- s      : Table containing strings.\n"
"-- prop   : The property to query and format (based on its OSD representation).\n"
"-- attr   : Optional table to overwrite certain (formatting) attributes for\n"
"--          this property.\n"
"-- exclude: Optional table containing keys which are considered invalid values\n"
"--          for this property. Specifying this will replace empty string as\n"
"--          default invalid value (nil is always invalid).\n"
"local function append_property(s, prop, attr, excluded)\n"
"    excluded = excluded or {[\"\"] = true}\n"
"    local ret = mp.get_property_osd(prop)\n"
"    if not ret or excluded[ret] then\n"
"        if o.debug then\n"
"            print(\"No value for property: \" .. prop)\n"
"        end\n"
"        return false\n"
"    end\n"
"    return append(s, ret, attr)\n"
"end\n"
"\n"
"\n"
"local function append_perfdata(s, dedicated_page)\n"
"    local vo_p = mp.get_property_native(\"vo-passes\")\n"
"    if not vo_p then\n"
"        return\n"
"    end\n"
"\n"
"    local ds = mp.get_property_bool(\"display-sync-active\", false)\n"
"    local target_fps = ds and mp.get_property_number(\"display-fps\", 0)\n"
"                       or mp.get_property_number(compat(\"container-fps\"), 0)\n"
"    if target_fps > 0 then target_fps = 1 / target_fps * 1e9 end\n"
"\n"
"    -- Sums of all last/avg/peak values\n"
"    local last_s, avg_s, peak_s = {}, {}, {}\n"
"    for frame, data in pairs(vo_p) do\n"
"        last_s[frame], avg_s[frame], peak_s[frame] = 0, 0, 0\n"
"        for _, pass in ipairs(data) do\n"
"            last_s[frame] = last_s[frame] + pass[\"last\"]\n"
"            avg_s[frame]  = avg_s[frame]  + pass[\"avg\"]\n"
"            peak_s[frame] = peak_s[frame] + pass[\"peak\"]\n"
"        end\n"
"    end\n"
"\n"
"    -- Pretty print measured time\n"
"    local function pp(i)\n"
"        -- rescale to microseconds for a saner display\n"
"        return format(\"%05d\", i / 1000)\n"
"    end\n"
"\n"
"    -- Format n/m with a font weight based on the ratio\n"
"    local function p(n, m)\n"
"        local i = 0\n"
"        if m > 0 then\n"
"            i = tonumber(n) / m\n"
"        end\n"
"        -- Calculate font weight. 100 is minimum, 400 is normal, 700 bold, 900 is max\n"
"        local w = (700 * math.sqrt(i)) + 200\n"
"        return format(\"{\\\\b%d}%02d%%{\\\\b0}\", w, i * 100)\n"
"    end\n"
"\n"
"    -- ensure that the fixed title is one element and every scrollable line is\n"
"    -- also one single element.\n"
"    s[#s+1] = format(\"%s%s%s%s{\\\\fs%s}%s{\\\\fs%s}\",\n"
"                     dedicated_page and \"\" or o.nl, dedicated_page and \"\" or o.indent,\n"
"                     b(\"Frame Timings:\"), o.prefix_sep, o.font_size * 0.66,\n"
"                     \"(last/average/peak  \316\274s)\", o.font_size)\n"
"\n"
"    for frame, data in pairs(vo_p) do\n"
"        local f = \"%s%s%s{\\\\fn%s}%s / %s / %s %s%s{\\\\fn%s}%s%s%s\"\n"
"\n"
"        if dedicated_page then\n"
"            s[#s+1] = format(\"%s%s%s:\", o.nl, o.indent,\n"
"                             b(frame:gsub(\"^%l\", string.upper)))\n"
"\n"
"            for _, pass in ipairs(data) do\n"
"                s[#s+1] = format(f, o.nl, o.indent, o.indent,\n"
"                                 o.font_mono, pp(pass[\"last\"]),\n"
"                                 pp(pass[\"avg\"]), pp(pass[\"peak\"]),\n"
"                                 o.prefix_sep .. o.prefix_sep, p(pass[\"last\"], last_s[frame]),\n"
"                                 o.font, o.prefix_sep, o.prefix_sep, pass[\"desc\"])\n"
"\n"
"                if o.plot_perfdata and o.use_ass then\n"
"                    -- use the same line that was already started for this iteration\n"
"                    s[#s] = s[#s] ..\n"
"                              generate_graph(pass[\"samples\"], pass[\"count\"],\n"
"                                             pass[\"count\"], pass[\"peak\"],\n"
"                                             pass[\"avg\"], 0.9, 0.25)\n"
"                end\n"
"            end\n"
"\n"
"            -- Print sum of timing values as \"Total\"\n"
"            s[#s+1] = format(f, o.nl, o.indent, o.indent,\n"
"                             o.font_mono, pp(last_s[frame]),\n"
"                             pp(avg_s[frame]), pp(peak_s[frame]), \"\", \"\", o.font,\n"
"                             o.prefix_sep, o.prefix_sep, b(\"Total\"))\n"
"        else\n"
"            -- for the simplified view, we just print the sum of each pass\n"
"            s[#s+1] = format(f, o.nl, o.indent, o.indent, o.font_mono,\n"
"                            pp(last_s[frame]), pp(avg_s[frame]), pp(peak_s[frame]),\n"
"                            \"\", \"\", o.font, o.prefix_sep, o.prefix_sep,\n"
"                            frame:gsub(\"^%l\", string.upper))\n"
"        end\n"
"    end\n"
"end\n"
"\n"
"local function append_general_perfdata(s, offset)\n"
"    local perf_info = mp.get_property_native(\"perf-info\") or {}\n"
"    local count = 0\n"
"    for _, data in ipairs(perf_info) do\n"
"        count = count + 1\n"
"    end\n"
"    offset = max(1, min((offset or 1), count))\n"
"\n"
"    local i = 0\n"
"    for _, data in ipairs(perf_info) do\n"
"        i = i + 1\n"
"        if i >= offset then\n"
"            append(s, data.text or data.value, {prefix=\"[\"..tostring(i)..\"] \"..data.name..\":\"})\n"
"\n"
"            if o.plot_perfdata and o.use_ass and data.value then\n"
"                buf = perf_buffers[data.name]\n"
"                if not buf then\n"
"                    buf = {0, pos = 1, len = 50, max = 0}\n"
"                    perf_buffers[data.name] = buf\n"
"                end\n"
"                graph_add_value(buf, data.value)\n"
"                s[#s+1] = generate_graph(buf, buf.pos, buf.len, buf.max, nil, 0.8, 1)\n"
"            end\n"
"        end\n"
"    end\n"
"    return offset\n"
"end\n"
"\n"
"local function append_display_sync(s)\n"
"    if not mp.get_property_bool(\"display-sync-active\", false) then\n"
"        return\n"
"    end\n"
"\n"
"    local vspeed = append_property(s, \"video-speed-correction\", {prefix=\"DS:\"})\n"
"    if vspeed then\n"
"        append_property(s, \"audio-speed-correction\",\n"
"                        {prefix=\"/\", nl=\"\", indent=\" \", prefix_sep=\" \", no_prefix_markup=true})\n"
"    else\n"
"        append_property(s, \"audio-speed-correction\",\n"
"                        {prefix=\"DS:\" .. o.prefix_sep .. \" - / \", prefix_sep=\"\"})\n"
"    end\n"
"\n"
"    append_property(s, \"mistimed-frame-count\", {prefix=\"Mistimed:\", nl=\"\"})\n"
"    append_property(s, \"vo-delayed-frame-count\", {prefix=\"Delayed:\", nl=\"\"})\n"
"\n"
"    -- As we need to plot some graphs we print jitter and ratio on their own lines\n"
"    if not display_timer.oneshot and (o.plot_vsync_ratio or o.plot_vsync_jitter) and o.use_ass then\n"
"        local ratio_graph = \"\"\n"
"        local jitter_graph = \"\"\n"
"        if o.plot_vsync_ratio then\n"
"            ratio_graph = generate_graph(vsratio_buf, vsratio_buf.pos, vsratio_buf.len, vsratio_buf.max, nil, 0.8, 1)\n"
"        end\n"
"        if o.plot_vsync_jitter then\n"
"            jitter_graph = generate_graph(vsjitter_buf, vsjitter_buf.pos, vsjitter_buf.len, vsjitter_buf.max, nil, 0.8, 1)\n"
"        end\n"
"        append_property(s, \"vsync-ratio\", {prefix=\"VSync Ratio:\", suffix=o.prefix_sep .. ratio_graph})\n"
"        append_property(s, \"vsync-jitter\", {prefix=\"VSync Jitter:\", suffix=o.prefix_sep .. jitter_graph})\n"
"    else\n"
"        -- Since no graph is needed we can print ratio/jitter on the same line and save some space\n"
"        local vratio = append_property(s, \"vsync-ratio\", {prefix=\"VSync Ratio:\"})\n"
"        append_property(s, \"vsync-jitter\", {prefix=\"VSync Jitter:\", nl=\"\" or o.nl})\n"
"    end\n"
"end\n"
"\n"
"\n"
"local function append_filters(s, prop, prefix)\n"
"    local length = 0\n"
"    local filters = {}\n"
"\n"
"    for _,f in ipairs(mp.get_property_native(prop, {})) do\n"
"        local n = f.name\n"
"        if f.enabled ~= nil and not f.enabled then\n"
"            n = n .. \" (disabled)\"\n"
"        end\n"
"\n"
"        local p = {}\n"
"        for key,value in pairs(f.params) do\n"
"            p[#p+1] = key .. \"=\" .. value\n"
"        end\n"
"        if #p > 0 then\n"
"            p = \" [\" .. table.concat(p, \" \") .. \"]\"\n"
"        else\n"
"            p = \"\"\n"
"        end\n"
"\n"
"        length = length + n:len() + p:len()\n"
"        filters[#filters+1] = no_ASS(n) .. it(no_ASS(p))\n"
"    end\n"
"\n"
"    if #filters > 0 then\n"
"        local ret\n"
"        if length < o.filter_params_max_length then\n"
"            ret = table.concat(filters, \", \")\n"
"        else\n"
"            local sep = o.nl .. o.indent .. o.indent\n"
"            ret = sep .. table.concat(filters, sep)\n"
"        end\n"
"        s[#s+1] = o.nl .. o.indent .. b(prefix) .. o.prefix_sep .. ret\n"
"    end\n"
"end\n"
"\n"
"\n"
"local function add_header(s)\n"
"    s[#s+1] = text_style()\n"
"end\n"
"\n"
"\n"
"local function add_file(s)\n"
"    append(s, \"\", {prefix=\"File:\", nl=\"\", indent=\"\"})\n"
"    append_property(s, \"filename\", {prefix_sep=\"\", nl=\"\", indent=\"\"})\n"
"    if not (mp.get_property_osd(\"filename\") == mp.get_property_osd(\"media-title\")) then\n"
"        append_property(s, \"media-title\", {prefix=\"Title:\"})\n"
"    end\n"
"\n"
"    local editions = mp.get_property_number(\"editions\")\n"
"    local edition = mp.get_property_number(\"current-edition\")\n"
"    local ed_cond = (edition and editions > 1)\n"
"    if ed_cond then\n"
"        append_property(s, \"edition-list/\" .. tostring(edition) .. \"/title\",\n"
"                       {prefix=\"Edition:\"})\n"
"        append_property(s, \"edition-list/count\",\n"
"                        {prefix=\"(\" .. tostring(edition + 1) .. \"/\", suffix=\")\", nl=\"\",\n"
"                         indent=\" \", prefix_sep=\" \", no_prefix_markup=true})\n"
"    end\n"
"\n"
"    local ch_index = mp.get_property_number(\"chapter\")\n"
"    if ch_index and ch_index >= 0 then\n"
"        append_property(s, \"chapter-list/\" .. tostring(ch_index) .. \"/title\", {prefix=\"Chapter:\",\n"
"                        nl=ed_cond and \"\" or o.nl})\n"
"        append_property(s, \"chapter-list/count\",\n"
"                        {prefix=\"(\" .. tostring(ch_index + 1) .. \"/\", suffix=\")\", nl=\"\",\n"
"                         indent=\" \", prefix_sep=\" \", no_prefix_markup=true})\n"
"    end\n"
"\n"
"    local fs = append_property(s, \"file-size\", {prefix=\"Size:\"})\n"
"    append_property(s, \"file-format\", {prefix=\"Format/Protocol:\", nl=fs and \"\" or o.nl})\n"
"\n"
"    local demuxer_cache = mp.get_property_native(\"demuxer-cache-state\", {})\n"
"    if demuxer_cache[\"fw-bytes\"] then\n"
"        demuxer_cache = demuxer_cache[\"fw-bytes\"] -- returns bytes\n"
"    else\n"
"        demuxer_cache = 0\n"
"    end\n"
"    local demuxer_secs = mp.get_property_number(\"demuxer-cache-duration\", 0)\n"
"    if demuxer_cache + demuxer_secs > 0 then\n"
"        append(s, utils.format_bytes_humanized(demuxer_cache), {prefix=\"Total Cache:\"})\n"
"        append(s, format(\"%.1f\", demuxer_secs), {prefix=\"(\", suffix=\" sec)\", nl=\"\",\n"
"               no_prefix_markup=true, prefix_sep=\"\", indent=o.prefix_sep})\n"
"    end\n"
"end\n"
"\n"
"\n"
"local function add_video(s)\n"
"    local r = mp.get_property_native(\"video-params\")\n"
"    -- in case of e.g. lavi-complex there can be no input video, only output\n"
"    if not r then\n"
"        r = mp.get_property_native(\"video-out-params\")\n"
"    end\n"
"    if not r then\n"
"        return\n"
"    end\n"
"\n"
"    append(s, \"\", {prefix=o.nl .. o.nl .. \"Video:\", nl=\"\", indent=\"\"})\n"
"    if append_property(s, \"video-codec\", {prefix_sep=\"\", nl=\"\", indent=\"\"}) then\n"
"        append_property(s, \"hwdec-current\", {prefix=\"(hwdec:\", nl=\"\", indent=\" \",\n"
"                         no_prefix_markup=true, suffix=\")\"}, {no=true, [\"\"]=true})\n"
"    end\n"
"    append_property(s, \"avsync\", {prefix=\"A-V:\"})\n"
"    if append_property(s, compat(\"decoder-frame-drop-count\"),\n"
"                       {prefix=\"Dropped Frames:\", suffix=\" (decoder)\"}) then\n"
"        append_property(s, compat(\"frame-drop-count\"), {suffix=\" (output)\", nl=\"\", indent=\"\"})\n"
"    end\n"
"    if append_property(s, \"display-fps\", {prefix=\"Display FPS:\", suffix=\" (specified)\"}) then\n"
"        append_property(s, \"estimated-display-fps\",\n"
"                        {suffix=\" (estimated)\", nl=\"\", indent=\"\"})\n"
"    else\n"
"        append_property(s, \"estimated-display-fps\",\n"
"                        {prefix=\"Display FPS:\", suffix=\" (estimated)\"})\n"
"    end\n"
"    if append_property(s, compat(\"container-fps\"), {prefix=\"FPS:\", suffix=\" (specified)\"}) then\n"
"        append_property(s, \"estimated-vf-fps\",\n"
"                        {suffix=\" (estimated)\", nl=\"\", indent=\"\"})\n"
"    else\n"
"        append_property(s, \"estimated-vf-fps\",\n"
"                        {prefix=\"FPS:\", suffix=\" (estimated)\"})\n"
"    end\n"
"\n"
"    append_display_sync(s)\n"
"    append_perfdata(s, o.print_perfdata_passes)\n"
"\n"
"    if append(s, r[\"w\"], {prefix=\"Native Resolution:\"}) then\n"
"        append(s, r[\"h\"], {prefix=\"x\", nl=\"\", indent=\" \", prefix_sep=\" \", no_prefix_markup=true})\n"
"    end\n"
"    append_property(s, \"current-window-scale\", {prefix=\"Window Scale:\"})\n"
"    if r[\"aspect\"] ~= nil then\n"
"        append(s, format(\"%.2f\", r[\"aspect\"]), {prefix=\"Aspect Ratio:\"})\n"
"    end\n"
"    append(s, r[\"pixelformat\"], {prefix=\"Pixel Format:\"})\n"
"    if r[\"hw-pixelformat\"] ~= nil then\n"
"        append(s, r[\"hw-pixelformat\"], {prefix_sep=\"[\", nl=\"\", indent=\" \",\n"
"                suffix=\"]\"})\n"
"    end\n"
"\n"
"    -- Group these together to save vertical space\n"
"    local prim = append(s, r[\"primaries\"], {prefix=\"Primaries:\"})\n"
"    local cmat = append(s, r[\"colormatrix\"], {prefix=\"Colormatrix:\", nl=prim and \"\" or o.nl})\n"
"    append(s, r[\"colorlevels\"], {prefix=\"Levels:\", nl=cmat and \"\" or o.nl})\n"
"\n"
"    -- Append HDR metadata conditionally (only when present and interesting)\n"
"    local hdrpeak = r[\"sig-peak\"] or 0\n"
"    local hdrinfo = \"\"\n"
"    if hdrpeak > 1 then\n"
"        hdrinfo = \" (HDR peak: \" .. format(\"%.2f\", hdrpeak) .. \")\"\n"
"    end\n"
"\n"
"    append(s, r[\"gamma\"], {prefix=\"Gamma:\", suffix=hdrinfo})\n"
"    append_property(s, \"packet-video-bitrate\", {prefix=\"Bitrate:\", suffix=\" kbps\"})\n"
"    append_filters(s, \"vf\", \"Filters:\")\n"
"end\n"
"\n"
"\n"
"local function add_audio(s)\n"
"    local r = mp.get_property_native(\"audio-params\")\n"
"    -- in case of e.g. lavi-complex there can be no input audio, only output\n"
"    if not r then\n"
"        r = mp.get_property_native(\"audio-out-params\")\n"
"    end\n"
"    if not r then\n"
"        return\n"
"    end\n"
"\n"
"    append(s, \"\", {prefix=o.nl .. o.nl .. \"Audio:\", nl=\"\", indent=\"\"})\n"
"    append_property(s, \"audio-codec\", {prefix_sep=\"\", nl=\"\", indent=\"\"})\n"
"    local cc = append(s, r[\"channel-count\"], {prefix=\"Channels:\"})\n"
"    append(s, r[\"format\"], {prefix=\"Format:\", nl=cc and \"\" or o.nl})\n"
"    append(s, r[\"samplerate\"], {prefix=\"Sample Rate:\", suffix=\" Hz\"})\n"
"    append_property(s, \"packet-audio-bitrate\", {prefix=\"Bitrate:\", suffix=\" kbps\"})\n"
"    append_filters(s, \"af\", \"Filters:\")\n"
"end\n"
"\n"
"\n"
"-- Determine whether ASS formatting shall/can be used and set formatting sequences\n"
"local function eval_ass_formatting()\n"
"    o.use_ass = o.ass_formatting and has_vo_window()\n"
"    if o.use_ass then\n"
"        o.nl = o.ass_nl\n"
"        o.indent = o.ass_indent\n"
"        o.prefix_sep = o.ass_prefix_sep\n"
"        o.b1 = o.ass_b1\n"
"        o.b0 = o.ass_b0\n"
"        o.it1 = o.ass_it1\n"
"        o.it0 = o.ass_it0\n"
"    else\n"
"        o.nl = o.no_ass_nl\n"
"        o.indent = o.no_ass_indent\n"
"        o.prefix_sep = o.no_ass_prefix_sep\n"
"        o.b1 = o.no_ass_b1\n"
"        o.b0 = o.no_ass_b0\n"
"        o.it1 = o.no_ass_it1\n"
"        o.it0 = o.no_ass_it0\n"
"    end\n"
"end\n"
"\n"
"\n"
"-- Returns an ASS string with \"normal\" stats\n"
"local function default_stats()\n"
"    local stats = {}\n"
"    eval_ass_formatting()\n"
"    add_header(stats)\n"
"    add_file(stats)\n"
"    add_video(stats)\n"
"    add_audio(stats)\n"
"    return table.concat(stats)\n"
"end\n"
"\n"
"local function scroll_vo_stats(stats, fixed_items, offset)\n"
"    local ret = {}\n"
"    local count = #stats - fixed_items\n"
"    offset = max(1, min((offset or 1), count))\n"
"\n"
"    for i, line in pairs(stats) do\n"
"        if i <= fixed_items or i >= fixed_items + offset then\n"
"            ret[#ret+1] = stats[i]\n"
"        end\n"
"    end\n"
"    return ret, offset\n"
"end\n"
"\n"
"-- Returns an ASS string with extended VO stats\n"
"local function vo_stats()\n"
"    local stats = {}\n"
"    eval_ass_formatting()\n"
"    add_header(stats)\n"
"\n"
"    -- first line (title) added next is considered fixed\n"
"    local fixed_items = #stats + 1\n"
"    append_perfdata(stats, true)\n"
"\n"
"    local page = pages[o.key_page_2]\n"
"    stats, page.offset = scroll_vo_stats(stats, fixed_items, page.offset)\n"
"    return table.concat(stats)\n"
"end\n"
"\n"
"local function perf_stats()\n"
"    local stats = {}\n"
"    eval_ass_formatting()\n"
"    add_header(stats)\n"
"    local page = pages[o.key_page_4]\n"
"    append(stats, \"\", {prefix=o.nl .. o.nl .. page.desc .. \":\", nl=\"\", indent=\"\"})\n"
"    page.offset = append_general_perfdata(stats, page.offset)\n"
"    return table.concat(stats)\n"
"end\n"
"\n"
"local function opt_time(t)\n"
"    if type(t) == type(1.1) then\n"
"        return mp.format_time(t)\n"
"    end\n"
"    return \"\077\"\n"
"end\n"
"\n"
"-- Returns an ASS string with stats about the demuxer cache etc.\n"
"local function cache_stats()\n"
"    local stats = {}\n"
"\n"
"    eval_ass_formatting()\n"
"    add_header(stats)\n"
"    append(stats, \"\", {prefix=o.nl .. o.nl .. \"Cache info:\", nl=\"\", indent=\"\"})\n"
"\n"
"    local info = mp.get_property_native(\"demuxer-cache-state\")\n"
"    if info == nil then\n"
"        append(stats, \"Unavailable.\", {})\n"
"        return table.concat(stats)\n"
"    end\n"
"\n"
"    local a = info[\"reader-pts\"]\n"
"    local b = info[\"cache-end\"]\n"
"\n"
"    append(stats, opt_time(a) .. \" - \" .. opt_time(b), {prefix = \"Packet queue:\"})\n"
"\n"
"    local r = nil\n"
"    if (a ~= nil) and (b ~= nil) then\n"
"        r = b - a\n"
"    end\n"
"\n"
"    local r_graph = nil\n"
"    if not display_timer.oneshot and o.use_ass then\n"
"        r_graph = generate_graph(cache_ahead_buf, cache_ahead_buf.pos,\n"
"                                 cache_ahead_buf.len, cache_ahead_buf.max,\n"
"                                 nil, 0.8, 1)\n"
"        r_graph = o.prefix_sep .. r_graph\n"
"    end\n"
"    append(stats, opt_time(r), {prefix = \"Read-ahead:\", suffix = r_graph})\n"
"\n"
"    -- These states are not necessarily exclusive. They're about potentially\n"
"    -- separate mechanisms, whose states may be decoupled.\n"
"    local state = \"reading\"\n"
"    local seek_ts = info[\"debug-seeking\"]\n"
"    if seek_ts ~= nil then\n"
"        state = \"seeking (to \" .. mp.format_time(seek_ts) .. \")\"\n"
"    elseif info[\"eof\"] == true then\n"
"        state = \"eof\"\n"
"    elseif info[\"underrun\"] then\n"
"        state = \"underrun\"\n"
"    elseif info[\"idle\"]  == true then\n"
"        state = \"inactive\"\n"
"    end\n"
"    append(stats, state, {prefix = \"State:\"})\n"
"\n"
"    local speed = info[\"raw-input-rate\"] or 0\n"
"    local speed_graph = nil\n"
"    if not display_timer.oneshot and o.use_ass then\n"
"        speed_graph = generate_graph(cache_speed_buf, cache_speed_buf.pos,\n"
"                                     cache_speed_buf.len, cache_speed_buf.max,\n"
"                                     nil, 0.8, 1)\n"
"        speed_graph = o.prefix_sep .. speed_graph\n"
"    end\n"
"    append(stats, utils.format_bytes_humanized(speed) .. \"/s\", {prefix=\"Speed:\",\n"
"        suffix=speed_graph})\n"
"\n"
"    append(stats, utils.format_bytes_humanized(info[\"total-bytes\"]),\n"
"           {prefix = \"Total RAM:\"})\n"
"    append(stats, utils.format_bytes_humanized(info[\"fw-bytes\"]),\n"
"           {prefix = \"Forward RAM:\"})\n"
"\n"
"    local fc = info[\"file-cache-bytes\"]\n"
"    if fc ~= nil then\n"
"        fc = utils.format_bytes_humanized(fc)\n"
"    else\n"
"        fc = \"(disabled)\"\n"
"    end\n"
"    append(stats, fc, {prefix = \"Disk cache:\"})\n"
"\n"
"    append(stats, info[\"debug-low-level-seeks\"], {prefix = \"Media seeks:\"})\n"
"    append(stats, info[\"debug-byte-level-seeks\"], {prefix = \"Stream seeks:\"})\n"
"\n"
"    append(stats, \"\", {prefix=o.nl .. o.nl .. \"Ranges:\", nl=\"\", indent=\"\"})\n"
"\n"
"    append(stats, info[\"bof-cached\"] and \"yes\" or \"no\",\n"
"           {prefix = \"Start cached:\"})\n"
"    append(stats, info[\"eof-cached\"] and \"yes\" or \"no\",\n"
"           {prefix = \"End cached:\"})\n"
"\n"
"    local ranges = info[\"seekable-ranges\"] or {}\n"
"    for n, r in ipairs(ranges) do\n"
"        append(stats, mp.format_time(r[\"start\"]) .. \" - \" ..\n"
"                      mp.format_time(r[\"end\"]),\n"
"               {prefix = format(\"Range %s:\", n)})\n"
"    end\n"
"\n"
"    return table.concat(stats)\n"
"end\n"
"\n"
"-- Record 1 sample of cache statistics.\n"
"-- (Unlike record_data(), this does not return a function, but runs directly.)\n"
"local function record_cache_stats()\n"
"    local info = mp.get_property_native(\"demuxer-cache-state\")\n"
"    if info == nil then\n"
"        return\n"
"    end\n"
"\n"
"    local a = info[\"reader-pts\"]\n"
"    local b = info[\"cache-end\"]\n"
"    if (a ~= nil) and (b ~= nil) then\n"
"        graph_add_value(cache_ahead_buf, b - a)\n"
"    end\n"
"\n"
"    graph_add_value(cache_speed_buf, info[\"raw-input-rate\"] or 0)\n"
"end\n"
"\n"
"cache_recorder_timer = mp.add_periodic_timer(0.25, record_cache_stats)\n"
"cache_recorder_timer:kill()\n"
"\n"
"-- Current page and <page key>:<page function> mapping\n"
"curr_page = o.key_page_1\n"
"pages = {\n"
"    [o.key_page_1] = { f = default_stats, desc = \"Default\" },\n"
"    [o.key_page_2] = { f = vo_stats, desc = \"Extended Frame Timings\", scroll = true },\n"
"    [o.key_page_3] = { f = cache_stats, desc = \"Cache Statistics\" },\n"
"    [o.key_page_4] = { f = perf_stats, desc = \"Internal performance info\", scroll = true },\n"
"}\n"
"\n"
"\n"
"-- Returns a function to record vsratio/jitter with the specified \140skip\140 value\n"
"local function record_data(skip)\n"
"    init_buffers()\n"
"    skip = max(skip, 0)\n"
"    local i = skip\n"
"    return function()\n"
"        if i < skip then\n"
"            i = i + 1\n"
"            return\n"
"        else\n"
"            i = 0\n"
"        end\n"
"\n"
"        if o.plot_vsync_jitter then\n"
"            local r = mp.get_property_number(\"vsync-jitter\", nil)\n"
"            if r then\n"
"                vsjitter_buf.pos = (vsjitter_buf.pos % vsjitter_buf.len) + 1\n"
"                vsjitter_buf[vsjitter_buf.pos] = r\n"
"                vsjitter_buf.max = max(vsjitter_buf.max, r)\n"
"            end\n"
"        end\n"
"\n"
"        if o.plot_vsync_ratio then\n"
"            local r = mp.get_property_number(\"vsync-ratio\", nil)\n"
"            if r then\n"
"                vsratio_buf.pos = (vsratio_buf.pos % vsratio_buf.len) + 1\n"
"                vsratio_buf[vsratio_buf.pos] = r\n"
"                vsratio_buf.max = max(vsratio_buf.max, r)\n"
"            end\n"
"        end\n"
"    end\n"
"end\n"
"\n"
"-- Call the function for \140page\140 and print it to OSD\n"
"local function print_page(page)\n"
"    if o.persistent_overlay then\n"
"        mp.set_osd_ass(0, 0, pages[page].f())\n"
"    else\n"
"        mp.osd_message(pages[page].f(), display_timer.oneshot and o.duration or o.redraw_delay + 1)\n"
"    end\n"
"end\n"
"\n"
"\n"
"local function clear_screen()\n"
"    if o.persistent_overlay then mp.set_osd_ass(0, 0, \"\") else mp.osd_message(\"\", 0) end\n"
"end\n"
"\n"
"local function scroll_delta(d)\n"
"    if display_timer.oneshot then display_timer:kill() ; display_timer:resume() end\n"
"    pages[curr_page].offset = (pages[curr_page].offset or 1) + d\n"
"    print_page(curr_page)\n"
"end\n"
"local function scroll_up() scroll_delta(-o.scroll_lines) end\n"
"local function scroll_down() scroll_delta(o.scroll_lines) end\n"
"\n"
"local function reset_scroll_offsets()\n"
"    for _, page in pairs(pages) do\n"
"        page.offset = nil\n"
"    end\n"
"end\n"
"local function bind_scroll()\n"
"    if not scroll_bound then\n"
"        mp.add_forced_key_binding(o.key_scroll_up, o.key_scroll_up, scroll_up, {repeatable=true})\n"
"        mp.add_forced_key_binding(o.key_scroll_down, o.key_scroll_down, scroll_down, {repeatable=true})\n"
"        scroll_bound = true\n"
"    end\n"
"end\n"
"local function unbind_scroll()\n"
"    if scroll_bound then\n"
"        mp.remove_key_binding(o.key_scroll_up)\n"
"        mp.remove_key_binding(o.key_scroll_down)\n"
"        scroll_bound = false\n"
"    end\n"
"end\n"
"local function update_scroll_bindings(k)\n"
"    if (pages[k].scroll) then\n"
"        bind_scroll()\n"
"    else\n"
"        unbind_scroll()\n"
"    end\n"
"end\n"
"\n"
"-- Add keybindings for every page\n"
"local function add_page_bindings()\n"
"    local function a(k)\n"
"        return function()\n"
"            reset_scroll_offsets()\n"
"            update_scroll_bindings(k)\n"
"            curr_page = k\n"
"            print_page(k)\n"
"            if display_timer.oneshot then display_timer:kill() ; display_timer:resume() end\n"
"        end\n"
"    end\n"
"    for k, _ in pairs(pages) do\n"
"        mp.add_forced_key_binding(k, k, a(k), {repeatable=true})\n"
"    end\n"
"    update_scroll_bindings(curr_page)\n"
"end\n"
"\n"
"\n"
"-- Remove keybindings for every page\n"
"local function remove_page_bindings()\n"
"    for k, _ in pairs(pages) do\n"
"        mp.remove_key_binding(k)\n"
"    end\n"
"    unbind_scroll()\n"
"end\n"
"\n"
"\n"
"local function process_key_binding(oneshot)\n"
"    reset_scroll_offsets()\n"
"    -- Stats are already being displayed\n"
"    if display_timer:is_enabled() then\n"
"        -- Previous and current keys were oneshot -> restart timer\n"
"        if display_timer.oneshot and oneshot then\n"
"            display_timer:kill()\n"
"            print_page(curr_page)\n"
"            display_timer:resume()\n"
"        -- Previous and current keys were toggling -> end toggling\n"
"        elseif not display_timer.oneshot and not oneshot then\n"
"            display_timer:kill()\n"
"            cache_recorder_timer:stop()\n"
"            clear_screen()\n"
"            remove_page_bindings()\n"
"            if recorder then\n"
"                mp.unobserve_property(recorder)\n"
"                recorder = nil\n"
"            end\n"
"        end\n"
"    -- No stats are being displayed yet\n"
"    else\n"
"        if not oneshot and (o.plot_vsync_jitter or o.plot_vsync_ratio) then\n"
"            recorder = record_data(o.skip_frames)\n"
"            -- Rely on the fact that \"vsync-ratio\" is updated at the same time.\n"
"            -- Using \"none\" to get a sample any time, even if it does not change.\n"
"            -- Will stop working if \"vsync-jitter\" property change notification\n"
"            -- changes, but it's fine for an internal script.\n"
"            mp.observe_property(\"vsync-jitter\", \"none\", recorder)\n"
"        end\n"
"        if not oneshot then\n"
"            cache_ahead_buf = {0, pos = 1, len = 50, max = 0}\n"
"            cache_speed_buf = {0, pos = 1, len = 50, max = 0}\n"
"            cache_recorder_timer:resume()\n"
"        end\n"
"        display_timer:kill()\n"
"        display_timer.oneshot = oneshot\n"
"        display_timer.timeout = oneshot and o.duration or o.redraw_delay\n"
"        add_page_bindings()\n"
"        print_page(curr_page)\n"
"        display_timer:resume()\n"
"    end\n"
"end\n"
"\n"
"\n"
"-- Create the timer used for redrawing (toggling) or clearing the screen (oneshot)\n"
"-- The duration here is not important and always set in process_key_binding()\n"
"display_timer = mp.add_periodic_timer(o.duration,\n"
"    function()\n"
"        if display_timer.oneshot then\n"
"            display_timer:kill() ; clear_screen() ; remove_page_bindings()\n"
"        else\n"
"            print_page(curr_page)\n"
"        end\n"
"    end)\n"
"display_timer:kill()\n"
"\n"
"-- Single invocation key binding\n"
"mp.add_key_binding(o.key_oneshot, \"display-stats\", function() process_key_binding(true) end,\n"
"    {repeatable=true})\n"
"\n"
"-- Toggling key binding\n"
"mp.add_key_binding(o.key_toggle, \"display-stats-toggle\", function() process_key_binding(false) end,\n"
"    {repeatable=false})\n"
"\n"
"-- Single invocation bindings without key, can be used in input.conf to create\n"
"-- bindings for a specific page: \"e script-binding stats/display-page-2\"\n"
"for k, _ in pairs(pages) do\n"
"    mp.add_key_binding(nil, \"display-page-\" .. k,\n"
"        function()\n"
"            curr_page = k\n"
"            process_key_binding(true)\n"
"        end, {repeatable=true})\n"
"end\n"
"\n"
"-- Reprint stats immediately when VO was reconfigured, only when toggled\n"
"mp.register_event(\"video-reconfig\",\n"
"    function()\n"
"        if display_timer:is_enabled() then\n"
"            print_page(curr_page)\n"
"        end\n"
"    end)\n"