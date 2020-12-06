#include <iostream>
#include <string>
#include <cmath>	
#include "BigInteger.h"

BigInt::BigInt() {
	num = "0";
	sign = false;
}

BigInt::BigInt(string str) {
	if (isdigit(str[0])) {
		setNumber(str);
		sign = false;
	}
	else
	{
		setNumber(str.substr(1));
		setSign(str[0] == '-'); // If sign is -, then sign would be true else false.
	}
}

BigInt::BigInt(string str, bool sign) {
	setNumber(str);
	setSign(sign);
}

BigInt::BigInt(int integer) {
	string str = to_string(integer);
	setNumber(str);
	if (integer < 0)
		setSign(true);
	else
		setSign(false);
}

BigInt::BigInt(const BigInt& b) {
	setNumber(b.num);
	setSign(b.sign);
}

void BigInt::setNumber(string str) {
	num = str;
}

const string& BigInt::getNumber() {
	return num;
}

void BigInt::setSign(bool s) {
	sign = s;
}

const bool& BigInt::getSign() {
	return sign;
}

BigInt BigInt::absolute() {
	return BigInt(getNumber());
}

void BigInt::operator=(BigInt operand) {
	setNumber(operand.getNumber());
	setSign(operand.getSign());
}

BigInt BigInt::operator+(BigInt b) {
	BigInt sum;
	if (getSign() == b.getSign()) {
		sum.setNumber(add(getNumber(), b.getNumber()));
		sum.setSign(getSign());
	}
	else
	{
		if (absolute() > b.absolute()) {
			sum.setNumber(subtract(getNumber(), b.getNumber()));
			sum.setSign(getSign());
		}
		else
		{
			sum.setNumber(subtract(b.getNumber(), getNumber()));
			sum.setSign(b.getSign());
		}
	}
	if (sum.getNumber() == "0") 
		sum.setSign(false);

	return sum;
}
BigInt BigInt::operator - (BigInt b)
{
	b.setSign(!b.getSign()); // x - y = x + (-y)
	return (*this) + b;
}
BigInt BigInt::operator * (BigInt b)
{
	BigInt mul;

	mul.setNumber(multiply(getNumber(), b.getNumber()));
	mul.setSign(getSign() != b.getSign());

	if (mul.getNumber() == "0") // avoid (-0) problem
		mul.setSign(false);

	return mul;
}

// Warning: Denomerator must be within "long long" size not "BigInt"
BigInt BigInt::operator / (BigInt b)
{
	long long den = toInt(b.getNumber());
	BigInt div;

	div.setNumber(divide(getNumber(), den).first);
	div.setSign(getSign() != b.getSign());

	if (div.getNumber() == "0") // avoid (-0) problem
		div.setSign(false);

	return div;
}
bool BigInt::operator == (BigInt b)
{
	return equals((*this), b);
}

bool BigInt::operator != (BigInt b)
{
	return !equals((*this), b);
}

bool BigInt::operator > (BigInt b)
{
	return greater((*this), b);
}

bool BigInt::operator < (BigInt b)
{
	return less((*this), b);
}
//-------------------------------------------------------------
bool BigInt::operator >= (BigInt b)
{
	return equals((*this), b)
		|| greater((*this), b);
}
//-------------------------------------------------------------
bool BigInt::operator <= (BigInt b)
{
	return equals((*this), b)
		|| less((*this), b);
}

bool BigInt::equals(BigInt num1, BigInt num2)
{
	return num1.getNumber() == num2.getNumber()
		&& num1.getSign() == num2.getSign();
}

