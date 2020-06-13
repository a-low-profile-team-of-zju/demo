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

/*初始化menu*/
void initMenu(void)
{
	SetPenSize(1);
	setMenuColors("Dark Gray", "White", "Black", "White", 1);
	double fontHeight = GetFontHeight();/*获取文本高度*/
	double menuHeight = 1.5 * fontHeight, defaultMenuWidth;
	int selection;

	/*----------------------------------------------------------------------------------英文菜单--------------------------------------------------------------------------------*/
	static char* menuListFile[] = { "File",
		"New  | Ctrl-N",
		"Open | Ctrl-O",
		"Save | Ctrl-S",
		"Save as",
		"Close",
		"Exit"
	};
	static char* menuListEdit[] = { "Edit",
		"Cut    | Ctrl-X",
		"Copy   | Ctrl-C",
		"Paste  | Ctrl-V",
		"Delete | Ctrl-D" ,
		"Enlarge | Ctrl-E",
		"Reduce | Ctrl-R",
		"Fill/Unfill | Ctrl-F"
	};
	static char* menuListDraw[] = { "Draw",
		"Rectangle",
		"RoundedRec",
		"Diamond",
		"Line",
		"Arrow" ,
		"DoubleheadedArrow",
		"Parallelogram",
		"Circle",
		"Oval"
	};
	static char* menuListHelp[] = { "Help",
		"About us",
		"More info",
		"Switch Language"
	};
	static char* menuListFillColors[] = { "Fill Colors",
		"Black(default)",
		"Dark Gray",
		"Gray",
		"Light Gray",
		"White(!)",
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
	static char* menuListFontColors[] = { "Font Colors",
		"Black(default)",
		"Dark Gray",
		"Gray",
		"Light Gray",
		"White(!)",
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
	static char* menuListPenSize[] = { "Pen Size",
		"#1 Line",
		"#2 Line",
		"#3 Line",
		"#4 Line",
		"#5 Line"
	};

	/*----------------------------------------------------------------------------------中文菜单--------------------------------------------------------------------------------*/
	static char* menuListCFile[] = { "文件",
		"新建  | Ctrl-N",
		"打开 | Ctrl-O",
		"保存 | Ctrl-S",
		"另存为",
		"关闭",
		"退出"
	};
	static char* menuListCEdit[] = { "编辑",
		"剪切    | Ctrl-X",
		"复制   | Ctrl-C",
		"粘贴  | Ctrl-V",
		"删除 | Ctrl-D" ,
		"放大 | Ctrl-E",
		"缩小 | Ctrl-R",
		"填充/不填充 | Ctrl-F"
	};
	static char* menuListCDraw[] = { "绘图",
		"矩形",
		"圆角矩形",
		"菱形",
		"直线",
		"单向箭头" ,
		"双向箭头",
		"平行四边形",
		"圆形",
		"椭圆形"
	};
	static char* menuListCHelp[] = { "帮助",
		"关于我们",
		"更多信息",
		"切换语言"
	};
	static char* menuListCFillColors[] = { "填充颜色",
		"黑色(默认)",
		"深灰色",
		"灰色",
		"亮灰色",
		"白色(!)",
		"棕色",
		"红色",
		"橙色",
		"黄色",
		"绿色",
		"蓝色",
		"蓝紫色",
		"品红色",
		"青色"
	};
	static char* menuListCFontColors[] = { "文本颜色",
		"黑色(默认)",
		"深灰色",
		"灰色",
		"亮灰色",
		"白色(!)",
		"棕色",
		"红色",
		"橙色",
		"黄色",
		"绿色",
		"蓝色",
		"蓝紫色",
		"品红色",
		"青色"
	};
	static char* menuListCPenSize[] = { "画笔大小",
		"1号线条",
		"2号线条",
		"3号线条",
		"4号线条",
		"5号线条"
	};

	defaultMenuWidth = TextStringWidth(menuListFile[0]) * 4;

	/*menuBar*/
	drawMenuBar(0, winHeight - menuHeight, winWidth, menuHeight);

	/*File菜单*/
	selection = menuList(GenUIID(0), 0 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListFile[2]) * 1.5, menuHeight, !lang ? menuListFile : menuListCFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 1)
	{
		/*保存后，统统初始化！*/
		if (rectangleHead ||
			rRectangleHead ||
			diamondHead ||
			lineHead ||
			arrowHead ||
			dArrowHead ||
			paraHead ||
			circleHead ||
			ovalHead )save();
		char lpFileName[MAX_PATH];/*代码来源https://zhidao.baidu.com/question/518459589225069325.html*/
		GetModuleFileName(NULL, lpFileName, MAX_PATH);
		// 运行新的自身
		SHELLEXECUTEINFO ShExecInfo;
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = NULL;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = lpFileName; // 执行的程序名
		ShExecInfo.lpParameters = NULL;
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_NORMAL;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		//关闭自身
		exit(0);
	}
	else if (selection == 2)
	{
		open();
		
	}
	else if (selection == 3)
	{
		isSaveAs = FALSE;
		save();
		
	}
	else if (selection == 4)
	{
		isSaveAs = TRUE;
		save();
		
	}
	else if (selection == 5)
	{
		if (MessageBox(NULL, !lang ? "Need save the file?" : "需要保存当前文件吗？", 
			!lang ? "Attention" : "注意", MB_YESNO | MB_ICONQUESTION) == IDYES)/*调用了系统api，生成一个对话框*/
		{
			isSaveAs = TRUE;
			save();		
		}
		else
			exit(0);
		
	}
	else if (selection == 6)
	{
		exit(0);
	}

	/*Edit菜单*/
	selection = menuList(GenUIID(0), 1 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListEdit[7]) * 1.5, menuHeight, !lang ? menuListEdit : menuListCEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	if (selection == 1)
	{
		cut();
		
	}
	else if (selection == 2)
	{
		copy();
		
	}
	else if (selection == 3)
	{
		paste();
		
	}
	else if (selection == 4)
	{
		del();
		
	}
	else if (selection == 5)
	{
		enlargeGraphicSize();
		
	}
	else if (selection == 6)
	{
		reduceGraphicSize();
		
	}
	else if (selection == 7)
	{
		fill();
		
	}

	/*Draw菜单*/
	selection = menuList(GenUIID(0), 2 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListDraw[6]) * 1.5, menuHeight, !lang ? menuListDraw : menuListCDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	if (selection)
	{
		operation = draw;
		type = selection;
		
	}

	/*Fill Colors菜单*/
	selection = menuList(GenUIID(0), 3 * defaultMenuWidth, winHeight - menuHeight, 1.5 * defaultMenuWidth, TextStringWidth(menuListFillColors[1]) * 2, menuHeight, !lang ? menuListFillColors : menuListCFillColors, sizeof(menuListFillColors) / sizeof(menuListFillColors[0]));
	if (selection)
	{
	//if (operation == selected)/*不要加这个*/
	//{
	changeFillColor(selection - 1);
	
	//}
	}

	/*Font Colors菜单*/
	selection = menuList(GenUIID(0), 4.5 * defaultMenuWidth, winHeight - menuHeight, 1.5 * defaultMenuWidth, TextStringWidth(menuListFillColors[1]) * 2, menuHeight,!lang ?  menuListFontColors : menuListCFontColors, sizeof(menuListFontColors) / sizeof(menuListFontColors[0]));
	if (selection)
	{
		//if (operation == selected)
		//{
		changeTextColor(selection - 1);
		
		//}
	}

	/*Pen Size菜单*/
	selection = menuList(GenUIID(0), 6 * defaultMenuWidth, winHeight - menuHeight, 1.5 * defaultMenuWidth, TextStringWidth(menuListFillColors[1]) * 2, menuHeight, !lang ? menuListPenSize : menuListCPenSize, sizeof(menuListPenSize) / sizeof(menuListPenSize[0]));
	if (selection)
	{
		changePenSize(selection);
		
	}

	/*Help菜单*/
	selection = menuList(GenUIID(0), 7.5 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListHelp[3]) * 2, menuHeight, !lang ? menuListHelp : menuListCHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection == 1)
	{
		/*"About us"的功能*/
	}
	else if (selection == 2)
	{
		ShellExecute(NULL, "open", "https://github.com/a-low-profile-team-of-zju/demo", NULL, NULL, SW_HIDE);/*导向我们的GitHub项目页*/
		
	}
	else if (selection == 3)
	{
		if (lang == English)
			lang = Chinese;
		else
			lang = English;
	}
}

