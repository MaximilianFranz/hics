#include "WorkerThread.h"

void WorkerThread::run() {
    ClassificationResult *result = nullptr;
    if(mWH) {
        result = mWH->notify();
        emit resultReady(result);
    }
}

WorkerThread::WorkerThread(MainWindowHandler *mWH) : mWH(mWH) {};