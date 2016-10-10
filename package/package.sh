#!/bin/bash

# Windows deployment
rm -rv windows
mkdir windows

WINEPREFIX="/home/ruman/PlayOnLinux's virtual drives/WindowsDevelopment/" wine windeployqt --dir windows ../build-SilVerPLuM-Desktop_Qt_5_7_0_MinGW_32bit-Release/release/SilVerPLuM.exe
cp lib-windows/* windows
cp ../build-SilVerPLuM-Desktop_Qt_5_7_0_MinGW_32bit-Release/release/SilVerPLuM.exe windows
cp ../LICENSE windows
cp ../README.md windows

# Linux deployment

rm -rv linux
mkdir linux

cp ../build-SilVerPLuM-Desktop-Release/SilVerPLuM linux
cp ../LICENSE linux
cp ../README.md linux

# Package

rm SilVerPLuM_windows.zip 
rm SilVerPLuM_linux.zip

cd windows
zip -r ../SilVerPLuM_windows.zip .
cd ..
cd  linux
zip -r ../SilVerPLuM_linux.zip .
cd ..

