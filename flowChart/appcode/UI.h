#ifndef __UI_h__
#define __UI_h__

static int choose;/*�ж���ɫ�ı�Ķ���Ĭ���ж���ɫ�ı�Ķ���Ϊ�����ɫ*/

double winWidth, winHeight;
/*textBox���ı�����*/
char tmpText[101];
/*�ж���Ӣ�ģ�Ĭ��Ӣ��*/
enum language
{
	Chinese = 0,
	English
}lang;

/*��ʼ��menu*/
void initMenu(void);
/*��ʼ��buttomBar��������ʾ��ǰ״̬�������ı���*/
void initButtomBar(void);
/*��ʼ��button*/
void initButton(void);

#endif 
