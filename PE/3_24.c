#include <stdio.h>

#include <windows.h>

#define File_Path "3_24.dll"
 
PIMAGE_DOS_HEADER pDosHeader = NULL;//DOS ͷ
PIMAGE_NT_HEADERS pNTHeader = NULL;//NTͷ
PIMAGE_FILE_HEADER pPEHeader = NULL;//��׼PEͷ
PIMAGE_OPTIONAL_HEADER32 pOptionHeader = NULL;//��ѡPEͷ��
PIMAGE_SECTION_HEADER pSectionHeader = NULL;//�ڱ�

IMAGE_DATA_DIRECTORY PEtables  ; //������
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
        printf("��ȡ�ļ�ʧ��\n");
        return 0;
    }
    fseek(RFile,0,SEEK_END);
    FizeSize = ftell(RFile);
    if(!FizeSize)
    {
        printf("��ȡ�ļ���Сʧ��\n");
        fclose(RFile);
        return 0;
    }
    FileBuff = malloc(FizeSize);
    if(!FileBuff)
    {
        printf("����ռ�ʧ��\n");
        fclose(RFile);
        return 0;
    }
    memset(FileBuff,0,FizeSize);//��ʼ���ڴ�
    fseek(RFile,0,SEEK_SET);
	
    n = fread(FileBuff,FizeSize,1,RFile);
        if(!n)
        {
            printf("��ȡ�ռ�ʧ��\n");
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
        printf("�ڴ����ļ���ȫ���� RVA=FOA\n");
    

        return RVAaddress;
    }
    //�ж��Ƿ�λ��
   if(RVAaddress<=pOptionHeader->SizeOfHeaders)
    {

        return RVAaddress;
    }

    for (; i <= pPEHeader->NumberOfSections; i++)//i�����ж��ڵڼ����ڱ�
    {
        PIMAGE_SECTION_HEADER pesectionBuff = pSectionHeader;
        PIMAGE_SECTION_HEADER NextpesectionBuff = pesectionBuff+i;
        
       if(RVAaddress>=pesectionBuff->VirtualAddress && RVAaddress<NextpesectionBuff->VirtualAddress);
        {
           while (pesectionBuff)
           {
            /* code */
            //RVA���ݽڱ�ת����FOA 
            //ûд���� ������

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
   
    Exportable = RVAchangeFOA((LPVOID)PEtables.VirtualAddress); //ָ�򵼳���//RVAתFOA

    printf("�ļ���ַ:%x\n",DllData);

    printf("������FOA:%x\n",Exportable);

    TrueExport = ((DWORD)DllData+(DWORD)Exportable);//����gcc���벻���� ����vc6 ������dll�ļ���32λ��gcc�������Ϊ64λ 
    printf("������Ϊ:%x\n",TrueExport);

	printf("/*************************************************************/\n");


	printf("�������Ϊ:%x",TrueExport->Base);

	
	printf("������������:%d\n",TrueExport->NumberOfNames);
	printf("/*************************************************************/\n");
	FunctionAddtable = TrueExport->AddressOfFunctions;
	FunctionNametable = TrueExport->AddressOfNames;
	FunctionNameOrdinalstable = TrueExport->AddressOfNameOrdinals;
	//�����������Ʒֱ�Ϊ:
	for(;k<TrueExport->NumberOfNames;k++)
	{
		printf("�����������Ʒֱ�Ϊ:%s\n",(char *)*((*FunctionNametable)+k*4)); //��֪��Ϊʲôһֱ��������
	
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