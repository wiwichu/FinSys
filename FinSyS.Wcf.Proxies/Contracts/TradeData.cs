using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Proxies.Contracts
{
    [DataContract]
    public class TradeData
    {
        [DataMember]
        public int Id{ get; set; }
        [DataMember]
        public string PortfolioId{ get; set; }
        [DataMember]
        public string InstrumentId{ get; set; }
        [DataMember]
        public double Amount{ get; set; }
        [DataMember]
        public double Price{ get; set; }
        [DataMember]
        public DateTime ValueDate{get; set;}
        [DataMember]
        public string CounterParty{get; set;}
    }
}
