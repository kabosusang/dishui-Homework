#include <stdio.h>
#include<stdlib.h>
#include<Windows.h>

LPVOID ReadPEFile(char * FilePath)
{
    FILE* Pefile = NULL;
    DWORD Filesize = 0;
    LPVOID FileBuff = NULL;

    Pefile = fopen(FilePath,"rb");
        if(!Pefile)
         {
             printf("读取文件失败\n");
             fclose(Pefile);
             return NULL;
         }

    fseek(Pefile,0,SEEK_END); //文件指针为读取文件大小作准备
    Filesize = ftell(Pefile);
        if(!Filesize)
        {
            printf("读取大小失败\n");
            fclose(Pefile);
            return NULL;
        }
            
    fseek(Pefile,0,SEEK_SET);
    FileBuff = malloc(Filesize);
    //printf("需要发配空间为%x",Filesize);2c400
        if(!FileBuff)
        {
            printf("分配空间失败\n");
            fclose(Pefile);
            return NULL;
        }

    size_t n = fread(FileBuff,Filesize,1,Pefile);
        if(!n)
        {
            printf("存取空间失败\n");
            fclose(Pefile);
            free(FileBuff);
            return  NULL;
        }
        fclose(Pefile);
return FileBuff;
}

LPVOID ReadFileBuff(LPVOID FileBUff)
{
    LPVOID pFileBuffer = FileBUff;//
	PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS 头
	PIMAGE_NT_HEADERS pNTHeader = NULL;//NT头
	PIMAGE_FILE_HEADER pPEHeader = NULL;//标准PE头
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;//可选PE头·
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;//节表
    LPVOID Imagefile = NULL;// ImageFile内存

    //PE头初始化 
    pDosHeader=(PIMAGE_DOS_HEADER)pFileBuffer;//文件内存传入DOS头
    pNTHeader = (PIMAGE_NT_HEADERS)((char *)pFileBuffer+pDosHeader->e_lfanew);//传入NT头
    pPEHeader = (PIMAGE_FILE_HEADER)&(pNTHeader->FileHeader);//传入标准PE头
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((char *)pPEHeader+20);//传入可选PE头
    pSectionHeader = (PIMAGE_SECTION_HEADER)((char *)pOptionHeader+pPEHeader->SizeOfOptionalHeader);//传入节表

    /*printf("%x\n",pDosHeader->e_lfanew);
    printf("%x\n",pNTHeader->Signature);
    printf("%x\n",pPEHeader->TimeDateStamp);  
    printf("%x\n",pOptionHeader->FileAlignment);
    printf("%s",pSectionHeader->Name);*/
return Imagefile;
}


