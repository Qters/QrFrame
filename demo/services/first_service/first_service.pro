QT       += core

DEFINES += FIRST_SERVICE_LIBRARY

TARGET = first_service

include($$PWD/../services.pri)

INCLUDEPATH += \
    $$PWD/include \

SOURCES += \
    src/first_service.cpp

HEADERS  += \
    include/first_service_global.h \
    include/first_service.h
