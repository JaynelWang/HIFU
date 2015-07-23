#pragma once

#include "math.h"
#include "assert.h" 
#define  PI    3.14159
enum WaveformStyle {sine, triangle, square};

struct WaveformParameter
{
   WaveformStyle Style;
   double        HighLevel;
   double        LowLevel;
};

class WaveformGenerator
{
private:
   int m_pointPerPeriod; 

public:
   WaveformGenerator(int pointPerPeriod)
   {
      m_pointPerPeriod = pointPerPeriod;
   }

   void SetPointPerPeriod(int pointPerPeriod)
   {
      m_pointPerPeriod = pointPerPeriod;
   }

   double GetOnePoint(WaveformStyle style, int index, double highLevel, double lowLevel)
   {
      double amplitude = (highLevel - lowLevel) / 2;
      double offset = (highLevel + lowLevel) / 2;
      double data = 0;

      assert(index >= 0 && index <= m_pointPerPeriod);

      switch (style)
      {
      case sine:
         {
            data = amplitude * sin(index * 2.0 * PI / m_pointPerPeriod) + offset;
            break;
         }
      case triangle:
         {
            if (index < (m_pointPerPeriod / 4.0))
            {
               data = amplitude * (index / (m_pointPerPeriod / 4.0)) + offset;
            }
            else if (index < 3 * (m_pointPerPeriod / 4.0))
            {
               data = amplitude * ((2.0 * (m_pointPerPeriod / 4.0) - index) / (m_pointPerPeriod / 4.0)) + offset;
            }
            else
            {
               data = amplitude * ((index - m_pointPerPeriod) / (m_pointPerPeriod / 4.0)) + offset;
            }
            break;
         } 
      case square:
         {
            if ((index >= 0) && (index < (m_pointPerPeriod / 2)))
            {
               data = amplitude * 1 + offset;
            }
            else
            {
               data = amplitude * (-1) + offset;
            }
            break;
         }
      default:
         {
            break;
         }   
      }   
      return data;
   }

   void GetOnePeriod(double *waveformBuffer, WaveformParameter waveParam)
   {
      for (int i = 0; i < m_pointPerPeriod; i++ )
      {
         waveformBuffer[i] = GetOnePoint(waveParam.Style, i, waveParam.HighLevel, waveParam.LowLevel);
      }
   }
   void GetMultipleWaveform(double *waveform, int waveCount, WaveformParameter *waveParam)
   {
      for (int i = 0; i < m_pointPerPeriod;i++ )
      {
         for (int j = 0; j < waveCount; j++)
         {
            waveform[j + i * waveCount] = GetOnePoint(waveParam[j].Style, i, waveParam[j].HighLevel, waveParam[j].LowLevel);
         }
      }
   }
};
