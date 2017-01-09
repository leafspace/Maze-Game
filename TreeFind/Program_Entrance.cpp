#include "PublicResources_Header.h"

LinkList FeasibleList;                                                       //表示可以行走的点列
TreeMaze LabyrinthTree;                                                      //行走路线树
Point CavalierPoint;                                                         //骑士所在的位置
Point PrincessPoint;                                                         //公主所在的位置
TreeMaze FindPrincess;                                                       //找到公主的方法

int main()
{
	if (!InitMazeData()) {
		cout << "This map has problem , please check the map!" << endl;
		exit(-1);
	}
	else {
		cout << "This map init ok!" << endl;
	}
	InitListData();
	LabyrinthTree.InsertData(CavalierPoint);
	InitTreeData();

	cout << "[" << PrincessPoint.GetX() << "," << PrincessPoint.GetY() << "]";
	ShowWay(&LabyrinthTree);
	cout << "<-[" << CavalierPoint.GetX() << "," << CavalierPoint.GetY() << "]";
	return 0;
}