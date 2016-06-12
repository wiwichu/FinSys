using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using Xamarin.Forms;

namespace FinSys.Mobile.Services
{
    public class CalculatorRepository : ICalculatorRepository
    {
        private List<string> classes = new List<string>();
        private List<string> dayCounts = new List<string>();
        public CalculatorRepository()
        {
            classes = GetInstrumentClassesAsync().Result;
            classes = GetDayCountsAsync().Result;
        }

        public async Task<List<string>> GetDayCountsAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> daycounts = new List<string>();
                int size;
                IntPtr ptr = DependencyService.Get<ILibApi>().getDayCounts(out size);
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
                try
                {
                    //var info = DependencyService.Get<ILibApi>().getIOSInfo();
                    int size;
                    IntPtr ptr = DependencyService.Get<ILibApi>().getClassDescriptions(out size);
                    IntPtr strPtr;
                    for (int i = 0; i < size; i++)
                    {
                        strPtr = Marshal.ReadIntPtr(ptr);
                        string description = Marshal.PtrToStringAnsi(strPtr);
                        instrumentClasses.Add(description);
                        ptr += Marshal.SizeOf(typeof(IntPtr));
                    }
                }
                catch (Exception ex)
                {
                }
                return instrumentClasses;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
            //List<string> result = await Task.Run(() =>
            //{
            //    if (classes.Count > 0)
            //    {
            //        return classes;
            //    }
            //    List<string> instrumentClasses = new List<string>()
            //    {
            //        "German Bund",
            //        "Japan Gov",
            //        "UK Gilt",
            //        "UK CD",
            //        "UK Discount",
            //        "US CD",
            //        "US Discount",
            //        "US TBOND",
            //        "Commercial Paper",
            //        "Finanzierungsschatz",
            //        "U-Schatz",
            //        "Eurobond",
            //        "MBS"
            //    };
            //    return instrumentClasses;
            //})
            //.ConfigureAwait(false) //necessary on UI Thread
            //;
            //return result;
        }

    }

}