bool BigInt::less(BigInt num1, BigInt num2)
{
	bool sign1 = num1.getSign();
	bool sign2 = num2.getSign();

	if (sign1 && !sign2) // if num1 is -ve and n2 is +ve
		return true;

	else if (!sign1 && sign2)
		return false;

	else if (!sign1) // both +ve
	{
		if (num1.getNumber().length() < num2.getNumber().length())
			return true;
		if (num1.getNumber().length() > num2.getNumber().length())
			return false;
		return num1.getNumber() < num2.getNumber();
	}
	else // both -ve
	{
		if (num1.getNumber().length() > num2.getNumber().length())
			return true;
		if (num1.getNumber().length() < num2.getNumber().length())
			return false;
		return num1.getNumber().compare(num2.getNumber()) > 0;
	}
}

bool BigInt::greater(BigInt num1, BigInt num2)
{
	return !equals(num1, num2) && !less(num1, num2);
}

string BigInt::add(string num1, string num2) {
	string sum = (num1.length() > num2.length()) ? num1 : num2;
	char carry = '0';
	int diff = abs(int(num1.size() - num2.size()));
	if (num1.size() > num2.size())
		num2.insert(0, diff, '0');
	else
		num1.insert(0, diff, '0');

	for (int i = num1.size() - 1; i >= 0; i--)
	{
		sum[i] = ((carry - '0') + (num
			[i] - '0') + (num2[i] - '0')) + '0';

		if (i != 0) {
			if (sum[i] > '9')
			{
				sum[i] -= 10;
				carry = '1';
			}
			else
				carry = '0';
		}
	}
	if (sum[0] > '9') {
		sum[0] -= 10;
		sum.insert(0, 1, '1');
	}
	return sum;

}

string BigInt::subtract(string num1, string num2)
{
	string sub = (num1.length() > num2.length()) ? num1 : num2;
	int diff = abs((int)(num1.size() - num2.size()));

	if (num1.size() > num2.size())
		num2.insert(0, diff, '0');

	else
		num1.insert(0, diff, '0');

	for (int i = num1.length() - 1; i >= 0; --i)
	{
		if (num1[i] < num2[i])
		{
			num1[i] += 10;
			num1[i - 1]--;
		}
		sub[i] = ((num1[i] - '0') - (num2[i] - '0')) + '0';
	}

	while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
		sub.erase(0, 1);

	return sub;
}


string BigInt::multiply(string num1, string num2)
{
	if (num1.length() > num2.length())
		num1.swap(num2);

	string res = "0";
	for (int i = num1.length() - 1; i >= 0; --i)
	{
		string temp = num2;
		int currentDigit = num1[i] - '0';
		int carry = 0;

		for (int j = temp.length() - 1; j >= 0; --j)
		{
			temp[j] = ((temp[j] - '0') * currentDigit) + carry;

			if (temp[j] > 9)
			{
				carry = (temp[j] / 10);
				temp[j] -= (carry * 10);
			}
			else
				carry = 0;

			temp[j] += '0'; 
		}

		if (carry > 0)
			temp.insert(0, 1, (carry + '0'));

		temp.append((num1.length() - i - 1), '0'); // as like mult by 10, 100, 1000, 10000 and so on

		res = add(res, temp);
	}

	while (res[0] == '0' && res.length() != 1) // erase leading zeros
		res.erase(0, 1);

	return res;
}


pair<string, long long> BigInt::divide(string str, long long den)
{
	long long rem = 0;
	string result; result.resize(10000);

	for (int indx = 0, len = str.length(); indx < len; ++indx)
	{
		rem = (rem * 10) + (str[indx] - '0');
		result[indx] = rem / den + '0';
		rem %= den;
	}
	result.resize(str.length());

	while (result[0] == '0' && result.length() != 1)
		result.erase(0, 1);

	if (result.length() == 0)
		result = "0";

	return make_pair(result, rem);
}

string BigInt::toString(long long n)
{
	return (n >= 0 ? "" : "-") + to_string(n);
}

long long BigInt::toInt(string s)
{
	long long sum = 0;

	for (int i = 0; i < s.length(); i++)
		sum = (sum * 10) + (s[i] - '0');

	return sum;
}