using FinSys.Wpf.Helpers;
using FinSys.Wpf.Messages;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    static class RepositoryFactory
    {
        private static IPortfoliosRepository portfolios = null;
        private static IPositionsRepository positions = null;
        private static ITradesRepository trades = null;
        static RepositoryFactory()
        {
            portfolios = new PortfoliosRepositoryWcf();
            positions = new PositionsRepositoryWcf();
            trades = new TradesRepositoryWcf();
            //BuildPositions();

        }
       static async public Task BuildPositions()
        {
            try
            {
                await BuildPositions(Trades.GetTradesAsync().Result).ConfigureAwait(false);
            }
            finally
            {
                Repositories.repositoriesInitialized.Set();
            }
        }
        static async public Task BuildPositions(List<Model.Trade> trades)
        {
            await Positions.BuildPositions(trades).ConfigureAwait(false);
            Messenger.Default.Send<DataBuilt>(new DataBuilt());
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
