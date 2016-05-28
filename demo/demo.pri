
include($$PWD/../config.pri)
include($$PWD/../output.pri)

QR_FRAME_PRO = $$PWD/../source

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_FRAME_PRO/../../build_debug_qrframe/ -lQrFramed \
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_FRAME_PRO/../../build_release_qrframe/ -lQrFrame \
}

INCLUDEPATH += \
    $$QR_FRAME_PRO\include \
    $$QR_FRAME_PRO\inl \
