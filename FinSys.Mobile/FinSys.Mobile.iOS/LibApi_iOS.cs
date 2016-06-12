using FinSys.Mobile.iOS;
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

        //[DllImport("__Internal", EntryPoint = "iOSInfo")]
        //public static extern string iOSInfo();

        public IntPtr getClassDescriptions(out int size)
        {
            return getclassdescriptions(out size);
        }

        public IntPtr getDayCounts(out int size)
        {
            return getdaycounts(out size);
        }

        public string getIOSInfo()
        {
            return "";
            //return iOSInfo();
        }
    }
}
