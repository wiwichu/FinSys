using FinSys.Wpf.Helpers;
using System;

namespace FinSys.Wpf.Model
{
    class Portfolio : NotifyPropertyChanged
    {
        public override bool Equals(object obj)
        {
            Portfolio portfolio = obj as Portfolio;
            if (portfolio == null)
            {
                return base.Equals(obj);
            }
            else
            {
                return this.Id == portfolio.Id;
            }
        }
        public bool Equals(Portfolio p)
        {
            Portfolio arg = p as Portfolio;
            if (arg != null)
            {
                return arg.Id == this.Id;
            }
            else
            {
                return base.Equals(p);
            }
        }
        public override int GetHashCode()
        {
            return this.Id.GetHashCode();
        }

        public static bool operator ==(Portfolio p1, Portfolio p2)
        {
            try
            {
                return p1.Equals(p2);
            }
            catch (NullReferenceException)
            {
                return false;
            }
        }
        public static bool operator !=(Portfolio p1, Portfolio p2)
        {
            try
            {
                return !p1.Equals(p2);
            }
            catch (NullReferenceException)
            {
                return false;
            }
        }

        private string id;
        public string Id
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
    }
}
