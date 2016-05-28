QT       += core

DEFINES += FIRST_MODULE_LIBRARY

TARGET = first_module

include($$PWD/../modules.pri)

INCLUDEPATH += \
    $$PWD/include \

SOURCES += \
    src/first_module.cpp

HEADERS  += \
    include/first_module_global.h \
    include/first_module.h
