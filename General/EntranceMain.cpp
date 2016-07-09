#include "Header.h"

int main()
{
	Point bishop, gateway;                                                         //定义棋子跟门的位置
	if (!InitPoint(&bishop, &gateway)) {                                           //将棋子跟门的位置找到
		printf("ERROR ! Could not find elements !\n");                             //点没有初始化成功
		exit(-1);                                                                  //如果没有初始化成功那么就无法进行下去
	}
	else {
		printf("Initialize the point OK !\n");                                     //初始化点成功了
	}
	SqStack stepStack;                                                             //定义栈
	if (!stepStack.InitStack()) {                                                  //栈初始化
		printf("ERROR ! Stack initialization failed !\n");                         //初始化栈失败了
	}
	else {
		printf("Initialize Stack the OK !\n");                                     //初始化栈成功
	}
	if (DisposeKeyWalk(&stepStack, &bishop, &gateway) == false) {                  //寻找路径
		printf("No path can perform !\n");                                         //没有路径能走
	}
	else{
		printf("We have find the way !\n\n\n");

		printf("================================================================================\n\n");

		ElemType *temp = (ElemType*)malloc(sizeof(ElemType)*stepStack.StackLength());
		int i;
		for (i = 0; !stepStack.StackEmpty(); ++i) {
			stepStack.Pop(&temp[i]);
		}
		printf("[%d,%d]", bishop.X, bishop.Y);
		do {
			i--;
			switch (temp[i])
			{
			case 'W': bishop.Y--; break;                                           //向上走
			case 'A': bishop.X--; break;                                           //向左走
			case 'S': bishop.Y++; break;                                           //向下走
			case 'D': bishop.X++; break;                                           //向右走
			default:break;
			}
			printf("->[%d,%d]",bishop.X,bishop.Y);
		} while (i);
	}
	printf("\n\n");
	return 0;
}
