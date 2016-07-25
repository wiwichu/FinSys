using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.ViewModels
{
    public class DayCountViewModel
    {
        public string Id { get; set; }
        public string Status { get; set; }
        public string Message { get; set; }
        [Required]
        public string Rule { get; set; }
        [Required]
        public DateTime StartDate { get; set; }
        [Required]
        public DateTime EndDate { get; set; }
        [Required]
        public int Days { get; set; }
        [Required]
        public double Factor { get; set; }
    }
}
