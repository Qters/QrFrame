
include($$PWD/../demo.pri)

TEMPLATE = lib

CONFIG(debug, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../Qters_debug/qrframe/modules
    DLLDESTDIR = $$QR_FRAME_PRO/../../Qters_debug/output/modules
}
CONFIG(release, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../Qters_release/output/modules
    DLLDESTDIR = $$QR_FRAME_PRO/../../Qters_release/qrframe/modules
}
