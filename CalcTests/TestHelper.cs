using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace CalcTests
{

    public class TestHelper
    {
        internal static CashFlowsDescr makeCashFlows(List<CashFlowDescr> cfList)
        {
            CashFlowsDescr cashFlowsDescr = new CashFlowsDescr();
            CashFlowDescr[] cfArray = cfList.ToArray();
            cashFlowsDescr.size = cfList.Count;
            cashFlowsDescr.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) * cfArray.Length);
            IntPtr buffer = new IntPtr(cashFlowsDescr.cashFlows.ToInt64());
            for (int i = 0; i < cfArray.Length; i++)
            {
                Marshal.StructureToPtr(cfArray[i], buffer, true);
                buffer = new IntPtr(buffer.ToInt64() + Marshal.SizeOf(typeof(CashFlowDescr)));
            }
            return cashFlowsDescr;
        }
        internal static DatesDescr makeDates(IEnumerable<DateTime> dates)
        {
            DatesDescr datesDescr = new DatesDescr();
            List<DateDescr> dList = dates.Select((d) =>
                new DateDescr
                {
                    day = d.Day,
                    month = d.Month,
                    year = d.Year
                }
            ).ToList();
            DateDescr[] dArray = dList.ToArray();
            datesDescr.size = dList.Count;
            datesDescr.dates = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)) * dArray.Length);
            IntPtr buffer = new IntPtr(datesDescr.dates.ToInt64());
            for (int i = 0; i < dArray.Length; i++)
            {
                Marshal.StructureToPtr(dArray[i], buffer, true);
                buffer = new IntPtr(buffer.ToInt64() + Marshal.SizeOf(typeof(DateDescr)));
            }
            return datesDescr;
        }


        public enum tenor_rule
        {
            date_no_cal,
            date_act_cal,
            date_30_cal,
            date_30e_cal,
            date_365_cal,
            date_365L_cal,
            date_actISDA_cal,
            date_365_25_cal,
            date_30german_cal,
            date_NL365_cal,
            date_30eplus_cal,
            date_30US_cal,
            date_365A_cal,
            date_366_cal
        };
        public enum instr_class_descs
        {
            instr_bund_class_desc,
            instr_goj_class_desc,
            instr_euro_class_desc,
            instr_gilt_class_desc,
            instr_ukcd_class_desc,
            instr_ukdsc_class_desc,
            instr_uscd_class_desc,
            instr_usdsc_class_desc,
            instr_ustbo_class_desc,
            instr_cp_class_desc,
            instr_fschatz_class_desc,
            instr_uschatz_class_desc,
            instr_uschatz_buba_class_desc,
            instr_ssd_class_desc,
            instr_mbs_class_desc/*,
			instr_float_class_desc,
			instr_cashflow_class_desc*/
        };
        //static public readonly int date_last_day_count = 14;
        static public readonly int noValue = 99999;

        public enum day_counts
        {
            date_30e_360_day_count
            , date_30_360_day_count
            , date_act_360_day_count
            , date_act_365_day_count
            , date_act_365cd_day_count
            , date_act_act_day_count
            , date_act_365L_day_count
        , date_act_actISDA_day_count
        , date_30_360german_day_count
        , date_NL_365_day_count
        , date_30eplus_360_day_count
        , date_30_360US_day_count
        , date_act_365A_day_count
        , date_act_366_day_count
            , date_act_360cd_day_count
        };
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
        event_sched_no_holiday_adj=99
        }
        //public static readonly int freq_count = 4;
        public enum frequency
        {
            frequency_annually
        , frequency_monthly
        , frequency_quarterly
        , frequency_semiannually
        };
       // public static readonly int py_last_yield_meth = 15; /*{py_last_yield_meth marks the last symbol.}*/
        public enum yield_method
        {
            py_aibd_yield_meth,
            py_mmdisc_yield_meth,
            py_mm_yield_meth,
            py_ytm_simp_yield_meth,
            py_ytm_comp_yield_meth,
            py_simp_yield_meth,
            py_curr_yield_meth,
            py_gm_yield_meth,
            py_muni_yield_meth,
            py_corp_yield_meth,
            py_ustr_yield_meth,
            py_moos_yield_meth,
            py_bf_yield_meth,
            py_ty_yield_meth
        };


    }
    [StructLayout(LayoutKind.Sequential)]
    internal class CashFlowDescr
    {
        public int year;
        public int month;
        public int day;
        public double amount;
        public double presentValue;
        public int adjustedYear;
        public int adjustedMonth;
        public int adjustedDay;
        public double discountRate;
    };
    [StructLayout(LayoutKind.Sequential)]
    internal class CashFlowsDescr
    {
        public IntPtr cashFlows; //CashFlowStruct Array
        public int size;
    };

    [StructLayout(LayoutKind.Sequential)]
    public class InstrumentDescr
    {
        public InstrumentDescr()
        {
            //holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_no_holiday_adj;
            holidayAdjust = TestHelper.noValue;
            //intDayCount = TestHelper.date_last_day_count;
            intDayCount = TestHelper.noValue;
            //intPayFreq = TestHelper.freq_count;
            intPayFreq = TestHelper.noValue;
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

    [StructLayout(LayoutKind.Sequential)]
    public class CalculationsDescr
    {
        public CalculationsDescr()
        {
            //yieldDayCount = TestHelper.date_last_day_count;
            yieldDayCount = TestHelper.noValue;
            //yieldFreq = TestHelper.freq_count;
            yieldFreq = TestHelper.noValue;
            // yieldMethod = TestHelper.py_last_yield_meth;
            yieldMethod = TestHelper.noValue;
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
    [StructLayout(LayoutKind.Sequential)]
    public class DateDescr
    {
        public int year;
        public int month;
        public int day;
    };
    [StructLayout(LayoutKind.Sequential)]
    public class DatesDescr
    {
        public IntPtr dates;
        public int size;
    };
    [StructLayout(LayoutKind.Sequential)]
    internal class RateCurveDescr
    {
        public IntPtr rates; //RateStruct Array
        public int size;
    };
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
    }
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
    }

}
