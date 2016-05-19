using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Services
{
    public class CalculatorRepository : ICalculatorRepository
    {
        private List<string> classes = new List<string>();
        public CalculatorRepository()
        {
            classes = GetInstrumentClassesAsync().Result;
        }
        public async Task<List<string>> GetInstrumentClassesAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                if (classes.Count > 0)
                {
                    return classes;
                }
                List<string> instrumentClasses = new List<string>()
                {
                    "German Bund",
                    "Japan Gov",
                    "UK Gilt",
                    "UK CD",
                    "UK Discount",
                    "US CD",
                    "US Discount",
                    "US TBOND",
                    "Commercial Paper",
                    "Finanzierungsschatz",
                    "U-Schatz",
                    "Eurobond",
                    "MBS"
                };
                return instrumentClasses;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }

    }

}

