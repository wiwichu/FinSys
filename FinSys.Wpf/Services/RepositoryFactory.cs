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
            portfolios = new PortfoliosRepository();
            positions = new PositionsRepository();
            trades = new TradesRepository();
            //BuildPositions();

        }
       static async public void BuildPositions()
        {
            try
            {
                await Positions.BuildPositions(Trades.GetTradesAsync().Result).ConfigureAwait(false);
                Messenger.Default.Send<DataBuilt>(new DataBuilt());

            }
            finally
            {
                Repositories.repositoriesInitialized.Set();
            }
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
