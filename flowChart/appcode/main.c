#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <math.h>

#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "imgui.h"

#include <windows.h>
#include <olectl.h>
#include <stdio.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>

#include "draw.h"
#include "UI.h"
#include "operation.h"

/*�ı���Ϣ�ص�����*/
void CharEventProcess(char ch);
/*������Ϣ�ص�����*/
void KeyboardEventProcess(int key, int event);
/*�����Ϣ�ص�����*/
void MouseEventProcess(int x, int y, int button, int event);
/*ȫ��ˢ����ʾ*/
void display();

double tmpX, tmpY;/*��moveʱ������λ��dx��dy�ı���*/

static int click;/*��������ƴΣ�������bug*/
/*��������ʼ����һ��*/
void Main()
{
	SetWindowTitle("Flow Chart");/*���ô�������*/
	SetWindowSize(20,13);/*��λӢ��*/
	InitGraphics();/*��ʼ��ͼ�λ�����*/

	winWidth = GetWindowWidth();
	winHeight = GetWindowHeight();

	registerCharEvent(CharEventProcess);        /*ע���ַ���Ϣ*/
	registerKeyboardEvent(KeyboardEventProcess);/*ע�������Ϣ*/
	registerMouseEvent(MouseEventProcess);/*ע�������Ϣ*/

	initMenu();
	initButtomBar();

	/*����ͼ������ͷ��ʼ��ΪNULL*/
	rectangleHead = NULL;
	rRectangleHead = NULL;
	diamondHead = NULL;
	lineHead = NULL;
	arrowHead = NULL;
	dArrowHead = NULL;
	paraHead = NULL;
	circleHead = NULL;
	ovalHead = NULL;
}

void CharEventProcess(char ch)
{
	uiGetChar(ch); /*GUI�ַ�����*/
	display(); /*ˢ����ʾ*/
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); /*GUI��ȡ����*/
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);

	double curX = ScaleXInches(x);
	double curY = ScaleYInches(y);

	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)/*�����������¾ͼ�¼��ǰ���λ��*/
		{
			if (operation == selected && selectGraph(curX, curY) != 1)
			{
				operation = none;
			}
			if (operation == none || operation == selected)
			{
				if (selectGraph(curX, curY))
				{
					if (click == 0)click = 1;
					operation = selected;
					tmpX = curX;
					tmpY = curY;
					moveFlag = FALSE;
				}
			}
			if (operation == draw)
			{
				if (click == 0)click = 1;
				switch (type)
				{
				case ����:
					initRec(curX,curY);
					break;
				case Բ�Ǿ���:
					initRoundedRec(curX, curY);
					break;
				case ����:
					initDiam(curX,curY);
					break;
				case ֱ��:
					initLine(curX, curY);
					break;
				case �����ͷ:
					initArrow(curX, curY);
					break;
				case ˫���ͷ:
					initdArrow(curX, curY);
					break;
				case ƽ���ı���:
					initPara(curX, curY);
					break;
				case Բ��:
					initCircle(curX, curY);
					break;
				case ��Բ��:
					initOval(curX, curY);
					break;
				}
			}
		}
		break;
	case BUTTON_UP:
		if (button == LEFT_BUTTON)
		{
			if (operation == draw)
			{
				operation = none;
				click = 0;
			}
			else if (operation == selected && moveFlag == TRUE)
			{
				operation = selected;
				click = 0;
				//selectedGraph = NULL;/*ȡ��ѡ��*/
				moveFlag = FALSE;
			}
			else if (operation == selected && moveFlag == FALSE)
			{
				click = 0;
			}
		}
		break;
	case MOUSEMOVE:
		if (operation == draw && click == 1)
		{
			switch (type)
			{
			case ����:
				rectangleHead->data.endX = curX;/*����ƶ�ʱ����仯��ʵʱ�����괫������*/
				rectangleHead->data.endY = curY;
				break;
			case Բ�Ǿ���:
				rRectangleHead->data.endX = curX;
				rRectangleHead->data.endY = curY;
				break;
			case ����:
				diamondHead->data.endX = curX;
				diamondHead->data.endY = curY;
				break;
			case ֱ��:
				lineHead->data.endX = curX;
				lineHead->data.endY = curY;
				break;
			case �����ͷ:
				arrowHead->data.endX = curX;
				arrowHead->data.endY = curY;
				break;
			case ˫���ͷ:
				dArrowHead->data.endX = curX;
				dArrowHead->data.endY = curY;
				break;
			case ƽ���ı���:
				paraHead->data.endX = curX;
				paraHead->data.endY = curY;
				break;
			case Բ��:
				circleHead->data.radius = sqrt((curX - circleHead->data.startX) * (curX - circleHead->data.startX)+
					(curY - circleHead->data.startY) * (curY - circleHead->data.startY));
				break;
			case ��Բ��:
				ovalHead->data.xRadius = curX - ovalHead->data.startX;
				ovalHead->data.yRadius = curY - ovalHead->data.startY;
				break;
			}
		}

		if (operation == selected && click == 1)
		{
			double dx = curX - tmpX;
			double dy = curY - tmpY;
			moveGraph(dx, dy);
			/*��ջ���*/
			tmpX = curX;
			tmpY = curY;
			moveFlag = TRUE;
		}
		break;
	case ROLL_UP:
		if (operation == selected)
			enlargeGraphicSize();
		break;
	case ROLL_DOWN:
		if (operation == selected)
			reduceGraphicSize();
		break;
	}

	display();
}

/*ȫ��ˢ����ʾ*/
void display()
{
	DisplayClear();

	drawRec(rectangleHead);
	drawRoundedRec(rRectangleHead);
	drawDiam(diamondHead);
	drawLine(lineHead);
	drawArrow(arrowHead);
	drawdArrow(dArrowHead);
	drawPara(paraHead);
	drawCircle(circleHead);
	drawOval(ovalHead);

	initMenu();
	initButtomBar();
}
