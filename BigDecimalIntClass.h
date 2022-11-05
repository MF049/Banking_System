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
public:
    static bool checkvalid_realnumber(string number);
    BigReal () : rn("0.0"), sign('+'){}; // Default constructor
    BigReal (string realNumber);
    BigReal (double realNumber);
    BigReal (BigDecimalInt bigInteger);
    BigReal (const BigReal& other); // Copy constructor
    BigReal (BigReal&& other); // Move constructor
    BigReal& operator= (BigReal& other); // Assignment operator
    BigReal& operator= (BigReal&& other); // Move assignment
    // ------
    BigReal operator+ (BigReal& other);
    BigReal operator- (BigReal& other);
    // ------
    bool operator< (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    int size();
    int Sign();
    friend ostream& operator << (ostream& out, BigReal num);
    friend istream& operator >> (istream& out, BigReal &num);
    void improve(BigReal anotherReal, string* fx1, string* fx2, string* fr1, string* fr2);

    // method to initializing object after declare it
    void init(const string& no) {
        rn = no;
    }
    string getnum()
    {
        return rn;
    }
};


#endif //BIGDECIMALINT_BIGDECIMALINTCLASS_H
