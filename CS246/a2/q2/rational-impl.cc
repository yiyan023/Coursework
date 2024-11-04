module rational;
import <iostream>;
import <string>;
using namespace std;

Rational::Rational(int num, int den) {
    this->num = num;
    this->den = den;   
    simplify();
}

Rational Rational::operator+(const Rational &rhs) const {
	Rational sum;
	sum.den = this->den * rhs.den; 
	sum.num = (this->num * rhs.den) + (rhs.num * this->den);
	sum.simplify();
	return sum;
}

Rational Rational::operator-(const Rational &rhs) const {
	Rational diff;
	diff.den = this->den * rhs.den; 
	diff.num = (this->num * rhs.den) - (rhs.num * this->den);
	diff.simplify();
	return diff;
}

Rational Rational::operator*(const Rational &rhs) const {
	Rational prod;
	prod.den = this->den * rhs.den;
	prod.num = this->num * rhs.num;
	prod.simplify();
	return prod;
}

Rational Rational::operator/(const Rational &rhs) const {
	Rational quot;
	quot.den = this->den * rhs.num;
	quot.num = this->num * rhs.den;
	quot.simplify();
	return quot;
}

Rational Rational::operator-() const {
	Rational neg;
	neg.num = -this->num;
	neg.den = this->den;
	neg.simplify();
	return neg;
}

Rational& Rational::operator+=(const Rational &rhs) {
	Rational sum = *this + rhs;
	sum.simplify();
	this->num = sum.num;
	this->den = sum.den;
	return *this;
}

Rational& Rational::operator-=(const Rational &rhs) {
	Rational diff = *this - rhs;
	diff.simplify();
	this->num = diff.num;
	this->den = diff.den;
	return *this;
}

int Rational::getNumerator() const {
	return num;
}

int greatestCommonFactor(int a, int b) { // finds the GCD of two intgers
	int res = 1;

	for(int n = 1; n <= min(a, b); n++) {
		if (a % n == 0 && b % n == 0) { // if both a and b are divisible by n, update res value
			res = n;
		}
	}

	return res;
}

int absolute(int a) { //find absolute value of an integer
	if (a < 0) {
		return -a;
	} else {
		return a;
	}
}

void Rational::simplify() {
	bool neg_den = (this->den < 0);
	int gcd = greatestCommonFactor(absolute(this->num), absolute(this->den));

	if (neg_den) {
		this->num /= -gcd;
		this->den /= -gcd; 
	} else {
		this->num /= gcd;
		this->den /= gcd;
	}

	return;
}

int Rational::getDenominator() const {
	return this->den;
}
bool Rational::isZero() const {
	return this->num == 0;
}

ostream &operator<<(ostream &out, const Rational &rat) {
	if (rat.den != 1 && rat.num != 0) {
		out << rat.num << '/' << rat.den;
	} else { // should print 1 or 0 as an integer, not a rational
		out << rat.num;
	}
	return out;
}

istream &operator>>(istream &in, Rational &rat) {
    char s = ' ';
    in >> rat.num >> s >> rat.den;
    rat.simplify();
    return in;
}
