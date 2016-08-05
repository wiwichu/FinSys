using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Contracts
{
    [ServiceContract(CallbackContract =typeof(IFinSysServiceCallback), Namespace ="http://www.pelesflame.com/FinSys/FinSysService")]
    public interface IFinSysService
    {
        [OperationContract]
        void Register();
        [OperationContract]
        void UnRegister();
        [OperationContract]
        void AddOrUpdatePortfolio(PortfolioData portfolio);
        [OperationContract]
        IEnumerable<PortfolioData> GetPortfolios();
        [OperationContract]
        void AddOrUpdatePosition(PositionData positiion);
        [OperationContract]
        IEnumerable<PositionData> GetPositions();
        [OperationContract]
        IEnumerable<TradeData> GetTrades();
        [OperationContract]
        void AddOrUpdateTrade(TradeData trade);
        [OperationContract]
        void AddOrUpdateTrades(IEnumerable<TradeData> trades);
        [OperationContract]
        void DeleteTrade(TradeData trade);
        [OperationContract]
        void DeleteTrades(IEnumerable<TradeData> trades);

    }
    [ServiceContract(Namespace = "http://www.pelesflame.com/FinSys/FinSysService")]
    public interface IFinSysServiceCallback
    {
        [OperationContract(IsOneWay =true)]
        void DataUpdated();
    }
}
