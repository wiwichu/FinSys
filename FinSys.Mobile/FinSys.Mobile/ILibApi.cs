using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile
{
    public interface ILibApi
    {
        IntPtr getClassDescriptions(out int size);
        IntPtr getDayCounts(out int size);
        string getIOSInfo();
    }
}
