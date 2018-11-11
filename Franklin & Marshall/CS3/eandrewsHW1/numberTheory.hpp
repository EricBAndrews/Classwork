#ifndef NUMBERTHEORY_H
#define NUMBERTHEORY_H
#include<iostream>

template<class X>
bool isPrime(const X& num) {
    if (num < 2) {
	return false;
    }
    X i;
    for (i = 2; i <= num / 2; ++i) {
	if (num % i == 0) {
	    return false;
	}
    }
    return true;
}

template<class X>
X modPower(const X& base, const X& exponent, const X& modulus) {
    // assumes all input non-negative, modulus != 0
    if (exponent == 0) {
	return 1 % modulus;
    }
    X modbase = base % modulus;
    X x = modPower(modbase, exponent / 2, modulus);
    X modx = x % modulus;
    if (exponent % 2 != 0) {
	return (modbase * modx * modx) % modulus;
    }
    return (modx * modx) % modulus;
}

template<class X>
X extendedEuclid(const X& a, const X& b, X* x, X* y) {
    if (b == 0) {
	*x = (X)1;
	*y = (X)0;
	return a;
    }
    X tempx;
    X tempy;
    X d = extendedEuclid(b, a % b, &tempx, &tempy);
    *x = tempy;
    *y = tempx - (tempy * (a / b));
    return d;
}

#endif
