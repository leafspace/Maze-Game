#pragma once
//#include <cctype>
#include <stdio.h>                                                             //用以支持基础IO操作
#include <stdlib.h>                                                            //用以支持内存分配操作
#include <string.h>                                                            //用以支持字符串操作
#define OK 1                                                                   //设置Stack的bool类返回
#define ERROR 0                                                                //设置Stack的bool类返回
#define MAX_SIZE 80                                                            //标定stack的最大存储值
#define STACK_INT_SIZE 10                                                      //设置Stack的初始大小
#define STACKINCREMENT 5                                                       //设置Stack的扩展大小
#define ARRAY_SIZE 10                                                          //设置地图的大小
typedef char ElemType;                                                         //标定Stack中存储内容的类型

const char Map[ARRAY_SIZE][ARRAY_SIZE] = {                                     //设置地图中的内容
	{ '1','1','1','1','1','1','1','1','1','1' },
	{ '1','0','1','1','0','0','0','1','0','#' },
	{ '1','0','1','1','0','1','1','1','0','1' },
	{ '1','0','0','0','0','1','1','1','0','1' },
	{ '1','0','1','1','1','0','0','0','0','1' },
	{ '1','0','0','P','1','0','1','1','0','1' },
	{ '1','0','1','0','0','0','1','1','0','1' },
	{ '1','0','1','1','1','0','1','1','0','1' },
	{ '1','1','0','0','0','0','0','0','0','1' },
	{ '1','1','1','1','1','1','1','1','1','1' },
};

class SqStack                                                                  //Stack类的定义
{
private:
	ElemType *base;                                                            //栈底位置值
	ElemType *top;                                                             //设置栈顶位置值
	int stacksize;                                                             //表示栈当前存在内容的个数
public:
	int InitStack(void);                                                       //初始化栈
	int ClearStack(void);                                                      //清空栈
	int StackEmpty(void);                                                      //判断栈是否为空
	int StackLength(void);                                                     //返回栈的元素个数
	int Push(ElemType e);                                                      //压入内容
	int Pop(ElemType *e);                                                      //弹出内容
	int GetTop(ElemType *e);                                                   //返回栈顶内容
	void ShowStack(void);                                                      //输出栈中所有的元素
};

typedef struct Point                                                           //点结构的定义
{
	int X = 0;                                                                 //横坐标的值
	int Y = 0;                                                                 //纵坐标的值
}Point;

bool InitPoint(Point *, Point *);                                              //初始化棋子跟门口的位置
char PointWalk(SqStack *, Point *);                                            //描述退后一步的操作
char PointWalk(SqStack *, Point *,char);                                       //描述前进一步的操作
char JudgeStep(SqStack *, Point *, char);
bool JudgeStepBack(char , char);
bool JudgeStepDoable(Point , char );
bool DisposeKeyWalk(SqStack *, Point *, Point *);