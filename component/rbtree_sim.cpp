#include "rbtree_sim.h"
#include "animation/rbtree_model.h"
#include "datasource/rbdata.h"

Rbtree::Rbtree():Simulator(std::make_shared<RbtreeModel>(),std::make_shared<RbData>())
{

}

Rbtree::~Rbtree()
{

}

void Rbtree::convertInput(const std::vector<int> &v)
{
    Input a={RbData::Insert,100};
    for(int i=0;i<a.dataLength;i++)
        a.data[i]=i;
    dataSource->prepare();
    dataSource->setInput({a});
    animation->pullInform({a});
}

void Rbtree::prepareReplay()
{
    animation->initModelData();
}

