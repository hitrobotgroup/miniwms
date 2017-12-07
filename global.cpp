﻿#include "global.h"
#include <QTime>
#include <QCoreApplication>

const QString DATE_TIME_FORMAT = "yyyy-MM-dd hh:mm:ss";//统一时间格式
QString g_strExeRoot;
Sql *g_sql = NULL;
Configure configure;

/////////////////////////////////////////////////////////
int row;
int column;
QList<int> endPoints;//考虑到平移的问题，用于标记该行是否执行到底，
QList<WidgetGood *> widgetGoods;

//标记下一个取货A的点
int nextTakeColumnA;
int nextTakeRowA;

//标记下一个取货B的点
int nextTakeRowB;
int nextTakeColumnB;
/////////////////////////////////////////////////////////

void QyhSleep(int msec)
{
    QTime dieTime = QTime::currentTime().addMSecs(msec);

    while( QTime::currentTime() < dieTime )
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}

int getRandom(int maxRandom)
{
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    if(maxRandom>0)
        return qrand()%maxRandom;
    return qrand();
}


int getNextAStation()
{
    if(nextTakeRowA*column+nextTakeColumnA > widgetGoods.length())return -1;
    if(widgetGoods.at(nextTakeRowA*column+nextTakeColumnA)->hasGood())
    {
        return  nextTakeRowA*column+nextTakeColumnA;
    }
    return -1;
}

int getNextBStation()
{
    if(nextTakeRowB*column+nextTakeColumnB > widgetGoods.length())return -1;
    if(widgetGoods.at(nextTakeRowB*column+nextTakeColumnB)->hasGood())
    {
        return  nextTakeRowB*column+nextTakeColumnB;
    }
    return -1;
}
