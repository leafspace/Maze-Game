#pragma once
#include <iostream>
using namespace std;

class Point;
class LNode;
class LinkList;
class TreeMaze;

using ElemType = TreeMaze;                                                   //待修改

class Point                                                                  //设置迷宫中的每个点的数据结构
{
private:
	int x;                                                                   //从左向右依次为0-9的x轴数值
	int y;                                                                   //从上到下依次为0-9的y轴数值
public:
	Point(int tempX = 0, int tempY = 0) :x(tempX), y(tempY) {}               //可以直接为点初始化赋值，也可以默认为0数值
	~Point() {}                                                              //析构函数无操作
	void InsertData(int, int);                                               //将数据赋给对象
	int GetX(void);                                                          //做为函数接口，提供x值的返回方法
	int GetY(void);                                                          //做为函数接口，提供y值的返回方法
	void ClearData(void);                                                    //清除数据结构当中的内容
	friend bool operator ==(Point,Point);
};

class LNode                                                                  //表示链表中的每一个节点
{
public:
	ElemType *data;                                                          //每一个节点的数据项
	LNode *next;                                                             //指向链表的下一个节点
	LNode();
};

class LinkList                                                               //链表的数据结构（1.可行列 2.树的结点列）
{
private:
	LNode *head;                                                             //链表的头
	LNode *tail;                                                             //链表的表尾
	int nodeNumber;                                                          //节点的个数
public:
	LinkList() { head = tail = NULL; nodeNumber = 0; }                       //初始化表头表尾数据量
	~LinkList() {}
	int getNodeNumber();                                                     //获取可行点的个数
	void InsertData(Point);                                                  //向链表中插入一个节点（因为没有子树，所以只插入一个点）
	bool DeleteData(void);                                                   //删除链表中的一个节点
	bool DeleteData(Point);                                                  //删除链表中的指定一个节点
	int SearchNode(Point);
	LNode GetListNode(void);                                                 //返回头指针指向的第一个节点数据
	LNode *GetListNode(int);                                                  //返回指定位置上的节点
	void ShowList(void);                                                     //显示链表当中所有的节点的Point数值
	void ClearList(void);                                                    //清除表中所有的数据
};

class TreeMaze                                                               //一般树的存储结构
{
private:
	Point data;                                                              //树中的节点资源
	LinkList *sonTree;                                                       //当前结点的子节点们，为NULL表示此节点为叶子
public:
	TreeMaze() { sonTree = NULL; }                                                            //默认的构造函数
	TreeMaze(Point tempPoint) { data = tempPoint; sonTree = NULL; }
	~TreeMaze() {}
	
	/*树中的其余几个操作*/
	void InsertData(Point);                                                  //向树中插入数据部分
	Point GetPoint(void);                                                    //提取出当前数据点
	int GetDepth(void);                                                      //获取树的深度
	LNode *GetSonNode(int);
	void SetSonTree(LinkList*);
	int GetSonNodeNumber(void);
};