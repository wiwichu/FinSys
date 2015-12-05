using FinSys.Wpf.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    public interface ICalculatorRepository
    {
        Task<List<InstrumentClass>> GetInstrumentClassesAsync();
        Task<List<string>> GetDayCountsAsync();
        Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> calcs);
    }
    /*
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public struct INSTRUMENT
    {
        public string name;
        public string instrClass;
        public string intDayCount;
    };
    */
    [StructLayout(LayoutKind.Sequential)]
    public class InstrumentDescr
    {
        public int instrumentClass;
        public int intDayCount;
        public IntPtr maturityDate;
    };

    [StructLayout(LayoutKind.Sequential)]
    public class DateDescr
    {
        public int year;
        public int month;
        public int day;
    };
    [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Ansi)]
    public class INSTRUMENT
         {
             IntPtr nam;
             public string name
             {
                 get { return Marshal.PtrToStringAnsi(nam); }
                 set { nam =  Marshal.StringToHGlobalAnsi(value); }
             }
             IntPtr instrclass;
             public string instrClass
             {
                 get { return Marshal.PtrToStringAnsi(instrclass); }
                 set { instrclass = Marshal.StringToHGlobalAnsi(value); }
             }
             IntPtr intdaycount;
             public string intDayCount
             {
                 get { return Marshal.PtrToStringAnsi(intdaycount); }
                 set { intdaycount = Marshal.StringToHGlobalAnsi(value); }
             }
         };
    
    [StructLayout(LayoutKind.Sequential)]
    public class CALCULATION
    {
        public IntPtr instrument;
        public IntPtr userData;
    }
    [StructLayout(LayoutKind.Sequential)]
    public struct CALCULATIONS
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = Globals.INSTRUMENTSHASHSIZE)]
        public IntPtr[] instruments;
        public IntPtr userData;
    }
    public class Globals
    {
        public const int INSTRUMENTSHASHSIZE = 151;

    }
}
