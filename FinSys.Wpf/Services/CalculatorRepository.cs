using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;

namespace FinSys.Wpf.Services
{
    public class CalculatorRepository : ICalculatorRepository
    {
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getclassdescriptions(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getdaycounts(out int size);

        public async Task<List<string>> GetDayCountsAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> daycounts = new List<string>();
                int size;
                IntPtr ptr = getdaycounts(out size);
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

        public async Task<List<InstrumentClass>> GetInstrumentClassesAsync()
        {
            List<Model.InstrumentClass> result = await Task.Run(() =>
            {
                List<Model.InstrumentClass> instrumentClasses = new List<Model.InstrumentClass>();
                int size;
                IntPtr ptr = getclassdescriptions(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    Console.WriteLine("i = " + i);
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string description = Marshal.PtrToStringAnsi(strPtr);
                    InstrumentClass ic = new InstrumentClass
                    {
                        Name=description
                    };
                    instrumentClasses.Add(ic);
                    ptr += Marshal.SizeOf(typeof(IntPtr));
                }
                return instrumentClasses;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }
    }
}
