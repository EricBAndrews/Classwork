#include<math.h>
#include "ReallyLongInt.hpp"

// private
ReallyLongInt::ReallyLongInt(unsigned int* digitArr, unsigned int arrSize, bool isNeg) {
    removeLeadingZeros(digitArr, arrSize);
    digits = digitArr;
    numDigits = arrSize;
    this->isNeg = digits[0] != 0 ? isNeg : false;
}

void ReallyLongInt::removeLeadingZeros(unsigned int* x, unsigned int& xSize) const {
    unsigned int i;
    unsigned int j;
    unsigned int tempSize = xSize; // size without leading zeros
    for (i = 0; i < xSize; i++) {
	// find size without leading zeros
	if (x[i] == 0) {
	    tempSize--;
	}
	// shift all numbers to the front of the rlInt
	else {
	    for (j = 0; j < tempSize; j++) {
		x[j] = x[i + j];
	    }
	    break;
	}
    }
    // zero case
    if (tempSize == 0) {
	tempSize = 1;
    }
    // new size
    xSize = tempSize;
}

void ReallyLongInt::swap(ReallyLongInt other) {
    std::swap(this->isNeg, other.isNeg);
    std::swap(this->digits, other.digits);
    std::swap(this->numDigits, other.numDigits);
}

bool ReallyLongInt::absGreater(const ReallyLongInt& other) const {
    // get different orders of magnitude out of the way
    if (numDigits > other.numDigits) {
	return true;
    }
    if (other.numDigits > numDigits) {
	return false;
    }
    // digit-by-digit comparison starting from the most significant and working down
    unsigned int i;
    for (i = 0; i < numDigits; i++) {
	if (digits[i] > other.digits[i]) {
	    return true;
	}
	if (digits[i] < other.digits[i]) {
	    return false;
	}
    }
    return false;
}

ReallyLongInt ReallyLongInt::absAdd(const ReallyLongInt& other) const {
    unsigned int resultSize;
    if (this->absGreater(other)) {
	resultSize = numDigits + 1;
    }
    else {
	resultSize = other.numDigits + 1;
    }
    unsigned int* sum = new unsigned int[resultSize];
    unsigned int carry = 0;
    unsigned int i;
    unsigned int xDigit;
    unsigned int yDigit;
    unsigned int curDigit;
    ReallyLongInt* ret;
    for (i = 0; i < resultSize; i++) {
	// get digits to add
	if (i > numDigits - 1) {
	    xDigit = 0;
	}
	else {
	    xDigit = digits[numDigits - 1 - i];
	}
	if (i > other.numDigits - 1) {
	    yDigit = 0;
	}
	else {
	    yDigit = other.digits[other.numDigits - 1 - i];
	}
	// add the digits
	curDigit = xDigit + yDigit + carry;
	carry = 0;
	// carry
	if (curDigit > 9) {
	    sum[resultSize - 1 - i] = curDigit % 10;
	    carry = curDigit / 10;
	}
	else {
	    sum[resultSize - 1 - i] = curDigit;
	}
    }
    removeLeadingZeros(sum, resultSize);
    ret = new ReallyLongInt();
    ret->isNeg = false;
    ret->digits = sum;
    ret->numDigits = resultSize;
    delete[] sum;
    return *ret;
}

