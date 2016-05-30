
include($$PWD/path.pri)

CONFIG += c++11

CONFIG(debug, debug|release) {
    unix: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)

    DESTDIR = $$PWD/../Qters_debug/qrframe
}
CONFIG(release, debug|release) {
    DESTDIR = $$PWD/../Qters_release/qrframe
}

CONFIG(debug, debug|release) {
    LIBS += \
        -L$$QR_COMMON_PRO/../../Qters_debug/qrcommon/ -lQrCommond \
        -L$$QR_ORM_PRO/../../Qters_debug/qrorm/ -lQrOrmd \
        -L$$QR_LOGGER_PRO/../Qters_debug/qrlogger/ -lQrLoggerd \
}
CONFIG(release, debug|release) {
    LIBS += \
        -L$$QR_COMMON_PRO/../../Qters_release/qrcommon/ -lQrCommon \
        -L$$QR_LOGGER_PRO/../Qters_release/qrlogger/ -QrLogger \
}
INCLUDEPATH += \
    $$QR_COMMON_PRO/include \
    $$QR_COMMON_PRO/inl \
    $$QR_ORM_PRO/include \
    $$QR_ORM_PRO/inl \
    $$QR_LOGGER_PRO/include \
