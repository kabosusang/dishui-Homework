#include "3-16.h"
#define F_PATH1 "C:/Windows/System32/notepad.exe"

int main()
{
    LPVOID FPOINT=ReadPEFile(F_PATH1);
   //FileBuff=ReadFileBuff(FPOINT);
   LPVOID Image = ChangeImageBuff(FPOINT);


for (size_t i = 0; i < 0x2c4005a4d/sizeof(long long); i++)
{
   
     printf("%x\t",*(long long *)Image);
    (long long *)Image++;
    Sleep(50);
}
    return 0;
}
