#include "simplegraph.h"
#include <math.h>
#include <QPainter>
#include <QMessageBox>
using namespace std;


QColor SimpleGraph::lineColor[16] = {
	QColor(255, 0, 0),
	QColor(0, 255, 0),
	QColor(185, 99, 188),
	QColor(255, 0, 255),
	QColor(0, 255, 255),
	QColor(255, 255, 0),
	QColor(155,55,255),
	QColor(255, 127, 0),
	QColor(106, 147, 219),
	QColor(209, 146, 117),
	QColor(143, 188, 143),
	QColor(245, 182, 204),
	QColor(40, 193, 164),
	QColor(165, 228, 64),
	QColor(204, 150, 53),
	QColor(236, 228, 137)

};

SimpleGraph::SimpleGraph(QWidget *parent)
: QFrame(parent)
{
	m_dataPointBuffer = NULL;
	m_drawDataBuffer = NULL;

	m_yCordRangeMax = 0;
	m_yCordRangeMin = 0;
	m_xIncByTime = 0;
	m_xCordTimeOffset = 0;
	m_xCordDividedRate = 0;
	m_xCordTimeDiv = 0;
	
	m_shiftCount = 0;

	m_plotCount = 0;
	m_copyDataCountPerChan = 0;
	m_pointCountPerScreen = 0;
	m_dataCountCachePerPlot = 0;
	m_dataCountPerPlot = 0;
	m_mapDataIndexPerPlot = 0;
	m_drawDataBufferLength = 0;
	
	setPalette(QPalette(Qt::black));
	setAutoFillBackground(true);
}

SimpleGraph::~SimpleGraph()
{
	if (m_drawDataBuffer != NULL)
	{
		delete []m_drawDataBuffer;
		m_drawDataBuffer = NULL;
	}

	if (m_dataPointBuffer != NULL)
	{
		delete []m_dataPointBuffer;
		m_dataPointBuffer = NULL;
	}
}

void SimpleGraph::paintEvent(QPaintEvent *event)
{
	QPainter p(this);
	QPen pen(Qt::darkGreen);
	p.setPen(pen);

	for (int i = 1; i < 10; i++)
	{
		p.drawLine(QPoint(i * rect().width() / 10, rect().top()), 
			QPoint(i * rect().width() / 10, rect().bottom()));
		p.drawLine(QPoint(rect().left(), i * rect().height() / 10),
			QPoint(rect().right(), i * rect().height() / 10));
	}
	QPoint *pstep = m_dataPointBuffer;
	for (int i = 0; i < m_plotCount; i++)
	{
		pen.setColor(SimpleGraph::lineColor[i]);
		p.setPen(pen);
		p.drawPolyline(pstep, m_copyDataCountPerChan);
		pstep = pstep + rect().width() * 4 + 1;
	}
}

void SimpleGraph::Chart(double *dataScaled, 
						int plotCount, 
						int dataCountPerPlot, 
						double xIncBySec)
{
	m_xIncByTime = xIncBySec;
	m_dataCountPerPlot = dataCountPerPlot;

	if (NULL == m_drawDataBuffer || plotCount != m_plotCount)
	{
		if (m_drawDataBuffer != NULL)
		{
			delete []m_drawDataBuffer;
			m_drawDataBuffer = NULL;
		}

		m_drawDataBufferLength = plotCount * (rect().width() * 4 + 1);
		m_drawDataBuffer = new double[m_drawDataBufferLength];
		memset(m_drawDataBuffer, 0, m_drawDataBufferLength * sizeof(double));
		if (m_drawDataBuffer == NULL)
		{
			QMessageBox::information(this, "Warning", tr("Sorry! Error in allocating memory..."));
			return;
		}

		if (m_dataPointBuffer != NULL)
		{
			delete []m_dataPointBuffer;
			m_dataPointBuffer = NULL;
		}

		m_dataPointBuffer = new QPoint[plotCount * (rect().width() * 4 + 1)];
		if (m_dataPointBuffer == NULL)
		{
			QMessageBox::information(this, "Warning", tr("Sorry! Error in allocating memory..."));
			return;
		}

		m_dataCountCachePerPlot = 0;
		m_plotCount = plotCount;
	}

	CalcDrawParams(m_xIncByTime, m_dataCountPerPlot);
	SaveData(dataScaled, plotCount, m_dataCountPerPlot);
	MapDataPoints();
	//repaint();
	update();
	
}

