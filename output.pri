
CONFIG(debug, debug|release) {
    DLLDESTDIR = $$PWD/../Qters_debug/output
}
CONFIG(release, debug|release) {
    DLLDESTDIR = $$PWD/../Qters_release/output
}
