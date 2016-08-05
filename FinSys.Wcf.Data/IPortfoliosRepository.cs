using FinSys.Wcf.Contracts;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace FinSys.Wcf.Data
{
    public interface IPortfoliosRepository
    {
        Task AddOrUpdateAsync(PortfolioData portfolio);
        void AddOrUpdate(PortfolioData portfolio);
        Task<List<PortfolioData>> GetPortfoliosAsync();
    }
}
