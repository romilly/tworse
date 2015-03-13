#!/usr/bin/env bash
cd distribution
rm * -rf
cp ../python . -r
cp ../sketches . -r
zip -R tworse '*'
cp tworse.zip ../zip/