#include<iostream>
#include<fstream>
#include"numberTheory.hpp"
#include"ReallyLongInt.hpp"

int main(int argc, char* argv[]) {
    // argv[1] = private key; argv[2] = input file; argv[3] = output file
    std::ifstream privateKey(argv[1]);
    string dString, nString;
    ReallyLongInt d, n;
    privateKey >> dString >> nString;
    privateKey.close();
    d = dString;
    n = nString;
    std::ifstream encrypted(argv[2]);
    std::ofstream decrypted(argv[3]);
    string toDecryptString;
    ReallyLongInt toDecrypt;
    while (std::getline(encrypted, toDecryptString)) {
	toDecrypt = toDecryptString;
	decrypted << char(modPower(toDecrypt, d, n).toLongLong());
    }
    encrypted.close();
    decrypted.close();
    return 0;
}
