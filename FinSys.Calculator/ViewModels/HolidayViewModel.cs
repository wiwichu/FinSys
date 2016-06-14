using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.ViewModels
{
    public class HolidayViewModel
    {
        [Required]
        public DateTime HolidayDate { get; set; }
    }
}
