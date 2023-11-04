class BigReal{
private:
    string BigNumber,integer,fraction;
    long long intSize,fractionSize ;
    char sign;
    bool firstZero, addSub;
public:

    BigReal();
    BigReal(string real);

    bool operator==(BigReal oo2);


    int operator<(BigReal oo2 );

    void printf();
    void addition(BigReal& other);


};

