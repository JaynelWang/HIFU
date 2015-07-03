#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H

#include <QFrame>
#include <QMutex>
#include "../../../inc/bdaqctrl.h"
using namespace Automation::BDaq;

enum TimeUnit { Microsecond, Millisecond, Second};

enum FrequencyUnit { Hz, KHz, MHz};

class SimpleGraph : public QFrame
{
	Q_OBJECT

public:
	SimpleGraph(QWidget *parent);
	~SimpleGraph();

	static void GetXCordRange(QString *rangeStrs, double rangeMax, double rangeMin, TimeUnit unit);
	static void GetYCordRange(QString *rangeStrs, double rangeMax, double rangeMin, FrequencyUnit unit);
	static void GetYCordRange(QString *rangeStrs, double rangeMax, double rangeMin, ValueUnit unit);

	void Chart(double *dataScaled, int plotCount, int dataCountOfPerPlot, double xIncBySec);
	void Clear(void);
	void Shift(int shiftTime);
	void Div(int divTime);
	void paintEvent(QPaintEvent *event);

private:
	void CalcDrawParams(double XIncBySec, int dataCountPerPlot);
	void MapDataPoints();
	void SaveData(double *data, int plotCount, int dataCountPerPlot);
	void Draw();

private:
	int			m_plotCount;
	int			m_pointCountPerScreen;
	int			m_copyDataCountPerChan;
	double		m_xIncByTime;
	double		m_xCordDividedRate;
	double		*m_drawDataBuffer;
	QPoint		*m_dataPointBuffer;
	double		m_shiftCount;
	int			m_drawDataBufferLength;
	int			m_dataCountCachePerPlot;
	int			m_mapDataIndexPerPlot;
	int			m_dataCountPerPlot;
	QMutex		mutex;

public:
	double				m_xCordTimeDiv;
	double				m_xCordTimeOffset;
	double				m_yCordRangeMax;
	double				m_yCordRangeMin;
	static QColor		lineColor[16];
};

#endif // SIMPLEGRAPH_H
