using FinSys.Wpf.Helpers;
using System;

namespace FinSys.Wpf.Model
{

    class Trade : NotifyPropertyChanged
    {
        public Trade()
            :base()
        {
            ValueDate = DateTime.Now.Date;
        }
        public override bool Equals(object obj)
        {
            Trade t = obj as Trade;
            if (t == null)
            {
                return base.Equals(obj);
            }
            else
            {
                return this.Id == t.Id;
            }
        }
        public bool Equals(Trade t)
        {
            Trade arg = t as Trade;
            if (arg != null)
            {
                return arg.Id == this.Id;
            }
            else
            {
                return base.Equals(t);
            }
        }
        public override int GetHashCode()
        {
            return this.Id.GetHashCode();
        }

        public static bool operator ==(Trade t1, Trade t2)
        {
            try
            {
                return t1.Equals(t2);
            }
            catch (NullReferenceException)
            {
                return false;
            }
        }
        public static bool operator !=(Trade t1, Trade t2)
        {
            try
            {
                return !t1.Equals(t2);
            }
            catch (NullReferenceException)
            {
                return false;
            }
        }

        private int id;
        public int Id
        {
            get
            {
                return id;
            }
            set
            {
                id = value;
                OnPropertyChanged();
            }
        }
        private string portfolio;
        public string PortfolioId
        {
            get
            {
                return portfolio;
            }
            set
            {
                portfolio = value;
                OnPropertyChanged();
            }
        }
        private string instrument;
        public string InstrumentId
        {
            get
            {
                return instrument;
            }
            set
            {
                instrument = value;
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
        private double price;
        public double Price
        {
            get
            {
                return price;
            }
            set
            {
                price = value;
                OnPropertyChanged();
            }
        }
        private DateTime valueDate;
        public DateTime ValueDate
        {
            get
            {
                return valueDate;
            }
            set
            {
                valueDate = value;
                OnPropertyChanged();
            }
        }
        private string counterParty;
        public string CounterParty
        {
            get
            {
                return counterParty;
            }
            set
            {
                counterParty = value;
                OnPropertyChanged();
            }
        }
    }

}
