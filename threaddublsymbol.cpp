#include "threaddublsymbol.h"

ThreadDublSymbol::ThreadDublSymbol(QObject *parent) : QObject(parent)
{

}

void ThreadDublSymbol::runTimer(){;
    timer = new QTimer;
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(process()));
    timer->start(SleepTime1);

};


void ThreadDublSymbol::process(){
    QTextStream cout(stdout);
    try {
        if ((!arr->empty())or(*flagEnd == 1)){
            if ((*flagEnd == 0)or(!arr->empty())) {
                QMutexLocker lockerArr(m_arr);
                QString str = arr->front();
                arr->pop_front();
                QString str3;
                for (int i=0;i<max_leng;i++){
                    str3.append(str[i]);
                    str3.append(str[i]);
                }
                QMutexLocker lockerOut(m_out);
                cout << "This is 1 stream: "<< str3 << endl;
            }
            else{

               timer->stop();
               emit finished();
               cout << "End work stream 1" << endl;
               return;
            }

         }

        }
    catch (...) {
           timer->stop();
           emit finished();
           cout << "Error 1 stream" << endl;
        }
};

void ThreadDublSymbol::SetParam(QQueue<QString> &arr2, QMutex &m_arr2, QMutex &m_out2, int &flagEnd2, int max_leng2, int SleepTimeThread1){

    arr = &arr2;
    m_arr = &m_arr2;
    m_out = &m_out2;
    flagEnd = &flagEnd2;
    max_leng = max_leng2;
    SleepTime1 = SleepTimeThread1*1000;

};
