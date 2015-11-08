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
        static long id;
        //static List<Trade> trades = new List<Trade>();
        public static ConcurrentDictionary<Trade, int> trades = new ConcurrentDictionary<Trade, int>();
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
                    Portfolio = "Porta",
                    Instrument = "Instr1",
                    Amount = 5000,
                    Price = .80,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t1,0, (t,v)=>0);
                Trade t2 = new Trade()
                {
                    Id = ++id,
                    Portfolio = "Porta",
                    Instrument = "Instr1",
                    Amount = 5000,
                    Price = 1.0,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t2,0, (t,v)=>0);
                Trade t3 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr2",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t3,0, (t,v)=>0);
                Trade t4 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr2",
                    Amount = -10000,
                    Price = 1.15,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t4,0, (t,v)=>0);
                Trade t5 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Porta",
                    Instrument = "Instr2",
                    Amount = 10000,
                    Price = .89,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t5,0, (t,v)=>0);
                Trade t6 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Porta",
                    Instrument = "Instr2",
                    Amount = 10000,
                    Price = .91,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t6,0, (t,v)=>0);
                Trade t7 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Porta",
                    Instrument = "Instr2",
                    Amount = -10000,
                    Price = .86,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t7,0, (t,v)=>0);
                Trade t8 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr1",
                    Amount = 20000,
                    Price = 1.0,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t8,0, (t,v)=>0);
                Trade t9 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr1",
                    Amount = 20000,
                    Price = 1.20,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp1"
                };
                trades.AddOrUpdate(t9,0, (t,v)=>0);
                Trade t10 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr1",
                    Amount = -20000,
                    Price = 1.25,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp3"
                };
                trades.AddOrUpdate(t10,0, (t,v)=>0);
                Trade t11 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Porta",
                    Instrument = "Instr3",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp4"
                };
                trades.AddOrUpdate(t11,0, (t,v)=>0);
                Trade t12 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr3",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t12,0, (t,v)=>0);
                Trade t13 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Porta",
                    Instrument = "Instr4",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t13,0, (t,v)=>0);
                Trade t14 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr4",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t14,0, (t,v)=>0);
                Trade t15 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Porta",
                    Instrument = "Instr5",
                    Amount = 10000,
                    Price = .90,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t15,0, (t,v)=>0);
                Trade t16 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portb",
                    Instrument = "Instr5",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2"
                };
                trades.AddOrUpdate(t16,0, (t,v)=>0);
                Trade t17 = new Trade
                {
                    Id = ++id,
                    Portfolio = "Portx",
                    Instrument = "Instrx",
                    Amount = 20000,
                    Price = 1.10,
                    ValueDate = DateTime.Now.Date,
                    CounterParty = "cp2x"
                };
                trades.AddOrUpdate(t17,0, (t,v)=>0);
            }
        }

        public async Task AddOrUpdate(List<Trade> trades)
        {
            await Task.Run(() =>
            {
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task AddOrUpdate(Trade trade)
        {
            await Task.Run(() =>
            {
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task<List<Trade>> GetTradesAsync()
        {
            List<Trade> trade = await Task.Run(() =>
            {
                return trades.Keys.OrderBy((t)=>t.ValueDate).ThenBy((t)=>t.Id).ToList();
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return trade;
        }
    }
}
