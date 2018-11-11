#define CATCH_CONFIG_MAIN
#include"catch.hpp"

#include"Scheduler.h"

TEST_CASE("TESTING RoundRobin class") {

    SECTION("functions") {
	CPUBoundProcess* process0 = new CPUBoundProcess(0);
	CPUBoundProcess* process1 = new CPUBoundProcess(1);
	CPUBoundProcess* process2 = new CPUBoundProcess(2);
	RoundRobin* robin0 = new RoundRobin();

	robin0->addProcess(process0);
	robin0->addProcess(process1);
	robin0->addProcess(process2);

	CHECK(robin0->popNext(0) == process0);
	CHECK(robin0->popNext(0) == process1);
	CHECK(robin0->popNext(0) == process2);
    }
}
