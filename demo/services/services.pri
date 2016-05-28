
include($$PWD/../demo.pri)

TEMPLATE = lib


CONFIG(debug, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../build_debug_output/services
    DLLDESTDIR = $$QR_FRAME_PRO/../../build_debug_qrframe/services
}
CONFIG(release, debug|release) {
    DESTDIR = $$QR_FRAME_PRO/../../build_release_output/services
    DLLDESTDIR = $$QR_FRAME_PRO/../../build_release_qrframe/services
}
