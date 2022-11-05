#include "BigDecimalIntClass.h"

// regex function that checks the validation of the input.
bool BigDecimalInt :: checkValidInput(string input)
{
    regex validInput("[-+]?[0-9]+");
    return regex_match(input, validInput);
}

// constructor that takes a string as an input.
void BigDecimalInt :: setNumber(string num)
{
    bool validNumber = checkValidInput(num);
    if(validNumber)
    {
        number = num;
        if(number[0] == '+')
        {
            number.erase(0,1);
            sign = '+';
        }
        else if (number[0] == '-')
        {
            number.erase(0,1);
            sign = '-';
        }
        else
        {
            sign = '+';
        }
    }
    else
    {
        cout << "Invalid" << "\n";
        exit(1);
    }
}

// operator < overloading function.
bool BigDecimalInt :: operator < (const BigDecimalInt& anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(sign == '-' && anotherDec.sign == '+')
    {
        return true;
    }
    else if(sign == '+' && anotherDec.sign == '-')
    {
        return false;
    }
    else if(sign == '+' && anotherDec.sign == '+')
    {
        return comp1 < comp2;
    }
    else
    {
        return comp1 > comp2;
    }
}

// operator > overloading function.
bool BigDecimalInt :: operator > (const BigDecimalInt &anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(sign == '-' && anotherDec.sign == '+')
    {
        return false;
    }
    else if(sign == '+' && anotherDec.sign == '-')
    {
        return true;
    }
    else if(sign == '+' && anotherDec.sign == '+')
    {
        return comp1 > comp2;
    }
    else
    {
        return comp1 < comp2;
    }
}

// operator == overloading function.
bool BigDecimalInt :: operator == (const BigDecimalInt anotherDec)
{
    if (sign == anotherDec.sign && number == anotherDec.number)
    {
        return true;

    }
    else
    {
        return false;
    }
}

// operator = overloading function.
BigDecimalInt& BigDecimalInt :: operator = (BigDecimalInt anotherDec)
{
    sign = anotherDec.sign;
    number = anotherDec.number;
    return *this;
}

