" Vim color file
" Maintainer:	Bram Moolenaar <Bram@vim.org>
" Last Change:	2001 Jul 23

" This is the default color scheme.  It doesn't define the Normal
" highlighting, it uses whatever the colors used to be.

" Set 'background' back to the default.  The value can't always be estimated
" and is then guessed.
hi clear Normal
set bg&


" Remove all existing highlighting and set the defaults.
hi clear

" Load the syntax highlighting defaults, if it's enabled.
if exists("syntax_on")
  syntax reset
endif

let colors_name = "wshl"

" vim: sw=2

" added by wsh
hi Normal ctermfg=black ctermbg=white cterm=none
hi Statement ctermfg=blue
hi LineNr ctermfg=black
hi Operator ctermfg=magenta cterm=none
hi Comment ctermfg=black cterm=bold
hi wsFunc ctermfg=blue
hi wsMemb ctermfg=blue cterm=none
hi wsClass ctermfg=green cterm=none
