#include<iostream>
#include<fstream>
#include"numberTheory.hpp"
#include"ReallyLongInt.hpp"

int main(int argc, char* argv[]) {
    // parse numerical command line arguments
    string strNum1 = argv[1];
    string strNum2 = argv[2];
    ReallyLongInt num1 = ReallyLongInt(strNum1);
    ReallyLongInt num2 = ReallyLongInt(strNum2);
    // make sure given numbers are prime
    if (!isPrime(num1)) {
    	std::cout << num1 << " is not prime; exiting" << std::endl;
    	return 1;
    }
    else if (!isPrime(num2)) {
    	std::cout << num2 << " is not prime; exiting" << std::endl;
    	return 1;
    }
    // calculate n, t, e, d
    ReallyLongInt n = num1 * num2;
    ReallyLongInt t = (num1 - 1) * (num2 - 1);
    ReallyLongInt e;
    ReallyLongInt d;
    ReallyLongInt y;
    for (e = 2; e < t; ++e) {
    	if (extendedEuclid(e, t, &d, &y) == 1) {
    	    break;
    	}
    }
    if (d < 0) {
    	d = d + t;
    }
    // write output to files
    std::ofstream publicKey(argv[3]);
    std::ofstream privateKey(argv[4]);
    publicKey << e << " " << n << std::endl;
    privateKey << d << " " << n << std::endl;
    publicKey.close();
    privateKey.close();
    return 0;
}
