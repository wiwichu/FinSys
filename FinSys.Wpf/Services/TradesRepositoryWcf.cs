using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using FinSys.Wpf.Model;
using FinSyS.Wcf.Proxies;
using System.Linq;
using FinSys.Wpf.Helpers;

namespace FinSys.Wpf.Services
{
    class TradesRepositoryWcf : ITradesRepository
    {
        public async Task AddOrUpdateAsync(List<Trade> trades)
        {
            await Task.Run(() =>
            {
                List<Wcf.Contracts.TradeData> tradesData = new List<Wcf.Contracts.TradeData>();
                trades.All((t) =>
                {
                    
                    Wcf.Contracts.TradeData data = new Wcf.Contracts.TradeData
                    {
                        Amount = t.Amount,
                        InstrumentId = t.InstrumentId,
                        PortfolioId = t.PortfolioId,
                        Price = t.Price,
                        CounterParty = t.CounterParty,
                        Id = t.Id,
                        ValueDate = t.ValueDate
                    };
                    tradesData.Add(data);
                    return true;
                });
                FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
                proxy.AddOrUpdateTrades(tradesData);
                proxy.Close();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task AddOrUpdateAsync(Trade trade)
        {
            await Task.Run(() =>
            {
                Wcf.Contracts.TradeData data = new Wcf.Contracts.TradeData
                {
                    Amount = trade.Amount,
                    InstrumentId = trade.InstrumentId,
                    PortfolioId = trade.PortfolioId,
                    Price = trade.Price,
                    CounterParty = trade.CounterParty,
                    Id = trade.Id,
                    ValueDate = trade.ValueDate
                };
                FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
                proxy.AddOrUpdateTrade(data);
                proxy.Close();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task DeleteAsync(List<Trade> trades)
        {
            await Task.Run(() =>
            {
                List<Wcf.Contracts.TradeData> tradesData = new List<Wcf.Contracts.TradeData>();
                trades.All((t) =>
                {

                    Wcf.Contracts.TradeData data = new Wcf.Contracts.TradeData
                    {
                        Id = t.Id
                    };
                    tradesData.Add(data);
                    return true;
                });
                FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
                proxy.AddOrUpdateTrades(tradesData);
                proxy.Close();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task DeleteAsync(Trade trade)
        {
            await Task.Run(() =>
            {
                Wcf.Contracts.TradeData data = new Wcf.Contracts.TradeData
                {
                    Id = trade.Id
                };
                FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
                proxy.DeleteTrade(data);
                proxy.Close();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task<List<Trade>> GetTradesAsync()
        {
            List<Model.Trade> trades = new List<Trade>();
            await Task.Run(() =>
            {
                List<Model.Trade> tradesData = new List<Model.Trade>();

                FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
                IEnumerable<Wcf.Contracts.TradeData> data = proxy.GetTrades();

                data.All((t) =>
                {
                    Model.Trade trade = new Trade
                    {
                        Amount = t.Amount,
                        InstrumentId = t.InstrumentId,
                        PortfolioId = t.PortfolioId,
                        Price = t.Price,
                        Id=t.Id,
                        CounterParty=t.CounterParty,
                        ValueDate=t.ValueDate
                    };
                    trades.Add(trade);
                    return true;
                });

                proxy.Close();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return trades;
        }
    }
}
