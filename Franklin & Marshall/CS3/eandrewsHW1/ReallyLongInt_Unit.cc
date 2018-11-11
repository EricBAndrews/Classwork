#define CATCH_CONFIG_MAIN //This will make our main for us :)
#include "catch.hpp"

/*More info on Catch
  Git-Page: https://github.com/philsquared/Catch
*/

//What are we testing today?
#include"ReallyLongInt.hpp"
#include"numberTheory.hpp"

TEST_CASE("TESTING ReallyLongInt class") {

    SECTION("constructors") {
	ReallyLongInt* num0 = new ReallyLongInt();
	ReallyLongInt* num1 = new ReallyLongInt(1);
	ReallyLongInt* num2 = new ReallyLongInt(-1);
	ReallyLongInt* num3 = new ReallyLongInt("1");
	ReallyLongInt* num4 = new ReallyLongInt("-1");
	ReallyLongInt* num5 = new ReallyLongInt(*num4);
	ReallyLongInt* num6 = new ReallyLongInt(-(*num5));

	CHECK(*num0 == 0);
	CHECK(*num1 == 1);
	CHECK(*num2 == -1);
	CHECK(*num3 == 1);
	CHECK(*num4 == -1);
	CHECK(*num5 == -1);
	CHECK(*num6 == 1);
    }

    SECTION("comparison operators") {
	ReallyLongInt* num0 = new ReallyLongInt(0);
	ReallyLongInt* num1 = new ReallyLongInt(11);
	ReallyLongInt* num2 = new ReallyLongInt(22);
	ReallyLongInt* num3 = new ReallyLongInt(-11);
	ReallyLongInt* num4 = new ReallyLongInt(-22);
	ReallyLongInt* num5 = new ReallyLongInt(11);
	ReallyLongInt* num6 = new ReallyLongInt(-11);
	
	CHECK(*num0 < *num1);
	CHECK(*num1 < *num2);
	CHECK(*num0 > *num3);
	CHECK(*num3 > *num4);
	CHECK(*num3 < *num1);
	CHECK(*num1 <= *num5);
	CHECK(*num3 >= *num6);
    }

    SECTION("arithmetic operators") {
	ReallyLongInt* num0 = new ReallyLongInt(0);
	ReallyLongInt* num1 = new ReallyLongInt(11);
	ReallyLongInt* num2 = new ReallyLongInt(-11);
	ReallyLongInt* num3 = new ReallyLongInt(7);
	ReallyLongInt* num4 = new ReallyLongInt(3);
	ReallyLongInt* num5 = new ReallyLongInt(1000);
	ReallyLongInt* num6 = new ReallyLongInt(1);
	ReallyLongInt* num7 = new ReallyLongInt(LLONG_MAX);
	++(*num7);
	ReallyLongInt* num8 = new ReallyLongInt(*num7);
	++(*num8);
	ReallyLongInt* num9 = new ReallyLongInt(11);
	ReallyLongInt* num10 = new ReallyLongInt(-1044);

	CHECK(*num0 + *num1 == 11);
	CHECK(*num0 + *num2 == -11);
	CHECK(*num1 + *num2 == 0);
	CHECK(*num2 + *num1 == 0);
	CHECK(*num0 - *num1 == -11);
	CHECK(*num0 - *num2 == 11);
	CHECK(*num1 - *num2 == 22);
	CHECK(*num2 - *num1 == -22);
	CHECK(*num2 - *num2 == 0);
	CHECK(*num5 - *num6 == 999);
	CHECK(*num9 - *num10 == 1055);
	CHECK(*num0 * *num1 == 0);
	CHECK(*num0 * *num2 == 0);
	CHECK(*num1 * *num2 == -121);
	CHECK(*num0 / *num1 == 0);
	CHECK(*num0 / *num2 == 0);
	CHECK(*num1 / *num2 == -1);
	CHECK(*num2 / *num1 == -1);
	CHECK(*num3 % *num4 == 1);
	CHECK(*num8 % *num7 == 1);
    }

    SECTION("assignment operators") {
	ReallyLongInt* num0 = new ReallyLongInt(0);
	ReallyLongInt* num1 = new ReallyLongInt(99);
	ReallyLongInt* num2 = new ReallyLongInt(-99);
	
	*num0 += *num1;
	CHECK(*num0 == 99);
	*num0 -= *num2;
	CHECK(*num0 == 198);
	*num0 -= *num1;
	CHECK(*num0 == 99);
	*num0 += *num2;
	CHECK(*num0 == 0);
	*num0 -= *num1;
	CHECK(*num0 == -99);
	*num0 += *num2;
	CHECK(*num0 == -198);
	*num1 *= *num1;
	CHECK(*num1 == 9801);
	*num2 *= *num1;
	CHECK(*num2 == -970299);
	*num2 *= *num2;
	CHECK(*num2 == 941480149401);
	*num2 /= *num1;
	CHECK(*num2 == 96059601);
	
    }

    SECTION("misc operators") {
	ReallyLongInt* num0 = new ReallyLongInt(0);
	ReallyLongInt* num1 = new ReallyLongInt(1);
	ReallyLongInt* num2 = new ReallyLongInt(-1);
	
	CHECK_FALSE(*num1 == *num2);
	(*num0)++;
	CHECK(*num0 == 1);
	++(*num0);
	CHECK(*num0 == 2);
	(*num0)--;
	CHECK(*num0 == 1);
	--(*num0);
	CHECK(*num0 == 0);
	CHECK(-(*num1) == -1);
	CHECK(-(*num2) == 1);
    }

    SECTION("misc functions") {
	ReallyLongInt* num0 = new ReallyLongInt(10);
	ReallyLongInt* num1 = new ReallyLongInt(LLONG_MAX);
	ReallyLongInt* num2 = new ReallyLongInt(-10);
	long long longNum0;
	long long longNum1;
	long long longNum2;

	longNum0 = num0->toLongLong();
	CHECK(longNum0 == 10);
	longNum1 = num1->toLongLong();
	CHECK(longNum1 == LLONG_MAX);
	++(*num1);
	longNum1 = num1->toLongLong();
	CHECK(longNum1 == 0);
	longNum2 = num2->toLongLong();
	CHECK(longNum2 == -10);
    }
}

