#ifndef WIDGET_H
#define WIDGET_H

#include<initializer_list>
#include<memory>
#include <QWidget>
#include"myscreen.h"
#include"setting.h"
#include"common.h"

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
    Simulator * currentSimulator;
    QVector<std::shared_ptr<Simulator>> simContainer;
    QTimer * animationTimer;
    QTimer * throttleTimer;     //节流计时器
    bool isctl;
    QPixmap  pp{300,300};
    int factor=1;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
private slots:
    void on_startBtn_clicked();
signals:
    void changeElementsSize(int);
};
#endif // WIDGET_H
