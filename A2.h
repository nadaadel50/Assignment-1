class BigReal{
private:
    string BigNumber,integer,fraction;
    long long intSize,fractionSize ;
    char sign;
    bool firstZero;
public:

    BigReal();
    BigReal(string real);

    bool operator==(BigReal oo2);


    int operator<(BigReal oo2 );

    void printf();
    void add(BigReal& other);


};
