#include "Header.h"
bool InitPoint(Point *bishop, Point *gateway)                                  //初始化棋子跟门口的位置
{
	int flagBishop = 0, flagGateway = 0;                                       //定义有没有找到点的标志
	for (int i = 0; i < ARRAY_SIZE; ++i) {                                     //对地图中所有点的扫描操作
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			switch (Map[i][j])                                                 //判断点来确定要执行什么操作
			{
			case 'P':
			case 'p': bishop->X = j; bishop->Y = i; flagBishop++; break;       //保存棋子的位置并设置标志
			case '#': gateway->X = j; gateway->Y = i; flagGateway++; break;    //保存门的位置并设置标志
			default:break;
			}
			if (flagBishop == 1 && flagGateway == 1) {                         //如果标志都成功了，那么函数返回成功
				return OK;
			}
		}
	}
	return ERROR;                                                              //如果到最后标志都没有全部设置完毕，那么函数初始化无效
}
char PointWalk(SqStack *stepStack, Point *standPerson)                         //描述退后一步的操作
{
	char step;                                                                 //此用来描述前面一次前进所进行的方向
	if (!stepStack->Pop(&step)) {                                              //弹出刚刚进行的方向
		printf("Stack ERROR! \n");                                             //栈出错，栈出错只有一种情况，就是栈底没有数值
		step = 'B';                                                            //返回B
	}
	/*=================================================*/
	printf("pop %c\n", step);
	/*=================================================*/
	switch (step)                                                              //如果前面有步骤的话，就按照下面的方式去计算
	{
	case 'W': standPerson->Y++; break;                                         //前一步骤是向上
	case 'A': standPerson->X++; break;                                         //前一步骤是向左
	case 'S': standPerson->Y--; break;                                         //前一步骤是向下
	case 'D': standPerson->X--; break;                                         //前一步骤是向右
	default:break;
	}
	return step;                                                               //如果是B，则栈已经为空
}
char PointWalk(SqStack *stepStack, Point *standPerson, char step)              //描述前进一步的操作
{
	step = JudgeStep(stepStack, standPerson, step);                            //对即将要走的步伐进行判断，这边返回会出现WASDB五种情况的路径
	switch (step)                                                              //根据下一步可以行走的步子，我们可以对其进行判断性操作
	{
	case 'W': standPerson->Y--; break;                                         //向上走
	case 'A': standPerson->X--; break;                                         //向左走
	case 'S': standPerson->Y++; break;                                         //向下走
	case 'D': standPerson->X++; break;                                         //向右走
	case 'B': step = PointWalk(stepStack, standPerson);                        //如果此时要后退了，执行后退步子操作
		if (step == 'B') {
			return 'B';
		}
		/*这个时候应该按照前面走过的方向看看下一个方向是什么*/
		return step;
		/*有问题！！！！*/


	default: printf("Judge step ERROR! \n"); exit(-1); break;                  //如果出现了其他情况，则判断失误
	}
	/*=================================================*/
	printf("push %c\n",step);
	/*=================================================*/
	stepStack->Push(step);                                                     //将现在走的一步放入栈中
	return 'N';
}
char JudgeStep(SqStack *stepStack, Point *standPerson, char step)
{
	char stepTemp[7] = "NAWDSB";                                               //定义走路方向的顺序
	char stepSave;
	stepStack->GetTop(&stepSave);
	//描述的是根据之前走过的步子，来判断下一个要走的是什么步子，并返回
	//定义这是一个新的步子，step=‘N’
	//B为当前所有可以走的步子已经走完了，需要退后一步了
	//=============================================================
	//要知道从原来走到这一步是怎么走的，然后就不能从那个地方回去,也就是不能等于堆栈最上面的那个
	//judge还要做正确可能性的判断
	for (int i = 0; i < 5; ++i) {                                              //从前往后扫描
		//1.确定这个方向是可以走的
		//2.确定这个方向不是刚才上来的相反方向
		//3.确定这个方向不是N的错误方向
		//4.确定这个方向是满足顺序的
		if (step == stepTemp[i]) {                                             //找到刚才走的方向
			step = stepTemp[i + 1];                                            //依旧原方向无法行走，过度到下一个方向
			if (JudgeStepBack(stepSave, step) ||                               //这新方向不能与原方向相反
				JudgeStepDoable(*standPerson, step)) {                         //看看前面的路是否是阻挡
				continue;                                                      //如果满足上述条件，则此路不通，继续下一个方向
			}
			else {                                                             //如果此方向是可行的，则退出
				break;
			}
		}
	}
	if (step == 'N') {                                                         //出现的错误判断，一般这是不可能的
		printf("Judge ERRPR! \n");
		exit(-1);                                                              //再次出现N，则程序将终止
	}
	return step;                                                               //返回可以行走的方向
}
bool JudgeStepBack(char stepBefore, char stepAfter)
{
	if (stepBefore == 'W'&&stepAfter == 'S' ||                                 //不能是相反方向
		stepBefore == 'S'&&stepAfter == 'W' ||                                 //不能是相反方向
		stepBefore == 'A'&&stepAfter == 'D' ||                                 //不能是相反方向
		stepBefore == 'D'&&stepAfter == 'A') {                                 //不能是相反方向
		return true;
	}
	else{
		return false;
	}
}
bool JudgeStepDoable(Point standPerson, char step)                             //standPerson传入数值，所以当中对其的数值操作，对原数据没有影响
{
	switch (step)                                                              //数值行走
	{
	case 'W': standPerson.Y--; break;
	case 'A': standPerson.X--; break;
	case 'S': standPerson.Y++; break;
	case 'D': standPerson.X++; break;
	}
	if (Map[standPerson.Y][standPerson.X] == '1') {                            //遇到墙了
		return true;
	}
	else {
		return false;
	}
}
bool DisposeKeyWalk(SqStack *stepStack, Point *bishop, Point *gateway)         //走路的循环
{
	Point bishopWalk = *bishop;
	char step = 'N';
	while (true) {
		if (step == 'B'&&stepStack->StackEmpty()) {
			return false;
		}
		//PointWalk中使用的是上一次走过的路子。   然后将本次走的路子返回记录，然后用作下一次的使用
		step = PointWalk(stepStack, &bishopWalk, step);
		printf("[%d,%d]\n",bishopWalk.X,bishopWalk.Y);
		stepStack->ShowStack();
		if (bishopWalk.X == gateway->X&&bishopWalk.Y == gateway->Y) {
			break;
		}
	}
	return true;
}