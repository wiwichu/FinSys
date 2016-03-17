using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.Data.Entity;

namespace FinSys.Calculator.Models
{
    public class FinSysContext : DbContext
    {
        public FinSysContext()
        {
            Database.EnsureCreated();
        }
        public DbSet<Log> Logs { get; set; }
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            var connString = Startup.Configuration["Data:FinSysConnection"];

            optionsBuilder.UseSqlServer(connString);

            base.OnConfiguring(optionsBuilder);
        }
    }
}
