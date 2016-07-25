using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.ViewModels
{
    public class RateCurveViewModel
    {
        [Required]
        public DateTime RateDate { get; set; } = DateTime.UtcNow.ToLocalTime();
        [Required]
        public double Rate { get; set; }
    }
}
