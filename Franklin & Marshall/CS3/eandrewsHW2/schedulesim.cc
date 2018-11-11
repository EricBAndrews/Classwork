#include"simulate.h"
#include"Scheduler.h"

#include<iostream>
#include<cstdlib>
#include<sstream>
#include<chrono>

int main(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "wrong number of arguments (expected 3)" << std::endl;
    return 1;
  }
  int cpuCount = std::atoi(argv[1]);
  int ioCount = std::atoi(argv[2]);
  int cycles = std::atoi(argv[3]);
  Scheduler* schedulers[] = {new RoundRobin(),
                             new FastRoundRobin(),
                             // new CompletelyFair(),
                             new FastCompletelyFair()};
  std::string resultArray[4];
  // auto start = std::chrono::system_clock::now(); // gets start time
  for (int i = 0; i < 3; ++i) {
    std::stringstream resultString;
    double* results = simulate(schedulers[i], cpuCount, ioCount, cycles);
    resultString << "naoseconds per scheduler call: " << results[0] << std::endl
                 << "average cpu-bound cpu time: " << results[1] << std::endl
                 << "average cpu-bound wait time: " << results[2] << std::endl
                 << "average io-bound cpu time: " << results[3] << std::endl
                 << "average io-bound wait time: " << results[4] << std::endl;
    resultArray[i] = resultString.str();
  }
  // auto end = std::chrono::system_clock::now();
  // auto dur = end - start;
  // auto durNS = std::chrono::duration_cast<std::chrono::nanoseconds>(dur);
  // std::cout << "elapsed: " << durNS.count() << std::endl;
  std::string schedulerTypes[] = {"Round Robin:",
                                  "Fast Round Robin:",
                                  // "Completely Fair: ",
                                  "Fast Completely Fair: "};
  for (int i = 0; i < 3; ++i) {
    std::cout << schedulerTypes[i] << std::endl << resultArray[i] << std::endl;
  }
  for (int i = 0; i < 3; ++i) {
    delete schedulers[i];
  }
  return 0;
}
