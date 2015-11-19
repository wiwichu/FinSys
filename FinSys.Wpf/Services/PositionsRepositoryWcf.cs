using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;

namespace FinSys.Wpf.Services
{
    class PositionsRepositoryWcf : IPositionsRepository
    {
        public void AddOrUpdate(Position position)
        {
            throw new NotImplementedException();
        }

        public Task AddOrUpdateAsync(Position position)
        {
            throw new NotImplementedException();
        }

        public Task BuildPositions(List<Trade> trades)
        {
            throw new NotImplementedException();
        }

        public Task<List<Position>> GetPositionsAsync()
        {
            throw new NotImplementedException();
        }
    }
}
