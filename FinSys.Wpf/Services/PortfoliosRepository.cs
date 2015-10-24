using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;

namespace FinSys.Wpf.Services
{
    class PortfoliosRepository : IPortfoliosRepository
    {
        static List<Portfolio> portfolios = new List<Portfolio>();

        static PortfoliosRepository()
        {
            Portfolio porta = new Portfolio()
            {
                Id = "Porta"
            };
            portfolios.Add(porta);
            Portfolio portb = new Portfolio()
            {
                Id = "Portb"
            };
            portfolios.Add(portb);
            Portfolio portc = new Portfolio()
            {
                Id = "Portc"
            };
            portfolios.Add(portc);
            Portfolio portd = new Portfolio()
            {
                Id = "Portd"
            };
            portfolios.Add(portd);
            Portfolio porte = new Portfolio()
            {
                Id = "Porte"
            };
            portfolios.Add(porte);
        }
        public async Task<List<Portfolio>> GetPortfoliosAsync()
        {
            List<Portfolio> port = await Task.Run(() =>
            {
                return portfolios;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return port;
        }
    }
}
