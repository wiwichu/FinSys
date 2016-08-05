using FinSys.Mobile.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile
{
    public interface ILibApi
    {
        IntPtr GetClassDescriptions(out int size);
        IntPtr GetDayCounts(out int size);
        int GetInstrumentDefaultsAndData(Instrument instrument, Calculations calculations);
        string getIOSInfo();
    }
}
