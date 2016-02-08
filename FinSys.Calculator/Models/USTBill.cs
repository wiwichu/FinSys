using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Models
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
        public DateTime MaturityDate { get; set; } = DateTime.Now.AddYears(1);
        public DateTime ValueDate { get; set; } = DateTime.Now;
        public CALCULATEFROM CalcFrom { get; set; }
        public double CalcSource { get; set; }
        public bool IncludeCashFlows { get; set; }
    }
}
