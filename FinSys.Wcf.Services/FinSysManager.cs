using FinSys.Wcf.Contracts;
using FinSys.Wcf.Data;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Services
{
    public class FinSysManager : IFinSysService
    {
        private static ConcurrentDictionary<IFinSysServiceCallback, IFinSysServiceCallback> callbacks = new ConcurrentDictionary<IFinSysServiceCallback, IFinSysServiceCallback>();
        public FinSysManager()
        {
            RepositoryFactory.BuildPositions();
        }
        public void AddOrUpdatePortfolio(PortfolioData portfolio)
        {
            RepositoryFactory.Portfolios.AddOrUpdate(portfolio);
            UpdateNotify();
        }

        public void AddOrUpdatePosition(PositionData position)
        {
            RepositoryFactory.Positions.AddOrUpdate(position);
            UpdateNotify();
        }

        public async void AddOrUpdateTrade(TradeData trade)
        {
            await RepositoryFactory.Trades.AddOrUpdateAsync(trade);
            UpdateNotify();
        }

        public async void AddOrUpdateTrades(IEnumerable<TradeData> trades)
        {
            await RepositoryFactory.Trades.AddOrUpdateAsync(trades);
            UpdateNotify();
        }

        public async void DeleteTrade(TradeData trade)
        {
            await RepositoryFactory.Trades.DeleteAsync(trade);
            UpdateNotify();
        }

        public async void DeleteTrades(IEnumerable<TradeData> trades)
        {
            await RepositoryFactory.Trades.DeleteAsync(trades);
            UpdateNotify();
        }

        public IEnumerable<PortfolioData> GetPortfolios()
        {
            return RepositoryFactory.Portfolios.GetPortfoliosAsync().Result;
        }

        public IEnumerable<PositionData> GetPositions()
        {
            return RepositoryFactory.Positions.GetPositionsAsync().Result;
        }

        public IEnumerable<TradeData> GetTrades()
        {
            return RepositoryFactory.Trades.GetTradesAsync().Result;
        }

        public void Register()
        {
            if (OperationContext.Current != null)
            {
                IFinSysServiceCallback callback =
                    OperationContext.Current.GetCallbackChannel<IFinSysServiceCallback>();
                if (callback != null)
                {
                    callbacks.TryAdd(callback, callback);
                }
            }

        }

        public void UnRegister()
        {
            if (OperationContext.Current != null)
            {
                IFinSysServiceCallback callback =
                    OperationContext.Current.GetCallbackChannel<IFinSysServiceCallback>();
                if (callback != null)
                {
                    IFinSysServiceCallback callbackOut;
                    callbacks.TryRemove(callback, out callbackOut);
                }
            }
        }

        private void UpdateNotify()
        {
            if (callbacks != null)
            {
                callbacks.Values.All((c) =>
                {
                    c.DataUpdated();
                    return true;
                });
            }
        }
    }
}
