#include "threaddelsymbol.h"

ThreadDelSymbol::ThreadDelSymbol(QObject *parent) : QObject(parent)
{

}

void ThreadDelSymbol::runTimer(){
    timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    timer->start(SleepTime2);
};


void ThreadDelSymbol::process(){
    QTextStream cout(stdout);
    try {
        if ((!arr->empty())or(*flagEnd == 1)){
            if ((*flagEnd == 0)or(!arr->empty())) {
                QMutexLocker lockerArr(m_arr);
                QString str = arr->front();
                arr->pop_front();
                str.remove(0,1);
                QMutexLocker lockerOut(m_out);
                cout << "This is 2 stream: " << str << endl;
            }
            else{
               timer->stop();
               emit finished();
               cout << "End work stream 2" << endl;
               return;
            }

         }

        }
    catch (...) {
           timer->stop();
           emit finished();
           cout << "Error 2 stream" << endl;
        }
};

void ThreadDelSymbol::SetParam(QQueue<QString> &arr2, QMutex &m_arr2, QMutex &m_out2, int &flagEnd2, int max_leng2, int SleepTimeThread2){

    arr = &arr2;
    m_arr = &m_arr2;
    m_out = &m_out2;
    flagEnd = &flagEnd2;
    max_leng = max_leng2;
    SleepTime2 = SleepTimeThread2*1000;

};
