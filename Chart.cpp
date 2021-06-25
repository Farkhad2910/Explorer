#include "Chart.h"

Chart::~Chart()
{
    delete c_view;
}

Chart::Chart(QLayout *layout)
{
    c_model = new QChart();
    c_view = new QChartView();
    c_view->setChart(c_model);
    addWidget(layout);
}

void Chart::setChart(QList<Data> data) const
{
    qint64 size = 0;
    for (auto x : data)
    {
        size += x.size.toLongLong();
    }
    c_model->setTitle("");

    if (size == 0 || data.isEmpty())
    {
        c_model->setTitle("Folder is empty");
        c_model->removeAllSeries();
        return;
    }

    if (data.size() > 5)
    {
        qint64 siz = 0;
        auto ptr = data.begin() + 4;
        while (ptr != data.end())
        {
            siz += ptr->size.toLongLong();
            ptr = data.erase(ptr);
        }

        double percent = double(siz * 100) / size;
        data.push_back(Data("Others", QString::number(siz), QString::number(percent, 'f', 2).append(" %"), (qreal)siz / size));
    }

    setData(data);
}

void Chart::addWidget(QLayout *layout)
{
    layout->addWidget(c_view);
}

void Chart::update(QList<Data> data) const
{
    setChart(data);
}

void Chart::deleteSeries(QChart *chart) const
{
    chart->removeAllSeries();
}

void Chart::addSeries(QAbstractSeries *series) const
{
    c_model->addSeries(series);
}

void Chart::setData(QList<Data> data) const
{
    deleteSeries(c_model);
    QAbstractSeries* series = addData(data);
    addSeries(series);
}

PieChart::PieChart(QLayout *layout) : Chart(layout) {}

QAbstractSeries *PieChart::addData(QList<Data> data) const
{
    QPieSeries* series = new QPieSeries();
    for (auto ptr : data)
    {
        series->append(ptr.name + " (" + ptr.percent.toHtmlEscaped() + ")", ptr.part);
    }
    return series;
}

BarChart::BarChart(QLayout *layout) : Chart(layout) {}

QAbstractSeries *BarChart::addData(QList<Data> data) const
{
    QBarSeries* series = new QBarSeries();
    for (auto ptr : data)
    {
        QBarSet* set = new QBarSet(ptr.name + " (" + ptr.percent.toHtmlEscaped() + ")");
        set->append(ptr.part);
        series->append(set);
    }
    return series;
}
