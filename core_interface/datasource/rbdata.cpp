#include "rbdata.h"
#include<QThread>
#include<iostream>

RbData::RbData()
{
    registerMethod(static_cast<int>(MethodA::AddOne),[](){});
    registerMethod(static_cast<int>(MethodA::AddMuch),[](){
        for(int i=0;i<5;i++){
            std::cout<<"睡眠 "<<i+1<<std::endl;
            QThread::sleep(1);
        }
        std::cout<<"睡眠结束"<<std::endl;
    });
}

RbData::~RbData()
{

}
