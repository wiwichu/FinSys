using FinSys.Wcf.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Data
{
    interface ITradesRepository
    {
        Task<List<TradeData>> GetTradesAsync();
        Task AddOrUpdateAsync(TradeData trade);
        Task AddOrUpdateAsync(List<TradeData> trades);
        Task DeleteAsync(TradeData trade);
        Task DeleteAsync(List<TradeData> trades);
    }
}
