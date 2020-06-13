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
#include <commdlg.h>

#include "draw.h"
#include "UI.h"
#include "operation.h"

/*用来提供文本线条及填充颜色*/
char* colors[] =
{
	"Black",
	"Dark Gray",
	"Gray",
	"Light Gray",
	"White",
	"Brown",
	"Red",
	"Orange",
	"Yellow",
	"Green",
	"Blue",
	"Violet",
	"Magenta",
	"Cyan"
};

/*用来根据当前鼠标位置选择图形，返回值为1时表示选中，反之则无
注意，这个遍历方法会使得选中图形时具有优先级，矩形优先级最大，椭圆最小*/
int selectGraph(double x, double y)
{
	/*判断矩形*/
	rectangleNode tmp1 = rectangleHead;
	while (tmp1 != NULL)
	{
		if ((x - tmp1->data.startX) * (x - tmp1->data.endX) <= 0 && (y - tmp1->data.startY) * (y - tmp1->data.endY) <= 0)
		{
			type = 矩形;
			selectedGraph = tmp1;
			return 1;
		}
		else
			tmp1 = tmp1->pNext;/*链表后移*/
	}
	free(tmp1);

	/*判断圆角矩形*/
	rRectangleNode tmp2 = rRectangleHead;
	while (tmp2 != NULL)
	{
		if ((x - tmp2->data.startX) * (x - tmp2->data.endX) <= 0 && (y - tmp2->data.startY) * (y - tmp2->data.endY) <= 0)/*这里和矩形判定一样，懒得改了，反正差不多*/
		{
			type = 圆角矩形;
			selectedGraph = tmp2;
			return 1;
		}
		else
			tmp2 = tmp2->pNext;/*链表后移*/
	}
	free(tmp2);

	/*判断菱形*/
	diamNode tmp3 = diamondHead;
	while (tmp3 != NULL)
	{
		double width = fabs(tmp3->data.endX - tmp3->data.startX);
		double height = fabs(tmp3->data.endY - tmp3->data.startY);
		double midY = (tmp3->data.startY + tmp3->data.endY) / 2;
		double k = height / width;
		if ((x - tmp3->data.startX) * (x - tmp3->data.endX) <= 0 &&
			(y - k * (x - tmp3->data.startX) - midY) * (y + k * (x - tmp3->data.startX) - midY) <= 0 &&
			(y + k * (x - tmp3->data.endX) - midY) * (y - k * (x - tmp3->data.endX) - midY) <= 0)
		{
			type = 菱形;
			selectedGraph = tmp3;
			return 1;
		}
		else
			tmp3 = tmp3->pNext;/*链表后移*/
	}
	free(tmp3);

	/*判断直线*/
	lineNode tmp4 = lineHead;
	while (tmp4 != NULL)
	{
		double dx = tmp4->data.endX - tmp4->data.startX;
		double dy = tmp4->data.endY - tmp4->data.startY;
		if (tmp4->data.endX <= tmp4->data.startX + 0.2 && tmp4->data.endX >= tmp4->data.startX - 0.2 &&
			(x - tmp4->data.endX - 0.2) * (x - tmp4->data.endX + 0.2) <= 0 && (y - tmp4->data.startY) * (y - tmp4->data.endY) <= 0)/*直线上下0.2（英寸）均为有效判定区域*/
		{
			type = 直线;
			selectedGraph = tmp4;
			return 1;
		}
		else if ((x - tmp4->data.startX) * (x - tmp4->data.endX) <= 0 &&
			(y - dy / dx * (x - tmp4->data.startX) - tmp4->data.startY - 0.2) * (y - dy / dx * (x - tmp4->data.startX) - tmp4->data.startY + 0.2) <= 0)
		{
			type = 直线;
			selectedGraph = tmp4;
			return 1;
		}
		else
			tmp4 = tmp4->pNext;/*链表后移*/
	}
	free(tmp4);

	/*判断单向箭头*/
	arrowNode tmp5 = arrowHead;
	while (tmp5 != NULL)
	{
		double dx = tmp5->data.endX - tmp5->data.startX;
		double dy = tmp5->data.endY - tmp5->data.startY;
		if (tmp5->data.endX <= tmp5->data.startX + 0.2 && tmp5->data.endX >= tmp5->data.startX - 0.2 &&
			(x - tmp5->data.endX - 0.2) * (x - tmp5->data.endX + 0.2) <= 0 && (y - tmp5->data.startY) * (y - tmp5->data.endY) <= 0)/*单向箭头上下0.2（英寸）均为有效判定区域*/
		{
			type = 单向箭头;
			selectedGraph = tmp5;
			return 1;
		}
		else if ((x - tmp5->data.startX) * (x - tmp5->data.endX) <= 0 &&
			(y - dy / dx * (x - tmp5->data.startX) - tmp5->data.startY - 0.2) * (y - dy / dx * (x - tmp5->data.startX) - tmp5->data.startY + 0.2) <= 0)
		{
			type = 单向箭头;
			selectedGraph = tmp5;
			return 1;
		}
		else
			tmp5 = tmp5->pNext;/*链表后移*/
	}
	free(tmp5);

	/*判断双向箭头*/
	dArrowNode tmp6 = dArrowHead;
	while (tmp6 != NULL)
	{
		double dx = tmp6->data.endX - tmp6->data.startX;
		double dy = tmp6->data.endY - tmp6->data.startY;
		if (tmp6->data.endX <= tmp6->data.startX + 0.2 && tmp6->data.endX >= tmp6->data.startX - 0.2 &&
			(x - tmp6->data.endX - 0.2) * (x - tmp6->data.endX + 0.2) <= 0 && (y - tmp6->data.startY) * (y - tmp6->data.endY) <= 0)/*双向箭头上下0.2（英寸）均为有效判定区域*/
		{
			type = 双向箭头;
			selectedGraph = tmp6;
			return 1;
		}
		else if ((x - tmp6->data.startX) * (x - tmp6->data.endX) <= 0 &&
			(y - dy / dx * (x - tmp6->data.startX) - tmp6->data.startY - 0.2) * (y - dy / dx * (x - tmp6->data.startX) - tmp6->data.startY + 0.2) <= 0)
		{
			type = 双向箭头;
			selectedGraph = tmp6;
			return 1;
		}
		else
			tmp6 = tmp6->pNext;/*链表后移*/
	}
	free(tmp6);

	/*判断平行四边形*/
	paraNode tmp7 = paraHead;
	while (tmp7 != NULL)
	{
		double dx = (tmp7->data.endX - tmp7->data.startX) * 0.2;/*这个0.2是因为定义了平行四边形上下边为鼠标水平移动距离的0.8倍*/
		double dy = (tmp7->data.endY - tmp7->data.startY);
		if ((x - tmp7->data.startX) * (x - tmp7->data.endX) <= 0 &&
			(y - tmp7->data.startY) * (y - dy / dx * (x - tmp7->data.startX) - tmp7->data.startY) <= 0 &&
			(y - tmp7->data.endY) * (y - dy / dx * (x - tmp7->data.endX) - tmp7->data.endY) <= 0)
		{
			type = 平行四边形;
			selectedGraph = tmp7;
			return 1;
		}
		else
			tmp7 = tmp7->pNext;/*链表后移*/
	}
	free(tmp7);

	/*判断圆形*/
	circleNode tmp8 = circleHead;
	while (tmp8 != NULL)
	{
		if (sqrt((x - tmp8->data.startX) * (x - tmp8->data.startX) + (y - tmp8->data.startY) * (y - tmp8->data.startY)) <= tmp8->data.radius)
		{
			type = 圆形;
			selectedGraph = tmp8;
			return 1;
		}
		else
			tmp8 = tmp8->pNext;/*链表后移*/
	}
	free(tmp8);

	/*判断圆形*/
	ovalNode tmp9 = ovalHead;
	while (tmp9 != NULL)
	{
		if (fabs(tmp9->data.xRadius) >= fabs(tmp9->data.yRadius))/*焦点在x轴时*/
		{
			double c = sqrt(tmp9->data.xRadius * tmp9->data.xRadius - tmp9->data.yRadius * tmp9->data.yRadius);
			double d = sqrt(pow(x - tmp9->data.startX - c, 2) + pow(y - tmp9->data.startY, 2)) +
				sqrt(pow(x - tmp9->data.startX + c, 2) + pow(y - tmp9->data.startY, 2));/*到两焦点的距离和*/
			if (d <= 2 * fabs(tmp9->data.xRadius))
			{
				type = 椭圆形;
				selectedGraph = tmp9;
				return 1;
			}
			else
			tmp9 = tmp9->pNext;/*链表后移*/
		}
		else if (fabs(tmp9->data.xRadius) < fabs(tmp9->data.yRadius))/*焦点在y轴时*/
		{
			double c = sqrt(tmp9->data.yRadius * tmp9->data.yRadius - tmp9->data.xRadius * tmp9->data.xRadius);
			double d = sqrt(pow(y - tmp9->data.startY - c, 2) + pow(x - tmp9->data.startX, 2)) +
				sqrt(pow(y - tmp9->data.startY + c, 2) + pow(x - tmp9->data.startX, 2));/*到两焦点的距离和*/
			if (d <= 2 * fabs(tmp9->data.yRadius))
			{
				type = 椭圆形;
				selectedGraph = tmp9;
				return 1;
			}
			else
				tmp9 = tmp9->pNext;/*链表后移*/
		}
	}
	free(tmp9);
}

