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
        public void TBillDiscountFromPrice()
        {
            InstrumentDescr instrument = new InstrumentDescr();
            CalculationsDescr calculations = new CalculationsDescr();
            instrument.instrumentClass = (int)TestHelper.instr_class_descs.instr_usdsc_class_desc;

            DateDescr matDate = new DateDescr { year = 2002, month = 12, day = 26 };
            instrument.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
            Marshal.StructureToPtr(matDate, instrument.maturityDate, false);

            calculations.priceIn = 0.99593;
            DateDescr valueDate = new DateDescr { year = 2002, month = 09, day = 26 };
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
            calculations.calculatePrice = 0;
            status = calculate(instrument, calculations);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            double result = 0.0161;
            Assert.IsTrue(Math.Abs(result- calculations.yieldOut)<.00001);
            GC.KeepAlive(instrument);
            GC.KeepAlive(calculations);

        }
    }
}
