#ifndef SEQUENCEPLOT_H
#define SEQUENCEPLOT_H

#include <qwt_plot.h>
#include <QWidget>

class QwtPlotCurve;
class QwtPlotDirectPainter;

namespace Ui{
    class SequencePlot;
}

class SequencePlot : public QwtPlot
{
    Q_OBJECT

public:
    SequencePlot(QWidget *parent = NULL);
    virtual ~SequencePlot();

    void appendPoint(const QPointF &);
    void clearPoints();
    int size();

public Q_SLOTS:
    void showSymbols(bool);

private:
    QwtPlotCurve *curve;
    QwtPlotDirectPainter *dPainter;
};

#endif // SEQUENCEPLOT_H
