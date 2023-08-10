#!/bin/bash


rm -rf build
mkdir -p build
mkdir -p lib
cd build
cmake ..
make all VERBOSE=1

cp ../include/VisionPlugin.h ../test/
cp ../include/VisionPluginTypes.h ../test/
cp libacvisionplugin.so ../test/
cp libacvisionplugin.so ../lib/
cd ../test
make all VERBOSE=1
