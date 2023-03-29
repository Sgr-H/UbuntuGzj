#ifndef LIFTMANAGER_H
#define LIFTMANAGER_H

#include <QWidget>

namespace Ui {
class LiftManager;
}

class LiftManager : public QWidget
{
    Q_OBJECT

public:
    explicit LiftManager(QWidget *parent = nullptr);
    ~LiftManager();
signals:
    void showWidgetUI();
private:
    Ui::LiftManager *ui;
};

#endif // LIFTMANAGER_H
