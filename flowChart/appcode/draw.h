#ifndef __draw_h__
#define __draw_h__

#define defaultFillFlag FALSE/*默认不填充*/
#define defaultPenSize 3/*默认画笔粗细为3*/
#define defaultFillColor "BLACK"/*默认边线及填充颜色为黑色*/
#define defaultTextColor "Black"/*默认文本颜色为黑色*/
#define defaultText "text here"/*默认图形内文本框内容*/

/*用来判断图形类型*/
enum type
{
	矩形 = 1,
	圆角矩形,
	菱形,
	直线,
	单向箭头,
	双向箭头,
	平行四边形,
	圆形,
	椭圆形,
} type;

/*用来判断当前操作*/
enum operation
{
	none = 0,
	draw,
	selected,
} operation;

static bool moveFlag;/*判断选中是否是为了移动，还是单纯的选中来改变属性*/

/*--------------------------------------------------------------------------------------矩形绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建矩形参数的结构体*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	char textColor[15];/*文本颜色*/
	char text[101];/*文本内容，最大100字符*/
	int penSize;
} rectangle;

typedef struct /*创建矩形链表*/
{
	rectangle data;
	struct recNode* pNext;
}recNode;

typedef recNode* rectangleNode;
rectangleNode rectangleHead;/*矩形链表的头结点*/

/*初始化一个矩形链表节点并插入链表头部*/
void initRec(double x,double y);
/*绘制矩形带文本*/
void drawRec(rectangleNode recHead);

/*--------------------------------------------------------------------------------------圆角矩形绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建圆角矩形参数的结构体*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	char textColor[15];/*文本颜色*/
	char text[101];/*文本内容，最大100字符*/
	int penSize;
} roundedRectangle;
typedef struct /*创建圆角矩形链表*/
{
	roundedRectangle data;
	struct recNode* pNext;
}roundedRecNode;
typedef roundedRecNode* rRectangleNode;
rRectangleNode rRectangleHead;/*圆角矩形链表的头结点*/

/*初始化一个圆角矩形链表节点并插入链表头部*/
void initRoundedRec(double x, double y);
/*绘制圆角矩形带文本*/
void drawRoundedRec(rRectangleNode roundedRecHead);

/*这个display声明放在这个头文件里是为了给他源文件引用*/
void display(void);
void displayUI(void);

/*--------------------------------------------------------------------------------------菱形绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建菱形参数的结构体*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	char textColor[15];/*文本颜色*/
	char text[101];/*文本内容，最大100字符*/
	int penSize;
} diamond;
typedef struct /*创建菱形链表*/
{
	diamond data;
	struct recNode* pNext;
} diamondNode;
typedef diamondNode* diamNode;
diamNode diamondHead;/*菱形链表的头结点*/

/*初始化一个菱形链表节点并插入链表头部*/
void initDiam(double x, double y);
/*绘制菱形带文本*/
void drawDiam(diamNode diamondHead);

/*--------------------------------------------------------------------------------------直线绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建直线参数的结构体*/
{
	double startX, startY;
	double endX, endY;
	//bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	//char textColor[15];/*文本颜色*/
	//char text[101];/*文本内容，最大100字符*/
	int penSize;
} line;

typedef struct /*创建直线链表*/
{
	line data;
	struct lNode* pNext;
}lNode;

typedef lNode* lineNode;
lineNode lineHead;/*直线链表的头结点*/

/*初始化一个直线链表节点并插入链表头部*/
void initLine(double x, double y);
/*绘制直线*/
void drawLine(lineNode lineHead);

/*--------------------------------------------------------------------------------------单向箭头绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建单向箭头参数的结构体*/
{
	double startX, startY;
	double endX, endY;
	//bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	//char textColor[15];/*文本颜色*/
	//char text[101];/*文本内容，最大100字符*/
	int penSize;
} arrow;

typedef struct /*创建单向箭头链表*/
{
	arrow data;
	struct aNode* pNext;
}aNode;

typedef aNode* arrowNode;
arrowNode arrowHead;/*单向箭头链表的头结点*/

/*初始化一个单向箭头链表节点并插入链表头部*/
void initArrow(double x, double y);
/*绘制单向箭头*/
void drawArrow(arrowNode arrowHead);

/*--------------------------------------------------------------------------------------双向箭头绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建双向箭头参数的结构体*/
{
	double startX, startY;
	double endX, endY;
	//bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	//char textColor[15];/*文本颜色*/
	//char text[101];/*文本内容，最大100字符*/
	int penSize;
} doubleArrow;

typedef struct /*创建双向箭头链表*/
{
	doubleArrow data;
	struct daNode* pNext;
}daNode;

typedef daNode* dArrowNode;
dArrowNode dArrowHead;/*双向箭头链表的头结点*/

/*初始化一个双向箭头链表节点并插入链表头部*/
void initdArrow(double x, double y);
/*绘制双向箭头*/
void drawdArrow(dArrowNode dArrowHead);

/*--------------------------------------------------------------------------------------平行四边形绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建平行四边形参数的结构体*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	char textColor[15];/*文本颜色*/
	char text[101];/*文本内容，最大100字符*/
	int penSize;
} parallelogram;

typedef struct /*创建平行四边形链表*/
{
	parallelogram data;
	struct pNode* pNext;
}pNode;

typedef pNode* paraNode;
paraNode paraHead;/*平行四边形链表的头结点*/

/*初始化一个平行四边形链表节点并插入链表头部*/
void initPara(double x, double y);
/*绘制平行四边形带文本*/
void drawPara(paraNode paraHead);

/*--------------------------------------------------------------------------------------圆形绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建圆形参数的结构体*/
{
	double startX, startY;
	double radius;
	bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	char textColor[15];/*文本颜色*/
	char text[101];/*文本内容，最大100字符*/
	int penSize;
} circle;

typedef struct /*创建圆形链表*/
{
	circle data;
	struct cNode* pNext;
}cNode;

typedef cNode* circleNode;
circleNode circleHead;/*圆形链表的头结点*/

/*初始化一个圆形链表节点并插入链表头部*/
void initCircle(double x, double y);
/*绘制圆形带文本*/
void drawCircle(circleNode circleHead);

/*--------------------------------------------------------------------------------------椭圆形绘制部分--------------------------------------------------------------------------------------*/
typedef struct /*创建椭圆形参数的结构体*/
{
	double startX, startY;
	double xRadius,yRadius;
	bool fillFlag;/*是否填充*/
	char fillColor[15];/*填充以及边线颜色*/
	char textColor[15];/*文本颜色*/
	char text[101];/*文本内容，最大100字符*/
	int penSize;
} oval;

typedef struct /*创建椭圆形链表*/
{
	oval data;
	struct oNode* pNext;
}oNode;

typedef oNode* ovalNode;
ovalNode ovalHead;/*椭圆形链表的头结点*/

/*初始化一个椭圆形链表节点并插入链表头部*/
void initOval(double x, double y);
/*绘制椭圆形带文本*/
void drawOval(ovalNode ovalHead);

#endif