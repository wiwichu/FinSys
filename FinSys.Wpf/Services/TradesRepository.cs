using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;
using System.Collections.Concurrent;

namespace FinSys.Wpf.Services
{
    class TradesRepository : ITradesRepository
    {
        static int id;
        //static List<Trade> trades = new List<Trade>();
        public static ConcurrentDictionary<Trade, Trade> trades = new ConcurrentDictionary<Trade, Trade>();
        static TradesRepository()
        {
            Initialize();
            //PositionsRepository.BuildPositions(trades.Keys.ToList());
        }
        private static void Initialize()
        {
            lock (Repositories.repositoryLock)
            {
                trades.Clear();
                Trade t1 = new Trade()
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr1",
                    Amount = 5000,
                    Price = .80,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t1, t1, (t, v) => t1);
                Trade t2 = new Trade()
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr1",
                    Amount = 5000,
                    Price = 1.0,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t2,t2, (t,v)=>t2);
                Trade t3 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr2",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t3,t3, (t,v)=>t3);
                Trade t4 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr2",
                    Amount = -10000,
                    Price = 1.15,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t4,t4, (t,v)=>t4);
                Trade t5 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr2",
                    Amount = 10000,
                    Price = .89,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t5,t5, (t,v)=>t5);
                Trade t6 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr2",
                    Amount = 10000,
                    Price = .91,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t6,t6, (t,v)=>t6);
                Trade t7 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr2",
                    Amount = -10000,
                    Price = .86,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t7,t7, (t,v)=>t7);
                Trade t8 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr1",
                    Amount = 20000,
                    Price = 1.0,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t8,t8, (t,v)=>t8);
                Trade t9 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr1",
                    Amount = 20000,
                    Price = 1.20,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t9,t9, (t,v)=>t9);
                Trade t10 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr1",
                    Amount = -20000,
                    Price = 1.25,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp3"
                };
                trades.AddOrUpdate(t10,t10, (t,v)=>t10);
                Trade t11 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr3",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp4"
                };
                trades.AddOrUpdate(t11,t11, (t,v)=>t11);
                Trade t12 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr3",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t12,t12, (t,v)=>t12);
                Trade t13 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr4",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t13,t13, (t,v)=>t13);
                Trade t14 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr4",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t14,t14, (t,v)=>t14);
                Trade t15 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Porta",
                    InstrumentId = "Instr5",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t15,t15, (t,v)=>t15);
                Trade t16 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portb",
                    InstrumentId = "Instr5",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t16,t16, (t,v)=>t16);
                Trade t17 = new Trade
                {
                    Id = ++id,
                    PortfolioId = "Portx",
                    InstrumentId = "Instrx",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2x"
                };
                trades.AddOrUpdate(t17,t17, (t,v)=>t17);
            }
        }

        public async Task AddOrUpdateAsync(List<Trade> tradesArg)
        {
            await Task.Run(async () =>
            {
                tradesArg.All((trade) =>
                {
                    if (trade.Id == 0)
                    {
                        trade.Id = id++;
                    }
                    trades.AddOrUpdate(trade, trade, (t, v) => trade);
                    return true;
                }
                );
                await RepositoryFactory.BuildPositions();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task AddOrUpdateAsync(Trade trade)
        {
            await Task.Run(async () =>
            {
                if (trade.Id == 0)
                {
                    trade.Id = id++;
                }
                trades.AddOrUpdate(trade, trade, (t, v) => trade);
                await RepositoryFactory.BuildPositions();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }
        public async Task DeleteAsync(List<Trade> tradesArg)
        {
            await Task.Run(async () =>
            {
                tradesArg.All((trade) =>
                {
                    Trade val;
                    trades.TryRemove(trade, out val);
                    return true;
                }
                );
                await RepositoryFactory.BuildPositions();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task DeleteAsync(Trade trade)
        {
            await Task.Run(async () =>
            {
                Trade val;
                trades.TryRemove(trade, out val);
                await RepositoryFactory.BuildPositions();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task<List<Trade>> GetTradesAsync()
        {
            List<Trade> trade = await Task.Run(() =>
            {
                return trades.Values.OrderBy((t)=>t.ValueDate).ThenBy((t)=>t.Id).ToList();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return trade;
        }
    }
}
