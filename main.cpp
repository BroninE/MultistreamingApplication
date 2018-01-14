#include <QTextStream>
#include <QFile>
#include <Qstring>
#include <Qqueue>
#include <QThread>
#include <Qmutex>
#include <QTime>
#include <QCoreApplication>
#include <threaddublsymbol.h>
#include <threaddelsymbol.h>

#define SleepTimeMainThread 1 // задержка главного потока в секундах
#define SleepTimeThread1 1 // задержка 1 потока в секундах
#define SleepTimeThread2 2 // задержка 2 потока в секундах
#define max_leng 15 // длина считываемого блока из файла
#define DirFile "E:\\1.txt" // Путь до файла с текстом


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream cout(stdout);
    if(!QFile::exists(DirFile))
        {
            cout << "file not found";
            return 0;
        }
    int flagEndWork = 0; // Флаг того, что вся информация считана
    QFile file(DirFile);
    QQueue<QString> Thread1Queue; // буффер 1 потока
    QQueue<QString> Thread2Queue; // буффер 2 потока
    QMutex m_arr, m_out;

    // Поток для дублирования символов
    QThread* thread1 = new QThread;
    ThreadDublSymbol* threadDublSymbol = new ThreadDublSymbol();
    threadDublSymbol->SetParam(ref(Thread1Queue), ref(m_arr), ref(m_out), ref(flagEndWork),  max_leng, SleepTimeThread1);
    threadDublSymbol->moveToThread(thread1);
    QObject::connect(thread1, SIGNAL(started()), threadDublSymbol, SLOT(runTimer()));
    QObject::connect(threadDublSymbol, SIGNAL(finished()), thread1, SLOT(quit()),Qt::DirectConnection);
    QObject::connect(threadDublSymbol, SIGNAL(finished()), threadDublSymbol, SLOT(deleteLater()),Qt::DirectConnection);
    QObject::connect(thread1, SIGNAL(finished()), thread1, SLOT(deleteLater()));
    thread1->start();

    // Поток для удаления 1 символа
    QThread* thread2 = new QThread;
    ThreadDelSymbol* threadDelSymbol = new ThreadDelSymbol();
    threadDelSymbol->SetParam(ref(Thread2Queue), ref(m_arr), ref(m_out), ref(flagEndWork),  max_leng, SleepTimeThread2);
    threadDelSymbol->moveToThread(thread2);
    QObject::connect(thread2, SIGNAL(started()), threadDelSymbol, SLOT(runTimer()));
    QObject::connect(threadDelSymbol, SIGNAL(finished()), thread2, SLOT(quit()),Qt::DirectConnection);
    QObject::connect(threadDelSymbol, SIGNAL(finished()), threadDelSymbol, SLOT(deleteLater()),Qt::DirectConnection);
    QObject::connect(thread2, SIGNAL(finished()), thread2, SLOT(deleteLater()));
    thread2->start();

    try {
        if (file.open(QIODevice::ReadOnly))
            {
            while(!file.atEnd())
                {
                      QTime stopTime= QTime::currentTime().addSecs(SleepTimeMainThread);
                      while (QTime::currentTime() < stopTime)
                      QCoreApplication::processEvents(QEventLoop::AllEvents);
                      QString block = file.read(max_leng);
                      QMutexLocker lockerArr(&m_arr);
                      Thread1Queue.enqueue(block); //добавление нового блока данных в буффер потока 1
                      Thread2Queue.enqueue(block); //добавление нового блока данных в буффер потока 2
                      QMutexLocker lockerOut(&m_out);
                      cout << "This is main stream: " << block << endl;
                }
            }

    }
    catch(...){
        cout << "Error main stream" << endl;
    }
    flagEndWork = 1; //Главный поток передал все данные на обработку
    file.close();
    thread1->wait();
    thread2->wait();
    cout << "End of work" << endl;
    return 0;
}
