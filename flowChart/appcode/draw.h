#ifndef __draw_h__
#define __draw_h__

#define defaultFillFlag FALSE/*Ĭ�ϲ����*/
#define defaultPenSize 3/*Ĭ�ϻ��ʴ�ϸΪ3*/
#define defaultFillColor "BLACK"/*Ĭ�ϱ��߼������ɫΪ��ɫ*/
#define defaultTextColor "Black"/*Ĭ���ı���ɫΪ��ɫ*/
#define defaultText "text here"/*Ĭ��ͼ�����ı�������*/

/*�����ж�ͼ������*/
enum type
{
	���� = 1,
	Բ�Ǿ���,
	����,
	ֱ��,
	�����ͷ,
	˫���ͷ,
	ƽ���ı���,
	Բ��,
	��Բ��,
} type;

/*�����жϵ�ǰ����*/
enum operation
{
	none = 0,
	draw,
	selected,
} operation;

static bool moveFlag;/*�ж�ѡ���Ƿ���Ϊ���ƶ������ǵ�����ѡ�����ı�����*/

/*--------------------------------------------------------------------------------------���λ��Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*�������β����Ľṹ��*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	char textColor[15];/*�ı���ɫ*/
	char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} rectangle;

typedef struct /*������������*/
{
	rectangle data;
	struct recNode* pNext;
}recNode;

typedef recNode* rectangleNode;
rectangleNode rectangleHead;/*���������ͷ���*/

/*��ʼ��һ����������ڵ㲢��������ͷ��*/
void initRec(double x,double y);
/*���ƾ��δ��ı�*/
void drawRec(rectangleNode recHead);

/*--------------------------------------------------------------------------------------Բ�Ǿ��λ��Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*����Բ�Ǿ��β����Ľṹ��*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	char textColor[15];/*�ı���ɫ*/
	char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} roundedRectangle;
typedef struct /*����Բ�Ǿ�������*/
{
	roundedRectangle data;
	struct recNode* pNext;
}roundedRecNode;
typedef roundedRecNode* rRectangleNode;
rRectangleNode rRectangleHead;/*Բ�Ǿ��������ͷ���*/

/*��ʼ��һ��Բ�Ǿ�������ڵ㲢��������ͷ��*/
void initRoundedRec(double x, double y);
/*����Բ�Ǿ��δ��ı�*/
void drawRoundedRec(rRectangleNode roundedRecHead);

/*���display�����������ͷ�ļ�����Ϊ�˸���Դ�ļ�����*/
void display(void);
void displayUI(void);

/*--------------------------------------------------------------------------------------���λ��Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*�������β����Ľṹ��*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	char textColor[15];/*�ı���ɫ*/
	char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} diamond;
typedef struct /*������������*/
{
	diamond data;
	struct recNode* pNext;
} diamondNode;
typedef diamondNode* diamNode;
diamNode diamondHead;/*���������ͷ���*/

/*��ʼ��һ����������ڵ㲢��������ͷ��*/
void initDiam(double x, double y);
/*�������δ��ı�*/
void drawDiam(diamNode diamondHead);

/*--------------------------------------------------------------------------------------ֱ�߻��Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*����ֱ�߲����Ľṹ��*/
{
	double startX, startY;
	double endX, endY;
	//bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	//char textColor[15];/*�ı���ɫ*/
	//char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} line;

typedef struct /*����ֱ������*/
{
	line data;
	struct lNode* pNext;
}lNode;

typedef lNode* lineNode;
lineNode lineHead;/*ֱ�������ͷ���*/

/*��ʼ��һ��ֱ������ڵ㲢��������ͷ��*/
void initLine(double x, double y);
/*����ֱ��*/
void drawLine(lineNode lineHead);

/*--------------------------------------------------------------------------------------�����ͷ���Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*���������ͷ�����Ľṹ��*/
{
	double startX, startY;
	double endX, endY;
	//bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	//char textColor[15];/*�ı���ɫ*/
	//char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} arrow;

typedef struct /*���������ͷ����*/
{
	arrow data;
	struct aNode* pNext;
}aNode;

typedef aNode* arrowNode;
arrowNode arrowHead;/*�����ͷ�����ͷ���*/

/*��ʼ��һ�������ͷ����ڵ㲢��������ͷ��*/
void initArrow(double x, double y);
/*���Ƶ����ͷ*/
void drawArrow(arrowNode arrowHead);

/*--------------------------------------------------------------------------------------˫���ͷ���Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*����˫���ͷ�����Ľṹ��*/
{
	double startX, startY;
	double endX, endY;
	//bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	//char textColor[15];/*�ı���ɫ*/
	//char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} doubleArrow;

typedef struct /*����˫���ͷ����*/
{
	doubleArrow data;
	struct daNode* pNext;
}daNode;

typedef daNode* dArrowNode;
dArrowNode dArrowHead;/*˫���ͷ�����ͷ���*/

/*��ʼ��һ��˫���ͷ����ڵ㲢��������ͷ��*/
void initdArrow(double x, double y);
/*����˫���ͷ*/
void drawdArrow(dArrowNode dArrowHead);

/*--------------------------------------------------------------------------------------ƽ���ı��λ��Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*����ƽ���ı��β����Ľṹ��*/
{
	double startX, startY;
	double endX, endY;
	bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	char textColor[15];/*�ı���ɫ*/
	char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} parallelogram;

typedef struct /*����ƽ���ı�������*/
{
	parallelogram data;
	struct pNode* pNext;
}pNode;

typedef pNode* paraNode;
paraNode paraHead;/*ƽ���ı��������ͷ���*/

/*��ʼ��һ��ƽ���ı�������ڵ㲢��������ͷ��*/
void initPara(double x, double y);
/*����ƽ���ı��δ��ı�*/
void drawPara(paraNode paraHead);

/*--------------------------------------------------------------------------------------Բ�λ��Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*����Բ�β����Ľṹ��*/
{
	double startX, startY;
	double radius;
	bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	char textColor[15];/*�ı���ɫ*/
	char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} circle;

typedef struct /*����Բ������*/
{
	circle data;
	struct cNode* pNext;
}cNode;

typedef cNode* circleNode;
circleNode circleHead;/*Բ�������ͷ���*/

/*��ʼ��һ��Բ������ڵ㲢��������ͷ��*/
void initCircle(double x, double y);
/*����Բ�δ��ı�*/
void drawCircle(circleNode circleHead);

/*--------------------------------------------------------------------------------------��Բ�λ��Ʋ���--------------------------------------------------------------------------------------*/
typedef struct /*������Բ�β����Ľṹ��*/
{
	double startX, startY;
	double xRadius,yRadius;
	bool fillFlag;/*�Ƿ����*/
	char fillColor[15];/*����Լ�������ɫ*/
	char textColor[15];/*�ı���ɫ*/
	char text[101];/*�ı����ݣ����100�ַ�*/
	int penSize;
} oval;

typedef struct /*������Բ������*/
{
	oval data;
	struct oNode* pNext;
}oNode;

typedef oNode* ovalNode;
ovalNode ovalHead;/*��Բ�������ͷ���*/

/*��ʼ��һ����Բ������ڵ㲢��������ͷ��*/
void initOval(double x, double y);
/*������Բ�δ��ı�*/
void drawOval(ovalNode ovalHead);

#endif