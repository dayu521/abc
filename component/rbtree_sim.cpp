#include "rbtree_sim.h"
#include "animation/rbtree_model.h"
#include "datasource/rbdata.h"
#include<iostream>

Rbtree::Rbtree():Simulator(std::make_shared<RbtreeModel>(),std::make_shared<RbData>())
{
    fb=new FreeBoy();
    fb->switchD(dataSource);
    thread=new QThread(this);
    fb->moveToThread(thread);
    connect(this,&Rbtree::start,fb,&FreeBoy::run);
    connect(thread,&QThread::finished,fb,&QObject::deleteLater);
    connect(fb,&FreeBoy::completed,this,[](){
        std::cout<<"fuck you "<<std::endl;
    });
    thread->start();
}

Rbtree::~Rbtree()
{
    thread->exit();
    thread->wait();
}

void Rbtree::setInputData(const std::vector<int> &v)
{
//    dataSource->setInput(v);
}

void Rbtree::produceModelData()
{
    dataSource->setInput({{static_cast<int>(RbData::MethodA::AddMuch)}});
    emit start();
}

void Rbtree::clearModelData()
{

}

void Rbtree::prepareReplay()
{
    animation->initModelData();
}