//addition implementation.
string addition(string num1,string num2)
{
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
    int carry = 0;
    while (it1 != num1.rend())
    {
        int twoDigitsSum;
        carry = 0;
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
        if (twoDigitsSum >= 10)
        {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
        it1++;
        it2++;
    }
    if (carry)
    {
        res = char((carry) + '0') + res;
    }
    return res;
}

//subtraction implementation
string subtraction(string num1,string num2){
    deque<long long>d;
    string res;

    for (long long i = num1.length() - 1; i >= 0; i--)
    {
        if (num1[i] < num2[i])
        {
            num1[i] = char (((num1[i] - '0') + 10) + '0');
            num1[i - 1] = char (((num1[i - 1] - '0') - 1) + '0');
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
        else
        {
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
    }

    for (auto i : d)
    {
        res += to_string(i);
    }
    return res;
}

// // operator + overloading function.
BigDecimalInt BigDecimalInt :: operator + (BigDecimalInt number2)
{
    BigDecimalInt result;
    char signNumber1 = sign, signNumber2 = number2.sign;
    string num1 = number, num2 = number2.number;
    BigDecimalInt number1 = *this;

    while (num1.length() < num2.length()){
        num1 = '0' + num1;
    }
    while (num2.length() < num1.length()){
        num2 = '0' + num2;
    }

    if (signNumber1 == signNumber2){
        result.sign = signNumber1;
        result.number = addition(num1,num2);

    }else{

        if(number1.sign=='-')
        {
            number1.sign = '+';
            result = (number2-number1);
        }
        else{
            number2.sign = '+';
            result = (number1-number2);
        }
    }
    return result;
}

// operator - overloading function.
BigDecimalInt BigDecimalInt :: operator - (BigDecimalInt anotherDec)
{
    BigDecimalInt obj;
    deque<long long> d;
    string strmin = "", res = "";
    string num1 = number, num2 = anotherDec.number;
    char sign1 = sign, sign2 = anotherDec.sign;

    if (number.length() > anotherDec.number.length())
    {
        for (long long i = 0; i < number.length() - anotherDec.number.length(); i++)
        {
            strmin += '0';
        }
        strmin += anotherDec.number;
        num2 = strmin;
    }
    else if (number.length() < anotherDec.number.length())
    {
        for (long long i = 0; i < anotherDec.number.length() - number.length(); i++)
        {
            strmin += '0';
        }
        strmin += number;
        num1 = strmin;
    }

    bool ok = false, is_determined = false;
    if (num1 < num2)
    {
        swap(num1, num2);
        swap(sign1, sign2);
        ok = true;
    }

    if (sign1 == sign2 )
    {
        res = subtraction(num1,num2);

        if(sign1=='-')ok = !ok;
    }
    else
    {
        res = addition(num1,num2);
        if(sign == '-')
        {
            obj.sign = '-';
            is_determined = true;
        }
        else
        {
            obj.sign = '+';
            is_determined = true;
        }

    }

    bool right = false;
    for (long long i = 0; i < res.length(); i++)
    {
        if (res[i] != '-' && res[i] != '0')
        {
            right = true;
        }
        if (!right && res[i] == '0')
        {
            res.erase(i, 1);
            i--;
        }
    }

    if(res.empty()) res = "0";
    if (!is_determined && (ok))
    {
        obj.sign = '-';
    }
    else if(!is_determined)
    {
        obj.sign = '+';
    }

    obj.number=res;
    return obj;
}

// function to return the size of number.
int BigDecimalInt :: size()
{
    return number.size();
}

// function returns the sign.
int BigDecimalInt :: Sign()
{
    if (sign == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// function to push a character.
void BigDecimalInt ::push_back(char ch)
{
    number.push_back(ch);
}

// function to push a character in the front.
void BigDecimalInt ::push_front(char ch)
{
    string temp;
    temp = ch + number;
    number = temp;
}

// operator << overloading function.
ostream &operator << (ostream &out, BigDecimalInt num)
{
    if(num.sign == '+')
    {
        out << num.number ;
    }
    else
    {
        if(num.number == "0")
        {
            out << num.number ;
        }
        else
        {
            out << num.sign << num.number ;
        }
    }
    return out;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            // Checking input
bool BigReal::checkvalid_realnumber(string number) {
    regex valid_input("[-+]?[0-9]+[.][0-9]+");
    return regex_match(number, valid_input);
}
//______________________________________________________
                            // Declaring numbers
BigReal::BigReal(string realNumber){
    bool valid_realnumber = checkvalid_realnumber(realNumber);
    if (valid_realnumber) {
        rn = realNumber;
        if (rn[0] == '+')
        {
            rn.erase(0 , 1);
            sign = '+';
        }
        else if (rn[0] == '-')
        {
            rn.erase(0 , 1);
            sign = '-';
        }
        else
        {
            sign = '+';
        }
    }
    else
    {
        cout << "Invalid input";
    }
}
//_____________________________________________________
                    //Assinment Operator
BigReal &BigReal::operator=(BigReal &other) {
    sign = other.sign;
    rn = other.rn;
    return *this;
}
//______________________________________________________
BigReal::BigReal(const BigReal &other) {
    sign = other.sign;
    rn = other.rn;
}
//______________________________________________________
BigReal::BigReal(double realNumber) {
    rn = to_string(realNumber);
    cout << rn;
}
//______________________________________________________
BigReal::BigReal(BigReal &&other) {
    this->rn = other.rn;
    other.rn = nullptr;
}
//______________________________________________________
BigReal &BigReal::operator=(BigReal &&other) {
        this -> rn = other.rn;
        other.rn = nullptr;
    return *this;
}
//______________________________________________________
BigReal::BigReal(BigDecimalInt bigInteger) {
        sign = bigInteger.Sign();
        rn = bigInteger.getnum();
}
//______________________________________________________
string add(string num1,string num2) {
    int pos = num1.find("."), pos2 = num2.find(".");
    num1.erase(remove(num1.begin(), num1.end(),'.'),num1.end());
    num2.erase(remove(num2.begin(), num2.end(),'.'),num2.end());
    const int chk =num1.length() , chk2 =num2.length();
    int fchk;
    if (chk>chk2)
        fchk = chk;
    else
        fchk = chk2;

    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
    int carry = 0;

    while (it1 != num1.rend())
    {
        int twoDigitsSum;
        carry = 0;
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));

        if (twoDigitsSum >= 10)
        {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
        it1++;
        it2++;
    }
    if (carry)
    {
        res = char((carry) + '0') + res;
    }
        if (res.length() > fchk)
            pos++;
        res.insert(pos, ".");
        return res;


    }


//___________________________________________________________
string sub(string num1,string num2){
    int pos = num1.find("."), pos2 = num2.find(".");
    num1.erase(remove(num1.begin(), num1.end(),'.'),num1.end());
    num2.erase(remove(num2.begin(), num2.end(),'.'),num2.end());
    const int chk =num1.length() , chk2 =num2.length();
    int fchk; //this var is ref for "." after the addition to know "." position
    if (chk>chk2)
        fchk = chk;
    else
        fchk = chk2;
    deque<long long>d;
    string res;

    for (long long i = num1.length() - 1; i >= 0; i--)
    {
        if (num1[i] < num2[i])
        {
            num1[i] = char (((num1[i] - '0') + 10) + '0');
            num1[i - 1] = char (((num1[i - 1] - '0') - 1) + '0');
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
        else
        {
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
    }

    for (auto i : d)
    {
        res += to_string(i);
    }
    if (res.length() > fchk)
        pos++;
    res.insert(pos, ".");
    return res;
}
//____________________________________________________________
    BigReal BigReal::operator+(BigReal &other) {
        BigReal rs;
        char sigNum1 = sign, sigNum2 = other.sign;
        string num1 = rn, num2 = other.rn;
        BigReal number1 = *this;
        int pos = num1.find("."), pos2 = num2.find(".");

          while (pos != pos2) {

            if (pos == pos2) {
                break;
            } else if (pos < pos2) {


                num1 = '0' + num1;
                pos++;
            } else if (pos > pos2) {
                num2 = '0' + num2;
                pos2++;
            } }

            while (num1.length() != num2.length()){
              if (num1.length() > num2.length()) {
                   num2 = num2 + '0';
              }
                 else if (num1.length() < num2.length()) {
                num1 = num1 + '0';
                }
         }
        if (sigNum1 == sigNum2) {
            rs.sign = sigNum1;
            rs.rn = add(num1, num2);
        }
    return rs;
    }
    //-------------------------------------------------------------
    BigReal BigReal :: operator - (BigReal & other)
    {
        BigReal obj;
        deque<long long> d;
        string strmin = "", rs = "";
        string num1 = rn, num2 = other.rn;
        char sign1 = sign, sign2 = other.sign;
        long long  pos = num1.find("."), pos2 = num2.find(".");

        while (pos != pos2) {

            if (pos == pos2) {
                break;
            } else if (pos < pos2) {


                num1 = '0' + num1;
                pos++;
            } else if (pos > pos2) {
                num2 = '0' + num2;
                pos2++;
            } }

        while (num1.length() != num2.length()){
            if (num1.length() > num2.length()) {
                num2 = num2 + '0';
            }
            else if (num1.length() < num2.length()) {
                num1 = num1 + '0';
            }
        }

        bool ok = false, is_determined = false;
        if (num1 < num2)
        {
            swap(num1, num2);
            swap(sign1, sign2);
            ok = true;
        }

        if (sign1 == sign2 )
        {
            rs = sub(num1,num2);

            if(sign1=='-')ok = !ok;
        }
        else
        {
            rs = addition(num1,num2);
            if(sign == '-')
            {
                obj.sign = '-';
                is_determined = true;
            }
            else
            {
                obj.sign = '+';
                is_determined = true;
            }

        }

        bool right = false;
        for (long long i = 0; i < rs.length(); i++)
        {
            if (rs[i] != '-' && rs[i] != '0')
            {
                right = true;
            }
            if (!right && rs[i] == '0')
            {
                rs.erase(i, 1);
                i--;
            }
        }

        if(rs.empty()) rs = "0";
        if (!is_determined && (ok))
        {
            obj.sign = '-';
        }
        else if(!is_determined)
        {
            obj.sign = '+';
        }

        obj.rn=rs;
        return obj;


    }


//------------------------------------------

/* function that add zeros left to the fixed number and right to the
 * fraction nubmers to make the length the same to compare correctly */
void BigReal::improve(BigReal anotherReal, string* fx1, string* fx2, string* fr1, string* fr2) {
    string zeros;
    int pos1, pos2;
    long long len1, len2;

    // set the len1, len2 to the whole number length
    len1 = rn.length();
    len2 = anotherReal.rn.length();

    // find the index of the dot
    pos1 = rn.find('.');
    pos2 = anotherReal.rn.find('.');

    // set values of num1
    *fx1 = rn.substr(0, pos1);
    *fr1 = rn.substr(pos1 + 1, abs((int) len1 - (pos1 + 1)));

    // set values of num2
    *fx2 = anotherReal.rn.substr(0, pos2);
    *fr2 = anotherReal.rn.substr(pos2 + 1, abs((int) len2 - (pos2 + 1)));


    // change len1, len2 values to fixed
    len1 = fx1->length();
    len2 = fx2->length();

    // add zeros to the fixed numbers
    while(len1 < len2) {
        zeros += "0";
        len1++;
    }
    zeros += *fx1;
    *fx1 = zeros;

    // empty the var to use it again
    zeros = "";

    while(len2 < len1) {
        zeros += "0";
        len2++;
    }
    zeros += *fx2;
    *fx2 = zeros;

    // empty the var to use it again
    zeros = "";

    //--------------------------------------

    // change len1, len2 values to fraction
    len1 = fr1->length();
    len2 = fr2->length();

    // add zeros to the fraction numbers
    while(len1 < len2) {
        zeros += '0';
        len1++;
    }
    *fr1 += zeros;

    // empty the var to use it again
    zeros = "";

    while(len2 < len1) {
        zeros += '0';
        len2++;
    }
    *fr2 += zeros;


}



//--------------------------------------------------
bool BigReal::operator<(BigReal anotherReal) {
    string fixed1, frac1, fixed2, frac2;

    /* function that add zeros left to the fixed number and right to the
     * fraction nubmers to make the length the same to compare correctly */
    improve(anotherReal, &fixed1, &fixed2, &frac1, &frac2);

    // comparison
    if (sign == '+' && anotherReal.sign == '-') {
        return false;
    } else if (sign == '-' && anotherReal.sign == '+') {
        return true;
    } else if (sign == '+' && anotherReal.sign == '+') {

        if( (fixed1 < fixed2) || (fixed1 == fixed2 && frac1 < frac2) ) {
            return true;
        }

    } else {
        if((fixed1 > fixed2) || (fixed1 == fixed2 && frac1 > frac2)) {
            return true;
        }
    }

    return false;
}

//______________________________________________________

bool BigReal::operator>(BigReal anotherReal) {
    string fixed1, frac1, fixed2, frac2;

    improve(anotherReal, &fixed1, &fixed2, &frac1, &frac2);

    // comparison
    if (sign == '+' && anotherReal.sign == '-') {
        return true;
    } else if (sign == '-' && anotherReal.sign == '+') {
        return false;
    } else if (sign == '+' && anotherReal.sign == '+') {

        if( (fixed1 > fixed2) || (fixed1 == fixed2 && frac1 > frac2) ) {
            return true;
        }

    } else {
        if((fixed1 < fixed2) || (fixed1 == fixed2 && frac1 < frac2)) {
            return true;
        }
    }
    return false;
}

bool BigReal::operator== (BigReal anotherReal){
    string fixed1, frac1, fixed2, frac2;

    improve(anotherReal, &fixed1, &fixed2, &frac1, &frac2);

    // comparison
    if(sign == anotherReal.sign) {
        if(fixed1 == fixed2 && frac1 == frac2) {
            return true;
        }
    }
    return false;

}

//-------------------------------------------
int BigReal::Sign() {
    if(sign == '+') {
        return 1;
    } else {
        return 0;
    }

}

//-------------------------------------------
int BigReal::size() {
    return rn.length();

}

//-------------------------------------------
ostream& operator << (ostream& out, BigReal num) {
    if(num.sign == '+')
    {
        out << num.rn ;
    } else {
        if(num.rn == "0") {
            out << num.rn ;
        } else {
            out << num.sign << num.rn ;
        }
    }

    return out;
}


//------------------------------------------------
istream& operator >> (istream& out, BigReal &num){
    bool isValid; string temp;

    out >> temp;
    isValid =  BigReal::checkvalid_realnumber(temp);

    if(isValid) {
        num.init(temp);

        if (num.rn[0] == '-') {
            num.sign = '-';
            num.rn.erase(0, 1);
        } else if (num.rn[0] == '+') {
            num.sign = '+';
            num.rn.erase(0, 1);
        } else {
            num.sign = '+';
        }
    } else {
        cout << "invalid real number";
        exit(0);
    }


    return out;

}




