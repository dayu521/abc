#ifndef WIDGET_H
#define WIDGET_H

#include<initializer_list>
#include<memory>
#include <QWidget>
#include"myscreen.h"
#include"setting.h"
#include"common.h"
#include<QPointer>
#include"csimulator.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class QScrollArea;
class QMenu;
class Simulator;
class QStackedWidget;

enum Status{HasData,Unused};

struct WidgetMappingInfo : Util::ObjFD
{
    QString showName{};     //控件显示的名字
    int menuListIndex{0};       //显示的菜单列表索引
    int dataInputPaneIndex{0};       //在被容器插入时,由插入时顺序决定
//        Status stat=Unused;        //模拟器状态
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void addMapping(std::initializer_list<WidgetMappingInfo> list_);
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

    int currentSimMapping=0;
    std::shared_ptr<Simulator> currentSimulator;
    int currentActionIndex=0;
    int currentActionNumber=0;

    QHash<int,WidgetMappingInfo> simMappingContainer;
    QPointer<QTimer> timeLine;
    QPointer<QTimer> throttleTimer;     //节流计时器
    bool isctl;
    int factor=5;
    Mode mode;

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
    void on_horizontalSlider_valueChanged(int value);

signals:
    void changeElementsSize(int);
};

#endif // WIDGET_H
