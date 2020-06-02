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

#include "menu.h"


/* 菜单演示程序*/
void drawMenu()
{
/*定义窗口尺寸（英寸）*/
double windowWidth, windowHeight;

/*定义menu的尺寸(英寸）*/
double menuHeight = 0.4, menuWidth;

/*定义menu list的宽度（英寸）*/
double menuListWidth;

windowWidth = GetWindowWidth();
windowHeight = GetWindowHeight();

	static char* menuListFile[] = { "文件",
		"新建 | Ctrl-N",
		"打开 | Ctrl-O",
		"保存 | Ctrl-S",
		"退出 | Ctrl-E" };
	static char* menuListTool[] = { "编辑",
		"复制 | Ctrl-C",
		"剪切 | Ctrl-X",
		"粘贴 | Ctrl-V",
		"删除 | Delete" };
	static char* menuListDraw[] = { "绘图",
		"矩形",
		"圆角矩形",
		"菱形",
		"箭头",
		"折线箭头",
		"文本框" };
	static char* menuListHelp[] = { "帮助",
		"查看帮助",
		"关于" };

	static char* selectedLabel = NULL;

	menuWidth = TextStringWidth(menuListHelp[0]) * 2; /* 控件宽度，取决于文字长度*/
	menuListWidth = TextStringWidth(menuListTool[3]) * 1.2;

	int    selection;

	/* File 菜单*/
	selection = menuList(GenUIID(0), 0, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 3)
		exit(-1); // choose to exit

	/* Tool 菜单*/
	selection = menuList(GenUIID(0), 1 * menuWidth, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListTool, sizeof(menuListTool) / sizeof(menuListTool[0]));

	/* draw 菜单*/
	selection = menuList(GenUIID(0), 2 * menuWidth, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));

	/* Help 菜单*/
	selection = menuList(GenUIID(0), 3 * menuWidth, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));

	drawMenuBar(4 * menuWidth, windowHeight - menuHeight, windowWidth - 4 * menuWidth, menuHeight);
}