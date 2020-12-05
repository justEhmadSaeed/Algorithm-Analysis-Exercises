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
    BigInt(BigInt* b);
    ~BigInt();

    void setNumber(string str);
    const string& getNumber();
    void setSign(bool sign);
    void operator=(BigInt operand);
    BigInt& operator+(BigInt operand);
    BigInt& operator-(BigInt operand);
    BigInt& operator*(BigInt operand);
    BigInt& operator/(BigInt operand);

private:
    bool equals(BigInt num1, BigInt num2);
};
