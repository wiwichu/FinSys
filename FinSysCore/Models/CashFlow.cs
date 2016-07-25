﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.Models
{
    public class CashFlow
    {
        public DateTime ScheduledDate { get; set; }
        public double Amount { get; set; }
        public double PresentValue { get; set; }
        public DateTime AdjustedDate { get; set; }
        public double DiscountRate { get; set; }
    }
}
