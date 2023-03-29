#ifndef FIREP_H
#define FIREP_H

#include <QWidget>

namespace Ui {
class FireP;
}

class FireP : public QWidget
{
    Q_OBJECT

public:
    explicit FireP(QWidget *parent = nullptr);
    ~FireP();
signals:
    void showWidgetUI();
    void process_fpMsg(const quint8 &_info_port,const QString &_string_data);
private:
    Ui::FireP *ui;
};

#endif // FIREP_H
