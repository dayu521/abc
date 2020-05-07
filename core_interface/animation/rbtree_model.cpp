#include "rbtree_model.h"
#include<tuple>

RbtreeModel::RbtreeModel()
{

}

RbtreeModel::~RbtreeModel()
{

}

void RbtreeModel::nextNFrame(int i)
{

}

void RbtreeModel::previousFrame(int i)
{

}

void RbtreeModel::currentSnapshot() const
{

}

void RbtreeModel::changeElementSize(int factor)
{       
    auto temp=Elements{ele.diameter+factor};
    try {
        if(temp.radius>0&&temp.diameter>0&&temp.fontSize>0&&temp.nodeLineHeight>0)
            ele=temp;
        else
            throw std::runtime_error("No element can  be less 0");
    }  catch (const std::exception & a) {
        Util::logExcept(a.what());
    }

}

bool RbtreeModel::acceptableScale(int factor)
{

}

std::tuple<Util::__width_int, Util::__height_int> RbtreeModel::calculationMinPixSize()
{
    return {5,6};
}

bool RbtreeModel::isBlow()
{
    return false;
}

void RbtreeModel::clearAllDatas()
{

}

void RbtreeModel::initModelData()
{

}
