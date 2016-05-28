QT       += core

DEFINES += SECOND_SERVICE_LIBRARY

TARGET = second_service

include($$PWD/../services.pri)

INCLUDEPATH += \
    $$PWD/include \

SOURCES += \
    src/second_service.cpp

HEADERS  += \
    include/second_service_global.h \
    include/second_service.h
