#include "wordclock.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WordClock w;
    w.show();
    return a.exec();
}
