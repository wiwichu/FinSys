﻿using FinSys.Wpf.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    public interface ICalculatorRepository
    {
        Task<List<string>> GetInstrumentClassesAsync();
        Task<List<string>> GetDayCountsAsync();
        Task<List<string>> GetHolidayAdjustAsync();
        Task<List<string>> GetPayFreqsAsync();
        Task<KeyValuePair<Instrument, Calculations>> GetInstrumentDefaultsAsync(Instrument instrument, Calculations calcs);
        Task<KeyValuePair<Instrument,Calculations>> GetDefaultDatesAsync(Instrument instrument, Calculations calculations,IEnumerable<Holiday> holidays);
        Task<List<string>> GetYieldMethodsAsync();
        Task<List<string>> GetInterpolationMethodsAsync();
        Task<KeyValuePair<Instrument, Calculations>> CalculateAsync(Instrument instrument, Calculations calculations,IEnumerable<Holiday> holidays);
        Task<DateTime> Forecast(DateTime startDate, DateTime endDate, int dayCountRule, int months, int days);
        Task<List<CashFlow>> PriceCashFlows(List<CashFlow> cashFlows, 
            string yieldMth, 
            string frequency, 
            string dayCount, 
            DateTime valueDate, 
            List<RateCurve> rateCurve,
            string interpolation);
    }
}
