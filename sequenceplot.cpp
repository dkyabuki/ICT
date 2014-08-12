#include "sequenceplot.h"
#include <qwt_plot.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_curve.h>
#include <qwt_symbol.h>
#include <qwt_plot_directpainter.h>
#include <qwt_painter.h>
#include <qpaintengine.h>

class PlotData : public QwtArraySeriesData<QPointF>
{
public:
    PlotData()
    {
    }

    virtual QRectF boundingRect() const
    {
        if ( d_boundingRect.width() < 0.0 )
        d_boundingRect = qwtBoundingRect( *this );
        return d_boundingRect;
    }

    inline void append( const QPointF &point )
    {
        d_samples += point;
    }

    void clear()
    {
        d_samples.clear();
        d_samples.squeeze();
        d_boundingRect = QRectF( 0.0, 0.0, -1.0, -1.0 );
    }
};

SequencePlot::SequencePlot(QWidget *parent):QwtPlot(parent),curve(NULL)
{
    dPainter = new QwtPlotDirectPainter(this);

    if ( QwtPainter::isX11GraphicsSystem() )
    {
#if QT_VERSION < 0x050000
        canvas()->setAttribute( Qt::WA_PaintOutsidePaintEvent, true );
#endif
        canvas()->setAttribute( Qt::WA_PaintOnScreen, true );
    }

    curve = new QwtPlotCurve( "Test Curve" );
    curve->setData( new PlotData() );
    showSymbols( true );

    curve->attach( this );

    setAutoReplot( false );
}

SequencePlot::~SequencePlot()
{
    delete curve;
}

void SequencePlot::appendPoint(const QPointF &point)
{
    PlotData *data = static_cast<PlotData *>( curve->data() );
    data->append( point );

    const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
    if ( doClip )
    {
        const QwtScaleMap xMap = canvasMap( curve->xAxis() );
        const QwtScaleMap yMap = canvasMap( curve->yAxis() );

        QRegion clipRegion;

        const QSize symbolSize = curve->symbol()->size();
        QRect r( 0, 0, symbolSize.width() + 2, symbolSize.height() + 2 );

        const QPointF center =
            QwtScaleMap::transform( xMap, yMap, point );
        r.moveCenter( center.toPoint() );
        clipRegion += r;

        dPainter->setClipRegion( clipRegion );
    }

    dPainter->drawSeries( curve, data->size() - 1, data->size() - 1 );
}

void SequencePlot::clearPoints()
{
    PlotData *data = static_cast<PlotData *>(curve->data());
    data->clear();
    replot();
}

void SequencePlot::showSymbols( bool on )
{
    if ( on )
    {
        curve->setStyle( QwtPlotCurve::NoCurve );
        curve->setSymbol( new QwtSymbol( QwtSymbol::XCross,
            Qt::NoBrush, QPen( Qt::black ), QSize( 4, 4 ) ) );
    }
    else
    {
        curve->setPen( Qt::white );
        curve->setStyle( QwtPlotCurve::Dots );
        curve->setSymbol( NULL );
    }

    replot();
}
