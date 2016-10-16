#!/bin/bash

# Windows deployment
rm -rv windows
mkdir windows

WINEPREFIX="/home/ruman/PlayOnLinux's virtual drives/WindowsDevelopment/" wine windeployqt --dir windows ../build-SilVerPLuM-Desktop_Qt_5_7_0_MinGW_32bit-Release/release/SilVerPLuM.exe
cp -r lib-windows/* windows
cp -r shared/* windows
cp ../build-SilVerPLuM-Desktop_Qt_5_7_0_MinGW_32bit-Release/release/SilVerPLuM.exe windows
cp ../LICENSE windows
cp ../README.md windows

# Linux deployment

rm -rv linux
mkdir linux

cp -r shared/* linux
cp -r lib-linux/* linux
rm linux/README.md
cp ../build-quazip-Desktop-Release/quazip/* linux/lib
cp ../build-SilVerPLuM-Desktop-Release/SilVerPLuM linux
cp ../LICENSE linux
cp ../README.md linux
cp ../src/resources/icons/application-128.png linux/icon.png

# Package

rm SilVerPLuM_windows.zip 
rm SilVerPLuM_linux.zip

cd windows
zip -r ../SilVerPLuM_windows.zip .
cd ..
cd  linux
zip -r ../SilVerPLuM_linux.zip .
cd ..

