using System;
using System.Collections.Generic;
using System.Threading.Tasks;
using FinSys.Wpf.Model;

namespace FinSys.Wpf.Services
{
    class TradesRepositoryWcf : ITradesRepository
    {
        public Task AddOrUpdateAsync(List<Trade> trades)
        {
            throw new NotImplementedException();
        }

        public Task AddOrUpdateAsync(Trade trade)
        {
            throw new NotImplementedException();
        }

        public Task DeleteAsync(List<Trade> trades)
        {
            throw new NotImplementedException();
        }

        public Task DeleteAsync(Trade trade)
        {
            throw new NotImplementedException();
        }

        public Task<List<Trade>> GetTradesAsync()
        {
            throw new NotImplementedException();
        }
    }
}
