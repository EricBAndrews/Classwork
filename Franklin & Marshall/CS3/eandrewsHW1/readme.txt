Eric Andrews
Project 1: RSA
= = = = = = = = = = = = = = = =
FILES
- - - - - - - -
primary:
encrypt.cc
decrypt.cc
numberTheory.cc
keygen.cc
ReallyLongInt.cc
factorial.cc
numberTheory.h
ReallyLongInt.h
Makefile
Homework Cover Sheet-1.docx
readme.txt

secondary:
ReallyLongInt_Unit.cc
private.txt
public.txt
plaintext.txt
encrypted.txt
decrypted.txt
catch.hpp

other:
encrypt
decrypt
keygen
ReallyLongInt.o
factorial
ReallyLongIntUnit
= = = = = = = = = = = = = = = =
INSTRUCTIONS
- - - - - - - -
invoking `make' will compile all primary source files; invoking `make catchdebug' will compile the unit tests, and invoking `make coverage' will compile the unit tests for coverage testing. make can also be invoked with any specific file to compile (e.g. `make encrypt' to only compile encrypt.cc).

keygen:
keygen is used to generate a public/private keypair from two prime numbers, and writes them to specified text files.
keygen takes 4 command line arguments: two prime numbers, the name of the file to store the public key in, and the name of the file to store the private key in.
       example: ./keygen 7 11 public.txt private.txt

encrypt:
encrypt uses a public key to encrypt a specified plaintext file, and stores the encrypted output in a specified file.
encrypt takes 3 command line arguments: the public key to encrypt with, the name of the text file to encrypt, and the name of the file to put the encrypted output in.
	example: ./encrypt public.txt plaintext.txt encrypted.txt

decrypt:
decrypt uses a private key to decrypt a specified file encrypted with the encrypt program, and stores the decrypted output in a specified file.
decrypt takes 3 command line arguments: the private key to decrypt with, the name of the text file to decrypt, and the name of the file to put the decrypted output in.
	example: ./decrypt private.txt encrypted.txt decrypted.txt

factorial:
factorial computes the factorial of a given number of any length.
factorial takes 1 command line argument: the number to compute the factorial of.

ReallyLongIntUnit:
ReallyLongIntUnit runs the unit tests in ReallyLongInt_Unit.cc.
ReallyLongIntUnit takes 0 command line arguments.

NumberTheoryUnit:
NumberTheoryUnit runs the unit tests in NumberTheory_Unit.cc.
NumberTheoryUnit takes 0 command line arguments.
= = = = = = = = = = = = = = = =
KNOWN ISSUES
- - - - - - - -
none
