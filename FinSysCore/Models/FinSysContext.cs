using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Configuration;

namespace FinSysCore.Models
{
    public class FinSysContext : DbContext
    {
        static bool dbCreated = false;
        private IConfigurationRoot _config;
        public FinSysContext(DbContextOptions options, IConfigurationRoot config)
            : base(options)
        {
            _config = config;
            if (!dbCreated)
            {
                Database.EnsureCreated();
                dbCreated = true;
            }
        }
        public DbSet<Log> Logs { get; set; }
        protected override void OnConfiguring(DbContextOptionsBuilder optionsBuilder)
        {
            var connString = _config["Data:FinSysConnection"];

            optionsBuilder.UseSqlServer(connString);

            base.OnConfiguring(optionsBuilder);
        }
    }
}
