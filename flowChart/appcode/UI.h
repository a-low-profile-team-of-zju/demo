#ifndef __UI_h__
#define __UI_h__

double winWidth, winHeight;
/*textBox的文本缓存*/
char tmpText[101];
/*判断中英文，默认中文*/
enum language
{
	Chinese = 0,
	English
}lang;

/*初始化menu*/
void initMenu(void);
/*初始化buttomBar，用来显示当前状态和输入文本框*/
void initButtomBar(void);

#endif 
