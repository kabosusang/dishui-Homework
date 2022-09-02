#include <stdio.h>
#include <windows.h>

class Monster								
{								
public:								
	int ID;							
	int Level;							
	char Name[20];							
public:								
	Monster(){}							
	Monster(int ID,int Level,const char* Name)							
	{							
		this->ID = ID;						
		this->Level = Level;						
		memcpy(&this->Name,Name,strlen(Name)+1);						
	}							
};								
								
template<class T>								
class TreeNode{								
public:								
	T element;					//当前节点存储的数据		
	TreeNode<T>* pLeft;					//指向左子节点的指针		
	TreeNode<T>* pRight;					//指向右子节点的指针		
								
	TreeNode(T& ele){							
		//初始化Node节点						
		memset(&element,0,sizeof(TreeNode));						
		//为元素赋值						
		memcpy(&element,&ele,sizeof(T));						
		pLeft = pRight = NULL;						
	}							
};								
								
template<class T>								
class BSortTree{								
public:								
	BSortTree();					//构造函数		
	~BSortTree();					//析构函数		
public:								
	void InOrderTraverse(TreeNode<T>* pNode);					//中序遍历		
	void PreOrderTraverse(TreeNode<T>* pNode);					//前序遍历		
	void PostOrderTraverse(TreeNode<T>* pNode);					//后序遍历		
	TreeNode<T>* GetRoot();					//返回根节点		
	int GetDepth(TreeNode<T>* pNode);					//返回某个节点的高度/深度		
private:								
	void Init();							
private:								
	TreeNode<T>* m_pRoot;					//根结点指针		
	int size;					//树中元素总个数		
};								
								
template<class T> 								
BSortTree<T>::BSortTree()								
{								
	Init();							
}								
template<class T> 								
BSortTree<T>::~BSortTree(){								
								
	//释放所以节点空间							
								
}								
								
template<class T> 								
void BSortTree<T>::Init()								
{								
								
	Monster m1(1,1,"刺猬");							
	Monster m2(2,2,"野狼");							
	Monster m3(3,3,"野猪");							
	Monster m4(4,4,"士兵");							
	Monster m5(5,5,"火龙");							
	Monster m6(6,6,"独角兽");							
	Monster m7(7,7,"江湖大盗");							
								
								
	TreeNode<Monster>* n1 = new TreeNode<Monster>(m1);							
	TreeNode<Monster>* n2 = new TreeNode<Monster>(m2);							
	TreeNode<Monster>* n3 = new TreeNode<Monster>(m3);							
	TreeNode<Monster>* n4 = new TreeNode<Monster>(m4);							
	TreeNode<Monster>* n5 = new TreeNode<Monster>(m5);							
	TreeNode<Monster>* n6 = new TreeNode<Monster>(m6);							
	TreeNode<Monster>* n7 = new TreeNode<Monster>(m7);							
								
	m_pRoot = n5;							
	n5->pLeft = n4;							
	n5->pRight = n6;							
	n4->pLeft = n1;							
	n1->pRight = n2;							
	n6->pLeft = n3;							
	n3->pRight = n7;							
	size = 7;							
	/*							
					5			
								
				4		6		
								
			1		    3			
								
			     2		        7			
								
	*/							
}								
template<class T> 								
TreeNode<T>* BSortTree<T>::GetRoot()								
{								
	return m_pRoot;							
}								
template<class T>								
int BSortTree<T>::GetDepth(TreeNode<T>* pNode)								
{								
     if(pNode==NULL) 								
    {								
	return 0;  							
    }								
    else  								
    {  								
        int m = GetDepth(pNode->pLeft);  								
        int n = GetDepth(pNode->pRight);  								
        return (m > n) ? (m+1) : (n+1);   								
    }  								
}								
template<class T> 								
void BSortTree<T>::InOrderTraverse(TreeNode<T>* pNode)								
{								
								
	//中序遍历所有怪物,列出怪的名字	
	char* pName = NULL;						
	if(pNode!=NULL)
	{
		InOrderTraverse(pNode->pLeft);
		pName = (char *)&pNode->element;
		pName =	pName+8;
		printf("%s\n",pName);
		InOrderTraverse(pNode->pRight);
	}
	/*							
					5			
								
				4		6		
								
			1		    3			
								
			     2		        7			
				
	*/							
								
}								
								
template<class T> 								
void BSortTree<T>::PreOrderTraverse(TreeNode<T>* pNode)								
{								
	char* pName = NULL;							
	//前序遍历所有怪物,列出怪的名字	
		if(pNode!=NULL)
	{
		pName = (char *)&pNode->element;
		pName =	pName+8;
		printf("%s\n",pName);
		PreOrderTraverse(pNode->pLeft);
		PreOrderTraverse(pNode->pRight);
	}					
								
}								
								
template<class T> 								
void BSortTree<T>::PostOrderTraverse(TreeNode<T>* pNode)								
{								
								
	//后序遍历所有怪物,列出怪的名字	
	char* pName = NULL;							
	//前序遍历所有怪物,列出怪的名字	
		if(pNode!=NULL)
	{
		
		PreOrderTraverse(pNode->pLeft);
		PreOrderTraverse(pNode->pRight);
		pName = (char *)&pNode->element;
		pName =	pName+8;
		printf("%s\n",pName);
	}											
								
}								

int main()
{
	BSortTree<Monster>* p = new BSortTree<Monster>;
		p->InOrderTraverse(p->GetRoot());

}