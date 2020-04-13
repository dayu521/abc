#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>

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
    void initMesg(const QString s="请先进行数据模拟,生成绘图数据");
signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QVector<QPixmap *> pixContainer;
    int currentPixIndex=0;
    QPixmap * pix;
};

#endif // MYSCREEN_H
