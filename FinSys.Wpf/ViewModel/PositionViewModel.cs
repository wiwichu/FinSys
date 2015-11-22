using FinSys.Wpf.Helpers;
using FinSys.Wpf.Messages;
using FinSys.Wpf.Model;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using System.Windows.Input;

namespace FinSys.Wpf.ViewModel
{
    class PositionViewModel : NotifyPropertyChanged
    {

        public PositionViewModel(Position p)
        {
            this.Amount = p.Amount;
            this.InstrumentId = p.InstrumentId;
            this.PortfolioId = p.PortfolioId;
            this.Price = p.Price;
            this.Trades = new ObservableCollection<TradeViewModel>();
        }
        public ICommand ViewTradeCommand { get; set; }
        public PositionViewModel()
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
        }
        public override void RegisterWithMessenger()
        {
            UnregisterWithMessenger();
            Messenger.Default.Register<PositionUpdate>(this, (d) =>
            {
                if (Trades.Contains(LastSelectedTrade))
                {
                    SelectedTrade = LastSelectedTrade;
                    OnPropertyChanged("SelectedTrade");
                }
            });
        }

        public override void UnregisterWithMessenger()
        {
            Messenger.Default.UnRegister(this);
        }
        public override bool Equals(object obj)
        {
            PositionViewModel pos = obj as PositionViewModel;
            if (obj == BindingOperations.DisconnectedSource || obj == DependencyProperty.UnsetValue )
            {
                return base.Equals(obj);
            }
            else
            {
                return this.PortfolioId == pos.PortfolioId && this.InstrumentId == pos.InstrumentId;
            }
        }
        public bool Equals(PositionViewModel p)
        {
            PositionViewModel arg = p as PositionViewModel;
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

        public static bool operator ==(PositionViewModel p1, PositionViewModel p2)
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
        public static bool operator !=(PositionViewModel p1, PositionViewModel p2)
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
        object _SelectedTrade;
        static public object LastSelectedTrade
        {
            get;
            set;
        }
        public object SelectedTrade
        {
            get
            {
                return _SelectedTrade;
            }
            set
            {
                if (_SelectedTrade != value)
                {
                    if (value != null)
                    {
                        LastSelectedTrade = value;
                    }
                    _SelectedTrade = value;
                    OnPropertyChanged();
                }
            }
        }
        public int SelectedPositionIndex { get; set; }

    }
}
