#
# ~/.bashrc
#

# If not running interactively, don't do anything
[[ $- != *i* ]] && return

alias ls='ls --color=auto'
PS1='[\u@\h \W]\$ '

PS1='\[\033[1;36m\]\u\[\033[1;31m\]@\[\033[1;32m\]\h:\[\033[1;35m\]\w\[\033[1;31m\]\$\[\033[0m\] '

fcd() {
	cd "$(find -type d | fzf)"
}
open() {
	xdg-open "$(find -path ./.cache/paru/clone/ttyper -prune -false -o -type f | fzf)"
}

alias getpath="find -type f | fzf | sed 's/^..//' | tr -d '\n' | xclip -selection c"


[ -d "$HOME/.w3m/bin" ] && PATH="$HOME/.w3m/bin:$PATH"



export PATH="$HOME/.emacs.d/bin:$PATH"

alias cpu-temp="$(sensors | grep edge | grep -o '.\{9\}$' )"



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




show_colour() {
    perl -e 'foreach $a(@ARGV){print "\e[48:2::".join(":",unpack("C*",pack("H*",$a)))."m \e[49m "};print "\n"' "$@"
}


alias bandwidth-data="cat ~/.cache/bandwidth.txt"

alias vnstat="vnstat -i  wlp7s0f3u3 --style 1"

alias shownotes-write="nvim ~/.local/share/shownotes"

export PROMPT_COMMAND='history -a'

alias vimx="vim -x"

alias fhf="cat ~/.cache/zsh/history | sort | uniq | fzf | xclip -selection copy"



books ()  {
  file_name=$(cd ~/vimwiki/; find . -type f \( -regex ".*\.pdf" -o -regex ".*\.djvu" \) | cut -c 3- | fzf --reverse -q "$*")

  [ -n "$file_name" ] && zathura --fork "$HOME/vimwiki/$file_name"
}
