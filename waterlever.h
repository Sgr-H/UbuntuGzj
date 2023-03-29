#ifndef WATERLEVER_H
#define WATERLEVER_H

#include <QWidget>

namespace Ui {
class WaterLever;
}

class WaterLever : public QWidget
{
    Q_OBJECT

public:
    explicit WaterLever(QWidget *parent = nullptr);
    ~WaterLever();
signals:
    void showWidgetUI();
private:
    Ui::WaterLever *ui;
};

#endif // WATERLEVER_H
