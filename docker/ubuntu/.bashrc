# ~/.bashrc: executed by bash(1) for non-login shells.
# see /usr/share/doc/bash/examples/startup-files (in the package bash-doc)
# for examples

# If not running interactively, don't do anything
[ -z "$PS1" ] && return

# don't put duplicate lines in the history. See bash(1) for more options
# ... or force ignoredups and ignorespace
HISTCONTROL=ignoredups:ignorespace

# append to the history file, don't overwrite it
shopt -s histappend

# for setting history length see HISTSIZE and HISTFILESIZE in bash(1)
HISTSIZE=1000
HISTFILESIZE=2000

# check the window size after each command and, if necessary,
# update the values of LINES and COLUMNS.
shopt -s checkwinsize

# make less more friendly for non-text input files, see lesspipe(1)
[ -x /usr/bin/lesspipe ] && eval "$(SHELL=/bin/sh lesspipe)"

# set variable identifying the chroot you work in (used in the prompt below)
if [ -z "$debian_chroot" ] && [ -r /etc/debian_chroot ]; then
    debian_chroot=$(cat /etc/debian_chroot)
fi

# set a fancy prompt (non-color, unless we know we "want" color)
case "$TERM" in
    xterm-color) color_prompt=yes;;
esac

# uncomment for a colored prompt, if the terminal has the capability; turned
# off by default to not distract the user: the focus in a terminal window
# should be on the output of commands, not on the prompt
#force_color_prompt=yes

if [ -n "$force_color_prompt" ]; then
    if [ -x /usr/bin/tput ] && tput setaf 1 >&/dev/null; then
	# We have color support; assume it's compliant with Ecma-48
	# (ISO/IEC-6429). (Lack of such support is extremely rare, and such
	# a case would tend to support setf rather than setaf.)
	color_prompt=yes
    else
	color_prompt=
    fi
fi

if [ "$color_prompt" = yes ]; then
    PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[00m\]\$ '
else
    PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w\$ '
fi
unset color_prompt force_color_prompt

# If this is an xterm set the title to user@host:dir
case "$TERM" in
xterm*|rxvt*)
    PS1="\[\e]0;${debian_chroot:+($debian_chroot)}\u@\h: \w\a\]$PS1"
    ;;
*)
    ;;
esac

# enable color support of ls and also add handy aliases
if [ -x /usr/bin/dircolors ]; then
    test -r ~/.dircolors && eval "$(dircolors -b ~/.dircolors)" || eval "$(dircolors -b)"
    alias ls='ls --color=auto'
    #alias dir='dir --color=auto'
    #alias vdir='vdir --color=auto'

    alias grep='grep --color=auto'
    alias fgrep='fgrep --color=auto'
    alias egrep='egrep --color=auto'
fi

# some more ls aliases
alias ll='ls -alF'
alias la='ls -A'
alias l='ls -CF'

# Alias definitions.
# You may want to put all your additions into a separate file like
# ~/.bash_aliases, instead of adding them here directly.
# See /usr/share/doc/bash-doc/examples in the bash-doc package.

if [ -f ~/.bash_aliases ]; then
    . ~/.bash_aliases
fi

# enable programmable completion features (you don't need to enable
# this, if it's already enabled in /etc/bash.bashrc and /etc/profile
# sources /etc/bash.bashrc).
#if [ -f /etc/bash_completion ] && ! shopt -oq posix; then
#    . /etc/bash_completion
#fi
# GIT_PS1_SHOWDIRTYSTATE=true









## custom_yshimoda

# Add git branch if its present to PS1
# parse_git_branch() {
#  git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
# }
# if [ "$color_prompt" = yes ]; then
#  PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[01;31m\]$(parse_git_branch)\[\033[00m\]\$ '
# else
#  PS1='${debian_chroot:+($debian_chroot)}\u@\h:\w$(parse_git_branch)\$ '
# fi
parse_git_branch() {
 git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
} 
PS1='${debian_chroot:+($debian_chroot)}\[\033[01;32m\]\u@\h\[\033[00m\]:\[\033[01;34m\]\w\[\033[01;31m\]$(parse_git_branch)\[\033[00m\]\$ '

