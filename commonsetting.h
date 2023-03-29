#ifndef COMMONSETTING_H
#define COMMONSETTING_H

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class CommonSetting;
}

class CommonSetting : public QWidget
{
    Q_OBJECT

public:
    explicit CommonSetting(QWidget *parent = nullptr);
    ~CommonSetting();
signals:
    void showWidgetUI();
    void signtest();
private slots:
    void init();

    void on_close_clicked();

    void on_return_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::CommonSetting *ui;
};

#endif // COMMONSETTING_H
