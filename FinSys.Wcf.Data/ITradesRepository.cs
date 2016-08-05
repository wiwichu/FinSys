using FinSys.Wcf.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Data
{
    public interface ITradesRepository
    {
        Task<IEnumerable<TradeData>> GetTradesAsync();
        Task AddOrUpdateAsync(TradeData trade);
        Task AddOrUpdateAsync(IEnumerable<TradeData> trades);
        Task DeleteAsync(TradeData trade);
        Task DeleteAsync(IEnumerable<TradeData> trades);
    }
}
