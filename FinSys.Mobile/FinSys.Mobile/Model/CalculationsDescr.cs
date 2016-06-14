using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Model
{
    [StructLayout(LayoutKind.Sequential)]
    public class CalculationsDescr
    {
        //public static readonly int py_last_yield_meth = 15; /*{py_last_yield_meth marks the last symbol.}*/

        public CalculationsDescr()
        {
            //yieldDayCount = InstrumentDescr.date_last_day_count;
            //yieldFreq = InstrumentDescr.freq_count;
            //yieldMethod = py_last_yield_meth;
            yieldDayCount = InstrumentDescr.noValue;
            yieldFreq = InstrumentDescr.noValue;
            yieldMethod = InstrumentDescr.noValue;
        }
        public int interestDays;
        public IntPtr valueDate;
        public IntPtr previousPayDate;
        public IntPtr nextPayDate;
        public double interest;
        public double priceIn;
        public double priceOut;
        public double yieldIn;
        public double yieldOut;
        public double duration;
        public double convexity;
        public double pvbp;
        public int isExCoup;
        public int exCoupDays;
        public double serviceFee;
        public int prepayModel;
        public int calculatePrice;
        public int yieldDayCount;
        public int yieldFreq;
        public int yieldMethod;
        public double modifiedDuration;
        public double pvbpConvexityAdjusted;
        public int tradeflat;
    };
}
