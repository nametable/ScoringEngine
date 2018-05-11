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

QtBuild
```
git clone https://code.qt.io/qt/qt5.git qt5
cd qt5
git checkout v5.10.0
perl init-repository --module-subset=qtbase
./configure -prefix ../qt5-static/ -release -opensource -confirm-license -static -no-sql-mysql -no-sql-psql -no-sql-sqlite -no-icu -no-journald -qt-zlib -no-mtdev -no-gif -qt-libpng -qt-libjpeg -qt-freetype -qt-harfbuzz -no-openssl -qt-pcre -qt-xcb -no-glib -no-egl -qt-xkbcommon -qt-xkbcommon-x11 -xkb-config-root /usr/share/X11/xkb -no-compile-examples -no-cups -no-iconv -no-tslib -qt-xcb -no-xcb-xlib -no-eglfs -no-directfb -no-linuxfb -no-kms -no-opengl -nomake examples -nomake tests -skip qtwebsockets -skip qtwebchannel -skip qtwebengine -skip qtwayland -skip qtwinextras -skip qtsvg -skip qtsensors -skip qtcanvas3d -skip qtconnectivity -skip declarative -skip quick1 -no-libproxy -no-opengl -no-openvg -no-libjpeg
```

## Screenshots
![Configuration Screenshot](configscreenshot.png?raw=true "Config Screenshot")
![Report Screenshot](scorereportscreenshot.png?raw=true "Report Screenshot")
