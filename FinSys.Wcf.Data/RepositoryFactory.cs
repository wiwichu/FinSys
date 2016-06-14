using FinSys.Wcf.Contracts;
using System.Collections.Generic;
using System.Threading.Tasks;

namespace FinSys.Wcf.Data
{
    public static class RepositoryFactory
    {
        private static IPortfoliosRepository portfolios = null;
        private static IPositionsRepository positions = null;
        private static ITradesRepository trades = null;
        static RepositoryFactory()
        {
            portfolios = new PortfoliosRepositoryEF();
            positions = new PositionsRepositoryEF();
            trades = new TradesRepositoryEF();
            //BuildPositions();

        }
       static async public Task BuildPositions()
        {
            await BuildPositions(Trades.GetTradesAsync().Result).ConfigureAwait(false);
        }
        static async public Task BuildPositions(IEnumerable<TradeData> trades)
        {
            await Positions.BuildPositions(trades).ConfigureAwait(false);
            //Messenger.Default.Send<DataBuilt>(new DataBuilt());
        }
        public static IPositionsRepository Positions
        {
            get
            {
                return positions;
            }
        }
        public static ITradesRepository Trades
        {
            get
            {
                return trades;
            }
        }
        public static IPortfoliosRepository Portfolios
        {
            get
            {
                return portfolios;
            }
        }
    }
}
