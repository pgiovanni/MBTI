#ifndef PIECHART_H
#define PIECHART_H


#include <QPieSeries>


class PieChart : public QPieSeries
{
public:
    PieChart();
    virtual ~PieChart();
    PieChart* getNextChart();
    void setNextChart(PieChart* pieChartPointer);
private:
    PieChart* nextChart;


};

#endif // PIECHART_H
