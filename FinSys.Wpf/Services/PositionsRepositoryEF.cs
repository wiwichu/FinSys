using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;
using FinSys.EFData;

namespace FinSys.Wpf.Services
{
    class PositionsRepositoryEF : IPositionsRepository
    {
        public void AddOrUpdate(Position position)
        {
            using (var context = new FinSysContext())
            {
                var positionEF = context.Positions.Find(new object[] { position.PortfolioId, position.InstrumentId });
                if (positionEF == null)
                {
                    positionEF = new EFClasses.Position
                    {
                        Amount = position.Amount,
                        InstrumentId = position.InstrumentId,
                        PortfolioId = position.PortfolioId,
                        Price = position.Price
                    };
                    context.Positions.Add(positionEF);
                }
                else
                {
                    positionEF.Amount = position.Amount;
                    positionEF.InstrumentId = position.InstrumentId;
                    positionEF.PortfolioId = position.PortfolioId;
                    positionEF.Price = position.Price;
                }
                context.SaveChanges();

            }
        }

        public async Task AddOrUpdateAsync(Position position)
        {
            await Task.Run(() =>
            {
                AddOrUpdate(position);
            }
            )
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }
        public async Task BuildPositions(List<Trade> trades)
        {
            await Task.Run(() =>
            {
                using (var context = new FinSysContext())
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
                                EFClasses.Position posEFInit = context.Positions.Find(new object[] { currentPortfolio, currentInstrument });
                                posEFInit.Amount = 0;
                                posEFInit.Price = 0;
                                context.SaveChanges();
                               
                            }

                            EFClasses.Position posEF = context.Positions.Find(new object[] { currentPortfolio, currentInstrument });

                            double newAmount = posEF.Amount + t.Amount;
                            double newPrice = posEF.Amount * newAmount < 0
                                ? t.Price : newAmount == 0
                                    ? 0 : Math.Abs(newAmount) > Math.Abs(posEF.Amount)
                                        ? ((posEF.Amount * posEF.Price) + (t.Amount * t.Price)) / (posEF.Amount + t.Amount) : posEF.Price;
                            posEF.Amount = newAmount;
                            posEF.Price = newPrice;
                            return true;
                        });

                    context.SaveChanges();
                    return true;
                        
                }
            }).ConfigureAwait(false);
        }

        public async Task<List<Model.Position>> GetPositionsAsync()
        {
            List<Position> pos = await Task.Run(() =>
            {
               // return positions.Values.OrderBy((p) => p.PortfolioId).ThenBy((p) => p.InstrumentId).ToList();
                List<Model.Position> positions = new List<Model.Position>();
                using (var context = new FinSysContext())
                {
                    //context.Database.Log = Console.WriteLine;
                    var posEF = context.Positions.ToList();
                    foreach (var position in posEF)
                    {
                        var p = new Model.Position
                        {
                            Amount = position.Amount,
                            InstrumentId = position.InstrumentId,
                            PortfolioId = position.PortfolioId,
                            Price = position.Price
                        };
                        positions.Add(p);
                    }
                    return positions;
                }
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return pos;
        }
    }
}
