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
#include "menu.h"

/*�û�����ʾ����*/
void display(void);

/*�û����ַ��¼���Ӧ����*/
void CharEventProcess(char ch);
/*�û��ļ����¼���Ӧ����*/
void KeyboardEventProcess(int key, int event);
/*�û�������¼���Ӧ����*/
void MouseEventProcess(int x, int y, int button, int event);

void Main()
{
	/* ��ʼ�����ں�ͼ��ϵͳ*/
	SetWindowTitle("FlowChart");
	SetWindowSize(15, 10);
	InitGraphics();
	InitGUI();

	/* ע��ʱ����Ӧ����*/
	registerCharEvent(CharEventProcess);        /*�ַ�*/
	registerKeyboardEvent(KeyboardEventProcess);/* ����*/
	registerMouseEvent(MouseEventProcess);      /* ���*/
	usePredefinedButtonColors(4);
	usePredefinedMenuColors(4);
}

/*�û�����ʾ����*/
void display(void)
{
	DisplayClear();/*����*/
	
	drawButton();
	drawMenu();
}

/*�û����ַ��¼���Ӧ����*/
void CharEventProcess(char ch)
{
	uiGetChar(ch); /* GUI�ַ�����*/
	display(); /*ˢ����ʾ*/
}

/*�û��ļ����¼���Ӧ����*/
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); /* GUI��ȡ����*/
	display(); /* ˢ����ʾ*/
}

/*�û�������¼���Ӧ����*/
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); /*GUI��ȡ���*/
	display(); /* ˢ����ʾ*/
}