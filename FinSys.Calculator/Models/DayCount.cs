using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Models
{
    public class DayCount
    {
        public string Id { get; set; }
        public string Status { get; set; }
        public string Message { get; set; }
        public string Rule { get; set; }
        public DateTime StartDate { get; set; }
        public DateTime EndDate { get; set; }
        public int Days { get; set; }
        public double Factor { get; set; }
    }
}
