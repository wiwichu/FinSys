using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;
using System.Collections.Concurrent;

namespace FinSys.Wpf.Services
{
    class PositionsRepository : IPositionsRepository
    {
        //static List<Position> positions = new List<Position>();
        static ConcurrentDictionary<Position, int> positions = new ConcurrentDictionary<Position, int>();
        public async Task BuildPositions(List<Trade> trades)
        {
            await Task.Run(() =>
            {
                lock (Repositories.repositoryLock)
                {
                    string currentPortfolio = null;
                    string currentInstrument = null;
                    trades.OrderBy((t) => t.Portfolio).ThenBy((t) => t.Instrument).ThenBy((t) => t.ValueDate).ThenBy((t) => t.Id)
                        .All((t) =>
                        {
                            if (!(t.Portfolio == currentPortfolio && t.Instrument == currentInstrument))
                            {
                                RepositoryFactory.Portfolios.AddOrUpdate(new Portfolio { Id = t.Portfolio });
                                RepositoryFactory.Positions.AddOrUpdate(new Position { Portfolio = t.Portfolio, Instrument = t.Instrument });

                                currentInstrument = t.Instrument;
                                currentPortfolio = t.Portfolio;
                                positions.Keys.Where((p) =>
                                    p.Portfolio == currentPortfolio && p.Instrument == currentInstrument
                                ).All((p) =>
                                {
                                    p.Amount = 0;
                                    p.Price = 0;
                                    return true;
                                });
                            }

                            positions.Keys.Where((p) =>
                                    p.Portfolio == currentPortfolio && p.Instrument == currentInstrument
                                ).All((p) =>
                                {
                                    double newAmount = p.Amount + t.Amount;
                                    double newPrice = p.Amount * newAmount < 0
                                        ? t.Price : newAmount == 0
                                            ? 0 : Math.Abs(newAmount) > Math.Abs(p.Amount)
                                                ? ((p.Amount * p.Price) + (t.Amount * t.Price)) / (p.Amount + t.Amount) : p.Price;
                                    p.Amount = newAmount;
                                    p.Price = newPrice;
                                    return true;
                                });

                            return true;
                        });
                }
            });
        }
        static PositionsRepository()
        {
            Initialize();
        }

        private static void Initialize()
        {
            /*
            lock(Repositories.repositoryLock)
            {
                positions.Clear();
                
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
                positions.AddOrUpdate(a1,0,(p,v)=>0);
                positions.AddOrUpdate(b1,0,(p,v)=>0);
                positions.AddOrUpdate(a2,0,(p,v)=>0);
                positions.AddOrUpdate(b2,0,(p,v)=>0);
                positions.AddOrUpdate(a3,0,(p,v)=>0);
                positions.AddOrUpdate(b3,0,(p,v)=>0);
                positions.AddOrUpdate(a4,0,(p,v)=>0);
                positions.AddOrUpdate(b4,0,(p,v)=>0);
                positions.AddOrUpdate(a5,0,(p,v)=>0);
                positions.AddOrUpdate(b5,0,(p,v)=>0);
            }
            */
        }
        public async Task AddOrUpdateAsync(Position position)
        {
            await Task.Run(() =>
            {
                positions.AddOrUpdate(position, 0, (p, v) => 0);
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;

        }
        public void AddOrUpdate(Position position)
        {
            positions.AddOrUpdate(position, 0, (p, v) => 0);
        }

        public async Task<List<Position>> GetPositionsAsync()
        {
            List<Position> pos = await Task.Run(() =>
            {
                return positions.Keys.OrderBy((p)=>p.Portfolio).ThenBy((p)=>p.Instrument).ToList();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return pos;
        }
    }
}