TEST_CASE("TESTING numberTheory algorithms") {
    SECTION("isPrime") {
	int intNum1 = 7;
	int intNum2 = 15;
	int intNum3 = -2;
	long long longNum1 = 7;
	long long longNum2 = 15;
	long long longNum3 = -2;
	ReallyLongInt* rlNum1 = new ReallyLongInt(7);
	ReallyLongInt* rlNum2 = new ReallyLongInt(15);
	ReallyLongInt* rlNum3 = new ReallyLongInt(-2);
	
	CHECK(isPrime(intNum1));
	CHECK_FALSE(isPrime(intNum2));
	CHECK_FALSE(isPrime(intNum3));
	CHECK(isPrime(longNum1));
	CHECK_FALSE(isPrime(longNum2));
	CHECK_FALSE(isPrime(longNum3));
	CHECK(isPrime(*rlNum1));
	CHECK_FALSE(isPrime(*rlNum2));
	CHECK_FALSE(isPrime(*rlNum3));
    }

    SECTION("modPower") {
	unsigned int intNum1 = 12;
	unsigned int intNum2 = 8;
	unsigned int intNum3 = 17;
	unsigned long long longNum1 = 12;
	unsigned long long longNum2 = 8;
	unsigned long long longNum3 = 17;
	ReallyLongInt* rlNum1 = new ReallyLongInt(121);
	ReallyLongInt* rlNum2 = new ReallyLongInt(7);
	ReallyLongInt* rlNum3 = new ReallyLongInt(31);

	CHECK(modPower(intNum1, intNum2, intNum3) == 16);
	CHECK(modPower(longNum1, longNum2, longNum3) == 16);
	CHECK(modPower(*rlNum1, *rlNum2, *rlNum3) == 14);
    }

    SECTION("extendedEuclid") {
	int intNum1 = 1234;
	int intNum2 = 7482;
	int intCo1;
	int intCo2;
	int intGCD;
	long long longNum1 = 1234;
	long long longNum2 = 7482;
	long long longCo1;
	long long longCo2;
	long long longGCD;
	ReallyLongInt* rlNum1 = new ReallyLongInt(1234);
	ReallyLongInt* rlNum2 = new ReallyLongInt(7482);
	ReallyLongInt* rlCo1 = new ReallyLongInt();
	ReallyLongInt* rlCo2 = new ReallyLongInt();
	ReallyLongInt* rlGCD = new ReallyLongInt();
	
	intGCD = extendedEuclid(intNum1, intNum2, &intCo1, &intCo2);
	longGCD = extendedEuclid(longNum1, longNum2, &longCo1, &longCo2);
	*rlGCD = extendedEuclid(*rlNum1, *rlNum2, rlCo1, rlCo2);
	CHECK(intGCD == 2);
	CHECK(longGCD == 2);
	CHECK(*rlGCD == 2);
	CHECK((intCo1 * intNum1) + (intCo2 * intNum2) == intGCD);
	CHECK((longCo1 * longNum1) + (longCo2 * longNum2) == longGCD);
	CHECK(*rlCo1 == 1055);
	CHECK(*rlCo2 == -174);
	CHECK((*rlCo1 * *rlNum1) + (*rlCo2 * *rlNum2) == *rlGCD);
    }
}
