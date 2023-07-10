#include "videodesignerwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    videoDesignerWindow w;
    w.show();
    return a.exec();
}
