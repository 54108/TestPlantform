#ifndef CHART_H
#define CHART_H

#include <QObject>
#include <QThread>
#include <QChart>
#include <QLineSeries>
#include <QValueAxis>

class chart : public QObject
{
    Q_OBJECT

public:
    QChart *m_chart;

    chart(QObject *parent = nullptr)
    {
        // 创建折线序列
        m_series = new QLineSeries();

        // 创建图表
        m_chart = new QChart();
        m_chart->addSeries(m_series);
        m_chart->setTitle("测试");

        // 创建坐标轴
        m_axisX = new QValueAxis();
        m_axisY = new QValueAxis();
        m_chart->addAxis(m_axisX, Qt::AlignBottom);
        m_chart->addAxis(m_axisY, Qt::AlignLeft);
        m_series->attachAxis(m_axisX);
        m_series->attachAxis(m_axisY);

        // 设置坐标轴范围（根据实际需求调整）
        m_axisX->setRange(0, 100);
        m_axisY->setRange(0, 1000);
    }

public slots:
    void updateData(double xValue, double yValue)
    {
        // 添加新的数据点
        m_series->append(xValue, yValue);

        // 根据需要调整坐标轴范围
        if (xValue > m_axisX->max())
            m_axisX->setMax(xValue);

        // 重新绘制图表
        m_chart->update();
    }
    void test(int yValue)
    {
        // 添加新的数据点
        m_series->append(x, yValue);

        // 根据需要调整坐标轴范围
        if (x > m_axisX->max())
            m_axisX->setMax(x);

        x++;

        // 重新绘制图表
        m_chart->update();
    }

private:
    QLineSeries *m_series;
    QValueAxis *m_axisX;
    QValueAxis *m_axisY;
    int x = 0; //test
};

#endif // CHART_H
