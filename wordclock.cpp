#include "WordClock.h"
#include <QDebug>

WordClock::WordClock(QWidget *parent) : QMainWindow(parent) {
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setupGrid();
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &WordClock::updateClock);
    timer->start(60000);
    updateClock();
}

void WordClock::setupGrid() {
    grid = new QGridLayout(centralWidget);
    // Update to 11 rows and 11 columns.
    const int rows = 11;
    const int cols = 11;

    // Update the words list to have 11 characters in each string.
    QStringList words = {
        "ITLISASAMPMX",
        "ACQUARTERDCX",
        "TWENTYFIVEXX",
        "HALFSTENFTOX",
        "PASTERUNINEX",
        "ONESIXTHREEX",
        "FOURFIVETWOX",
        "EIGHTELEVENX",
        "SEVENTWELVEX",
        "TENSEOCLOCKX",
        "            "   // Additional row with 11 elements
    };

    // Create the grid of labels with updated rows and columns.
    labels.resize(rows);
    for (int i = 0; i < rows; i++) {
        labels[i].resize(cols);
        for (int j = 0; j < cols; j++) {
            QLabel* label = new QLabel(QString(words[i][j]), this);
            label->setAlignment(Qt::AlignCenter);
            label->setStyleSheet("QLabel { color: grey; }"); // Default colour
            grid->addWidget(label, i, j);
            labels[i][j] = label;
        }
    }

    centralWidget->setLayout(grid);
}


void WordClock::updateClock() {
    const QTime time = QTime::currentTime();
    highlightWords(time);
}

QStringList WordClock::getHourWords(int hour) {
    QStringList words;
    hour %= 12;
    if (hour == 0) hour = 12;

    switch (hour) {
    case 1: words << "ONE"; break;
    case 2: words << "TWO"; break;
    case 3: words << "THREE"; break;
    case 4: words << "FOUR"; break;
    case 5: words << "FIVE"; break;
    case 6: words << "SIX"; break;
    case 7: words << "SEVEN"; break;
    case 8: words << "EIGHT"; break;
    case 9: words << "NINE"; break;
    case 10: words << "TEN"; break;
    case 11: words << "ELEVEN"; break;
    case 12: words << "TWELVE"; break;
    default: break;
    }

    return words;
}

QStringList WordClock::getMinuteWords(int minute) {
    QStringList words;
    if (minute >= 1 && minute < 5) {
        words << "FIVE" << "PAST";
    } else if (minute >= 5 && minute < 10) {
        words << "TEN" << "PAST";
    }
    else if (minute >= 5 && minute < 15) {
        words << "QUARTER" << "PAST";
    } else if (minute >= 15 && minute < 25) {
        words << "TWENTY" << "PAST";
    }
    else if (minute >= 25 && minute < 30) {
        words << "TWENTY" << "FIVE" << "PAST";
    }
    else if (minute >= 30 && minute < 45) {
        words << "HALF" << "TO";
    } else if (minute >= 45 && minute < 50) {
        words << "QUARTER" << "TO";
    } else if (minute >= 50 && minute < 55) {
        words << "TEN" << "TO";
    }
    else if(minute >= 55){
        words << "FIVE" << "TO";
    }
    else {
        // This would be on the hour, handled separately.
    }

    return words;
}

void WordClock::highlightWords(const QTime& time) {
    clearHighlights();

    QStringList wordsToHighlight = {"IT", "IS"};

    int hour = time.hour();
    int minute = time.minute();

    wordsToHighlight << getMinuteWords(minute);

    if (minute >= 30) {
        hour++;
    }

    if(hour == 24) {
        hour = 0;
    }

    wordsToHighlight << getHourWords(hour % 12);


    if (minute < 5) {
        wordsToHighlight << "OCLOCK";
    }

    // Highlight the words
    for (const QString& word : wordsToHighlight) {
        highlightWord(word);
    }
}

void WordClock::clearHighlights() {
    for (int i = 0; i < labels.size(); i++) {
        for (int j = 0; j < labels[i].size(); j++) {
            labels[i][j]->setStyleSheet("QLabel { color: grey; }");
        }
    }
}

void WordClock::highlightWord(const QString& word) {
    for (int i = 0; i < labels.size(); i++) {
        QString rowString;
        for (int j = 0; j < labels[i].size(); j++) {
            rowString.append(labels[i][j]->text());
        }

        int startIndex = rowString.indexOf(word);
        if (startIndex != -1) {
            for (int k = startIndex; k < startIndex + word.length(); k++) {
                labels[i][k]->setStyleSheet("QLabel { color: red; font-weight: bold; }");
            }
            break;
        }
    }
}


