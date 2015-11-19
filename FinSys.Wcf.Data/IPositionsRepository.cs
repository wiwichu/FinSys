using FinSys.Wcf.Contracts;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Data
{
    interface IPositionsRepository
    {
        Task BuildPositions(List<TradeData> trades);
        void AddOrUpdate(PositionData positiion);
        Task AddOrUpdateAsync(PositionData position);
        Task<List<PositionData>> GetPositionsAsync();
    }
}
