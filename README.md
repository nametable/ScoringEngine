# ScoringEngine
A system for practicing security skills on Linux distros

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
./configure -release -confirm-license -opensource -static -qt-zlib -qt-libpng -qt-libjpeg
```

## Screenshots
![Configuration Screenshot](configscreenshot.png?raw=true "Config Screenshot")
![Report Screenshot](scorereportscreenshot.png?raw=true "Report Screenshot")
