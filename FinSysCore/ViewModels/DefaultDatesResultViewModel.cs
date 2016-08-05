using System;

namespace FinSysCore.ViewModels
{
    public class DefaultDatesResultViewModel
    {
        public DateTime MaturityDate { get; set; }
        public DateTime IssueDate { get; set; }
        public DateTime FirstPayDate { get; set; }
        public DateTime NextToLastPayDate { get; set; }
    }
}
