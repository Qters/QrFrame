QT       += core gui widgets

TARGET = frame_demo
TEMPLATE = app

include($$PWD/../demo.pri)

CONFIG(debug, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../Qters_debug/output
}
CONFIG(release, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../Qters_release/output
}

INCLUDEPATH += \
    $$PWD/include \

SOURCES += \
    src/main.cpp \
    src/demomainwindow.cpp

HEADERS  += \
    include/demomainwindow.h
