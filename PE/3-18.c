#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#define File_Path "C:/Users/37548/Desktop/vscodec/JJunckcode.exe" 
#define CreateFile_Path "C:/Users/37548/Desktop/vscodec/NEWJJunckcode.exe" 
#define MESSBOXADD 0x74531930

char ShellCode[]={

    0x6A,00,0x6A,00,0x6A,00,0x6A,00,0xE8,00,00,00,00,0xE9,00,00,00,00
};

PVOID GetFileBuff( char * FilePath)
{
    FILE* RFile = NULL;
    DWORD64 FizeSize = 0;
    PVOID FileBuff = NULL;

    RFile = fopen(FilePath,"rb");
    if(!RFile)
    {
        printf("读取文件失败\n");
        return 0;
    }
    fseek(RFile,0,SEEK_END);
    FizeSize = ftell(RFile);
    if(!FizeSize)
    {
        printf("读取文件大小失败\n");
        fclose(RFile);
        return 0;
    }
    FileBuff = malloc(FizeSize);
    if(!FileBuff)
    {
        printf("分配空间失败\n");
        fclose(RFile);
        return 0;
    }
    memset(FileBuff,0,FizeSize);//初始化内存
    fseek(RFile,0,SEEK_SET);
     size_t n = fread(FileBuff,FizeSize,1,RFile);
        if(!n)
        {
            printf("存取空间失败\n");
            fclose(RFile);
            free(FileBuff);
            return  NULL;
        }
    fclose(RFile);
    return FileBuff;
}