void SimpleGraph::CalcDrawParams(double XIncBySec, int dataCountPerPlot)
{
	mutex.lock();

	m_shiftCount = (int)(m_xCordTimeOffset * 1.0 / (XIncBySec * 1000));
	double XcoordinateDivBase = rect().width() * XIncBySec * 100.0;
	if (XIncBySec * 10 * 1000 <= 1)
	{
		m_shiftCount = (int)(m_shiftCount / 1000);
		XcoordinateDivBase = XcoordinateDivBase * 1000.0;
	}

	m_xCordDividedRate = XcoordinateDivBase / m_xCordTimeDiv;
	m_pointCountPerScreen = (int)ceil(rect().width() * m_xCordTimeDiv / XcoordinateDivBase) + 1;

	mutex.unlock();
}

void SimpleGraph::SaveData(double *data, int plotCount, int dataCountPerPlot)
{
	if (dataCountPerPlot * plotCount > m_drawDataBufferLength)
	{
		if (m_drawDataBuffer != NULL)
		{
			delete []m_drawDataBuffer;
			m_drawDataBuffer = NULL;
		}
		m_drawDataBufferLength = (dataCountPerPlot + 1) * plotCount;
		m_drawDataBuffer = new double[m_drawDataBufferLength];
		if (m_drawDataBuffer == NULL)
		{
			QMessageBox::information(this, "Warning", tr("Sorry! Error in allocating memory..."));
			return;
		}
		memset(m_drawDataBuffer, 0, m_drawDataBufferLength * sizeof(double));
	}

	if (dataCountPerPlot >= m_pointCountPerScreen)
	{
		m_mapDataIndexPerPlot = (m_dataCountPerPlot - m_pointCountPerScreen - 1);
		memcpy(m_drawDataBuffer, data, plotCount * dataCountPerPlot * sizeof(double));
		m_dataCountCachePerPlot = dataCountPerPlot;
	}
	else
	{
		m_mapDataIndexPerPlot = 0;
		if (m_dataCountCachePerPlot + dataCountPerPlot <= m_pointCountPerScreen)
		{
			memcpy(m_drawDataBuffer + m_dataCountCachePerPlot * plotCount, data, 
				plotCount * dataCountPerPlot * sizeof(double));
			m_dataCountCachePerPlot += dataCountPerPlot;
		} 
		else
		{
			int overflowCount = plotCount * (m_dataCountCachePerPlot + 
				dataCountPerPlot - m_pointCountPerScreen);
			memmove(m_drawDataBuffer, m_drawDataBuffer + overflowCount, 
				(plotCount * m_dataCountCachePerPlot - overflowCount) * sizeof(double));
			memcpy(m_drawDataBuffer + plotCount * m_dataCountCachePerPlot - overflowCount, 
				data, plotCount * dataCountPerPlot * sizeof(double));
			m_dataCountCachePerPlot = m_pointCountPerScreen;
		}
	}
}