/*初始化buttomBar，用来显示当前状态和输入文本框*/
void initButtomBar(void)
{
	char status[10];
	double fontHeight = GetFontHeight();/*获取文本高度*/
	double barHeight = 1.5 * fontHeight;
	double statusWidth = 11.25*GetFontHeight();

	switch (operation)
	{
	case none:
		strcpy(status, !lang ? "None" : "无操作");
		break;
	case draw:
		strcpy(status, !lang ? "Drawing" : "绘图中");
		break;
	case selected:
		if (moveFlag)
			strcpy(status, !lang ? "Moving" : "移动中");
		else
			strcpy(status, !lang ? "Selecting" : "选中");
		break;
	}
	/*画一个menuBar作为背景*/
	drawMenuBar(0,0,winWidth,barHeight);

	SetPenColor("White");
	/*显示当前操作状态*/
	drawLabel((statusWidth - TextStringWidth(status)) / 2, (barHeight-fontHeight)/2, status);
	
	setTextBoxColors("Gray", "Black", "Gray", "Black", 1);
	if (textbox(GenUIID(0), statusWidth, 0, winWidth-statusWidth, barHeight, tmpText, 101)) 
	{
		if (selectedGraph != NULL)
		{
			switch (type)
			{
			case 矩形:
				strcpy(((rectangleNode)selectedGraph)->data.text, tmpText);
				break;
			case 圆角矩形:
				strcpy(((rRectangleNode)selectedGraph)->data.text, tmpText);
				break;
			case 菱形:
				strcpy(((diamNode)selectedGraph)->data.text, tmpText);
				break;
			case 直线:
				break;
			case 单向箭头:
				break;
			case 双向箭头:
				break;
			case 平行四边形:
				strcpy(((paraNode)selectedGraph)->data.text, tmpText);
				break;
			case 圆形:
				strcpy(((circleNode)selectedGraph)->data.text, tmpText);
				break;
			case 椭圆形:
				strcpy(((ovalNode)selectedGraph)->data.text, tmpText);
				break;
			}
		}
		//
	}
}

