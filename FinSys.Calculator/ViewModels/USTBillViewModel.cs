using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class USTBillViewModel
    {
        static public IEnumerable<string> CalculateFrom = new List<string>()
        {
            "Price","Discount","BondEquivalent","MMYield"
        };
        [Required]
        public DateTime MaturityDate { get; set; }
        [Required]
        public DateTime ValueDate { get; set; }
        [Required]
        public string CalcFrom { get; set; }
        [Required]
        public double CalcSource { get; set; }
        [Required]
        public bool IncludeCashFlows { get; set; }
    }
}
