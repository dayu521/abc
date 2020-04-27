#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>
#include<QTimer>
#include<memory>

class Simulator;
namespace {
    constexpr unsigned short MAXCOUNTS=8;
}
class FlutteringWings : public QWidget
{
    Q_OBJECT
public:
    explicit FlutteringWings(QWidget *parent = nullptr);
    ~FlutteringWings() override;

    using __width=int;
    using __height=int;

    void changeCanvasSize(__width w_,__height h_);

    void makeElementsBig(int factor);

    void initMesg(const QString & s="请先进行数据模拟,生成绘图数据");

    //返回当前可容纳所有内容的最小大小.例如,显示控件大小必定至少等于此大小(width,height)
    virtual std::tuple<__width,__height> calculationMinPixSize()=0;

    //播放动画
    virtual void playAnimation()=0;

    //停止动画
    virtual void stopAnimation()=0;

    //切换模拟器
    void switchS( int witch_);

    //当前模拟器
    auto getS()const
    {
        return sim;
    }

    using SimCreator=std::function<std::shared_ptr<Simulator>()>;

    template<typename T>
    std::enable_if_t<std::is_base_of_v<Simulator,T>,int> registerSim();

    void creatorObject(int type_=-1);

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    int currentPixIndex=0;
    QPixmap * pix{};
    QVector<std::shared_ptr<QPixmap>> pixContainer{};
    std::shared_ptr<Simulator> sim{};
    //key=type,value=isAlreadyCreated,createFn
    QHash<int,std::pair<bool,SimCreator>> objRegisters{};
    //simulator,pixId
    QVector<std::pair<std::shared_ptr<Simulator>,int>> vecSim{};

    QTimer ainmationTimer{};
};

template<typename T>
std::enable_if_t<std::is_base_of_v<Simulator,T>, int> FlutteringWings::registerSim()
{
    static int i=0;
    int key=-1;
    if(i==0){
        key=vecSim.size();
        objRegisters.insert(key,std::make_pair(false,[](){std::make_shared<T>();}));
        i++;
    }
    return key;
}

#endif // MYSCREEN_H