ReallyLongInt ReallyLongInt::absSub(const ReallyLongInt& other) const {
    ReallyLongInt x; // larger operand
    ReallyLongInt y; // smaller operand
    bool retIsNeg;
    unsigned int difDigits;
    unsigned int* dif;
    unsigned int i;
    unsigned int borrowIndex;
    ReallyLongInt* ret;
    if (other.absGreater(*this)) {
	x = other;
	y = *this;
	retIsNeg = true;
    }
    else {
	y = other;
	x = *this;
	retIsNeg = false;
    }
    // std::cout << "x: " << x << " y: " << y << std::endl;
    difDigits = x.numDigits;
    dif = new unsigned int[difDigits];
    for (i = 0; i < difDigits; i++) {
	dif[i] = x.digits[i];
    }
    for (i = 0; i < y.numDigits; i++) {
	if (dif[difDigits - 1 - i] < y.digits[y.numDigits - 1 - i]) {
	    // need to borrow
	    borrowIndex = difDigits - 1 - i;
	    dif[borrowIndex] += 10;
	    borrowIndex--;
	    while (dif[borrowIndex] == 0) {
		dif[borrowIndex] = 9;
		borrowIndex--;
	    }
	    dif[borrowIndex]--;
	}
	dif[difDigits - 1 - i] -= y.digits[y.numDigits - 1 - i];
    }
    removeLeadingZeros(dif, difDigits);
    ret = new ReallyLongInt();
    ret->isNeg = retIsNeg;
    ret->digits = dif;
    ret->numDigits = difDigits;
    delete[] dif;
    return *ret;
}

ReallyLongInt ReallyLongInt::absMult(const ReallyLongInt& other) const {
    unsigned int prodNumDigits = this->numDigits + other.numDigits;
    unsigned int* prod = new unsigned int[prodNumDigits];
    unsigned int i;
    unsigned int j;
    unsigned int carry;
    unsigned int curDigit;
    unsigned int sum;
    for (i = 0; i < prodNumDigits; i++) {
	prod[i] = 0;
    }
    for (i = 0; i < this->numDigits; i++) {
	carry = 0;
	for (j = 0; j < other.numDigits; j++) {
	    curDigit = prodNumDigits - i - j - 1;
	    sum = prod[curDigit] + carry + this->digits[this->numDigits - 1 - i] *
		other.digits[other.numDigits - 1 - j];
	    prod[curDigit] = sum % 10;
	    carry = sum / 10;
	}
	prod[this->numDigits - 1 - i] += carry;
    }
    removeLeadingZeros(prod, prodNumDigits);
    ReallyLongInt* ret = new ReallyLongInt();
    ret->digits = prod;
    ret->numDigits = prodNumDigits;
    delete[] prod;
    return *ret;
}

void ReallyLongInt::absDiv(const ReallyLongInt& other, ReallyLongInt& quotient,
			ReallyLongInt& remainder) const {
    unsigned int quotSize = numDigits;
    unsigned int* quotDigits = new unsigned int[quotSize];
    unsigned int i;
    unsigned int digit;
    remainder = 0;
    for (i = 0; i < numDigits; ++i) {
	remainder = remainder.absMult(10);
	remainder = remainder.absAdd(digits[i]);
	digit = 0;
	while (remainder.absGreater(other.absSub(1))) {
	    remainder = remainder.absSub(other);
	    ++digit;
	}
	quotDigits[i] = digit;
    }
    removeLeadingZeros(quotDigits, quotSize);
    quotient.digits = quotDigits;
    quotient.numDigits = quotSize;
}
    
void ReallyLongInt::flipSign() {
    if (*this != 0) {
	isNeg = !isNeg;
    }
}

// public
ReallyLongInt::ReallyLongInt() {
    // creates a rlInt equal to 0
    isNeg = false;
    unsigned int* tempDigits = new unsigned int[1];
    tempDigits[0] = 0;
    digits = tempDigits;
    numDigits = 1;
}

ReallyLongInt::ReallyLongInt(long long num) {
    // creates a rlInt equal to num
    long long tempNum;
    unsigned int i;
    unsigned int* tempDigits;
    int digitIndex;
    if (num < 0) {
	isNeg = true;
	tempNum = num * -1;
    }
    else {
	isNeg = false;
	tempNum = num;
    }
    if (num == 0) {
	numDigits = 1;
    }
    else {
	numDigits = log10(tempNum) / 1 + 1;
    }
    tempDigits = new unsigned int[numDigits];
    digitIndex = numDigits - 1;
    for (i = 0; i < numDigits; i++) {
	tempDigits[digitIndex - i] = tempNum % 10;
	tempNum = tempNum / 10;
    }
    digits = tempDigits;
}

