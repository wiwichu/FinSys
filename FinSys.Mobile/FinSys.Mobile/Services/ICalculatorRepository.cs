using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Services
{
    public interface ICalculatorRepository
    {
        Task<List<string>> GetInstrumentClassesAsync();
    }
}
