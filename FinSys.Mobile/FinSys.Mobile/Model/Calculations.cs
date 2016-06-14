using FinSys.Mobile.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Model
{
    public class Calculations
    {
        public DateTime ValueDate { get; set; }
        public DateTime PreviousPayDate { get; set; }
        public DateTime NextPayDate { get; set; }
        public double Interest { get; set; }
        public double PriceIn { get; set; }
        public double PriceOut { get; set; }
        public double YieldIn { get; set; }
        public double YieldOut { get; set; }
        public double Duration { get; set; }
        public double ModifiedDuration { get; set; }
        public double Convexity { get; set; }
        public double Pvbp { get; set; }
        public bool IsExCoup { get; set; }
        public int ExCoupDays { get; set; }
        public int InterestDays { get; set; }
        public double ServiceFee { get; set; }
        public int PrepayModel { get; set; }
        public bool CalculatePrice { get; set; }
        public string YieldDayCount { get; set; }
        public string YieldFreq { get; set; }
        public string YieldMethod { get; set; }
        public double PvbpConvexityAdjusted { get; set; }
        public IEnumerable<CashFlow> Cashflows { get; set; }
        public string PayHolidayAdjust { get; set; }
        public bool TradeFlat { get; set; }
    }
}
