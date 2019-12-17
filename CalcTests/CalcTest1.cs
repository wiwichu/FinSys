﻿using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Diagnostics;
using System.Collections.Concurrent;

namespace CalcTests
{
    [TestClass]
    [DeploymentItem(CalcTest1.calcPath)]
    public class CalcTest1
    {


        const string calcPath = "C:/FinsyscoreCode/FinSysCore/bin/Debug/netcoreapp3.0/calc.dll";
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getclassdescriptions(out int size);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getdaycounts(out int size);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getpayfreqs(out int size);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int getStatusText(int status, StringBuilder text, out int textSize);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int getInstrumentDefaults(InstrumentDescr instrument);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int getDefaultDatesAndData(InstrumentDescr instrument, CalculationsDescr calculations, DatesDescr holidays);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getyieldmethods(out int size);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int calculate(InstrumentDescr instrument, CalculationsDescr calculations, DatesDescr holidays);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int getInstrumentDefaultsAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int getCashFlows(CashFlowsDescr cashFlows, int dateAdjustRule);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int getNewCashFlows(CashFlowsDescr cashFlows, int dateAdjustRule);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int tenor(DateDescr startDate, DateDescr endDate, int dayCountRule, out int tenor);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int intCalc(DateDescr startDate, DateDescr endDate, int dayCountRule,out int days,out double dayCountFraction);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int calculateWithCashFlows(InstrumentDescr instrument, CalculationsDescr calculations, CashFlowsDescr cashFlows, 
            //int dateAdjustRule, 
            DatesDescr holidays);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getHolidayAdjust(out int size);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int forecast(DateDescr startDate, DateDescr endDate, int dayCountRule, int months, int days);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromPrice(DateDescr valueDate, DateDescr maturityDate,
            double price, out double discount, out double mmYield, out double beYield);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromPriceWithCashFlows(DateDescr valueDate, DateDescr maturityDate,
            double price, out double discount, out double mmYield, out double beYield, CashFlowsDescr cashFlows, int dateAdjustRule, DatesDescr holidays);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromMMYield(DateDescr valueDate, DateDescr maturityDate,
           double mmYield, out double price, out double discount,  out double beYield,
               out double duration, out double modifiedDuration,out double convexity, out double pvbp, out double pvbpConvexityAdjusted);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromDiscount(DateDescr valueDate, DateDescr maturityDate,
            double mmYield, out double price, out double discount, out double beYield);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int USTBillCalcFromBEYield(DateDescr valueDate, DateDescr maturityDate,
            double beYield,out  double price, out double mmYield, out double discount);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int priceCashFlows(CashFlowsDescr cashFlowsStruct,
            int yieldMth,
            int frequency,
            int dayCount,
            DateDescr valueDate,
            RateCurveDescr rateCurve,
            int interpolation);
        public TestContext TestContext { get; set; }
        [TestMethod]
        public void GetCashFlows_1()
        {
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            int startYear = 2000;
            int startMonth = 6;
            int startDay = 1;
            int startAmount = 100;
            List<CashFlowDescr> cfList = new List<CashFlowDescr>();
            TestContext.WriteLine("BEFORE CALL:");
            TestContext.WriteLine("");
            for (int i = 1;i<=10;i++)
            {
                CashFlowDescr cashFlow = new CashFlowDescr();
                cashFlow.year = startYear + i;
                cashFlow.month = startMonth;
                cashFlow.day = startDay;
                cashFlow.amount = (startAmount * i) + i;

                cfList.Add(cashFlow);

                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3}",cashFlow.year,cashFlow.month,cashFlow.day,cashFlow.amount);
                cashFlows.size = cfList.Count;

            }
            CashFlowDescr[] cfArray = cfList.ToArray();
            cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) * cfArray.Length);
            IntPtr buffer = new IntPtr(cashFlows.cashFlows.ToInt64());
            for (int i = 0; i < cfArray.Length; i++)
            {
                Marshal.StructureToPtr(cfArray[i], buffer, true);
                buffer = new IntPtr(buffer.ToInt64() + Marshal.SizeOf(typeof(CashFlowDescr)));
            }
            int dateAdjust = (int)TestHelper.DateAdjustRule.event_sched_same_holiday_adj;
            int status = getCashFlows(cashFlows,dateAdjust);
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
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3}", cfd.year, cfd.month, cfd.day, cfd.amount);
            }
        }
        [TestMethod]
        public void MemTest()
        {
            //for (int i =0;i<10000;i++)
            //{
            //    GetCashFlows_1();
            //    System.Threading.Thread.Sleep(10);
            //    //Task.Delay(100).Wait();
            //}
        }
        [TestMethod]
        public void GetNewCashFlows_1()
        {
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            int dateAdjust = (int)TestHelper.DateAdjustRule.event_sched_same_holiday_adj;
            int status = getNewCashFlows(cashFlows,dateAdjust);
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
                //cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3}", cfd.year, cfd.month, cfd.day, cfd.amount);
            }
        }


        [TestMethod]
        public void TBillDiscountFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 12, day = 26 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 09, day = 26 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mmdisc_yield_meth;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0161;
            calculations.priceIn = 0.99593;
            calculations.calculatePrice = 0;
            status = calculate(instrument, calculations,holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result- calculations.yieldOut)<.00001);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillDiscountFromPrice_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mmdisc_yield_meth;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0497;
            calculations.priceIn = 0.97501194;
            calculations.calculatePrice = 0;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .00001);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }

        [TestMethod]
        public void TBillPriceFromDiscount_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 12, day = 26 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 09, day = 26 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mmdisc_yield_meth;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.99593;
            calculations.yieldIn = 0.01610;
            calculations.calculatePrice = 1;
            status = calculate(instrument, calculations,holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000001);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillPriceFromDiscount_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;


            DateDescr matDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mmdisc_yield_meth;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.97501194;
            calculations.yieldIn = 0.0497;
            calculations.calculatePrice = 1;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .00000001);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillBEFromPriceLE182Days_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.045;
            calculations.priceIn = 0.978172;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_annually;
            calculations.calculatePrice = 0;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillPriceFromBELE182Days_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;


            DateDescr matDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.978172;
            calculations.yieldIn = 0.045;

            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_annually;
            calculations.calculatePrice = 1;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillBEFromPriceGT182Days_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2008, month = 12, day = 24 };
            DateDescr valueDate = new DateDescr { year = 2007, month = 12, day = 27 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0394;
            calculations.priceIn = 0.96202;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mm_yield_meth;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_NL_365_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.calculatePrice = 0;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .00002);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillPriceFromBEGT182Days_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2008, month = 12, day = 24 };
            DateDescr valueDate = new DateDescr { year = 2007, month = 12, day = 27 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.96202;
            calculations.yieldIn = 0.0394;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mm_yield_meth;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_NL_365_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.calculatePrice = 1;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .00002);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillMMYFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mmdisc_yield_meth;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0510;
            calculations.priceIn = 0.97501194;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mm_yield_meth;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0001);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillMMYFromPrice_Tester()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2017, month = 3, day = 16 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 3, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mmdisc_yield_meth;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0510;
            calculations.priceIn = 0.97;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mm_yield_meth;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            //Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0001);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBillPriceFromMMY_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mmdisc_yield_meth;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.97501194;
            calculations.yieldIn = 0.0510;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mm_yield_meth;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .00003);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BundAct365AnnualPriceFromYMoos_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_bund_class_desc;

            DateDescr matDate = new DateDescr { year = 2013, month = 11, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2009, month = 2, day = 18 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.039487;
            calculations.yieldIn = 0.06;
            calculations.calculatePrice = 1;
            instrument.intDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_moos_yield_meth;
            instrument.interestRate = 0.07;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BundAct365AnnualYMoosFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_bund_class_desc;

            DateDescr matDate = new DateDescr { year = 2013, month = 11, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2009, month = 2, day = 18 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.06;
            calculations.priceIn = 1.039487;
            calculations.calculatePrice = 0;
            instrument.intDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_moos_yield_meth;
            instrument.interestRate = 0.07;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BundAct365AnnualPriceFromYISMA_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_bund_class_desc;

            DateDescr matDate = new DateDescr { year = 2013, month = 11, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2009, month = 2, day = 18 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.039830;
            calculations.yieldIn = 0.06;
            calculations.calculatePrice = 1;
            instrument.intDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.07;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BundAct365AnnualYISMAFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_bund_class_desc;

            DateDescr matDate = new DateDescr { year = 2013, month = 11, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2009, month = 2, day = 18 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.06;
            calculations.priceIn = 1.039830;
            calculations.calculatePrice = 0;
            instrument.intDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.07;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void Bund30360SemiPriceFromYISMA_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_bund_class_desc;

            DateDescr matDate = new DateDescr { year = 2013, month = 11, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2010, month = 11, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.027086;
            calculations.yieldIn = 0.06;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.07;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void Bund30360SemiYISMAFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_bund_class_desc;

            DateDescr matDate = new DateDescr { year = 2013, month = 11, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2010, month = 11, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.06;
            calculations.priceIn = 1.027086;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.07;
            holidays.size = 0;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }


        [TestMethod]
        public void TBondPriceFromYtm_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1997, month = 1, day = 20 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.048106;
            calculations.yieldIn = 0.04;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            holidays.size = 0;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000003);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKGilt_OldMethod_PriceFromYtm_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_gilt_class_desc;
            instrument.intDayCount = (int)TestHelper.day_counts.date_act_365_day_count;

            DateDescr matDate = new DateDescr { year = 1987, month = 2, day = 10 };
            DateDescr valueDate = new DateDescr { year = 1986, month = 7, day = 2 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.04425;
            calculations.yieldIn = 0.09462;
            calculations.calculatePrice = 1;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.1025;
            holidays.size = 0;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - (calculations.priceOut + calculations.interest)) < .000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKGilt_OldMethod_YtmFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_gilt_class_desc;
            instrument.intDayCount = (int)TestHelper.day_counts.date_act_365_day_count;

            DateDescr matDate = new DateDescr { year = 1987, month = 2, day = 10 };
            DateDescr valueDate = new DateDescr { year = 1986, month = 7, day = 2 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.09462;
            calculations.priceIn = 1.0043746;
            calculations.calculatePrice = 0;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.1025;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1997, month = 1, day = 20 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.04;
            calculations.priceIn = 1.048106;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000003);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        //////////////////////////
        [TestMethod]
        public void TBondPriceFromYtm_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1997, month = 1, day = 20 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .999951;
            calculations.yieldIn = 0.05;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000003);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromPrice_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1997, month = 1, day = 20 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.05;
            calculations.priceIn = 0.999951;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000003);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        ////////////////////////
        [TestMethod]
        public void TBondPriceFromYtm_3()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1997, month = 1, day = 20 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.954384;
            calculations.yieldIn = 0.06;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromPrice_3()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1997, month = 1, day = 20 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.06;
            calculations.priceIn = 0.954384;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000003);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromPriceShortFirstCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2021, month = 3, day = 1 };
            DateDescr valueDate = new DateDescr { year = 2008, month = 11, day = 11 };
            DateDescr issueDate = new DateDescr { year = 2008, month = 10, day = 15 };
            DateDescr firstPayDate = new DateDescr { year = 2009, month = 3, day = 1 };
            //DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0625;
            calculations.priceIn = 1.1359771747;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0785;
            //instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondPriceFromYtmShortFirstCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2021, month = 3, day = 1 };
            DateDescr valueDate = new DateDescr { year = 2008, month = 11, day = 11 };
            DateDescr issueDate = new DateDescr { year = 2008, month = 10, day = 15 };
            DateDescr firstPayDate = new DateDescr { year = 2009, month = 3, day = 1 };
            //DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.13597717474079;
            calculations.yieldIn = 0.0625;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0785;
            //instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondPriceFromYtmOddFirstAndLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2001, month = 10, day = 1 };
            DateDescr valueDate = new DateDescr { year = 2000, month = 1, day = 12 };
            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2000, month = 1, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2000, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.04;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondFlatPriceFromYtmOddFirstAndLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2001, month = 10, day = 1 };
            DateDescr valueDate = new DateDescr { year = 2000, month = 1, day = 12 };
            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2000, month = 1, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2000, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.958172634;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            calculations.tradeflat = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.04;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void Gilt_Old_Holidays_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_gilt_class_desc;

            DateDescr matDate = new DateDescr { year = 1987, month = 2, day = 24 };
            DateDescr valueDate = new DateDescr { year = 1986, month = 7, day = 3 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);


            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            instrument.intDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_365_day_count;
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            List<DateTime> dates = new List<DateTime>();
            dates.Add(new DateTime(1986, 8, 25));
            DatesDescr holidays = TestHelper.makeDates(dates);
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .0763802;
            calculations.priceIn = .968125;
            calculations.calculatePrice = 0;
            instrument.interestRate = 0.025;
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            calculations.payDateAdj = (int)TestHelper.DateAdjustRule.event_sched_next_holiday_adj;
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
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
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000005);
            Assert.AreEqual(cashFlowsOut[0].adjustedDay, 26);
            Assert.AreEqual(cashFlowsOut[0].adjustedMonth, 8);
            Assert.AreEqual(cashFlowsOut[0].adjustedYear, 1986);
            //GC.KeepAlive(instrument);
            //GC.KeepAlive(calculations);
            //GC.KeepAlive(cashFlows);

        }
        [TestMethod]
        public void Cashflow_Pricing_Parallel_1()
        {
            //Use parallel when:
            //calc > 1
            //cf > 150 && !true yield

            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;
            //instrument.instrumentClass = (int)TestHelper.instr_class_descs.inst
            //cf > 50 && true yieldr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2060, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 5, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 10 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2020, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_same_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            calculations.payDateAdj = instrument.holidayAdjust;
            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOutSer = new ConcurrentBag<CashFlowDescr>();
            var cashFlowsOut = new ConcurrentBag<CashFlowDescr>();

            IEnumerable< int > calcs = new List<int>(new int[300]);
            Func<int, bool> calcsPredSer =
                (c) =>
                {
                    CashFlowsDescr cashFlows = new CashFlowsDescr();
                    status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
                    //status = calculate(instrument, calculations, holidays);
                    if (status != 0)
                    {
                        StringBuilder statusText = new StringBuilder(200);
                        int textSize;
                        status = getStatusText(status, statusText, out textSize);
                        throw new InvalidOperationException(statusText.ToString());
                    }

                    var cashFlowOut = cashFlows.cashFlows;

                    for (int i = 0; i < cashFlows.size; i++)
                    {
                        cashFlowsOutSer.Add((CashFlowDescr)Marshal.PtrToStructure(new IntPtr(cashFlowOut.ToInt64()),
                            typeof(CashFlowDescr)));
                        cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
                    }

                    return true;
                };
            Func<int, bool> calcsPred =
                (c) =>
                {
                    CashFlowsDescr cashFlows = new CashFlowsDescr();
                    status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
                    //status = calculate(instrument, calculations, holidays);
                    if (status != 0)
                    {
                        StringBuilder statusText = new StringBuilder(200);
                        int textSize;
                        status = getStatusText(status, statusText, out textSize);
                        throw new InvalidOperationException(statusText.ToString());
                    }

                    var cashFlowOut = cashFlows.cashFlows;

                    for (int i = 0; i < cashFlows.size; i++)
                    {
                        cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                            typeof(CashFlowDescr)));
                        cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
                    }

                    return true;
                };
            Stopwatch sw = new Stopwatch();
            sw.Start();
            calcs.All(calcsPredSer);
            sw.Stop();
            TestContext.WriteLine("");
            TestContext.WriteLine("Serial Calc: {0}", sw.Elapsed);
            TestContext.WriteLine("");
            sw.Reset();
            sw.Start();
            calcs.AsParallel().All(calcsPred);
            sw.Stop();
            TestContext.WriteLine("");
            TestContext.WriteLine("Parallel Calc: {0}", sw.Elapsed);
            TestContext.WriteLine("");
            sw.Reset();

            int ym = calculations.yieldMethod;
            int yf = calculations.yieldFreq;
            int ydc = calculations.yieldDayCount;
            int itp = 0;
            DateDescr vDate = new DateDescr
            {
                year = valueDate.year,
                month = valueDate.month,
                day = valueDate.day
            };
            RateCurveDescr rateCurveDescr = new RateCurveDescr
            {
                size = 0,
                rates = IntPtr.Zero
            };
            CashFlowsDescr cashFlowsDescrSer = TestHelper.makeCashFlows(cashFlowsOutSer.ToList());
            IList<CashFlowsDescr> cashFlowsDescrsSer = new List<CashFlowsDescr>();
            cashFlowsOutSer.All((c) =>
            {
                List<CashFlowDescr> cfdl = new List<CashFlowDescr>();
                cfdl.Add(c);
                CashFlowsDescr cfds = TestHelper.makeCashFlows(cfdl);
                cashFlowsDescrsSer.Add(cfds);
                return true;
            });
            CashFlowsDescr cashFlowsDescr = TestHelper.makeCashFlows(cashFlowsOut.ToList());
            IList<CashFlowsDescr> cashFlowsDescrs = new List<CashFlowsDescr>();
            cashFlowsOut.All((c) =>
            {
                List<CashFlowDescr> cfdl = new List<CashFlowDescr>();
                cfdl.Add(c);
                CashFlowsDescr cfds = TestHelper.makeCashFlows(cfdl);
                cashFlowsDescrs.Add(cfds);
                return true;
            });
            TestContext.WriteLine("");
            TestContext.WriteLine("Total CashFlows: {0}", cashFlowsDescrsSer.Count());
            TestContext.WriteLine("");
            Func<CashFlowsDescr, bool> cfsPredSer =
            (c) =>
            {
                status = priceCashFlows(c, ym, yf, ydc, vDate, rateCurveDescr, itp);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }

                return true;
            };
            sw.Start();
            status = priceCashFlows(cashFlowsDescr, ym, yf, ydc, vDate, rateCurveDescr, itp);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            sw.Stop();
            TestContext.WriteLine("");
            TestContext.WriteLine("Single Price Call: {0}", sw.Elapsed);
            TestContext.WriteLine("");
            sw.Reset();


            sw.Start();
            cashFlowsDescrsSer.All(cfsPredSer);
            sw.Stop();
            TestContext.WriteLine("");
            TestContext.WriteLine("Serial CF: {0}", sw.Elapsed);
            TestContext.WriteLine("");
            sw.Reset();

            List<CashFlowDescr> serCf = new List<CashFlowDescr>();
            List<CashFlowsDescr> serCfd = new List<CashFlowsDescr>(cashFlowsDescrsSer);
            sw.Start();
            cashFlowsDescrs.AsParallel().ForAll((c) =>
            {
                status = priceCashFlows(c, ym, yf, ydc, vDate, rateCurveDescr, itp);
                if (status != 0)
                {
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    status = getStatusText(status, statusText, out textSize);
                    throw new InvalidOperationException(statusText.ToString());
                }
            });
            sw.Stop();
            TestContext.WriteLine("");
            TestContext.WriteLine("Parallel CF: {0}", sw.Elapsed);
            TestContext.WriteLine("");
            sw.Reset();

            TestContext.WriteLine("");
            TestContext.WriteLine("Prepare Serial CashFlows Collectiom.");
            TestContext.WriteLine("");
            serCfd.All((c) =>
            {
                for (int i = 0; i < c.size; i++)
                {
                    serCf.Add((CashFlowDescr)Marshal.PtrToStructure(c.cashFlows,
                        typeof(CashFlowDescr)));
                    c.cashFlows = new IntPtr(c.cashFlows.ToInt64() + structSize);
                }

                return true;
            });

            TestContext.WriteLine("");
            TestContext.WriteLine("Prepare Parallel CashFlows Collectiom.");
            TestContext.WriteLine("");
            List<CashFlowDescr> parCf = new List<CashFlowDescr>();
            List<CashFlowsDescr> parCfd = new List<CashFlowsDescr>(cashFlowsDescrs);
            parCfd.All((c) =>
            {
                for (int i = 0; i < c.size; i++)
                {
                    parCf.Add((CashFlowDescr)Marshal.PtrToStructure(c.cashFlows,
                        typeof(CashFlowDescr)));
                    c.cashFlows = new IntPtr(c.cashFlows.ToInt64() + structSize);
                }

                return true;
            });
            TestContext.WriteLine("");
            TestContext.WriteLine($"Serial Count { serCf.Count()} ");
            TestContext.WriteLine($"Parallel Count { parCf.Count()} ");
            TestContext.WriteLine("");

            for (int i=0;i<serCf.Count();i++)
            {
                if (Math.Abs(serCf[i].presentValue - parCf[i].presentValue) >= .0000000005)
                {
                    TestContext.WriteLine("");
                    TestContext.WriteLine($"Cashflow mismatch. Count { i} Serial: {serCf[i].presentValue}  Parallel: {parCf[i].presentValue} ");
                    TestContext.WriteLine("");

                }
                //Assert.IsTrue(Math.Abs(serCf[i].presentValue - parCf[i].presentValue) < .0005);
            }

            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }

        [TestMethod]
        public void UKCD_DateSync_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2060, month = 07, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 7, day = 31 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_same_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            instrument.endOfMonthPay = 0;
            
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            calculations.priceIn = 0.95;
            calculations.calculatePrice = 0;
            instrument.interestRate = 0.04;
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            calculations.payDateAdj = instrument.holidayAdjust;
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKCD_Cashflows_NextDayHolidayAdjust_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 5, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 10 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_next_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 16);
            Assert.AreEqual(cashFlowsOut[0].month, 5);
            Assert.AreEqual(cashFlowsOut[0].year, 2016);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKCD_Cashflows_NextPrevDayHolidayAdjust_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 5, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 10 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_np_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 16);
            Assert.AreEqual(cashFlowsOut[0].month, 5);
            Assert.AreEqual(cashFlowsOut[0].year, 2016);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKCD_Cashflows_PrevDayHolidayAdjust_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 5, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 10 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_prev_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 13);
            Assert.AreEqual(cashFlowsOut[0].month, 5);
            Assert.AreEqual(cashFlowsOut[0].year, 2016);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKCD_Cashflows_PrevNextDayHolidayAdjust_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 5, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 10 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_pn_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 13);
            Assert.AreEqual(cashFlowsOut[0].month, 5);
            Assert.AreEqual(cashFlowsOut[0].year, 2016);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKCD_Cashflows_NextPrevDayHolidayAdjust_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 4, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 30 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 30 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 30 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_np_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows,  holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 29);
            Assert.AreEqual(cashFlowsOut[0].month, 4);
            Assert.AreEqual(cashFlowsOut[0].year, 2016);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKCD_Cashflows_PrevNextDayHolidayAdjust_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 4, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 1 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_pn_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 2);
            Assert.AreEqual(cashFlowsOut[0].month, 5);
            Assert.AreEqual(cashFlowsOut[0].year, 2016);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void UKCD_Cashflows_NoHolidayAdjust_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 5, day = 10 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 10 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_same_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            calculations.payDateAdj = (int)TestHelper.DateAdjustRule.event_sched_next_holiday_adj;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 15);
            Assert.AreEqual(cashFlowsOut[0].month, 5);
            Assert.AreEqual(cashFlowsOut[0].year, 2016);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void USCD_PriceFromYield_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_uscd_class_desc;

            DateDescr matDate = new DateDescr { year = 1987, month = 10, day = 8 };
            DateDescr valueDate = new DateDescr { year = 1986, month = 8, day = 24 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            //instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_same_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.033052;
            calculations.yieldIn = 0.0775;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.08;
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.IsTrue(Math.Abs(result - (calculations.priceOut + calculations.interest)) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void USCD_YieldFromPrice_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_uscd_class_desc;

            DateDescr matDate = new DateDescr { year = 1987, month = 10, day = 8 };
            DateDescr valueDate = new DateDescr { year = 1986, month = 8, day = 24 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            //instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_same_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0775;
            calculations.priceIn = 1.002385;
            calculations.calculatePrice = 0;
            instrument.interestRate = 0.08;
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            calculations.payDateAdj = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculateWithCashFlows(instrument, calculations, cashFlows, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }


        [TestMethod]
        public void UKCD_NoCashflows_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ukcd_class_desc;

            DateDescr matDate = new DateDescr { year = 2025, month = 10, day = 7 };
            DateDescr valueDate = new DateDescr { year = 2015, month = 7, day = 12 };
            DateDescr issueDate = new DateDescr { year = 2014, month = 1, day = 10 };
            DateDescr firstPayDate = new DateDescr { year = 2015, month = 12, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2024, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);

            instrument.intPayFreq = (int)TestHelper.frequency.frequency_monthly;
            instrument.holidayAdjust = (int)TestHelper.DateAdjustRule.event_sched_next_holiday_adj;

            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .957;
            calculations.yieldIn = 0.0659;
            calculations.calculatePrice = 1;
            instrument.interestRate = 0.04;
            //calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            // instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            //instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            //calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            //cashFlows.cashFlows = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(CashFlowDescr)) );
            int dateAdjust = instrument.holidayAdjust;
            //int status = calculate(instr, calcs);
            status = calculate(instrument, calculations,holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }


        [TestMethod]
        public void TBondYtmFromPriceOddFirstAndLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2001, month = 10, day = 1 };
            DateDescr valueDate = new DateDescr { year = 2000, month = 1, day = 12 };
            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2000, month = 1, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2000, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .0659;
            calculations.priceIn = .9570;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.04;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromFlatPriceOddFirstAndLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2001, month = 10, day = 1 };
            DateDescr valueDate = new DateDescr { year = 2000, month = 1, day = 12 };
            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2000, month = 1, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2000, month = 4, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .0659;
            calculations.priceIn = 0.9582;
            calculations.calculatePrice = 0;
            calculations.tradeflat = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.04;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }

        [TestMethod]
        public void TBondPriceFromYtmLongFirstCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2014, month = 10, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2007, month = 5, day = 1 };
            DateDescr issueDate = new DateDescr { year = 2007, month = 3, day = 24 };
            DateDescr firstPayDate = new DateDescr { year = 2007, month = 10, day = 31 };
            //DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .927942029404091;
            calculations.yieldIn = 0.01;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0;
            //instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondPriceFromYtmLongFirstCoupon_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2005, month = 3, day = 1 };
            DateDescr valueDate = new DateDescr { year = 1992, month = 11, day = 11 };
            DateDescr issueDate = new DateDescr { year = 1992, month = 6, day = 15 };
            DateDescr firstPayDate = new DateDescr { year = 1993, month = 3, day = 1 };
            //DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.12478106;
            calculations.yieldIn = 0.0775;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0935;
            //instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromPriceLongFirstCoupon_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2005, month = 3, day = 1 };
            DateDescr valueDate = new DateDescr { year = 1992, month = 11, day = 11 };
            DateDescr issueDate = new DateDescr { year = 1992, month = 6, day = 15 };
            DateDescr firstPayDate = new DateDescr { year = 1993, month = 3, day = 1 };
            //DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0775;
            calculations.priceIn = 1.12478106;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0935;
            //instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondInterestLongFirstCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2016, month = 4, day = 1 };
            DateDescr valueDate = new DateDescr { year = 1993, month = 2, day = 1 };
            DateDescr issueDate = new DateDescr { year = 1992, month = 7, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 1993, month = 4, day = 1 };
            //DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 4.4196;
            int interestResult = 215;
            calculations.yieldIn = 0.075;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 7.5;
            //instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.interest) < .00005);
            Assert.AreEqual(interestResult, calculations.interestDays);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromPriceLongFirstCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2014, month = 10, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2007, month = 5, day = 1 };
            DateDescr issueDate = new DateDescr { year = 2007, month = 3, day = 24 };
            DateDescr firstPayDate = new DateDescr { year = 2007, month = 10, day = 31 };
            //DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.01;
            calculations.priceIn = .927942029404091;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0;
            //instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BondPriceFromYtmLongLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 3, day = 20 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 10 };
