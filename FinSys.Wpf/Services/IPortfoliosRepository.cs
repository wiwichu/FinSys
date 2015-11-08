using FinSys.Wpf.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    interface IPortfoliosRepository
    {
        Task AddOrUpdateAsync(Portfolio portfolio);
        void AddOrUpdate(Portfolio portfolio);
        Task<List<Portfolio>> GetPortfoliosAsync();
    }
}
