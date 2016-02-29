using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class InstrumentDefaultsViewModel
    {
        public string DayCount { get; set; }
        public string PayFreq { get; set; }
        public string YieldDayCount { get; set; }
        public string YieldFrequency {get; set;}
        public string YieldMethod { get; set; }
        public bool EndOfMonthPay { get; set; }
        public string HolidayAdjust { get; set; }
    }
}
