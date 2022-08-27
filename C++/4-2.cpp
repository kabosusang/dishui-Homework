#include<stdio.h>
#include<Windows.h>
struct DateInfo
{
   int year;
   int month;
   int day;

   DateInfo(int year,int month,int day)
   {
   }
   DateInfo()
   {
      this->year = 2015;
      this->month = 4;
      this->day = 2;
   }
   
   void SetDay(int day)
   {
      this->day = day;
   }

   int GetDay()
   {
      return this->day;
   }
    
    void SetYear(int year)
   {
      this->year = year;
   }

   int GetYear()
   {
      return this->year;
   }

   void SetMonth(int month)
   {
      this->month = month;
   }

   int GetMonth()
   {
      return this->month;
   }
};

struct TimeInfo:DateInfo
{
 char hour;
 char minute;
 char second;

TimeInfo()
{
   hour=19;
   minute=00;
   second=19;
}
};
struct Mystring
{
   void* GivAddree;

   Mystring(int size)
      {
        GivAddree = malloc(size);
      }

   Mystring()
      {
         GivAddree = malloc(1024);
      }

   ~Mystring()
      {
         free(GivAddree);
      }

   void SetString(char * String)
   {
    char * c =(char *)GivAddree;

      for (size_t i = 0; i < strlen(String)+1; i++)
      {
         *c = *((char *) String+i);
         c++;
      }
      
   }

   void  PrintString()
   {
      printf("%s\n",GivAddree);
   }
   
   int Size()
   {
      
      return strlen((char *)GivAddree);
   }

   void AppendString(char * strings)
   {
    char * c =(char *)GivAddree+Size();

      for (size_t i = 0; i < strlen(strings)+1; i++)
      {
         *c = *((char *) strings+i);
         c++;
      }

   }

};



int main()
{
TimeInfo b;

DateInfo* c = &b;
//c->hour; 报错语句 访问不到

TimeInfo* d = &b;

Mystring INstring(1000);

INstring.SetString("Hello Word");
INstring.PrintString();
INstring.AppendString("KA_bo");
INstring.PrintString();


printf("现在的时间是:%d小时\n",d->hour);

}
  



