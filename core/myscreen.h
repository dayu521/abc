#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>
class Simulator;

class MyScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MyScreen(QWidget *parent = nullptr);
    void setSource(Simulator *);
    void setHeight(int h){
        pixheight=h;
    }
    void setWidth(int w){
        pixwidth=w;
    }
signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    int pixheight;
    int pixwidth;
    QPixmap pixTemp{500,500};
    QPixmap * pix;
};

#endif // MYSCREEN_H
