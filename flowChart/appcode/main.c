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

/*文本消息回调函数*/
void CharEventProcess(char ch);
/*键盘消息回调函数*/
void KeyboardEventProcess(int key, int event);
/*鼠标消息回调函数*/
void MouseEventProcess(int x, int y, int button, int event);
/*全局刷新显示*/
void display();

double tmpX, tmpY;/*在move时用来算位移dx，dy的变量*/

static int click;/*给鼠标点击计次，否则有bug*/
/*主函数初始化仅一次*/
void Main()
{
	SetWindowTitle("Flow Chart");/*设置窗口名称*/
	SetWindowSize(20,13);/*单位英寸*/
	InitGraphics();/*初始化图形化窗口*/

	winWidth = GetWindowWidth();
	winHeight = GetWindowHeight();

	registerCharEvent(CharEventProcess);        /*注册字符信息*/
	registerKeyboardEvent(KeyboardEventProcess);/*注册键盘信息*/
	registerMouseEvent(MouseEventProcess);/*注册鼠标信息*/

	initMenu();
	initButtomBar();

	/*各个图形链表头初始化为NULL*/
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
	uiGetChar(ch); /*GUI字符输入*/
	display(); /*刷新显示*/
}

void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); /*GUI获取键盘*/
}

void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event);

	double curX = ScaleXInches(x);
	double curY = ScaleYInches(y);

	switch (event)
	{
	case BUTTON_DOWN:
		if (button == LEFT_BUTTON)/*如果是左键按下就记录当前鼠标位置*/
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
				case 矩形:
					initRec(curX,curY);
					break;
				case 圆角矩形:
					initRoundedRec(curX, curY);
					break;
				case 菱形:
					initDiam(curX,curY);
					break;
				case 直线:
					initLine(curX, curY);
					break;
				case 单向箭头:
					initArrow(curX, curY);
					break;
				case 双向箭头:
					initdArrow(curX, curY);
					break;
				case 平行四边形:
					initPara(curX, curY);
					break;
				case 圆形:
					initCircle(curX, curY);
					break;
				case 椭圆形:
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
				//selectedGraph = NULL;/*取消选中*/
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
			case 矩形:
				rectangleHead->data.endX = curX;/*鼠标移动时坐标变化，实时将坐标传入链表*/
				rectangleHead->data.endY = curY;
				break;
			case 圆角矩形:
				rRectangleHead->data.endX = curX;
				rRectangleHead->data.endY = curY;
				break;
			case 菱形:
				diamondHead->data.endX = curX;
				diamondHead->data.endY = curY;
				break;
			case 直线:
				lineHead->data.endX = curX;
				lineHead->data.endY = curY;
				break;
			case 单向箭头:
				arrowHead->data.endX = curX;
				arrowHead->data.endY = curY;
				break;
			case 双向箭头:
				dArrowHead->data.endX = curX;
				dArrowHead->data.endY = curY;
				break;
			case 平行四边形:
				paraHead->data.endX = curX;
				paraHead->data.endY = curY;
				break;
			case 圆形:
				circleHead->data.radius = sqrt((curX - circleHead->data.startX) * (curX - circleHead->data.startX)+
					(curY - circleHead->data.startY) * (curY - circleHead->data.startY));
				break;
			case 椭圆形:
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
			/*清空缓冲*/
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

/*全局刷新显示*/
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
