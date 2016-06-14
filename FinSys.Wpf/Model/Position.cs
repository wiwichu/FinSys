using FinSys.Wpf.Helpers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Model
{
    class Position : NotifyPropertyChanged
    {
        public override bool Equals(object obj)
        {
            Position pos = obj as Position;
            if (pos == null)
            {
                return base.Equals(obj);
            }
            else
            {
                return this.PortfolioId == pos.PortfolioId && this.InstrumentId == pos.InstrumentId;
            }
        }
        public bool Equals(Position p)
        {
            Position arg = p as Position;
            if (arg != null)
            {
                return arg.PortfolioId == this.PortfolioId && arg.InstrumentId == this.InstrumentId;
            }
            else
            {
                return base.Equals(p);
            }
        }
        public override int GetHashCode()
        {
            return this.PortfolioId.GetHashCode() ^ this.InstrumentId.GetHashCode();
        }

        public static bool operator ==(Position p1, Position p2)
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
        public static bool operator !=(Position p1, Position p2)
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

    }
}
