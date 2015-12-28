using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Runtime.InteropServices;
using System.Text;

namespace CalcTests
{
    [TestClass]
    [DeploymentItem("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll")]
    public class CalcTest1
    {
        static string calcPath = "C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll";
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getclassdescriptions(out int size);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getdaycounts(out int size);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getpayfreqs(out int size);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getStatusText(int status, StringBuilder text, out int textSize);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getInstrumentDefaults(InstrumentDescr instrument);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getDefaultDates(InstrumentDescr instrument, DateDescr valueDate);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getDefaultDatesAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getyieldmethods(out int size);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int calculate(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern int getInstrumentDefaultsAndData(InstrumentDescr instrument, CalculationsDescr calculations);


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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0517;
            calculations.priceIn = 0.97501194;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mm_yield_meth;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_act_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.calculatePrice = 0;
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.97501194;
            calculations.yieldIn = 0.0517;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_mm_yield_meth;
            calculations.yieldDayCount = (int)TestHelper.day_counts.date_act_act_day_count;
            calculations.yieldFreq = (int)TestHelper.frequency.frequency_semiannually;
            calculations.calculatePrice = 1;
            status = calculate(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000007);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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

            DateDescr matDate = new DateDescr { year = 2005, month = 3, day = 1 };
            DateDescr valueDate = new DateDescr { year = 1992, month = 11, day = 11 };
            DateDescr issueDate = new DateDescr { year = 1992, month = 10, day = 15 };
            DateDescr firstPayDate = new DateDescr { year = 1993, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
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
            status = getDefaultDatesAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0625;
            calculations.priceIn = 1.136;
            calculations.calculatePrice = 0;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0785;
            status = calculate(instrument, calculations);
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
        public void TBondPriceFromYtmShortFirstCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_ustbo_class_desc;

            DateDescr matDate = new DateDescr { year = 2005, month = 3, day = 1 };
            DateDescr valueDate = new DateDescr { year = 1992, month = 11, day = 11 };
            DateDescr issueDate = new DateDescr { year = 1992, month = 10, day = 15 };
            DateDescr firstPayDate = new DateDescr { year = 1993, month = 3, day = 1 };

            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
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
            status = getDefaultDatesAndData(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 1.136;
            calculations.yieldIn = 0.0625;
            calculations.calculatePrice = 1;
            calculations.yieldMethod = (int)TestHelper.yield_method.py_ustr_yield_meth;
            instrument.interestRate = 0.0785;
            status = calculate(instrument, calculations);
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
        public void BondPriceFromYtmLongLastCoupon_1()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

            DateDescr matDate = new DateDescr { year = 2009, month = 3, day = 20 };
            DateDescr valueDate = new DateDescr { year = 2006, month = 9, day = 10 };
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

            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
//            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
 //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
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

            instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
            //            instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            //           Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
            instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
            Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
            status = getDefaultDatesAndData(instrument, calculations);
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
            status = calculate(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            Assert.IsTrue(Math.Abs(result - calculations.priceOut) < .000005);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
        /*
                [TestMethod]
                public void BondPriceFromYtmShortFirstCouponAndLongLastCoupon_1()
                {
                    InstrumentDescr instrument = new InstrumentDescr();
                    CalculationsDescr calculations = new CalculationsDescr();
                    instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_euro_class_desc;

                    DateDescr matDate = new DateDescr { year = 2001, month = 10, day = 1 };
                    DateDescr valueDate = new DateDescr { year = 2000, month = 1, day = 12 };
                    DateDescr issueDate = new DateDescr { year = 2000, month = 1, day = 1 };
                    DateDescr firstPayDate = new DateDescr { year = 2000, month = 1, day = 15 };
                    DateDescr preLastPayDate = new DateDescr { year = 2000, month = 4, day = 15 };

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
                    instrument.intPayFreq = (int)TestHelper.frequency.frequency_quarterly;
                    calculations.yieldDayCount = (int)TestHelper.day_counts.date_30_360US_day_count;
                    calculations.yieldFreq = (int)TestHelper.frequency.frequency_quarterly;

                    instrument.nextToLastPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
                    Marshal.StructureToPtr(preLastPayDate, instrument.nextToLastPayDate, false);
                    instrument.issueDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
                    Marshal.StructureToPtr(issueDate, instrument.issueDate, false);
                    instrument.firstPayDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
                    Marshal.StructureToPtr(firstPayDate, instrument.firstPayDate, false);
                    Marshal.StructureToPtr(matDate, instrument.maturityDate, false);
                    Marshal.StructureToPtr(valueDate, calculations.valueDate, false);
                    status = getDefaultDatesAndData(instrument, calculations);
                    if (status != 0)
                    {
                        StringBuilder statusText = new StringBuilder(200);
                        int textSize;
                        status = getStatusText(status, statusText, out textSize);
                        throw new InvalidOperationException(statusText.ToString());
                    }
                    double result = 0.957;
                    calculations.yieldIn = 0.0659;
                    calculations.calculatePrice = 1;
                    calculations.yieldMethod = (int)TestHelper.yield_method.py_aibd_yield_meth;
                    instrument.interestRate = 0.04;
                    status = calculate(instrument, calculations);
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
                */
    }
}
