using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.Models
{
    public class CashFlowPricing
    {
        public IEnumerable<CashFlow> CashFlows { get; set; }
        public string YieldMethod { get; set; }
        public string DiscountFrequency { get; set; }
        public string DayCount { get; set; }
        public DateTime ValueDate { get; set; }
        public IEnumerable<RateCurve> RateCurve { get; set; }
        public string Interpolation { get; set; }
        public bool PriceFromCurve { get; set; }
    }
}
