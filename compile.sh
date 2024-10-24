sudo apt-get install -y --fix-missing google-perftools libgoogle-perftools-dev cmake libgtest-dev libgflags-dev python-is-python3
./tools/make_deps.sh
./build/gyp/gyp --depth=. scal.gyp