# 42Tokyo
alias f='c_formatter_42'
alias n='norminette -R CheckForbiddenSourceHeader'
alias nh='norminette -R CheckDefine'

# c
alias gccw='gcc -Wall -Wextra -Werror'

# docker
alias dc='docker compose'
alias dcb='docker compose build'
alias dcd='docker compose down'
# alias dcr='docker compose run'
alias dcu='docker compose up -d'
alias dk='docker'
alias dke='docker exec -it'
alias dki='docker images'
alias dkl='docker logs'
alias dklf='docker logs -f'
alias dkps='docker ps'
alias dkpsa='docker ps -a'
alias dkrm='docker rm'
alias dkrmi='docker rmi'
# alias dks='docker service'

# dir
alias ...='cd ../..'
alias ....='cd ../../..'
alias .....='cd ../../../..'
alias ......='cd ../../../../..'
alias h='cd ~'
alias cddow='cd ~/Downloads'
alias cdde='cd ~/Desktop'
alias cddes='cd ~/Desktop'
alias cdhost='cd /mnt/host'

# git
alias g='git'
alias ga='git add'
alias gaa='git add --all'
alias gb='git branch'
alias gba='git branch -a'
alias gbd='git branch -d'
alias gbD='git branch -D'
alias gcb='git checkout -b'
alias gcf='git config --list'
alias gcl='git clone --recurse-submodules'
alias gco='git checkout'
alias gcor='git checkout --recurse-submodules'
alias gcmsg='git commit -m'
alias gd='git diff'
alias gdca='git diff --cached'
alias gf='git fetch'
alias gfa='git fetch --all --prune --jobs=10'
alias gl='git pull'
alias glg='git log --stat'
alias glog='git log --oneline --decorate --graph'
alias gm='git merge'
alias gma='git merge --abort'
alias gp='git push'
alias gpsup='git push --set-upstream origin $(git_current_branch)'
alias gpf!='git push --force'
alias gr='git remote'
alias gra='git remote add'
alias grh='git reset'
alias grhh='git reset --hard'
alias gsb='git status -sb'
alias gss='git status -s'
alias gst='git status'

# python
alias py='python'

# remove
alias rma='find . -name  "a.out" | xargs rm'
alias rmds='find . -name ".DS_Store" | xargs rm'


# vim
alias vimn='vim -u NONE -N'
vack() {
    case $1 in
        i|install) git clone -- "$2" "$HOME/.vim/pack/vack/start/$(basename "$2")" ;;
        r|remove)  rm -rf -- "$HOME/.vim/pack/vack/start/$(basename "$2")" ;;
        l|list)    ls -- "$HOME/.vim/pack/vack/start" ;;
    esac
}

