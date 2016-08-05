using FinSys.Wpf.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Model
{
    public class Holiday : NotifyPropertyChanged
    {
        private DateTime holidayDate;
        public DateTime HolidayDate
        {
            get
            {
                return holidayDate;
            }
            set
            {
                holidayDate = value;
                OnPropertyChanged();
            }
        }
    }
}
