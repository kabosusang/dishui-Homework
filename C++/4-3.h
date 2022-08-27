#include<stdio.h>
#include<Windows.h>
class DateInfo
{
public:

DateInfo(int year,int month,int day);
DateInfo();
void SetDay(int day);
int GetDay();
void SetYear(int year);
int GetYear();
void SetMonth(int month);
int GetMonth();

private:
   int year;
   int month;
   int day;
};

class TimeInfo:DateInfo
{
public:
TimeInfo();

private:
char hour;
char minute;
char second;

};


class Mystring
{
 public:       
    Mystring(int size);
    Mystring();
    ~Mystring();
    void SetString(char * String);
    void PrintString();
    int Size();
    void AppendString(char * strings);

private:
    void* GivAddree;

};