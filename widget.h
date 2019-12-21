#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"myscreen.h"
#include"setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class QScrollArea;
class Simulator;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    void initInterface();
    void prepareNewSimulation();

private:
    Ui::Widget *ui;
    QWidget * leftContainerWidget;
    MyScreen * rightContainerWidget;
    SettingPane * globalSetting;
    int i=0;
    QScrollArea * rightContainerWidgetWrap;
    Simulator *simulator;
    QTimer * animationTimer;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_startBtn_clicked();
};
#endif // WIDGET_H
