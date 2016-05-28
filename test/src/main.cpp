
#include "qrtestsuitefactory.h"
#include "qrrunner.h"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);
    return Qters::QrTest::QrRunner::runAllTest ();
}
