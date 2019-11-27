" author wwssh

"""""""""""""""""
" global settings
"""""""""""""""""
syntax enable
set history=10000
set guifont=consolas:h10
set backspace=indent,eol,start

"""""""""""""""""
" coding settings
"""""""""""""""""
set smarttab
set shiftwidth=2
set tabstop=2
set expandtab
set nolist
set nonu
set cindent
set fenc=utf-8
set enc=utf-8
set fileformats=unix
set colorcolumn=120
autocmd Filetype c setlocal tabstop=8 shiftwidth=2 expandtab
autocmd Filetype cpp setlocal tabstop=8 shiftwidth=2 expandtab
autocmd Filetype python setlocal tabstop=4 shiftwidth=4 expandtab


"""""""""""""""""
" ui settings
"""""""""""""""""
" always having status line or not
set laststatus=2
set splitright
set splitbelow
set hlsearch
set smartcase
set nowrap
set cscopequickfix=s-,c-,d-,i-,t-,e-
" %l=cursor-line-num, %L=total-line-num,%c=column, fenc=file-encoding,%f=filename
set statusline=[%l/%L,%c,%{&ff},%{&fenc}][%{getcwd()}][%f]
" colorscheme default

" colores of cterm is fixed with 16 numbers
" highlights, try :highlight to got colors
" highlights, define a pattern to hightlight, match should behind highlight
highlight codeline term=underline ctermbg=4
match codeline /\%80v/
highlight Comment ctermfg=cyan
highlight Search cterm=NONE ctermfg=grey ctermbg=blue
highlight ColorColumn ctermbg=black guibg=black
highlight Identifier ctermfg=blue guibg=black
highlight Special ctermfg=blue guibg=black
highlight PreProc ctermfg=blue guibg=black
highlight Constant ctermfg=blue guibg=black
"highlight CursorLine cterm=none


"""""""""""""""""
" autocmd
"""""""""""""""""
" InsertEnter = starting Insert mode, event, * = all files, pattern, set cursorline, cmd
" there will be a line under the cursorline if cursorline setted
autocmd InsertEnter * set cursorline
autocmd InsertLeave * set cursorline!
"bufwritepost = after writing the whole buffer to a file
autocmd bufwritepost .vimrc source ~/.vimrc
"autocmd BufReadPost * if line("'\"")>0&&line("'\"")<=line("$") | exe "normal g'\""
"autocmd BufWritePost * call system("ctags -R *.cc *.h")


"""""""""""""""""
" key-map settings
"""""""""""""""""
let mapleader = ","
map <silent> <leader>ss :source ~/.vimrc<cr>
map <silent> <leader>ee :e ~/.vimrc<cr>
" remap = recursive map, noremap = no-remap, nnoremap = normal-no-remap
" disable up down left and right
nnoremap <up> <nop>
nnoremap <down> <nop>
nnoremap <left> <nop>
nnoremap <right> <nop>

" quickly insert an empty line without entering insert mode
nnoremap <C-o> o<ESC>
nnoremap <C-O> O<ESC>
" quickly move backward-word/forward-word like less
nnoremap <C-b> <S-left>
nnoremap <C-f> <S-right>
" quickly move to beginning-of-line/end-of-line line readline
nnoremap <C-a> <home>
nnoremap <C-e> <end>

" window commands:" move the cursor to the window left/right/above/below the current one
nnoremap <C-J> <C-W><C-J>
nnoremap <C-K> <C-W><C-K>
nnoremap <C-H> <C-W><C-H>
nnoremap <C-L> <C-W><C-L>

" insert mode key-map: C-N = find the next match word
" <C-N>: find the next match words that start with the keyword in front of the cursor
inoremap <C-J> <C-N>
" <C-P>: find the previous match words that start with the keyword in front of the cursor
inoremap <C-K> <C-P>

