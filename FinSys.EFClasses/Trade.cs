using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.EFClasses
{
    public class Trade
    {
        public int Id { get; set; }
        public Portfolio Portfolio {get; set;}
        public string PortfolioId
        {get; set; }
        public string InstrumentId{get; set; }
        public double Amount{get; set; }
        public double Price{ get; set; }
        public DateTime ValueDate{ get; set; }
        public string CounterParty{get; set;}
    }
}
