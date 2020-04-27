#include "rbtree_sim.h"
#include "animation/abstract_animation.h"

Rbtree::Rbtree():Simulator(std::make_shared<FreezePainter>(),std::make_shared<FarAway>())
{

}

bool Rbtree::isOver() const
{
    this->animation->;
}
