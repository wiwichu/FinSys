using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class DefaultDatesViewModel
    {
        [Required]
        public string IntDayCount { get; set; }
        [Required]
        public string IntPayFreq { get; set; }
        [Required]
        public DateTime MaturityDate { get; set; }
        [Required]
        public DateTime ValueDate { get; set; }
        [Required]
        public bool EndOfMonthPay { get; set; }
        [Required]
        public string HolidayAdjust { get; set; }
        [Required]
        public IEnumerable<DateTime> Holidays { get; set; }
    }
}
