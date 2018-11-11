#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include "Scheduler.h"

TEST_CASE("TESTING CompletelyFair class") {
    CompletelyFair* scheduler0 = new CompletelyFair();
    Process* process0 = new CPUBoundProcess(0);
    
    scheduler0->addProcess(process0);

    CHECK(scheduler0->popNext(0) == process0);

    delete scheduler0;
    delete process0;
}
