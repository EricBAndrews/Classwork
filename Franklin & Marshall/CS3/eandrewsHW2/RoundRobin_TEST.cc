#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include "Scheduler.h"

TEST_CASE("TESTING RoundRobin class") {
    RoundRobin* scheduler0 = new RoundRobin();
    Process* process0 = new CPUBoundProcess(0);
    Process* process1 = new CPUBoundProcess(1);
    scheduler0->addProcess(process0);
    scheduler0->addProcess(process1);

    CHECK(scheduler0->popNext(0) == process0);
    CHECK(scheduler0->popNext(0) == process1);

    delete scheduler0;
    delete process0;
    delete process1;
}
