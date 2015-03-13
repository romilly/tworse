#!/usr/bin/env bash
cd distribution
rm * -rf
cp ../python . -r
cp ../sketches . -r
cp ../manuscript/tworse.pdf .
zip -R tworse '*'