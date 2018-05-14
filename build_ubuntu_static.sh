#!/bin/bash
echo "Installing Build dependencies"
#Dependencies for Ubuntu
sudo apt -y install g++
sudo apt-get -y build-dep qt5-default
sudo apt-get -y install libxcb-xinerama0-dev libfontconfig1-dev libfreetype6-dev
sudo apt-get -y install '^libxcb.*-dev' libx11-xcb-dev libglu1-mesa-dev libxrender-dev libxi-dev
#For other systems dependencies are listed at https://wiki.qt.io/Building_Qt_5_from_Git
echo "Building dependencies..."
echo "Building Boost"
cd ..
wget -c https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.bz2
tar -xjf boost_1_67_0.tar.bz2
cd boost_1_67_0
./bootstrap.sh
./b2 --stagedir=boost-lin-64 --with-serialization --with-filesystem --with-system --with-regex release
cd ..
echo "Building qt"
git clone https://code.qt.io/qt/qt5.git qt5
cd qt5
git checkout v5.10.0
perl init-repository --module-subset=qtbase
./configure -prefix ../qt5-static/ -release -opensource -confirm-license -static -no-sql-mysql -no-sql-psql -no-sql-sqlite -no-icu -no-journald -qt-zlib -no-mtdev -no-gif -qt-libpng -qt-libjpeg -system-freetype -qt-harfbuzz -no-openssl -qt-pcre -qt-xcb -no-glib -no-egl -qt-xkbcommon -qt-xkbcommon-x11 -xkb-config-root /usr/share/X11/xkb -no-compile-examples -no-cups -no-iconv -no-tslib -qt-xcb -no-xcb-xlib -no-eglfs -no-directfb -no-linuxfb -no-kms -no-opengl -nomake examples -nomake tests -skip qtwebsockets -skip qtwebchannel -skip qtwebengine -skip qtwayland -skip qtwinextras -skip qtsvg -skip qtsensors -skip qtcanvas3d -skip qtconnectivity -skip declarative -skip quick1 -no-libproxy -no-opengl -no-openvg -no-libjpeg -fontconfig
make
cd ../ScoringEngine
echo "Building ScoringEngine"
sed -i '/INCLUDEPATH/c INCLUDEPATH += ../boost_1_67_0/' ScoringEngine.pro
sed -i '/LIBS += -L/c LIBS += -L../boost_1_67_0/boost-lin-64/lib -l:libboost_filesystem.a -l:libboost_system.a -l:libboost_serialization.a -l:libboost_regex.a' ScoringEngine.pro
sed -i '/!debug {/c release {' ScoringEngine.pro
../qt5-static/bin/qmake
make release
