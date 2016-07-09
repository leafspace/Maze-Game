#include "PublicResources_Header.h"

bool InitMazeData(void)
{
	int flagC = 0, flagP = 0;                                                //标识骑士与公主的点是否已经初始化
	for (int i = 0; i < ARRAY_SIZE; ++i) {                                   //扫描每一个点
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			if (MAP[i][j] == 'P') {
				CavalierPoint.InsertData(i, j);                              //初始化骑士点
				flagC = 1;
			}
			if (MAP[i][j] == '#') {
				PrincessPoint.InsertData(i, j);                              //初始化公主点
				flagP = 1;
			}
		}
	}
	if (flagC*flagP==0) {                                                    //如果骑士跟公主两个点当中有一个没有初始化完成
		return false;                                                        //初始化不成功
	}
	return true;
}

bool InitListData(void)
{
	for (int i = 0; i < ARRAY_SIZE; ++i) {                                   //扫描每一个点
		for (int j = 0; j < ARRAY_SIZE; ++j) {
			if (MAP[i][j] == '0') {                                          //如果为可以行走的点位
				FeasibleList.InsertData(Point(i, j));                        //插入可行点
			}
		}
	}
	FeasibleList.ShowList();
	//Test delete
	/*
	{
		FeasibleList.DeleteData();
		FeasibleList.DeleteData(Point(1, 1));
		FeasibleList.DeleteData(Point(1, 2));
		FeasibleList.DeleteData(Point(5, 6));
		FeasibleList.DeleteData(Point(8, 7));
		FeasibleList.DeleteData(Point(8, 8));
	}
	*/
	return true;
}

bool InitTreeData(void)
{
	while (FeasibleList.getNodeNumber()) {

	}
}


