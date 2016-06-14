using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class CashFlowPricingViewModel
    {
        [Required]
        public IEnumerable<CashFlowViewModel> CashFlows { get; set; }
        [Required]
        public string YieldMethod { get; set; }
        [Required]
        public string DiscountFrequency { get; set; }
        [Required]
        public string DayCount { get; set; }
        [Required]
        public DateTime ValueDate { get; set; }
        [Required]
        public IEnumerable<RateCurveViewModel> RateCurve { get; set; }
        [Required]
        public string Interpolation { get; set; }
        [Required]
        public bool PriceFromCurve { get; set; }
    }
}
