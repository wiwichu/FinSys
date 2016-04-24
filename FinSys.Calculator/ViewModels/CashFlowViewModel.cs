using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class CashFlowViewModel
    {
        [Required]
        public DateTime ScheduledDate { get; set; } = DateTime.UtcNow.ToLocalTime();
        [Required]
        public double Amount { get; set; }
        [Required]
        public double PresentValue { get; set; }
        [Required]
        public DateTime AdjustedDate { get; set; } = DateTime.UtcNow.ToLocalTime();
        [Required]
        public double DiscountRate { get; set; }
    }
}
