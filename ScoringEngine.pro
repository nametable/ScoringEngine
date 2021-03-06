#-------------------------------------------------
#
# Project created by Logan
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ScoringEngine
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    basescorechecker.cpp \
    pathexistscorechecker.cpp \
    runcommandscorechecker.cpp \
    scorecheckingconfig.cpp \
    emptyscorechecker.cpp \
    valuescorechecker.cpp \
    scriptscorechecker.cpp \
    configpropertieswindow.cpp \
    scripteditdialog.cpp \
    backgroundservice.cpp \
    templatescorechecker.cpp \
    templateeditwindow.cpp \
    scorecheckerviewmodel.cpp \
    scorecheckerviewdelegate.cpp \
    startdialog.cpp \
    questionanswerscorechecker.cpp \
    playerdashboard.cpp

HEADERS += \
        mainwindow.h \
    basescorechecker.h \
    pathexistscorechecker.h \
    runcommandscorechecker.h \
    scorecheckingconfig.h \
    emptyscorechecker.h \
    valuescorechecker.h \
    scriptscorechecker.h \
    configpropertieswindow.h \
    scripteditdialog.h \
    backgroundservice.h \
    templatescorechecker.h \
    templateeditwindow.h \
    version.h \
    scorecheckerviewmodel.h \
    scorecheckerviewdelegate.h \
    startdialog.h \
    questionanswerscorechecker.h \
    playerdashboard.h \
    constants.h

FORMS += \
        mainwindow.ui \
    configpropertieswindow.ui \
    scripteditdialog.ui \
    templateeditwindow.ui \
    startdialog.ui \
    playerdashboard.ui

release {
INCLUDEPATH += ../boost_1_67_0/

LIBS += -L../boost_1_67_0/boost-lin-64/lib -l:libboost_filesystem.a -l:libboost_system.a -l:libboost_serialization.a -l:libboost_regex.a
}
debug {
    LIBS += -lboost_filesystem -lboost_system -lboost_serialization -lboost_regex
}

DISTFILES +=

RESOURCES += \
    resources.qrc
