#ifndef CHART_H
#define CHART_H
#include "FileExplorer.h"
#include <QWidget>
#include <QtCharts/QChartGlobal>
#include <memory>
#include <QtCharts/QAbstractSeries>
#include <QBarSeries>
#include <QPieSeries>
#include <QBarSet>
#include <QGraphicsLayout>
#include <QChartView>
#include <QLayout>
#include <QChartView>

using namespace QtCharts;

class Chart : public Observer
{
private:
    QChartView* c_view;
    QChart* c_model;
public:
    Chart() = default;
    virtual ~Chart();
    Chart(QLayout* layout);

    void setChart(QList<Data> data) const;
    void addWidget(QLayout* layout); // Добавление к layout'у
    void update(QList<Data> data) const; // Сигнал передает при завершении формирования данных
    void setData(QList<Data> data) const; // Данные в график
    virtual QAbstractSeries* addData( QList<Data> data) const = 0;
    void addSeries(QAbstractSeries* series) const;
    void deleteSeries(QChart* chart) const; // Данные из графика
};

class PieChart : public Chart
{
public:
    explicit PieChart(QLayout* layout);
    PieChart() = default;
    QAbstractSeries * addData(QList<Data> data) const;
};

class BarChart : public Chart
{
public:
    explicit BarChart(QLayout* layout);
    BarChart() = default;
    QAbstractSeries * addData(QList<Data> dataa) const;
};

#endif // CHART_H
