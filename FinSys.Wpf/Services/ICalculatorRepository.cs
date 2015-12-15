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
        Task<List<string>> GetPayFreqsAsync();
        Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> calcs);
    }
}
