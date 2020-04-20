#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>
#include<memory>

class Simulator;
namespace {
    constexpr unsigned short MAXCOUNTS=8;
}
class MyScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MyScreen(QWidget *parent = nullptr);
    ~MyScreen() override;
    void setPixmapSource(Simulator *);
    void changeCanvasSize(int w_,int h_);
    void initMesg(const QString & s="请先进行数据模拟,生成绘图数据");
signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QVector<std::shared_ptr<QPixmap>> pixContainer;
    int currentPixIndex=0;
    std::shared_ptr<QPixmap>  pix;
};

#endif // MYSCREEN_H
