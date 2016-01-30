using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Models
{
    public class Instrument
    {
        public string Name { get; set; }
        public string Class { get; set; }
        public string IntDayCount { get; set; }
        public string IntPayFreq { get; set; }
        public DateTime MaturityDate { get; set; }
        public DateTime IssueDate { get; set; }
        public DateTime FirstPayDate { get; set; }
        public DateTime NextToLastPayDate { get; set; }
        public bool EndOfMonthPay { get; set; }
        public double InterestRate { get; set; }
        public string HolidayAdjust { get; set; }
    }
}
