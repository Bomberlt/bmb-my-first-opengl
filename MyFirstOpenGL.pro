#-------------------------------------------------
#
# Project created by QtCreator 2011-09-03T21:20:48
#
#-------------------------------------------------

QT       += core gui

TARGET = MyFirstOpenGL
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

LIBS += -lopengl32 -lglu32# -glut32

INCLUDEPATH = C:/glut-3.5/include
LIBS += C:/glut-3.7.6-bin/glut32.lib

OTHER_FILES += \
    CurrentView.jpg






