#ifndef WIDGETUI_H
#define WIDGETUI_H

#include <QWidget>
#include <QTimer>
#include <QThread>
#include "bridgemanager.h"
#include <QFont>
#include <QFontDatabase>
#include <QMessageBox>
//#include "framelesscore/framelessmainwindow.h"
#include "framelesscore/framelesswidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class WidgetUI; }
QT_END_NAMESPACE

class WidgetUI : public FramelessWidget
{
    Q_OBJECT

public:
    WidgetUI(QWidget *parent = nullptr);
    ~WidgetUI();
signals:
    void signtest();
private slots:
    //    void on_serialPushButton_clicked();

    void on_pushButton_clicked();

    void on_aboutgzjPushButton_clicked();


    void on_btnMenu_Min_clicked();

private:
    void init();
    void initWidgetUI();
    void UIConnect();

    //刷新定位变量
    quint8 elecRowPos=0;
    QTimer *flashElec=nullptr;

    //测试用变量
    quint8 switchPage=1;
    QSqlTableModel *model=nullptr;
    QFont iconfont;
    QThread *bridgeManagerThread=nullptr;
    Ui::WidgetUI *ui;
};
#endif // WIDGETUI_H
