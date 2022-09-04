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
    start_test("main");
    start_test("main2");
    return 0;
}