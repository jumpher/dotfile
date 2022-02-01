//Modify this file to change whatever commands output to your statusbar, and recompile using the make command.
static const Block blocks[] = {
	/*Icon*/	/*Command*/		/*Update Interval*/	/*Update Signal*/
	/* {"⌨", "sb-kbselect", 0, 30}, */
	{"", "cat /tmp/recordingicon 2>/dev/null",	0,	9},
	{"", "[ -f /tmp/some_lock_file.lock ] && echo '⏲️ '",	 0, 10},
	{"", "[ -f /tmp/pomo-icon.lock ] && echo '📔 '",	 0, 10},
	{"",	"sb-tasks",	10,	26},
	{"",	"sb-music",	0,	11},
	{"",	"sb-oye",	0,	10},
	{"",	"sb-pacpackages",	0,	8},
	{"",	"sb-news",		0,	6},
	{"",	"sb-torrent",	20,	7},
	{"",	"sb-memory",	10,	14},
	{"",	"sb-nettraf",	1,	16},
	{"📅 ",	"sb-clock",	60,	1},
	{"",	"sb-internet",	5,       4},
};



//Sets delimiter between status commands. NULL character ('\0') means no delimiter.
static char *delim = "  |  ";

// Have dwmblocks automatically recompile and run when you edit this file in
// vim with the following line in your vimrc/init.vim:

// autocmd BufWritePost ~/.local/src/dwmblocks/config.h !cd ~/.local/src/dwmblocks/; sudo make install && { killall -q dwmblocks;setsid dwmblocks & }
	/*{"",	"sb-volume",	0,	10},*/
	/*{"",	"sb-oye",	0,	10},*/

