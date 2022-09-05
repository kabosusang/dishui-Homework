#include <stdio.h>

#include <windows.h>

#define File_Path "3_24.dll"
 
PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS 头
PIMAGE_NT_HEADERS pNTHeader = NULL;//NT头
PIMAGE_FILE_HEADER pPEHeader = NULL;//标准PE头
PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;//可选PE头·
PIMAGE_SECTION_HEADER pSectionHeader = NULL;//节表

IMAGE_DATA_DIRECTORY PEtables  ; //导出表
PIMAGE_EXPORT_DIRECTORY Exportable = NULL; 
PIMAGE_EXPORT_DIRECTORY TrueExport = NULL;
PVOID GetFileBuff( char * FilePath)
{
    FILE* RFile = NULL;
    DWORD64 FizeSize = 0;
    PVOID FileBuff = NULL;
	int n = 0;

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
	
    n = fread(FileBuff,FizeSize,1,RFile);
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
 
void IniPefileDate(LPVOID DllBuff)
{
pDosHeader = (PIMAGE_DOS_HEADER)DllBuff;
pNTHeader = (PIMAGE_NT_HEADERS)((char *)DllBuff+pDosHeader->e_lfanew);
pPEHeader =  pPEHeader = (PIMAGE_FILE_HEADER)&pNTHeader->FileHeader;
pOptionHeader =(PIMAGE_OPTIONAL_HEADER32)((char*)pPEHeader+20);
pSectionHeader = (PIMAGE_SECTION_HEADER)((char *)pOptionHeader+pPEHeader->SizeOfOptionalHeader);
}

LPVOID  RVAchangeFOA(LPVOID RVAaddress)
{
	int i = 1;
    if(pOptionHeader->FileAlignment == pOptionHeader->SectionAlignment)
    {
        printf("内存与文件完全对齐 RVA=FOA\n");
    

        return RVAaddress;
    }
    //判断是否位于
   if(RVAaddress<=pOptionHeader->SizeOfHeaders)
    {

        return RVAaddress;
    }

    for (; i <= pPEHeader->NumberOfSections; i++)//i可以判断在第几个节表
    {
        PIMAGE_SECTION_HEADER pesectionBuff = pSectionHeader;
        PIMAGE_SECTION_HEADER NextpesectionBuff = pesectionBuff+i;
        
       if(RVAaddress>=pesectionBuff->VirtualAddress && RVAaddress<NextpesectionBuff->VirtualAddress);
        {
           while (pesectionBuff)
           {
            /* code */
            //RVA根据节表转化成FOA 
            //没写出来 呜呜呜

           }
           
            

            return 0;
        }
       pesectionBuff++;
       
    }
    





}

void PeExportPrint(LPVOID DllData)
{
	int k = 0;
	DWORD** FunctionAddtable = NULL;
	DWORD** FunctionNametable = NULL;
	DWORD** FunctionNameOrdinalstable = NULL;

    PEtables = pOptionHeader->DataDirectory[0];
   
    Exportable = RVAchangeFOA((LPVOID)PEtables.VirtualAddress); //指向导出表//RVA转FOA

    printf("文件地址:%x\n",DllData);

    printf("导出表FOA:%x\n",Exportable);

    TrueExport = ((DWORD)DllData+(DWORD)Exportable);//这里gcc编译不出来 用了vc6 估计是dll文件是32位而gcc编译程序为64位 
    printf("导出表为:%x\n",TrueExport);

	printf("/*************************************************************/\n");


	printf("导出表基为:%x",TrueExport->Base);

	
	printf("导出函数个数:%d\n",TrueExport->NumberOfNames);
	printf("/*************************************************************/\n");
	FunctionAddtable = TrueExport->AddressOfFunctions;
	FunctionNametable = TrueExport->AddressOfNames;
	FunctionNameOrdinalstable = TrueExport->AddressOfNameOrdinals;
	//函数所有名称分别为:
	for(;k<TrueExport->NumberOfNames;k++)
	{
		printf("函数所有名称分别为:%s\n",(char *)*((*FunctionNametable)+k*4)); //不知道为什么一直读不出来
	
	}

	printf("/*************************************************************/\n");



}


int main()
{

LPVOID DllData = GetFileBuff(File_Path);
IniPefileDate(DllData);
PeExportPrint(DllData);

Sleep(132132);

}