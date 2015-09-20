using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;

namespace FinSys.Wpf.Services
{
    class PositionsRepository : IPositionsRepository
    {
        static List<Position> positions = new List<Position>();
        static PositionsRepository()
        {
            Position a = new Position
            {
                Portfolio = "Porta",
                Instrument = "Instr1",
                Amount = 10000,
                Price = .90
            };
            positions.Add(a);
        }
        public async Task<List<Position>> GetPositionsAsync()
        {
            List<Position> pos = await Task.Run(() =>
            {
                return positions;
            }).ConfigureAwait(false);
            return pos;
        }
    }
}
