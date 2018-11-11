#include<iostream>
#include<fstream>
#include"numberTheory.hpp"
#include"ReallyLongInt.hpp"

int main(int argc, char* argv[]) {
    // argv[1] = public key; argv[2] = input file; argv[3] = output file
    std::ifstream publicKey(argv[1]);
    string eString, nString;
    ReallyLongInt e, n;
    publicKey >> eString >> nString;
    publicKey.close();
    e = eString;
    n = nString;
    std::ifstream plaintext(argv[2]);
    std::ofstream encrypted(argv[3]);
    char toEncryptChar;
    ReallyLongInt toEncrypt;
    while (plaintext.get(toEncryptChar)) {
	toEncrypt = toEncryptChar;
	encrypted << modPower(toEncrypt, e, n) << std::endl;
    }
    plaintext.close();
    encrypted.close();
    return 0;
}
