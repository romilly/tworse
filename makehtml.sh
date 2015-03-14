#!/bin/bash
# symlink from ~/bin/makepdf
pandoc -f markdown -o $1.html $1.md -V fontfamily=droid
