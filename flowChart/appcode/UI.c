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

/*��ʼ��menu*/
void initMenu(void)
{
	SetPenSize(1);
	setMenuColors("Dark Gray", "White", "Black", "White", 1);
	double fontHeight = GetFontHeight();/*��ȡ�ı��߶�*/
	double menuHeight = 1.5 * fontHeight, defaultMenuWidth;
	int selection;

	/*----------------------------------------------------------------------------------Ӣ�Ĳ˵�--------------------------------------------------------------------------------*/
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
		"parallelogram",
		"circle",
		"oval"
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

	/*----------------------------------------------------------------------------------���Ĳ˵�--------------------------------------------------------------------------------*/
	static char* menuListCFile[] = { "�ļ�",
		"�½�  | Ctrl-N",
		"�� | Ctrl-O",
		"���� | Ctrl-S",
		"���Ϊ",
		"�ر�",
		"�˳�"
	};
	static char* menuListCEdit[] = { "�༭",
		"����    | Ctrl-X",
		"����   | Ctrl-C",
		"ճ��  | Ctrl-V",
		"ɾ�� | Ctrl-D" ,
		"�Ŵ� | Ctrl-E",
		"��С | Ctrl-R",
		"���/����� | Ctrl-F"
	};
	static char* menuListCDraw[] = { "��ͼ",
		"����",
		"Բ�Ǿ���",
		"����",
		"ֱ��",
		"�����ͷ" ,
		"˫���ͷ",
		"ƽ���ı���",
		"Բ��",
		"��Բ��"
	};
	static char* menuListCHelp[] = { "����",
		"��������",
		"������Ϣ",
		"�л�����"
	};
	static char* menuListCFillColors[] = { "�����ɫ",
		"��ɫ(Ĭ��)",
		"���ɫ",
		"��ɫ",
		"����ɫ",
		"��ɫ(!)",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"����ɫ",
		"Ʒ��ɫ",
		"��ɫ"
	};
	static char* menuListCFontColors[] = { "�ı���ɫ",
		"��ɫ(Ĭ��)",
		"���ɫ",
		"��ɫ",
		"����ɫ",
		"��ɫ(!)",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"��ɫ",
		"����ɫ",
		"Ʒ��ɫ",
		"��ɫ"
	};
	static char* menuListCPenSize[] = { "���ʴ�С",
		"1������",
		"2������",
		"3������",
		"4������",
		"5������"
	};

	defaultMenuWidth = TextStringWidth(menuListFile[0]) * 4;

	/*menuBar*/
	drawMenuBar(0, winHeight - menuHeight, winWidth, menuHeight);

	/*File�˵�*/
	selection = menuList(GenUIID(0), 0 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListFile[2]) * 1.5, menuHeight, lang ? menuListFile : menuListCFile, sizeof(menuListFile) / sizeof(menuListFile[0]));
	if (selection == 1)
	{
		/*�����ͳͳ��ʼ����*/
		save();
		char lpFileName[MAX_PATH];/*������Դhttps://zhidao.baidu.com/question/518459589225069325.html*/
		GetModuleFileName(NULL, lpFileName, MAX_PATH);
		// �����µ�����
		SHELLEXECUTEINFO ShExecInfo;
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
		ShExecInfo.fMask = NULL;
		ShExecInfo.hwnd = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = lpFileName; // ִ�еĳ�����
		ShExecInfo.lpParameters = NULL;
		ShExecInfo.lpDirectory = NULL;
		ShExecInfo.nShow = SW_NORMAL;
		ShExecInfo.hInstApp = NULL;
		ShellExecuteEx(&ShExecInfo);
		//�ر�����
		exit(0);
	}
	else if (selection == 2)
	{
		open();
		display();
	}
	else if (selection == 3)
	{
		isSaveAs = FALSE;
		save();
		display();
	}
	else if (selection == 4)
	{
		isSaveAs = TRUE;
		save();
		display();
	}
	else if (selection == 5)
	{
		if (MessageBox(NULL, lang ? "Need save the file?" : "��Ҫ���浱ǰ�ļ���", 
			lang ? "Attention" : "ע��", MB_YESNO | MB_ICONQUESTION) == IDYES)/*������ϵͳapi������һ���Ի���*/
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

	/*Edit�˵�*/
	selection = menuList(GenUIID(0), 1 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListEdit[7]) * 1.5, menuHeight, lang ? menuListEdit : menuListCEdit, sizeof(menuListEdit) / sizeof(menuListEdit[0]));
	if (selection == 1)
	{
		cut();
		display();
	}
	else if (selection == 2)
	{
		copy();
		display();
	}
	else if (selection == 3)
	{
		paste();
		display();
	}
	else if (selection == 4)
	{
		del();
		display();
	}
	else if (selection == 5)
	{
		enlargeGraphicSize();
		display();/*�������ʱˢ��Edit�˵����ͻ���ʧ*/
	}
	else if (selection == 6)
	{
		reduceGraphicSize();
		display();
	}
	else if (selection == 7)
	{
		fill();
		display();
	}

	/*Draw�˵�*/
	selection = menuList(GenUIID(0), 2 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListDraw[6]) * 1.5, menuHeight, lang ? menuListDraw : menuListCDraw, sizeof(menuListDraw) / sizeof(menuListDraw[0]));
	if (selection)
	{
		operation = draw;
		type = selection;
	}

	/*Fill Colors�˵�*/
	selection = menuList(GenUIID(0), 3 * defaultMenuWidth, winHeight - menuHeight, 1.5 * defaultMenuWidth, TextStringWidth(menuListFillColors[1]) * 2, menuHeight, lang ? menuListFillColors : menuListCFillColors, sizeof(menuListFillColors) / sizeof(menuListFillColors[0]));
	if (selection)
	{
	//if (operation == selected)/*��Ҫ�����*/
	//{
	changeFillColor(selection - 1);
	display();
	//}
	}

	/*Font Colors�˵�*/
	selection = menuList(GenUIID(0), 4.5 * defaultMenuWidth, winHeight - menuHeight, 1.5 * defaultMenuWidth, TextStringWidth(menuListFillColors[1]) * 2, menuHeight,lang ?  menuListFontColors : menuListCFontColors, sizeof(menuListFontColors) / sizeof(menuListFontColors[0]));
	if (selection)
	{
		//if (operation == selected)
		//{
		changeTextColor(selection - 1);
		display();
		//}
	}

	/*Pen Size�˵�*/
	selection = menuList(GenUIID(0), 6 * defaultMenuWidth, winHeight - menuHeight, 1.5 * defaultMenuWidth, TextStringWidth(menuListFillColors[1]) * 2, menuHeight, lang ? menuListPenSize : menuListCPenSize, sizeof(menuListPenSize) / sizeof(menuListPenSize[0]));
	if (selection)
	{
		changePenSize(selection);
		display();
	}

	/*Help�˵�*/
	selection = menuList(GenUIID(0), 7.5 * defaultMenuWidth, winHeight - menuHeight, defaultMenuWidth, TextStringWidth(menuListHelp[3]) * 2, menuHeight, lang ? menuListHelp : menuListCHelp, sizeof(menuListHelp) / sizeof(menuListHelp[0]));
	if (selection == 1)
	{
		/*"About us"�Ĺ���*/
	}
	else if (selection == 2)
	{
		ShellExecute(NULL, "open", "https://github.com/a-low-profile-team-of-zju/demo", NULL, NULL, SW_HIDE);/*�������ǵ�GitHub��Ŀҳ*/
	}
	else if (selection == 3)
	{
		if (lang == English)
			lang = Chinese;
		else
			lang = English;
	}
}

