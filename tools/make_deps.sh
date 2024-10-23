#!/bin/bash

echo " -> updating dependencies for scal"
echo ""

echo " -> gyp... "
echo ""

if [[ -d build/gyp ]]; then
  echo ""
else
  mkdir -p build/gyp
  git clone https://chromium.googlesource.com/external/gyp build/gyp
  cd build/gyp && git checkout caa60026e223fc501e8b337fd5086ece4028b1c6 && cd ../../
fi

if [ $? -eq 0 ]; then
  echo ""
  echo " -> gyp... done"
else
  exit $?
fi
