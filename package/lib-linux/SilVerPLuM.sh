#!/bin/bash

# This launcher is not needed if you have installed
# qt >= 5.7
# quazip5

# http://stackoverflow.com/questions/4774054/reliable-way-for-a-bash-script-to-get-the-full-path-to-itself
pushd `dirname $0` > /dev/null
SCRIPTPATH=`pwd -P`
popd > /dev/null

export LD_LIBRARY_PATH="${SCRIPTPATH}/lib"
export QT_QPA_PLATFORM_PLUGIN_PATH="${SCRIPTPATH}/plugins/platforms"

./SilVerPLuM "$@"
