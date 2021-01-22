#-------------------------------------------------
#
# Project created by QtCreator 2021-01-11T14:21:44
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ans_function_test_opencv
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

CONFIG += c++14

SOURCES += \
        crc16/crc16.c \
        hidbasehandle.cpp \
        hidcomm.cpp \
        main.cpp \
        mainwindow.cpp \
        testthread.cpp \
        writefunctioncheck.cpp

HEADERS += \
        crc16/crc16.h \
        hid/hidapi.h \
        hidbasehandle.h \
        hidcomm.h \
        mainwindow.h \
        testthread.h \
        writefunctioncheck.h

FORMS += \
        mainwindow.ui
INCLUDEPATH += C:/Qt/opencv_install/include
INCLUDEPATH += C:/opencv/ans_function_test_opencv/hid/
LIBS += C:/Qt/opencv_install/x64/mingw/lib/libopencv*
LIBS += C:/opencv/ans_function_test_opencv/hid/hidapi*
LIBS += -L$$_PRO_FILE_PWD_/hid/ -lhidapi

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


