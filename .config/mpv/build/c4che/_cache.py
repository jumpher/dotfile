AR = ['/usr/bin/ar']
ARFLAGS = ['rcs']
BASHDIR = '/usr/local/share/bash-completion/completions'
BINDIR = '/usr/local/bin'
BIN_PERL = ['/usr/bin/perl']
CC = ['/usr/bin/cc']
CCLNK_SRC_F = []
CCLNK_TGT_F = ['-o']
CC_NAME = 'gcc'
CC_SRC_F = []
CC_TGT_F = ['-c', '-o']
CC_VERSION = ('10', '2', '0')
CFLAGS = ['-D_ISOC99_SOURCE', '-D_GNU_SOURCE', '-D_FILE_OFFSET_BITS=64', '-Wall', '-std=c11', '-O2', '-g', '-Werror=implicit-function-declaration', '-Wno-error=deprecated-declarations', '-Wno-error=unused-function', '-Wempty-body', '-Wdisabled-optimization', '-Wstrict-prototypes', '-Wno-format-zero-length', '-Werror=format-security', '-Wno-redundant-decls', '-Wvla', '-Wno-format-truncation', '-Wimplicit-fallthrough', '-fno-math-errno', '-Wall', '-Wundef', '-Wmissing-prototypes', '-Wshadow', '-Wno-switch', '-Wparentheses', '-Wpointer-arith', '-Wno-pointer-sign', '-Wno-unused-result']
CFLAGS_MACBUNDLE = ['-fPIC']
CFLAGS_cshlib = ['-fPIC']
CFLAGS_pthreads = ['-pthread']
CFLAGS_pulse = ['-pthread']
COMPILER_CC = 'gcc'
CONFDIR = '/usr/local/etc/mpv'
CONFLOADDIR = '/usr/local/etc/mpv'
CPPPATH_ST = '-I%s'
CXXFLAGS_pulse = ['-pthread']
DATADIR = '/usr/local/share'
DATAROOTDIR = '/usr/local/share'
DEFINES = []
DEFINES_ST = '-D%s'
DEFINES_pulse = ['_REENTRANT']
DEFINE_COMMENTS = {'DEFAULT_DVD_DEVICE': '', 'DEFAULT_CDROM_DEVICE': '', 'HAVE_LGPL': '', 'HAVE_GPL': '', 'HAVE_CPLAYER': '', 'HAVE_LIBMPV_SHARED': '', 'HAVE_LIBMPV_STATIC': '', 'HAVE_STATIC_BUILD': '', 'HAVE_BUILD_DATE': '', 'HAVE_OPTIMIZE': '', 'HAVE_DEBUG_BUILD': '', 'HAVE_TESTS': '', 'HAVE_TA_LEAK_REPORT': '', 'HAVE_MANPAGE_BUILD': '', 'HAVE_HTML_BUILD': '', 'HAVE_PDF_BUILD': '', 'HAVE_LIBDL': '', 'HAVE_CPLUGINS': '', 'HAVE_ASM': '', 'HAVE_CLANG_DATABASE': '', 'HAVE_SWIFT_STATIC': '', 'HAVE_NOEXECSTACK': '', 'HAVE_LIBM': '', 'HAVE_MINGW': '', 'HAVE_POSIX': '', 'HAVE_ANDROID': '', 'HAVE_TVOS': '', 'HAVE_EGL_ANDROID': '', 'HAVE_POSIX_OR_MINGW': '', 'HAVE_SWIFT': '', 'HAVE_UWP': '', 'HAVE_WIN32_DESKTOP': '', 'HAVE_WIN32_INTERNAL_PTHREADS': '', 'HAVE_PTHREADS': '', 'HAVE_PTHREAD_DEBUG': '', 'HAVE_STDATOMIC': '', 'HAVE_LIBRT': '', 'HAVE_ICONV': '', 'HAVE_DOS_PATHS': '', 'HAVE_GLOB_POSIX': '', 'HAVE_GLOB_WIN32': '', 'HAVE_GLOB': '', 'HAVE_VT_H': '', 'HAVE_CONSIO_H': '', 'HAVE_GBM_H': '', 'HAVE_GLIBC_THREAD_NAME': '', 'HAVE_OSX_THREAD_NAME': '', 'HAVE_BSD_THREAD_NAME': '', 'HAVE_BSD_FSTATFS': '', 'HAVE_LINUX_FSTATFS': '', 'HAVE_LINUX_INPUT_EVENT_CODES': '', 'HAVE_LUA': '', 'HAVE_52ARCH': '', 'HAVE_JAVASCRIPT': '', 'HAVE_LIBASS': '', 'HAVE_ZLIB': '', 'HAVE_LIBBLURAY': '', 'HAVE_DVDNAV': '', 'HAVE_CDDA': '', 'HAVE_UCHARDET': '', 'HAVE_RUBBERBAND': '', 'HAVE_ZIMG': '', 'HAVE_LCMS2': '', 'HAVE_VAPOURSYNTH': '', 'HAVE_LIBARCHIVE': '', 'HAVE_DVBIN': '', 'HAVE_SDL2': '', 'HAVE_SDL2_GAMEPAD': '', 'HAVE_FFMPEG': '', 'HAVE_LIBAVDEVICE': '', 'HAVE_FFMPEG_STRICT_ABI': '', 'HAVE_SDL2_AUDIO': '', 'HAVE_PULSE': '', 'HAVE_JACK': '', 'HAVE_OPENAL': '', 'HAVE_OPENSLES': '', 'HAVE_ALSA': '', 'HAVE_COREAUDIO': '', 'HAVE_AUDIOUNIT': '', 'HAVE_WASAPI': '', 'HAVE_SDL2_VIDEO': '', 'HAVE_COCOA': '', 'HAVE_DRM': '', 'HAVE_GBM': '', 'HAVE_WAYLAND_PROTOCOLS': '', 'HAVE_WAYLAND': '', 'HAVE_MEMFD_CREATE': '', 'HAVE_X11': '', 'HAVE_XV': '', 'HAVE_GL_COCOA': '', 'HAVE_GL_X11': '', 'HAVE_RPI': '', 'HAVE_EGL': '', 'HAVE_EGL_X11': '', 'HAVE_EGL_DRM': '', 'HAVE_GL_WAYLAND': '', 'HAVE_GL_WIN32': '', 'HAVE_GL_DXINTEROP': '', 'HAVE_EGL_ANGLE': '', 'HAVE_EGL_ANGLE_LIB': '', 'HAVE_EGL_ANGLE_WIN32': '', 'HAVE_VDPAU': '', 'HAVE_VDPAU_GL_X11': '', 'HAVE_VAAPI': '', 'HAVE_VAAPI_X11': '', 'HAVE_VAAPI_WAYLAND': '', 'HAVE_VAAPI_DRM': '', 'HAVE_VAAPI_X_EGL': '', 'HAVE_VAAPI_EGL': '', 'HAVE_CACA': '', 'HAVE_JPEG': '', 'HAVE_DIRECT3D': '', 'HAVE_SHADERC_SHARED': '', 'HAVE_SHADERC_STATIC': '', 'HAVE_SHADERC': '', 'HAVE_SPIRV_CROSS_SHARED': '', 'HAVE_SPIRV_CROSS_STATIC': '', 'HAVE_SPIRV_CROSS': '', 'HAVE_D3D11': '', 'HAVE_IOS_GL': '', 'HAVE_PLAIN_GL': '', 'HAVE_GL': '', 'HAVE_LIBPLACEBO': '', 'HAVE_VULKAN': '', 'HAVE_VAAPI_VULKAN': '', 'HAVE_EGL_HELPERS': '', 'HAVE_SIXEL': '', 'HAVE_VIDEOTOOLBOX_HWACCEL': '', 'HAVE_VIDEOTOOLBOX_GL': '', 'HAVE_D3D_HWACCEL': '', 'HAVE_D3D9_HWACCEL': '', 'HAVE_GL_DXINTEROP_D3D9': '', 'HAVE_FFNVCODEC': '', 'HAVE_CUDA_HWACCEL': '', 'HAVE_CUDA_INTEROP': '', 'HAVE_RPI_MMAL': '', 'HAVE_WIN32_EXECUTABLE': '', 'HAVE_MACOS_TOUCHBAR': '', 'HAVE_MACOS_10_11_FEATURES': '', 'HAVE_MACOS_10_12_2_FEATURES': '', 'HAVE_MACOS_10_14_FEATURES': '', 'HAVE_MACOS_MEDIA_PLAYER': '', 'HAVE_MACOS_COCOA_CB': '', 'CONFIGURATION': '', 'MPV_CONFDIR': '', 'FULLCONFIG': ''}
DEST_BINFMT = 'elf'
DEST_CPU = 'x86_64'
DEST_OS = 'linux'
DOCDIR = '/usr/local/share/doc/mpv'
DVIDIR = '/usr/local/share/doc/mpv'
EXEC_PREFIX = '/usr/local'
HAVE_52ARCH = 1
HAVE_ALSA = 1
HAVE_CACA = 1
HAVE_CPLUGINS = 1
HAVE_DRM = 1
HAVE_EGL = 1
HAVE_FFMPEG = 1
HAVE_GBM = 1
HAVE_GBM_H = 1
HAVE_GLIBC_THREAD_NAME = 1
HAVE_GLOB_POSIX = 1
HAVE_GL_WAYLAND = 1
HAVE_ICONV = 1
HAVE_JACK = 1
HAVE_JAVASCRIPT = 1
HAVE_JPEG = 1
HAVE_LCMS2 = 1
HAVE_LIBARCHIVE = 1
HAVE_LIBASS = 1
HAVE_LIBAVDEVICE = 1
HAVE_LIBBLURAY = 1
HAVE_LIBDL = 1
HAVE_LIBM = 1
HAVE_LIBPLACEBO = 1
HAVE_LIBRT = 1
HAVE_LINUX_FSTATFS = 1
HAVE_LINUX_INPUT_EVENT_CODES = 1
HAVE_MEMFD_CREATE = 1
HAVE_NOEXECSTACK = 1
HAVE_POSIX = 1
HAVE_PTHREADS = 1
HAVE_PULSE = 1
HAVE_RUBBERBAND = 1
HAVE_SHADERC_SHARED = 1
HAVE_STDATOMIC = 1
HAVE_UCHARDET = 1
HAVE_VAAPI = 1
HAVE_VAAPI_DRM = 1
HAVE_VAAPI_WAYLAND = 1
HAVE_VAAPI_X11 = 1
HAVE_VDPAU = 1
HAVE_VT_H = 1
HAVE_VULKAN = 1
HAVE_WAYLAND = 1
HAVE_WAYLAND_PROTOCOLS = 1
HAVE_X11 = 1
HAVE_XV = 1
HAVE_ZLIB = 1
HTMLDIR = '/usr/local/share/doc/mpv'
INCLUDEDIR = '/usr/local/include'
INCLUDES_52arch = ['/usr/include/lua5.2']
INCLUDES_drm = ['/usr/include/libdrm']
INCLUDES_libass = ['/usr/include/freetype2', '/usr/include/libpng16', '/usr/include/harfbuzz', '/usr/include/glib-2.0', '/usr/lib/glib-2.0/include', '/usr/include/fribidi']
INCLUDES_libbluray = ['/usr/include/libxml2', '/usr/include/freetype2', '/usr/include/libpng16', '/usr/include/harfbuzz', '/usr/include/glib-2.0', '/usr/lib/glib-2.0/include']
INCLUDES_uchardet = ['/usr/include/uchardet']
INFODIR = '/usr/local/share/info'
LIBDIR = '/usr/local/lib'
LIBEXECDIR = '/usr/local/libexec'
LIBPATH_ST = '-L%s'
LIB_52arch = ['lua5.2', 'm']
LIB_ST = '-l%s'
LIB_alsa = ['asound']
LIB_caca = ['caca']
LIB_drm = ['drm']
LIB_egl = ['EGL']
LIB_ffmpeg = ['avutil', 'avcodec', 'avformat', 'swscale', 'avfilter', 'swresample']
LIB_gbm = ['gbm']
LIB_gl_wayland = ['wayland-egl', 'wayland-client']
LIB_jack = ['jack', 'pthread']
LIB_javascript = ['mujs']
LIB_jpeg = ['jpeg']
LIB_lcms2 = ['lcms2']
LIB_libarchive = ['archive']
LIB_libass = ['ass']
LIB_libavdevice = ['avdevice']
LIB_libbluray = ['bluray']
LIB_libdl = ['dl']
LIB_libm = ['m']
LIB_libplacebo = ['placebo']
LIB_librt = ['rt']
LIB_pulse = ['pulse']
LIB_rubberband = ['rubberband']
LIB_shaderc_shared = ['shaderc_shared']
LIB_uchardet = ['uchardet']
LIB_vaapi = ['va']
LIB_vaapi_drm = ['va-drm', 'va']
LIB_vaapi_wayland = ['va-wayland', 'va', 'wayland-client']
LIB_vaapi_x11 = ['va-x11', 'va']
LIB_vdpau = ['vdpau']
LIB_vulkan = ['vulkan']
LIB_wayland = ['wayland-client', 'wayland-cursor', 'xkbcommon']
LIB_x11 = ['X11', 'Xss', 'Xext', 'Xinerama', 'Xrandr']
LIB_xv = ['Xv']
LIB_zlib = ['z']
LINKFLAGS = ['-rdynamic']
LINKFLAGS_MACBUNDLE = ['-bundle', '-undefined', 'dynamic_lookup']
LINKFLAGS_cplugins = ['-rdynamic']
LINKFLAGS_cshlib = ['-shared']
LINKFLAGS_cstlib = ['-Wl,-Bstatic']
LINKFLAGS_noexecstack = ['-Wl,-z,noexecstack']
LINKFLAGS_pthreads = ['-pthread']
LINKFLAGS_pulse = ['-pthread']
LINK_CC = ['/usr/bin/cc']
LOCALEDIR = '/usr/local/share/locale'
LOCALSTATEDIR = '/usr/local/var'
MANDIR = '/usr/local/share/man'
OLDINCLUDEDIR = '/usr/include'
PACKAGE = 'mpv'
PDFDIR = '/usr/local/share/doc/mpv'
PKG_CONFIG = ['/usr/bin/pkg-config']
PREFIX = '/usr/local'
PSDIR = '/usr/local/share/doc/mpv'
RPATH_ST = '-Wl,-rpath,%s'
SBINDIR = '/usr/local/sbin'
SHAREDSTATEDIR = '/usr/local/com'
SHLIB_MARKER = '-Wl,-Bdynamic'
SONAME_ST = '-Wl,-h,%s'
STLIBPATH_ST = '-L%s'
STLIB_MARKER = '-Wl,-Bstatic'
STLIB_ST = '-l%s'
SYSCONFDIR = '/usr/local/etc'
WAYSCAN = ['/usr/bin/wayland-scanner']
WL_PROTO_DIR = '//usr/share/wayland-protocols'
ZSHDIR = '/usr/local/share/zsh/site-functions'
cfg_files = ['/home/ram/.config/mpv/build/config.h']
cprogram_PATTERN = '%s'
cshlib_PATTERN = 'lib%s.so'
cstlib_PATTERN = 'lib%s.a'
define_key = []
known_deps = ['win32-internal-pthreads', 'openal', 'vdpau', 'macos-media-player', 'vaapi', 'jpeg', 'win32-desktop', 'shaderc', 'swift-static', 'libmpv-shared', 'caca', 'vulkan', 'wayland', 'spirv-cross-static', 'd3d-hwaccel', 'mingw', 'cdda', 'gbm.h', 'dos-paths', 'sdl2-gamepad', 'sdl2-audio', 'vt.h', 'optimize', 'gbm', 'gpl', 'gl-dxinterop', 'macos-10-11-features', 'os-linux', 'sixel', 'cuda-interop', 'static-build', 'egl-drm', 'tests', 'pthreads', 'macos-10-14-features', 'glob', 'vaapi-wayland', 'libarchive', 'spirv-cross-shared', 'videotoolbox-gl', 'consio.h', 'libass', 'osx-thread-name', 'stdatomic', 'ffnvcodec', 'wayland-scanner', 'rubberband', 'noexecstack', 'libm', 'plain-gl', 'libplacebo', 'gl-dxinterop-d3d9', 'posix-or-mingw', 'libdl', 'egl', 'clang-database', 'vaapi-x-egl', 'gl-win32', 'uwp', 'egl-angle-win32', 'bsd-thread-name', 'manpage-build', 'lua', 'sdl2', 'cplayer', 'cuda-hwaccel', 'spirv-cross', 'jack', 'libbluray', 'coreaudio', 'vapoursynth', 'gl', 'shaderc-shared', 'gl-cocoa', 'egl-angle-lib', 'videotoolbox-hwaccel', 'html-build', 'glob-win32', 'ta-leak-report', 'vaapi-vulkan', 'd3d9-hwaccel', 'pdf-build', 'wayland-protocols', 'cocoa', 'rpi-mmal', 'audiounit', 'debug-build', 'swift', 'd3d11', 'ffmpeg-strict-abi', 'glob-posix', 'xv', 'uchardet', 'javascript', 'direct3d', 'vaapi-x11', 'egl-helpers', 'egl-angle', 'sdl2-video', 'macos-10-12-2-features', 'wasapi', 'macos-touchbar', 'alsa', 'build-date', 'pulse', 'android', 'librt', 'glibc-thread-name', 'bsd-fstatfs', 'egl-x11', 'x11', 'gl-x11', 'vdpau-gl-x11', 'linux-input-event-codes', 'vaapi-drm', 'drm', 'gl-wayland', 'libmpv-static', 'linux-fstatfs', 'ffmpeg', 'iconv', 'dvdnav', 'vaapi-egl', 'dvbin', 'memfd_create', 'asm', 'zlib', 'egl-android', 'lgpl', 'lcms2', 'zimg', 'opensles', 'rpi', 'macos-cocoa-cb', 'posix', 'ios-gl', 'shaderc-static', 'cplugins', 'win32-executable', 'tvos', 'pthread-debug', 'libavdevice']
macbundle_PATTERN = '%s.bundle'
satisfied_deps = ['egl-drm', 'gl', 'shaderc-shared', 'pthreads', 'glob', 'vaapi-wayland', 'build-date', 'pulse', 'librt', 'libarchive', 'glibc-thread-name', 'vdpau', 'vaapi-vulkan', 'libass', 'egl-x11', 'stdatomic', 'x11', 'wayland-protocols', 'linux-input-event-codes', 'vaapi', 'vaapi-drm', 'jpeg', 'shaderc', 'drm', 'gl-wayland', 'debug-build', 'linux-fstatfs', 'rubberband', 'ffmpeg', 'iconv', 'wayland-scanner', 'noexecstack', 'caca', 'vaapi-egl', 'vulkan', 'memfd_create', 'glob-posix', 'libm', 'asm', 'zlib', 'wayland', 'xv', 'libplacebo', 'uchardet', 'javascript', 'posix-or-mingw', 'lcms2', 'gbm.h', 'libdl', 'egl', 'vaapi-x11', 'egl-helpers', 'vaapi-x-egl', 'posix', 'vt.h', '52arch', 'libavdevice', 'lua', 'libbluray', 'cplayer', 'optimize', 'gbm', 'cplugins', 'jack', 'gpl', 'alsa', 'os-linux']