/*移动图形*/
void moveGraph(double dx, double dy)
{
	switch (type)
	{
	case 矩形:
		((rectangleNode)selectedGraph)->data.startX += dx;
		((rectangleNode)selectedGraph)->data.startY += dy;
		((rectangleNode)selectedGraph)->data.endX += dx;
		((rectangleNode)selectedGraph)->data.endY += dy;
		break;
	case 圆角矩形:
		((rRectangleNode)selectedGraph)->data.startX += dx;
		((rRectangleNode)selectedGraph)->data.startY += dy;
		((rRectangleNode)selectedGraph)->data.endX += dx;
		((rRectangleNode)selectedGraph)->data.endY += dy;
		break;
	case 菱形:
		((diamNode)selectedGraph)->data.startX += dx;
		((diamNode)selectedGraph)->data.startY += dy;
		((diamNode)selectedGraph)->data.endX += dx;
		((diamNode)selectedGraph)->data.endY += dy;
		break;
	case 直线:
		((lineNode)selectedGraph)->data.startX += dx;
		((lineNode)selectedGraph)->data.startY += dy;
		((lineNode)selectedGraph)->data.endX += dx;
		((lineNode)selectedGraph)->data.endY += dy;
		break;
	case 单向箭头:
		((arrowNode)selectedGraph)->data.startX += dx;
		((arrowNode)selectedGraph)->data.startY += dy;
		((arrowNode)selectedGraph)->data.endX += dx;
		((arrowNode)selectedGraph)->data.endY += dy;
		break;
	case 双向箭头:
		((dArrowNode)selectedGraph)->data.startX += dx;
		((dArrowNode)selectedGraph)->data.startY += dy;
		((dArrowNode)selectedGraph)->data.endX += dx;
		((dArrowNode)selectedGraph)->data.endY += dy;
		break;
	case 平行四边形:
		((paraNode)selectedGraph)->data.startX += dx;
		((paraNode)selectedGraph)->data.startY += dy;
		((paraNode)selectedGraph)->data.endX += dx;
		((paraNode)selectedGraph)->data.endY += dy;
		break;
	case 圆形:
		((circleNode)selectedGraph)->data.startX += dx;
		((circleNode)selectedGraph)->data.startY += dy;
		break;
	case 椭圆形:
		((ovalNode)selectedGraph)->data.startX += dx;
		((ovalNode)selectedGraph)->data.startY += dy;
		break;
	}
}

