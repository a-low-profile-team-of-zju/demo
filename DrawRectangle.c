#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

typedef struct /*创建矩形参数的结构体*/
{
	double clickX, clickY;
	double finalX, finalY;
	double angle;
} rectangle;

typedef struct /*创建矩形链表*/
{
	rectangle rect;
	struct recNode* pNext;
}recNode;

typedef recNode* rectangleNode;

rectangleNode rectangleHead=NULL;/*矩形链表的头结点*/

void DrawRectangle(rectangleNode recHead);/*绘制矩形*/
void MouseEventProcess(int x, int y, int button, int event);/*鼠标消息回调函数*/
void display();/*全局刷新显示*/


void Main()/*主函数初始化仅一次*/
{
	InitGraphics();/*初始化图形化窗口*/

	registerMouseEvent(MouseEventProcess);/*注册鼠标信息*/

	SetWindowTitle("Draw Rectangle");/*设置窗口名称*/

	SetPenColor("Red");/*画笔参数*/
	SetPenSize(1);
}

void DrawRectangle(rectangleNode recHead)
{
	while (recHead)
	{
		MovePen(recHead->rect.clickX,recHead->rect.clickY);                           /*绘制矩形的四条边*/
		DrawLine(0,recHead->rect.finalY-recHead->rect.clickY);
		DrawLine(recHead->rect.finalX - recHead->rect.clickX, 0);

		MovePen(recHead->rect.clickX, recHead->rect.clickY);                           
		DrawLine(recHead->rect.finalX - recHead->rect.clickX, 0);
		DrawLine(0, recHead->rect.finalY - recHead->rect.clickY);

		recHead = recHead->pNext;/*链表后移*/
	}
}

void MouseEventProcess(int x, int y, int button, int event)
{
	rectangleNode tmp = (rectangleNode)malloc(sizeof(recNode));/*创建一个临时的节点，用来加入链表的头*/

	static bool isRecord = FALSE;/*isRecord表示是否继续记录该矩形的信息到链表中*/

	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)/*如果是左键按下就记录当前鼠标位置*/
		{
			isRecord = TRUE;/*允许绘制图像*/
			rectangle Data;/*一个临时的结构体，用来暂存当前的矩形信息*/
			Data.clickX = ScaleXInches(x);/*把鼠标点击的坐标存入Data结构体*/
			Data.clickY = ScaleYInches(y);
			Data.finalX = ScaleXInches(x);
			Data.finalY = ScaleYInches(y);
			Data.angle = 0;/*默认初始角度为0*/

			
			tmp->rect.clickX = Data.clickX;/*把Data中的信息传入临时节点tmp*/
			tmp->rect.clickY = Data.clickY;
			tmp->rect.finalX = Data.finalX;
			tmp->rect.finalY = Data.finalY;
			tmp->rect.angle = Data.angle;
			tmp->pNext = NULL;

			if (rectangleHead == NULL)/*判断当前链表的头结点是否为空*/
				rectangleHead = tmp;
			else
			{
				tmp->pNext = rectangleHead;
				rectangleHead = tmp;
			}
		}
		break;
	case BUTTON_UP:
		if (button == LEFT_BUTTON)/*如果是左键按下就记录当前鼠标位置*/
		{
			isRecord = FALSE;
			free(tmp);
			display();
		}
		break;
	case MOUSEMOVE:
		if (isRecord)
		{
			rectangleHead->rect.finalX = ScaleXInches(x);/*因为鼠标移动时坐标变化，需实时将坐标传入链表*/
			rectangleHead->rect.finalY = ScaleYInches(y);
			display();
		}
		break;
	}
}

void display()
{
	DisplayClear();/*清屏*/

	DrawRectangle(rectangleHead);/*目前仅有画矩形的函数*/
}