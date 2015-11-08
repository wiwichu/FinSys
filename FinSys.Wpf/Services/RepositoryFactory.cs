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
        private static bool built = false;
        static async public void BuildPositions()
        {
            if (!built)
            {
                built = true;
                try
                {
                    await Positions.BuildPositions(Trades.GetTradesAsync().Result);
                }
                finally
                {
                    Repositories.repositoriesInitialized.Set();
                }
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
