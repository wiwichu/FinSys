using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;

namespace FinSys.Wpf.Services
{
    public class CalculatorRepository : ICalculatorRepository
    {


        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getclassdescriptions(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getdaycounts(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getpayfreqs(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getStatusText(int status, StringBuilder text, out int textSize);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getInstrumentDefaults(InstrumentDescr instrument);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getDefaultDates(InstrumentDescr instrument, DateDescr valueDate);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getDefaultDatesAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getyieldmethods(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int calculate(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getInstrumentDefaultsAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getCashFlows( CashFlowsDescr cashFlows, ref int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int calculateWithCashFlows(InstrumentDescr instrument, CalculationsDescr calculations, CashFlowsDescr cashFlows, int dateAdjustRule);


        private List<string> classes = new List<string>();
        private List<string> dayCounts = new List<string>();
        private List<string> payFreqs = new List<string>();
        private List<string> yieldMethods = new List<string>();
        public CalculatorRepository()
        {
            classes = new List<string>( GetInstrumentClassesAsync().Result.Select((ic)=>ic.Name));
            dayCounts = GetDayCountsAsync().Result;
            payFreqs = GetPayFreqsAsync().Result;
            yieldMethods = GetYieldMethodsAsync().Result;
        }

        public async Task<List<string>> GetDayCountsAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> daycounts = new List<string>();
                int size;
                IntPtr ptr = getdaycounts(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string name = Marshal.PtrToStringAnsi(strPtr);
                    daycounts.Add(name);
                    ptr += Marshal.SizeOf(typeof(IntPtr));
                }
                return daycounts;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }

        public async Task<List<InstrumentClass>> GetInstrumentClassesAsync()
        {
            List<InstrumentClass> result = await Task.Run(() =>
            {
                List<InstrumentClass> instrumentClasses = new List<InstrumentClass>();
                int size;
                IntPtr ptr = getclassdescriptions(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    Console.WriteLine("i = " + i);
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string description = Marshal.PtrToStringAnsi(strPtr);
                    InstrumentClass ic = new InstrumentClass
                    {
                        Name=description
                    };
                    instrumentClasses.Add(ic);
                    ptr += Marshal.SizeOf(typeof(IntPtr));
                }
                return instrumentClasses;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }

        public async Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> instrumentsIn)
        {
            try {
                List<Instrument> result = await Task.Run(() =>
                {
                    List<Instrument> instruments = new List<Instrument>();
                    for (int i = 0; i < instrumentsIn.Count; i++)
                    {
                        Instrument ins = instrumentsIn[i];
                        InstrumentDescr instr = makeInstrumentDescr(ins);
                        instr.holidayAdjust = (int)InstrumentDescr.DateAdjustRule.event_sched_no_holiday_adj;
                        instr.intDayCount = InstrumentDescr.date_last_day_count;
                        instr.intPayFreq = InstrumentDescr.freq_count;

                        int status = getInstrumentDefaults(instr);
                        if (status != 0)
                        {
                            StringBuilder statusText = new StringBuilder(200);
                            int textSize;
                            status = getStatusText(status, statusText, out textSize);
                            throw new InvalidOperationException(statusText.ToString());
                        }
                        Instrument newInstr = makeInstrument(instr);
                        instruments.Add(newInstr);
                        GC.KeepAlive(instr);
                    }
                    return instruments;
                })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
                return result;
            }
            catch (InvalidOperationException)
            {
                throw;
            }
        }

        public async Task<List<string>> GetPayFreqsAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> payfreqs = new List<string>();
                int size;
                IntPtr ptr = getpayfreqs(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string name = Marshal.PtrToStringAnsi(strPtr);
                    payfreqs.Add(name);
                    ptr += Marshal.SizeOf(typeof(IntPtr));
                }
                return payfreqs;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }
        private Instrument makeInstrument(InstrumentDescr instr)
        {
            IntPtr matPtr = Marshal.ReadIntPtr(instr.maturityDate);
            DateDescr matDate = new DateDescr();
            matDate = Marshal.PtrToStructure<DateDescr>(instr.maturityDate);
            IntPtr issPtr = Marshal.ReadIntPtr(instr.issueDate);
            DateDescr issDate = new DateDescr();
            issDate = Marshal.PtrToStructure<DateDescr>(instr.issueDate);
            IntPtr fpPtr = Marshal.ReadIntPtr(instr.firstPayDate);
            DateDescr fpDate = new DateDescr();
            fpDate = Marshal.PtrToStructure<DateDescr>(instr.firstPayDate);
            IntPtr ntlPtr = Marshal.ReadIntPtr(instr.nextToLastPayDate);
            DateDescr ntlDate = new DateDescr();
            ntlDate = Marshal.PtrToStructure<DateDescr>(instr.nextToLastPayDate);
            Instrument newInstr = new Instrument
            {
                EndOfMonthPay = (instr.endOfMonthPay==1),
                IntDayCount = dayCounts[instr.intDayCount],
                IntPayFreq = payFreqs[instr.intPayFreq],
                Class = new InstrumentClass
                {
                    Name = classes[instr.instrumentClass]
                },
                MaturityDate = new DateTime(matDate.year, matDate.month, matDate.day),
                IssueDate = new DateTime(issDate.year, issDate.month, issDate.day),
                FirstPayDate = new DateTime(fpDate.year, fpDate.month, fpDate.day),
                NextToLastPayDate = new DateTime(ntlDate.year, ntlDate.month, ntlDate.day),
                InterestRate = instr.interestRate              
            };

            return newInstr;
        }

        private InstrumentDescr makeInstrumentDescr(Instrument instrument)
        {
            Instrument ins = instrument;
            int insClassNum = classes.IndexOf(ins.Class.Name);
            int insDayCount = dayCounts.IndexOf(ins.IntDayCount);
            int insPayFreq = payFreqs.IndexOf(ins.IntPayFreq);
            InstrumentDescr instr = new InstrumentDescr
            {
                endOfMonthPay = ins.EndOfMonthPay ? 1:0,
                instrumentClass = insClassNum,
                intDayCount = insDayCount,
                intPayFreq = insPayFreq,
                interestRate = ins.InterestRate
            };
            DateDescr maturityDate = new DateDescr
            {
                year = ins.MaturityDate.Year,
                month = ins.MaturityDate.Month,
                day = ins.MaturityDate.Day
            };
            DateDescr issueDate = new DateDescr
            {
                year = ins.IssueDate.Year,
                month = ins.IssueDate.Month,
                day = ins.IssueDate.Day
            };
            DateDescr firstPayDate = new DateDescr
            {
                year = ins.FirstPayDate.Year,
                month = ins.FirstPayDate.Month,
                day = ins.FirstPayDate.Day
            };
            DateDescr nextToLastPayDate = new DateDescr
            {
                year = ins.NextToLastPayDate.Year,
                month = ins.NextToLastPayDate.Month,
                day = ins.NextToLastPayDate.Day
            };
            instr.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(maturityDate, instr.maturityDate, false);
            instr.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instr.issueDate, false);
            instr.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instr.firstPayDate, false);
            instr.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(nextToLastPayDate, instr.nextToLastPayDate, false);

            return instr;
        }
        private CalculationsDescr makeCalculationsDescr(Calculations calcs)
        {
            CalculationsDescr calculations = new CalculationsDescr
            {
                isExCoup = calcs.IsExCoup ? 1:0,
                priceIn = calcs.PriceIn,
                yieldIn = calcs.YieldIn,
                serviceFee = calcs.ServiceFee,
                prepayModel = calcs.PrepayModel,
                interest = 0,
                interestDays = 0,
                convexity = 0,
                duration = 0,
                modifiedDuration = 0,
                priceOut = 0,
                pvbp = 0,
                yieldOut = 0,
                exCoupDays = calcs.IsExCoup ? 1:0,
                calculatePrice = calcs.CalculatePrice ? 1:0,
                yieldDayCount = dayCounts.IndexOf(calcs.YieldDayCount),
                yieldFreq = payFreqs.IndexOf(calcs.YieldFreq),
                yieldMethod = yieldMethods.IndexOf(calcs.YieldMethod)
            };
            DateDescr valueDate = new DateDescr
            {
                year = calcs.ValueDate.Year,
                month = calcs.ValueDate.Month,
                day = calcs.ValueDate.Day
            };
            DateDescr previousPayDate = new DateDescr
            {
                year = calcs.PreviousPayDate.Year,
                month = calcs.PreviousPayDate.Month,
                day = calcs.PreviousPayDate.Day
            };
            DateDescr nextPayDate = new DateDescr
            {
                year = calcs.NextPayDate.Year,
                month = calcs.NextPayDate.Month,
                day = calcs.NextPayDate.Day
            };
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.previousPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(previousPayDate, calculations.previousPayDate, false);
            calculations.nextPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(nextPayDate, calculations.nextPayDate, false);

            return calculations;
        }
        private Calculations makeCalculations(CalculationsDescr calcs)
        {
            IntPtr valPtr = Marshal.ReadIntPtr(calcs.valueDate);
            DateDescr valDate = new DateDescr();
            valDate = Marshal.PtrToStructure<DateDescr>(calcs.valueDate);
            IntPtr ppdPtr = Marshal.ReadIntPtr(calcs.previousPayDate);
            DateDescr ppdDate = new DateDescr();
            ppdDate = Marshal.PtrToStructure<DateDescr>(calcs.previousPayDate);
            IntPtr npdPtr = Marshal.ReadIntPtr(calcs.nextPayDate);
            DateDescr npdDate = new DateDescr();
            npdDate = Marshal.PtrToStructure<DateDescr>(calcs.nextPayDate);
            Calculations calculations = new Calculations
            {
                Interest = calcs.interest,
                InterestDays = calcs.interestDays,
                Duration = calcs.duration,
                ModifiedDuration = calcs.modifiedDuration,
                Convexity = calcs.convexity,
                ExCoupDays = calcs.exCoupDays,
                IsExCoup = (calcs.isExCoup == 1),
                PriceIn = calcs.priceIn,
                PriceOut = calcs.priceOut,
                YieldIn = calcs.yieldIn,
                YieldOut = calcs.yieldOut,
                Pvbp = calcs.pvbp,
                ServiceFee = calcs.serviceFee,
                PrepayModel = calcs.prepayModel,
                PreviousPayDate = new DateTime(ppdDate.year, ppdDate.month, ppdDate.day),
                NextPayDate = new DateTime(npdDate.year,npdDate.month,npdDate.day),
                ValueDate = new DateTime(valDate.year,valDate.month,valDate.day),
                CalculatePrice = (calcs.calculatePrice == 1)
            };

            return calculations;
        }

        public async Task<KeyValuePair<Instrument, Calculations>> GetDefaultDatesAsync(Instrument instrument, Calculations calculations)
        {
            KeyValuePair<Instrument, Calculations> result = await Task.Run(() =>
            {
                InstrumentDescr instr = makeInstrumentDescr(instrument);
                CalculationsDescr calcs = makeCalculationsDescr(calculations);
                int status = getDefaultDatesAndData(instr, calcs);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }
                Instrument newInstr = makeInstrument(instr);
                Calculations newCalcs = makeCalculations(calcs);

                return new KeyValuePair<Instrument, Calculations>(newInstr,newCalcs);
                })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
            return result;
    }


    public async Task<Instrument> GetDefaultDatesAsync(Instrument instrument, DateTime valueDate)
        {
            try
            {
                Instrument result = await Task.Run(() =>
                {
                    InstrumentDescr instr = makeInstrumentDescr(instrument);
                    DateDescr valDate = new DateDescr
                    {
                        year = valueDate.Year,
                        month = valueDate.Month,
                        day = valueDate.Day
                    };
                    int status = getDefaultDates(instr, valDate);
                    if (status != 0)
                    {
                        StringBuilder statusText = new StringBuilder(200);
                        int textSize;
                        status = getStatusText(status, statusText, out textSize);
                        throw new InvalidOperationException(statusText.ToString());
                    }
                    Instrument newInstr = makeInstrument(instr);
                    GC.KeepAlive(instr);
                    return newInstr;
                })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
                return result;
            }
            catch(InvalidOperationException)
            {
                throw;
            }
        }

 
        public async Task<List<string>> GetYieldMethodsAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> yieldmethods = new List<string>();
                int size;
                IntPtr ptr = getyieldmethods(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string name = Marshal.PtrToStringAnsi(strPtr);
                    yieldmethods.Add(name);
                    ptr += Marshal.SizeOf(typeof(IntPtr));
                }
                return yieldmethods;
            })
             .ConfigureAwait(false) //necessary on UI Thread
             ;
            return result;
        }

