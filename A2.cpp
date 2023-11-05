#include <bits/stdc++.h>
using namespace std;
#include "The_BigReal.h"

BigReal::BigReal() {
    integer='0';
    fraction='0';
    sign='+';
    intSize=0;
    fractionSize=0;
    addsub = true;
}
// the is invalid function  is in the constructor that if the number is not in form ("[+-]?\\d*.?\\d+") or
// is not in form ("[+-]?\\d+")that the number is invalid otherwise the number is valid
BigReal::BigReal(string real) {
    addsub = true;
    if(real[0]=='+'||real[0]=='-') {
        for (int i = 1; i < real.size(); ++i) {
            if(!isdigit(real[i])&&real[i]!='.'){
                real[i]='0';
            }
            else{
                break;
            }
        }
    }
    if(regex_match(real,regex("[+-]?\\d+"))){
        if(real[0]=='+'){  //+11
            sign='+';
            real[0]='0';
            integer=real;
            fraction="0";
        }

        else if(real[0]=='-'){  //-11.11
            sign='-';
            real[0]='0';
            integer=real;
            fraction="0";
        }

        else{      //11.11
            sign='+';
            integer=real;
            fraction="0";
        }
    }
    else if(regex_match(real,regex("[+-]?\\d*.?\\d+"))){
        if(real[0]=='+'){  //+11.11
            sign='+';
            real[0]='0';
            integer=real.substr(0,real.find('.'));
            fraction=real.substr(integer.size()+1,real.size()-1);
        }

        else if(real[0]=='-'){  //-11.11
            sign='-';
            real[0]='0';
            integer=real.substr(0,real.find('.'));
            fraction=real.substr(integer.size()+1,real.size()-1);


        }
        else{      //11.11
            sign='+';
            if(real[0]=='.'){
                integer="0";
                fraction=real.substr(integer.size(),real.size()-1);

            }
            else{
                integer=real.substr(0,real.find('.'));
                fraction=real.substr(integer.size()+1,real.size()-1);
            }


        }
    }

    else{
        cout<<" the big number is invalid.\n";
        integer="0";
        fraction="0";
    }

    intSize=integer.size(); fractionSize=fraction.size();
    cout<<"The integer size is:"<<intSize<<" , the fraction size is:"<<fractionSize<<"\n";
    BigNumber=sign+integer+'.'+fraction;
}
//------------------------------------------------------------------------------
BigReal &BigReal::operator=(BigReal &other) {
    sign = other.sign;
    integer = other.integer;
    fraction = other.fraction;
}

// copy constructor
BigReal::BigReal(const BigReal &other) {
    sign = other.sign;
    integer = other.integer;
    fraction = other.fraction;
}
//---------------------------------------------------------------------------
// compare
/* first compiler check if size of integer is similar in 2 objects and check if size of fraction is similar in 2 objects
 then if integer object1==integer object2 and if fraction object1==fraction object2 and the sign in
 object1==sign in equal 2--> the 2 objects are equal */
bool BigReal::operator==(BigReal oo2) {
    if(intSize!=oo2.intSize||fractionSize!=oo2.fractionSize){
        if(intSize!=oo2.intSize){
            if(oo2.intSize<intSize){
                for (int i = 0; i < intSize-oo2.intSize; ++i) {
                    oo2.integer="0"+oo2.integer;
                    oo2.intSize++;
                }

            }
            else if(oo2.intSize>intSize){
                for (int i = 0; i < oo2.intSize-intSize; ++i) {
                    integer="0"+integer;
                    intSize++;
                }
            }
            intSize=oo2.intSize;

        }

        if(fractionSize!=oo2.fractionSize){
            if(fractionSize>oo2.fractionSize){
                for (int i = 0; i < fractionSize-oo2.fractionSize; ++i) {
                    oo2.fraction=oo2.fraction+"0";
                    oo2.fractionSize++;
                }
            }
            else if (fractionSize<oo2.fractionSize) {
                for (int i = 0; i < oo2.fractionSize - fractionSize; ++i) {
                    fraction = fraction + "0";
                    fractionSize++;
                }
            }
            oo2.fractionSize=fractionSize;
        }
    }

    if(sign==oo2.sign){
        if(intSize==oo2.intSize&&fractionSize==oo2.fractionSize){
            if(integer==oo2.integer&&fraction==oo2.fraction){
                return true;
            }
            else{
                return false;
            }

        }
    }

    else{
        return false;
    }


}

/*  operator <
  then if integer object1<integer object2 or if fraction object1<fraction object2 and the sign in
  object1==sign in object2 =='+'--> the object2 is greater
  if the sign in object1==sign in object2 =='-'and integer object1>integer object2 or if fraction object1>fraction object2
  --> the object2 is greater
  if the sign in object2 is'+' --> the object2 is greater*/
