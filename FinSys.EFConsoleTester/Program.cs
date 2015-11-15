using FinSys.EFClasses;
using FinSys.EFData;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.EFConsoleTester
{
    class Program
    {
        static void Main(string[] args)
        {
            InsertPortfolio();
            DeleteProcedureViaId();
            RetrieveDataWithStoredProcedure();
            DeleteProcedureViaId();
            RetrieveDataWithStoredProcedure();
            Console.ReadLine();
        }

        private static void DeleteProcedureViaId()
        {
            var keyVal = "PortA";
            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                var portfolios = context.Portfolios.SqlQuery("exec DeletePortfolioViaId (0)", keyVal);
                
            }
        }

        private static void RetrieveDataWithStoredProcedure()
        {
            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                var portfolios = context.Portfolios.SqlQuery("exec GetAllPortfolios");
                foreach (var portfolio in portfolios)
                {
                    Console.WriteLine(portfolio.Id);
                }
            }
        }

        private static void InsertPortfolio()
        {
            var port = new Portfolio
            {
                Id = "PortA"
            };
            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                context.Portfolios.Add(port);
                context.SaveChanges();
            }
        }
    }
}
