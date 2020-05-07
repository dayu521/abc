#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>
#include<QTimer>
#include<memory>
#include"register_type.h"
#include"something.h"

class Simulator;

class FlutteringWings : public QWidget
{
    Q_OBJECT
public:
    explicit FlutteringWings(QWidget *parent = nullptr);
    ~FlutteringWings() override;

    struct SimMapping :Util::ObjFD
    {
        int pixFd{0};
    };

    void addMapping(std::initializer_list<SimMapping> s);

    void changeCanvasSize(Util::__width_int w_,Util::__height_int h_,bool isForce_=false);

    bool makeElementsBig(int factor);

    void initMesgOnPix(const QString & s="请先进行数据模拟,生成绘图数据");

    //播放动画
    virtual void playAnimation();

    //停止动画
    virtual void stopAnimation();

    bool isRunning()
    {
        return animationTimer->isActive();
    }

    //重放动画
    void prepareReplayAnimation();

    //设置动画间隔
    void setInterval(int millisecond_);

    //切换模拟器
    void setSim( int which_);

    //保存状态
    void saveStatus(int which_);

    //恢复
    void applyStatus(int which_);

signals:
    void hasNoModelData();
    void canNotPlay();
    void elementsSizeChanged(bool);
    void playCompleted();
//    void
public slots :
    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    int currentPixIndex{0};
    QPixmap * pix{};
    QVector<std::shared_ptr<QPixmap>> pixContainer{};

    int currentSimIndex{0};
    std::shared_ptr<Simulator> sim{};

    FreezePainter * currentFp{nullptr};

    QVector<SimMapping> mappingVec{};

    QTimer * animationTimer{nullptr};
    QTimer* throttleTimer{nullptr};     //节流计时器

    Util::__width_int wantedWidth{};
    Util::__height_int wantedHeight{};
    Util::__factor_int factor{};

};


#endif // MYSCREEN_H
