#ifndef WIDGET_H
#define WIDGET_H

#include<initializer_list>
#include<memory>
#include <QWidget>
#include"myscreen.h"
#include"setting.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE
class QScrollArea;
class Simulator;
class QStackedWidget;

struct Fufu
{
    int id=0;
    QString name;
    Simulator *sim=nullptr;
    QWidget *ui=nullptr;
    Fufu(int id_=0,QString name_=QString(),Simulator * s_=nullptr,QWidget * ui_=nullptr):
        id(id_),name(name_),sim(s_),ui(ui_){}
};
struct Configuration
{
    int animationInterval;

};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void setSimulator(std::initializer_list<std::shared_ptr<Simulator>> list_);
    ~Widget();
private:
    void loadCnf();
    void initUI();
    void prepareNewSimulation();
    void initAction();
    void prepare();

private:
    Ui::Widget *ui;
    Configuration settings;
    SettingPane * globalSetting;
    QStackedWidget * dataInputPane;
    int currentIndex=0;
    Fufu currentSimulator;
    QVector<std::shared_ptr<Simulator>> simContainer;
    QTimer * animationTimer;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
private slots:
    void on_startBtn_clicked();
};
#endif // WIDGET_H