void SimpleGraph::MapDataPoints()
{
	double YCordDividedRate = 1.0 * (rect().height() - 1) / (m_yCordRangeMax - m_yCordRangeMin);
	int count = m_dataCountCachePerPlot - (int)m_shiftCount - m_mapDataIndexPerPlot;
	int index = 0;

	m_copyDataCountPerChan = count > m_pointCountPerScreen ? m_pointCountPerScreen : count;
	for (int offset = m_mapDataIndexPerPlot; 
		offset < m_mapDataIndexPerPlot + m_copyDataCountPerChan; offset++)
	{
		index = offset - m_mapDataIndexPerPlot;
		for (int i = 0; i < m_plotCount; i++)
		{
			m_dataPointBuffer[i * (rect().width() * 4 + 1) + index].setY((long)ceil(YCordDividedRate * 
				(m_yCordRangeMax - m_drawDataBuffer[(int)(m_plotCount * (offset + m_shiftCount) + i)])));
			m_dataPointBuffer[i * (rect().width() * 4 + 1) + index].setX((long)((offset - 
				m_mapDataIndexPerPlot) * m_xCordDividedRate));
		}
	}
}

void SimpleGraph::Clear(void)
{
	m_xIncByTime = 0;
	m_plotCount = 0;
	m_copyDataCountPerChan = 0;
	
	m_mapDataIndexPerPlot = 0;
	m_pointCountPerScreen = 0;
	m_dataCountCachePerPlot = 0;
	m_dataCountPerPlot = 0;
	
	m_shiftCount = 0;
	repaint();
}

void SimpleGraph::Shift(int shiftTime)
{
   m_mapDataIndexPerPlot = 0;
	m_xCordTimeOffset = shiftTime;
	Draw();
}

void SimpleGraph::Div(int divTime)
{
   m_mapDataIndexPerPlot = 0;
	m_xCordTimeDiv = divTime;
	Draw();
}

void SimpleGraph::Draw()
{
	CalcDrawParams(m_xIncByTime, m_dataCountPerPlot);
	MapDataPoints();
	repaint();
}

void SimpleGraph::GetXCordRange(QString *rangeStrs, 
								double rangeMax, 
								double rangeMin, 
								TimeUnit unit)
{
	QString spted_unit[] = {tr("us"), tr("ms"), tr("Sec")};
	int tm_unit_idx;
	for (tm_unit_idx = unit; tm_unit_idx < Second && !(rangeMax < 1000); ++tm_unit_idx)
	{
		rangeMax /= 1000;
		rangeMin /= 1000;
	}

	rangeStrs[0].sprintf("%g", rangeMax);
	rangeStrs[0] += spted_unit[tm_unit_idx];
	rangeStrs[1].sprintf("%g", rangeMin);
	rangeStrs[1] += spted_unit[tm_unit_idx];
}

void SimpleGraph::GetYCordRange(QString *rangeStrs, 
								double rangeMax, 
								double rangeMin, 
								ValueUnit unit)
{
	QString spted_unit[] = {tr("kV"), tr("V"), tr("mV"), tr("uV"), 
							tr("KA"), tr("A"), tr("mA"), tr("uA"), 
							tr("C"), tr("")};
	int index = (int)unit;
	if (-1 == index)
	{
		index = 8;
	}

	rangeStrs[0].sprintf("%g", rangeMax);
	rangeStrs[0] += spted_unit[index];
	rangeStrs[1].sprintf("%g", rangeMin);
	rangeStrs[1] += spted_unit[index];
	rangeStrs[2] = (rangeMax == -rangeMin) ? tr("0") : tr("");
}

void SimpleGraph::GetYCordRange(QString *rangeStrs, 
								double rangeMax, 
								double rangeMin, 
								FrequencyUnit unit)
{
	QString spted_unit[] = {tr("Hz"), tr("KHz"), tr("MHz"), tr("")};
	int index = (int)unit;
	if (-1 == index)
	{
		index = 3;
	}

	rangeStrs[0].sprintf("%g", rangeMax);
	rangeStrs[0] += spted_unit[index];
	rangeStrs[1].sprintf("%g", rangeMin);
	rangeStrs[0] += spted_unit[index];
	rangeStrs[2] = (rangeMax == - rangeMin) ? tr("0") : tr("");
}