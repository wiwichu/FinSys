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
            Initialize();
            Console.ReadLine();
        }

        private static void Initialize()
        {
            TruncateTables();
            InsertPortfolios();
            List<Trade> trades = new List<Trade>();
                Trade t1 = new Trade()
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr1",
                    Amount = 5000,
                    Price = .80,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.Add(t1);
                Trade t2 = new Trade()
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr1",
                    Amount = 5000,
                    Price = 1.0,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t2);
                Trade t3 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr2",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t3);
                Trade t4 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr2",
                    Amount = -10000,
                    Price = 1.15,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.Add(t4);
                Trade t5 = new Trade
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr2",
                    Amount = 10000,
                    Price = .89,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.Add(t5);
                Trade t6 = new Trade
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr2",
                    Amount = 10000,
                    Price = .91,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.Add(t6);
                Trade t7 = new Trade
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr2",
                    Amount = -10000,
                    Price = .86,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t7);
                Trade t8 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr1",
                    Amount = 20000,
                    Price = 1.0,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t8);
                Trade t9 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr1",
                    Amount = 20000,
                    Price = 1.20,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.Add(t9);
                Trade t10 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr1",
                    Amount = -20000,
                    Price = 1.25,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp3"
                };
                trades.Add(t10);
                Trade t11 = new Trade
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr3",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp4"
                };
                trades.Add(t11);
                Trade t12 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr3",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t12);
                Trade t13 = new Trade
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr4",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t13);
                Trade t14 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr4",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t14);
                Trade t15 = new Trade
                {
                    PortfolioId = "Porta",
                    InstrumentId = "Instr5",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t15);
                Trade t16 = new Trade
                {
                    PortfolioId = "Portb",
                    InstrumentId = "Instr5",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.Add(t16);
                Trade t17 = new Trade
                {
                    PortfolioId = "Portc",
                    InstrumentId = "Instrx",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2x"
                };
                trades.Add(t17);

            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                context.Trades.AddRange(trades);
                context.SaveChanges();
            }
        }

        private static void TruncateTables()
        {
            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                context.Database.ExecuteSqlCommand("DELETE FROM Trades");
                context.Database.ExecuteSqlCommand("DELETE FROM Positions");
                context.Database.ExecuteSqlCommand("DELETE FROM Portfolios");
                context.SaveChanges();

            }
        }

        private static void DeleteProcedureViaId()
        {
            var keyVal = "Port1";
            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                context.Database.ExecuteSqlCommand("exec DeletePortfolioViaId (0)", keyVal);
                context.SaveChanges();

            }
        }
        private static void DeleteRange()
        {
            //List<Portfolio> portfolios = new List<Portfolio>();
            //for (int i = 1; i<100;i++)
            //{
            //    if (i % 2 == 0)
            //    {
            //        var portfolio = new Portfolio
            //        {
            //            Id = "Port" + i
            //        };
            //        portfolios.Add(portfolio);
            //    }
            //}
            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                var portfolios = context.Portfolios.ToList();
                
                context.Portfolios.RemoveRange(portfolios.Where((p) => (Convert.ToInt32(p.Id.Substring(4)) % 2 == 0)).ToList());
                context.SaveChanges();

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

        private static void InsertPortfolios()
        {
            List<Portfolio> portfolios = new List<Portfolio>();
            //for (int i = 1; i < 100; i++)
            //{
            //    var port = new Portfolio
            //    {
            //        Id = "Port" + i
            //    };
            //    portfolios.Add(port);
            //}

            var porta = new Portfolio { Id = "Porta" };
            portfolios.Add(porta);
            var portb = new Portfolio { Id = "Portb" };
            portfolios.Add(portb);
            var portc = new Portfolio { Id = "Portc" };
            portfolios.Add(portc);


            using (var context = new FinSysContext())
            {
                context.Database.Log = Console.WriteLine;
                context.Portfolios.AddRange(portfolios);
                context.SaveChanges();
            }
        }
    }
}
