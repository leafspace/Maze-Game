#pragma once
#include "DataStruct_Header.h"

const int ARRAY_SIZE = 10;                                                   //�����ͼ�Ĵ�С
const char MAP[ARRAY_SIZE][ARRAY_SIZE] = {                                   //�����ͼ������
	{ '1','1','1','1','1','1','1','1','1','1' },
	{ '1','0','0','1','0','0','0','1','0','#' },
	{ '1','0','0','1','0','0','0','1','0','1' },
	{ '1','0','0','0','0','1','1','0','0','1' },
	{ '1','0','1','1','1','0','0','0','0','1' },
	{ '1','0','0','P','1','0','0','0','0','1' },
	{ '1','0','1','0','0','0','1','0','0','1' },
	{ '1','0','1','1','1','0','1','1','0','1' },
	{ '1','1','0','0','0','0','0','0','0','1' },
	{ '1','1','1','1','1','1','1','1','1','1' },
};


extern LinkList FeasibleList;                                                       //��ʾ�������ߵĵ���
extern TreeMaze LabyrinthTree;                                                      //����·����
extern Point CavalierPoint;                                                         //��ʿ���ڵ�λ��
extern Point PrincessPoint;                                                         //�������ڵ�λ��

bool InitMazeData(void);                                                     //��ʼ����Ҫ���������ڵ�
bool InitListData(void);                                                     //��ʼ�������������е���ֵ
bool InitTreeData(void);                                                     //��ʼ�����е�ֵ
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