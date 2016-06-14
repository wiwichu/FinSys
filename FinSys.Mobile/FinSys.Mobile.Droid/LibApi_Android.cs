using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Android.App;
using Android.Content;
using Android.OS;
using Android.Runtime;
using Android.Views;
using Android.Widget;
using System.Runtime.InteropServices;
using Xamarin.Forms;
using FinSys.Mobile.Droid;
using FinSys.Mobile.Model;

[assembly: Dependency(typeof(LibApi_Android))]

namespace FinSys.Mobile.Droid
{
    class LibApi_Android : ILibApi
    {
        [DllImport("libCLib", EntryPoint = "getclassdescriptions")]
        public static extern IntPtr getclassdescriptions(out int size);
        [DllImport("libCLib", EntryPoint = "getdaycounts")]
        public static extern IntPtr getdaycounts(out int size);
        [DllImport("libCLib", EntryPoint = "getInstrumentDefaultsAndData")]
        private static extern int getInstrumentDefaultsAndData(InstrumentDescr instrument, CalculationsDescr calculations);
        [DllImport("libCLib", EntryPoint = "iOSInfo")]
        public static extern string iOSInfo();

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
            return iOSInfo();
        }
    }
}