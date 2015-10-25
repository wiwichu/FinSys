using FinSys.Wpf.Helpers;
using FinSys.Wpf.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.ViewModel
{
    class PositionViewModel : NotifyPropertyChanged
    {
        public PositionViewModel(Position p)
        {
            this.Amount = p.Amount;
            this.Instrument = p.Instrument;
            this.Portfolio = p.Portfolio;
            this.Price = p.Price;
            this.Trades = new ObservableCollection<TradeViewModel>();
        }
        public PositionViewModel()
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
        }
        private string portfolio;
        public string Portfolio
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
        public string Instrument
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
        private ObservableCollection<TradeViewModel> trades = new ObservableCollection<TradeViewModel>();
        public ObservableCollection<TradeViewModel> Trades
        {
            get
            {
                return trades;
            }
            set
            {
                trades = value;
                OnPropertyChanged();
            }
        }
        object _SelectedPosition;
        public object SelectedPosition
        {
            get
            {
                return _SelectedPosition;
            }
            set
            {
                if (_SelectedPosition != value)
                {
                    _SelectedPosition = value;
                    OnPropertyChanged();
                }
            }
        }
        public int SelectedPositionIndex { get; set; }

    }
}
