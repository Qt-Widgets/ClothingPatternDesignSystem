#ifndef MYPATHDATA_H
#define MYPATHDATA_H

#include <QPointF>
#include <QString>
#include <QTextStream>
#include <QList>
#include <QMap>
#include "curvepoint.h"

class QPainterPath;
class QFile;
class QPainterPath;
class PainterArea;

struct PathData{
    int id; /**< 路径在数组中的序号 */
    bool isLine; /**< 是否为直线 */
    CurvePoint* startPoint; /**< 起点指针 */
    CurvePoint* endPoint; /**< 终点指针 */
    QPainterPath *path; /**< 原始路径数据 */
};

class MyPathData
{
public:
    MyPathData(QString name,PainterArea* parent);
    ~MyPathData();

    PainterArea* parent=nullptr;
    QString name=""; /**< MyPathData实例的名称 */
    const static int MAX_NUM_POINT=250; /**< 点的数目上限 */
    const static int MAX_NUM_PATH=120; /**< 路径数目上限 */
    int numberPath=0; /**< 路径数目 */
    int numberPoint=0; /**< 点的数目 */
    PathData pathData[MAX_NUM_PATH]; /**< 路径数组 */
    QPointF pointData[MAX_NUM_POINT]; /**< 点的数组 */
    QMap<QString,int> pointMap; /**< 记录点的名称 */

    bool addLineTo(QPointF endPoint,int idStartPoint=-1);
    void addLine(QPointF startPoint,QPointF endPoint);
    void addCurve(QList<QPointF> points,QPointF ctrlPoint1,QPointF ctrlPoint2,QPainterPath path);
    int addPoint(QPointF point,QString name=""); //将point加入pointData数组（若已存在就不会添加），返回在数组中的索引
    int addCtrlPoint(QPointF ctrlPoint); //将ctrlPoint加入pointData数组（不管是否已存在同位置的点），返回在数组中的索引
    int findPoint(QPointF point,bool addIfNotFind=false); //在pointData数组中寻找point，返回它的索引。
    bool pointMapHas(QPointF point);
    QPointF findPoint(QString name);
    QString findName(int id);
    QString stringOf(CurvePoint *point);
    QString stringsOf(CurvePoint *point);

    bool saveTo(QString path);
    bool writeASTM(QString filePath);
    void clear();

private:
    const qreal E=0.1;
    int idCurrentPoint=0; //记录当前点在pointData数组中的索引
    int findPathBySP(int idSP);
    bool equal(QPointF p1,QPointF p2); //判断两点是否相等（对应坐标相差不超过常量(E)mm）
    void writeText(QFile* file,QString str,qreal x=0,qreal y=0,int layer=1);
    void writePolyL(QFile* file,PathData path,int layer=1);
    void writePolyL(QFile* file,const QPainterPath& path,int layer);
    void writePolyLHead(QFile* file,int layer=1);
    void writeBoundary(QFile* file);
    void writeNotches(QFile* file);
    void writeInLines(QFile* file);
    QString stringReal(qreal n);
    QString stringPoint(QPointF p);
    QString stringPoint(qreal x,qreal y);
};

#endif // MYPATHDATA_H