" command mode key-map, S-left = shift + left
"cnoremap <C-h> <left>
"cnoremap <C-l> <right>
"" quickly move backward-word/forward-word like less
cnoremap <C-b> <S-left>
cnoremap <C-f> <S-right>
"" quickly move to beginning-of-line/end-of-line line readline
cnoremap <C-a> <home>
cnoremap <C-e> <end>

" buffer list
" go to the necwxt buffer in t he buffer list
nnoremap bp :bprevious<CR>
" go to the next buffer in t he buffer list
nnoremap bn :bnext<CR>
" go to the first buffer in t he buffer list
nnoremap bf :bfirst<CR>
" go to the last buffer in t he buffer list
nnoremap bl :blast<CR>

" location list
" M will affect Esc from insert mode
nnoremap  <C-p> :lprevious<CR>
nnoremap  <C-n> :lnext<CR>
" ll will slow command l
nnoremap  <C-a> :lfirst<CR>
nnoremap  <C-e> :llast<CR>

" quickfix list
nnoremap <silent> qp :cprevious<CR>
nnoremap <silent> qn :cnext<CR>
nnoremap <silent> qf :cfirst<CR>
nnoremap <silent> ql :clast<CR>

"""""""""""""""""
" Function key short-cut mapping
"""""""""""""""""
" display unprintable characters or not
nmap <F2> :set list!<CR>

nmap <F3> :set nu!<CR>
function! NUSwitch()
  if &nu == 0 && &rnu == 0
    set nu
  elseif &nu == 1 && &rnu == 0
    set nonu rnu
  elseif &nu == 0 && &rnu == 1
    set nu rnu
  else
    set nonu nornu
  endif
endfunction

" expand('<cword>') is the word under the cursor
nmap <F4> :let @/=expand('<cword>') \| set hlsearch!<CR>
"nmap <F4> :call HLCursorWord()<CR>
"function! HLCursorWord()
"  let @/=expand('<cword>')
"  set hlsearch!
"endfunction

" F5-F8 vim-window layouts
" F5 used in plugin lookupfile

" F9-12 tags related
" generate project filename list
nmap <F9> :!find . -name "*.h" -o -name "*.cc" -o "*.c" -type f > ctags.project.filenamelist<CR><CR>
" generate tas files for source code
nmap <F10> :!ctags -L ctags.project.filenamelist --c++-kinds=+p --fields=+iaS --extra=+q --language-force=c++<CR><CR>
" cscope
nmap <F11> :!cscope -bq<CR><CR>
nmap <F12> :TlistToggle<CR>

"""""""""""""""""
" Taglist plugin
"""""""""""""""""
" show tags of the current opened file
let Tlist_Show_One_File=1
"" vim will exit if the taglist is the only window
let Tlist_Exit_OnlyWindow=1

"""""""""""""""""""
" lookupfile plugin
"""""""""""""""""""
let g:LookupFile_MinPatLength = 1
let g:LookupFile_TagExpr = string('./ltags')
let g:LookupFile_PreserveLastPattern = 0
let g:LookupFile_PreservePatternHistory = 0
nmap <silent> <leader>ll :LUTags<cr>
nmap <silent> <leader>lk :LUBufs<cr>
nmap <silent> <leader>lj :LUWalk<cr>

""""""""""""""""
"cscope settings
""""""""""""""""
if has("cscope")
  set csprg=/usr/local/bin/cscope
  set csto=0
  set cst
  set nocsverb
  if filereadable("cscope.out")
    cs add cscope.out
  endif
  set csverb
endif
nmap <c-@>s :cs find s <c-r>=expand("<cword>")<cr><cr>:cw<CR>
nmap <c-@>g :cs find g <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>c :cs find c <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>t :cs find t <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>e :cs find e <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>f :cs find f <c-r>=expand("<cfile>")<cr><cr>
nmap <c-@>i :cs find i ^<c-R>=expand("<cfile>")<cr>$<cr>
nmap <c-@>d :cs find d <c-r>=expand("<cword>")<cr><cr>
