#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <QWidget>

namespace Ui {
class Environment;
}

class Environment : public QWidget
{
    Q_OBJECT

public:
    explicit Environment(QWidget *parent = nullptr);
    ~Environment();
signals:
    void showWidgetUI();

private slots:
    void on_envReturnButton_clicked();

private:
    Ui::Environment *ui;
};

#endif // ENVIRONMENT_H
