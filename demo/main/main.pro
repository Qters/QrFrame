QT       += core gui widgets

TARGET = frame_demo
TEMPLATE = app

include($$PWD/../demo.pri)

CONFIG(debug, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../build_debug_output
}
CONFIG(release, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../build_release_output
}

INCLUDEPATH += \
    $$PWD/include \

SOURCES += \
    src/main.cpp \
    src/demomainwindow.cpp

HEADERS  += \
    include/demomainwindow.h
