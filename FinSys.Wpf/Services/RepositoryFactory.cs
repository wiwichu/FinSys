using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    static class RepositoryFactory
    {
        public static IPositionsRepository Positions
        {
            get
            {
                return new PositionsRepository();
            }
        }
        public static ITradesRepository Trades
        {
            get
            {
                return new TradesRepository();
            }
        }
    }
}
