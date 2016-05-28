
CONFIG(debug, debug|release) {
    DLLDESTDIR = $$PWD/../build_debug_output
}
CONFIG(release, debug|release) {
    DLLDESTDIR = $$PWD/../build_release_output
}
