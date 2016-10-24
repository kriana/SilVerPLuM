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
mkdir linux/lib
mkdir linux/plugins

cp -r shared/* linux
cp lib-linux/SilVerPLuM.sh linux
cp lib-linux/lib/libQt5Widgets* linux/lib
cp lib-linux/lib/libQt5Gui* linux/lib
cp lib-linux/lib/libQt5Network* linux/lib
cp lib-linux/lib/libQt5Concurrent* linux/lib
cp lib-linux/lib/libQt5Xml* linux/lib
cp lib-linux/lib/libQt5Core* linux/lib
cp lib-linux/lib/libicui18n* linux/lib
cp lib-linux/lib/libicuuc* linux/lib
cp lib-linux/lib/libicudata* linux/lib
cp lib-linux/lib/libQt5XcbQpa* linux/lib
cp lib-linux/lib/libQt5DBus* linux/lib
cp -r lib-linux/plugins/platforms linux/plugins
cp ../build-quazip-Desktop-Release/quazip/* linux/lib
cp ../build-quazip-Desktop-Release/quazip/libquazip.so linux/lib/libquazip5.so
cp ../build-quazip-Desktop-Release/quazip/libquazip.so.1 linux/lib/libquazip5.so.1
cp ../build-quazip-Desktop-Release/quazip/libquazip.so.1.0 linux/lib/libquazip5.so.1.0
cp ../build-quazip-Desktop-Release/quazip/libquazip.so.1.0.0 linux/lib/libquazip5.so.1.0.0
cp ../build-SilVerPLuM-Desktop-Release/SilVerPLuM linux
cp ../LICENSE linux
cp ../README.md linux
cp ../src/resources/icons/application-128.png linux/icon.png

# Default mods
mkdir linux/defaultmods
mkdir windows/defaultmods
cp ../repository/repositorylist.zip linux/defaultmods
cp ../repository/repositorylist.zip windows/defaultmods

# Package

rm SilVerPLuM_windows.zip 
rm SilVerPLuM_linux.zip

cd windows
zip -r ../SilVerPLuM_windows.zip .
cd ..
cd  linux
zip -r ../SilVerPLuM_linux.zip .
cd ..

