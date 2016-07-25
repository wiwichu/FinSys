using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.Models
{
    public class USTBillResult
    {
        public double Price { get; set; }
        public double Discount { get; set; }
        public double BondEquivalent { get; set; }
        public double MMYield { get; set; }
        public double Duration { get; set; }
        public double ModifiedDuration { get; set; }
        public double Convexity { get; set; }
        public double Pvbp { get; set; }
        public double ConvexityAdjustedPvbp { get; set; }
        public IEnumerable<CashFlow> CashFlows { get; set; }
    }
}
