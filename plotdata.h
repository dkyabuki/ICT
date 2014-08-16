#ifndef PLOTDATA_H
#define PLOTDATA_H
#include <qwt_series_data.h>

class PlotData : public QwtArraySeriesData<QPointF>
{
public:
    PlotData();
    static PlotData &instancePot();
    static PlotData &instanceTor();

    virtual QRectF boundingRect() const;

    void append( const QPointF &point );

    void clear();
};

#endif // PLOTDATA_H
