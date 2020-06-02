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


/* �˵���ʾ����*/
void drawMenu()
{
/*���崰�ڳߴ磨Ӣ�磩*/
double windowWidth, windowHeight;

/*����menu�ĳߴ�(Ӣ�磩*/
double menuHeight = 0.4, menuWidth;

/*����menu list�Ŀ�ȣ�Ӣ�磩*/
double menuListWidth;

windowWidth = GetWindowWidth();
windowHeight = GetWindowHeight();

	static char* menuListFile[] = { "�ļ�",
		"�½� | Ctrl-N",
		"�� | Ctrl-O",
		"���� | Ctrl-S",
		"�˳� | Ctrl-E" };
	static char* menuListTool[] = { "�༭",
		"���� | Ctrl-C",
		"���� | Ctrl-X",
		"ճ�� | Ctrl-V",
		"ɾ�� | Delete" };
	static char* menuListDraw[] = { "��ͼ",
		"����",
		"Բ�Ǿ���",
		"����",
		"��ͷ",
		"���߼�ͷ",
		"�ı���" };
	static char* menuListHelp[] = { "����",
		"�鿴����",
		"����" };

	static char* selectedLabel = NULL;

	menuWidth = TextStringWidth(menuListHelp[0]) * 2; /* �ؼ���ȣ�ȡ�������ֳ���*/
	menuListWidth = TextStringWidth(menuListTool[3]) * 1.2;

	int    selection;

	/* File �˵�*/
	selection = menuList(GenUIID(0), 0, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 3)
		exit(-1); // choose to exit

	/* Tool �˵�*/
	selection = menuList(GenUIID(0), 1 * menuWidth, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListTool, sizeof(menuListTool) / sizeof(menuListTool[0]));

	/* draw �˵�*/
	selection = menuList(GenUIID(0), 2 * menuWidth, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));

	/* Help �˵�*/
	selection = menuList(GenUIID(0), 3 * menuWidth, windowHeight - menuHeight, menuWidth, menuListWidth, menuHeight, menuListHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));

	drawMenuBar(4 * menuWidth, windowHeight - menuHeight, windowWidth - 4 * menuWidth, menuHeight);
}