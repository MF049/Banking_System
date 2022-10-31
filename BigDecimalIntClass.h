#ifndef BIGDECIMALINT_BIGDECIMALINTCLASS_H
#define BIGDECIMALINT_BIGDECIMALINTCLASS_H

#include <iostream>
#include <deque>
#include <regex>

using namespace std;

class BigDecimalInt{
private:
    string number;
    char sign;
    void setNumber(string num);
    bool checkValidInput(string input);

public:
    bool operator < (const BigDecimalInt& anotherDec);
    bool operator > (const BigDecimalInt& anotherDec);
    bool operator == (const BigDecimalInt anotherDec);
    BigDecimalInt& operator = (BigDecimalInt anotherDec);
    BigDecimalInt operator + (BigDecimalInt number2);
    BigDecimalInt operator - (BigDecimalInt anotherDec);
    friend ostream &operator << (ostream &out, BigDecimalInt num);
    int size();
    int Sign();
    void push_back(char ch);
    void push_front(char ch);
    BigDecimalInt(){}
    BigDecimalInt(string num)
    {
        setNumber(num);
    }
    string getnum(){
        return number;
    }
};
//________________________________________________
class BigReal{
private:
    string rn;
    char sign;
    bool checkvalid_realnumber(string number);
public:
    BigReal () : rn("0.0"){}; // Default constructor
    BigReal (string realNumber);
    BigReal (double realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment
    string getnum()
    {
        return rn;
    }
};


#endif //BIGDECIMALINT_BIGDECIMALINTCLASS_H
