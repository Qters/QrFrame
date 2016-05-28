
include($$PWD/../demo.pri)

TEMPLATE = lib

CONFIG(debug, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../build_debug_output/modules
    DLLDESTDIR = $$QR_FRAME_PRO/../../build_debug_qrframe/modules
}
CONFIG(release, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../build_release_output/modules
    DLLDESTDIR = $$QR_FRAME_PRO/../../build_release_qrframe/modules
}
