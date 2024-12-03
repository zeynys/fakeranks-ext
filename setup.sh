#!/bin/bash

export MMSOURCE20="$(pwd)/alliedmodders/metamod"
export HL2SDKCS2="$(pwd)/alliedmodders/hl2sdk"

if [ ! -d build ]; then
    mkdir build
    cd build
    CC=gcc CXX=g++ python ../configure.py --enable-optimize -s cs2
    cd ..
fi

cd build
ambuild
cd ..