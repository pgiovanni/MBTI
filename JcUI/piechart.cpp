#include "piechart.h"

PieChart::PieChart()
{

}

PieChart* PieChart::getNextChart() {
    return nextChart;
}

void PieChart::setNextChart(PieChart* pieChartPointer){
    nextChart = pieChartPointer;
}

PieChart::~PieChart() {}
