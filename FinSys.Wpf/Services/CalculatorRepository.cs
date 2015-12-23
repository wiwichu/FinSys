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
            List<Model.InstrumentClass> result = await Task.Run(() =>
            {
                List<Model.InstrumentClass> instrumentClasses = new List<Model.InstrumentClass>();
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
                    PrepayModel = calcs.prepayModel,
                    YieldDayCount = dayCounts[calcs.yieldDayCount],
                    YieldFreq = payFreqs[calcs.yieldFreq],
                    YieldMethod = yieldMethods[calcs.yieldMethod]
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
                int status = calculate(instr, calcs);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
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
    [StructLayout(LayoutKind.Sequential)]
    internal class InstrumentDescr
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
    internal class CalculationsDescr
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
    internal class DateDescr
    {
        public int year;
        public int month;
        public int day;
    };
}
