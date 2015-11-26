using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Contracts
{
    [DataContract]
    public class PositionData
    {
        [DataMember]
        public string PortfolioId{ get; set; }
        [DataMember]
        public string InstrumentId{ get; set; }
        [DataMember]
        public double Amount{ get; set; }
        [DataMember]
        public double Price{get; set;}
    }
}
