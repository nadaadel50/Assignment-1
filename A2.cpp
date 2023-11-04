#include <bits/stdc++.h>
using namespace std;
#include "A2_Task2_S2.h"

BigReal::BigReal() {
    integer='0';
    fraction='0';
    sign='+';
    intSize=0;
    fractionSize=0;
    firstZero = false;
    addSub = true;
}
BigReal::BigReal(string real) {
    addSub = true;
    firstZero = false;
    if(real[0]=='+'||real[0]=='-') {
        for (int i = 1; i < real.size(); ++i) {
            if(!isdigit(real[i])&&real[i]!='.'){
                real[i]='0';
                firstZero = true;
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
            firstZero = true;
            integer=real;
            fraction="0";
        }

        else if(real[0]=='-'){  //-11.11
            sign='-';
            real[0]='0';
            firstZero = true;
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
            firstZero = true;
            integer=real.substr(0,real.find('.'));
            fraction=real.substr(integer.size()+1,real.size()-1);
        }

        else if(real[0]=='-'){  //-11.11
            sign='-';
            real[0]='0';
            firstZero = true;
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
    BigNumber=sign+integer+'.'+fraction;
}

bool BigReal::operator==(BigReal oo2) {
    if(intSize!=oo2.intSize||fractionSize!=oo2.fractionSize){
        if(intSize!=oo2.intSize){
            if(oo2.intSize<intSize){
                for (int i = 0; i < intSize-oo2.intSize; ++i) {
                    oo2.integer="0"+oo2.integer;
                }
            }
            else if(oo2.intSize>intSize){
                for (int i = 0; i < oo2.intSize-intSize; ++i) {
                    integer="0"+integer;
                }
            }
            oo2.intSize=intSize;
        }

        if(fractionSize!=oo2.fractionSize){
            if(fractionSize>oo2.fractionSize){
                for (int i = 0; i < fractionSize-oo2.fractionSize; ++i) {
                    oo2.fraction=oo2.fraction+"0";
                }
            }
            else if (fractionSize<oo2.fractionSize) {
                for (int i = 0; i < oo2.fractionSize - fractionSize; ++i) {
                    fraction = fraction + "0";
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

int BigReal::operator<(BigReal oo2) {
    if(sign==oo2.sign&&sign=='+'){
        if(integer<oo2.integer||fraction<oo2.fraction){
            return 1;
        }
        else{
            return 2;
        }
    }

    else if(sign==oo2.sign&&sign=='-'){
        if(integer<oo2.integer||fraction<oo2.fraction){
            return 2;
        }
        else{
            return 1;
        }
    }
    else if(sign=='-'&&oo2.sign=='+'){
        return 1;
    }
    else if(sign=='+'&&oo2.sign=='-'){
        return 2;
    }

}

void BigReal::addition(BigReal& other){
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
        // Subtraction
        addSub = false;
    }

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

    if(addSub){
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
        if(firstZero){
            for(int i = 1; i < (result.size()-decimalPosition); i++){
                cout << result[i];
            }
            cout << ".";
            for(int i = (result.size() - decimalPosition); i < result.size() ; i++){
                cout << result[i];
            }
        }
        else{
            for(int i = 0; i < (result.size()-decimalPosition); i++){
                cout << result[i];
            }
            cout << ".";
            for(int i = (result.size() - decimalPosition); i < result.size() ; i++){
                cout << result[i];
            }
        }
    }
    else{
        cout << "Subtract";
    }
    }



void BigReal::printf() {
    cout<<BigNumber<<"-->";
    cout<<integer<<" "<<fraction<<" ";
    cout<<"\n";
}

