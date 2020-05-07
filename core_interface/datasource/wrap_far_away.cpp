
#include "wrap_far_away.h"

WrapFarAway::WrapFarAway()
{

}

void WrapFarAway::doWork()
{
    {
        QMutexLocker L(&mutex);
        stMutex.lock();
        st=Status::Running;
        stMutex.unlock();
        try {
            for(const auto & f :input)
                ms.find(f.method)->second();
        }  catch (const std::out_of_range &) {
            throw  std::runtime_error("can not execute this method.no such method");
        }
    }
//    QCoreApplication::postEvent(nullptr,nullptr);
    stMutex.lock();
    st=Status::GodJob;
    stMutex.unlock();
}

bool WrapFarAway::setInput(const std::vector<Input> & p)
{
    if(mutex.tryLock()){
        input=p;
        mutex.unlock();
        stMutex.lock();
        st=Status::Ready;
        stMutex.unlock();
        return true;
    }
    return false;
}

std::vector<Instruction> &WrapFarAway::getOutput()
{
    QMutexLocker L(&mutex);
    return oupt;
}

