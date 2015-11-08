using FinSys.Wpf.Model;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    interface IPositionsRepository
    {
        Task BuildPositions(List<Trade> trades);
        void AddOrUpdate(Position portfolio);

        Task AddOrUpdateAsync(Position portfolio);
        Task<List<Position>> GetPositionsAsync();
    }
}
