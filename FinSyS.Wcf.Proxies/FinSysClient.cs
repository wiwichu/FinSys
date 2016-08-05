using FinSys.Wcf.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace FinSyS.Wcf.Proxies
{
    public class FinSysClient : DuplexClientBase<IFinSysService>, IFinSysService
    {
        public FinSysClient(InstanceContext instanceContext)
            : base(instanceContext)
        {

        }
        public void Register()
        {
            Channel.Register();
        }
        public void UnRegister()
        {
            Channel.UnRegister();
        }
        public void AddOrUpdatePortfolio(PortfolioData portfolio)
        {
            Channel.AddOrUpdatePortfolio(portfolio);
        }

        public void AddOrUpdatePosition(PositionData positiion)
        {
            Channel.AddOrUpdatePosition(positiion);
        }

        public void AddOrUpdateTrade(TradeData trade)
        {
            Channel.AddOrUpdateTrade(trade);
        }

        public void AddOrUpdateTrades(IEnumerable<TradeData> trades)
        {
            Channel.AddOrUpdateTrades(trades);
        }

        public void DeleteTrade(TradeData trade)
        {
            Channel.DeleteTrade(trade);
        }

        public void DeleteTrades(IEnumerable<TradeData> trades)
        {
            Channel.DeleteTrades(trades);
        }

        public IEnumerable<PortfolioData> GetPortfolios()
        {
            return Channel.GetPortfolios();
        }

        public IEnumerable<PositionData> GetPositions()
        {
            return Channel.GetPositions();
        }

        public IEnumerable<TradeData> GetTrades()
        {
            return Channel.GetTrades();
        }
    }
}