ReallyLongInt::ReallyLongInt(const string& numStr) {
    numDigits = numStr.size();
    unsigned int* longNum = new unsigned int[numDigits];
    unsigned int i = 0;
    if (numStr[0] == '-') {
	i = 1;
	longNum[0] = 0;
	isNeg = numStr[1] != '0' ? true : false;
    }
    else {
	isNeg = false;
    }
    for (; i < numDigits; ++i) {
	longNum[i] = numStr[i] - 48;
    }
    removeLeadingZeros(longNum, numDigits);
    digits = longNum;
}

ReallyLongInt::ReallyLongInt(const ReallyLongInt& other) {
    unsigned int i;
    unsigned int* temp;
    numDigits = other.numDigits;
    isNeg = other.isNeg;
    temp = new unsigned int[numDigits];
    for (i = 0; i < numDigits; i++) {
	temp[i] = other.digits[i];
    }
    digits = temp;
}

ReallyLongInt::~ReallyLongInt() {
    delete[](digits);
}

long long ReallyLongInt::toLongLong() const {
    ReallyLongInt* temp = new ReallyLongInt(*this);
    ReallyLongInt* max = new ReallyLongInt(LLONG_MAX);
    ReallyLongInt* maxPlus = new ReallyLongInt(*max);
    ++(*maxPlus);
    while (*temp > *max) {
	*temp %= *maxPlus;
    }
    long long ret = 0;
    unsigned int i;
    for (i = 0; i < temp->numDigits; i++) {
	ret *= 10;
	ret += temp->digits[i];
    }
    if (isNeg) {
	ret *= -1;
    }
    delete temp;
    delete max;
    delete maxPlus;
    return ret;
}

bool ReallyLongInt::equal(const ReallyLongInt& other) const {
    // ASSUMES LEADING ZEROS ARE STRIPPED
    // can't be equal if they're different sizes
    if (numDigits != other.numDigits) {
	return false;
    }
    // can't be equal if they're a different sign
    if (isNeg ^ other.isNeg) { // i like bitwise operators. sue me.
	return false;
    }
    // digit-by-digit comparison; direction doesn't matter
    unsigned int i;
    for (i = 0; i < numDigits; i++) {
	if (digits[i] != other.digits[i]) {
	    return false;
	}
    }
    return true;
}

bool ReallyLongInt::greater(const ReallyLongInt &other) const {
    if (isNeg ^ other.isNeg) {
	return other.isNeg;
    }
    if (isNeg) {
	if (this->equal(other)) {
	    return false;
	}
	return !absGreater(other);
    }
    return absGreater(other);
}

ReallyLongInt ReallyLongInt::add(const ReallyLongInt &other) const {
    if (isNeg && other.isNeg) {
	ReallyLongInt ret = this->absAdd(other);
	ret.flipSign();
	return ret;
    }
    if (isNeg) {
	return other.absSub(*this);
    }
    if (other.isNeg) {
	return this->absSub(other);
    }
    return this->absAdd(other);
}

ReallyLongInt ReallyLongInt::sub(const ReallyLongInt &other) const {
    if (isNeg && other.isNeg) {
	return other.absSub(*this);
    }
    if (isNeg) {
	ReallyLongInt ret = this->absAdd(other);
	ret.flipSign();
	return ret;
    }
    if (other.isNeg) {
	return this->absAdd(other);
    }
    return this->absSub(other);
}

ReallyLongInt ReallyLongInt::mult(const ReallyLongInt &other) const {
    ReallyLongInt ret = this->absMult(other);
    if (isNeg ^ other.isNeg && ret != 0) {
	ret.flipSign();
    }
    return ret;
}