PVOID FileBuffToImageBuff(PVOID FileBuff)
{
    LPVOID pFileBuffer = FileBuff;//
    PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS 头
	PIMAGE_NT_HEADERS pNTHeader = NULL;//NT头
	PIMAGE_FILE_HEADER pPEHeader = NULL;//标准PE头
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;//可选PE头·
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;//节表
    LPVOID ImagefileMU = NULL;// ImageFile内存

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer; // 赋值DOS头

    pNTHeader = (PIMAGE_NT_HEADERS)((char *)FileBuff+pDosHeader->e_lfanew); // 赋值NT头

    pPEHeader = (PIMAGE_FILE_HEADER)&pNTHeader->FileHeader;

    pOptionHeader =(PIMAGE_OPTIONAL_HEADER32)((char*)pPEHeader+20);

    pSectionHeader = (PIMAGE_SECTION_HEADER)((char *)pOptionHeader+pPEHeader->SizeOfOptionalHeader);

    ImagefileMU = malloc(pOptionHeader->SizeOfImage); //内存中PE文件大小
    if(!ImagefileMU)
    {
        printf("内存大小获取失败\n");
        return 0;
    }
    memset(ImagefileMU,0,pOptionHeader->SizeOfImage); //初始化内存
    memcpy(ImagefileMU,pFileBuffer,pOptionHeader->SizeOfHeaders); //文件头内存复制



   
    for (int i = 0; i < pPEHeader->NumberOfSections; i++)
    {
        PIMAGE_SECTION_HEADER SectionBeginAdd = NULL;
        SectionBeginAdd = pSectionHeader;

        memcpy((char *)ImagefileMU+SectionBeginAdd->VirtualAddress,(char *)pFileBuffer+SectionBeginAdd->PointerToRawData,SectionBeginAdd->SizeOfRawData);

        SectionBeginAdd++;
    } // 复制到IMage内存
    /* 填入代码进入内存区域  修改OEP */
    pDosHeader = (PIMAGE_DOS_HEADER)ImagefileMU; // 用上一个变量重新赋值 DOS头
    printf("文件地址为:%x\n",*(WORD*)ImagefileMU);
    pNTHeader = (PIMAGE_NT_HEADERS)((char *)ImagefileMU+pDosHeader->e_lfanew); // 赋值NT头

    pPEHeader = (PIMAGE_FILE_HEADER)&pNTHeader->FileHeader;

    pOptionHeader =(PIMAGE_OPTIONAL_HEADER32)((char*)pPEHeader+20);

    pSectionHeader = (PIMAGE_SECTION_HEADER)((char *)pOptionHeader+pPEHeader->SizeOfOptionalHeader);
    PIMAGE_SECTION_HEADER pSectionHeader2 = pSectionHeader+1; //获取第二个节表地址

    printf("%x\n",pNTHeader->Signature);
    
    printf("%s\n",pSectionHeader->Name);
    
    printf("内存文件总大小为:%x\n",pOptionHeader->SizeOfImage);

    printf("%x\n",pSectionHeader->VirtualAddress);

    printf("节表个数为:%d\n",pPEHeader->NumberOfSections);
  
    //MESSBOXADD
    if(pSectionHeader2->VirtualAddress-pSectionHeader->VirtualAddress+pSectionHeader->SizeOfRawData > sizeof(ShellCode)) //判断地址空间是否大于Shellcode
    {
        PVOID ADDaddress = NULL;
    
        ADDaddress = (char*)ImagefileMU+pSectionHeader->VirtualAddress+pSectionHeader->SizeOfRawData;
        memset(ADDaddress,0,sizeof(ShellCode));
        memcpy((char*)ADDaddress,ShellCode,sizeof(ShellCode));//存入shellcode
   
        printf("%hhx\n",*((char *)ADDaddress+8));//测试
        //MESSBOXADD-(char)ADDaddress+0xd;   //实际要跳转地址
        //printf("实际要跳转地址:%x",MESSBOXADD-(DWORD)AddAddress1+0xd);

        //(char *)ADDaddress - ImagefileMU; // 偏移
        printf("%x\n",pOptionHeader->ImageBase);
        DWORD CALLaddress = MESSBOXADD-((DWORD)pOptionHeader->ImageBase+(DWORD)ADDaddress-(DWORD)ImagefileMU);
        //ADDaddress+9
        
        printf("CALLaddress:地址是%x\n",&CALLaddress);
        /*for(int j = 0;j<4;j++) // 复制地址转入内存
        {
                char* CUtADD = (char *)&CALLaddress+4-j;
                memset((char *)ADDaddress+9+j,*CUtADD,1);
        }*/
        for (int k = 0; k < sizeof(ShellCode); k++)
        {
            char* o = (char*)ADDaddress;
            printf("%hhx\t",*((char*)ADDaddress+k));
          
        }
        //printf("出错地址:%x\n",*(char*)CALLaddress+9);
    
        //char* ASD = CALLaddress;
        printf("\n%x\n",ADDaddress);
      
        printf("正常截取地址:%x\n",CALLaddress);
        printf("截取的地址:%x\n",(char)CALLaddress);
        //循环赋值地址
        for (int l = 0; l < 4; l++)
        {
        DWORD CUTadd2 = 0;
        CUTadd2 = *((char*)&CALLaddress+l);
        printf("测试读取:%x\n",CUTadd2);
        memset((char*)ADDaddress+9+l,CUTadd2,1); //
        }
        
        //写入 要跳转的地址

        printf("%x\n",pOptionHeader->AddressOfEntryPoint);
        DWORD ENTRYAdd = pOptionHeader->AddressOfEntryPoint;
        for (int l = 0; l < 4; l++)
        {
        DWORD CUTadd3 = 0;
        CUTadd3 = *((char*)&ENTRYAdd+l);
        printf("测试读取:%hhx\n",CUTadd3);
        memset((char*)ADDaddress+14+l,CUTadd3,1); //
        }
       
        printf("最初地址:%x\n",ADDaddress);
        printf("%x\n",ImagefileMU);
        pOptionHeader->AddressOfEntryPoint = (DWORD)((char*)ADDaddress-(char*)ImagefileMU);
    }

    printf("相减为:%x\n",pOptionHeader->AddressOfEntryPoint);
    
    pFileBuffer =  NULL;
    free(FileBuff);
    return ImagefileMU;
}
VOID ReadImageToFIle(PVOID ImageBuff,char * WritePath)
{
    LPVOID pFileBuffer = ImageBuff;//
    PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS 头
	PIMAGE_NT_HEADERS pNTHeader = NULL;//NT头
	PIMAGE_FILE_HEADER pPEHeader = NULL;//标准PE头
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;//可选PE头·
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;//节表
    PIMAGE_SECTION_HEADER EndpSectionHeader = NULL; //最后一张节表
    LPVOID ImagefileMU = NULL;// ImageFile内存

    pDosHeader = (PIMAGE_DOS_HEADER)pFileBuffer; // 赋值DOS头

    pNTHeader = (PIMAGE_NT_HEADERS)((char *)pFileBuffer+pDosHeader->e_lfanew); // 赋值NT头

    pPEHeader = (PIMAGE_FILE_HEADER)&pNTHeader->FileHeader;

    pOptionHeader =(PIMAGE_OPTIONAL_HEADER32)((char*)pPEHeader+20);

    pSectionHeader = (PIMAGE_SECTION_HEADER)((char *)pOptionHeader+pPEHeader->SizeOfOptionalHeader);

    EndpSectionHeader =(PIMAGE_SECTION_HEADER)(pSectionHeader+pPEHeader->NumberOfSections-1); //找到最后一一个节表

   
    DWORD CRFileBuff =(DWORD)(EndpSectionHeader->PointerToRawData+EndpSectionHeader->SizeOfRawData); //计算要存入空间的大小

    printf("要创建的大小为:%x\n",CRFileBuff);

    PVOID CreateFilePoint = NULL; 

    CreateFilePoint = malloc(CRFileBuff);
    if(!CreateFilePoint)
    {
        printf("创建新文件空间失败\n");
        free(pFileBuffer);
        return 0;
    }
    memset(CreateFilePoint,0,CRFileBuff); // 初始化空间

    memcpy(CreateFilePoint,pDosHeader,sizeof(PIMAGE_DOS_HEADER)); //赋值DOS头

    memcpy((char *)CreateFilePoint+sizeof(PIMAGE_NT_HEADERS),pNTHeader,sizeof(PIMAGE_NT_HEADERS)); //赋值NT头

    memcpy((char *)CreateFilePoint+sizeof(PIMAGE_FILE_HEADER)+4,pPEHeader,sizeof(PIMAGE_FILE_HEADER)); //赋值标准PE头

    memcpy((char *)CreateFilePoint+sizeof(PIMAGE_FILE_HEADER)+4+20,pOptionHeader,sizeof(PIMAGE_OPTIONAL_HEADER32)); //赋值NT头
    
    memcpy((char *)CreateFilePoint+sizeof(PIMAGE_FILE_HEADER)+4+20+pPEHeader->SizeOfOptionalHeader,pSectionHeader,sizeof(PIMAGE_SECTION_HEADER));

    //测试内存是否读取成功

   /* for (int i = 0; i < 100; i++)
    {
        char * PUTachar = NULL;
        PUTachar = (char *)CreateFilePoint+i;
        printf("测试字节:%hhx\t",*PUTachar );
       
    }*/
    //ps:不想写了 摆!
    //memcpy((char *)CreateFilePoint);




    


}


int main()
{
   PVOID FileChangeImage = NULL;
   FileChangeImage = FileBuffToImageBuff(GetFileBuff(File_Path));
   ReadImageToFIle(FileChangeImage,CreateFile_Path);

   return 0;
}















