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
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getpayfreqs(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getStatusText(int status, StringBuilder text, out int textSize);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getInstrumentDefaults(InstrumentDescr instrument);

        private List<string> classes = new List<string>();
        private List<string> dayCounts = new List<string>();
        private List<string> payFreqs = new List<string>();
        public CalculatorRepository()
        {
            classes = new List<string>( GetInstrumentClassesAsync().Result.Select((ic)=>ic.Name));
            dayCounts = GetDayCountsAsync().Result;
            payFreqs = GetPayFreqsAsync().Result;
        }

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

        public async Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> instrumentsIn)
        {
            List<Instrument> result = await Task.Run(() =>
            {
                List<Instrument> instruments = new List<Instrument>();
                for (int i = 0; i < instrumentsIn.Count; i++)
                {
                    Instrument ins = instrumentsIn[i];
                    int insClassNum = classes.IndexOf(ins.Class.Name);
                    int insDayCount = dayCounts.IndexOf(ins.IntDayCount);
                    int insPayFreq = payFreqs.IndexOf(ins.IntPayFreq);
                    InstrumentDescr instr = new InstrumentDescr
                    {
                        instrumentClass = insClassNum,
                        intDayCount = insDayCount,
                        intPayFreq = insPayFreq
                    };
                    DateDescr maturityDate = new DateDescr
                    {
                        year = 1000,
                        month = 12,
                        day = 12
                    };
                    instr.maturityDate = Marshal.AllocHGlobal(Marshal.SizeOf(typeof(DateDescr)));
                    Marshal.StructureToPtr(maturityDate, instr.maturityDate, false);
                    StringBuilder statusText = new StringBuilder(200);
                    int textSize;
                    int status = getInstrumentDefaults(instr);
                    status = getStatusText(status, statusText, out textSize);
                    IntPtr matPtr = Marshal.ReadIntPtr(instr.maturityDate);
                    DateDescr matDate = new DateDescr();
                    matDate = Marshal.PtrToStructure<DateDescr>(instr.maturityDate);
                    Instrument newInstr = new Instrument
                    {
                        IntDayCount = dayCounts[instr.intDayCount],
                        IntPayFreq = payFreqs[instr.intPayFreq],
                        Class = new InstrumentClass
                        {
                            Name = classes[instr.instrumentClass]
                        }

                    };
                    instruments.Add(newInstr);
                    GC.KeepAlive(instr);
                }
               return instruments;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;

        }

        public async Task<List<string>> GetPayFreqsAsync()
        {
            List<string> result = await Task.Run(() =>
            {
                List<string> payfreqs = new List<string>();
                int size;
                IntPtr ptr = getpayfreqs(out size);
                IntPtr strPtr;
                for (int i = 0; i < size; i++)
                {
                    strPtr = Marshal.ReadIntPtr(ptr);
                    string name = Marshal.PtrToStringAnsi(strPtr);
                    payfreqs.Add(name);
                    ptr += Marshal.SizeOf(typeof(IntPtr));
                }
                return payfreqs;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;
        }
    }
    [StructLayout(LayoutKind.Sequential)]
    internal class InstrumentDescr
    {
        public int instrumentClass;
        public int intDayCount;
        public int intPayFreq;
        public IntPtr maturityDate;
    };

    [StructLayout(LayoutKind.Sequential)]
    internal class DateDescr
    {
        public int year;
        public int month;
        public int day;
    };
}
