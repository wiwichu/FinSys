using FinSys.Wpf.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Model
{
    public class Calculations : NotifyPropertyChanged
    {
        private DateTime valueDate;
        public DateTime ValueDate
        {
            get
            {
                return ValueDate;
            }
            set
            {
                valueDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime previousPayDate;
        public DateTime PreviousPayDate
        {
            get
            {
                return PreviousPayDate;
            }
            set
            {
                previousPayDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime nextPayDate;
        public DateTime NextPayDate
        {
            get
            {
                return NextPayDate;
            }
            set
            {
                nextPayDate = value;
                OnPropertyChanged();
            }
        }
    }
}