bool BigReal::operator<(BigReal oo2) {
    if(sign==oo2.sign&&sign=='+'){
        if(integer<oo2.integer||fraction<oo2.fraction){
            return true;
        }
        else{
            return false;
        }
    }

    else if(sign==oo2.sign&&sign=='-'){
        if(integer>oo2.integer||fraction>oo2.fraction){
            return true;
        }
        else{
            return false;
        }
    }
    else if(sign=='-'&&oo2.sign=='+'){
        return true;
    }
    else if(sign=='+'&&oo2.sign=='-'){
        return false;
    }

}
/*   operator >
  then if integer object1>integer object2 or if fraction object1>fraction object2 and the sign in
  object1==sign in object2 =='+'--> the object1 is greater
  if the sign in object1==sign in object2 =='-'and integer object1<integer object2 or if fraction object1<fraction object2
  --> the object1 is greater
  if the sign in object1 is'+' --> the object1 is greater*/
bool BigReal::operator>(BigReal oo2) {
    if(sign==oo2.sign&&sign=='+'){
        if(integer>oo2.integer||fraction>oo2.fraction){
            return true;
        }
        else{
            return false;
        }
    }

    else if(sign==oo2.sign&&sign=='-'){
        if(integer<oo2.integer||fraction<oo2.fraction){
            return true;
        }
        else{
            return false;
        }
    }
    else if(sign=='-'&&oo2.sign=='+'){
        return false;
    }
    else if(sign=='+'&&oo2.sign=='-'){
        return true;
    }
}


//---------------------------------------------------------------------
void BigReal::add(BigReal& other){
    string result = "";
    char result_sign;
    int carry = 0;
    if(sign == '+' && other.sign == '+'){
        result_sign = '+';
    }
    else if(sign == '-' && other.sign == '-'){
        result_sign = '-';
    }
    else{
        addsub = false;
        if(sign=='+'&&other.sign=='-' &&integer!=other.integer){
            other.sign='+';
            subtract(other);
        }
        else if(sign=='-'&&other.sign=='+'  &&integer!=other.integer){
            other.sign='-';
            subtract(other);

        }
        else if((sign=='-'&& other.sign=='+'  &&integer==other.integer) || ((sign=='+'&&other.sign=='-'  && integer==other.integer)) ) {
            result+="0.0";
            cout<<result<<endl;
        }

    }
    if(addsub){
        // Firstly we need to make the number of digits equal in both a and b
        // padding with zero's
        if(fraction.size() != other.fraction.size()){
            if(fraction.size() > other.fraction.size()){
                int dif = fraction.size() - other.fraction.size();
                while(dif--){
                    other.fraction = other.fraction +  "0";
                }
            }
            else{
                int dif = other.fraction.size() - fraction.size();
                while(dif--){
                    fraction = fraction + "0";
                }
            }
        }

        // Adding the fraction , integer parts
        // Adding the fraction part
        int fractionSize_a = fraction.size();
        int fractionSize_b = other.fraction.size();
        int i = fractionSize_a - 1;
        int j = fractionSize_b - 1;

        int sum;
        while (i >= 0 || j >= 0) {
            sum = carry;
            if (i >= 0)
                sum += (fraction[i] - '0');
            if (j >= 0)
                sum += (other.fraction[j] - '0');
            carry = sum / 10;
            sum %= 10;
            result = to_string(sum) + result;
            i--; j--;
        }
        int decimalPosition;
        decimalPosition = result.size();

        // Adding the integer part
        int integerSize_a = integer.size();
        int integerSize_b = other.integer.size();
        i = integerSize_a - 1;
        j = integerSize_b - 1;
        while (i >= 0 || j >= 0) {
            sum = carry;
            if (i >= 0)
                sum += (integer[i] - '0');
            if (j >= 0)
                sum += (other.integer[j] - '0');
            carry = sum / 10;
            sum %= 10; // It gives the current digit of result
            result = to_string(sum) + result;
            i--; j--;
        }

        if (carry > 0) {
            result = to_string(carry) + result;
        }



        // Printing result of adding
        cout << "Result: ";
        cout << result_sign;

        for(int i = 0; i < (result.size()-decimalPosition); i++){
            cout << result[i];
        }
        cout << ".";
        for(int i = (result.size() - decimalPosition); i < result.size() ; i++){
            cout << result[i];
        }

        cout << endl;

    }
}


//-----------------------------------------------------------------------------------
/*
  We will subtract digit by digit but in the beginning we will make reverse to the integer ,fraction and
  the other.integer and the other.fraction because we want to make for loop from the end of the string to the
  right but the reverse is easier.
  Then we will check the sign and if integer>other.integer or the opposite ,so all this will control if
  we will subtract the digit1 of the integer from the digit 2 of the other.integer  or opposite
  and the difference will subtract from carry and if the number <0 we will add 10 on it;
*/

