using FinSys.Wpf.Model;
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
        Task<List<InstrumentClass>> GetInstrumentClassesAsync();
        Task<List<string>> GetDayCountsAsync();
        Task<List<string>> GetHolidayAdjustAsync();
        Task<List<string>> GetPayFreqsAsync();
        Task<KeyValuePair<Instrument, Calculations>> GetInstrumentDefaultsAsync(Instrument instrument, Calculations calcs);
        Task<Instrument> GetDefaultDatesAsync(Instrument instrument, DateTime valueDate);
        Task<KeyValuePair<Instrument,Calculations>> GetDefaultDatesAsync(Instrument instrument, Calculations calculations);
        Task<List<string>> GetYieldMethodsAsync();
        Task<KeyValuePair<Instrument, Calculations>> CalculateAsync(Instrument instrument, Calculations calculations);
        Task<DateTime> Forecast(DateTime startDate, DateTime endDate, int dayCountRule, int months, int days);
    }
}
