using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.ViewModels
{
    public class CalculatorResultViewModel
    {
        public string Id { get; set; }
        public string Status { get; set; }
        public string Message { get; set; }
        [Required]
        public double Yield { get; set; }
        [Required]
        public double CleanPrice { get; set; }
        [Required]
        public double AccruedInterest { get; set; }
        [Required]
        public int InterestDays { get; set; }
        [Required]
        public double DirtyPrice { get; set; }
        [Required]
        public DateTime PreviousPay { get; set; }
        [Required]
        public DateTime NextPay { get; set; }
        [Required]
        public double Duration { get; set; }
        [Required]
        public double ModifiedDuration { get; set; }
        [Required]
        public double Convexity { get; set; }
        [Required]
        public double Pvbp { get; set; }
        [Required]
        public double ConvexityAdjustedPvbp { get; set; }
        [Required]
        public IEnumerable<CashFlowViewModel> Cashflows  { get; set; }
        [Required]
        public DateTime IssueDate { get; set; }
        [Required]
        public DateTime FirstPayDate { get; set; }
        [Required]
        public DateTime NextToLastDate { get; set; }
    }
}