string BigReal::subtract(BigReal &other)
{
    string thisInt = integer;
    string fraction1 = fraction;
    string integer2 = other.integer;
    string fraction2 = other.fraction;
    int thisIntLength = thisInt.length();
    int integer2Length = integer2.length();
    while (thisIntLength < integer2Length) {
        thisInt = "0" + thisInt;   //padding
        integer="0"+integer;
        thisIntLength++;
        intSize++;
    }
    while (integer2Length < thisIntLength) {
        integer2 = "0" + integer2;
        other.integer="0"+other.integer;
        integer2Length++;

    }
    int fraction1Length = fraction1.length();
    int fraction2Length = fraction2.length();
    while (fraction1Length < fraction2Length) {
        fraction+="0";
        fraction1 += "0";
        fraction1Length++;
        fractionSize++;
    }
    while (fraction2Length < fraction1Length) {
        other.fraction+="0";
        fraction2 += "0";
        fraction2Length++;
    }
    reverse(thisInt.begin(), thisInt.end());
    reverse(integer2.begin(), integer2.end());
    reverse(fraction1.begin(), fraction1.end());
    reverse(fraction2.begin(), fraction2.end());
    string resultInt;
    string resultFrac;
    string result;
    int carry = 0;
    //-------------------------------------------------------------------
    if(sign==other.sign&&sign=='+'){
        if(integer>other.integer){
            for (int i = 0; i < fraction1.length(); ++i) {
                int d1 = fraction1[i] - '0';
                int d2 = fraction2[i] - '0';
                int diff = d1 - d2 - carry; // <----
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                resultFrac += to_string(diff);
            }

            for (int i = 0; i < thisInt.length(); ++i) {
                int d1 = (thisInt[i] - '0');
                int d2 = integer2[i] - '0';

                int diff = d1 - d2-carry ; //  <-----
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                resultInt += to_string(diff);
            }
            reverse(resultInt.begin(), resultInt.end());
            reverse(resultFrac.begin(), resultFrac.end());
            if (resultFrac.empty())
                result = resultInt;
            else
                result = resultInt + '.' + resultFrac;
            cout << sign;
            cout<< result;
        }

            //------------------------------------

        else if(integer<other.integer){
            sign='-';
            for (int i = 0; i < fraction1.length(); ++i) {
                int d1 = fraction1[i] - '0';
                int d2 = fraction2[i] - '0';
                int diff = d2 - d1 - carry;  //  <-----
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                resultFrac += to_string(diff);
            }

            for (int i = 0; i < thisInt.length(); ++i) {
                int d1 = (thisInt[i] - '0');
                int d2 = integer2[i] - '0';

                int diff = d2 - d1-carry ;   //  <-----
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
                resultInt += to_string(diff);
            }
            reverse(resultInt.begin(), resultInt.end());
            reverse(resultFrac.begin(), resultFrac.end());
            if (resultFrac.empty())
                result = resultInt;
            else
                result = resultInt + '.' + resultFrac;
            cout << sign;
            cout<< result;

        }
    }

        //--------------------- negative---------------------------

    else if(sign==other.sign&&sign=='-'){
        if(integer>other.integer){
            sign='-';
            for (int i = 0; i < fraction1.length(); ++i) {
                int digit1 = fraction1[i] - '0';
                int digit2 = fraction2[i] - '0';
                int diff = digit1 - digit2 - carry;  //  <-----
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
//                diff=10-diff;
                resultFrac += to_string(diff);
            }

            for (int i = 0; i < thisInt.length(); ++i) {
                int digit1 = (thisInt[i] - '0');
                int digit2 = integer2[i] - '0';

                int diff = digit1 - digit2-carry ;
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
//                diff=10-diff;
                resultInt += to_string(diff);
            }
            reverse(resultInt.begin(), resultInt.end());
            reverse(resultFrac.begin(), resultFrac.end());
            if (resultFrac.empty())
                result = resultInt;
            else
                result = resultInt + '.' + resultFrac;
            cout << sign;
            cout<< result;
        }

            //-------------------------------

        else if(integer<other.integer){
            sign='+';
            for (int i = 0; i < fraction1.length(); ++i) {
                int digit1 = fraction1[i] - '0';
                int digit2 = fraction2[i] - '0';
                int diff = digit2 - digit1 - carry;
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
//                diff=10-diff;
                resultFrac += to_string(diff);
            }

            for (int i = 0; i < thisInt.length(); ++i) {
                int digit1 = (thisInt[i] - '0');
                int digit2 = integer2[i] - '0';

                int diff = digit2 - digit1-carry ;
                if (diff < 0) {
                    diff += 10;
                    carry = 1;
                } else {
                    carry = 0;
                }
//                diff=10-diff;
                resultInt += to_string(diff);
            }
            reverse(resultInt.begin(), resultInt.end());
            reverse(resultFrac.begin(), resultFrac.end());
            if (resultFrac.empty())
                result = resultInt;
            else
                result = resultInt + '.' + resultFrac;
            cout << sign;
            cout<< result;
        }
    }
        //---------------------(-,+)
    else if(sign=='+'&&other.sign=='-'){
        other.sign='+';
        add(other);
    }
    else if(sign=='-'&&other.sign=='+'){
        other.sign='-';
        add(other);
    }

}
//----------------------------------------------------------------------------------------------
void print_num(BigReal x){
    cout<<x.integer<<"."<<x.fraction<<"-->";
    cout <<"the integer is:" <<x.integer << " , the fraction is:"<< x.fraction <<" ";
    cout<<"\n";
}

