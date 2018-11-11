#include"ReallyLongInt.hpp"

int main(int argc, char* argv[]) {
    if (argc != 2) {
	cout << "error: wrong number of arguments (expected 1). exiting.";
	return 1;
    }
    ReallyLongInt* x = new ReallyLongInt(argv[1]);
    ReallyLongInt* cur = new ReallyLongInt(1);
    ReallyLongInt* ret = new ReallyLongInt(1);
    for (; *cur <= *x; ++*cur) {
	*ret *= *cur;
    }
    std::cout << *ret << std::endl;
    return 0;
}
