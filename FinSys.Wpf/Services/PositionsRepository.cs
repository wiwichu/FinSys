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
        static ConcurrentDictionary<Position, Position> positions = new ConcurrentDictionary<Position, Position>();
        public async Task BuildPositions(List<Trade> trades)
        {
            await Task.Run(() =>
            {
                lock (Repositories.repositoryLock)
                {
                    string currentPortfolio = null;
                    string currentInstrument = null;
                    trades.OrderBy((t) => t.PortfolioId).ThenBy((t) => t.InstrumentId).ThenBy((t) => t.ValueDate).ThenBy((t) => t.Id)
                        .All((t) =>
                        {
                            if (!(t.PortfolioId == currentPortfolio && t.InstrumentId == currentInstrument))
                            {
                                RepositoryFactory.Portfolios.AddOrUpdate(new Portfolio { Id = t.PortfolioId });
                                RepositoryFactory.Positions.AddOrUpdate(new Position { PortfolioId = t.PortfolioId, InstrumentId = t.InstrumentId });

                                currentInstrument = t.InstrumentId;
                                currentPortfolio = t.PortfolioId;
                                positions.Keys.Where((p) =>
                                    p.PortfolioId == currentPortfolio && p.InstrumentId == currentInstrument
                                ).All((p) =>
                                {
                                    p.Amount = 0;
                                    p.Price = 0;
                                    return true;
                                });
                            }

                            positions.Values.Where((p) =>
                                    p.PortfolioId == currentPortfolio && p.InstrumentId == currentInstrument
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
            }).ConfigureAwait(false);
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
                positions.AddOrUpdate(position, position, (p, v) => position);
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;

        }
        public void AddOrUpdate(Position position)
        {
            positions.AddOrUpdate(position, position, (p, v) => position);
        }

        public async Task<List<Position>> GetPositionsAsync()
        {
            List<Position> pos = await Task.Run(() =>
            {
                return positions.Values.OrderBy((p)=>p.PortfolioId).ThenBy((p)=>p.InstrumentId).ToList();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return pos;
        }
    }
}
