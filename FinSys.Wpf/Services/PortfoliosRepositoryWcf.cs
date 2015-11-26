using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;
using FinSyS.Wcf.Proxies;
using FinSys.Wpf.Helpers;
using System.ServiceModel;
using FinSys.Wcf.Proxies.Contracts;

namespace FinSys.Wpf.Services
{
    class PortfoliosRepositoryWcf : IPortfoliosRepository
    {
        public void AddOrUpdate(Portfolio portfolio)
        {
            Wcf.Contracts.PortfolioData data = new Wcf.Contracts.PortfolioData
            {
                Id = portfolio.Id
            };
            FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
            proxy.AddOrUpdatePortfolio(data);
            proxy.Close();
        }

        public async Task AddOrUpdateAsync(Portfolio portfolio)
        {
            await Task.Run(() =>
            {
                AddOrUpdate(portfolio);
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task<List<Portfolio>> GetPortfoliosAsync()
        {
            List<Model.Portfolio> port = await Task.Run(() =>
            {
                List<Model.Portfolio> ports = new List<Model.Portfolio>();

                FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
                IEnumerable<Wcf.Contracts.PortfolioData> data = proxy.GetPortfolios();

                data.All((p) =>
                {
                    Model.Portfolio portfolio = new Portfolio
                    {
                        Id = p.Id
                    };
                    ports.Add(portfolio);
                    return true;
                });

                proxy.Close();

                return ports;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return port;
        }
    }
}
