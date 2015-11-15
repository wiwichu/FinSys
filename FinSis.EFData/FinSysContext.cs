using FinSys.EFClasses;
using System.Data.Entity;

namespace FinSys.EFData
{
    public class FinSysContext : DbContext
    {
        public DbSet<Portfolio> Portfolios { get; set; }
        public DbSet<Position> Positions { get; set; }
        public DbSet<Trade> Trades { get; set; }
    }
}
