#include <stdio.h>
#include <Windows.h>


#define SUCCESS           			 1 // 成功		
#define ERROR            			 -1 // 失败		
#define MALLOC_ERROR			 -2 // 申请内存失败		
#define INDEX_ERROR		 	 -3 // 错误的索引号		
					
					
	template <class T_ELE>											
	class Vector											
	{											
	public:											
		Vector();										
		Vector(DWORD dwSize);										
		~Vector();										
	public:											
		DWORD	at(DWORD dwIndex,OUT T_ELE* pEle);				//根据给定的索引得到元素				
	    DWORD   push_back(T_ELE Element);						//将元素存储到容器最后一个位置				
		VOID	pop_back();					                    //删除最后一个元素				
		DWORD	insert(DWORD dwIndex, T_ELE Element);			//向指定位置新增一个元素				
		DWORD	capacity();					                    //返回在不增容的情况下，还能存储多少元素				
		VOID	clear();					                    //清空所有元素				
		BOOL	empty();					                    //判断Vector是否为空 返回true时为空				
		VOID	erase(DWORD dwIndex);					        //删除指定元素				
		DWORD	size();					                        //返回Vector元素数量的大小				
	private:											
		BOOL	expand();									
	private:											
		DWORD  m_dwIndex;						//下一个可用索引				
		DWORD  m_dwIncrement;					//每次增容的大小				
		DWORD  m_dwLen;							//当前容器的长度				
		DWORD  m_dwInitSize;					//默认初始化大小				
		T_ELE *m_pVector;						//容器指针				
	};											
	
template <class T_ELE>					
Vector<T_ELE>::Vector()					
:m_dwInitSize(100),m_dwIncrement(5)					
{					
	//1.创建长度为m_dwInitSize个T_ELE对象				
	m_pVector = new T_ELE[m_dwInitSize];
	//2.将新创建的空间初始化				
	memset(m_pVector,0,m_dwInitSize*sizeof(T_ELE));				
	//3.设置其他值
	m_dwIndex = 0;
	m_dwLen = m_dwInitSize;
}					
template <class T_ELE>					
Vector<T_ELE>::Vector(DWORD dwSize)					
:m_dwIncrement(5)					
{					
	//1.创建长度为dwSize个T_ELE对象				
	m_pVector = new T_ELE[dwSize];
	//2.将新创建的空间初始化				
	memset(m_pVector,0,dwSize*sizeof(T_ELE));		
	//3.设置其他值	
	m_dwIndex = 0;
	m_dwLen = dwSize;
	
}				
template <class T_ELE>					
Vector<T_ELE>::~Vector()					
{								
	//释放空间 delete[]				
	delete[] m_pVector;	
	m_pVector = NULL;
}					
					
template <class T_ELE>					
BOOL Vector<T_ELE>::expand()					
{					
	// 1. 计算增加后的长度	
	DWORD64 N_dwlen = m_dwLen+m_dwIncrement;					
	// 2. 申请空间				
	T_ELE *newSpace = new T_ELE[N_dwlen];
	if(newSpace==NULL)
	{
		return ERROR;
	}						
	// 3. 将数据复制到新的空间
	ZeroMemory(newSpace,m_dwLen);				
	memcpy(newSpace,m_pVector,sizeof(T_ELE)*m_dwLen);	
					
	// 4. 释放原来空间				
	delete[] m_pVector;			
	m_pVector = newSpace;
	newSpace = NULL;
	// 5. 为各种属性赋值				
	m_dwLen =(DWORD)N_dwlen;

	return SUCCESS;
}					
					
template <class T_ELE>					
DWORD  Vector<T_ELE>::push_back(T_ELE Element)					
{					
	//1.判断是否需要增容，如果需要就调用增容的函数				
	if(m_dwIndex >= m_dwLen)
	{
		this->expand();
		this->m_dwLen += this->m_dwIncrement;
	}	
	//2.将新的元素复制到容器的最后一个位置
		memcpy(&m_pVector[m_dwIndex],&Element,sizeof(T_ELE));					
	//3.修改属性值	
		m_dwIndex++;

	return SUCCESS;				
}					
					
template <class T_ELE>					
DWORD  Vector<T_ELE>::insert(DWORD dwIndex, T_ELE Element)					
{					
	//1.判断是否需要增容，如果需要就调用增容的函数				
		if(m_dwIndex >= m_dwLen)
	{
		this->expand();
		this->m_dwLen += this->m_dwIncrement;
	}								
	//2.判断索引是否在合理区间				
		if(dwIndex>m_dwLen || dwIndex<0)
		{
			return INDEX_ERROR;
		}					
	//3.将dwIndex之后的元素后移				
		for (int i = m_dwLen ; i > dwIndex; i--)
		{
			memcpy(&m_pVector[i],&m_pVector[i-1],sizeof(T_ELE));
			/* code */
		}
						
	//4.将Element元素复制到dwIndex位置				
		memcpy(&m_pVector[dwIndex],&Element,sizeof(T_ELE));			
					
	//5.修改属性值
	m_dwIndex++;

}					
template <class T_ELE>					
DWORD Vector<T_ELE>::at(DWORD dwIndex,T_ELE* pEle)					
{					
	//判断索引是否在合理区间				
	if(dwIndex >= m_dwLen || dwIndex<0)
	{
		return INDEX_ERROR;
	}									
	//将dwIndex的值复制到pEle指定的内存		
	memcpy(pEle,&m_pVector[dwIndex],sizeof(T_ELE));		
					
}					
					
//其他函数。。自己实现

void TestVector()
{
	Vector<int>* pVector = new Vector<int>;
	pVector->push_back(1);
	pVector->push_back(2);
	pVector->push_back(3);
	pVector->push_back(4);
	int x = 0;	

	pVector->at(2,&x);

	printf("%d\n",x);
}






int main()
{
	TestVector();
	  //模板用<>
}
