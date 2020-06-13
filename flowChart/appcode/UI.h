#ifndef __UI_h__
#define __UI_h__

static int choose;/*判断颜色改变的对象，默认判断颜色改变的对象为填充颜色*/

double winWidth, winHeight;
/*textBox的文本缓存*/
char tmpText[101];
/*判断中英文，默认英文*/
enum language
{
	Chinese = 0,
	English
}lang;

/*初始化menu*/
void initMenu(void);
/*初始化buttomBar，用来显示当前状态和输入文本框*/
void initButtomBar(void);
/*初始化button*/
void initButton(void);

#endif 
