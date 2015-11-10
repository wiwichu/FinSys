using FinSys.Wpf.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    interface ITradesRepository
    {
        Task<List<Trade>> GetTradesAsync();
        Task AddOrUpdateAsync(Trade trade);
        Task AddOrUpdateAsync(List<Trade> trades);
        Task DeleteAsync(Trade trade);
        Task DeleteAsync(List<Trade> trades);
    }
}
