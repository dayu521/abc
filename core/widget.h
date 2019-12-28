#ifndef WIDGET_H
#define WIDGET_H

#include<initializer_list>
#include<memory>
#include <QWidget>
#include"myscreen.h"
#include"setting.h"
#include"common.h"
#include<QPointer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QScrollArea;
class QMenu;
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
    void changeSimulator(int index_=0);
    void showMsg();

private:
    Ui::Widget *ui;
    QPointer<QMenu> menu;
    Configuration settings;
    QPointer<SettingPane> globalSetting;
    QPointer<QStackedWidget> dataInputPane;     //容纳各个simulator各自的输入和控制面板
    int currentIndex=0;
    Simulator * currentSimulator;
    QVector<std::shared_ptr<Simulator>> simContainer;
    QPointer<QTimer> animationTimer;
    QPointer<QTimer> throttleTimer;     //节流计时器
    bool isctl;
    int factor=5;   
    Mode mode;
    int mm=0;

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual bool eventFilter(QObject *object, QEvent *event) override;
    virtual void contextMenuEvent(QContextMenuEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;
private slots:
    void on_startBtn_clicked();
signals:
    void changeElementsSize(int);
};
#endif // WIDGET_H
