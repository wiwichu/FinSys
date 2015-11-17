using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using FinSys.EFData;

namespace FinSys.Wpf.Services
{
    class PortfoliosRepositoryEF : IPortfoliosRepository
    {
        public void AddOrUpdate(Model.Portfolio portfolio)
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


        public async Task AddOrUpdateAsync(Model.Portfolio portfolio)
        {
            await Task.Run(() =>
            {
                    AddOrUpdate(portfolio);
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task<List<Model.Portfolio>> GetPortfoliosAsync()
        {
            List<Model.Portfolio> port = await Task.Run(() =>
            {
                List<Model.Portfolio> ports = new List<Model.Portfolio>();
                using (var context = new FinSysContext())
                {
                    //context.Database.Log = Console.WriteLine;
                    var portfolios = context.Portfolios.SqlQuery("exec GetAllPortfolios").ToList();
                    foreach (var portfolio in portfolios)
                    {
                        var p = new Model.Portfolio
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
