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

/*用户的显示函数*/
void display(void);

/*用户的字符事件响应函数*/
void CharEventProcess(char ch);
/*用户的键盘事件响应函数*/
void KeyboardEventProcess(int key, int event);
/*用户的鼠标事件响应函数*/
void MouseEventProcess(int x, int y, int button, int event);

void Main()
{
	/* 初始化窗口和图形系统*/
	SetWindowTitle("FlowChart");
	SetWindowSize(15, 10);
	InitGraphics();
	InitGUI();

	/* 注册时间响应函数*/
	registerCharEvent(CharEventProcess);        /*字符*/
	registerKeyboardEvent(KeyboardEventProcess);/* 键盘*/
	registerMouseEvent(MouseEventProcess);      /* 鼠标*/
	usePredefinedButtonColors(4);
	usePredefinedMenuColors(4);
}

/*用户的显示函数*/
void display(void)
{
	DisplayClear();/*清屏*/
	
	drawButton();
	drawMenu();
}

/*用户的字符事件响应函数*/
void CharEventProcess(char ch)
{
	uiGetChar(ch); /* GUI字符输入*/
	display(); /*刷新显示*/
}

/*用户的键盘事件响应函数*/
void KeyboardEventProcess(int key, int event)
{
	uiGetKeyboard(key, event); /* GUI获取键盘*/
	display(); /* 刷新显示*/
}

/*用户的鼠标事件响应函数*/
void MouseEventProcess(int x, int y, int button, int event)
{
	uiGetMouse(x, y, button, event); /*GUI获取鼠标*/
	display(); /* 刷新显示*/
}