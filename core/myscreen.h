#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>

class MyScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MyScreen(QWidget *parent = nullptr);
    void paint(QPixmap &&);
    void setHeight(int h){
        height=h;
    }
    void setWidth(int w){
        width=w;
    }
signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
private:
    int height;
    int width;
    QPixmap pix{100,200};
};

#endif // MYSCREEN_H
