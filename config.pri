
include($$PWD/path.pri)

CONFIG += c++11

CONFIG(debug, debug|release) {
    unix: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)

    DESTDIR = $$PWD/../build_debug_qrframe
}
CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../build_release_qrframe
}

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_COMMON_PRO/../../build_debug_qrcommon/ -lQrCommond \
        -L$$QR_ORM_PRO/../../build_debug_qrorm/ -lQrOrmd \
        -L$$QR_LOGGER_PRO/../build_debug_qrlogger/ -lQrLoggerd \
}
CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_COMMON_PRO/../../build_release_qrcommon/ -lQrCommon \
        -L$$QR_LOGGER_PRO/../build_release_qrlogger/ -QrLogger \
}
INCLUDEPATH += \
    $$QR_COMMON_PRO/include \
    $$QR_COMMON_PRO/inl \
    $$QR_ORM_PRO/include \
    $$QR_ORM_PRO/inl \
    $$QR_LOGGER_PRO/include \
