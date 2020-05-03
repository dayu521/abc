#include "rbtree_model.h"

RbtreeModel::RbtreeModel()
{

}

void RbtreeModel::changeElementSize(int factor)
{
    if(factor==0)
        throw std::runtime_error("Factor can not be 0");
    ele.diameter*=factor;
    ele.radius=ele.diameter / 2;
    ele.nodeLineHeight=3 * ele.diameter / 2;
    ele.fontSize=ele.radius;
}
