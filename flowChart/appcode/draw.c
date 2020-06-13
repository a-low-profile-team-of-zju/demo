#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#define _USE_MATH_DEFINES
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

double selectedDx = 0.2; /*选中框的左上角偏移量*/
double selectedDy = 0.2;

/*--------------------------------------------------------------------------------------矩形绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个矩形链表节点并插入链表头部*/
void initRec(double x,double y)
{
	rectangleNode tmp = (rectangleNode)malloc(sizeof(recNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (rectangleHead == NULL)/*判断当前链表的头结点是否为空*/
		rectangleHead = tmp;
	else
	{
		tmp->pNext = rectangleHead;
		rectangleHead = tmp;
	}
}

/*绘制矩形带文本*/
void drawRec(rectangleNode recHead)
{
	rectangleNode tmp;
	tmp = recHead;

	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = tmp->data.endX - tmp->data.startX;
			double h = tmp->data.endY - tmp->data.startY;
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - selectedDx : tmp->data.startX + selectedDx, h >= 0 ? tmp->data.startY - selectedDy : tmp->data.startY + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		if (tmp->data.fillFlag) StartFilledRegion(1);
			/*画边框*/
			MovePen(tmp->data.startX, tmp->data.startY);               
			DrawLine(0, tmp->data.endY - tmp->data.startY);
			DrawLine(tmp->data.endX - tmp->data.startX, 0);
			DrawLine(0, -tmp->data.endY + tmp->data.startY);
			DrawLine(-tmp->data.endX + tmp->data.startX, 0);
		if (tmp->data.fillFlag) EndFilledRegion();

			/*写文本*/
			if(fabs(tmp->data.endX - tmp->data.startX)>TextStringWidth(tmp->data.text) && 
				fabs(tmp->data.endY - tmp->data.startY) > GetFontAscent(tmp->data.text))/*判断框的大小是否比文本大，否则不输出*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
					(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
					tmp->data.text);
			}

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------圆角矩形绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个圆角矩形链表节点并插入链表头部*/
void initRoundedRec(double x, double y)
{
	rRectangleNode tmp = (rRectangleNode)malloc(sizeof(roundedRecNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (rRectangleHead == NULL)/*判断当前链表的头结点是否为空*/
		rRectangleHead = tmp;
	else
	{
		tmp->pNext = rRectangleHead;
		rRectangleHead = tmp;
	}
}

/*绘制圆角矩形带文本*/
void drawRoundedRec(rRectangleNode roundedRecHead)
{
	rRectangleNode tmp;
	tmp = roundedRecHead;
	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = tmp->data.endX - tmp->data.startX;
			double h = tmp->data.endY - tmp->data.startY;
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - selectedDx : tmp->data.startX + selectedDx, h >= 0 ? tmp->data.startY - selectedDy : tmp->data.startY + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		double width = tmp->data.endX - tmp->data.startX;
		double height = tmp->data.endY - tmp->data.startY;
			if (width * height<=0)/*保证鼠标往4个方向拖动时画的图形正常*/
			{
				if (tmp->data.fillFlag) StartFilledRegion(1);
				/*画边框*/
				MovePen(tmp->data.startX + width *5 / 6, tmp->data.startY);
				DrawLine(-width * 2 / 3, 0);
				DrawEllipticalArc(width / 6, -height / 6, 90, 90);
				DrawLine(0, height * 2 / 3);
				DrawEllipticalArc(width / 6, -height / 6, 180, 90);
				DrawLine(width * 2 / 3, 0);
				DrawEllipticalArc(width / 6, -height / 6, 270, 90);
				DrawLine(0, -height * 2 / 3);
				DrawEllipticalArc(width / 6, -height / 6, 360, 90);
				if (tmp->data.fillFlag) EndFilledRegion();

				/*写文本*/
				if (fabs(width) > TextStringWidth(tmp->data.text) &&
					fabs(height) > GetFontAscent(tmp->data.text))/*判断框的大小是否比文本大，否则不输出*/
				{
					SetPenColor(tmp->data.textColor);
					drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
						(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
						tmp->data.text);
				}
			}
			else
			{
				if (tmp->data.fillFlag) StartFilledRegion(1);
				/*画边框*/
				MovePen(tmp->data.startX + width / 6, tmp->data.startY);
				DrawLine(width * 2 / 3, 0);
				DrawEllipticalArc(width / 6, height / 6, -90, 90);
				DrawLine(0, height * 2 / 3);
				DrawEllipticalArc(width / 6, height / 6, 0, 90);
				DrawLine(-width * 2 / 3, 0);
				DrawEllipticalArc(width / 6, height / 6, 90, 90);
				DrawLine(0, -height * 2 / 3);
				DrawEllipticalArc(width / 6, height / 6, 180, 90);
				if (tmp->data.fillFlag) EndFilledRegion();

				/*写文本*/
				if (fabs(width) > TextStringWidth(tmp->data.text) &&
					fabs(height) > GetFontAscent(tmp->data.text))/*判断框的大小是否比文本大，否则不输出*/
				{
					SetPenColor(tmp->data.textColor);
					drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
						(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
						tmp->data.text);
				}
			}

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------菱形绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个菱形链表节点并插入链表头部*/
void initDiam(double x, double y)
{
	diamNode tmp = (diamNode)malloc(sizeof(diamondNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (diamondHead == NULL)/*判断当前链表的头结点是否为空*/
		diamondHead = tmp;
	else
	{
		tmp->pNext = diamondHead;
		diamondHead = tmp;
	}
}

/*绘制菱形带文本*/
void drawDiam(diamNode diamondHead)
{
	diamNode tmp;
	tmp = diamondHead;
	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = tmp->data.endX - tmp->data.startX;
			double h = tmp->data.endY - tmp->data.startY;
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - selectedDx : tmp->data.startX + selectedDx, h >= 0 ? tmp->data.startY - selectedDy : tmp->data.startY + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		if (tmp->data.fillFlag) StartFilledRegion(1);
			/*画边框*/
			MovePen((tmp->data.startX+tmp->data.endX)/2, tmp->data.startY);
			DrawLine((tmp->data.endX-tmp->data.startX)/2, (tmp->data.endY - tmp->data.startY)/2);
			DrawLine(-(tmp->data.endX - tmp->data.startX) / 2, (tmp->data.endY - tmp->data.startY) / 2);
			DrawLine(-(tmp->data.endX - tmp->data.startX) / 2, -(tmp->data.endY - tmp->data.startY) / 2);
			DrawLine((tmp->data.endX - tmp->data.startX) / 2, -(tmp->data.endY - tmp->data.startY) / 2);
		if (tmp->data.fillFlag) EndFilledRegion();

			/*写文本*/
			if (fabs(tmp->data.endX - tmp->data.startX) > TextStringWidth(tmp->data.text) &&
				fabs(tmp->data.endY - tmp->data.startY) > GetFontAscent(tmp->data.text))/*判断框的大小是否比文本大，否则不输出*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
					(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
					tmp->data.text);
			}
		

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------直线绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个直线链表节点并插入链表头部*/
void initLine(double x, double y)
{
	lineNode tmp = (lineNode)malloc(sizeof(lNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	strcpy(tmp->data.fillColor, defaultFillColor);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (lineHead == NULL)/*判断当前链表的头结点是否为空*/
		lineHead = tmp;
	else
	{
		tmp->pNext = lineHead;
		lineHead = tmp;
	}
}

/*绘制直线*/
void drawLine(lineNode lineHead)
{
	lineNode tmp;
	tmp = lineHead;
	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = tmp->data.endX - tmp->data.startX;
			double h = tmp->data.endY - tmp->data.startY;
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - selectedDx : tmp->data.startX + selectedDx, h >= 0 ? tmp->data.startY - selectedDy : tmp->data.startY + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		/*画边框*/
		MovePen(tmp->data.startX, tmp->data.startY);
		DrawLine(tmp->data.endX - tmp->data.startX, tmp->data.endY - tmp->data.startY);

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------单向箭头绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个单向箭头链表节点并插入链表头部*/
void initArrow(double x, double y)
{
	arrowNode tmp = (arrowNode)malloc(sizeof(aNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	strcpy(tmp->data.fillColor, defaultFillColor);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (arrowHead == NULL)/*判断当前链表的头结点是否为空*/
		arrowHead = tmp;
	else
	{
		tmp->pNext = arrowHead;
		arrowHead = tmp;
	}
}

/*绘制单向箭头*/
void drawArrow(arrowNode arrowHead)
{
	arrowNode tmp;
	tmp = arrowHead;
	double angle = 15;   /*顶角 30°，可修改*/
	double waist = 0.3;/*箭头边长*/
	
	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = tmp->data.endX - tmp->data.startX;
			double h = tmp->data.endY - tmp->data.startY;
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - selectedDx : tmp->data.startX + selectedDx, h >= 0 ? tmp->data.startY - selectedDy : tmp->data.startY + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		double width = tmp->data.endX - tmp->data.startX;
		double height = tmp->data.endY - tmp->data.startY;
		double length = sqrt(width * width + height * height);
		double alpha = atan2(width, height);/*atan2()是个好东西*/
		double sina = height / length;
		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		/*画直线*/
		MovePen(tmp->data.startX, tmp->data.startY);
		DrawLine(tmp->data.endX - tmp->data.startX, tmp->data.endY - tmp->data.startY);
		/*画箭头,如果直线短于1.5倍waist太短就不画了*/
		if (length > 1.5 * waist)
		{
			DrawLine(waist * sin(alpha - angle), waist * cos(alpha - angle));
			MovePen(tmp->data.endX,tmp->data.endY);
			DrawLine(waist * sin(alpha + angle), waist * cos(alpha + angle));
		}

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------双向箭头绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个双向箭头链表节点并插入链表头部*/
void initdArrow(double x, double y)
{
	dArrowNode tmp = (dArrowNode)malloc(sizeof(daNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	strcpy(tmp->data.fillColor, defaultFillColor);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (dArrowHead == NULL)/*判断当前链表的头结点是否为空*/
		dArrowHead = tmp;
	else
	{
		tmp->pNext = dArrowHead;
		dArrowHead = tmp;
	}
}

/*绘制双向箭头*/
void drawdArrow(dArrowNode dArrowHead)
{
	dArrowNode tmp;
	tmp = dArrowHead;
	double angle = 15;   /*顶角 30°，可修改*/
	double waist = 0.3;/*箭头边长*/

	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = tmp->data.endX - tmp->data.startX;
			double h = tmp->data.endY - tmp->data.startY;
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - selectedDx : tmp->data.startX + selectedDx, h >= 0 ? tmp->data.startY - selectedDy : tmp->data.startY + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		double width = tmp->data.endX - tmp->data.startX;
		double height = tmp->data.endY - tmp->data.startY;
		double length = sqrt(width * width + height * height);
		double alpha = atan2(width, height);/*atan2()是个好东西*/
		double sina = height / length;
		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		/*画直线*/
		MovePen(tmp->data.startX, tmp->data.startY);
		DrawLine(tmp->data.endX - tmp->data.startX, tmp->data.endY - tmp->data.startY);
		/*画箭头,如果直线短于3倍waist太短就不画了*/
		if (length > 3 * waist)
		{
			/*末箭头*/
			DrawLine(waist * sin(alpha - angle), waist * cos(alpha - angle));
			MovePen(tmp->data.endX, tmp->data.endY);
			DrawLine(waist * sin(alpha + angle), waist * cos(alpha + angle));
			/*头箭头*/
			MovePen(tmp->data.startX, tmp->data.startY);
			DrawLine(-waist * sin(alpha - angle), -waist * cos(alpha - angle));
			MovePen(tmp->data.startX, tmp->data.startY);
			DrawLine(-waist * sin(alpha + angle), -waist * cos(alpha + angle));
		}

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------平行四边形绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个平行四边形链表节点并插入链表头部*/
void initPara(double x, double y)
{
	paraNode tmp = (paraNode)malloc(sizeof(pNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (paraHead == NULL)/*判断当前链表的头结点是否为空*/
		paraHead = tmp;
	else
	{
		tmp->pNext = paraHead;
		paraHead = tmp;
	}
}

/*绘制平行四边形带文本*/
void drawPara(paraNode paraHead)
{
	paraNode tmp;
	tmp = paraHead;
	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = tmp->data.endX - tmp->data.startX;
			double h = tmp->data.endY - tmp->data.startY;
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - selectedDx : tmp->data.startX + selectedDx, h >= 0 ? tmp->data.startY - selectedDy: tmp->data.startY + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		if (tmp->data.fillFlag) StartFilledRegion(1);
			/*画边框*/
			MovePen(tmp->data.startX, tmp->data.startY);
			DrawLine((tmp->data.endX - tmp->data.startX) * 0.8, 0);/*平行四边形上下底边长为0.8倍的鼠标水平移动距离*/
			DrawLine((tmp->data.endX - tmp->data.startX) * 0.2, tmp->data.endY-tmp->data.startY);
			DrawLine(-(tmp->data.endX - tmp->data.startX) * 0.8, 0);
			DrawLine(-(tmp->data.endX - tmp->data.startX) * 0.2, -(tmp->data.endY - tmp->data.startY));
		if (tmp->data.fillFlag) EndFilledRegion();

			/*写文本*/
			if (fabs(tmp->data.endX - tmp->data.startX)*0.8 > TextStringWidth(tmp->data.text) &&
				fabs(tmp->data.endY - tmp->data.startY) > GetFontAscent(tmp->data.text))/*判断框的大小是否比文本大，否则不输出*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
					(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
					tmp->data.text);
		    }

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------圆形绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个圆形链表节点并插入链表头部*/
void initCircle(double x, double y)
{
	circleNode tmp = (circleNode)malloc(sizeof(cNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.radius = 0;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (circleHead == NULL)/*判断当前链表的头结点是否为空*/
		circleHead = tmp;
	else
	{
		tmp->pNext = circleHead;
		circleHead = tmp;
	}
}

/*绘制圆形带文本*/
void drawCircle(circleNode circleHead)
{
	circleNode tmp;
	tmp = circleHead;
	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = 2 * (tmp->data.radius);
			double h = 2 * (tmp->data.radius);
			StartFilledRegion(0.5);
			MovePen(tmp->data.startX - w / 2 - selectedDx, tmp->data.startY + w / 2 + selectedDy);
			DrawLine(w + 2 * selectedDx, 0);
			DrawLine(0, -(h + 2 * selectedDy));
			DrawLine(-w - 2 * selectedDx, 0);
			DrawLine(0, h + 2 * selectedDy);
			EndFilledRegion();
		}

		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		if (tmp->data.fillFlag) StartFilledRegion(1);
			/*画边框*/
			MovePen(tmp->data.startX + tmp->data.radius, tmp->data.startY);
			DrawArc(tmp->data.radius, 0, 360);
		if (tmp->data.fillFlag) EndFilledRegion();
			
			/*写文本*/
			if (fabs(tmp->data.radius * 2 > TextStringWidth(tmp->data.text)))/*判断框的大小是否比文本大，否则不输出*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel(tmp->data.startX - TextStringWidth(tmp->data.text) / 2,
					tmp->data.startY  - GetFontAscent(tmp->data.text) / 2,
					tmp->data.text);
			}

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------椭圆形绘制部分--------------------------------------------------------------------------------------*/
/*初始化一个椭圆形链表节点并插入链表头部*/
void initOval(double x, double y)
{
	ovalNode tmp = (ovalNode)malloc(sizeof(oNode));/*创建一个临时的节点，用来加入链表的头*/
	tmp->data.startX = x;/*把Data中的信息传入临时节点tmp*/
	tmp->data.startY = y;
	tmp->data.xRadius = 0;
	tmp->data.yRadius = 0;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*插入链表头部*/
	if (ovalHead == NULL)/*判断当前链表的头结点是否为空*/
		ovalHead = tmp;
	else
	{
		tmp->pNext = ovalHead;
		ovalHead = tmp;
	}
}

/*绘制椭圆形带文本*/
void drawOval(ovalNode ovalHead)
{
	ovalNode tmp;
	tmp = ovalHead;
	while (tmp != NULL)
	{
		if (tmp == selectedGraph)
		{
			SetPenSize(1);
			DefineColor("Light Blue", .0, .47, .84);
			SetPenColor("Light Blue");
			double w = 2 * (tmp->data.xRadius);
			double h = 2 * (tmp->data.yRadius);
			StartFilledRegion(0.5);
			MovePen(w >= 0 ? tmp->data.startX - w / 2 - selectedDx : tmp->data.startX - w / 2 + selectedDx,
				h >= 0 ? tmp->data.startY - h / 2 - selectedDy : tmp->data.startY - h / 2 + selectedDy);
			DrawLine(w >= 0 ? w + 2 * selectedDx : w - 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? h + 2 * selectedDy : h - 2 * selectedDy);
			DrawLine(w >= 0 ? -w - 2 * selectedDx : -w + 2 * selectedDx, 0);
			DrawLine(0, h >= 0 ? -h - 2 * selectedDy : -h + 2 * selectedDy);
			EndFilledRegion();
		}

		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		if (tmp->data.fillFlag) StartFilledRegion(1);
			/*画边框*/
			MovePen(tmp->data.startX + tmp->data.xRadius, tmp->data.startY);
			DrawEllipticalArc(tmp->data.xRadius,tmp->data.yRadius,0,360);
		if (tmp->data.fillFlag) EndFilledRegion();

		/*写文本*/
		if (fabs(tmp->data.xRadius * 2) > TextStringWidth(tmp->data.text) &&
			fabs(tmp->data.yRadius * 2) > GetFontAscent(tmp->data.text))/*判断框的大小是否比文本大，否则不输出*/
		{
			SetPenColor(tmp->data.textColor);
			drawLabel(tmp->data.startX - TextStringWidth(tmp->data.text) / 2,
				tmp->data.startY - GetFontAscent(tmp->data.text) / 2,
				tmp->data.text);
		}

		tmp = tmp->pNext;/*链表后移*/
	}
	free(tmp);
}
