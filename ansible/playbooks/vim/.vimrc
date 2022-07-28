set nocompatible
filetype off

filetype plugin indent on

au BufNewFile,BufRead *.py
  \ set tabstop=4
  \ softtabstop=4
  \ shiftwidth=4
  \ textwidth=79
  \ expandtab
  \ autoindent
  \ fileformat=unix

au BufNewFile,BufRead *.c,*.cpp,*.css,*.go,*.groovy,*.h,*.hpp,*.html,*.js,*.json,*.lua,*.pl,*.pm,*.rs,*.sh,*.t,*.txt,*.xml,*.yaml,*.yml
  \ set tabstop=2
  \ softtabstop=2
  \ shiftwidth=2
  \ expandtab
  \ autoindent
  \ fileformat=unix


au FileType make set noexpandtab shiftwidth=8 softtabstop=0

syntax enable

set backspace=indent,eol,start

set incsearch
set hlsearch

set showcmd
set cursorline
set showmatch

let python_highlight_all=1
autocmd filetype crontab setlocal nobackup nowritebackup
