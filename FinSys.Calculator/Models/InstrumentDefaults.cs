using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Models
{
    public class InstrumentDefaults
    {
        public string DayCount { get; set; }
        public string PayFreq { get; set; }
        public string YieldDayCount { get; set; }
        public string YieldFrequency { get; set; }
        public string YieldMethod { get; set; }
        public string EndOfMonthPay { get; set; }
        public string CalcHolidayAdjust { get; set; }
        public string PayHolidayAdjust { get; set; }
    }
}
