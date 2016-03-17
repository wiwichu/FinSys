using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Models
{
    public class Log
    {
        public int Id { get; set; }
        public string User { get; set; }
        public string Severity { get; set; }
        public DateTime LogTime { get; set; }
        public string Topic { get; set; }
        public string Message { get; set; }

    }
}
