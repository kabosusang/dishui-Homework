#include <stdio.h>
#include <Windows.h>

									
#define SUCCESS           1 // 执行成功								
#define ERROR            -1 // 执行失败								
#define INDEX_IS_ERROR   -2 // 错误的索引号								
#define BUFFER_IS_EMPTY  -3 // 缓冲区已空								
									
									
template <class T_ELE>								
class LinkedList								
{								
public:								
	LinkedList();							
	~LinkedList();							
public:								
	BOOL  IsEmpty();						                                    //判断链表是否为空 空返回1 非空返回0	
	void  Clear();						                                        //清空链表	
	DWORD GetElement(IN DWORD dwIndex,OUT T_ELE& Element);						//根据索引获取元素	
	DWORD GetElementIndex(IN T_ELE& Element);						            //根据元素获取链表中的索引	
	DWORD Insert(IN T_ELE Element);						                        //新增元素	
	DWORD Insert(IN DWORD dwIndex, IN T_ELE Element);						    //根据索引新增元素	
	DWORD Delete(IN DWORD dwIndex);						                        //根据索引删除元素	
	DWORD GetSize();						                                    //获取链表中元素的数量	
private:								
	typedef struct _NODE 							
	{							
		T_ELE  Data;						
		_NODE *pNext;						
	}NODE,*PNODE;							
	PNODE GetIndexCurrentNode(DWORD dwIndex);					//获取索引为dwIndex的指针	
	PNODE GetIndexPreviousNode(DWORD dwIndex);				    //获取索引为dwIndex的前一个节点指针	
	PNODE GetIndexNextNode(DWORD dwIndex);						//获取索引为dwIndex的后一个节点指针	
private:								
	PNODE m_pList;						                        //链表头指针，指向第一个节点	
	DWORD m_dwLength;						                    //元素的数量	
};								
									
	//无参构造函数 初始化成员								
template<class T_ELE> 
LinkedList<T_ELE>::LinkedList()								
	:m_pList(NULL),m_dwLength(0)							
{								
									
}								
//析构函数 清空元素								
template<class T_ELE> 
LinkedList<T_ELE>::~LinkedList()								
{								
	Clear();							
}								
//判断链表是否为空   看头指针							
template<class T_ELE> 
BOOL LinkedList<T_ELE>::IsEmpty()								
{								
	if(m_pList == NULL)
	{
		return 1;
	}
	else
	{
		return 0;
	}														
								//0 1 2 3 4 5	
}								
//清空链表								
template<class T_ELE> 
void LinkedList<T_ELE>::Clear()								
{								
		// 1. 判断链表是否为空
		// 2. 循环删除链表中的节点		
		if(m_pList != NULL)
		{
			PNODE i = m_pList;
			
			while (i->pNext!=NULL)
			{
				
				for (int j = 1; j < m_dwLength; j++)
				{
					PNODE p = (PNODE)i->pNext;
					
					delete p;
					p = NULL;
					p = (PNODE)i->pNext;
				}
				
			}
			
		}																											
		// 3. 删除最后一个节点并将链表长度置为0							
		delete[] m_pList;
		m_pList	= NULL;
		m_dwLength = 0;	
}								
//根据索引获取元素								
template<class T_ELE> 
DWORD LinkedList<T_ELE>::GetElement(IN DWORD dwIndex,OUT T_ELE& Element)								
{								
		// 1. 判断索引是否有效
		if(dwIndex>this->m_dwLength || dwIndex<0)
		{
			return ERROR;
		}							
									
		// 2. 取得索引指向的节点	
		T_ELE* bUFFIndex = NULL;

		bUFFIndex = (T_ELE*)m_pList+dwIndex-1;
		// 3. 将索引指向节点的值复制到OUT参数
		Element = *(T_ELE*)bUFFIndex;							
		return SUCCESS;							
}								
//根据元素内容获取索引								
template<class T_ELE> 
DWORD LinkedList<T_ELE>::GetElementIndex(IN T_ELE& Element)								
{								
		// 1. 判断链表是否为空
		if(m_pList == NULL)
		{
			return ERROR;
		}							
									
		// 2. 循环遍历链表，找到与Element相同的元素	
		for (int i = 0; i < m_dwLength; i++)
		{
			T_ELE* CmpMem = NULL;
			CmpMem = (T_ELE* )m_pList;
			int c = memcmp(CmpMem,Element,sizeof(T_ELE));
			if(c == 0)
			{
				return i;
			}
			/* code */
		}								
}								
//在链表尾部新增节点								
template<class T_ELE> 
DWORD LinkedList<T_ELE>::Insert(IN T_ELE Element)								
{		
		PNODE CriLink = new PNODE;
		memeset(CriLink,0,sizeof(NODE));
		memcpy(&CriLink->Data,&Element,sizeof(T_ELE));						
		// 1. 判断链表是否为空							
		if(m_pList == NULL || m_dwLength = 0)
		{
			m_pList = CriLink;
			m_dwLength++;	
			return SUCCESS;
		}								
		// 2. 如果链表中已经有元素	
	 	PNODE pTempNode = m_pList;
		for (DOWRD i = 0; i < m_dwLength; i++)
		{
				pTempNode = pTempNode->pNext; //循环指向最后一个元素
		}
		pTempNode->pNext = CriLink;
		m_dwLength++;	
		return SUCCESS;				 
}								
	//将节点新增到指定索引的位置						//0 1 2 3 4		
