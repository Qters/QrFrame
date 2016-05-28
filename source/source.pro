
QT       += core xml gui widgets sql

TARGET = QrFrame

TEMPLATE = lib

DEFINES += QRFRAME_LIBRARY

include($$PWD/../config.pri)
include($$PWD/../output.pri)

INCLUDEPATH += \
    $$PWD/inl \
    $$PWD/include \

HEADERS += \
    include/qrframe_global.h \
    include/qrmainwindow.h \
    include/core/qrmoduleinterface.h \
    include/core/qrserviceinterface.h \
    include/core/qrserviceloader.h \
    include/core/qrframer.h \
    include/db/qrtblloadinfo.h \
    include/db/qrtblloadtype.h \
    include/db/qrdblocal.h \
    include/db/qrtblframeconfig.h

SOURCES += \
    src/qrmainwindow.cpp \
    src/core/qrframer.cpp \
    src/core/qrserviceloader.cpp \
    src/db/qrtblloadinfo.cpp \
    src/db/qrtblloadtype.cpp \
    src/db/qrdblocal.cpp \
    src/db/qrtblframeconfig.cpp
