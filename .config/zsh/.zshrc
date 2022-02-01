# Luke's config for the Zoomer Shell


shuf ~/Desktop/Word.txt | head -n 1


# Enable colors and change prompt:
autoload -U colors && colors	# Load colors
PS1="%B%{$fg[red]%}[%{$fg[yellow]%}%n%{$fg[green]%}@%{$fg[blue]%}%M %{$fg[magenta]%}%~%{$fg[red]%}]%{$reset_color%}$%b "
setopt autocd		# Automatically cd into typed directory.
stty stop undef		# Disable ctrl-s to freeze terminal.
setopt interactive_comments

# History in cache directory:
HISTSIZE=10000000
SAVEHIST=10000000
HISTFILE=~/.cache/zsh/history

# Load aliases and shortcuts if existent.
[ -f "${XDG_CONFIG_HOME:-$HOME/.config}/shell/shortcutrc" ] && source "${XDG_CONFIG_HOME:-$HOME/.config}/shell/shortcutrc"
[ -f "${XDG_CONFIG_HOME:-$HOME/.config}/shell/aliasrc" ] && source "${XDG_CONFIG_HOME:-$HOME/.config}/shell/aliasrc"
[ -f "${XDG_CONFIG_HOME:-$HOME/.config}/shell/zshnameddirrc" ] && source "${XDG_CONFIG_HOME:-$HOME/.config}/shell/zshnameddirrc"

# Basic auto/tab complete:
autoload -U compinit
zstyle ':completion:*' menu select
zmodload zsh/complist
compinit
_comp_options+=(globdots)		# Include hidden files.

# vi mode
bindkey -v
export KEYTIMEOUT=1

# Use vim keys in tab complete menu:
bindkey -M menuselect 'h' vi-backward-char
bindkey -M menuselect 'k' vi-up-line-or-history
bindkey -M menuselect 'l' vi-forward-char
bindkey -M menuselect 'j' vi-down-line-or-history
bindkey -v '^?' backward-delete-char

# Change cursor shape for different vi modes.
function zle-keymap-select () {
    case $KEYMAP in
        vicmd) echo -ne '\e[1 q';;      # block
        viins|main) echo -ne '\e[5 q';; # beam
    esac
}
zle -N zle-keymap-select
zle-line-init() {
    zle -K viins # initiate `vi insert` as keymap (can be removed if `bindkey -V` has been set elsewhere)
    echo -ne "\e[5 q"
}
zle -N zle-line-init
echo -ne '\e[5 q' # Use beam shape cursor on startup.
preexec() { echo -ne '\e[5 q' ;} # Use beam shape cursor for each new prompt.

# Use lf to switch directories and bind it to ctrl-o
lfcd () {
    tmp="$(mktemp)"
    lf -last-dir-path="$tmp" "$@"
    if [ -f "$tmp" ]; then
        dir="$(cat "$tmp")"
        rm -f "$tmp" >/dev/null
        [ -d "$dir" ] && [ "$dir" != "$(pwd)" ] && cd "$dir"
    fi
}
bindkey -s '^o' 'lfcd\n'

bindkey -s '^a' 'bc -lq\n'

bindkey -s '^f' 'cd "$(dirname "$(fzf)")"\n'

bindkey '^[[P' delete-char






fcd() {
	cd "$(find . > ~/.cache/files_and_folders 2> >(grep -v 'Permission denied' >&2) -type d | fzf)"
}

open() {
	xdg-open "$(find . > ~/.cache/files_and_folders 2> >(grep -v 'Permission denied' >&2) -type f | fzf)"
}

alias getpath="find . > ~/.cache/files_and_folders 2> >(grep -v 'Permission denied' >&2) -type f | fzf | sed 's/^..//' | tr -d '\n' | xclip -selection c"



alias fhf="cat ~/.cache/zsh/history | cut -c 8- | sort | fzf | tr '\\n' ' ' | xclip -selection c "

alias fgh="history | cut -c 8- | sort | fzf | tr '\\n' ' ' | xclip -selection c "










tsm-clearcompleted() {
	transmission-remote -l | grep 100% | grep Done | \
	awk '(print $1)' | xargs -n | -I % transmission-remote -t % -r ;}