template<class T_ELE> 
DWORD LinkedList<T_ELE>::Insert(IN DWORD dwIndex, IN T_ELE Element)								
{								
			PNODE pNEWnode = new PNODE;
			PNODE pPreviousNode = NULL;
			PNODE pCurrentNode = NULL;

	
			memset(pNEWnode,0,sizeof(PNODE));
			memcpy(&pNEWnode->Data,&Element,sizeof(T_ELE));
		//  1. 判断链表是否为空							
			if( m_pList== NULL || m_dwLength == 0)
			{
				m_pList=pNEWnode;
				m_dwLength++
				return SUCCESS;
			}					
		//  2. 判断索引值是否有效							
			if(dwIndex<0 || dwIndex>m_dwLength)
				return INDEX_IS_ERROR;				
		//  3. 如果索引为0							
			if(dwIndex==0)
			{
				pNEWnode->pNext = m_pList;
				m_pList = pNEWnode;
				m_dwLength++
				return SUCCESS;

			}					
		//  4. 如果索引为链表尾	
			if(dwIndex == m_dwLength)
			{
				pPreviousNode = GetIndexPreviousNode(dwIndex);
				pPreviousNode->pNext = pNEWnode;
				m_dwLength++
				return SUCCESS;
			}
		//  5. 如果索引为链表中	
			pPreviousNode =	 GetIndexPreviousNode(dwIndex);	
			
			pNEWnode->pNext= pPreviousNode->pNext;
			pPreviousNode->pNext = pNEWnode;
			m_dwLength++
			return SUCCESS;
}								
	//根据索引删除节点								
template<class T_ELE>
 DWORD LinkedList<T_ELE>::Delete(IN DWORD dwIndex)								
{								
		PNODE BUFFlink = NULL;
		PNODE Preverilink = NULL;
		PNODE NextLink = NULL;	
		//  1. 判断链表是否为空							
		if(m_pList==NULL)
		{
			return SUCCESS;
		}
		//  2. 判断索引值是否有效							
		if(dwIndex<0 || dwIndex>=m_dwLength )
			return INDEX_IS_ERROR;
		//  3. 如果链表中只有头节点，且要删除头节点							
		if(m_dwLength == 1 && dwIndex == 1)
		{		
			delete m_pList;
			m_pList =NULL;
			m_dwLength--;
		}						
		//  4. 如果要删除头节点							
		if(dwIndex == 1 && m_dwLength!=1)
		{
			BUFFlink = m_pList;
			m_pList=m_pList->pNext;
			delete BUFFlink;
			BUFFlink = NULL;
			m_dwLength--;
		}
		//  5. 如果是其他情况	 0 1 2 3 4 5
		//						1 2 3 4 5 6
		else
		{
		Preverilink = GetIndexPreviousNode(dwIndex);
		NextLink    = GetIndexNextNode(dwIndex);
		PNODE CurrentLink = NULL;
		CurrentLink = Preverilink->pNext;
		delete CurrentLink;
		CurrentLink = NULL;
		Preverilink->pNext = NextLink;
		m_dwLength--;
		}			
}								
	//获取链表中节点的数量								
template<class T_ELE> 
DWORD LinkedList<T_ELE>::GetSize()								
{								
		return m_dwLength;							
}								
	//获取dwIndex前面节点的地址								
template<class T_ELE> 								
LinkedList<T_ELE>::PNODE LinkedList<T_ELE>::GetIndexPreviousNode(DWORD dwIndex)								
{		
		PNODE MiddBuff = m_pList;
		if(m_pList==NULL)
		{
				printf("改链表为空 获取不到上个链表地址");
				return ERROR;
		}
		if(dwIndex == 1)
		{
				printf("改链表只有一个元素 获取不了上一个元素");
				return ERROR;
		}
		//  					0 1 2 3 4 5
		//						1 2 3 4 5 6
		for (int i = 2; i < m_dwLength; i++)
		{
			if(i == dwIndex)
			{
				return MiddBuff;
			}
			MiddBuff = MiddBuff->pNext;
						
		}
		

		// 就是一个循环							
									
}								
	//获取dwIndex节点的地址								
template<class T_ELE> 								
LinkedList<T_ELE>::PNODE 
LinkedList<T_ELE>::GetIndexCurrentNode(DWORD dwIndex)								
{								
		// 就是一个循环							
		PNODE MiddBuff = m_pList;
		if(m_pList==NULL)
		{
				printf("改链表为空 获取不到上个链表地址");
				return ERROR;
		}
		//  					0 1 2 3 4 5
		//						1 2 3 4 5 6
		for (int i = 1; i < m_dwLength; i++)
		{
			if(i == dwIndex)
			{
				return MiddBuff;
			}
			MiddBuff = MiddBuff->pNext;
						
		}

}								
	//获取dwIndex后面节点的地址								
template<class T_ELE> 								
LinkedList<T_ELE>::PNODE LinkedList<T_ELE>::GetIndexNextNode(DWORD dwIndex)								
{								
		// 就是一个循环	
		PNODE MiddBuff = m_pList;
		if(m_pList==NULL)
		{
				printf("改链表为空 获取不到上个链表地址");
				return ERROR;
		}
		//  					0 1 2 3 4 5
		//						1 2 3 4 5 6
		for (int i = 1; i < m_dwLength; i++)
		{
			if(i == dwIndex)
			{
				return MiddBuff->pNext;
			}
			MiddBuff = MiddBuff->pNext;
						
		}						
									
}								


int main()
{

}