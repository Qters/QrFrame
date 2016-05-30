
include($$PWD/../demo.pri)

TEMPLATE = lib


CONFIG(debug, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../Qters_debug/output/services
    DLLDESTDIR = $$QR_FRAME_PRO/../../Qters_debug/qrframe/services
}
CONFIG(release, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../Qters_release/output/services
    DLLDESTDIR = $$QR_FRAME_PRO/../../Qters_release/qrframe/services
}