        public async Task<KeyValuePair<Instrument, Calculations>> GetInstrumentDefaultsAsync(Instrument instrument, Calculations calculations)
        {
            KeyValuePair<Instrument, Calculations> result = await Task.Run(() =>
            {
                InstrumentDescr instr = makeInstrumentDescr(instrument);
                CalculationsDescr calcs = makeCalculationsDescr(calculations);
                calcs.yieldDayCount = InstrumentDescr.date_last_day_count;
                calcs.yieldFreq = InstrumentDescr.freq_count;
                calcs.yieldMethod = CalculationsDescr.py_last_yield_meth;
                instr.holidayAdjust = (int)InstrumentDescr.DateAdjustRule.event_sched_no_holiday_adj;
                instr.intDayCount = InstrumentDescr.date_last_day_count;
                instr.intPayFreq = InstrumentDescr.freq_count;

                int status = getInstrumentDefaultsAndData(instr,calcs);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }
                Instrument newInstr = new Instrument
                {
                    EndOfMonthPay = (instr.endOfMonthPay == 1),
                    IntDayCount = dayCounts[instr.intDayCount],
                    IntPayFreq = payFreqs[instr.intPayFreq],
                    Class = new InstrumentClass
                    {
                        Name = classes[instr.instrumentClass]
                    }
                };
                Calculations newCalcs = new Calculations
                {
                    ExCoupDays = calcs.exCoupDays,
                    IsExCoup = (calcs.isExCoup == 1),
                    PrepayModel = calcs.prepayModel
                    ,YieldDayCount = calcs.yieldDayCount == InstrumentDescr.date_last_day_count ?
                dayCounts[0] : dayCounts[calcs.yieldDayCount],
                    YieldFreq = calcs.yieldFreq == InstrumentDescr.freq_count ?
                payFreqs[0] : payFreqs[calcs.yieldFreq],
                    YieldMethod = calcs.yieldMethod == CalculationsDescr.py_last_yield_meth ?
                   yieldMethods[0] : yieldMethods[calcs.yieldMethod]
                };

                return new KeyValuePair<Instrument, Calculations>(newInstr, newCalcs);
            })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
            return result;
        }
        public async Task<KeyValuePair<Instrument, Calculations>> CalculateAsync(Instrument instrument, Calculations calculations)
        {
            KeyValuePair<Instrument, Calculations> result = await Task.Run(() =>
            {
                InstrumentDescr instr = makeInstrumentDescr(instrument);
                CalculationsDescr calcs = makeCalculationsDescr(calculations);
                CashFlowsDescr cashFlows = new CashFlowsDescr();
                //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
                int dateAdjust = (int)InstrumentDescr.DateAdjustRule.event_sched_same_holiday_adj;
                //int status = calculate(instr, calcs);
                int status = calculateWithCashFlows(instr, calcs, cashFlows,dateAdjust);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }

                var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
                var cashFlowsOut = new List<CashFlowDescr>();
                var cashFlowOut = cashFlows.cashFlows;

                for (int i = 0; i < cashFlows.size; i++)
                {
                    cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                        typeof(CashFlowDescr)));
                    //cashFlowOut = (IntPtr)((int)cashFlowOut + structSize);
                    cashFlowOut = (IntPtr)(cashFlowOut.ToInt32() + structSize);
                }

                Instrument newInstr = makeInstrument(instr);
                Calculations newCalcs = makeCalculations(calcs);

                return new KeyValuePair<Instrument, Calculations>(newInstr, newCalcs);
            })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
            return result;
        }
    }
    enum tenor_rule
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
    public int adjustedYear;
    public int adjustedMonth;
    public int adjustedDay;
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
    static public readonly int date_last_day_count = 14;
    public static readonly int freq_count = 4;
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
        holidayAdjust = (int)DateAdjustRule.event_sched_no_holiday_adj;
        intDayCount = date_last_day_count;
        intPayFreq = freq_count;
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
    public static readonly int py_last_yield_meth = 15; /*{py_last_yield_meth marks the last symbol.}*/

    public CalculationsDescr()
    {
        yieldDayCount = InstrumentDescr.date_last_day_count;
        yieldFreq = InstrumentDescr.freq_count;
        yieldMethod = py_last_yield_meth;
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


