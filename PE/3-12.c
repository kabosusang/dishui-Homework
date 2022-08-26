 #include <stdio.h>
#include<stdlib.h>
#include<Windows.h>
#define F_PATH1 "C:/Windows/System32/notepad.exe"

LPVOID ReadPEFile()
{

FILE*  pfile;
DWORD Fseeksize=0;
LPVOID pFileBuffer = NULL;

pfile=fopen(F_PATH1,"rb");
if(!pfile)
{
printf("读取失败\n");
return NULL;
}
fseek(pfile,0,SEEK_END);
Fseeksize=ftell(pfile);
fseek(pfile,0,SEEK_SET);
if(!Fseeksize)
{
	printf("获取大小失败\n");
	return NULL;
}       
pFileBuffer = malloc(Fseeksize);
if(!pFileBuffer)
{
printf("分配空间失败\n");
fclose(pfile);
return NULL;
}
size_t n= fread(pFileBuffer,Fseeksize,1,pfile);
if(!n)
{
printf("存取空间失败\n错误码为:%d",n);
free(pFileBuffer);
fclose(pfile); 
return NULL;
}
fclose(pfile);
return pFileBuffer;

}

VOID PrintHeads()
{
	LPVOID pFileBuffer = NULL;
	PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS 头
	PIMAGE_NT_HEADERS pNTHeader = NULL;//NT头
	PIMAGE_FILE_HEADER pPEHeader = NULL;//标准PE头
	PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;//可选PE头·
	PIMAGE_SECTION_HEADER pSectionHeader = NULL;//节表


	pFileBuffer= ReadPEFile();
	if(!pFileBuffer)
	{
	printf("读取文件失败\n");
	}

	if(*((WORD*)pFileBuffer)!=(WORD)0x5A4D)
	{
		printf("该文件不是PE文件");
	}

pDosHeader=(PIMAGE_DOS_HEADER)pFileBuffer;
if(pDosHeader)
{
printf("MZ头:%x\n",pDosHeader->e_magic);
printf("PE头所在位置:%x\n",pDosHeader->e_lfanew);
}

if(*((PDWORD)(pFileBuffer+pDosHeader->e_lfanew)) != IMAGE_NT_SIGNATURE)
{
	printf("不是有效PE位\n");
}
pNTHeader=(PIMAGE_NT_HEADERS)(pFileBuffer+pDosHeader->e_lfanew);

if(pNTHeader)
{
printf("PE标识:%x\n",pNTHeader->Signature);
}

pPEHeader=(PIMAGE_FILE_HEADER)&(pNTHeader->FileHeader);
if(pPEHeader)
{
printf("节表的个数:%d\n",pPEHeader->NumberOfSections);
}
printf("可选PE头大小为%x\n",pPEHeader->SizeOfOptionalHeader);

pOptionHeader=(PIMAGE_OPTIONAL_HEADER32)((PBYTE)pPEHeader+20);
if(pOptionHeader)
{
switch (pOptionHeader->Magic)
{
case 0x010B:
	printf("该文件是32位文件\n");
	break;
case 0x020B:
	printf("该文件是64位文件\n");
default:
	break;
}
printf("文件对齐为:0x%x\n",pOptionHeader->FileAlignment);
printf("内存对齐为:0x%x\n",pOptionHeader->SectionAlignment);

pSectionHeader = (PIMAGE_SECTION_HEADER)((char *)pOptionHeader+pPEHeader->SizeOfOptionalHeader);
printf("头表名字为%s\n",pSectionHeader->Name);
}

}

int main(int argc, char const* argv[])

{
	PrintHeads();
	
	return 0;
}


