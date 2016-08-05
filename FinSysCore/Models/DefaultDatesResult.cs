using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.Models
{
    public class DefaultDatesResult
    {
        public DateTime MaturityDate { get; set; }
        public DateTime IssueDate { get; set; }
        public DateTime FirstPayDate { get; set; }
        public DateTime NextToLastPayDate { get; set; }
    }
}
