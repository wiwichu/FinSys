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
        private static extern int getInstrumentDefaults(ref CALCULATION calculations);

        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void getInstrumentDefaults(IntPtr calculations);
//        private static extern IntPtr getInstrumentDefaults(IntPtr instruments);


        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getclassdescriptions(out int size);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr getdaycounts(out int size);

        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getStatusText(int status, StringBuilder text, out int textSize);
        [DllImport("calc.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int getDefaultInstrument(InstrumentDescr instrument);

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
                for (int i = 0; i < instrumentsIn.Count; i++)
                {
                    Instrument ins = instrumentsIn[i];
                    InstrumentDescr instr = new InstrumentDescr
                    {
                        instrumentClass = 2,
                        intDayCount = 2,
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
                    int status = getDefaultInstrument(instr);
                    status = getStatusText(status, statusText, out textSize);
                    IntPtr matPtr = Marshal.ReadIntPtr(instr.maturityDate);
                    DateDescr matDate = new DateDescr();
                    matDate = Marshal.PtrToStructure<DateDescr>(instr.maturityDate);
                    GC.KeepAlive(instr);
                }
                List<Instrument> instruments = new List<Instrument>();
                return instruments;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;

        }

        /*
        public async Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> instruments)
        {
            List<Instrument> result = await Task.Run(() =>
            {
                    Instrument instrument = instruments[0];
                    INSTRUMENT insIn = new INSTRUMENT
                    {
                        intDayCount = instrument.IntDayCount,
                        instrClass = instrument.Class.Name,
                        name = instrument.Name
                    };

                CALCULATION calculation = new CALCULATION() ;

                IntPtr buffer = Marshal.AllocCoTaskMem(Marshal.SizeOf(insIn));
                Marshal.StructureToPtr(insIn, buffer, false);

                calculation.instrument = buffer;

                int res = getInstrumentDefaults(ref calculation);

                INSTRUMENT INSTRUMENTRes =
                    (INSTRUMENT)Marshal.PtrToStructure(calculation.instrument,
                    typeof(INSTRUMENT));

                Marshal.FreeCoTaskMem(buffer);


                List<Instrument> instrOut = new List<Instrument>();
                return instrOut;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return result;

        }
*/
        /*
                public async Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> calcs)
                {
                    List<Instrument> result = await Task.Run(() =>
                    {

                            Instrument ins = calcs[0];
                            INSTRUMENT instrIn = new INSTRUMENT
                            {
                                intDayCount = ins.IntDayCount,
                                instrClass = ins.Class.Name,
                                name = ins.Name
                            };
                        int nSizeCalc = Marshal.SizeOf(instrIn);
                        IntPtr pCalcs = Marshal.AllocHGlobal(nSizeCalc);
                        Marshal.StructureToPtr(instrIn, pCalcs, false);

                        getInstrumentDefaults(pCalcs);

                        List<Instrument> instruments = new List<Instrument>();

                        return instruments;
                    })
                    .ConfigureAwait(false) //necessary on UI Thread
                    ;
                    return result;

                }
        */
        /*  
                        public async Task<List<Instrument>> GetInstrumentDefaultsAsync(List<Instrument> calcs)
                        {
                            List<Instrument> result = await Task.Run(() =>
                            {

                                CALCULATIONS[] calculations = new CALCULATIONS[Globals.INSTRUMENTSHASHSIZE];
                                CALCULATIONS calc = new CALCULATIONS();
                                calc.instruments = new IntPtr[Globals.INSTRUMENTSHASHSIZE];
                                INSTRUMENT[] instrs = new INSTRUMENT[Globals.INSTRUMENTSHASHSIZE];
                                for (int i = 0; i < calcs.Count; i++)
                                {
                                    Instrument ins = calcs[i];
                                    instrs[i] = new INSTRUMENT
                                    {
                                        intDayCount = ins.IntDayCount,
                                        instrClass = ins.Class.Name,
                                        name = ins.Name
                                    };
                                  }
                                List<int> instrSizes = new List<int>();
                                for (int ix = 0; ix < Globals.INSTRUMENTSHASHSIZE && instrs[ix] != null; ix++)
                                {
                                    int nSizeInstr = Marshal.SizeOf(instrs[ix]);
                                    instrSizes.Add(nSizeInstr);
                                    calc.instruments[ix] = Marshal.AllocHGlobal(nSizeInstr);
                                    Marshal.StructureToPtr(instrs[ix], calc.instruments[ix], false);
                                }
                                calculations[0] = calc;
                                int nSizeCalc = Marshal.SizeOf(calc);
                                IntPtr pCalcs = Marshal.AllocHGlobal(nSizeCalc);
                                Marshal.StructureToPtr(calc, pCalcs, false);

                                getInstrumentDefaults(pCalcs);


                                IntPtr calcPtr = Marshal.ReadIntPtr(pCalcs);
                                CALCULATIONS outCalc = Marshal.PtrToStructure<CALCULATIONS>(calcPtr);

                                for (int i = 0;i<instrSizes.Count;i++)
                                {

                                    //int nSizeInstr = Marshal.SizeOf(instrSizes[i]);
                                    //IntPtr pInstr = Marshal.AllocHGlobal(nSizeInstr);
                                    //IntPtr pInstr = Marshal.AllocHGlobal(instrSizes[i]);
                                    IntPtr insPtr = Marshal.ReadIntPtr(outCalc.instruments[i]);
                                    INSTRUMENT outInstr = new INSTRUMENT();
                                    //outInstr = Marshal.PtrToStructure<INSTRUMENT>(insPtr);
                                    Marshal.PtrToStructure<INSTRUMENT>(insPtr, outInstr);

                                }

                                List<Instrument> instruments = new List<Instrument>();
                                instrs.All((i) =>
                                {
                                    instruments.Add(new Instrument
                                    {
                                        Name = i.name,
                                        IntDayCount = i.intDayCount,
                                        Class = new InstrumentClass { Name = i.instrClass }

                                    });
                                    return true;
                                });

                                return instruments;
                            })
                            .ConfigureAwait(false) //necessary on UI Thread
                            ;
                            return result;

                        }
        */
    }
}
