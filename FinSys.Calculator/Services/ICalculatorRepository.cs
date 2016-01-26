using FinSys.Calculator.Models;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Services
{
    public interface ICalculatorRepository
    {
        Task<List<InstrumentClass>> GetInstrumentClassesAsync();
        Task<List<string>> GetDayCountsAsync();
        Task<List<string>> GetHolidayAdjustAsync();
        Task<List<string>> GetPayFreqsAsync();
        Task<KeyValuePair<Instrument, Calculations>> GetInstrumentDefaultsAsync(Instrument instrument, Calculations calcs);
        Task<KeyValuePair<Instrument, Calculations>> GetDefaultDatesAsync(Instrument instrument, Calculations calculations, IEnumerable<Holiday> holidays);
        Task<List<string>> GetYieldMethodsAsync();
        Task<List<string>> GetInterpolationMethodsAsync();
        Task<KeyValuePair<Instrument, Calculations>> CalculateAsync(Instrument instrument, Calculations calculations, IEnumerable<Holiday> holidays);
        Task<DateTime> Forecast(DateTime startDate, DateTime endDate, int dayCountRule, int months, int days);
        Task<List<CashFlow>> PriceCashFlowsAsync(List<CashFlow> cashFlows,
            string yieldMth,
            string frequency,
            string dayCount,
            DateTime valueDate,
            List<RateCurve> rateCurve,
            string interpolation);
    }
}
