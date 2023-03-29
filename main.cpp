#include "widgetui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    qputenv("QT_VIRTUALKEYBOARD_STYLE", "mystyle");
    QApplication a(argc, argv);
//    WidgetUI *w=new WidgetUI();
//    w->show();
    WidgetUI w;
    w.show();
    return a.exec();
}
