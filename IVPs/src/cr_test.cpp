#include "BatchSolver.h"

void start_test(cstring id)
{
    cstring jsonPath = cstring("../input/")+id+cstring(".json");
    BatchSolver test(jsonPath);
    test.setOutputPath(cstring("../output/data"));
    test.setIdentifier(id);
    test.solve();
}

int main()
{
    // AdamsBashforth
    start_test("crAB1T2");
    start_test("crAB2T2");
    start_test("crAB3T2");
    start_test("crAB4T2");

    // AdamsMoulton
    start_test("crAM2T2");
    start_test("crAM3T2");
    start_test("crAM4T2");
    start_test("crAM5T2");

    // BDF
    start_test("crBDF1T2");
    start_test("crBDF2T2");
    start_test("crBDF3T2");
    start_test("crBDF4T2");

    // CRK
    start_test("crCRKT2");

    // ESDIRK
    start_test("crESDIRKT2");

    // GL
    start_test("crGL1T2");
    start_test("crGL2T2");
    start_test("crGL3T2");

    // Fehlberg
    start_test("crFT2");

    // Dormand-Prince
    start_test("crDPT2");
}