LPVOID ChangeImageBuff(LPVOID ImageFile)
{
    LPVOID IMBuffer = ImageFile;//
	PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS 头
	PIMAGE_NT_HEADERS pNTHeader = NULL;//NT头
	PIMAGE_FILE_HEADER pPEHeader = NULL;//标准PE头
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;//可选PE头·
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;//节表
    LPVOID ImagefileMU = NULL;// ImageFile内存

    //PE头初始化 
    pDosHeader=(PIMAGE_DOS_HEADER)IMBuffer;//文件内存传入DOS头
    pNTHeader = (PIMAGE_NT_HEADERS)((char *)IMBuffer+pDosHeader->e_lfanew);//传入NT头
    pPEHeader = (PIMAGE_FILE_HEADER)&(pNTHeader->FileHeader);//传入标准PE头
    pOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((char *)pPEHeader+20);//传入可选PE头
    pSectionHeader = (PIMAGE_SECTION_HEADER)((char *)pOptionHeader+pPEHeader->SizeOfOptionalHeader);//传入节表

   
    ImagefileMU = malloc(pOptionHeader->SizeOfImage); // 存取Imagefile总长度
    ZeroMemory(ImagefileMU,pOptionHeader->SizeOfImage);//清零缓冲区
    if(!ImagefileMU)
    {
        printf("存取ImageFilemu空间失败");
        return NULL;
    }
    //拉伸内存
    PIMAGE_DOS_HEADER IMpDosHeader = NULL;//DOS 头
	PIMAGE_NT_HEADERS IMpNTHeader = NULL;//NT头
	PIMAGE_FILE_HEADER IMpPEHeader = NULL;//标准PE头
	PIMAGE_OPTIONAL_HEADER32 IMpOptionHeader = NULL;//可选PE头·
	PIMAGE_SECTION_HEADER IMpSectionHeader0 = NULL;//节表0
    PIMAGE_SECTION_HEADER IMpSectionHeader1 = NULL;//节表1
    PIMAGE_SECTION_HEADER IMpSectionHeader2 = NULL;//节表2
    PIMAGE_SECTION_HEADER IMpSectionHeader3 = NULL;//节表3
    PIMAGE_SECTION_HEADER IMpSectionHeader4 = NULL;//节表4
    PIMAGE_SECTION_HEADER IMpSectionHeader5 = NULL;//节表5
    PIMAGE_SECTION_HEADER IMpSectionHeader6 = NULL;//节表6

    int ShitCount = 0;

    IMpDosHeader=(PIMAGE_DOS_HEADER)IMBuffer;//文件内存传入DOS头
    IMpNTHeader = (PIMAGE_NT_HEADERS)((char *)IMBuffer+IMpDosHeader->e_lfanew);//传入NT头
    IMpPEHeader = (PIMAGE_FILE_HEADER)&(IMpNTHeader->FileHeader);//传入标准PE头
    IMpOptionHeader = (PIMAGE_OPTIONAL_HEADER32)((char *)IMpPEHeader+20);//传入可选PE头
    IMpSectionHeader0 = (PIMAGE_SECTION_HEADER)((char *)IMpOptionHeader+IMpPEHeader->SizeOfOptionalHeader);//传入节表
   //初始化节表
    IMpSectionHeader1 =IMpSectionHeader0+1;
    IMpSectionHeader2 =IMpSectionHeader1+1;
    IMpSectionHeader3 =IMpSectionHeader2+1;
    IMpSectionHeader4 =IMpSectionHeader3+1;
    IMpSectionHeader5 =IMpSectionHeader4+1;
    IMpSectionHeader6 =IMpSectionHeader5+1;

   // printf("%x\n",IMpOptionHeader->SizeOfHeaders);//7节
   // printf("%d\n",IMpPEHeader->NumberOfSections); //节的数量 偏移为40
   // printf("%x\n",IMpOptionHeader->SizeOfImage); //存进内存总长度//计算偏移面变量
    ImagefileMU = IMpDosHeader;//存入拉伸后的IM内存
    printf("MZ头为%x\n",*(WORD *)ImagefileMU); //存入MZ
     CHAR * ShifImg = ImagefileMU;  
    //printf("%x",sizeof(*(IMpDosHeader)));
   // printf("%x\n",ShifImg);
   // printf("%x\n",ImagefileMU);
    ShifImg+=IMpDosHeader->e_lfanew;
    ShitCount+=IMpDosHeader->e_lfanew;
    //printf("%x\n",ShifImg-(CHAR *)ImagefileMU);
    //ShifImg =(CHAR *)IMpNTHeader;
    ShifImg=(CHAR *)IMpPEHeader;
    printf("%x\n",*((WORD *)((CHAR *)ImagefileMU+0xf8+1+1+2))); // 测试是否存入
    
    ShifImg+=16;//偏移到可扩展PE头
    ShitCount+=24;
    printf("%x\n",ShifImg-(CHAR *)ImagefileMU);
    ShifImg=(CHAR *)IMpOptionHeader;
    
    ShifImg+=IMpPEHeader->SizeOfOptionalHeader;
    ShitCount+=IMpPEHeader->SizeOfOptionalHeader;
     //printf("%x\n",ShifImg-(CHAR *)ImagefileMU);
    ShifImg =(PVOID)IMpSectionHeader0;
    printf("%x\n",((CHAR *)ImagefileMU+ShitCount)-(CHAR *)ImagefileMU);
    printf("%s\n",(CHAR *)ImagefileMU+ShitCount); //写入测试

    //对链表的写入测试
    printf("%s\n",IMpSectionHeader1->Name);
    printf("%s\n",(PIMAGE_SECTION_HEADER)ShifImg+1);

    printf("%x\n",IMpSectionHeader0->PointerToRawData);//20a00
    printf("%x\n",IMpSectionHeader0->VirtualAddress); //22000
   
    //要拉伸的内存 IMpDosHeader
    //传入的内存 IMBuffer

     memcpy((char *)IMpDosHeader+IMpSectionHeader0->VirtualAddress,(char *)IMpDosHeader+IMpSectionHeader0->PointerToRawData,IMpSectionHeader0->SizeOfRawData);

     memcpy((char *)IMpDosHeader+IMpSectionHeader1->VirtualAddress,(char *)IMpDosHeader+IMpSectionHeader1->PointerToRawData,IMpSectionHeader1->SizeOfRawData);

    memcpy((char *)IMpDosHeader+IMpSectionHeader2->VirtualAddress,(char *)IMpDosHeader+IMpSectionHeader2->PointerToRawData,IMpSectionHeader2->SizeOfRawData);

    memcpy((char *)IMpDosHeader+IMpSectionHeader3->VirtualAddress,(char *)IMpDosHeader+IMpSectionHeader3->PointerToRawData,IMpSectionHeader3->SizeOfRawData);

    memcpy((char *)IMpDosHeader+IMpSectionHeader4->VirtualAddress,(char *)IMpDosHeader+IMpSectionHeader4->PointerToRawData,IMpSectionHeader4->SizeOfRawData);

    memcpy((char *)IMpDosHeader+IMpSectionHeader5->VirtualAddress,(char *)IMpDosHeader+IMpSectionHeader5->PointerToRawData,IMpSectionHeader5->SizeOfRawData);

    memcpy((char *)IMpDosHeader+IMpSectionHeader6->VirtualAddress,(char *)IMpDosHeader+IMpSectionHeader6->PointerToRawData,IMpSectionHeader6->SizeOfRawData);


return IMpDosHeader;

}
