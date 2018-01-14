#ifndef THREADDUBLSYMBOL_H
#define THREADDUBLSYMBOL_H

#include <QObject>
#include <Qstring>
#include <QQueue>
#include <QMutex>
#include <QTextStream>
#include <QTimer>



class ThreadDublSymbol : public QObject
{
    Q_OBJECT
    QQueue<QString> *arr;
    QMutex *m_arr;
    QMutex *m_out;
    int *flagEnd;
    int max_leng;
    QTimer *timer;
    int SleepTime1;
public:
    explicit ThreadDublSymbol(QObject *parent = nullptr);
signals:
    void finished();
public slots:
    void process();
    void runTimer();
    void SetParam(QQueue<QString> &arr2, QMutex &m_arr2, QMutex &m_out2, int &flagEnd2, int max_leng2, int SleepTimeThread1);

};

#endif // THREADDUBLSYMBOL_H


