#ifndef FORM_H
#define FORM_H

#include <QWidget>

namespace Ui {
class Form;
}

class SettingPane : public QWidget
{
    Q_OBJECT

public:
    explicit SettingPane(QWidget *parent = nullptr);
    ~SettingPane();

private:
    QWidget * parent;
    Ui::Form *ui;

    // QWidget interface
};

#endif // FORM_H
