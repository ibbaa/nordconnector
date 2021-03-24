#!/bin/sh
if [ -n "$LD_LIBRARY_PATH" ]; then
  LD_LIBRARY_PATH=$LD_LIBRARY_PATH:../lib
else
  LD_LIBRARY_PATH=../lib
fi
export LD_LIBRARY_PATH
exec nordc "$@"