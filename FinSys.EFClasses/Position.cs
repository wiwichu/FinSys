using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.ComponentModel.DataAnnotations.Schema;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.EFClasses
{
    public class Position
    {
        //public int Id { get; set; }
        public Portfolio Portfolio { get; set; }
        [Key, Column(Order = 0)]
        public string PortfolioId{get; set; }
        [Key, Column(Order = 1)]
        public string InstrumentId{get; set; }
        public double Amount{ get; set; }
        public double Price{get; set; }

    }
}