/*初始化button*/
void initButton(void)
{
	double line = 0.01;/*画笔粗细为1时的线粗*/
	double fontHeight = GetFontHeight();/*获取文本高度*/
	double menuHeight = 1.5 * fontHeight;/*需要借用menu的高度来确定button的位置*/
	double buttonWidth, buttonHeight;
	buttonHeight = 1.5 * menuHeight;/*定义button高为menu高的1.5倍*/
	buttonWidth = 5 * buttonHeight;/*定义button宽为高的5倍*/
	SetPenSize(1);
	setButtonColors("Light Gray", "Black", "Gray", "Black", 1);

	setMenuColors("Light Gray", "White", "Black", "White", 1);
	drawMenuBar(0, menuHeight, buttonWidth, winHeight - 2 * menuHeight);

	//drawBox(0, winHeight - 2 * menuHeight, buttonWidth, menuHeight, 1, "绘图工具栏", 'C', "White");
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 1 * buttonHeight, buttonWidth, buttonHeight, !lang ? "Rectangle" : "矩形"))
	{
		operation = draw;
		type = 矩形;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 2 * buttonHeight, buttonWidth, buttonHeight, !lang ? "RoundedRec" : "圆角矩形"))
	{
		operation = draw;
		type = 圆角矩形;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 3 * buttonHeight, buttonWidth, buttonHeight, !lang ? "Diamond" : "菱形"))
	{
		operation = draw;
		type = 菱形;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 4 * buttonHeight, buttonWidth, buttonHeight, !lang ? "Line" : "直线"))
	{
		operation = draw;
		type = 直线;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 5 * buttonHeight, buttonWidth, buttonHeight, !lang ? "Arrow" : "单向箭头"))
	{
		operation = draw;
		type = 单向箭头;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 6 * buttonHeight, buttonWidth, buttonHeight, !lang ? "DoubleheadedArrow" : "双向箭头"))
	{
		operation = draw;
		type = 双向箭头;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 7 * buttonHeight, buttonWidth, buttonHeight, !lang ? "Parallelogram" : "平行四边形"))
	{
		operation = draw;
		type = 平行四边形;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 8 * buttonHeight, buttonWidth, buttonHeight, !lang ? "Circle" : "圆形"))
	{
		operation = draw;
		type = 圆形;
	}
	if (button(GenUIID(0), 0, winHeight - 2 * menuHeight - 9 * buttonHeight, buttonWidth, buttonHeight, !lang ? "Oval" : "椭圆形"))
	{
		operation = draw;
		type = 椭圆形;
	}

	//drawBox(0, winHeight - 3 * menuHeight - 9 * buttonHeight, buttonWidth, menuHeight, 1, "编辑工具栏", 'C', "White");
	if (button(GenUIID(0), 0, winHeight - 3 * menuHeight - 10 * buttonHeight, buttonWidth / 2, buttonHeight, !lang ? "Cut" : "剪切"))
	{
		cut();
		//display();
	}
	if (button(GenUIID(0), buttonWidth / 2, winHeight - 3 * menuHeight - 10 * buttonHeight, buttonWidth / 2, buttonHeight, !lang ? "Copy" : "复制"))
	{
		copy();
		//display();
	}
	if (button(GenUIID(0), 0, winHeight - 3 * menuHeight - 11 * buttonHeight, buttonWidth / 2, buttonHeight, !lang ? "Paste" : "粘贴"))
	{
		paste();
		//display();
	}
	if (button(GenUIID(0), buttonWidth / 2, winHeight - 3 * menuHeight - 11 * buttonHeight, buttonWidth / 2, buttonHeight, !lang ? "Delete" : "删除"))
	{
		del();
		//display();
	}
	drawBox(0, winHeight - 3 * menuHeight - 9 * buttonHeight, buttonWidth, menuHeight, 1, "编辑工具栏", 'C', "White");
	
	//drawBox(0, winHeight - 4 * menuHeight - 11 * buttonHeight, buttonWidth, menuHeight, 1, "颜色工具栏", 'C', "White");
	if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 12 * buttonHeight, buttonWidth / 2, buttonHeight, !lang ? "Fill Color" : "填充颜色"))
	{
		choose = 0;
	}
	if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 12 * buttonHeight, buttonWidth / 2, buttonHeight, !lang ? "Text Color" : "文本颜色"))
	{
		choose = 1;
	}
	switch (choose)
	{
	case 0:
		setButtonColors("Black", "Black", "Black", "Black", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight,""))changeFillColor(0);
		setButtonColors("Dark Gray", "Dark Gray", "Dark Gray", "Dark Gray", 1);
		if (button(GenUIID(0), buttonWidth / 4, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(1);
		setButtonColors("Gray", "Gray", "Gray", "Gray", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(2);
		setButtonColors("Light Gray", "Light Gray", "Light Gray", "Light Gray", 1);
		if (button(GenUIID(0), buttonWidth * 3 / 4, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(3);
		setButtonColors("White", "White", "White", "White", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(4);
		setButtonColors("Brown", "Brown", "Brown", "Brown", 1);
		if (button(GenUIID(0), buttonWidth / 4, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(5);
		setButtonColors("Red", "Red", "Red", "Red", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(6);
		setButtonColors("Orange", "Orange", "Orange", "Orange", 1);
		if (button(GenUIID(0), buttonWidth * 3 / 4, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(7);
		setButtonColors("Yellow", "Yellow", "Yellow", "Yellow", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(8);
		setButtonColors("Green", "Green", "Green", "Green", 1);
		if (button(GenUIID(0), buttonWidth / 4, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(9);
		setButtonColors("Blue", "Blue", "Blue", "Blue", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(10);
		setButtonColors("Violet", "Violet", "Violet", "Violet", 1);
		if (button(GenUIID(0), buttonWidth * 3 / 4, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeFillColor(11);
		setButtonColors("Magenta", "Magenta", "Magenta", "Magenta", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 16 * buttonHeight - line, buttonWidth / 2, buttonHeight, ""))changeFillColor(12);
		setButtonColors("Cyan", "Cyan", "Cyan", "Cyan", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 16 * buttonHeight - line, buttonWidth / 2, buttonHeight, ""))changeFillColor(13);
		break;
	case 1:
		setButtonColors("Black", "Black", "Black", "Black", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(0);
		setButtonColors("Dark Gray", "Dark Gray", "Dark Gray", "Dark Gray", 1);
		if (button(GenUIID(0), buttonWidth / 4, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(1);
		setButtonColors("Gray", "Gray", "Gray", "Gray", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(2);
		setButtonColors("Light Gray", "Light Gray", "Light Gray", "Light Gray", 1);
		if (button(GenUIID(0), buttonWidth * 3 / 4, winHeight - 4 * menuHeight - 13 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(3);
		setButtonColors("White", "White", "White", "White", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(4);
		setButtonColors("Brown", "Brown", "Brown", "Brown", 1);
		if (button(GenUIID(0), buttonWidth / 4, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(5);
		setButtonColors("Red", "Red", "Red", "Red", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(6);
		setButtonColors("Orange", "Orange", "Orange", "Orange", 1);
		if (button(GenUIID(0), buttonWidth * 3 / 4, winHeight - 4 * menuHeight - 14 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(7);
		setButtonColors("Yellow", "Yellow", "Yellow", "Yellow", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(8);
		setButtonColors("Green", "Green", "Green", "Green", 1);
		if (button(GenUIID(0), buttonWidth / 4, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(9);
		setButtonColors("Blue", "Blue", "Blue", "Blue", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(10);
		setButtonColors("Violet", "Violet", "Violet", "Violet", 1);
		if (button(GenUIID(0), buttonWidth * 3 / 4, winHeight - 4 * menuHeight - 15 * buttonHeight - line, buttonWidth / 4, buttonHeight, ""))changeTextColor(11);
		setButtonColors("Magenta", "Magenta", "Magenta", "Magenta", 1);
		if (button(GenUIID(0), 0, winHeight - 4 * menuHeight - 16 * buttonHeight - line, buttonWidth / 2, buttonHeight, ""))changeTextColor(12);
		setButtonColors("Cyan", "Cyan", "Cyan", "Cyan", 1);
		if (button(GenUIID(0), buttonWidth / 2, winHeight - 4 * menuHeight - 16 * buttonHeight - line, buttonWidth / 2, buttonHeight, ""))changeTextColor(13);
		break;
	}

	SetPenColor("Dark Gray");
	drawBox(0, winHeight - 2 * menuHeight, buttonWidth, menuHeight, 1, !lang ? "Draw Tool" : "绘图工具栏", 'C', "White");
	SetPenColor("Dark Gray");
	drawBox(0, winHeight - 3 * menuHeight - 9 * buttonHeight, buttonWidth, menuHeight, 1, !lang ? "Edit Tool" : "编辑工具栏", 'C', "White");
	SetPenColor("Dark Gray");
	drawBox(0, winHeight - 4 * menuHeight - 11 * buttonHeight, buttonWidth, menuHeight, 1, !lang ? "Color Tool" : "颜色工具栏", 'C', "White");

	//
}
