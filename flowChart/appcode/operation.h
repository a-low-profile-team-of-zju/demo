#ifndef __operation_h__
#define __operation_h__

#define scaleUnit 0.1/*ÿ�����ŵ���С��λ����λΪӢ��*/

void* selectedGraph;/*������ʾ��ѡ�е�ͼ�εĽڵ�*/
void* copyGraph;/*������ʾ�����ƻ򱻼��е�ͼ�εĽڵ�*/

/*�������ݵ�ǰ���λ��ѡ��ͼ�Σ�����ֵΪ1ʱ��ʾѡ�У���֮����
ע�⣬�������������ʹ��ѡ��ͼ��ʱ�������ȼ����������ȼ������Բ��С*/
int selectGraph(double x, double y);
/*�ƶ�ͼ��*/
void moveGraph(double dx,double dy);
/*�ı������������ɫ*/
void changeFillColor(int choose);
/*�ı��ı���ɫ*/
void changeTextColor(int choose);
/*�������ı�ͼ�δ�С����Ϊ�Ŵ�*/
void enlargeGraphicSize(void);
/*�������ı�ͼ�δ�С����Ϊ��С*/
void reduceGraphicSize(void);
/*�ı仭�ʵĴ�ϸ*/
void changePenSize(int choose);
/*�ı�ͼ�ε����״̬*/
void fill(void);
/*����*/
void copy(void);
/*ճ��*/
void paste(void);
/*ɾ��*/
void del(void);
/*����*/
void cut(void);

/*���ļ�*/
void open(void);
/*�����ļ�*/
void save(void);

#endif 
