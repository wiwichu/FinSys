using AutoMapper;
using FinSysCore.Models;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSysCore.Services
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
        private static extern int getDefaultDatesAndData(InstrumentDescr instrument, CalculationsDescr calculations, DatesDescr holidays);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getyieldmethods(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int calculate(InstrumentDescr instrument, CalculationsDescr calculations, DatesDescr holidays);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getInstrumentDefaultsAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getCashFlows(CashFlowsDescr cashFlows, ref int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int calculateWithCashFlows(InstrumentDescr instrument, CalculationsDescr calculations, CashFlowsDescr cashFlows, 
            //int dateAdjustRule, 
            DatesDescr holidays);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getHolidayAdjust(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int forecast(DateDescr startDate, DateDescr endDate, int dayCountRule, int months, int days);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int priceCashFlows(CashFlowsDescr cashFlowsStruct,
            int yieldMth,
            int frequency,
            int dayCount,
            DateDescr valueDate,
            RateCurveDescr rateCurve,
            int interpolation);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromPrice(DateDescr valueDate, DateDescr maturityDate,
            double price, out double discount, out double mmYield, out double beYield);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromPriceWithCashFlows(DateDescr valueDate, DateDescr maturityDate,
            double price, out double discount, out double mmYield, out double beYield, CashFlowsDescr cashFlows, int dateAdjustRule, DatesDescr holidays);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromMMYield(DateDescr valueDate, DateDescr maturityDate,
           double mmYield, out double price, out double discount, out double beYield,
               out double duration, out double modifiedDuration, out double convexity, out double pvbp, out double pvbpConvexityAdjusted);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromDiscount(DateDescr valueDate, DateDescr maturityDate,
            double mmYield, out double price, out double discount, out double beYield);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromBEYield(DateDescr valueDate, DateDescr maturityDate,
            double beYield, out double price, out double mmYield, out double discount);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int intCalc(DateDescr startDate, DateDescr endDate, int dayCountRule, out int days, out double dayCountFraction);

        private List<string> classes = new List<string>();
        private List<string> dayCounts = new List<string>();
        private List<string> payFreqs = new List<string>();
        private List<string> yieldMethods = new List<string>();
        private List<string> holidayAdjusts = new List<string>();
        private List<string> interpolationMethods = new List<string>();
        private ILogger _logger;
        public CalculatorRepository(ILoggerFactory loggerFactory)
        {
            classes = GetInstrumentClassesAsync().Result;
            dayCounts = GetDayCountsAsync().Result;
            payFreqs = GetPayFreqsAsync().Result;
            yieldMethods = GetYieldMethodsAsync().Result;
            holidayAdjusts = GetHolidayAdjustAsync().Result;
            interpolationMethods = GetInterpolationMethodsAsync().Result;
            _logger = loggerFactory.CreateLogger<CalculatorRepository>();
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

        public async Task<List<string>> GetInstrumentClassesAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> instrumentClasses = new List<string>();
                int size;
                IntPtr ptr = getclassdescriptions(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    Console.WriteLine("i = " + i);
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string description = Marshal.PtrToStringAnsi(strPtr);
                    instrumentClasses.Add(description);
                    ptr += Marshal.SizeOf<IntPtr>();
                }
                return instrumentClasses;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }

        public async Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> instrumentsIn)
        {
            try
            {
                List<Instrument> result = await Task.Run(() =>
                {
                    List<Instrument> instruments = new List<Instrument>();
                    for (int i = 0; i < instrumentsIn.Count; i++)
                    {
                        Instrument ins = instrumentsIn[i];
                        InstrumentDescr instr = makeInstrumentDescr(ins);
                        //instr.holidayAdjust = (int)InstrumentDescr.DateAdjustRule.event_sched_no_holiday_adj;
                        instr.holidayAdjust = InstrumentDescr.noValue;
                        //instr.intDayCount = InstrumentDescr.date_last_day_count;
                        //instr.intPayFreq = InstrumentDescr.freq_count;
                        instr.intDayCount = InstrumentDescr.noValue;
                        instr.intPayFreq = InstrumentDescr.noValue;

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
            catch (Exception ex)
            {
                _logger.LogError("Could not get instrument defaults", ex);
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
                EndOfMonthPay = (instr.endOfMonthPay == 1),
                IntDayCount = dayCounts[instr.intDayCount],
                IntPayFreq = payFreqs[instr.intPayFreq],
                HolidayAdjust = holidayAdjusts[instr.holidayAdjust],
                Class = classes[instr.instrumentClass],
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
            int insClassNum = classes.IndexOf(ins.Class);
            int insDayCount = dayCounts.IndexOf(ins.IntDayCount);
            int insPayFreq = payFreqs.IndexOf(ins.IntPayFreq);
            int insHolidayAdjust = holidayAdjusts.IndexOf(ins.HolidayAdjust);
            InstrumentDescr instr = new InstrumentDescr
            {
                endOfMonthPay = ins.EndOfMonthPay ? 1 : 0,
                instrumentClass = insClassNum,
                intDayCount = insDayCount,
                intPayFreq = insPayFreq,
                interestRate = ins.InterestRate,
                holidayAdjust = insHolidayAdjust
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
                isExCoup = calcs.IsExCoup ? 1 : 0,
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
                exCoupDays = calcs.IsExCoup ? 1 : 0,
                calculatePrice = calcs.CalculatePrice ? 1 : 0,
                tradeflat = calcs.TradeFlat ? 1 : 0,
                yieldDayCount = dayCounts.IndexOf(calcs.YieldDayCount),
                yieldFreq = payFreqs.IndexOf(calcs.YieldFreq),
                yieldMethod = yieldMethods.IndexOf(calcs.YieldMethod),
                payDateAdj = holidayAdjusts.IndexOf(calcs.PayHolidayAdjust)
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
                PvbpConvexityAdjusted = calcs.pvbpConvexityAdjusted,
                ServiceFee = calcs.serviceFee,
                PrepayModel = calcs.prepayModel,
                PreviousPayDate = new DateTime(ppdDate.year, ppdDate.month, ppdDate.day),
                NextPayDate = new DateTime(npdDate.year, npdDate.month, npdDate.day),
                ValueDate = new DateTime(valDate.year, valDate.month, valDate.day),
                CalculatePrice = (calcs.calculatePrice == 1)
            };

            return calculations;
        }

        public async Task<KeyValuePair<Instrument, Calculations>> GetDefaultDatesAsync(Instrument instrument, Calculations calculations, IEnumerable<Holiday> holidays)
        {
            try
            { 
            KeyValuePair<Instrument, Calculations> result = await Task.Run(() =>
            {
                InstrumentDescr instr = makeInstrumentDescr(instrument);
                CalculationsDescr calcs = makeCalculationsDescr(calculations);
                calcs.yieldMethod = InstrumentDescr.noValue;
                calcs.yieldFreq = InstrumentDescr.noValue;
                calcs.yieldDayCount = InstrumentDescr.noValue;
                calcs.payDateAdj = InstrumentDescr.noValue;
                DatesDescr holidayList = makeDates(holidays);
                int status = getDefaultDatesAndData(instr, calcs, holidayList);
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
            catch (InvalidOperationException)
            {
                throw;
            }
            catch (Exception ex)
            {
                _logger.LogError("Could not get default dates", ex);
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

        public async Task<List<string>> GetInterpolationMethodsAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> interpolationmethods = new List<string>();
                interpolationmethods.Add("Linear");
                //interpolationmethods.Add("Continuous");
                return interpolationmethods;
            })
             .ConfigureAwait(false) //necessary on UI Thread
             ;
            return result;
        }


        public async Task<KeyValuePair<Instrument, Calculations>> GetInstrumentDefaultsAsync(Instrument instrument, Calculations calculations)
        {
            try
            { 
            KeyValuePair<Instrument, Calculations> result = await Task.Run(() =>
            {
                InstrumentDescr instr = makeInstrumentDescr(instrument);
                CalculationsDescr calcs = makeCalculationsDescr(calculations);
                calcs.yieldDayCount = InstrumentDescr.noValue;
                calcs.yieldFreq = InstrumentDescr.noValue;
                calcs.yieldMethod = InstrumentDescr.noValue;
                calcs.payDateAdj = InstrumentDescr.noValue;
                instr.holidayAdjust = InstrumentDescr.noValue;
                instr.intDayCount = InstrumentDescr.noValue;
                instr.intPayFreq = InstrumentDescr.noValue;

                int status = getInstrumentDefaultsAndData(instr, calcs);
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
                    HolidayAdjust = holidayAdjusts[instr.holidayAdjust],
                    Class = classes[instr.instrumentClass]
                };
                Calculations newCalcs = new Calculations
                {
                    ExCoupDays = calcs.exCoupDays,
                    IsExCoup = (calcs.isExCoup == 1),
                    PrepayModel = calcs.prepayModel
                   // ,YieldDayCount = calcs.yieldDayCount == InstrumentDescr.date_last_day_count ?
                   ,
                    YieldDayCount = calcs.yieldDayCount == InstrumentDescr.noValue ?
                    dayCounts[0] : dayCounts[calcs.yieldDayCount],
                    //YieldFreq = calcs.yieldFreq == InstrumentDescr.freq_count ?
                    YieldFreq = calcs.yieldFreq == InstrumentDescr.noValue ?
                    payFreqs[0] : payFreqs[calcs.yieldFreq],
                    //YieldMethod = calcs.yieldMethod == CalculationsDescr.py_last_yield_meth ?
                    YieldMethod = calcs.yieldMethod == InstrumentDescr.noValue ?
                    yieldMethods[0] : yieldMethods[calcs.yieldMethod]
                };

                return new KeyValuePair<Instrument, Calculations>(newInstr, newCalcs);
            })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
            return result;
            }
            catch (InvalidOperationException)
            {
                throw;
            }
            catch (Exception ex)
            {
                _logger.LogError("Could not get instrument defaults", ex);
                throw;

            }
        }
        public async Task<KeyValuePair<Instrument, Calculations>> CalculateAsync(Instrument instrument, Calculations calculations, IEnumerable<Holiday> holidays, bool includeCashflows)
        {
            try
            { 
            KeyValuePair<Instrument, Calculations> result = await Task.Run(() =>
            {
                InstrumentDescr instr = makeInstrumentDescr(instrument);
                CalculationsDescr calcs = makeCalculationsDescr(calculations);
                CashFlowsDescr cashFlows = new CashFlowsDescr();
                int dateAdjust = holidayAdjusts.IndexOf(calculations.PayHolidayAdjust);
                DatesDescr holidayList = makeDates(holidays);

                int status = 0;
                _logger.LogInformation($"Calculating {instrument.Class}");
                if (includeCashflows)
                {
                    status = calculateWithCashFlows(instr, calcs, cashFlows, 
                        //dateAdjust, 
                        holidayList);
                }
                else
                {
                    status = calculate(instr, calcs, holidayList);
                }
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }
                ////////////////

                var structSizeX = Marshal.SizeOf(typeof(CashFlowDescr));
                var cashFlowsOutX = new List<CashFlowDescr>();
                var cashFlowOutX = cashFlows.cashFlows;

                for (int i = 0; i < cashFlows.size; i++)
                {
                    cashFlowsOutX.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOutX,
                        typeof(CashFlowDescr)));
                    cashFlowOutX = (IntPtr)((int)cashFlowOutX + structSizeX);
                }

                ////////////////
                var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
                var cashFlowsOut = new List<CashFlowDescr>();
                var cashFlowOut = cashFlows.cashFlows;
                var cashFlowsResult = new List<CashFlow>();

                for (int i = 0; i < cashFlows.size; i++)
                {
                    CashFlowDescr cashFlowDescr = (CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                        typeof(CashFlowDescr));
                    if (
                          cashFlowDescr.adjustedDay == 0 ||
                          cashFlowDescr.adjustedMonth == 0 ||
                          cashFlowDescr.adjustedYear == 0 ||
                            cashFlowDescr.day == 0 ||
                            cashFlowDescr.month == 0 ||
                            cashFlowDescr.year == 0
                        )
                    {
                        continue;
                    }
                    CashFlow cf = new CashFlow
                    {
                        Amount = cashFlowDescr.amount,
                        AdjustedDate = new DateTime(cashFlowDescr.adjustedYear, cashFlowDescr.adjustedMonth, cashFlowDescr.adjustedDay),
                        PresentValue = cashFlowDescr.presentValue,
                        ScheduledDate = new DateTime(cashFlowDescr.year, cashFlowDescr.month, cashFlowDescr.day),
                        DiscountRate = cashFlowDescr.discountRate
                    };
                    cashFlowsResult.Add(cf);
                    cashFlowsOut.Add(cashFlowDescr);
                    //cashFlowOut = (IntPtr)((int)cashFlowOut + structSize);
                    cashFlowOut = (IntPtr)(cashFlowOut.ToInt32() + structSize);
                }

                Instrument newInstr = makeInstrument(instr);
                Calculations newCalcs = makeCalculations(calcs);
                newCalcs.Cashflows =
                cashFlowsResult
                .OrderBy((c) => c.ScheduledDate).GroupBy((c) => new
                {
                    c.ScheduledDate,
                    c.AdjustedDate
                }
                )
                .Select((cf) => new CashFlow
                {
                    Amount = cf.Sum(r => r.Amount),
                    ScheduledDate = cf.Key.ScheduledDate,
                    PresentValue = cf.Sum(r => r.PresentValue),
                    AdjustedDate = cf.Key.AdjustedDate,
                    DiscountRate = cf.Sum(r => r.DiscountRate)
                })
                .ToList();
                return new KeyValuePair<Instrument, Calculations>(newInstr, newCalcs);
            })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
            return result;
            }
            catch (InvalidOperationException)
            {
                throw;
            }
            catch (Exception ex)
            {
                _logger.LogError("Error calculating", ex);
                throw;

            }

        }

        public async Task<List<string>> GetHolidayAdjustAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> adjusts = new List<string>();
                int size;
                IntPtr ptr = getHolidayAdjust(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string name = Marshal.PtrToStringAnsi(strPtr);
                    adjusts.Add(name);
                    ptr += Marshal.SizeOf(typeof(IntPtr));
                }
                return adjusts;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }

        public async Task<DateTime> Forecast(DateTime startDate, DateTime endDate, int dayCountRule, int months, int days)
        {
            try
            { 
            DateTime result = await Task.Run(() =>
            {
                DateDescr dateIn = new DateDescr
                {
                    year = startDate.Year,
                    month = startDate.Month,
                    day = startDate.Day
                };
                DateDescr dateOut = new DateDescr
                {
                    year = startDate.Year,
                    month = startDate.Month,
                    day = startDate.Day
                };
                int status = forecast(dateIn, dateOut, dayCountRule, months, days);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }
                DateTime dateResult = new DateTime(dateOut.year, dateOut.month, dateOut.day);

                return dateResult;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
            }
            catch (InvalidOperationException)
            {
                throw;
            }
            catch (Exception ex)
            {
                _logger.LogError("Error forecasting", ex);
                throw;

            }
        }

        internal CashFlowsDescr makeCashFlows(List<CashFlow> cashFlows)
        {
            CashFlowsDescr cashFlowsDescr = new CashFlowsDescr();
            List<CashFlowDescr> cfList = cashFlows.Select((cf) =>
                new CashFlowDescr
                {
                    adjustedDay = cf.AdjustedDate.Day,
                    adjustedMonth = cf.AdjustedDate.Month,
                    adjustedYear = cf.AdjustedDate.Year,
                    amount = cf.Amount,
                    presentValue = cf.PresentValue,
                    day = cf.ScheduledDate.Day,
                    month = cf.ScheduledDate.Month,
                    year = cf.ScheduledDate.Year,
                    discountRate = cf.DiscountRate
                }
            ).ToList();
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
        internal DatesDescr makeDates(IEnumerable<Holiday> dates)
        {
            DatesDescr datesDescr = new DatesDescr();
            List<DateDescr> dList = dates.Select((d) =>
                new DateDescr
                {
                    day = d.HolidayDate.Day,
                    month = d.HolidayDate.Month,
                    year = d.HolidayDate.Year
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

        internal RateCurveDescr makeRateCurve(List<RateCurve> rateCurve)
        {
            RateCurveDescr rateCurveDescr = new RateCurveDescr();
            List<RateDescr> rcList = rateCurve.Select((rc) =>
                new RateDescr
                {
                    rate = rc.Rate,
                    day = rc.RateDate.Day,
                    month = rc.RateDate.Month,
                    year = rc.RateDate.Year
                }
            ).ToList();
            RateDescr[] rcArray = rcList.ToArray();
            rateCurveDescr.size = rcList.Count;
            rateCurveDescr.rates = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(RateDescr)) * rcArray.Length);
            IntPtr buffer = new IntPtr(rateCurveDescr.rates.ToInt64());
            for (int i = 0; i < rcArray.Length; i++)
            {
                Marshal.StructureToPtr(rcArray[i], buffer, true);
                buffer = new IntPtr(buffer.ToInt64() + Marshal.SizeOf(typeof(RateDescr)));
            }
            return rateCurveDescr;
        }
        public async Task<List<CashFlow>> PriceCashFlowsAsync(CashFlowPricing cfp )
        {
            try
            { 
            List<CashFlow> result = await Task.Run(() =>
            {
                List<RateCurve> rateCurve = cfp.RateCurve.ToList();
                if (!cfp.PriceFromCurve)
                {
                    rateCurve.Clear();
                }

                int ym = yieldMethods.IndexOf(cfp.YieldMethod);
                int yf = payFreqs.IndexOf(cfp.DiscountFrequency);
                int ydc = dayCounts.IndexOf(cfp.DayCount);
                int itp = interpolationMethods.IndexOf(cfp.Interpolation);
                List<CashFlow> cashFlowsResult = new List<CashFlow>();
                CashFlowsDescr cashFlowsDescr = makeCashFlows(cfp.CashFlows.ToList());
                RateCurveDescr rateCurveDescr = makeRateCurve(rateCurve);
                DateDescr vDate = new DateDescr
                {
                    year = cfp.ValueDate.Year,
                    month = cfp.ValueDate.Month,
                    day = cfp.ValueDate.Day
                };

                int status = priceCashFlows(cashFlowsDescr, ym, yf, ydc, vDate, rateCurveDescr, itp);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }
                var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
                for (int i = 0; i < cashFlowsDescr.size; i++)
                {
                    CashFlowDescr cashFlowDescr = (CashFlowDescr)Marshal.PtrToStructure(cashFlowsDescr.cashFlows,
                        typeof(CashFlowDescr));
                    CashFlow cf = new CashFlow
                    {
                        Amount = cashFlowDescr.amount,
                        AdjustedDate = new DateTime(cashFlowDescr.adjustedYear, cashFlowDescr.adjustedMonth, cashFlowDescr.adjustedDay),
                        PresentValue = cashFlowDescr.presentValue,
                        ScheduledDate = new DateTime(cashFlowDescr.year, cashFlowDescr.month, cashFlowDescr.day),
                        DiscountRate = cashFlowDescr.discountRate
                    };
                    cashFlowsResult.Add(cf);
                    //cashFlowsOut.Add(cashFlowDescr);
                    //cashFlowOut = (IntPtr)((int)cashFlowOut + structSize);
                    cashFlowsDescr.cashFlows = (IntPtr)(cashFlowsDescr.cashFlows.ToInt32() + structSize);
                }

                return cashFlowsResult;
            })
             .ConfigureAwait(false) //necessary on UI Thread
             ;
            return result;
            }
            catch (InvalidOperationException)
            {
                throw;
            }
            catch (Exception ex)
            {
                _logger.LogError("Error pricing cashflows", ex);
                throw;

            }

        }

        public async Task<USTBillResult> USTBillCalcAsync(USTBill usTbill)
        {
            try
            {
                USTBillResult result = await Task.Run(() =>
                {
                    DateDescr maturityDate = Mapper.Map<DateDescr>(usTbill.MaturityDate);
                    DateDescr valueDate = Mapper.Map<DateDescr>(usTbill.ValueDate);

                    double price = usTbill.CalcSource;
                    double discount = usTbill.CalcSource;
                    double mmYield = usTbill.CalcSource;
                    double beYield = usTbill.CalcSource;
                    double duration=0;
                    double modifiedDuration=0;
                    double convexity=0;
                    double pvbp=0;
                    double pvbpConvexityAdjusted=0;
                    DatesDescr holidays = new DatesDescr();
                    holidays.size = 0;
                    CashFlowsDescr cashFlows = null;
                    int dateAdjust = (int)InstrumentDescr.DateAdjustRule.event_sched_next_holiday_adj;
                    int status = 0;
                    switch (usTbill.CalcFrom)
                    {
                        case USTBill.CALCULATEFROM.BONDEQUIVALENT:
                            status = USTBillCalcFromBEYield(
                                valueDate,
                                maturityDate,
                                beYield,
                                 out price,
                               out mmYield,
                                out discount);
                            break;
                        case USTBill.CALCULATEFROM.DISCOUNT:
                            status = USTBillCalcFromDiscount(
                                valueDate,
                                maturityDate,
                                discount,
                                 out price,
                               out mmYield,
                                out beYield);
                            break;
                        case USTBill.CALCULATEFROM.MMYIELD:
                            status = USTBillCalcFromMMYield(
                                valueDate,
                                maturityDate,
                                mmYield,
                                 out price,
                               out discount,
                                out beYield,
                                out duration,
                                out modifiedDuration,
                                out convexity,
                                out pvbp,
                                out pvbpConvexityAdjusted);
                            break;
                        case USTBill.CALCULATEFROM.PRICE:
                            if (usTbill.IncludeCashFlows)
                            {
                                cashFlows = new CashFlowsDescr();
                                status = USTBillCalcFromPriceWithCashFlows(
                                    valueDate,
                                    maturityDate,
                                    price,
                                    out discount,
                                    out mmYield,
                                    out beYield, cashFlows, dateAdjust, holidays);
                            }
                            else
                            {
                                status = USTBillCalcFromPrice(
                                    valueDate,
                                    maturityDate,
                                    price,
                                    out discount,
                                    out mmYield,
                                    out beYield);
                            }
                            break;
                        default:
                            throw new ArgumentException("Invalid CalcFrom Argument.");
                    };
                    if (status != 0)
                    {
                        StringBuilder statusText = new StringBuilder(200);
                        int textSize;
                        status = getStatusText(status, statusText, out textSize);
                        throw new InvalidOperationException(statusText.ToString());
                    }
                    //Make sure volatility has been calculated
                    if (usTbill.CalcFrom != USTBill.CALCULATEFROM.MMYIELD)
                    {
                        status = USTBillCalcFromMMYield(
                            valueDate,
                            maturityDate,
                            mmYield,
                            out price,
                            out discount,
                            out beYield,
                            out duration,
                            out modifiedDuration,
                            out convexity,
                            out pvbp,
                            out pvbpConvexityAdjusted);
                    }
                    if (status != 0)
                    {
                        StringBuilder statusText = new StringBuilder(200);
                        int textSize;
                        status = getStatusText(status, statusText, out textSize);
                        throw new InvalidOperationException(statusText.ToString());
                    }
                    USTBillResult ustbResult = new USTBillResult();
                    ustbResult.BondEquivalent = beYield;
                    ustbResult.Convexity = convexity;
                    ustbResult.ConvexityAdjustedPvbp = pvbpConvexityAdjusted;
                    ustbResult.Discount = discount;
                    ustbResult.Duration = duration;
                    ustbResult.MMYield = mmYield;
                    ustbResult.ModifiedDuration = modifiedDuration;
                    ustbResult.Price = price;
                    ustbResult.Pvbp = pvbp;
                    //Make sure cashflows have been calculated
                    if (usTbill.IncludeCashFlows )
                    {
                        if (cashFlows == null)
                        {
                            cashFlows = new CashFlowsDescr();
                            status = USTBillCalcFromPriceWithCashFlows(
                                valueDate,
                                maturityDate,
                                price,
                                out discount,
                                out mmYield,
                                out beYield, cashFlows, dateAdjust, holidays);
                            if (status != 0)
                            {
                                StringBuilder statusText = new StringBuilder(200);
                                int textSize;
                                status = getStatusText(status, statusText, out textSize);
                                throw new InvalidOperationException(statusText.ToString());
                            }
                        }
                        var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
                        var cashFlowsOut = new List<CashFlowDescr>();
                        var cashFlowOut = cashFlows.cashFlows;
                        IList<CashFlow> newCf = new List<CashFlow>();
                        for (int i = 0; i < cashFlows.size; i++)
                        {
                            CashFlowDescr cfd = (CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                                typeof(CashFlowDescr));
                            cashFlowsOut.Add(cfd);
                            CashFlow cf = Mapper.Map<CashFlow>(cfd);
                            DateTime adt = new DateTime(cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
                            cf.AdjustedDate = adt;
                            DateTime sdt = new DateTime(cfd.year, cfd.month, cfd.day);
                            cf.ScheduledDate = sdt;
                            newCf.Add(cf);
                            cashFlowOut = (IntPtr)((int)cashFlowOut + structSize);
                        }
                        ustbResult.CashFlows = newCf;
                    }

                    return ustbResult;
                })
                .ConfigureAwait(false) //necessary on UI Thread
                ;
                return result;
            }
            catch (InvalidOperationException)
            {
                throw;
            }
            catch (Exception ex)
            {
                _logger.LogError("Error Calculating USTBill", ex);
                throw;
            }
        }

        public async Task<IEnumerable<DayCount>> IntCalcAsync(IEnumerable<DayCount> day_Counts)
        {
            IEnumerable<DayCount> result = await Task.Run(() =>
            {
                DayCount[] dcOut = new DayCount[day_Counts.Count()];
                int index = -1;
                bool hasError = false;
                foreach (DayCount dc in day_Counts)
                {
                    index++;
                    DateDescr startDate = new DateDescr();
                    startDate.year = dc.StartDate.Year;
                    startDate.month = dc.StartDate.Month;
                    startDate.day = dc.StartDate.Day;

                    DateDescr endDate = new DateDescr();
                    endDate.year = dc.EndDate.Year;
                    endDate.month = dc.EndDate.Month;
                    endDate.day = dc.EndDate.Day;
                    int days = 0;
                    double dayCountFraction = 0;
                    int status = intCalc(startDate,
                        endDate,
                        dayCounts.IndexOf(dc.Rule),
                        out days,
                        out dayCountFraction);
                    if (status != 0)
                    {
                        hasError = true;
                        StringBuilder statusText = new StringBuilder(200);
                        int textSize;
                        status = getStatusText(status, statusText, out textSize);
                        dc.Status = statusText.ToString();
                    }
                    else
                    {
                        dc.Days = days;
                        dc.Factor = dayCountFraction;
                    }
                    dcOut[index] = dc;
                }
                return dcOut.ToList();
            });
            return result;
        }

    }
    enum CurveInterpolation
    {
        Linear,
        Continuous
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
        , date_act_360cd_day_count
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
internal class RateDescr
{
    public int year;
    public int month;
    public int day;
    public double rate;
};
[StructLayout(LayoutKind.Sequential)]
internal class RateCurveDescr
{
    public IntPtr rates; //RateStruct Array
    public int size;
};

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
    public int payDateAdj;
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