void ReallyLongInt::div(const ReallyLongInt& denominator, ReallyLongInt& quotient,
			ReallyLongInt& remainder) const {
    this->absDiv(denominator, quotient, remainder);
    if (isNeg ^ denominator.isNeg) {
	quotient.flipSign();
    }
    if (isNeg) {
	remainder.flipSign();
    }
}

ReallyLongInt ReallyLongInt::operator-() const {
    ReallyLongInt* ret = new ReallyLongInt(*this);
    ret->isNeg = !ret->isNeg;
    return *ret;
}

ReallyLongInt& ReallyLongInt::operator=(const ReallyLongInt& other) {
    swap(other);
    return *this;
}

ReallyLongInt& ReallyLongInt::operator+=(const ReallyLongInt &other) {
    *this = *this + other;
    return *this;
}

ReallyLongInt& ReallyLongInt::operator-=(const ReallyLongInt &other) {
    *this = *this - other;
    return *this;
}

ReallyLongInt& ReallyLongInt::operator*=(const ReallyLongInt &other) {
    *this = *this * other;
    return *this;
}

ReallyLongInt& ReallyLongInt::operator/=(const ReallyLongInt &other) {
    *this = *this / other;
    return *this;
}

ReallyLongInt& ReallyLongInt::operator%=(const ReallyLongInt &other) {
    *this = *this % other;
    return *this;
}

ReallyLongInt& ReallyLongInt::operator++() {
    *this = *this + 1;
    return *this;
}

ReallyLongInt& ReallyLongInt::operator--() {
    *this = *this - 1;
    return *this;
}

ReallyLongInt ReallyLongInt::operator++(int dummy) {
    ReallyLongInt ret = *this;
    *this = *this + 1;
    return ret;
}

ReallyLongInt ReallyLongInt::operator--(int dummy) {
    ReallyLongInt ret = *this;
    *this = *this - 1;
    return ret;
}

ostream& ReallyLongInt::print(ostream& out) const {
    unsigned int i;
    if (isNeg) {
	out << '-';
    }
    for (i = 0; i < numDigits; i++) {
	out << digits[i];
    }
    return out;
}

// independent functions
bool operator==(const ReallyLongInt& x, const ReallyLongInt& y) {
    return x.equal(y);
}

bool operator!=(const ReallyLongInt& x, const ReallyLongInt& y) {
    return !x.equal(y);
}

bool operator>(const ReallyLongInt& x, const ReallyLongInt& y) {
    return x.greater(y);
}

bool operator<(const ReallyLongInt& x, const ReallyLongInt& y) {
    return y.greater(x);
}

bool operator>=(const ReallyLongInt& x, const ReallyLongInt& y) {
    return x.equal(y) || x.greater(y);
}

bool operator<=(const ReallyLongInt& x, const ReallyLongInt& y) {
    return x.equal(y) || y.greater(x);
}

ReallyLongInt operator+(const ReallyLongInt& x, const ReallyLongInt& y) {
    return x.add(y);
}

ReallyLongInt operator-(const ReallyLongInt& x, const ReallyLongInt& y) {
    return x.sub(y);
}

ReallyLongInt operator*(const ReallyLongInt& x, const ReallyLongInt& y) {
    return x.mult(y);
}

ReallyLongInt operator/(const ReallyLongInt& x, const ReallyLongInt& y) {
    ReallyLongInt* quotient = new ReallyLongInt();
    ReallyLongInt* remainder = new ReallyLongInt();
    x.div(y, *quotient, *remainder);
    return *quotient;
}

ReallyLongInt operator%(const ReallyLongInt& x, const ReallyLongInt& y) {
    ReallyLongInt* quotient = new ReallyLongInt();
    ReallyLongInt* remainder = new ReallyLongInt();
    x.div(y, *quotient, *remainder);
    return *remainder;
}

ostream& operator<<(ostream& out, const ReallyLongInt& x) {
    return x.print(out);
}
