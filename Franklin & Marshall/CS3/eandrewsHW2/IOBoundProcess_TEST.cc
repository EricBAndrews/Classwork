#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include"Process.h"

TEST_CASE("TESTING IOBoundProcess class") {
    IOBoundProcess* process0 = new IOBoundProcess(1);

    CHECK(process0->getID() == 1);
    CHECK(process0->getCPUTime() == 0);
    CHECK(process0->getWaitTime(0) == 0);
    CHECK_FALSE(process0->isBlocked(0));
    CHECK(process0->simulate(0, 10) <= 10);

    delete process0;
}