/*改变线条及填充颜色*/
void changeFillColor(int choose)
{
	if (selectedGraph != NULL)
	{
		switch (type)
		{
		case 矩形:
			strcpy(((rectangleNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 圆角矩形:
			strcpy(((rRectangleNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 菱形:
			strcpy(((diamNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 直线:
			strcpy(((lineNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 单向箭头:
			strcpy(((arrowNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 双向箭头:
			strcpy(((dArrowNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 平行四边形:
			strcpy(((paraNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 圆形:
			strcpy(((circleNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		case 椭圆形:
			strcpy(((ovalNode)selectedGraph)->data.fillColor, colors[choose]);
			break;
		}
		//operation = none;
	}
}

/*改变文本字体颜色*/
void changeTextColor(int choose)
{
	if (selectedGraph != NULL)
	{
		switch (type)
		{
		case 矩形:
			strcpy(((rectangleNode)selectedGraph)->data.textColor, colors[choose]);
			break;
		case 圆角矩形:
			strcpy(((rRectangleNode)selectedGraph)->data.textColor, colors[choose]);
			break;
		case 菱形:
			strcpy(((diamNode)selectedGraph)->data.textColor, colors[choose]);
			break;
		case 直线:
			break;
		case 单向箭头:
			break;
		case 双向箭头:
			break;
		case 平行四边形:
			strcpy(((paraNode)selectedGraph)->data.textColor, colors[choose]);
			break;
		case 圆形:
			strcpy(((circleNode)selectedGraph)->data.textColor, colors[choose]);
			break;
		case 椭圆形:
			strcpy(((ovalNode)selectedGraph)->data.textColor, colors[choose]);
			break;
		}
		//operation = none;
	}
}

/*按比例改变图形大小,此为放大*/
void enlargeGraphicSize(void)
{
	if (selectedGraph != NULL)
	{
		double width, height;
		switch (type)
		{
		case 矩形:
			width = fabs(((rectangleNode)selectedGraph)->data.endX - ((rectangleNode)selectedGraph)->data.startX);
			height = fabs(((rectangleNode)selectedGraph)->data.endY - ((rectangleNode)selectedGraph)->data.startY);
			if (((rectangleNode)selectedGraph)->data.endX >= ((rectangleNode)selectedGraph)->data.startX)
				((rectangleNode)selectedGraph)->data.endX += scaleUnit;/*我选用的方案为将水平宽度每次增加scaleUnit（英寸），其他图形也一样*/
			else
				((rectangleNode)selectedGraph)->data.endX -= scaleUnit;
			if (((rectangleNode)selectedGraph)->data.endY >= ((rectangleNode)selectedGraph)->data.startY)
				((rectangleNode)selectedGraph)->data.endY += scaleUnit / width * height;
			else
				((rectangleNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			break;
		case 圆角矩形:
			width = fabs(((rRectangleNode)selectedGraph)->data.endX - ((rRectangleNode)selectedGraph)->data.startX);
			height = fabs(((rRectangleNode)selectedGraph)->data.endY - ((rRectangleNode)selectedGraph)->data.startY);
			if (((rRectangleNode)selectedGraph)->data.endX >= ((rRectangleNode)selectedGraph)->data.startX)
				((rRectangleNode)selectedGraph)->data.endX += scaleUnit;
			else
				((rRectangleNode)selectedGraph)->data.endX -= scaleUnit;
			if (((rRectangleNode)selectedGraph)->data.endY >= ((rRectangleNode)selectedGraph)->data.startY)
				((rRectangleNode)selectedGraph)->data.endY += scaleUnit / width * height;
			else
				((rRectangleNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			break;
		case 菱形:
			width = fabs(((diamNode)selectedGraph)->data.endX - ((diamNode)selectedGraph)->data.startX);
			height = fabs(((diamNode)selectedGraph)->data.endY - ((diamNode)selectedGraph)->data.startY);
			if (((diamNode)selectedGraph)->data.endX >= ((diamNode)selectedGraph)->data.startX)
				((diamNode)selectedGraph)->data.endX += scaleUnit;
			else
				((diamNode)selectedGraph)->data.endX -= scaleUnit;
			if (((diamNode)selectedGraph)->data.endY >= ((diamNode)selectedGraph)->data.startY)
				((diamNode)selectedGraph)->data.endY += scaleUnit / width * height;
			else
				((diamNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			break;
		case 直线:
			width = fabs(((lineNode)selectedGraph)->data.endX - ((lineNode)selectedGraph)->data.startX);
			height = fabs(((lineNode)selectedGraph)->data.endY - ((lineNode)selectedGraph)->data.startY);
			if (width != 0)
			{
				if (((lineNode)selectedGraph)->data.endX >= ((lineNode)selectedGraph)->data.startX)
					((lineNode)selectedGraph)->data.endX += scaleUnit;
				else
					((lineNode)selectedGraph)->data.endX -= scaleUnit;
				if (((lineNode)selectedGraph)->data.endY >= ((lineNode)selectedGraph)->data.startY)
					((lineNode)selectedGraph)->data.endY += scaleUnit / width * height;
				else
					((lineNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			}
			else
			{
				if (((lineNode)selectedGraph)->data.endY >= ((lineNode)selectedGraph)->data.startY)
					((lineNode)selectedGraph)->data.endY += scaleUnit ;
				else
					((lineNode)selectedGraph)->data.endY -= scaleUnit ;
			}
			break;
		case 单向箭头:
			width = fabs(((arrowNode)selectedGraph)->data.endX - ((arrowNode)selectedGraph)->data.startX);
			height = fabs(((arrowNode)selectedGraph)->data.endY - ((arrowNode)selectedGraph)->data.startY);
			if (width != 0)
			{
				if (((arrowNode)selectedGraph)->data.endX >= ((arrowNode)selectedGraph)->data.startX)
					((arrowNode)selectedGraph)->data.endX += scaleUnit;
				else
					((arrowNode)selectedGraph)->data.endX -= scaleUnit;
				if (((arrowNode)selectedGraph)->data.endY >= ((arrowNode)selectedGraph)->data.startY)
					((arrowNode)selectedGraph)->data.endY += scaleUnit / width * height;
				else
					((arrowNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			}
			else
			{
				if (((arrowNode)selectedGraph)->data.endY >= ((arrowNode)selectedGraph)->data.startY)
					((arrowNode)selectedGraph)->data.endY += scaleUnit;
				else
					((arrowNode)selectedGraph)->data.endY -= scaleUnit;
			}
			break;
		case 双向箭头:
			width = fabs(((dArrowNode)selectedGraph)->data.endX - ((dArrowNode)selectedGraph)->data.startX);
			height = fabs(((dArrowNode)selectedGraph)->data.endY - ((dArrowNode)selectedGraph)->data.startY);
			if (width != 0)
			{
				if (((dArrowNode)selectedGraph)->data.endX >= ((dArrowNode)selectedGraph)->data.startX)
					((dArrowNode)selectedGraph)->data.endX += scaleUnit;
				else
					((dArrowNode)selectedGraph)->data.endX -= scaleUnit;
				if (((dArrowNode)selectedGraph)->data.endY >= ((dArrowNode)selectedGraph)->data.startY)
					((dArrowNode)selectedGraph)->data.endY += scaleUnit / width * height;
				else
					((dArrowNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			}
			else
			{
				if (((dArrowNode)selectedGraph)->data.endY >= ((dArrowNode)selectedGraph)->data.startY)
					((dArrowNode)selectedGraph)->data.endY += scaleUnit;
				else
					((dArrowNode)selectedGraph)->data.endY -= scaleUnit;
			}
			break;
		case 平行四边形:
			width = fabs(((paraNode)selectedGraph)->data.endX - ((paraNode)selectedGraph)->data.startX);
			height = fabs(((paraNode)selectedGraph)->data.endY - ((paraNode)selectedGraph)->data.startY);
			if (((paraNode)selectedGraph)->data.endX >= ((paraNode)selectedGraph)->data.startX)
				((paraNode)selectedGraph)->data.endX += scaleUnit;
			else
				((paraNode)selectedGraph)->data.endX -= scaleUnit;
			if (((paraNode)selectedGraph)->data.endY >= ((paraNode)selectedGraph)->data.startY)
				((paraNode)selectedGraph)->data.endY += scaleUnit / width * height;
			else
				((paraNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			break;
		case 圆形:
			if (((circleNode)selectedGraph)->data.radius >= 0)
				((circleNode)selectedGraph)->data.radius += scaleUnit;
			else
				((circleNode)selectedGraph)->data.radius -= scaleUnit;
			break;
		case 椭圆形:
			if (((ovalNode)selectedGraph)->data.xRadius >= 0)
				((ovalNode)selectedGraph)->data.xRadius += scaleUnit;
			else
				((ovalNode)selectedGraph)->data.xRadius -= scaleUnit;
			if (((ovalNode)selectedGraph)->data.yRadius >= 0)
				((ovalNode)selectedGraph)->data.yRadius += scaleUnit / fabs(((ovalNode)selectedGraph)->data.xRadius) * fabs(((ovalNode)selectedGraph)->data.yRadius);
			else
				((ovalNode)selectedGraph)->data.yRadius -= scaleUnit / fabs(((ovalNode)selectedGraph)->data.xRadius) * fabs(((ovalNode)selectedGraph)->data.yRadius);
			break;
		}
	}
}

/*按比例改变图形大小，此为缩小*/
void reduceGraphicSize(void)
{
	if (selectedGraph != NULL)
	{
		double width, height;
		switch (type)
		{
		case 矩形:
			width = fabs(((rectangleNode)selectedGraph)->data.endX - ((rectangleNode)selectedGraph)->data.startX);
			height = fabs(((rectangleNode)selectedGraph)->data.endY - ((rectangleNode)selectedGraph)->data.startY);
			if (((rectangleNode)selectedGraph)->data.endX >= ((rectangleNode)selectedGraph)->data.startX)
				((rectangleNode)selectedGraph)->data.endX -= scaleUnit;/*我选用的方案为将水平宽度每次减少scaleUnit（英寸），其他图形也一样*/
			else
				((rectangleNode)selectedGraph)->data.endX += scaleUnit;
			if (((rectangleNode)selectedGraph)->data.endY >= ((rectangleNode)selectedGraph)->data.startY)
				((rectangleNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			else
				((rectangleNode)selectedGraph)->data.endY += scaleUnit / width * height;
			break;
		case 圆角矩形:
			width = fabs(((rRectangleNode)selectedGraph)->data.endX - ((rRectangleNode)selectedGraph)->data.startX);
			height = fabs(((rRectangleNode)selectedGraph)->data.endY - ((rRectangleNode)selectedGraph)->data.startY);
			if (((rRectangleNode)selectedGraph)->data.endX >= ((rRectangleNode)selectedGraph)->data.startX)
				((rRectangleNode)selectedGraph)->data.endX -= scaleUnit;
			else
				((rRectangleNode)selectedGraph)->data.endX += scaleUnit;
			if (((rRectangleNode)selectedGraph)->data.endY >= ((rRectangleNode)selectedGraph)->data.startY)
				((rRectangleNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			else
				((rRectangleNode)selectedGraph)->data.endY += scaleUnit / width * height;
			break;
		case 菱形:
			width = fabs(((diamNode)selectedGraph)->data.endX - ((diamNode)selectedGraph)->data.startX);
			height = fabs(((diamNode)selectedGraph)->data.endY - ((diamNode)selectedGraph)->data.startY);
			if (((diamNode)selectedGraph)->data.endX >= ((diamNode)selectedGraph)->data.startX)
				((diamNode)selectedGraph)->data.endX -= scaleUnit;
			else
				((diamNode)selectedGraph)->data.endX += scaleUnit;
			if (((diamNode)selectedGraph)->data.endY >= ((diamNode)selectedGraph)->data.startY)
				((diamNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			else
				((diamNode)selectedGraph)->data.endY += scaleUnit / width * height;
			break;
		case 直线:
			width = fabs(((lineNode)selectedGraph)->data.endX - ((lineNode)selectedGraph)->data.startX);
			height = fabs(((lineNode)selectedGraph)->data.endY - ((lineNode)selectedGraph)->data.startY);
			if (width != 0)
			{
				if (((lineNode)selectedGraph)->data.endX >= ((lineNode)selectedGraph)->data.startX)
					((lineNode)selectedGraph)->data.endX -= scaleUnit;
				else
					((lineNode)selectedGraph)->data.endX += scaleUnit;
				if (((lineNode)selectedGraph)->data.endY >= ((lineNode)selectedGraph)->data.startY)
					((lineNode)selectedGraph)->data.endY -= scaleUnit / width * height;
				else
					((lineNode)selectedGraph)->data.endY += scaleUnit / width * height;
			}
			else
			{
				if (((lineNode)selectedGraph)->data.endY >= ((lineNode)selectedGraph)->data.startY)
					((lineNode)selectedGraph)->data.endY -= scaleUnit;
				else
					((lineNode)selectedGraph)->data.endY += scaleUnit;
			}
			break;
		case 单向箭头:
			width = fabs(((arrowNode)selectedGraph)->data.endX - ((arrowNode)selectedGraph)->data.startX);
			height = fabs(((arrowNode)selectedGraph)->data.endY - ((arrowNode)selectedGraph)->data.startY);
			if (width != 0)
			{
				if (((arrowNode)selectedGraph)->data.endX >= ((arrowNode)selectedGraph)->data.startX)
					((arrowNode)selectedGraph)->data.endX -= scaleUnit;
				else
					((arrowNode)selectedGraph)->data.endX += scaleUnit;
				if (((arrowNode)selectedGraph)->data.endY >= ((arrowNode)selectedGraph)->data.startY)
					((arrowNode)selectedGraph)->data.endY -= scaleUnit / width * height;
				else
					((arrowNode)selectedGraph)->data.endY += scaleUnit / width * height;
			}
			else
			{
				if (((arrowNode)selectedGraph)->data.endY >= ((arrowNode)selectedGraph)->data.startY)
					((arrowNode)selectedGraph)->data.endY -= scaleUnit;
				else
					((arrowNode)selectedGraph)->data.endY += scaleUnit;
			}
			break;
		case 双向箭头:
			width = fabs(((dArrowNode)selectedGraph)->data.endX - ((dArrowNode)selectedGraph)->data.startX);
			height = fabs(((dArrowNode)selectedGraph)->data.endY - ((dArrowNode)selectedGraph)->data.startY);
			if (width != 0)
			{
				if (((dArrowNode)selectedGraph)->data.endX >= ((dArrowNode)selectedGraph)->data.startX)
					((dArrowNode)selectedGraph)->data.endX -= scaleUnit;
				else
					((dArrowNode)selectedGraph)->data.endX += scaleUnit;
				if (((dArrowNode)selectedGraph)->data.endY >= ((dArrowNode)selectedGraph)->data.startY)
					((dArrowNode)selectedGraph)->data.endY -= scaleUnit / width * height;
				else
					((dArrowNode)selectedGraph)->data.endY += scaleUnit / width * height;
			}
			else
			{
				if (((dArrowNode)selectedGraph)->data.endY >= ((dArrowNode)selectedGraph)->data.startY)
					((dArrowNode)selectedGraph)->data.endY -= scaleUnit;
				else
					((dArrowNode)selectedGraph)->data.endY += scaleUnit;
			}
			break;
		case 平行四边形:
			width = fabs(((paraNode)selectedGraph)->data.endX - ((paraNode)selectedGraph)->data.startX);
			height = fabs(((paraNode)selectedGraph)->data.endY - ((paraNode)selectedGraph)->data.startY);
			if (((paraNode)selectedGraph)->data.endX >= ((paraNode)selectedGraph)->data.startX)
				((paraNode)selectedGraph)->data.endX -= scaleUnit;
			else
				((paraNode)selectedGraph)->data.endX += scaleUnit;
			if (((paraNode)selectedGraph)->data.endY >= ((paraNode)selectedGraph)->data.startY)
				((paraNode)selectedGraph)->data.endY -= scaleUnit / width * height;
			else
				((paraNode)selectedGraph)->data.endY += scaleUnit / width * height;
			break;
		case 圆形:
			if (((circleNode)selectedGraph)->data.radius >= 0)
				((circleNode)selectedGraph)->data.radius -= scaleUnit;
			else
				((circleNode)selectedGraph)->data.radius += scaleUnit;
			break;
		case 椭圆形:
			if (((ovalNode)selectedGraph)->data.xRadius >= 0)
				((ovalNode)selectedGraph)->data.xRadius -= scaleUnit;
			else
				((ovalNode)selectedGraph)->data.xRadius += scaleUnit;
			if (((ovalNode)selectedGraph)->data.yRadius >= 0)
				((ovalNode)selectedGraph)->data.yRadius -= scaleUnit / fabs(((ovalNode)selectedGraph)->data.xRadius) * fabs(((ovalNode)selectedGraph)->data.yRadius);
			else
				((ovalNode)selectedGraph)->data.yRadius += scaleUnit / fabs(((ovalNode)selectedGraph)->data.xRadius) * fabs(((ovalNode)selectedGraph)->data.yRadius);
			break;
		}
	}
}

/*改变画笔的粗细*/
void changePenSize(int choose)
{
	if (selectedGraph != NULL)
	{
		switch (type)
		{
		case 矩形:
			((rectangleNode)selectedGraph)->data.penSize = choose;
			break;
		case 圆角矩形:
			((rRectangleNode)selectedGraph)->data.penSize = choose;
			break;
		case 菱形:
			((diamNode)selectedGraph)->data.penSize = choose;
			break;
		case 直线:
			((lineNode)selectedGraph)->data.penSize = choose;
			break;
		case 单向箭头:
			((arrowNode)selectedGraph)->data.penSize = choose;
			break;
		case 双向箭头:
			((dArrowNode)selectedGraph)->data.penSize = choose;
			break;
		case 平行四边形:
			((paraNode)selectedGraph)->data.penSize = choose;
			break;
		case 圆形:
			((circleNode)selectedGraph)->data.penSize = choose;
			break;
		case 椭圆形:
			((ovalNode)selectedGraph)->data.penSize = choose;
			break;
		}
	}
}

/*改变图形的填充状态*/
void fill(void)
{
	if (selectedGraph != NULL)
	{
		switch (type)
		{
		case 矩形:
			((rectangleNode)selectedGraph)->data.fillFlag = !((rectangleNode)selectedGraph)->data.fillFlag;
			break;
		case 圆角矩形:
			((rRectangleNode)selectedGraph)->data.fillFlag = !((rRectangleNode)selectedGraph)->data.fillFlag;
			break;
		case 菱形:
			((diamNode)selectedGraph)->data.fillFlag = !((diamNode)selectedGraph)->data.fillFlag;
			break;
		case 直线:
			break;
		case 单向箭头:
			break;
		case 双向箭头:
			break;
		case 平行四边形:
			((paraNode)selectedGraph)->data.fillFlag = !((paraNode)selectedGraph)->data.fillFlag;
			break;
		case 圆形:
			((circleNode)selectedGraph)->data.fillFlag = !((circleNode)selectedGraph)->data.fillFlag;
			break;
		case 椭圆形:
			((ovalNode)selectedGraph)->data.fillFlag = !((ovalNode)selectedGraph)->data.fillFlag;
			break;
		}
	}
}

/*复制*/
void copy(void)
{
	if (selectedGraph != NULL)
	{
		void* tmp;/*一个临时的节点*/
		switch (type)
		{
		case 矩形:
			tmp = (rectangleNode)malloc(sizeof(recNode));
			/*复制所有信息*/
			//((rectangleNode)tmp)->data.startX = ((rectangleNode)selectedGraph)->data.startX;
			//((rectangleNode)tmp)->data.startY = ((rectangleNode)selectedGraph)->data.startY
			//((rectangleNode)tmp)->data.endX = ((rectangleNode)selectedGraph)->data.endX;
			//((rectangleNode)tmp)->data.endY = ((rectangleNode)selectedGraph)->data.endY;
			//((rectangleNode)tmp)->data.penSize = ((rectangleNode)selectedGraph)->data.penSize;
			//((rectangleNode)tmp)->data.fillFlag = ((rectangleNode)selectedGraph)->data.fillFlag;
			//strcpy(((rectangleNode)tmp)->data.textColor, ((rectangleNode)selectedGraph)->data.textColor);
			//strcpy(((rectangleNode)tmp)->data.fillColor, ((rectangleNode)selectedGraph)->data.fillColor);
			//strcpy(((rectangleNode)tmp)->data.text, ((rectangleNode)selectedGraph)->data.text);
			memcpy(tmp, ((rectangleNode)selectedGraph), sizeof(recNode));/*感谢我的一位同学的提出的解决方法*/
			((rectangleNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 圆角矩形:
			tmp = (rRectangleNode)malloc(sizeof(roundedRecNode));
			memcpy(tmp, ((rRectangleNode)selectedGraph), sizeof(roundedRecNode));
			((rRectangleNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 菱形:
			tmp = (diamNode)malloc(sizeof(diamondNode));
			memcpy(tmp, ((diamNode)selectedGraph), sizeof(diamondNode));
			((diamNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 直线:
			tmp = (lineNode)malloc(sizeof(lNode));
			memcpy(tmp, ((lineNode)selectedGraph), sizeof(lNode));
			((lineNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 单向箭头:
			tmp = (arrowNode)malloc(sizeof(aNode));
			memcpy(tmp, ((arrowNode)selectedGraph), sizeof(aNode));
			((arrowNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 双向箭头:
			tmp = (dArrowNode)malloc(sizeof(daNode));
			memcpy(tmp, ((dArrowNode)selectedGraph), sizeof(daNode));
			((dArrowNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 平行四边形:
			tmp = (paraNode)malloc(sizeof(pNode));
			memcpy(tmp, ((paraNode)selectedGraph), sizeof(pNode));
			((paraNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 圆形:
			tmp = (circleNode)malloc(sizeof(cNode));
			memcpy(tmp, ((circleNode)selectedGraph), sizeof(cNode));
			((circleNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		case 椭圆形:
			tmp = (ovalNode)malloc(sizeof(oNode));
			memcpy(tmp, ((ovalNode)selectedGraph), sizeof(oNode));
			((ovalNode)tmp)->pNext = NULL;
			copyGraph = tmp;
			break;
		}
	}
}

/*粘贴*/
void paste(void)
{
	if (copyGraph != NULL)
	{
		switch (type)
		{
		case 矩形:
			((rectangleNode)copyGraph)->data.startX += 1;/*把复制的图形较原图形偏离一小段距离，这个距离自定*/
			((rectangleNode)copyGraph)->data.startY += 1;
			((rectangleNode)copyGraph)->data.endX += 1;
			((rectangleNode)copyGraph)->data.endY += 1;
			if (rectangleHead == NULL)
				rectangleHead = (rectangleNode)copyGraph;
			else
			{
				((rectangleNode)copyGraph)->pNext = rectangleHead;
				rectangleHead = (rectangleNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 圆角矩形:
			((rRectangleNode)copyGraph)->data.startX += 1;
			((rRectangleNode)copyGraph)->data.startY += 1;
			((rRectangleNode)copyGraph)->data.endX += 1;
			((rRectangleNode)copyGraph)->data.endY += 1;
			if (rRectangleHead == NULL)
				rRectangleHead = (rRectangleNode)copyGraph;
			else
			{
				((rRectangleNode)copyGraph)->pNext = rRectangleHead;
				rRectangleHead = (rRectangleNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 菱形:
			((diamNode)copyGraph)->data.startX += 1;
			((diamNode)copyGraph)->data.startY += 1;
			((diamNode)copyGraph)->data.endX += 1;
			((diamNode)copyGraph)->data.endY += 1;
			if (diamondHead == NULL)
				diamondHead = (diamNode)copyGraph;
			else
			{
				((diamNode)copyGraph)->pNext = diamondHead;
				diamondHead = (diamNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 直线:
			((lineNode)copyGraph)->data.startX += 1;
			((lineNode)copyGraph)->data.startY += 1;
			((lineNode)copyGraph)->data.endX += 1;
			((lineNode)copyGraph)->data.endY += 1;
			if (lineHead == NULL)
				lineHead = (lineNode)copyGraph;
			else
			{
				((lineNode)copyGraph)->pNext = lineHead;
				lineHead = (lineNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 单向箭头:
			((arrowNode)copyGraph)->data.startX += 1;
			((arrowNode)copyGraph)->data.startY += 1;
			((arrowNode)copyGraph)->data.endX += 1;
			((arrowNode)copyGraph)->data.endY += 1;
			if (arrowHead == NULL)
				arrowHead = (arrowNode)copyGraph;
			else
			{
				((arrowNode)copyGraph)->pNext = arrowHead;
				arrowHead = (arrowNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 双向箭头:
			((dArrowNode)copyGraph)->data.startX += 1;
			((dArrowNode)copyGraph)->data.startY += 1;
			((dArrowNode)copyGraph)->data.endX += 1;
			((dArrowNode)copyGraph)->data.endY += 1;
			if (dArrowHead == NULL)
				dArrowHead = (dArrowNode)copyGraph;
			else
			{
				((dArrowNode)copyGraph)->pNext = dArrowHead;
				dArrowHead = (dArrowNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 平行四边形:
			((paraNode)copyGraph)->data.startX += 1;
			((paraNode)copyGraph)->data.startY += 1;
			((paraNode)copyGraph)->data.endX += 1;
			((paraNode)copyGraph)->data.endY += 1;
			if (paraHead == NULL)
				paraHead = (paraNode)copyGraph;
			else
			{
				((paraNode)copyGraph)->pNext = paraHead;
				paraHead = (paraNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 圆形:
			((circleNode)copyGraph)->data.startX += 1;
			((circleNode)copyGraph)->data.startY += 1;
			if (circleHead == NULL)
				circleHead = (circleNode)copyGraph;
			else
			{
				((circleNode)copyGraph)->pNext = circleHead;
				circleHead = (circleNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		case 椭圆形:
			((ovalNode)copyGraph)->data.startX += 1;
			((ovalNode)copyGraph)->data.startY += 1;
			if (ovalHead == NULL)
				ovalHead = (ovalNode)copyGraph;
			else
			{
				((ovalNode)copyGraph)->pNext = ovalHead;
				ovalHead = (ovalNode)copyGraph;
			}
			copyGraph = NULL;
			break;
		}
	}
}

/*删除*/
void del(void)
{
	if (selectedGraph != NULL)
	{
		void* tmp;/*一个临时的节点*/
		switch (type)
		{
		case 矩形:
			tmp = (rectangleNode)malloc(sizeof(recNode));
			tmp = rectangleHead;
			if ((rectangleNode)tmp == (rectangleNode)selectedGraph)
			{
				rectangleHead = ((rectangleNode)tmp)->pNext;
			}
			else
			{
				while (((rectangleNode)tmp)->pNext != (rectangleNode)selectedGraph)
					(rectangleNode)tmp = ((rectangleNode)tmp)->pNext;/*链表后移*/
				((rectangleNode)tmp)->pNext = ((rectangleNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 圆角矩形:
			tmp = (rRectangleNode)malloc(sizeof(roundedRecNode));
			tmp = rRectangleHead;
			if ((rRectangleNode)tmp == (rRectangleNode)selectedGraph)
			{
				rRectangleHead = ((rRectangleNode)tmp)->pNext;
			}
			else
			{
				while (((rRectangleNode)tmp)->pNext != (rRectangleNode)selectedGraph)
					(rRectangleNode)tmp = ((rRectangleNode)tmp)->pNext;/*链表后移*/
				((rRectangleNode)tmp)->pNext = ((rRectangleNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 菱形:
			tmp = (diamNode)malloc(sizeof(diamondNode));
			tmp = diamondHead;
			if ((diamNode)tmp == (diamNode)selectedGraph)
			{
				diamondHead = ((diamNode)tmp)->pNext;
			}
			else
			{
				while (((diamNode)tmp)->pNext != (diamNode)selectedGraph)
					(diamNode)tmp = ((diamNode)tmp)->pNext;/*链表后移*/
				((diamNode)tmp)->pNext = ((diamNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 直线:
			tmp = (lineNode)malloc(sizeof(lNode));
			tmp = lineHead;
			if ((lineNode)tmp == (lineNode)selectedGraph)
			{
				lineHead = ((lineNode)tmp)->pNext;
			}
			else
			{
				while (((lineNode)tmp)->pNext != (lineNode)selectedGraph)
					(lineNode)tmp = ((lineNode)tmp)->pNext;/*链表后移*/
				((lineNode)tmp)->pNext = ((lineNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 单向箭头:
			tmp = (arrowNode)malloc(sizeof(aNode));
			tmp = arrowHead;
			if ((arrowNode)tmp == (arrowNode)selectedGraph)
			{
				arrowHead = ((arrowNode)tmp)->pNext;
			}
			else
			{
				while (((arrowNode)tmp)->pNext != (arrowNode)selectedGraph)
					(arrowNode)tmp = ((arrowNode)tmp)->pNext;/*链表后移*/
				((arrowNode)tmp)->pNext = ((arrowNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 双向箭头:
			tmp = (dArrowNode)malloc(sizeof(daNode));
			tmp = dArrowHead;
			if ((dArrowNode)tmp == (dArrowNode)selectedGraph)
			{
				dArrowHead = ((dArrowNode)tmp)->pNext;
			}
			else
			{
				while (((dArrowNode)tmp)->pNext != (dArrowNode)selectedGraph)
					(dArrowNode)tmp = ((dArrowNode)tmp)->pNext;/*链表后移*/
				((dArrowNode)tmp)->pNext = ((dArrowNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 平行四边形:
			tmp = (paraNode)malloc(sizeof(pNode));
			tmp = paraHead;
			if ((paraNode)tmp == (paraNode)selectedGraph)
			{
				paraHead = ((paraNode)tmp)->pNext;
			}
			else
			{
				while (((paraNode)tmp)->pNext != (paraNode)selectedGraph)
					(paraNode)tmp = ((paraNode)tmp)->pNext;/*链表后移*/
				((paraNode)tmp)->pNext = ((paraNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 圆形:
			tmp = (circleNode)malloc(sizeof(cNode));
			tmp = circleHead;
			if ((circleNode)tmp == (circleNode)selectedGraph)
			{
				circleHead = ((circleNode)tmp)->pNext;
			}
			else
			{
				while (((circleNode)tmp)->pNext != (circleNode)selectedGraph)
					(circleNode)tmp = ((circleNode)tmp)->pNext;/*链表后移*/
				((circleNode)tmp)->pNext = ((circleNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		case 椭圆形:
			tmp = (ovalNode)malloc(sizeof(oNode));
			tmp = ovalHead;
			if ((ovalNode)tmp == (ovalNode)selectedGraph)
			{
				ovalHead = ((ovalNode)tmp)->pNext;
			}
			else
			{
				while (((ovalNode)tmp)->pNext != (ovalNode)selectedGraph)
					(ovalNode)tmp = ((ovalNode)tmp)->pNext;/*链表后移*/
				((ovalNode)tmp)->pNext = ((ovalNode)selectedGraph)->pNext;/*链表跳过selectedGraph节点*/
			}
			free(selectedGraph);/*释放内存空间*/
			selectedGraph = NULL;
			break;
		}
	}
}

/*剪切*/
void cut(void)
{
	copy();/*先复制*/
	del();/*再删除*/
	/*感觉这整个功能没啥用。。。*/
}

/*打开文件*/
void open(void)
{
	/*以下10行代码来源https://zhidao.baidu.com/question/396541341.html
	调用了系统的api来显示打开文件的对话框*/
	OPENFILENAME ofn;
	char openFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(ofn));
	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(openFile, 0, sizeof(char) * MAX_PATH);
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = (LPWSTR)"文本文件(.txt)\0*.txt\0";
	ofn.lpstrFile = (LPWSTR)openFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_FILEMUSTEXIST;
	int type;/*用来判断读入的图形类型*/
	GetOpenFileName(&ofn);
	if (strlen(openFile))/*openFile里被赋值为了所选文件的地址*/
	{
		FILE* fp = fopen(openFile, "r");
		strcpy(savedFile,openFile);
		fscanf(fp, "%d", &type);
		while (type != 0)
		{
			switch (type)
			{
			case 1:
				rectangleHead = NULL;
				rectangleNode tmp1 = (rectangleNode)malloc(sizeof(recNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &(tmp1->data.startX));
				fscanf(fp, "%lf", &(tmp1->data.startY));
				fscanf(fp, "%lf", &(tmp1->data.endX));
				fscanf(fp, "%lf", &(tmp1->data.endY));
				fscanf(fp, "%d", &(tmp1->data.fillFlag));
				fscanf(fp, "%d\n", &(tmp1->data.penSize));/*加一个\n来消除缓冲区里的\n，防止对fgets操作产生影响，下同*/
				fgets(tmp1->data.fillColor, 15, fp);tmp1->data.fillColor[strlen(tmp1->data.fillColor) - 1] = 0;/*把最后的\n变为\0结束符，下同*/
				fgets(tmp1->data.textColor, 15, fp);tmp1->data.textColor[strlen(tmp1->data.textColor) - 1] = 0;
				fgets(tmp1->data.text, 101, fp);tmp1->data.text[strlen(tmp1->data.text) - 1] = 0;

				tmp1->pNext = NULL;

				/*插入链表头部*/
				if (rectangleHead == NULL)/*判断当前链表的头结点是否为空*/
					rectangleHead = tmp1;
				else
				{
					tmp1->pNext = rectangleHead;
					rectangleHead = tmp1;
				}
				break;
			case 2:
				rRectangleHead = NULL;
				rRectangleNode tmp2 = (rRectangleNode)malloc(sizeof(roundedRecNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp2->data.startX);
				fscanf(fp, "%lf", &tmp2->data.startY);
				fscanf(fp, "%lf", &tmp2->data.endX);
				fscanf(fp, "%lf", &tmp2->data.endY);
				fscanf(fp, "%d", &tmp2->data.fillFlag);
				fscanf(fp, "%d\n", &tmp2->data.penSize);
				fgets(tmp2->data.fillColor, 15, fp);tmp2->data.fillColor[strlen(tmp2->data.fillColor) - 1] = 0;
				fgets(tmp2->data.textColor, 15, fp);tmp2->data.textColor[strlen(tmp2->data.textColor) - 1] = 0;
				fgets(tmp2->data.text, 101, fp);tmp2->data.text[strlen(tmp2->data.text) - 1] = 0;

				tmp2->pNext = NULL;

				/*插入链表头部*/
				if (rRectangleHead == NULL)/*判断当前链表的头结点是否为空*/
					rRectangleHead = tmp2;
				else
				{
					tmp2->pNext = rRectangleHead;
					rRectangleHead = tmp2;
				}
				break;
			case 3:
				diamondHead = NULL;
				diamNode tmp3 = (diamNode)malloc(sizeof(diamondNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp3->data.startX);
				fscanf(fp, "%lf", &tmp3->data.startY);
				fscanf(fp, "%lf", &tmp3->data.endX);
				fscanf(fp, "%lf", &tmp3->data.endY);
				fscanf(fp, "%d", &tmp3->data.fillFlag);
				fscanf(fp, "%d\n", &tmp3->data.penSize);
				fgets(tmp3->data.fillColor, 15, fp);tmp3->data.fillColor[strlen(tmp3->data.fillColor) - 1] = 0;
				fgets(tmp3->data.textColor, 15, fp);tmp3->data.textColor[strlen(tmp3->data.textColor) - 1] = 0;
				fgets(tmp3->data.text, 101, fp);tmp3->data.text[strlen(tmp3->data.text) - 1] = 0;
								
				tmp3->pNext = NULL;

				/*插入链表头部*/
				if (diamondHead == NULL)/*判断当前链表的头结点是否为空*/
					diamondHead = tmp3;
				else
				{
					tmp3->pNext = diamondHead;
					diamondHead = tmp3;
				}
				break;
			case 4:
				lineHead = NULL;
				lineNode tmp4 = (lineNode)malloc(sizeof(lNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp4->data.startX);
				fscanf(fp, "%lf", &tmp4->data.startY);
				fscanf(fp, "%lf", &tmp4->data.endX);
				fscanf(fp, "%lf", &tmp4->data.endY);
				fscanf(fp, "%d", &tmp4->data.penSize);
				fscanf(fp, "%s", tmp4->data.fillColor);

				tmp4->pNext = NULL;

				/*插入链表头部*/
				if (lineHead == NULL)/*判断当前链表的头结点是否为空*/
					lineHead = tmp4;
				else
				{
					tmp4->pNext = lineHead;
					lineHead = tmp4;
				}
				break;
			case 5:
				arrowHead = NULL;
				arrowNode tmp5 = (arrowNode)malloc(sizeof(aNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp5->data.startX);
				fscanf(fp, "%lf", &tmp5->data.startY);
				fscanf(fp, "%lf", &tmp5->data.endX);
				fscanf(fp, "%lf", &tmp5->data.endY);
				fscanf(fp, "%d", &tmp5->data.penSize);
				fscanf(fp, "%s", tmp5->data.fillColor);

				tmp5->pNext = NULL;

				/*插入链表头部*/
				if (arrowHead == NULL)/*判断当前链表的头结点是否为空*/
					arrowHead = tmp5;
				else
				{
					tmp5->pNext = arrowHead;
					arrowHead = tmp5;
				}
				break;
			case 6:
				dArrowHead = NULL;
				dArrowNode tmp6 = (dArrowNode)malloc(sizeof(daNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp6->data.startX);
				fscanf(fp, "%lf", &tmp6->data.startY);
				fscanf(fp, "%lf", &tmp6->data.endX);
				fscanf(fp, "%lf", &tmp6->data.endY);
				fscanf(fp, "%d", &tmp6->data.penSize);
				fscanf(fp, "%s", tmp6->data.fillColor);
				
				tmp6->pNext = NULL;

				/*插入链表头部*/
				if (dArrowHead == NULL)/*判断当前链表的头结点是否为空*/
					dArrowHead = tmp6;
				else
				{
					tmp6->pNext = dArrowHead;
					dArrowHead = tmp6;
				}
				break;
			case 7:
				paraHead = NULL;
				paraNode tmp7 = (paraNode)malloc(sizeof(pNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp7->data.startX);
				fscanf(fp, "%lf", &tmp7->data.startY);
				fscanf(fp, "%lf", &tmp7->data.endX);
				fscanf(fp, "%lf", &tmp7->data.endY);
				fscanf(fp, "%d", &tmp7->data.fillFlag);
				fscanf(fp, "%d\n", &tmp7->data.penSize);
				fgets(tmp7->data.fillColor, 15, fp);tmp7->data.fillColor[strlen(tmp7->data.fillColor) - 1] = 0;
				fgets(tmp7->data.textColor, 15, fp);tmp7->data.textColor[strlen(tmp7->data.textColor) - 1] = 0;
				fgets(tmp7->data.text, 101, fp);tmp7->data.text[strlen(tmp7->data.text) - 1] = 0;
				

				tmp7->pNext = NULL;

				/*插入链表头部*/
				if (paraHead == NULL)/*判断当前链表的头结点是否为空*/
					paraHead = tmp7;
				else
				{
					tmp7->pNext = paraHead;
					paraHead = tmp7;
				}
				break;
			case 8:
				circleHead = NULL;
				circleNode tmp8 = (circleNode)malloc(sizeof(cNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp8->data.startX);
				fscanf(fp, "%lf", &tmp8->data.startY);
				fscanf(fp, "%lf", &tmp8->data.radius);
				fscanf(fp, "%d", &tmp8->data.fillFlag);
				fscanf(fp, "%d\n", &tmp8->data.penSize);
				fgets(tmp8->data.fillColor, 15, fp);tmp8->data.fillColor[strlen(tmp8->data.fillColor) - 1] = 0;
				fgets(tmp8->data.textColor, 15, fp);tmp8->data.textColor[strlen(tmp8->data.textColor) - 1] = 0;
				fgets(tmp8->data.text, 101, fp);tmp8->data.text[strlen(tmp8->data.text) - 1] = 0;
				
				tmp8->pNext = NULL;

				/*插入链表头部*/
				if (circleHead == NULL)/*判断当前链表的头结点是否为空*/
					circleHead = tmp8;
				else
				{
					tmp8->pNext = circleHead;
					circleHead = tmp8;
				}
				break;
			case 9:
				ovalHead = NULL;
				ovalNode tmp9 = (ovalNode)malloc(sizeof(oNode));/*创建一个临时的节点，用来加入链表的头*/
				fscanf(fp, "%lf", &tmp9->data.startX);
				fscanf(fp, "%lf", &tmp9->data.startY);
				fscanf(fp, "%lf", &tmp9->data.xRadius);
				fscanf(fp, "%lf", &tmp9->data.yRadius);
				fscanf(fp, "%d", &tmp9->data.fillFlag);
				fscanf(fp, "%d\n", &tmp9->data.penSize);
				fgets(tmp9->data.fillColor, 15, fp);tmp9->data.fillColor[strlen(tmp9->data.fillColor) - 1] = 0;
				fgets(tmp9->data.textColor, 15, fp);tmp9->data.textColor[strlen(tmp9->data.textColor) - 1] = 0;
				fgets(tmp9->data.text, 101, fp);tmp9->data.text[strlen(tmp9->data.text) - 1] = 0;

				tmp9->pNext = NULL;

				/*插入链表头部*/
				if (ovalHead == NULL)/*判断当前链表的头结点是否为空*/
					ovalHead = tmp9;
				else
				{
					tmp9->pNext = ovalHead;
					ovalHead = tmp9;
				}
				break;
			}
			fscanf(fp, "%d", &type);
		}
	}
}

/*保存文件*/
void save(void)
{
	/*打开对话框*/
	OPENFILENAME ofn;
	char saveFile[MAX_PATH];
	ZeroMemory(&ofn, sizeof(ofn));
	memset(&ofn, 0, sizeof(OPENFILENAME));
	memset(saveFile, 0, sizeof(char) * MAX_PATH);
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFilter = (LPWSTR)"文本文件(.txt)\0*.txt\0";
	ofn.lpstrFile = (LPWSTR)saveFile;
	ofn.nMaxFile = MAX_PATH;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	if (strlen(savedFile) == 0 || isSaveAs == TRUE) GetSaveFileName(&ofn);
	else strcpy(saveFile, savedFile);
	if (strlen(saveFile))/*saveFile里被赋值为了保存的文件的地址*/
	{
		FILE* fp;
		if(strcmp(saveFile+strlen(saveFile)-4,".txt"))/*放置重复添加后缀名*/
			fp = fopen(strcat(saveFile, ".txt"), "w+");/*先新建再读写*/
		else
			fp = fopen(saveFile, "w+");
		strcpy(savedFile, saveFile);

		/*写矩形*/
		rectangleNode tmp1 = rectangleHead;
		while (tmp1 != NULL)
		{
			/*开头写个1表示为矩形*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%d\n%s\n%s\n%s\n", 1,
				tmp1->data.startX, tmp1->data.startY, tmp1->data.endX, tmp1->data.endY, tmp1->data.fillFlag, tmp1->data.penSize, tmp1->data.fillColor, tmp1->data.textColor, tmp1->data.text);
			tmp1 = tmp1->pNext;
		}
		free(tmp1);

		/*写圆角矩形*/
		rRectangleNode tmp2 = rRectangleHead;
		while (tmp2 != NULL)
		{
			/*开头写个2表示为圆角矩形*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%d\n%s\n%s\n%s\n", 2,
				tmp2->data.startX, tmp2->data.startY, tmp2->data.endX, tmp2->data.endY, tmp2->data.fillFlag, tmp2->data.penSize, tmp2->data.fillColor, tmp2->data.textColor, tmp2->data.text);
			tmp2 = tmp2->pNext;
		}
		free(tmp2);

		/*写菱形*/
		diamNode tmp3 = diamondHead;
		while (tmp3 != NULL)
		{
			/*开头写个3表示为菱形*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%d\n%s\n%s\n%s\n", 3,
				tmp3->data.startX, tmp3->data.startY, tmp3->data.endX, tmp3->data.endY, tmp3->data.fillFlag, tmp3->data.penSize, tmp3->data.fillColor, tmp3->data.textColor, tmp3->data.text);
			tmp3 = tmp3->pNext;
		}
		free(tmp3);

		/*写直线*/
		lineNode tmp4 = lineHead;
		while (tmp4 != NULL)
		{
			/*开头写个4表示为直线*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%s\n", 4,
				tmp4->data.startX, tmp4->data.startY, tmp4->data.endX, tmp4->data.endY, tmp4->data.penSize, tmp4->data.fillColor);
			tmp4 = tmp4->pNext;
		}
		free(tmp4);

		/*写单向箭头*/
		arrowNode tmp5 = arrowHead;
		while (tmp5 != NULL)
		{
			/*开头写个5表示为单向箭头*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%s\n", 5,
				tmp5->data.startX, tmp5->data.startY, tmp5->data.endX, tmp5->data.endY, tmp5->data.penSize, tmp5->data.fillColor);
			tmp5 = tmp5->pNext;
		}
		free(tmp5);

		/*写双向箭头*/
		dArrowNode tmp6 = dArrowHead;
		while (tmp6 != NULL)
		{
			/*开头写个6表示为双向箭头*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%s\n", 6,
				tmp6->data.startX, tmp6->data.startY, tmp6->data.endX, tmp6->data.endY, tmp6->data.penSize, tmp6->data.fillColor);
			tmp6 = tmp6->pNext;
		}
		free(tmp6);

		/*写平行四边形*/
		paraNode tmp7 = paraHead;
		while (tmp7 != NULL)
		{
			/*开头写个7表示为平行四边形*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%d\n%s\n%s\n%s\n", 7,
				tmp7->data.startX, tmp7->data.startY, tmp7->data.endX, tmp7->data.endY, tmp7->data.fillFlag, tmp7->data.penSize, tmp7->data.fillColor, tmp7->data.textColor, tmp7->data.text);
			tmp7 = tmp7->pNext;
		}
		free(tmp7);

		/*写圆形*/
		circleNode tmp8 = circleHead;
		while (tmp8 != NULL)
		{
			/*开头写个8表示为圆形*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%d\n%d\n%s\n%s\n%s\n", 8,
				tmp8->data.startX, tmp8->data.startY, tmp8->data.radius, tmp8->data.fillFlag, tmp8->data.penSize, tmp8->data.fillColor, tmp8->data.textColor, tmp8->data.text);
			tmp8 = tmp8->pNext;
		}
		free(tmp8);

		/*写椭圆形*/
		ovalNode tmp9 = ovalHead;
		while (tmp9 != NULL)
		{
			/*开头写个9表示为椭圆形*/
			fprintf(fp, "%d\n%f\n%f\n%f\n%f\n%d\n%d\n%s\n%s\n%s\n", 9,
				tmp9->data.startX, tmp9->data.startY, tmp9->data.xRadius, tmp9->data.yRadius, tmp9->data.fillFlag, tmp9->data.penSize, tmp9->data.fillColor, tmp9->data.textColor, tmp9->data.text);
			tmp9 = tmp9->pNext;
		}
		free(tmp9);

		fprintf(fp, "%d", 0);/*表示结束*/

		fclose(fp);
	}
}
