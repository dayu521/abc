#ifndef MYSCREEN_H
#define MYSCREEN_H
#include<QWidget>

class MyScreen : public QWidget
{
    Q_OBJECT
public:
    explicit MyScreen(QWidget *parent = nullptr);
    void paint(int x_);

signals:

public slots:

    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
private:
    QPixmap pix{100,200};
};

#endif // MYSCREEN_H
