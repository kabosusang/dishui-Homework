#include"4-3.h"

DateInfo::DateInfo()
{
    this->year = 2015;
    this->month = 4;
    this->day = 2;
}

void DateInfo::SetDay(int day)
{
    this->day = day;
}

int DateInfo::GetDay()
{
    return this->day;
}

void DateInfo::SetYear(int year)
{
    this->year = year;
}

int DateInfo::GetYear()
{
    return this->year;
}

void DateInfo::SetMonth(int month)
{
    this->month = month;
}

int DateInfo::GetMonth()
{
    return this->month;
}

/***********************************************************/
TimeInfo::TimeInfo()
{
   hour=19;
   minute=00;
   second=19;
}
/***********************************************************/

Mystring::Mystring(int size)\
{
    this->GivAddree= malloc(size);
}

Mystring::Mystring()
{
    this->GivAddree = malloc(1024);
}

Mystring::~Mystring()
{
    free(GivAddree);
}

void Mystring::SetString(char * String)
{
    char * c =(char *)GivAddree;

      for (size_t i = 0; i < strlen(String)+1; i++)
      {
         *c = *((char *) String+i);
         c++;
      }
}

void Mystring::PrintString()
{
    printf("%s\n",GivAddree);
}

int Mystring::Size()
{
    return strlen((char *)GivAddree);
}

void Mystring::AppendString(char * strings)
{
    char * c =(char *)GivAddree+Size();

      for (size_t i = 0; i < strlen(strings)+1; i++)
      {
         *c = *((char *) strings+i);
         c++;
      }
}


int main()
{
TimeInfo b;

Mystring INstring(1000);

INstring.SetString("Hello Word");
INstring.PrintString();
INstring.AppendString("KA_bo");
INstring.PrintString();

}