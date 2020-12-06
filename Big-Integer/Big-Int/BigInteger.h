#include <string>
using namespace std;
class BigInt
{
private:
    string num;
    bool sign;

public:
    BigInt();
    BigInt(string str);
    BigInt(string str, bool sign);
    BigInt(int integer);
    BigInt(const BigInt& b);
    ~BigInt();

    void setNumber(string str);
    const string& getNumber();
    void setSign(bool sign);
    const bool& getSign();
    void operator=(BigInt operand);
    BigInt operator+(BigInt operand);
    BigInt operator-(BigInt operand);
    BigInt operator*(BigInt operand);
    BigInt operator/(BigInt operand);
    bool operator == (BigInt b);
    bool operator != (BigInt b);
    bool operator > (BigInt b);
    bool operator < (BigInt b);
    bool operator >= (BigInt b);
    bool operator <= (BigInt b);
    BigInt absolute();
private:
    bool equals(BigInt num1, BigInt num2);
    bool less(BigInt num1, BigInt num2);
    bool greater(BigInt num1, BigInt num2);
    string add(string num1, string num2);
    string subtract(string num1, string num2);
    string multiply(string num1, string num2);
    pair<string, long long> divide(string n, long long den);
    string toString(long long n);
    long long toInt(string str);
};
