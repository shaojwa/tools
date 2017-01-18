set guifont=source_code_pro:h11
set guioptions-=T
set guitablabel=%N:%F
set encoding=utf-8
set lines=24
set columns=80
set textwidth=64
set shiftwidth=4
set tabstop=4
set expandtab
set nocompatible
set cursorline
set langmenu=en
let $lang='en'
set listchars=eol:↓,tab:→→,trail:·
set statusline=%<%F
set list
set nu
set directory=$VIMRUNTIME\..\swap\\
set backupdir=$VIMRUNTIME\..\backup\\

colorscheme desert

source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
behave mswin

set cc=80
highlight ColorColumn guibg=#202020

let Tlist_Ctags_Cmd='D:\ctags\ctags.exe'

"nmap <C-CR> _i<CR><Esc>
"nnoremap <C-Space> i<Space><Esc>

map <M-1> 1gt
map <M-2> 2gt
map <M-3> 3gt
map <M-4> 4gt
map <M-5> 5gt
map <M-6> 6gt
map <M-7> 7gt
map <M-8> 8gt
map <M-9> 9gt 
map <M-F1> :tabclose<CR>
map <M-F2> :tabedit<CR>

set diffexpr=MyDiff()
function MyDiff()
  let opt = '-a --binary '
  if &diffopt =~ 'icase' | let opt = opt . '-i ' | endif
  if &diffopt =~ 'iwhite' | let opt = opt . '-b ' | endif
  let arg1 = v:fname_in
  if arg1 =~ ' ' | let arg1 = '"' . arg1 . '"' | endif
  let arg2 = v:fname_new
  if arg2 =~ ' ' | let arg2 = '"' . arg2 . '"' | endif
  let arg3 = v:fname_out
  if arg3 =~ ' ' | let arg3 = '"' . arg3 . '"' | endif
  let eq = ''
  if $VIMRUNTIME =~ ' '
    if &sh =~ '\<cmd'
      let cmd = '""' . $VIMRUNTIME . '\diff"'
      let eq = '"'
    else
      let cmd = substitute($VIMRUNTIME, ' ', '" ', '') . '\diff"'
    endif
  else
    let cmd = $VIMRUNTIME . '\diff'
  endif
  silent execute '!' . cmd . ' ' . opt . arg1 . ' ' . arg2 . ' > ' . arg3 . eq
endfunction


