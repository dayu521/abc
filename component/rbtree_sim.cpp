#include "rbtree_sim.h"
#include "animation/rbtree_model.h"
#include "datasource/rbdata.h"

Rbtree::Rbtree():Simulator(std::make_shared<RbtreeModel>(),std::make_shared<RbData>())
{

}

Rbtree::~Rbtree()
{

}

void Rbtree::setInputData(const std::vector<int> &v)
{
//    dataSource->setInput(v);
    dataSource->setInput({{1}});
}

void Rbtree::clearModelData()
{
    animation->clearAllModelDatas();
    st=Simulator::Status::Empty;
}

void Rbtree::prepareReplay()
{
    animation->initModelData();
}

