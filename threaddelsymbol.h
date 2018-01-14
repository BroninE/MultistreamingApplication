#ifndef THREADDELSYMBOL_H
#define THREADDELSYMBOL_H

#include <QObject>
#include <QThread>
#include <Qstring>
#include <QQueue>
#include <QMutex>
#include <QTextStream>
#include <QTimer>
#include <QCoreApplication>



class ThreadDelSymbol : public QObject
{
    Q_OBJECT
    QQueue<QString> *arr;
    QMutex *m_arr;
    QMutex *m_out;
    int *flagEnd;
    int max_leng;
    QTimer *timer;
    int SleepTime2;
    QEventLoop loop;
public:
    explicit ThreadDelSymbol(QObject *parent = nullptr);
signals:
    void finished();
public slots:
    void process();
    void runTimer();
    void SetParam(QQueue<QString> &arr2, QMutex &m_arr2, QMutex &m_out2, int &flagEnd2, int max_leng2, int SleepTimeThread2);

};



#endif // THREADDELSYMBOL_H
