# CMake configuration

mkdir -p build
cd build

ARGS="-DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_INSTALL_SYSCONFDIR=/etc -DINSTALL=ON"

cmake .. $ARGS
