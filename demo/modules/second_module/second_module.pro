QT       += core

DEFINES += SECOND_MODULE_LIBRARY

TARGET = second_module

include($$PWD/../modules.pri)

INCLUDEPATH += \
    $$PWD/include \

SOURCES += \
    src/second_module.cpp

HEADERS  += \
    include/second_module_global.h \
    include/second_module.h
