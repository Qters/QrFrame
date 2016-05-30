CONFIG   += console
CONFIG   -= app_bundle

QT += testlib

include($$PWD/../config.pri)
QR_TEST_PRO = $$PWD/../../QrTest/source
QR_FRAME_PRO = $$PWD/../source

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../Qters_debug/qrtest/ -lQrTestd \
        -L$$QR_FRAME_PRO/../../Qters_debug/qrframe/ -lQrFramed \
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../Qters_release/qrtest/ -lQrTest \
        -L$$QR_FRAME_PRO/../../Qters_release/qrframe/ -lQrFrame \
}

INCLUDEPATH += \
    $$PWD/include \
    $$QR_TEST_PRO\include \
    $$QR_FRAME_PRO\include \
    $$QR_FRAME_PRO\inl \

HEADERS += \

SOURCES += \
    src/main.cpp \

