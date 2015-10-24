using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;

namespace FinSys.Wpf.Services
{
    class TradesRepository : ITradesRepository
    {
        static List<Trade> trades = new List<Trade>();
        static TradesRepository()
        {
            Trade t1 = new Trade()
            {
                Id = "1",
                Portfolio = "Porta",
                Instrument = "Instr1",
                Amount = 5000,
                Price = .80,
                ValueDate = DateTime.Now,
                CounterParty = "cp1"
            };
            trades.Add(t1);
            Trade t2 = new Trade()
            {
                Id = "2",
                Portfolio = "Porta",
                Instrument = "Instr1",
                Amount = 5000,
                Price = 1.0,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t2);
            Trade t3 = new Trade
            {
                Id = "3",
                Portfolio = "Portb",
                Instrument = "Instr2",
                Amount = 20000,
                Price = 1.10,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t3);
            Trade t4 = new Trade
            {
                Id = "4",
                Portfolio = "Portb",
                Instrument = "Instr2",
                Amount = -10000,
                Price = 1.15,
                ValueDate = DateTime.Now,
                CounterParty = "cp1"
            };
            trades.Add(t4);
            Trade t5 = new Trade
            {
                Id = "5",
                Portfolio = "Porta",
                Instrument = "Instr2",
                Amount = 10000,
                Price = .89,
                ValueDate = DateTime.Now,
                CounterParty = "cp1"
            };
            trades.Add(t5);
            Trade t6 = new Trade
            {
                Id = "6",
                Portfolio = "Porta",
                Instrument = "Instr2",
                Amount = 10000,
                Price = .91,
                ValueDate = DateTime.Now,
                CounterParty = "cp1"
            };
            trades.Add(t6);
            Trade t7 = new Trade
            {
                Id = "7",
                Portfolio = "Porta",
                Instrument = "Instr2",
                Amount = -10000,
                Price = .86,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t7);
            Trade t8 = new Trade
            {
                Id = "8",
                Portfolio = "Portb",
                Instrument = "Instr1",
                Amount = 20000,
                Price = 1.0,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t8);
            Trade t9 = new Trade
            {
                Id = "9",
                Portfolio = "Portb",
                Instrument = "Instr1",
                Amount = 20000,
                Price = 1.20,
                ValueDate = DateTime.Now,
                CounterParty = "cp1"
            };
            trades.Add(t9);
            Trade t10 = new Trade
            {
                Id = "10",
                Portfolio = "Portb",
                Instrument = "Instr1",
                Amount = -20000,
                Price = 1.25,
                ValueDate = DateTime.Now,
                CounterParty = "cp3"
            };
            trades.Add(t10);
            Trade t11 = new Trade
            {
                Id = "11",
                Portfolio = "Porta",
                Instrument = "Instr3",
                Amount = 10000,
                Price = .90,
                ValueDate = DateTime.Now,
                CounterParty = "cp4"
            };
            trades.Add(t11);
            Trade t12 = new Trade
            {
                Id = "12",
                Portfolio = "Portb",
                Instrument = "Instr3",
                Amount = 20000,
                Price = 1.10,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t12);
            Trade t13 = new Trade
            {
                Id = "13",
                Portfolio = "Porta",
                Instrument = "Instr4",
                Amount = 10000,
                Price = .90,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t13);
            Trade t14 = new Trade
            {
                Id = "14",
                Portfolio = "Portb",
                Instrument = "Instr4",
                Amount = 20000,
                Price = 1.10,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t14);
            Trade t15 = new Trade
            {
                Id = "15",
                Portfolio = "Porta",
                Instrument = "Instr5",
                Amount = 10000,
                Price = .90,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t15);
            Trade t16 = new Trade
            {
                Id = "16",
                Portfolio = "Portb",
                Instrument = "Instr5",
                Amount = 20000,
                Price = 1.10,
                ValueDate = DateTime.Now,
                CounterParty = "cp2"
            };
            trades.Add(t16);
        }
        public async Task<List<Trade>> GetTradesAsync()
        {
            List<Trade> trade = await Task.Run(() =>
            {
                return trades;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return trade;
        }
    }
}
