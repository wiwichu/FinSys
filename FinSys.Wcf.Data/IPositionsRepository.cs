using FinSys.Wcf.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Data
{
    public interface IPositionsRepository
    {
        Task BuildPositions(IEnumerable<TradeData> trades);
        void AddOrUpdate(PositionData positiion);
        Task AddOrUpdateAsync(PositionData position);
        Task<IEnumerable<PositionData>> GetPositionsAsync();
    }
}
