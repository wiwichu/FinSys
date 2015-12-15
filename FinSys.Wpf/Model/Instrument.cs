using FinSys.Wpf.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Model
{
    public class Instrument : NotifyPropertyChanged
    {
        private string name;
        public string Name
        {
            get
            {
                return name;
            }
            set
            {
                name = value;
                OnPropertyChanged();
            }
        }
        private InstrumentClass instrumentClass;
        public InstrumentClass Class
        {
            get
            {
                return instrumentClass;
            }
            set
            {
                instrumentClass = value;
                OnPropertyChanged();
            }
        }
        private string intDayCount;
        public string IntDayCount
        {
            get
            {
                return intDayCount;
            }
            set
            {
                intDayCount = value;
                OnPropertyChanged();
            }
        }
        private string intPayFreq;
        public string IntPayFreq
        {
            get
            {
                return intPayFreq;
            }
            set
            {
                intPayFreq = value;
                OnPropertyChanged();
            }
        }
    }
}

