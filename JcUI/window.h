#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include <QGroupBox>
#include <string>
#include <QGridLayout>
#include <QChart>
#include <QtCharts>
#include <vector>
#include <string>
#include <regex>
#include <piechart.h>
#include <iostream>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class Window : public QWidget
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);


public slots:
    void nextStep2();
    void sliceClicked(QString sliceIdentity, qsizetype i);
    void goToNextChart(QString nextChartMBTIstr);
    void otherLocations(QString otherLocationsMBTIstr);

private:
    QPieSlice *slice;
    QLineEdit *readInMBTI;
    QGroupBox *MBTI;
    std::string returnChart;
    std::vector<std::string> MBTIbroken;
    QWidget *wdg;
    QGroupBox *pieGroup;
    QGridLayout *chartLayout;
    PieChart* series;
    QList<QPieSlice> *pieSlices;
    QGridLayout *nextChartButtons;
    int clickCount;
    QGroupBox *pieGroup2;
    std::string MBTIstring;
    std::string line;
    std::string returnLine;
    QChartView *chartView;

};


#endif
