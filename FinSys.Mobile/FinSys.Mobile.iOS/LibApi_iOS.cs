using FinSys.Mobile.iOS;
using FinSys.Mobile.Model;
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
using System.Text;
using Xamarin.Forms;

[assembly: Dependency(typeof(LibApi_iOS))]

namespace FinSys.Mobile.iOS
{
    class LibApi_iOS : ILibApi
    {
        [DllImport("__Internal", EntryPoint = "getclassdescriptions")]
        public static extern IntPtr getclassdescriptions(out int size);
        [DllImport("__Internal", EntryPoint = "getdaycounts")]
        public static extern IntPtr getdaycounts(out int size);
        [DllImport("__Internal", EntryPoint = "getpayfreqs")]
        private static extern IntPtr getpayfreqs(out int size);
        [DllImport("__Internal", EntryPoint = "getStatusText")]
        private static extern int getStatusText(int status, StringBuilder text, out int textSize);
        [DllImport("__Internal", EntryPoint = "getInstrumentDefaults")]
        private static extern int getInstrumentDefaults(InstrumentDescr instrument);
        [DllImport("__Internal", EntryPoint = "getDefaultDatesAndData")]
        private static extern int getDefaultDatesAndData(InstrumentDescr instrument, CalculationsDescr calculations, DatesDescr holidays);
        [DllImport("__Internal", EntryPoint = "getyieldmethods")]
        private static extern IntPtr getyieldmethods(out int size);
        [DllImport("__Internal", EntryPoint = "calculate")]
        private static extern int calculate(InstrumentDescr instrument, CalculationsDescr calculations, DatesDescr holidays);
        [DllImport("__Internal", EntryPoint = "getInstrumentDefaultsAndData")]
        private static extern int getInstrumentDefaultsAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("__Internal", EntryPoint = "getCashFlows")]
        private static extern int getCashFlows(CashFlowsDescr cashFlows, ref int size);
        [DllImport("__Internal", EntryPoint = "calculateWithCashFlows")]
        private static extern int calculateWithCashFlows(InstrumentDescr instrument, CalculationsDescr calculations, CashFlowsDescr cashFlows, int dateAdjustRule, DatesDescr holidays);
        [DllImport("__Internal", EntryPoint = "getHolidayAdjust")]
        private static extern IntPtr getHolidayAdjust(out int size);
        [DllImport("__Internal", EntryPoint = "forecast")]
        private static extern int forecast(DateDescr startDate, DateDescr endDate, int dayCountRule, int months, int days);
        [DllImport("__Internal", EntryPoint = "priceCashFlows")]
        private static extern int priceCashFlows(CashFlowsDescr cashFlowsStruct,
            int yieldMth,
            int frequency,
            int dayCount,
            DateDescr valueDate,
            RateCurveDescr rateCurve,
            int interpolation);

        //[DllImport("__Internal", EntryPoint = "iOSInfo")]
        //public static extern string iOSInfo();

        public IntPtr GetClassDescriptions(out int size)
        {
            return getclassdescriptions(out size);
        }

        public IntPtr GetDayCounts(out int size)
        {
            return getdaycounts(out size);
        }
        public int GetInstrumentDefaultsAndData(Instrument instrument, Calculations calculations)
        {
            InstrumentDescr instr = null;
            CalculationsDescr calcs = null;
            return getInstrumentDefaultsAndData(instr, calcs);
        }

        public string getIOSInfo()
        {
            return "";
            //return iOSInfo();
        }
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

}

