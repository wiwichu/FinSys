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
        private string holidayAdjust;
        public string HolidayAdjust
        {
            get
            {
                return holidayAdjust;
            }
            set
            {
                holidayAdjust = value;
                OnPropertyChanged();
            }
        }
        private DateTime maturityDate;
        public DateTime MaturityDate
        {
            get
            {
                return maturityDate;
            }
            set
            {
                maturityDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime issueDate;
        public DateTime IssueDate
        {
            get
            {
                return issueDate;
            }
            set
            {
                issueDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime firstPayDate;
        public DateTime FirstPayDate
        {
            get
            {
                return firstPayDate;
            }
            set
            {
                firstPayDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime nextToLastPayDate;
        public DateTime NextToLastPayDate
        {
            get
            {
                return nextToLastPayDate;
            }
            set
            {
                nextToLastPayDate = value;
                OnPropertyChanged();
            }
        }
        private bool endOfMonthPay;
        public bool EndOfMonthPay
        {
            get
            {
                return endOfMonthPay;
            }
            set
            {
                endOfMonthPay = value;
                OnPropertyChanged();
            }
        }
        private double interestRate;
        public double InterestRate
        {
            get
            {
                return interestRate;
            }
            set
            {
                interestRate = value;
                OnPropertyChanged();
            }
        }
    }
}

