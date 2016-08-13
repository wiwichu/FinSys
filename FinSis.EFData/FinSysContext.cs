using FinSys.EFClasses;
using System.Data.Entity;

namespace FinSys.EFData
{
    public class FinSysContext : DbContext
    {
        static object saveLock = new object();
        public DbSet<Portfolio> Portfolios { get; set; }
        public DbSet<Position> Positions { get; set; }
        public DbSet<Trade> Trades { get; set; }
        public override int SaveChanges()
        {
            lock (saveLock)
            {
                return base.SaveChanges();
            }
        }
    }
}
