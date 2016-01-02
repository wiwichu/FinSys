using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CalcTests
{
    [TestClass]
    [DeploymentItem("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll")]
    public class DateTests
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
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getCashFlows(CashFlowsDescr cashFlows);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getNewCashFlows(CashFlowsDescr cashFlows);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int tenor(DateDescr startDate, DateDescr endDate, int dayCountRule, out int tenor);
        [DllImport("C:/Users/Patrick/Documents/Visual Studio 2015/Projects/FinSys/Calc/Debug/calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int intCalc(DateDescr startDate, DateDescr endDate, int dayCountRule, out int days, out double dayCountFraction);
        public TestContext TestContext { get; set; }

        [TestMethod]
        public void IntCalcActAct_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            DateDescr startDate = new DateDescr { year = 2007, month = 12, day = 28 };
            DateDescr endDate = new DateDescr { year = 2008, month = 2, day = 28 };
            int status = intCalc(startDate,
                endDate,
                (int)TestHelper.day_counts.date_act_act_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 62;
            double dayCountFractionResult = 0.16942884946478;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            DateDescr startDate = new DateDescr { year = 2007, month = 12, day = 28 };
            DateDescr endDate = new DateDescr { year = 2008, month = 2, day = 28 };
            int status = intCalc(startDate,
                endDate,
                (int)TestHelper.day_counts.date_act_365_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 62;
            double dayCountFractionResult = 0.16986301369863;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct360_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            DateDescr startDate = new DateDescr { year = 2007, month = 12, day = 28 };
            DateDescr endDate = new DateDescr { year = 2008, month = 2, day = 28 };
            int status = intCalc(startDate,
                endDate,
                (int)TestHelper.day_counts.date_act_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 62;
            double dayCountFractionResult = 0.172222222222222;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }

        [TestMethod]
        public void IntCalcAct365A_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            DateDescr startDate = new DateDescr { year = 2007, month = 12, day = 28 };
            DateDescr endDate = new DateDescr { year = 2008, month = 2, day = 28 };
            int status = intCalc(startDate,
                endDate,
                (int)TestHelper.day_counts.date_act_365A_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 62;
            double dayCountFractionResult = 0.16986301369863;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365L_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            DateDescr startDate = new DateDescr { year = 2007, month = 12, day = 28 };
            DateDescr endDate = new DateDescr { year = 2008, month = 2, day = 28 };
            int status = intCalc(startDate,
                endDate,
                (int)TestHelper.day_counts.date_act_365L_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 62;
            double dayCountFractionResult = 0.169398907103825;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcNL365_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            DateDescr startDate = new DateDescr { year = 2007, month = 12, day = 28 };
            DateDescr endDate = new DateDescr { year = 2008, month = 2, day = 28 };
            int status = intCalc(startDate,
                endDate,
                (int)TestHelper.day_counts.date_NL_365_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 62;
            double dayCountFractionResult = 0.16986301369863;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }



    }
}
