#include "quicksortsim.h"
#include<QWidget>

QuicksortSimulation::QuicksortSimulation()
{

}

void QuicksortSimulation::makeElementsBig(int factor)
{
    dHeight+=factor;
    width+=factor;
}

void QuicksortSimulation::produceSimulateData()
{
    quickSort(data);
}

void QuicksortSimulation::clearSimulateData()
{

}

void QuicksortSimulation::prepareRepaintPixmap()
{
    pix->fill();
}

QString QuicksortSimulation::getName() const
{
    return "快速排序";
}

void QuicksortSimulation::currentSnapshot(int n_) const
{
    Q_UNUSED(n_)
}

int QuicksortSimulation::frameAllNumber() const
{
    return 10;
}

void QuicksortSimulation::nextFrame(int n_)
{
    Q_UNUSED(n_)
}

QSize QuicksortSimulation::calculationMinPixSize()
{
    auto x=0;
    std::for_each(elementContainer.begin(),elementContainer.end(),[&x](int e){x=e>x?e:x;});
    return {width*elementContainer.size(),x*dHeight*2};
}

void QuicksortSimulation::quickSort(QVector<int> &vec_, int left_, int right_)
{
    //三个或三个以上进行快排
    if(left_<=right_-9){
        auto pivot_Value=median3(vec_,left_,right_);
        int i=left_+1,j=right_;
        while (true) {
            while (vec_[++i]<pivot_Value) {
//                i++;
            }
            while (vec_[--j]>pivot_Value) {
//                j--;
            }
            if(i<j)
                std::swap(vec_[i],vec_[j]);
            else
                break;
        }
        std::swap(vec_[left_+1],vec_[j]);
        quickSort(vec_,left_,j-1);
        quickSort(vec_,j+1,right_);
    }else{
        //插入排序
        for(int i=left_+1;i<=right_;i++){
            auto temp_=vec_[i];
            int j=i;
            for(;j>left_&&vec_[j-1]>temp_;j--){
                vec_[j]=vec_[j-1];
            }
            vec_[j]=temp_;
        }
    }
}

int QuicksortSimulation::median3(QVector<int> &vec_, int left_, int right_)
{
    auto mid_=(left_+right_)/2;
    //先找最大值
    if(vec_[right_]<vec_[mid_])
        std::swap(vec_[right_],vec_[mid_]);
    if(vec_[right_]<vec_[left_])
        std::swap(vec_[right_],vec_[left_]);
    //再判断最小值和中间值
    if(vec_[mid_]<vec_[left_])
        std::swap(vec_[mid_],vec_[left_]);
    std::swap(vec_[left_+1],vec_[mid_]);
    return vec_[left_+1];
}

