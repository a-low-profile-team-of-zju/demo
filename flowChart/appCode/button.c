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

/*�����жϵ�ǰ�ǻ��ƽ��滹�Ǳ༭����*/
enum
 {
	draw, edit
 } currentButton = draw;/*Ĭ��Ϊ���ƽ���*/

/*���ư�ť*/
void drawButton(void)
{


/*���崰�ڳߴ磨Ӣ�磩*/
double windowWidth, windowHeight;

 /*�����Ϸ���ť�ĳߴ磨Ӣ�磩*/
 double topButtonsWidth = 1.5, topButtonsHeight = 1.2;

 /*�����·���ť�ĳߴ磨Ӣ�磩*/
 double sideButtonsWidth = 3.0, sideButtonsHeight = 1.0;

 /*����menu�ĳߴ�(Ӣ�磩*/
 double menuHeight = 0.4;

 windowWidth = GetWindowWidth();
 windowHeight = GetWindowHeight();

	if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight, topButtonsWidth, topButtonsHeight, "����"))
	{
		currentButton = draw;
	}

	if (button(GenUIID(0), topButtonsWidth, windowHeight - menuHeight - topButtonsHeight, topButtonsWidth, topButtonsHeight, "�༭"))
	{
		currentButton = edit;
	}
	if (currentButton)/*������»��ư�ť����ʾ�����µĸ�����ť������Ǳ༭��ť��Ȼ*/
	{
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 1 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "�ı���ɫ"))
		{
			/*����д�ı���ɫ����*/
		}

		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 2 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "�����߿�"))
		{
			/*����д�����߿���*/
		}

		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 3 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "�����߿�"))
		{
			/*����д�����߿���*/
		}
	}
	else
	{
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 1 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "����"))
		{
			/*��д����*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 2 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "Բ�Ǿ���"))
		{
			/*��д����*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 3 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "����"))
		{
			/*��д����*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 4 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "��ͷ"))
		{
			/*��д����*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 5 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "���߼�ͷ"))
		{
			/*��д����*/
		}
		if (button(GenUIID(0), 0, windowHeight - menuHeight - topButtonsHeight - 6 * sideButtonsHeight, sideButtonsWidth, sideButtonsHeight, "�ı���"))
		{
			/*��д����*/
		}
	}
}