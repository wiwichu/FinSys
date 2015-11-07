using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;
using System.Collections.Concurrent;

namespace FinSys.Wpf.Services
{
    class PortfoliosRepository : IPortfoliosRepository
    {
        //static List<Portfolio> portfolios = new List<Portfolio>();
        static ConcurrentDictionary<Portfolio, int> portfolios = new ConcurrentDictionary<Portfolio, int>();
        static PortfoliosRepository()
        {
            Initialize();
        }

        private static void Initialize()
        {
            lock (Repositories.repositoryLock)
            {
                portfolios.Clear();
                Portfolio porta = new Portfolio()
                {
                    Id = "Porta"
                };
                portfolios.AddOrUpdate(porta, 0, (p, v) => 0);
                Portfolio portb = new Portfolio()
                {
                    Id = "Portb"
                };
                portfolios.AddOrUpdate(portb, 0, (p, v) => 0);
                Portfolio portc = new Portfolio()
                {
                    Id = "Portc"
                };
                portfolios.AddOrUpdate(portc, 0, (p, v) => 0);
                Portfolio portd = new Portfolio()
                {
                    Id = "Portd"
                };
                portfolios.AddOrUpdate(portd, 0, (p, v) => 0);
                Portfolio porte = new Portfolio()
                {
                    Id = "Porte"
                };
                portfolios.AddOrUpdate(porte, 0, (p, v) => 0);
            }
        }

        public async Task<List<Portfolio>> GetPortfoliosAsync()
        {
            List<Portfolio> port = await Task.Run(() =>
            {
                return portfolios.Keys.OrderBy((p)=>p.Id).ToList();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return port;
        }
        public async Task AddOrUpdateAsync(Portfolio portfolio)
        {
            await Task.Run(() =>
            {
                portfolios.AddOrUpdate(portfolio, 0, (p, v) => 0);
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }
    }
}