/*��ʼ��buttomBar��������ʾ��ǰ״̬�������ı���*/
void initButtomBar(void)
{
	char status[10];
	double fontHeight = GetFontHeight();/*��ȡ�ı��߶�*/
	double barHeight = 1.5 * fontHeight;
	double statusWidth = 3;

	switch (operation)
	{
	case none:
		strcpy(status, lang ? "None" : "�޲���");
		break;
	case draw:
		strcpy(status, lang ? "Drawing" : "��ͼ��");
		break;
	case selected:
		if (moveFlag)
			strcpy(status, lang ? "Moving" : "�ƶ���");
		else
			strcpy(status, lang ? "Selecting" : "ѡ��");
		break;
	}
	/*��һ��menuBar��Ϊ����*/
	drawMenuBar(0,0,winWidth,barHeight);

	SetPenColor("White");
	/*��ʾ��ǰ����״̬*/
	drawLabel((statusWidth - TextStringWidth(status)) / 2, (barHeight-fontHeight)/2, status);
	
	setTextBoxColors("Gray", "Black", "Gray", "Black", 1);
	if (textbox(GenUIID(0), statusWidth, 0, winWidth-3, barHeight, tmpText, 101)) 
	{
		if (selectedGraph != NULL)
		{
			switch (type)
			{
			case ����:
				strcpy(((rectangleNode)selectedGraph)->data.text, tmpText);
				break;
			case Բ�Ǿ���:
				strcpy(((rRectangleNode)selectedGraph)->data.text, tmpText);
				break;
			case ����:
				strcpy(((diamNode)selectedGraph)->data.text, tmpText);
				break;
			case ֱ��:
				break;
			case �����ͷ:
				break;
			case ˫���ͷ:
				break;
			case ƽ���ı���:
				strcpy(((paraNode)selectedGraph)->data.text, tmpText);
				break;
			case Բ��:
				strcpy(((circleNode)selectedGraph)->data.text, tmpText);
				break;
			case ��Բ��:
				strcpy(((ovalNode)selectedGraph)->data.text, tmpText);
				break;
			}
		}
	}
}
