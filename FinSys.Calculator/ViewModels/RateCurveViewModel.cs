using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class RateCurveViewModel
    {
        [Required]
        public DateTime RateDate { get; set; } = DateTime.UtcNow;
        [Required]
        public double Rate { get; set; }
    }
}
