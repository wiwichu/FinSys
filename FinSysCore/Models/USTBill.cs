using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.Models
{
    public class USTBill
    {
        public enum CALCULATEFROM
        {
            PRICE,
            DISCOUNT,
            BONDEQUIVALENT,
            MMYIELD
        };
        public DateTime MaturityDate { get; set; } = DateTime.UtcNow.AddYears(1).ToLocalTime();
        public DateTime ValueDate { get; set; } = DateTime.UtcNow.ToLocalTime();
        public CALCULATEFROM CalcFrom { get; set; }
        public double CalcSource { get; set; }
        public bool IncludeCashFlows { get; set; }
    }
}
