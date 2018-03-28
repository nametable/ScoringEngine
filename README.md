Scoring Engine for CyberPatriot practice and similar.

author: nametable
license:GPLv3

Dependencies: QtCore, QtGUI, QtMultimedia, BoostFilesystem, BoostSerialization

How to build.

cmake .
make
sudo make install

notes:

QtBuild

git clone https://code.qt.io/qt/qt5.git qt5
cd qt5
git checkout v5.10.0
perl init-repository --module-subset=essential,-qtmultimedia -f
./configure -developer-build -confirm-license -opensource -static -qt-zlib -qt-libpng -qt-libjpeg -opengl desktop
