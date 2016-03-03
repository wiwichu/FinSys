using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class CalculatorViewModel
    {
        public string Id { get; set; }
        [Required]
        public double InterestRate { get; set; }
        [Required]
        public DateTime MaturityDate { get; set; }
        [Required]
        public bool EndOfMonth { get; set; }
        [Required]
        public DateTime ValueDate { get; set; }
        [Required]
        public bool CalculatePrice { get; set; }
        [Required]
        public double YieldIn { get; set; }
        [Required]
        public double PriceIn { get; set; }
        [Required]
        public bool ExCoupon { get; set; }
        [Required]
        public bool TradeFlat { get; set; }
        [Required]
        public bool IncludeCashflows { get; set; }
        [Required]
        public bool UseHolidays { get; set; }
        [Required]
        public IEnumerable<DateTime> Holidays { get; set; }
        [Required]
        public string DayCount { get; set; }
        [Required]
        public string PayFrequency { get; set; }
        [Required]
        public string CalcDateAdjust { get; set; }
        [Required]
        public string PayDateAdjust { get; set; }
        [Required]
        public string YieldDayCount { get; set; }
        [Required]
        public string YieldFrequency { get; set; }
        [Required]
        public string YieldMethod { get; set; }
        [Required]
        public DateTime IssueDate { get; set; }
        [Required]
        public DateTime NextToLastDate { get; set; }




    }
}
