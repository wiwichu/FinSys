using FinSys.Wpf.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Model
{
    public class RateCurve : NotifyPropertyChanged
    {
        private DateTime rateDate;
        public DateTime RateDate
        {
            get
            {
                return rateDate;
            }
            set
            {
                rateDate = value;
                OnPropertyChanged();
            }
        }
        private double rate;
        public double Rate
        {
            get
            {
                return rate;
            }
            set
            {
                rate = value;
                OnPropertyChanged();
            }
        }
    }
}
