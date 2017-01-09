#include "DataStruct_Header.h"

void Point::InsertData(int dataX, int dataY) 
{
	x = dataX;                                                               //为点X初始化
	y = dataY;                                                               //为点Y初始化
}

int Point::GetX(void)
{
	return x;                                                                //返回X的数值
}

int Point::GetY(void)
{
	return y;                                                                //返回Y的数值
}

void Point::ClearData(void)
{
	x = 0;                                                                   //清除点X的数据
	y = 0;                                                                   //清除点Y的数据
}

bool operator==(Point point_A, Point point_B)
{
	if (point_A.GetX() == point_B.GetX() && point_A.GetY() == point_B.GetY()) {
		return true;
	}
	return false;
}


LNode::LNode()                                                               //新建这个节点的时候，为下面这个子树分配空间 
{
	//data = (TreeMaze*)malloc(sizeof(TreeMaze));                            //为LNode初始化空间
}

int LinkList::getNodeNumber()                                                //获取可行点的个数
{
	return nodeNumber;
}

void LinkList::InsertData(Point data)
{
	if (nodeNumber == 0) {                                                   //当节点数为0时
		head = tail = (LNode*)malloc(sizeof(LNode));                         //此时新建一个节点，头节点尾节点都是此节点
		head->data = (ElemType*)malloc(sizeof(ElemType));                    //为LNode初始化空间
		head->data->InsertData(data);                                        //赋值给节点的数据部分
		head->data->SetSonTree(NULL);
		head->next = NULL;                                                   //此节点的下一节点为空
	}
	else {                                                                   //此时链表有多个节点
		LNode *temp = (LNode*)malloc(sizeof(LNode));                         //新建节点
		temp->data = (ElemType*)malloc(sizeof(ElemType));                    //为LNode初始化空间
		temp->data->InsertData(data);                                        //填充数据
		temp->data->SetSonTree(NULL);
		temp->next = NULL;                                                   //数据项的尾部为空
		tail->next = temp;                                                   //将尾节点与新建节点连接
		tail = temp;                                                         //此时新节点及为新的尾节点
	}
	nodeNumber++;                                                            //节点数增加
}

bool LinkList::DeleteData(void)
{
	if (nodeNumber == 0) {                                                   //当链表中没有节点的时候
		return false;                                                        //无返回出错
	}
	else {
		LNode *temp = head;                                                  //将头节点的位置保存下来
		head = head->next;                                                   //跟新头节点为下一个节点位置
		free(temp);                                                          //释放原先头节点中的数据值
		if (nodeNumber == 1) {                                               //如果节点数原来是1的，那么现在没有节点了，但尾节点仍然在空位置
			tail = NULL;                                                     //尾节点数据重置
		}
	}
	nodeNumber--;                                                            //节点数减小
	cout << "Delete LNode OK!" << endl;
	return true;
}

bool LinkList::DeleteData(Point data)
{
	if (nodeNumber == 0) {                                                   //当链表中没有节点的时候
		return false;                                                        //无返回出错
	}
	else {
		LNode *temp = head;                                                  //将头节点的位置保存下来
		LNode *before = temp;                                                //保存要删除的前一个点
		while (temp) {                                                       //循环找寻要删除的点
			Point pTemp = temp->data->GetPoint();                            //获取数据
			if (pTemp.GetX() == data.GetX() &&                               //对比数据
				pTemp.GetY() == data.GetY()) {
				break;
			}
			before = temp;                                                   //此时变量点即将变成删除点的前一个点
			temp = temp->next;                                               //变量点控制
		}
		if (temp == NULL) {                                                  //此点不存在
			return false;
		}
		before->next = temp->next;                                           //删除temp点
		if (temp == head) {                                                  //如果删除点在头部
			head = head->next;                                               //原来的删除方法没有任何作用，要重新删除
		}
		else if (temp == tail) {                                             //如果删除点在尾部
			tail = before;                                                   //前一个变成了尾点
			before->next = NULL;                                             //前一个点的下一个节点变成了空
		}
		free(temp);                                                          //释放原先头节点中的数据值
		if (nodeNumber == 1) {                                               //如果节点数原来是1的，那么现在没有节点了，但尾节点仍然在空位置
			tail = NULL;                                                     //尾节点数据重置
		}
	}
	nodeNumber--;                                                            //节点数减小
	cout << "Delete LNode OK!" << endl;
	return true;
}

int LinkList::SearchNode(Point data)
{
	int index = 0;
	LNode *temp = this->head;
	while (temp){
		if (temp->data->GetPoint() == data) {
			return index;
		}
		temp = temp->next;
		++index;
	}
	return -1;
}

LNode LinkList::GetListNode(void)
{
	return *head;                                                            //返回头节点指向的数据
}

LNode *LinkList::GetListNode(int index)
{
	if (index < 0 || index > nodeNumber) {
		cout << "Error : Get list node over !" << endl;
		return NULL;
	}
	else {
		LNode *temp = this->head;
		for (int i = 0; i < nodeNumber; ++i) {
			if (i == index) {
				return temp;
			}
			temp = temp->next;
		}
	}
}

void LinkList::ShowList(void)
{
	LNode *temp = this->head;
	while (temp) {
		Point pTemp = temp->data->GetPoint();
		temp = temp->next;
		cout << "[" << pTemp.GetX() << "," << pTemp.GetY() << "]" << "->";
	}
	cout << "NULL" << endl;
}

void LinkList::ClearList(void)
{
	while (head != NULL) {                                                   //直到表头为空为止
		LNode *temp = head;                                                  //下面跟删除节点的操作一样
		head = head->next;
		free(temp);
	}
}

void TreeMaze::InsertData(Point data)
{
	this->data.InsertData(data.GetX(), data.GetY());                         //为数插入数据部分
}

Point TreeMaze::GetPoint(void)
{
	return Point(data.GetX(), data.GetY());                                  //返回数据部分
}

int TreeMaze::GetDepth(void)
{
	if (this->sonTree == NULL) {
		return 1;
	}
	else {
		int sumDepth = 0;
		for (int i = 0; i < this->sonTree->getNodeNumber(); ++i) {
			LNode *tempNode = this->sonTree->GetListNode(i);
			sumDepth += tempNode->data->GetDepth();
		}
		return sumDepth;
	}
	return 0;
}

LNode *TreeMaze::GetSonNode(int index)
{
	return sonTree->GetListNode(index);
}

void TreeMaze::SetSonTree(LinkList *sonTree)
{
	this->sonTree = sonTree;
}

int TreeMaze::GetSonNodeNumber(void)
{
	if (this->sonTree == NULL) {
		return 0;
	}else{
		return sonTree->getNodeNumber();
	}
}