# alias -='cd -'
# alias ...=../..
# alias ....=../../..
# alias .....=../../../..
# alias ......=../../../../..
# alias 1='cd -1'
# alias 2='cd -2'
# alias 3='cd -3'
# alias 4='cd -4'
# alias 5='cd -5'
# alias 6='cd -6'
# alias 7='cd -7'
# alias 8='cd -8'
# alias 9='cd -9'
# alias _='sudo '
# alias clang=clang-9
# alias diff='diff --color'
# alias egrep='grep -E --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}'
# alias fgrep='grep -F --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}'
# alias g=git
# alias ga='git add'
# alias gaa='git add --all'
# alias gam='git am'
# alias gama='git am --abort'
# alias gamc='git am --continue'
# alias gams='git am --skip'
# alias gamscp='git am --show-current-patch'
# alias gap='git apply'
# alias gapa='git add --patch'
# alias gapt='git apply --3way'
# alias gau='git add --update'
# alias gav='git add --verbose'
# alias gb='git branch'
# alias gbD='git branch -D'
# alias gba='git branch -a'
# alias gbd='git branch -d'
# alias gbda='git branch --no-color --merged | command grep -vE "^([+*]|\s*($(git_main_branch)|$(git_develop_branch))\s*$)" | command xargs git branch -d 2>/dev/null'
# alias gbl='git blame -b -w'
# alias gbnm='git branch --no-merged'
# alias gbr='git branch --remote'
# alias gbs='git bisect'
# alias gbsb='git bisect bad'
# alias gbsg='git bisect good'
# alias gbsr='git bisect reset'
# alias gbss='git bisect start'
# alias gc='git commit -v'
# alias 'gc!'='git commit -v --amend'
# alias gca='git commit -v -a'
# alias 'gca!'='git commit -v -a --amend'
# alias gcam='git commit -a -m'
# alias 'gcan!'='git commit -v -a --no-edit --amend'
# alias 'gcans!'='git commit -v -a -s --no-edit --amend'
# alias gcas='git commit -a -s'
# alias gcasm='git commit -a -s -m'
# alias gcb='git checkout -b'
# alias gcc=clang-9
# alias gcd='git checkout $(git_develop_branch)'
# alias gcf='git config --list'
# alias gcl='git clone --recurse-submodules'
# alias gclean='git clean -id'
# alias gcm='git checkout $(git_main_branch)'
# alias gcmsg='git commit -m'
# alias gcn='git commit -v --no-edit'
# alias 'gcn!'='git commit -v --no-edit --amend'
# alias gco='git checkout'
# alias gcor='git checkout --recurse-submodules'
# alias gcount='git shortlog -sn'
# alias gcp='git cherry-pick'
# alias gcpa='git cherry-pick --abort'
# alias gcpc='git cherry-pick --continue'
# alias gcs='git commit -S'
# alias gcsm='git commit -s -m'
# alias gcss='git commit -S -s'
# alias gcssm='git commit -S -s -m'
# alias gd='git diff'
# alias gdca='git diff --cached'
# alias gdct='git describe --tags $(git rev-list --tags --max-count=1)'
# alias gdcw='git diff --cached --word-diff'
# alias gds='git diff --staged'
# alias gdt='git diff-tree --no-commit-id --name-only -r'
# alias gdup='git diff @{upstream}'
# alias gdw='git diff --word-diff'
# alias gf='git fetch'
# alias gfa='git fetch --all --prune --jobs=10'
# alias gfg='git ls-files | grep'
# alias gfo='git fetch origin'
# alias gg='git gui citool'
# alias gga='git gui citool --amend'
# alias ggpull='git pull origin "$(git_current_branch)"'
# alias ggpur=ggu
# alias ggpush='git push origin "$(git_current_branch)"'
# alias ggsup='git branch --set-upstream-to=origin/$(git_current_branch)'
# alias ghh='git help'
# alias gignore='git update-index --assume-unchanged'
# alias gignored='git ls-files -v | grep "^[[:lower:]]"'
# alias git-svn-dcommit-push='git svn dcommit && git push github $(git_main_branch):svntrunk'
# alias gk='\gitk --all --branches &!'
# alias gke='\gitk --all $(git log -g --pretty=%h) &!'
# alias gl='git pull'
# alias glg='git log --stat'
# alias glgg='git log --graph'
# alias glgga='git log --graph --decorate --all'
# alias glgm='git log --graph --max-count=10'
# alias glgp='git log --stat -p'
# alias glo='git log --oneline --decorate'
# alias globurl='noglob urlglobber '
# alias glod='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%ad) %C(bold blue)<%an>%Creset'\'
# alias glods='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%ad) %C(bold blue)<%an>%Creset'\'' --date=short'
# alias glog='git log --oneline --decorate --graph'
# alias gloga='git log --oneline --decorate --graph --all'
# alias glol='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%ar) %C(bold blue)<%an>%Creset'\'
# alias glola='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%ar) %C(bold blue)<%an>%Creset'\'' --all'
# alias glols='git log --graph --pretty='\''%Cred%h%Creset -%C(auto)%d%Creset %s %Cgreen(%ar) %C(bold blue)<%an>%Creset'\'' --stat'
# alias glp=_git_log_prettily
# alias gluc='git pull upstream $(git_current_branch)'
# alias glum='git pull upstream $(git_main_branch)'
# alias gm='git merge'
# alias gma='git merge --abort'
# alias gmom='git merge origin/$(git_main_branch)'
# alias gmtl='git mergetool --no-prompt'
# alias gmtlvim='git mergetool --no-prompt --tool=vimdiff'
# alias gmum='git merge upstream/$(git_main_branch)'
# alias gp='git push'
# alias gpd='git push --dry-run'
# alias gpf='git push --force-with-lease'
# alias 'gpf!'='git push --force'
# alias gpoat='git push origin --all && git push origin --tags'
# alias gpr='git pull --rebase'
# alias gpristine='git reset --hard && git clean -dffx'
# alias gpsup='git push --set-upstream origin $(git_current_branch)'
# alias gpu='git push upstream'
# alias gpv='git push -v'
# alias gr='git remote'
# alias gra='git remote add'
# alias grb='git rebase'
# alias grba='git rebase --abort'
# alias grbc='git rebase --continue'
# alias grbd='git rebase $(git_develop_branch)'
# alias grbi='git rebase -i'
# alias grbm='git rebase $(git_main_branch)'
# alias grbo='git rebase --onto'
# alias grbom='git rebase origin/$(git_main_branch)'
# alias grbs='git rebase --skip'
# alias grep='grep --color=auto --exclude-dir={.bzr,CVS,.git,.hg,.svn,.idea,.tox}'
# alias grev='git revert'
# alias grh='git reset'
# alias grhh='git reset --hard'
# alias grm='git rm'
# alias grmc='git rm --cached'
# alias grmv='git remote rename'
# alias groh='git reset origin/$(git_current_branch) --hard'
# alias grrm='git remote remove'
# alias grs='git restore'
# alias grset='git remote set-url'
# alias grss='git restore --source'
# alias grst='git restore --staged'
# alias grt='cd "$(git rev-parse --show-toplevel || echo .)"'
# alias gru='git reset --'
# alias grup='git remote update'
# alias grv='git remote -v'
# alias gsb='git status -sb'
# alias gsd='git svn dcommit'
# alias gsh='git show'
# alias gsi='git submodule init'
# alias gsps='git show --pretty=short --show-signature'
# alias gsr='git svn rebase'
# alias gss='git status -s'
# alias gst='git status'
# alias gsta='git stash push'
# alias gstaa='git stash apply'
# alias gstall='git stash --all'
# alias gstc='git stash clear'
# alias gstd='git stash drop'
# alias gstl='git stash list'
# alias gstp='git stash pop'
# alias gsts='git stash show --text'
# alias gstu='gsta --include-untracked'
# alias gsu='git submodule update'
# alias gsw='git switch'
# alias gswc='git switch -c'
# alias gswd='git switch $(git_develop_branch)'
# alias gswm='git switch $(git_main_branch)'
# alias gtl='gtl(){ git tag --sort=-v:refname -n -l "${1}*" }; noglob gtl'
# alias gts='git tag -s'
# alias gtv='git tag | sort -V'
# alias gunignore='git update-index --no-assume-unchanged'
# alias gunwip='git log -n 1 | grep -q -c "\--wip--" && git reset HEAD~1'
# alias gup='git pull --rebase'
# alias gupa='git pull --rebase --autostash'
# alias gupav='git pull --rebase --autostash -v'
# alias gupom='git pull --rebase origin $(git_main_branch)'
# alias gupomi='git pull --rebase=interactive origin $(git_main_branch)'
# alias gupv='git pull --rebase -v'
# alias gwch='git whatchanged -p --abbrev-commit --pretty=medium'
# alias gwip='git add -A; git rm $(git ls-files --deleted) 2> /dev/null; git commit --no-verify --no-gpg-sign -m "--wip-- [skip ci]"'
# alias gwt='git worktree'
# alias gwta='git worktree add'
# alias gwtls='git worktree list'
# alias gwtmv='git worktree move'
# alias gwtrm='git worktree remove'
# alias history=omz_history
# alias l='ls -lah'
# alias la='ls -lAh'
# alias ll='ls -lh'
# alias ls='ls --color=tty'
# alias lsa='ls -lah'
# alias md='mkdir -p'
# alias norminette='~/.norminette/norminette.rb'
# alias rd=rmdir
# alias which-command=whence
