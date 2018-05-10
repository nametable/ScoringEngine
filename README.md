# ScoringEngine
A system for practicing security skills on Linux distros. This can be useful for the CyberPatriot Competition, other security competitions, or personal use/practice.

**Author: Logan Bateman**

**License: GPLv3**

Dependencies: QtCore, QtGUI, BoostFilesystem, BoostSerialization, BoostRegex

How to build - Needs work. Eventually a configure script would be nice ([TODO List](docs/TODO.md))

```
qmake
make
```

Notes:

Building Static Boost
```
wget -c https://dl.bintray.com/boostorg/release/1.67.0/source/boost_1_67_0.tar.bz2
tar -xjf boost_1_67_0.tar.bz2
cd boost_1_67_0
./bootstrap.sh
./b2 --stagedir=boost-lin-64 --with-serialization --with-filesystem --with-system --with-regex release
cd ..
```

QtBuild
```
git clone https://code.qt.io/qt/qt5.git qt5
cd qt5
git checkout v5.10.0
perl init-repository --module-subset=qtbase
./configure -release -confirm-license -opensource -static -qt-zlib -qt-libpng -qt-libjpeg -no-opengl
make
```

## Screenshots
![Configuration Screenshot](configscreenshot.png?raw=true "Config Screenshot")
![Report Screenshot](scorereportscreenshot.png?raw=true "Report Screenshot")
