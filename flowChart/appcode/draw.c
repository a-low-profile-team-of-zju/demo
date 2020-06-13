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

double selectedDx = 0.2; /*ѡ�п�����Ͻ�ƫ����*/
double selectedDy = 0.2;

/*--------------------------------------------------------------------------------------���λ��Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ����������ڵ㲢��������ͷ��*/
void initRec(double x,double y)
{
	rectangleNode tmp = (rectangleNode)malloc(sizeof(recNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (rectangleHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		rectangleHead = tmp;
	else
	{
		tmp->pNext = rectangleHead;
		rectangleHead = tmp;
	}
}

/*���ƾ��δ��ı�*/
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
			/*���߿�*/
			MovePen(tmp->data.startX, tmp->data.startY);               
			DrawLine(0, tmp->data.endY - tmp->data.startY);
			DrawLine(tmp->data.endX - tmp->data.startX, 0);
			DrawLine(0, -tmp->data.endY + tmp->data.startY);
			DrawLine(-tmp->data.endX + tmp->data.startX, 0);
		if (tmp->data.fillFlag) EndFilledRegion();

			/*д�ı�*/
			if(fabs(tmp->data.endX - tmp->data.startX)>TextStringWidth(tmp->data.text) && 
				fabs(tmp->data.endY - tmp->data.startY) > GetFontAscent(tmp->data.text))/*�жϿ�Ĵ�С�Ƿ���ı��󣬷������*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
					(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
					tmp->data.text);
			}

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------Բ�Ǿ��λ��Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ��Բ�Ǿ�������ڵ㲢��������ͷ��*/
void initRoundedRec(double x, double y)
{
	rRectangleNode tmp = (rRectangleNode)malloc(sizeof(roundedRecNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (rRectangleHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		rRectangleHead = tmp;
	else
	{
		tmp->pNext = rRectangleHead;
		rRectangleHead = tmp;
	}
}

/*����Բ�Ǿ��δ��ı�*/
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
			if (width * height<=0)/*��֤�����4�������϶�ʱ����ͼ������*/
			{
				if (tmp->data.fillFlag) StartFilledRegion(1);
				/*���߿�*/
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

				/*д�ı�*/
				if (fabs(width) > TextStringWidth(tmp->data.text) &&
					fabs(height) > GetFontAscent(tmp->data.text))/*�жϿ�Ĵ�С�Ƿ���ı��󣬷������*/
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
				/*���߿�*/
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

				/*д�ı�*/
				if (fabs(width) > TextStringWidth(tmp->data.text) &&
					fabs(height) > GetFontAscent(tmp->data.text))/*�жϿ�Ĵ�С�Ƿ���ı��󣬷������*/
				{
					SetPenColor(tmp->data.textColor);
					drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
						(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
						tmp->data.text);
				}
			}

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------���λ��Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ����������ڵ㲢��������ͷ��*/
void initDiam(double x, double y)
{
	diamNode tmp = (diamNode)malloc(sizeof(diamondNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (diamondHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		diamondHead = tmp;
	else
	{
		tmp->pNext = diamondHead;
		diamondHead = tmp;
	}
}

/*�������δ��ı�*/
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
			/*���߿�*/
			MovePen((tmp->data.startX+tmp->data.endX)/2, tmp->data.startY);
			DrawLine((tmp->data.endX-tmp->data.startX)/2, (tmp->data.endY - tmp->data.startY)/2);
			DrawLine(-(tmp->data.endX - tmp->data.startX) / 2, (tmp->data.endY - tmp->data.startY) / 2);
			DrawLine(-(tmp->data.endX - tmp->data.startX) / 2, -(tmp->data.endY - tmp->data.startY) / 2);
			DrawLine((tmp->data.endX - tmp->data.startX) / 2, -(tmp->data.endY - tmp->data.startY) / 2);
		if (tmp->data.fillFlag) EndFilledRegion();

			/*д�ı�*/
			if (fabs(tmp->data.endX - tmp->data.startX) > TextStringWidth(tmp->data.text) &&
				fabs(tmp->data.endY - tmp->data.startY) > GetFontAscent(tmp->data.text))/*�жϿ�Ĵ�С�Ƿ���ı��󣬷������*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
					(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
					tmp->data.text);
			}
		

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------ֱ�߻��Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ��ֱ������ڵ㲢��������ͷ��*/
void initLine(double x, double y)
{
	lineNode tmp = (lineNode)malloc(sizeof(lNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	strcpy(tmp->data.fillColor, defaultFillColor);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (lineHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		lineHead = tmp;
	else
	{
		tmp->pNext = lineHead;
		lineHead = tmp;
	}
}

/*����ֱ��*/
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
		/*���߿�*/
		MovePen(tmp->data.startX, tmp->data.startY);
		DrawLine(tmp->data.endX - tmp->data.startX, tmp->data.endY - tmp->data.startY);

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------�����ͷ���Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ�������ͷ����ڵ㲢��������ͷ��*/
void initArrow(double x, double y)
{
	arrowNode tmp = (arrowNode)malloc(sizeof(aNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	strcpy(tmp->data.fillColor, defaultFillColor);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (arrowHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		arrowHead = tmp;
	else
	{
		tmp->pNext = arrowHead;
		arrowHead = tmp;
	}
}

/*���Ƶ����ͷ*/
void drawArrow(arrowNode arrowHead)
{
	arrowNode tmp;
	tmp = arrowHead;
	double angle = 15;   /*���� 30�㣬���޸�*/
	double waist = 0.3;/*��ͷ�߳�*/
	
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
		double alpha = atan2(width, height);/*atan2()�Ǹ��ö���*/
		double sina = height / length;
		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		/*��ֱ��*/
		MovePen(tmp->data.startX, tmp->data.startY);
		DrawLine(tmp->data.endX - tmp->data.startX, tmp->data.endY - tmp->data.startY);
		/*����ͷ,���ֱ�߶���1.5��waist̫�̾Ͳ�����*/
		if (length > 1.5 * waist)
		{
			DrawLine(waist * sin(alpha - angle), waist * cos(alpha - angle));
			MovePen(tmp->data.endX,tmp->data.endY);
			DrawLine(waist * sin(alpha + angle), waist * cos(alpha + angle));
		}

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------˫���ͷ���Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ��˫���ͷ����ڵ㲢��������ͷ��*/
void initdArrow(double x, double y)
{
	dArrowNode tmp = (dArrowNode)malloc(sizeof(daNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	strcpy(tmp->data.fillColor, defaultFillColor);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (dArrowHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		dArrowHead = tmp;
	else
	{
		tmp->pNext = dArrowHead;
		dArrowHead = tmp;
	}
}

/*����˫���ͷ*/
void drawdArrow(dArrowNode dArrowHead)
{
	dArrowNode tmp;
	tmp = dArrowHead;
	double angle = 15;   /*���� 30�㣬���޸�*/
	double waist = 0.3;/*��ͷ�߳�*/

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
		double alpha = atan2(width, height);/*atan2()�Ǹ��ö���*/
		double sina = height / length;
		SetPenSize(tmp->data.penSize);
		SetPenColor(tmp->data.fillColor);
		/*��ֱ��*/
		MovePen(tmp->data.startX, tmp->data.startY);
		DrawLine(tmp->data.endX - tmp->data.startX, tmp->data.endY - tmp->data.startY);
		/*����ͷ,���ֱ�߶���3��waist̫�̾Ͳ�����*/
		if (length > 3 * waist)
		{
			/*ĩ��ͷ*/
			DrawLine(waist * sin(alpha - angle), waist * cos(alpha - angle));
			MovePen(tmp->data.endX, tmp->data.endY);
			DrawLine(waist * sin(alpha + angle), waist * cos(alpha + angle));
			/*ͷ��ͷ*/
			MovePen(tmp->data.startX, tmp->data.startY);
			DrawLine(-waist * sin(alpha - angle), -waist * cos(alpha - angle));
			MovePen(tmp->data.startX, tmp->data.startY);
			DrawLine(-waist * sin(alpha + angle), -waist * cos(alpha + angle));
		}

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------ƽ���ı��λ��Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ��ƽ���ı�������ڵ㲢��������ͷ��*/
void initPara(double x, double y)
{
	paraNode tmp = (paraNode)malloc(sizeof(pNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.endX = x;
	tmp->data.endY = y;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (paraHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		paraHead = tmp;
	else
	{
		tmp->pNext = paraHead;
		paraHead = tmp;
	}
}

/*����ƽ���ı��δ��ı�*/
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
			/*���߿�*/
			MovePen(tmp->data.startX, tmp->data.startY);
			DrawLine((tmp->data.endX - tmp->data.startX) * 0.8, 0);/*ƽ���ı������µױ߳�Ϊ0.8�������ˮƽ�ƶ�����*/
			DrawLine((tmp->data.endX - tmp->data.startX) * 0.2, tmp->data.endY-tmp->data.startY);
			DrawLine(-(tmp->data.endX - tmp->data.startX) * 0.8, 0);
			DrawLine(-(tmp->data.endX - tmp->data.startX) * 0.2, -(tmp->data.endY - tmp->data.startY));
		if (tmp->data.fillFlag) EndFilledRegion();

			/*д�ı�*/
			if (fabs(tmp->data.endX - tmp->data.startX)*0.8 > TextStringWidth(tmp->data.text) &&
				fabs(tmp->data.endY - tmp->data.startY) > GetFontAscent(tmp->data.text))/*�жϿ�Ĵ�С�Ƿ���ı��󣬷������*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel((tmp->data.startX + tmp->data.endX - TextStringWidth(tmp->data.text)) / 2,
					(tmp->data.startY + tmp->data.endY - GetFontAscent(tmp->data.text)) / 2,
					tmp->data.text);
		    }

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------Բ�λ��Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ��Բ������ڵ㲢��������ͷ��*/
void initCircle(double x, double y)
{
	circleNode tmp = (circleNode)malloc(sizeof(cNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.radius = 0;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (circleHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		circleHead = tmp;
	else
	{
		tmp->pNext = circleHead;
		circleHead = tmp;
	}
}

/*����Բ�δ��ı�*/
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
			/*���߿�*/
			MovePen(tmp->data.startX + tmp->data.radius, tmp->data.startY);
			DrawArc(tmp->data.radius, 0, 360);
		if (tmp->data.fillFlag) EndFilledRegion();
			
			/*д�ı�*/
			if (fabs(tmp->data.radius * 2 > TextStringWidth(tmp->data.text)))/*�жϿ�Ĵ�С�Ƿ���ı��󣬷������*/
			{
				SetPenColor(tmp->data.textColor);
				drawLabel(tmp->data.startX - TextStringWidth(tmp->data.text) / 2,
					tmp->data.startY  - GetFontAscent(tmp->data.text) / 2,
					tmp->data.text);
			}

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}

/*--------------------------------------------------------------------------------------��Բ�λ��Ʋ���--------------------------------------------------------------------------------------*/
/*��ʼ��һ����Բ������ڵ㲢��������ͷ��*/
void initOval(double x, double y)
{
	ovalNode tmp = (ovalNode)malloc(sizeof(oNode));/*����һ����ʱ�Ľڵ㣬�������������ͷ*/
	tmp->data.startX = x;/*��Data�е���Ϣ������ʱ�ڵ�tmp*/
	tmp->data.startY = y;
	tmp->data.xRadius = 0;
	tmp->data.yRadius = 0;
	tmp->data.penSize = defaultPenSize;
	tmp->data.fillFlag = defaultFillFlag;
	strcpy(tmp->data.textColor, defaultTextColor);
	strcpy(tmp->data.fillColor, defaultFillColor);
	strcpy(tmp->data.text, defaultText);

	tmp->pNext = NULL;

	/*��������ͷ��*/
	if (ovalHead == NULL)/*�жϵ�ǰ�����ͷ����Ƿ�Ϊ��*/
		ovalHead = tmp;
	else
	{
		tmp->pNext = ovalHead;
		ovalHead = tmp;
	}
}

/*������Բ�δ��ı�*/
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
			/*���߿�*/
			MovePen(tmp->data.startX + tmp->data.xRadius, tmp->data.startY);
			DrawEllipticalArc(tmp->data.xRadius,tmp->data.yRadius,0,360);
		if (tmp->data.fillFlag) EndFilledRegion();

		/*д�ı�*/
		if (fabs(tmp->data.xRadius * 2) > TextStringWidth(tmp->data.text) &&
			fabs(tmp->data.yRadius * 2) > GetFontAscent(tmp->data.text))/*�жϿ�Ĵ�С�Ƿ���ı��󣬷������*/
		{
			SetPenColor(tmp->data.textColor);
			drawLabel(tmp->data.startX - TextStringWidth(tmp->data.text) / 2,
				tmp->data.startY - GetFontAscent(tmp->data.text) / 2,
				tmp->data.text);
		}

		tmp = tmp->pNext;/*�������*/
	}
	free(tmp);
}