//            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
 
            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.9883315770;
            calculations.yieldIn = 0.055;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.05;
            DateDescr firstPayDate = new DateDescr { year = 2004, month = 3, day = 10 };
            DateDescr preLastPayDate = new DateDescr { year = 2008, month = 9, day = 10 };
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BondFlatPriceFromYtmLongLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 3, day = 20 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 10 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.9883315770;
            calculations.tradeflat = 1;
            calculations.yieldIn = 0.055;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.05;
            DateDescr firstPayDate = new DateDescr { year = 2004, month = 3, day = 10 };
            DateDescr preLastPayDate = new DateDescr { year = 2008, month = 9, day = 10 };
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void EuroSimpleYtmFromPriceLongLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 1993, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1993, month = 2, day = 7 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30e_360_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30e_360_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0405;
            calculations.priceIn = 0.99878286;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ytm_simp_yield_meth;
            instrument.interestRate = 0.0375;
            DateDescr firstPayDate = new DateDescr { year = 1991, month = 10, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 1992, month = 10, day = 15 };
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void EuroPriceFromSimpleYtmLongLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 1993, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 1993, month = 2, day = 7 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30e_360_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30e_360_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.99878286;
            calculations.yieldIn = 0.0405;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ytm_simp_yield_meth;
            instrument.interestRate = 0.0375;
            DateDescr firstPayDate = new DateDescr { year = 1991, month = 10, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 1992, month = 10, day = 15 };
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }

        [TestMethod]
        public void BondYtmFromPriceLongLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 3, day = 20 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 10 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.055;
            calculations.priceIn = 0.9883315770;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.05;
            DateDescr firstPayDate = new DateDescr { year = 2004, month = 3, day = 10 };
            DateDescr preLastPayDate = new DateDescr { year = 2008, month = 9, day = 10 };
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BondPriceFromYtmLongLastCoupon_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 3, day = 20 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 11 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2004, month = 3, day = 10 };
            DateDescr preLastPayDate = new DateDescr { year = 2008, month = 9, day = 10 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.9883416556;
            calculations.yieldIn = 0.055;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.05;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BondPriceFromYtmLongLastCoupon_3()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2008, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2008, month = 2, day = 7 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2006, month = 10, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2007, month = 10, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = .99882445698485;
            calculations.yieldIn = 0.0405;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.0375;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BondYtmFromPriceLongLastCoupon_3()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2008, month = 6, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2008, month = 2, day = 7 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2006, month = 10, day = 15 };
            DateDescr preLastPayDate = new DateDescr { year = 2007, month = 10, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0405;
            calculations.priceIn = .99882445698485;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.0375;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void BondYtmFromPriceLongLastCoupon_2()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 3, day = 20 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 11 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2004, month = 3, day = 10 };
            DateDescr preLastPayDate = new DateDescr { year = 2008, month = 9, day = 10 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.055;
            calculations.priceIn = 0.9883416556;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
            instrument.interestRate = 0.05;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .000000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondPriceFromYtmShortLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 6, day = 10 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 10 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2004, month = 3, day = 10 };
            DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 10 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_act_act_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_act_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.98747213511112;
            calculations.yieldIn = 0.055;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void TBondYtmFromPriceShortLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 6, day = 10 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 10 };
            //            DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
            DateDescr firstPayDate = new DateDescr { year = 2004, month = 3, day = 10 };
            DateDescr preLastPayDate = new DateDescr { year = 2009, month = 3, day = 10 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            instrument.intDayCount = (int)TestHelper.day_counts.date_act_act_day_count;
            instrument.intPayFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_act_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.055;
            calculations.priceIn = 0.98747213511112;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.05;
            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.yieldOut) < .0000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }


        [TestMethod]
        public void DurationModifiedDuration_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2017, month = 12, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2008, month = 1, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double durationResult = 7.45;
            double modDurationResult = 7.16;
            calculations.yieldIn = 0.08;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.06;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(durationResult - calculations.duration) < .005);
            Assert.IsTrue(Math.Abs(modDurationResult - calculations.modifiedDuration) < .005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void DurationConvexity_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2014, month = 1, day = 15 };
            DateDescr valueDate = new DateDescr { year = 2008, month = 1, day = 15 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double durationResult = 5.007;
            double modDurationResult = 4.77;
            double convexityResult = 27.72;
            calculations.yieldIn = 0.10;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.061;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(durationResult - calculations.duration) < .0005);
            Assert.IsTrue(Math.Abs(modDurationResult - calculations.modifiedDuration) < .005);
            Assert.IsTrue(Math.Abs(convexityResult - calculations.convexity) < .005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void DurationConvexityPvbp_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2022, month = 1, day = 5 };
            DateDescr valueDate = new DateDescr { year = 2016, month = 1, day = 5 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            calculations.valueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            int status = getInstrumentDefaultsAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }

            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            status = getDefaultDatesAndData(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double durationResult = 4.88;
            double modDurationResult = 4.69;
            double convexityResult = 27.23;
            double pvbpResult = .04693;
            double pvbpConvResult = .04556;
            calculations.yieldIn = 0.08;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.08;
            status = calculate(instrument, calculations, holidays);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(durationResult - calculations.duration) < .0005);
            Assert.IsTrue(Math.Abs(modDurationResult - calculations.modifiedDuration) < .005);
            Assert.IsTrue(Math.Abs(convexityResult - calculations.convexity) < .005);
            Assert.IsTrue(Math.Abs(pvbpResult - calculations.pvbp) < .000005);
            Assert.IsTrue(Math.Abs(pvbpConvResult - calculations.pvbpConvexityAdjusted) < .000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        [TestMethod]
        public void QuickUSTBillCalcFromPrice_1()
        {
            DateDescr maturityDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            double beResult = 0.0517;
            double discountResult = 0.0497;
            double mmyResult = 0.0510;
            double price = 0.97501194;
            double discount = 0;
            double mmYield = 0;
            double beYield = 0;
            DatesDescr holidays = new DatesDescr();
            holidays.size = 0;
            CashFlowsDescr cashFlows = new CashFlowsDescr();
            int dateAdjust = (int)TestHelper.DateAdjustRule.event_sched_next_holiday_adj;
            int status = USTBillCalcFromPriceWithCashFlows(
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
            TestContext.WriteLine("");

            var structSize = Marshal.SizeOf(typeof(CashFlowDescr));
            var cashFlowsOut = new List<CashFlowDescr>();
            var cashFlowOut = cashFlows.cashFlows;

            for (int i = 0; i < cashFlows.size; i++)
            {
                cashFlowsOut.Add((CashFlowDescr)Marshal.PtrToStructure(cashFlowOut,
                    typeof(CashFlowDescr)));
                cashFlowOut = new IntPtr(cashFlowOut.ToInt64() + structSize);
            }
            TestContext.WriteLine("");
            TestContext.WriteLine("After CALL:");
            TestContext.WriteLine("");

            foreach (CashFlowDescr cfd in cashFlowsOut)
            {
                TestContext.WriteLine("Date: {0}.{1}.{2} Amount: {3} AdjDate: {4}.{5}.{6} ", cfd.year, cfd.month, cfd.day, cfd.amount, cfd.adjustedYear, cfd.adjustedMonth, cfd.adjustedDay);
            }
            Assert.AreEqual(cashFlowsOut[0].day, 31);
            Assert.AreEqual(cashFlowsOut[0].month, 3);
            Assert.AreEqual(cashFlowsOut[0].year, 2003);

            Assert.IsTrue(Math.Abs(beResult - beYield) < .00005);
            Assert.IsTrue(Math.Abs(mmyResult - mmYield) < .00005);
            Assert.IsTrue(Math.Abs(discountResult - discount) < .00005);
        }

        [TestMethod]
        public void QuickUSTBillCalcFromPrice_2()
        {
            DateDescr maturityDate = new DateDescr { year = 2008, month = 12, day = 24 };
            DateDescr valueDate = new DateDescr { year = 2007, month = 12, day = 27 };

            double beResult = 0.0394;
            double price = 0.96202;
            double discount = 0;
            double mmYield = 0;
            double beYield = 0;
            int status = USTBillCalcFromPrice(
                valueDate, 
                maturityDate,
                price, 
                out discount, 
                out mmYield, 
                out beYield);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(beResult - beYield) < .00005);
        }
        [TestMethod]
        public void QuickUSTBillCalcFromMMYield_1()
        {
            DateDescr maturityDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            double beResult = 0.0517;
            double discountResult = 0.0497;
            double mmYield = 0.0510;
            double priceResult = 0.97501194;
            double discount = 0;
            double beYield = 0;
            double price = 0;
            double duration;
            double modifiedDuration;
            double convexity;
            double pvbp;
            double pvbpConvexityAdjusted;

            int status = USTBillCalcFromMMYield(
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
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(beResult - beYield) < .00005);
            double priceDiff = priceResult - price;
            Assert.IsTrue(Math.Abs(priceResult - price) < .00005);
            Assert.IsTrue(Math.Abs(discountResult - discount) < .00005);
        }
        [TestMethod]
        public void QuickUSTBillCalcFromBEYield_1()
        {
            DateDescr maturityDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            double beYield = 0.0517;
            double discountResult = 0.0497;
            double mmYieldResult = 0.0510;
            double priceResult = 0.97501194;
            double discount = 0;
            double mmYield = 0;
            double price = 0;
            int status = USTBillCalcFromBEYield(
                valueDate,
                maturityDate,
                beYield,
                 out price,
               out mmYield,
                out discount);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(mmYieldResult - mmYield) < .00005);
            double priceDiff = priceResult - price;
            Assert.IsTrue(Math.Abs(priceResult - price) < .00005);
            Assert.IsTrue(Math.Abs(discountResult - discount) < .00005);
        }
        [TestMethod]
        public void QuickUSTBillCalcFromBEYield_2()
        {
            DateDescr maturityDate = new DateDescr { year = 2008, month = 12, day = 24 };
            DateDescr valueDate = new DateDescr { year = 2007, month = 12, day = 27 };

            double beYield = 0.0394;
            double priceResult = 0.96202;
            double discount = 0;
            double mmYield = 0;
            double price = 0;
            int status = USTBillCalcFromBEYield(
                valueDate,
                maturityDate,
                beYield,
                 out price,
               out mmYield,
                out discount);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(priceResult - price) < .00005);
        }
        [TestMethod]
        public void QuickUSTBillCalcFromDiscount_1()
        {
            DateDescr maturityDate = new DateDescr { year = 2003, month = 3, day = 31 };
            DateDescr valueDate = new DateDescr { year = 2002, month = 10, day = 1 };

            double beResult = 0.0517;
            double discount = 0.0497;
            double mmYieldResult = 0.0510;
            double priceResult = 0.97501194;
            double beYield = 0;
            double mmYield = 0;
            double price = 0;
            int status = USTBillCalcFromDiscount(
                valueDate,
                maturityDate,
                discount,
                 out price,
               out mmYield,
                out beYield);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(beResult - beYield) < .00005);
            double priceDiff = priceResult - price;
            Assert.IsTrue(Math.Abs(priceResult - price) < .00005);
            Assert.IsTrue(Math.Abs(mmYieldResult - mmYield) < .00005);
        }


    }
}
