#pragma once
#include "DataStruct_Header.h"

extern int ARRAY_SIZE;
extern char **MAP;

extern LinkList FeasibleList;                                                       //表示可以行走的点列
extern TreeMaze LabyrinthTree;                                                      //行走路线树
extern Point CavalierPoint;                                                         //骑士所在的位置
extern Point PrincessPoint;                                                         //公主所在的位置
extern TreeMaze FindPrincess;
extern CString walkWay;

bool InitMazeData(void);                                                     //初始化重要的人物所在点
bool InitListData(void);                                                     //初始化可行列链表中的数值
bool InitTreeData(void);                                                     //初始化树中的值
LinkList *FindSonWay(Point);
bool ShowWay(TreeMaze*);
bool DoMaze(void);


/*
##########
#  #   # 0
#  #   # #
#    ##  #
# ###    #
#  P#    #
# #   #  #
# ### ## #
##       #
##########

 '#''#''#''#''#''#''#''#''#''#' 
 '#'' '' ''#'' '' '' ''#'' ''Q' 
 '#'' '' ''#'' '' '' ''#'' ''#' 
 '#'' '' '' '' ''#''#'' '' ''#' 
 '#'' ''#''#''#'' '' '' '' ''#' 
 '#'' '' ''P''#'' '' '' '' ''#' 
 '#'' ''#'' '' '' ''#'' '' ''#' 
 '#'' ''#''#''#'' ''#''#'' ''#' 
 '#''#'' '' '' '' '' '' '' ''#' 
 '#''#''#''#''#''#''#''#''#''#' 

*/