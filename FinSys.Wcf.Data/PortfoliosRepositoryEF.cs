using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using FinSys.EFData;
using FinSys.Wcf.Contracts;

namespace FinSys.Wcf.Data
{
    internal class PortfoliosRepositoryEF : IPortfoliosRepository
    {
        public void AddOrUpdate(PortfolioData portfolio)
        {

            using (var context = new FinSysContext())
            {
                if (context.Portfolios.Find(new object[] { portfolio.Id }) == null)
                {
                    //context.Database.Log = Console.WriteLine;
                    var portfolioEF = new FinSys.EFClasses.Portfolio
                    {
                        Id = portfolio.Id
                    };
                    context.Portfolios.Add(portfolioEF);
                    context.SaveChanges();
                }
            }
        }


        public async Task AddOrUpdateAsync(PortfolioData portfolio)
        {
            await Task.Run(() =>
            {
                    AddOrUpdate(portfolio);
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task<List<PortfolioData>> GetPortfoliosAsync()
        {
            List<PortfolioData> port = await Task.Run(() =>
            {
                List<PortfolioData> ports = new List<PortfolioData>();
                using (var context = new FinSysContext())
                {
                    //context.Database.Log = Console.WriteLine;
                    var portfolios = context.Portfolios.SqlQuery("exec GetAllPortfolios").ToList();
                    foreach (var portfolio in portfolios)
                    {
                        var p = new PortfolioData
                        {
                            Id = portfolio.Id
                        };
                        ports.Add(p);
                    }
                    return ports;
                }
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return port;
        }

    }
}
