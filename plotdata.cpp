#include "plotdata.h"

PlotData::PlotData()
{
}

QRectF PlotData::boundingRect() const
{
    if ( d_boundingRect.width() < 0.0 )
    d_boundingRect = qwtBoundingRect( *this );
    return d_boundingRect;
}

void PlotData::append( const QPointF &point )
{
    d_samples += point;
}

void PlotData::clear()
{
    d_samples.clear();
    d_samples.squeeze();
    d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
}
