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
            Position a1 = new Position
            {
                Portfolio = "Porta",
                Instrument = "Instr1",
                Amount = 10000,
                Price = .90
            };
            Position b1 = new Position
            {
                Portfolio = "Portb",
                Instrument = "Instr2",
                Amount = 20000,
                Price = 1.10
            };
            Position a2 = new Position
            {
                Portfolio = "Porta",
                Instrument = "Instr2",
                Amount = 10000,
                Price = .90
            };
            Position b2 = new Position
            {
                Portfolio = "Portb",
                Instrument = "Instr1",
                Amount = 20000,
                Price = 1.10
            };
            Position a3 = new Position
            {
                Portfolio = "Porta",
                Instrument = "Instr3",
                Amount = 10000,
                Price = .90
            };
            Position b3 = new Position
            {
                Portfolio = "Portb",
                Instrument = "Instr3",
                Amount = 20000,
                Price = 1.10
            };
            Position a4 = new Position
            {
                Portfolio = "Porta",
                Instrument = "Instr4",
                Amount = 10000,
                Price = .90
            };
            Position b4 = new Position
            {
                Portfolio = "Portb",
                Instrument = "Instr4",
                Amount = 20000,
                Price = 1.10
            };
            Position a5 = new Position
            {
                Portfolio = "Porta",
                Instrument = "Instr5",
                Amount = 10000,
                Price = .90
            };
            Position b5 = new Position
            {
                Portfolio = "Portb",
                Instrument = "Instr5",
                Amount = 20000,
                Price = 1.10
            };
            positions.Add(a1);
            positions.Add(b1);
            positions.Add(a2);
            positions.Add(b2);
            positions.Add(a3);
            positions.Add(b3);
            positions.Add(a4);
            positions.Add(b4);
            positions.Add(a5);
            positions.Add(b5);

        }
        public async Task<List<Position>> GetPositionsAsync()
        {
            List<Position> pos = await Task.Run(() =>
            {
                return positions;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return pos;
        }
    }
}
