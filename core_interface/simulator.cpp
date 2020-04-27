#include"simulator.h"

Simulator::Simulator(std::shared_ptr<FreezePainter> fp_,std::shared_ptr<FarAway> fa_):
    animation{fp_},dataSource{fa_}
{

}
