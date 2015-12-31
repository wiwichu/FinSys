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
        };
        public enum frequency
        {
            frequency_annually
        , frequency_monthly
        , frequency_quarterly
        , frequency_semiannually
        };
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
        public int instrumentClass;
        public int intDayCount;
        public int intPayFreq;
        public IntPtr maturityDate;
        public IntPtr issueDate;
        public IntPtr firstPayDate;
        public IntPtr nextToLastPayDate;
        public int endOfMonthPay;
        public double interestRate;
    };
    [StructLayout(LayoutKind.Sequential)]
    public class CalculationsDescr
    {
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
    };
    [StructLayout(LayoutKind.Sequential)]
    public class DateDescr
    {
        public int year;
        public int month;
        public int day;
    };
    public class InstrumentClass
    {
        public string Name { get; set; }
    }
    public class Instrument
    {
        public string Name { get; set; }
        public InstrumentClass Class { get; set; }
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
