using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Runtime.InteropServices;
using System.Text;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace CalcTests
{
    [TestClass]
    [DeploymentItem(DateTests.calcPath)]
    public class DateTests
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
        public static extern int getDefaultDates(InstrumentDescr instrument, DateDescr valueDate);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int getDefaultDatesAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr getyieldmethods(out int size);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int calculate(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        public static extern int getInstrumentDefaultsAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int getCashFlows(CashFlowsDescr cashFlows);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int getNewCashFlows(CashFlowsDescr cashFlows);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int tenor(DateDescr startDate, DateDescr endDate, int dayCountRule, out int tenor);
        [DllImport(calcPath, CallingConvention = CallingConvention.Cdecl)]
        private static extern int intCalc(DateDescr startDate, DateDescr endDate, int dayCountRule, out int days, out double dayCountFraction);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int forecast(DateDescr startDate, DateDescr endDate, int dayCountRule, int months, int days);

        private static DateDescr startDate_1 = new DateDescr { year = 2007, month = 12, day = 28 };
        private static DateDescr endDate_1 = new DateDescr { year = 2008, month = 2, day = 28 };
        private static DateDescr startDate_2 = new DateDescr { year = 2007, month = 12, day = 28 };
        private static DateDescr endDate_2 = new DateDescr { year = 2008, month = 2, day = 29 };
        private static DateDescr startDate_3 = new DateDescr { year = 2007, month = 2, day = 28 };
        private static DateDescr endDate_3 = new DateDescr { year = 2008, month = 2, day = 29 };
        private static DateDescr startDate_4 = new DateDescr { year = 2007, month = 10, day = 31 };
        private static DateDescr endDate_4 = new DateDescr { year = 2008, month = 11, day = 30 };
        private static DateDescr startDate_5 = new DateDescr { year = 2008, month = 2, day = 1 };
        private static DateDescr endDate_5 = new DateDescr { year = 2009, month = 5, day = 31 };


        public TestContext TestContext { get; set; }

        [TestMethod]
        public void IntCalcActAct_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
                (int)TestHelper.day_counts.date_act_actISDA_day_count,
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
            double dayCountFractionResult = 0.016942884946478;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
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
            double dayCountFractionResult = 0.016986301369863;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct360_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
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
            double dayCountFractionResult = 0.0172222222222222;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365A_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
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
            double dayCountFractionResult = 0.016986301369863;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365L_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
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
            double dayCountFractionResult = 0.0169398907103825;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcNL365_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
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
            double dayCountFractionResult = 0.016986301369863;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360ISDA_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
                (int)TestHelper.day_counts.date_30_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 60;
            double dayCountFractionResult = 0.0166666666666667;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30E360_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
                (int)TestHelper.day_counts.date_30e_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 60;
            double dayCountFractionResult = 0.0166666666666667;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30EPlus360_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
                (int)TestHelper.day_counts.date_30eplus_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 60;
            double dayCountFractionResult = 0.0166666666666667;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360German_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
                (int)TestHelper.day_counts.date_30_360german_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 60;
            double dayCountFractionResult = 0.0166666666666667;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360US_1()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_1,
                endDate_1,
                (int)TestHelper.day_counts.date_30_360US_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 60;
            double dayCountFractionResult = 0.0166666666666667;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }

        ////////////////////////////////////////////////////////////////////
        //Tests 2
        ////////////////////////////////////////////////////////////////////

        [TestMethod]
        public void IntCalcActAct_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
                (int)TestHelper.day_counts.date_act_actISDA_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 63;
            double dayCountFractionResult = 0.0172161089901939;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
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
            int intDaysResult = 63;
            double dayCountFractionResult = 0.0172602739726027;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct360_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
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
            int intDaysResult = 63;
            double dayCountFractionResult = 0.0175;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365A_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
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
            int intDaysResult = 63;
            double dayCountFractionResult = 0.0172131147540984;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365L_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
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
            int intDaysResult = 63;
            double dayCountFractionResult = 0.0172131147540984;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcNL365_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
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
            double dayCountFractionResult = 0.016986301369863;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360ISDA_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
                (int)TestHelper.day_counts.date_30_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 61;
            double dayCountFractionResult = 0.0169444444444444;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30E360_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
                (int)TestHelper.day_counts.date_30e_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 61;
            double dayCountFractionResult = 0.0169444444444444;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30EPlus360_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
                (int)TestHelper.day_counts.date_30eplus_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 61;
            double dayCountFractionResult = 0.0169444444444444;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360German_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
                (int)TestHelper.day_counts.date_30_360german_day_count,
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
            double dayCountFractionResult = 0.0172222222222222;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360US_2()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_2,
                endDate_2,
                (int)TestHelper.day_counts.date_30_360US_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 61;
            double dayCountFractionResult = 0.0169444444444444;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }


        ////////////////////////////////////////////////////////////////////
        //Tests 3
        ////////////////////////////////////////////////////////////////////

        [TestMethod]
        public void IntCalcActAct_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
                (int)TestHelper.day_counts.date_act_actISDA_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 366;
            double dayCountFractionResult = 0.10022980762033096;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
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
            int intDaysResult = 366;
            double dayCountFractionResult = 0.10027397260273974;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct360_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
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
            int intDaysResult = 366;
            double dayCountFractionResult = 0.10166666666666657;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365A_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
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
            int intDaysResult = 366;
            double dayCountFractionResult = 0.1;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365L_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
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
            int intDaysResult = 366;
            double dayCountFractionResult = 0.1;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcNL365_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
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
            int intDaysResult = 365;
            double dayCountFractionResult = 0.1;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360ISDA_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
                (int)TestHelper.day_counts.date_30_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 361;
            double dayCountFractionResult = 0.10027777777777769;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30E360_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
                (int)TestHelper.day_counts.date_30e_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 361;
            double dayCountFractionResult = 0.10027777777777769;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30EPlus360_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
                (int)TestHelper.day_counts.date_30eplus_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 361;
            double dayCountFractionResult = 0.10027777777777769;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360German_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
                (int)TestHelper.day_counts.date_30_360german_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 360;
            double dayCountFractionResult = 0.1;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360US_3()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_3,
                endDate_3,
                (int)TestHelper.day_counts.date_30_360US_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 360;
            double dayCountFractionResult = 0.10000000000000009;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        ////////////////////////////////////////////////////////////////////
        //Tests 4
        ////////////////////////////////////////////////////////////////////

        [TestMethod]
        public void IntCalcActAct_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
                (int)TestHelper.day_counts.date_act_actISDA_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 396;
            double dayCountFractionResult = .108243131970956;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
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
            int intDaysResult = 396;
            double dayCountFractionResult = .108493150684932;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct360_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
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
            int intDaysResult = 396;
            double dayCountFractionResult = 0.11;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365A_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
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
            int intDaysResult = 396;
            double dayCountFractionResult = .108196721311475;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365L_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
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
            int intDaysResult = 396;
            double dayCountFractionResult = .108196721311475;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcNL365_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
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
            int intDaysResult = 395;
            double dayCountFractionResult = .108219178082192;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360ISDA_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
                (int)TestHelper.day_counts.date_30_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 390;
            double dayCountFractionResult = .108333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30E360_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
                (int)TestHelper.day_counts.date_30e_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 390;
            double dayCountFractionResult = .108333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30EPlus360_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
                (int)TestHelper.day_counts.date_30eplus_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 390;
            double dayCountFractionResult = .108333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360German_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
                (int)TestHelper.day_counts.date_30_360german_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 390;
            double dayCountFractionResult = .108333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360US_4()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_4,
                endDate_4,
                (int)TestHelper.day_counts.date_30_360US_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 390;
            double dayCountFractionResult = .108333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }

        ////////////////////////////////////////////////////////////////////
        //Tests 5
        ////////////////////////////////////////////////////////////////////

        [TestMethod]
        public void IntCalcActAct_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
                (int)TestHelper.day_counts.date_act_actISDA_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 485;
            double dayCountFractionResult = .132625945055768;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
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
            int intDaysResult = 485;
            double dayCountFractionResult = .132876712328767;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct360_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
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
            int intDaysResult = 485;
            double dayCountFractionResult = .134722222222222;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365A_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
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
            int intDaysResult = 485;
            double dayCountFractionResult = .132513661202186;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcAct365L_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
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
            int intDaysResult = 485;
            double dayCountFractionResult = .132876712328767;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalcNL365_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
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
            int intDaysResult = 484;
            double dayCountFractionResult = .132602739726027;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360ISDA_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
                (int)TestHelper.day_counts.date_30_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 480;
            double dayCountFractionResult = .133333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30E360_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
                (int)TestHelper.day_counts.date_30e_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 479;
            double dayCountFractionResult = .133055555555556;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30EPlus360_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
                (int)TestHelper.day_counts.date_30eplus_360_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 480;
            double dayCountFractionResult = .133333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360German_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
                (int)TestHelper.day_counts.date_30_360german_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 479;
            double dayCountFractionResult = .133055555555556;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }
        [TestMethod]
        public void IntCalc30360US_5()
        {
            int days = 0;
            double dayCountFraction = 0;
            int status = intCalc(startDate_5,
                endDate_5,
                (int)TestHelper.day_counts.date_30_360US_day_count,
                out days,
                out dayCountFraction);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            int intDaysResult = 480;
            double dayCountFractionResult = .133333333333333;
            Assert.AreEqual(intDaysResult, days);
            Assert.IsTrue(Math.Abs(dayCountFractionResult - dayCountFraction) < .0000000001);

        }


        [TestMethod]
        public void Forecast_1()
        {
            int days = 0;
            int months = 6;
            DateDescr startDate = new DateDescr
            {
                year = 2010,
                month = 7,
                day = 15
            };
            DateDescr endDate = new DateDescr
            {
                year = 1900,
                month = 1,
                day = 1
            };
            int status = forecast(startDate,
              endDate,
            (int)TestHelper.tenor_rule.date_act_cal,
            months,
            days);
            if (status != 0)
            {
                StringBuilder statusText = new StringBuilder(200);
                int textSize;
                status = getStatusText(status, statusText, out textSize);
                throw new InvalidOperationException(statusText.ToString());
            }
            TestContext.WriteLine("Start Date: {0}.{1}.{2} ", startDate.year, startDate.month, startDate.day);
            TestContext.WriteLine("End Date: {0}.{1}.{2} ", endDate.year, endDate.month, endDate.day);

            Assert.AreEqual(15, endDate.day);
            Assert.AreEqual(1, endDate.month);
            Assert.AreEqual(2011, endDate.year);

        }



    }
}
