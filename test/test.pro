CONFIG   += console
CONFIG   -= app_bundle

QT += testlib

include($$PWD/../config.pri)
QR_TEST_PRO = $$PWD/../../QrTest/source
QR_FRAME_PRO = $$PWD/../source

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../build_debug_qrtest/ -lQrTestd \
        -L$$QR_FRAME_PRO/../../build_debug_qrframe/ -lQrFramed \
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_TEST_PRO/../../build_release_qrtest/ -lQrTest \
        -L$$QR_FRAME_PRO/../../build_release_qrframe/ -lQrFrame \
}

INCLUDEPATH += \
    $$PWD/include \
    $$QR_TEST_PRO\include \
    $$QR_FRAME_PRO\include \
    $$QR_FRAME_PRO\inl \

HEADERS += \

SOURCES += \
    src/main.cpp \

