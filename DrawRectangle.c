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

typedef struct /*�������β����Ľṹ��*/
{
	double clickX, clickY;
	double finalX, finalY;
	double angle;
} rectangle;

typedef struct /*������������*/
{
	rectangle rect;
	struct recNode* pNext;
}recNode;

typedef recNode* rectangleNode;

rectangleNode rectangleHead=NULL;/*���������ͷ���*/

void DrawRectangle(rectangleNode recHead);/*���ƾ���*/
void MouseEventProcess(int x, int y, int button, int event);/*�����Ϣ�ص�����*/
void display();/*ȫ��ˢ����ʾ*/


void Main()/*��������ʼ����һ��*/
{
	InitGraphics();/*��ʼ��ͼ�λ�����*/

	registerMouseEvent(MouseEventProcess);/*ע�������Ϣ*/

	SetWindowTitle("Draw Rectangle");/*���ô�������*/

	SetPenColor("Red");/*���ʲ���*/
	SetPenSize(1);
}

void DrawRectangle(rectangleNode recHead)
{
	while (recHead)
	{
		MovePen(recHead->rect.clickX,recHead->rect.clickY);                           /*���ƾ��ε�������*/
		DrawLine(0,recHead->rect.finalY-recHead->rect.clickY);
		DrawLine(recHead->rect.finalX - recHead->rect.clickX, 0);

		MovePen(recHead->rect.clickX, recHead->rect.clickY);                           
		DrawLine(recHead->rect.finalX - recHead->rect.clickX, 0);
		DrawLine(0, recHead->rect.finalY - recHead->rect.clickY);

		recHead = recHead->pNext;/*�������*/
	}
}

void MouseEventProcess(int x, int y, int button, int event)
{
	rectangleNode tmp = (rectangleNode)malloc(sizeof(recNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/

	static bool isRecord = FALSE;/*isRecord��ʾ�Ƿ������¼�þ��ε���Ϣ��������*/

	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)/*�����������¾ͼ�¼��ǰ���λ��*/
		{
			isRecord = TRUE;/*�������ͼ��*/
			rectangle Data;/*һ����ʱ�Ľṹ�壬�����ݴ浱ǰ�ľ�����Ϣ*/
			Data.clickX = ScaleXInches(x);/*����������������Data�ṹ��*/
			Data.clickY = ScaleYInches(y);
			Data.finalX = ScaleXInches(x);
			Data.finalY = ScaleYInches(y);
			Data.angle = 0;/*Ĭ�ϳ�ʼ�Ƕ�Ϊ0*/

			
			tmp->rect.clickX = Data.clickX;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
			tmp->rect.clickY = Data.clickY;
			tmp->rect.finalX = Data.finalX;
			tmp->rect.finalY = Data.finalY;
			tmp->rect.angle = Data.angle;
			tmp->pNext = NULL;

			if (rectangleHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
				rectangleHead = tmp;
			else
			{
				tmp->pNext = rectangleHead;
				rectangleHead = tmp;
			}
		}
		break;
	case BUTTON_UP:
		if (button == LEFT_BUTTON)/*�����������¾ͼ�¼��ǰ���λ��*/
		{
			isRecord = FALSE;
			free(tmp);
			display();
		}
		break;
	case MOUSEMOVE:
		if (isRecord)
		{
			rectangleHead->rect.finalX = ScaleXInches(x);/*��Ϊ����ƶ�ʱ����仯����ʵʱ�����괫������*/
			rectangleHead->rect.finalY = ScaleYInches(y);
			display();
		}
		break;
	}
}

void display()
{
	DisplayClear();/*����*/

	DrawRectangle(rectangleHead);/*Ŀǰ���л����εĺ���*/
}