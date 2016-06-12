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

[assembly: Dependency(typeof(LibApi_Android))]

namespace FinSys.Mobile.Droid
{
    class LibApi_Android : ILibApi
    {
        [DllImport("libCLib", EntryPoint = "getclassdescriptions")]
        public static extern IntPtr getclassdescriptions(out int size);
        [DllImport("libCLib", EntryPoint = "iOSInfo")]
        public static extern string iOSInfo();

        public IntPtr getClassDescriptions(out int size)
        {
            return getclassdescriptions(out size);
        }
        public string getIOSInfo()
        {
            return iOSInfo();
        }
    }
}