tsm() {transmission-remote -l ;}
tsm-altspeedenable() { transmission-remote --alt-speed ;}
tsm-altspeeddisable() { transmission-remote --no-alt-speed ;}
tsm-add() { transmission-remote -a "$1" ;}
tsm-pause() { transmission-remote -t "$1" --stop ;}
tsm-start()  { transmission-remote -t "$1" --start ;}
tsm-purge() { transmission-remote -t "$1" --remove-and-delete ;}
tsm-remove() { transmission-remote -t "$1" -r ;}
tsm-info() { transmission-remote -t "$1" -i ;}





function countdown(){
   date1=$((`date +%s` + $1));
   while [ "$date1" -ge `date +%s` ]; do
     echo -ne "$(date -u --date @$(($date1 - `date +%s`)) +%H:%M:%S)\r";
     sleep 0.1
   done
}
function stopwatch(){
  date1=`date +%s`;
   while true; do
    echo -ne "$(date -u --date @$((`date +%s` - $date1)) +%H:%M:%S)\r";
    sleep 0.1
   done
}



color_hex() {
    perl -e 'foreach $a(@ARGV){print "\e[48:2::".join(":",unpack("C*",pack("H*",$a)))."m \e[49m "};print "\n"' "$@"
}

alias vim="nvim"

export SPOTIPY_CLIENT_ID='10a30dcf1510418f8d4f88ba20e5a936'

export SPOTIPY_CLIENT_SECRET='10ea0560aad74a2eaf00090c36da8f70'

export TESSDATA_PREFIX='/usr/local/share/'

export PATH=$PATH:/home/ram/.local/share/cargo/bin

alias cpu-temp="$(sensors | grep edge | grep -o '.\{9\}$' )"

alias phrase="nvim ~/Desktop/Phrase.txt"

alias weather="curl wttr.in/Taranagar"

alias word="nvim ~/Desktop/Word.txt"

alias zxc="ranger"

alias bored="apropos . | shuf -n 1 | awk '{print$1}' | xargs man"

alias neofetch="neofetch --cpu_temp C --ascii_distro opensuse  --disk_percent on --color_block off"

alias gdrivedl="python ~/.xfrok/scripts/gdrivedl/gdrivedl.py"

alias mpv-gui="mpv --player-operation-mode=pseudo-gui"

alias vimx="/usr/bin/vim -x"

alias sdcv="sdcv -c"

alias ttyper-most="ttyper -w 200 -l english1000"

alias qwe="w3m  https://lite.duckduckgo.com/lite/"

alias youtube-dl="yt-dlp"

alias ytaria2c="yt-dlp --external-downloader=aria2c"

alias yt480p="youtube-dl -f 244+140"

# Download Youtube videos in the highest quality possible. Downloads to Videos folder
alias ytbestboth='noglob youtube-dl --ignore-errors --continue --no-overwrites --format 'bestvideo+bestaudio' "$@"'

# Download youtubevideo as mp3
alias ytaudio='noglob youtube-dl -x --ignore-errors --continue --no-overwrites --audio-format 'mp3' --audio-quality 0  "$@"'

alias ytopus='youtube-dl -x --ignore-errors --continue --no-overwrites --audio-format "opus" --audio-quality 0 -o "~/.Music/%(title)s.%(ext)s" "$@"'

alias mv="mv -iv"

alias cp="cp -riv"

alias mkdir="mkdir -vp"

alias rm='rm --one-file-system -I'

alias restart-karde='sudo init 6'

bindkey "^[[A" history-search-backward

bindkey "^[[B" history-search-forward

alias texas-time="TZ=America/North_Dakota/New_Salem date"

show_colour() {
    perl -e 'foreach $a(@ARGV){print "\e[48;2;".join(";",unpack("C*",pack("H*",$a)))."m \e[49m "};print "\n"' "$@"
}

alias random-colors="librewolf .xfrok/scripts/Random-Color-Palette-Generator/index.html"

alias ip-address="curl ipinfo.io/ip"

alias trash='mv --backup=numbered -fvt $XDG_DATA_HOME/Trash --'






 [[ ! -r /home/ram/.opam/opam-init/init.zsh ]] || source /home/ram/.opam/opam-init/init.zsh  > /dev/null 2> /dev/null


# Edit line in vim with ctrl-e:
autoload edit-command-line; zle -N edit-command-line
bindkey '^e' edit-command-line

# Load syntax highlighting; should be last.
source /usr/share/zsh/plugins/fast-syntax-highlighting/fast-syntax-highlighting.plugin.zsh 2>/dev/null
