
#include "wrap_far_away.h"

WrapFarAway::WrapFarAway()
{

}

void WrapFarAway::doWork()
{
    {
        QMutexLocker L(&dataMutex);
        stMutex.lock();
        st=FAStatus::Running;
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
    st=FAStatus::GodJob;
    stMutex.unlock();
}

bool WrapFarAway::setInput(std::vector<Input> p)
{
    if(dataMutex.tryLock()){
        input=std::move(p);
        dataMutex.unlock();
        stMutex.lock();
        st=FAStatus::Ready;
        stMutex.unlock();
        return true;
    }
    return false;
}

std::vector<Instruction> WrapFarAway::getOutput()
{
    QMutexLocker L(&dataMutex);
    return oupt;
}

