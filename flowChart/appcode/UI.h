#ifndef __UI_h__
#define __UI_h__

double winWidth, winHeight;
/*textBox���ı�����*/
char tmpText[101];
/*�ж���Ӣ�ģ�Ĭ������*/
enum language
{
	Chinese = 0,
	English
}lang;

/*��ʼ��menu*/
void initMenu(void);
/*��ʼ��buttomBar��������ʾ��ǰ״̬�������ı���*/
void initButtomBar(void);

#endif 
