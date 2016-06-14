using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Model
{
    [StructLayout(LayoutKind.Sequential)]
    public class InstrumentDescr
    {
        static public readonly int noValue = 99999;
        //static public readonly int date_last_day_count = 14;
        //public static readonly int freq_count = 4;
        public enum DateAdjustRule
        {
            event_sched_march_holiday_adj,
            /*{ event_sched_march_holiday_adj means the next business day is taken,
            and then becomes the new base for the next calculation, causing the day to
            march forward from month to month. It will never go into the next month
            however, but stay on the last business date once that is reached.}*/
            event_sched_next_holiday_adj,
            /*{ event_sched_next_holiday_adj means the next business day is taken.}*/
            event_sched_np_holiday_adj,
            /*{ event_sched_np_holiday_adj means the next business day is taken,
            but if this is in a different month, the previous business day is taken.}*/
            event_sched_prev_holiday_adj,
            /*{ event_sched_prev_holiday_adj means the previous business day is taken.}*/
            event_sched_pn_holiday_adj,
            /*{ event_sched_pn_holiday_adj means the previous business day is taken,
            but if this is in a different month, the next business day is taken.}*/
            event_sched_same_holiday_adj,
            /*{ event_sched_same_holiday_adj means that no adjustment occurs.}*/
            event_sched_no_holiday_adj = 99
        }

        public InstrumentDescr()
        {
            //holidayAdjust = (int)DateAdjustRule.event_sched_no_holiday_adj;
            //intDayCount = date_last_day_count;
            //intPayFreq = freq_count;
            holidayAdjust = noValue;
            intDayCount = noValue;
            intPayFreq = noValue;
        }
        public int instrumentClass;
        public int intDayCount;
        public int intPayFreq;
        public IntPtr maturityDate;
        public IntPtr issueDate;
        public IntPtr firstPayDate;
        public IntPtr nextToLastPayDate;
        public int endOfMonthPay;
        public double interestRate;
        public int holidayAdjust;
    };

}
