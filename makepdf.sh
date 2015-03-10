#!/bin/bash
# symlink from ~/bin/makepdf
pandoc -f markdown -o $1.pdf $1.md -V fontfamily=droid
