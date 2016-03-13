using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Data.Entity;

namespace FinSys.Calculator.Models
{
    public class LoggingContext : DbContext
    {
        public DbSet<Logging> Logs { get; set; }
    }
}
