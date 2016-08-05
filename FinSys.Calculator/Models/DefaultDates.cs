using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Models
{
    public class DefaultDates
    {
        public string IntDayCount { get; set; }
        public string IntPayFreq { get; set; }
        public DateTime MaturityDate { get; set; }
        public DateTime ValueDate { get; set; }
        public bool EndOfMonthPay { get; set; }
        public string HolidayAdjust { get; set; }
        public IEnumerable<DateTime> Holidays { get; set; }
    }
}
