let mapleader=","
map <silent> <leader>ss :source ~/.vimrc<cr>
map <silent> <leader>ee :e ~/.vimrc<cr>

"coding setting
set shiftwidth=2
set tabstop=2
set smarttab
set expandtab
set nu
set cindent
set fenc=utf-8
set enc=utf-8
set fileformats=unix
set colorcolumn=120

"ui setting
set statusline=[%l/%L,%c,%{&ff},%{&fenc}][%{getcwd()}][%f]
set laststatus=2
set splitright
set splitbelow
set hlsearch
set smartcase

set textwidth=64
"set list
set listchars=eol:↓,tab:→→,trail:·
set guifont=source_code_pro:h11
set guioptions-=T
set guitablabel=%N:%F
set nocompatible
set cursorline
set langmenu=en
set directory=$VIMRUNTIME\..\swap\\
set backupdir=$VIMRUNTIME\..\backup\\

let $lang='en'
colorscheme desert

source $VIMRUNTIME/vimrc_example.vim
source $VIMRUNTIME/mswin.vim
behave mswin

highlight ColorColumn ctermbg=grey
highlight Search cterm=NONE ctermfg=grey ctermbg=blue
highlight CursorLine cterm=none ctermfg=white gui=none guifg=white
let Tlist_Ctags_Cmd='D:\ctags\ctags.exe'

"nmap <C-CR> _i<CR><Esc>
nnoremap <Space> <C-F>
nnoremap <S-Space> <C-B>
nnoremap <CR> <C-D>
nnoremap <Down> <C-E>
nnoremap <Up> <C-Y>
nnoremap <Space> <C-U>
nmap <F2> :set list!<CR>
nmap <F3> :call ToggleLineNumber()<CR>
function ToggleLineNumber()
  if &nu == 0 && &rnu == 0
    set nu
  elseif &nu == 1  && &rnu == 0
    set nonu rnu
  elseif &nu == 0 && &rnu == 1
    set nu rnu
  else
    set nonu nornu
  endif
endfunction

nmap <F4> :!ctags -L project.files --c++-kinds=+p --fields=+iaS --extra=+q <CR><CR>
nmap <F12> :TlistToggle<CR>

let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1

let g:LookupFile_MinPatLength=2
let g:LookupFile_TagExpr=string('./ltags')
let g:LookupFile_PreserveLastPattern=0
let g:LookupFile_PreservePatternHistory=0
nmap <silient> <leader>ll :LUTags<cr>
nmap <silient> <leader>lk :LUBufs<cr>
nmap <silient> <leader>lj :LUWalk<cr>


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


