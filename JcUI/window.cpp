#include "window.h"

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <QComboBox>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QAction>
#include <QIcon>
#include <QPushButton>
#include <QtCharts>
#include <QPieSeries>
#include <QPieSlice>
#include <vector>
#include <regex>
#include <QDebug>
#include <QMessageBox>
#include <piechart.h>


Window::Window(QWidget *parent) : QWidget(parent) {


    QPushButton *button = new QPushButton("&Calculate", this);
    readInMBTI = new QLineEdit;
    readInMBTI->setPlaceholderText("Enter MBTI type and Astrological sign");
    readInMBTI->setFocus();

    QGridLayout *MBTIboxLayout = new QGridLayout;
    MBTIboxLayout->addWidget(readInMBTI, 0, 0);
    MBTIboxLayout->addWidget(button, 1, 0);
    QGroupBox *MBTI = new QGroupBox(tr("MBTI"));
    MBTI->setLayout(MBTIboxLayout);

    QGridLayout *layout = new QGridLayout;

    layout->addWidget(MBTI, 0, 0);
    setLayout(layout);

    connect(button, SIGNAL(clicked()), this, SLOT(nextStep2()));

}

void Window::nextStep2(){

    clickCount = 0;

    bool match =true;

    std::ifstream file("jcalg hardcode.txt");
    MBTIstring = std::string(this->readInMBTI->text().toStdString());

    if(MBTIstring.length() < 17) {

        while(getline(file, line)) {
         if(line.find(MBTIstring, 0) != std::string::npos && line.find(MBTIstring, 0) < 2) {
           returnLine = line;
           break;
         }
       }
    }


    if (returnLine == ""){
        QMessageBox noMBTImatch;;
        noMBTImatch.critical(0, "Error", "Does not match any given MBTI type");
        match = false;
    }

    if(match){


       wdg = new QWidget;
       wdg->show();

       std::regex r(" *(\\w+ \\w+)");
       std::smatch m;
       auto flag = std::regex_constants::match_continuous;
       while(std::regex_search(returnLine, m, r, flag)) {
           MBTIbroken.push_back(m[1]);
           returnLine = m.suffix().str();
       }



        series = new PieChart();
        series->append(QString::fromStdString(MBTIbroken[0]), 1);
        series->append(QString::fromStdString(MBTIbroken[1]), 2);
        series->append(QString::fromStdString(MBTIbroken[2]), 3);
        series->append(QString::fromStdString(MBTIbroken[3]), 4);
        series->append(QString::fromStdString(MBTIbroken[4]), 5);
        series->append(QString::fromStdString(MBTIbroken[5]), 6);
        series->append(QString::fromStdString(MBTIbroken[6]), 7);
        series->append(QString::fromStdString(MBTIbroken[7]), 8);
        series->append(QString::fromStdString(MBTIbroken[8]), 9);
        series->append(QString::fromStdString(MBTIbroken[9]), 10);
        series->append(QString::fromStdString(MBTIbroken[10]), 11);
        series->append(QString::fromStdString(MBTIbroken[11]), 12);

        series->setPieStartAngle(270);
        series->setPieEndAngle(-90);

        MBTIbroken.clear();

        QChart *chart = new QChart;
        chart->addSeries(series);
        chart->setTitle(QString::fromStdString(MBTIstring));


        chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartLayout = new QGridLayout(wdg);

        chartLayout->addWidget(chartView,0,0);

        for(qsizetype i = 0; i < series->count(); i++){
            QPieSlice *slice = series->slices().at(i);
            QString sliceID = slice->label();
            connect(series->slices().at(i), &QPieSlice::clicked, this, [this, sliceID, i] { sliceClicked(sliceID, i); });
        }
    }
}


void Window::sliceClicked (QString sliceIdentity, qsizetype i) {

    series->slices().at(i)->setExploded(true);

    for(qsizetype j = 0; j <series->slices().size(); j++){
        if(j!=i)
            series->slices().at(j)->setExploded(false);
    }

    if(clickCount == 0)
        clickCount = clickCount + 1;
    else if (clickCount == 1)
        clickCount = clickCount + 1;

    if(clickCount == 1){
        nextChartButtons = new QGridLayout;
        QPushButton *goToChart = new QPushButton ("&Go To Chart", this);
        QPushButton *seeWhereElse = new QPushButton ("&Other Locations", this);

        nextChartButtons->addWidget(goToChart, 0 , 0);
        nextChartButtons->addWidget(seeWhereElse, 1, 0);

        pieGroup = new QGroupBox(tr(sliceIdentity.toStdString().c_str()));

        pieGroup->setLayout(nextChartButtons);

        chartLayout->addWidget(pieGroup, 1, 0);
        connect(goToChart, &QPushButton::clicked, this, [this, sliceIdentity]{goToNextChart(sliceIdentity);});
        connect(seeWhereElse, &QPushButton::clicked, this, [this, sliceIdentity] {goToNextChart(sliceIdentity);});

    }

    else {
        pieGroup->setTitle(sliceIdentity);
    }
}

void Window::goToNextChart(QString nextChartMBTIstr){

    std::ifstream file("jcalg hardcode.txt");
    std::cerr << "in function" << std::endl;




}

void Window::otherLocations(QString otherLocationsMBTIstr){


}
