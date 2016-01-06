using FinSys.Wpf.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Model
{
    public class CashFlow : NotifyPropertyChanged
    {
        private DateTime scheduledDate;
        public DateTime ScheduledDate
        {
            get
            {
                return scheduledDate;
            }
            set
            {
                scheduledDate = value;
                OnPropertyChanged();
            }
        }
        private double amount;
        public double Amount
        {
            get
            {
                return amount;
            }
            set
            {
                amount = value;
                OnPropertyChanged();
            }
        }
        private double presentValue;
        public double PresentValue
        {
            get
            {
                return presentValue;
            }
            set
            {
                presentValue = value;
                OnPropertyChanged();
            }
        }

        private DateTime adjustedDate;
        public DateTime AdjustedDate
        {
            get
            {
                return adjustedDate;
            }
            set
            {
                adjustedDate = value;
                OnPropertyChanged();
            }
        }
    }
}
