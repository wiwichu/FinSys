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
        void AddOrUpdate(Position position);

        Task AddOrUpdateAsync(Position position);
        Task<List<Position>> GetPositionsAsync();
    }
}
