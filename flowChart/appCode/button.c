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

#include "button.h"

/*用来判断当前是绘制界面还是编辑界面*/
enum
 {
	draw, edit
 } currentButton = draw;/*默认为绘制界面*/

/*绘制按钮*/
void drawButton(void)
{


/*定义窗口尺寸（英寸）*/
double windowWidth, windowHeight;

 /*定义上方按钮的尺寸（英寸）*/
 double topButtonsWidth = 1.5, topButtonsHeight = 1.2;

 /*定义下方按钮的尺寸（英寸）*/
 double sideButtonsWidth = 3.0, sideButtonsHeight = 1.0;

 /*定义menu的尺寸(英寸）*/
 double menuHeight = 0.4;

 windowWidth = GetWindowWidth();
 windowHeight = GetWindowHeight();

	if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight, topButtonsWidth, topButtonsHeight, "绘制"))
	{
		currentButton = draw;
	}

	if (button(GenUIID(0), topButtonsWidth, windowHeight - menuHeight - topButtonsHeight, topButtonsWidth, topButtonsHeight, "编辑"))
	{
		currentButton = edit;
	}
	if (currentButton)/*如果按下绘制按钮则显示绘制下的各个按钮，如果是编辑按钮亦然*/
	{
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 1 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "改变颜色"))
		{
			/*待填写改变颜色功能*/
		}

		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 2 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "增加线宽"))
		{
			/*待填写增加线宽功能*/
		}

		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 3 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "减少线宽"))
		{
			/*待填写减少线宽功能*/
		}
	}
	else
	{
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 1 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "矩形"))
		{
			/*待写功能*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 2 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "圆角矩形"))
		{
			/*待写功能*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 3 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "菱形"))
		{
			/*待写功能*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 4 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "箭头"))
		{
			/*待写功能*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 5 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "折线箭头"))
		{
			/*待写功能*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 6 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "文本框"))
		{
			/*待写功能*/
		}
	}
}