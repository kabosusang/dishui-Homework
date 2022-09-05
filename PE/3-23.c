#include <windows.h>
#include <stdio.h>
typedef int (_stdcall *Lplus)(int,int);
typedef int (_stdcall *Lpsub)(int,int);
typedef int (_stdcall *LpMul)(int,int);
typedef int (_stdcall *Lpmiv)(int,int);






int main()
{
    Lplus   Myplus;
    Lpsub   Mypsub;
    LpMul   MypMul;
    Lpmiv   Mypmiv;

    HINSTANCE hmoudle = LoadLibrary("3_24.dll");

    printf("%x\n",hmoudle);
    printf("%d",GetLastError());
    /*Myplus = GetModuleHandle(hmoudle,  "_plus@8"); //因为_stdcall是内平栈 @8的意思是自身平栈8个字节
    Mypsub = GetModuleHandle(hmoudle,  "_Sub@8"); 
    MypMul = GetModuleHandle(hmoudle,  "_Mul@8"); 
    Mypmiv = GetModuleHandle(hmoudle,  "_Div@8"); */

   // printf("Plus后的值:%d",Myplus(4,2));
   
}