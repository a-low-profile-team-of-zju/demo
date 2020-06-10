#ifndef __operation_h__
#define __operation_h__

#define scaleUnit 0.1/*每次缩放的最小单位，单位为英寸*/

void* selectedGraph;/*用来表示被选中的图形的节点*/
void* copyGraph;/*用来表示被复制或被剪切的图形的节点*/

//static FILE* openedFile;/*记录当前打开的文件*/
static char savedFile[MAX_PATH];/*记录上一个保存过的文件*/
bool isSaveAs;/*用来判断是否选择另存为*/

/*用来根据当前鼠标位置选择图形，返回值为1时表示选中，反之则无
注意，这个遍历方法会使得选中图形时具有优先级，矩形优先级最大，椭圆最小*/
int selectGraph(double x, double y);
/*移动图形*/
void moveGraph(double dx,double dy);
/*改变线条及填充颜色*/
void changeFillColor(int choose);
/*改变文本颜色*/
void changeTextColor(int choose);
/*按比例改变图形大小，此为放大*/
void enlargeGraphicSize(void);
/*按比例改变图形大小，此为缩小*/
void reduceGraphicSize(void);
/*改变画笔的粗细*/
void changePenSize(int choose);
/*改变图形的填充状态*/
void fill(void);
/*复制*/
void copy(void);
/*粘贴*/
void paste(void);
/*删除*/
void del(void);
/*剪切*/
void cut(void);

/*打开文件*/
void open(void);
/*保存文件*/
void save(void);

#endif 
