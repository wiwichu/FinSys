using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wcf.Contracts;
using FinSys.EFData;

namespace FinSys.Wcf.Data
{
    internal class TradesRepositoryEF : ITradesRepository
    {
        public async Task AddOrUpdateAsync(IEnumerable<TradeData> trades)
        {
            await Task.Run(async () =>
            {
                using (var context = new FinSysContext())
                {

                    trades
                    .Where((t) =>
                        context.Trades.Find(new object[] { t.Id }) != null)
                    .All((tr) =>
                    {
                        RepositoryFactory.Portfolios.AddOrUpdate(new PortfolioData { Id = tr.PortfolioId });
                        EFClasses.Trade trd = context.Trades.Where((tdb) => tdb.Id == tr.Id).FirstOrDefault();
                        trd.Amount = tr.Amount;
                        trd.CounterParty = tr.CounterParty;
                        trd.InstrumentId = tr.InstrumentId;
                        trd.PortfolioId = tr.PortfolioId;
                        trd.Price = tr.Price;
                        trd.ValueDate = tr.ValueDate;
                        return true;
                    });

                    trades.Where((t) =>
                    context.Trades.Find(new object[] { t.Id }) == null)
                    .All((tr) =>
                    {
                        RepositoryFactory.Portfolios.AddOrUpdate(new PortfolioData { Id = tr.PortfolioId });
                        EFClasses.Trade trd = new EFClasses.Trade
                        {
                            Amount = tr.Amount,
                            CounterParty = tr.CounterParty,
                            InstrumentId = tr.InstrumentId,
                            PortfolioId = tr.PortfolioId,
                            Price = tr.Price,
                            ValueDate = tr.ValueDate
                        };
                        context.Trades.Add(trd);
                        return true;
                    }
                    );
                    context.SaveChanges();

                }
                await RepositoryFactory.BuildPositions();

            }
            )
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task AddOrUpdateAsync(TradeData trade)
        {
            await AddOrUpdateAsync(new List<TradeData> { trade });
        }

        public async Task DeleteAsync(IEnumerable<TradeData> trades)
        {
            await Task.Run(async () =>
            {
                using (var context = new FinSysContext())
                {
                    trades.Where((t) =>
                    context.Trades.Find(new object[] { t.Id }) != null)
                    .All((tr) =>
                    {
                        EFClasses.Trade trd = context.Trades.Where((tdb) => tdb.Id == tr.Id).FirstOrDefault();
                        context.Trades.Remove(trd);
                        return true;
                    });
                    context.SaveChanges();

                }
                await RepositoryFactory.BuildPositions();
            }
            )
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public async Task DeleteAsync(TradeData trade)
        {
            await DeleteAsync(new List<TradeData> { trade });
        }

        public async Task<IEnumerable<TradeData>> GetTradesAsync()
        {
            List<TradeData> trade = await Task.Run(() =>
            {
                //return trades.Values.OrderBy((t) => t.ValueDate).ThenBy((t) => t.Id).ToList();
                List<TradeData> trades = new List<TradeData>();
                using (var context = new FinSysContext())
                {
                    //context.Database.Log = Console.WriteLine;
                    var tradesDB = context.Trades.OrderBy((t)=>t.ValueDate).OrderBy((t)=>t.Id).ToList();
                    foreach (var trd in tradesDB)
                    {
                        var p = new TradeData
                        {
                            Id = trd.Id,
                            Amount = trd.Amount,
                            CounterParty = trd.CounterParty,
                            InstrumentId = trd.InstrumentId,
                            PortfolioId = trd.PortfolioId,
                            Price = trd.Price,
                            ValueDate = trd.ValueDate
                            
                        };
                        trades.Add(p);
                    }
                    return trades;
                }
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return trade;
        }
    }
}
