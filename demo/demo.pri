
include($$PWD/../config.pri)

QR_FRAME_PRO = $$PWD/../source

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_FRAME_PRO/../../Qters_debug/qrframe/ -lQrFramed \
}

CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_FRAME_PRO/../../Qters_release/qrframe/ -lQrFrame \
}

INCLUDEPATH += \
    $$QR_FRAME_PRO\include \
    $$QR_FRAME_PRO\inl \
