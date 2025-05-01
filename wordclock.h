#ifndef WORDCLOCK_H
#define WORDCLOCK_H

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QTimer>
#include <QTime>


QT_BEGIN_NAMESPACE
namespace Ui {
class WordClock;
}
QT_END_NAMESPACE

class WordClock : public QMainWindow {
    Q_OBJECT

public:
    WordClock(QWidget *parent = nullptr);

private slots:
    void updateClock();

private:
    void setupGrid();
    void highlightWords(const QTime &time);
    QStringList getMinuteWords(int minute);
    QStringList getHourWords(int minute);
    void clearHighlights();
    void highlightWord(const QString& word);
    QWidget *centralWidget;
    QGridLayout *grid;
    QVector<QVector<QLabel*>> labels;
};
#endif // WORDCLOCK_H
