#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include"Process.h"

TEST_CASE("TESTING CPUBoundProcess class") {
    CPUBoundProcess* process0 = new CPUBoundProcess(1);

    CHECK(process0->getID() == 1);
    CHECK(process0->getCPUTime() == 0);
    CHECK(process0->getWaitTime(0) == 0);
    CHECK_FALSE(process0->isBlocked(0));
    CHECK(process0->simulate(0, 15) == 15);
    CHECK(process0->getCPUTime() == 15);
    CHECK(process0->getWaitTime(15) == 0);

    delete process0;
}
