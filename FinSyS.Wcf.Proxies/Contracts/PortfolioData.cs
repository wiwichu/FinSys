using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wcf.Proxies.Contracts
{
    [DataContract]
    public class PortfolioData
    {
        [DataMember]
        public string Id { get; set; }
    }
}
