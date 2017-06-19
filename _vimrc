let mapleader=","
map <silent> <leader>ss :source ~/.vimrc<cr>
map <silent> <leader>ee :e ~/.vimrc<cr>

" coding settings
syntax enable
set shiftwidth=2
set tabstop=2
set smarttab
set expandtab
set nu
set cindent
set fenc=utf-8
set enc=utf-8
set ff=unix
set colorcolumn=120
"highlight codeline ctermbg=yellow
"match codeline /\%>80v/

" ui settings
colorscheme wsh
set statusline=[%l/%L,%c,%{&ff},%{&fenc}][%{getcwd()}][%f]
set laststatus=2
set splitright
set splitbelow
set hlsearch
set smartcase
set nowrap
set nowrap
set csqf=s-,c-,d-,i-,t-,e-
hi search ctermfg=gray ctermbg=blue cterm=none
hi colorcolumn ctermbg=black guibg=black
hi cursorline ctermfg=white cterm=none

autocmd insertenter,insertleave * set cul!

nnoremap <up> <nop>
nnoremap <down> <nop>
nnoremap <left> <nop>
nnoremap <right> <nop>
nnoremap <c-j> <c-w><c-j>
nnoremap <c-k> <c-w><c-k>
nnoremap <c-h> <c-w><c-h>
nnoremap <c-l> <c-w><c-l>

" buffer list
nnoremap <silent> ]b :bprevious<cr>
nnoremap <silent> [b :bnext<cr>
nnoremap <silent> ]B :bfirst<cr>
nnoremap <silent> [B :blast<cr>

" location list
nnoremap <silent> ]l :lprevious<cr>
nnoremap <silent> [l :lnext<cr>
nnoremap <silent> ]L :lfirst<cr>
nnoremap <silent> [L :llast<cr>


" quickfix list
nnoremap <silent> ]c :cprevious<cr>
nnoremap <silent> [c :cnext<cr>
nnoremap <silent> ]C :cfirst<cr>
nnoremap <silent> [C :clast<cr>

  nmap <F2> :set list!<cr>
function! LineNumberToggle()
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

nmap <F3> :call LineNumberToggle() <cr>
nmap <F4> :set hlsearch!<cr>
nmap <F8> :TlistToggle<cr>
nmap <F9> :!find . -name "*.h" -o -name "*.cc" -type f > project.files<cr><cr>
nmap <F10> :!ctags -L project.files --c++-kinds=+p --fields=+iaS --extra=+q --language-force=c++<cr><cr>
nmap <F11> :!cscope -bq<cr><cr>

" tag list
let Tlist_Show_One_File=1
let Tlist_Exit_OnlyWindow=1

" lookupfile
let g:LookupFile_MiNPatLength=1
let g:LookupFile_TagExpr=string("./ltags")
let g:LookupFile_PreserveLastPattern=0 
let g:LookupFile_PreservePatternHistory=0
nmap <silient> <leader>ll :LUTags<cr>
nmap <silient> <leader>lk :LUBufs<cr>
nmap <silient> <leader>lj :LUWalk<cr>

"cscope
if has("cscope")
  set csprg=/usr/local/bin/cscope
  set csto=1
  set cst
  set nocsverb
  if filereadable("cscope.out")
    cs add cscope.out
  endif
set csverb
endif

nmap <c-@>s :cs find s <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>g :cs find g <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>c :cs find c <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>t :cs find t <c-r>=expand("<cword>")<cr><cr>
nmap <c-@>e :cs find e <c-r>=expand("<cfile>")<cr><cr>
nmap <c-@>f :cs find f <c-r>=expand("<cfile>")<cr><cr>
nmap <c-@>i :cs find i ^<c-r>=expand("<cword>")<cr>$<cr>
nmap <c-@>d :cs find d <c-r>=expand("<cword>")<cr><cr>
