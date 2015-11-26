using FinSys.Wpf.Helpers;
using FinSys.Wpf.Messages;
using FinSys.Wpf.Model;
using FinSys.Wpf.Services;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using System.Windows.Input;

namespace FinSys.Wpf.ViewModel
{
    class TradeViewModel : NotifyPropertyChanged
    {
        DialogService dialogService = new DialogService();
        public ICommand ViewCommand
        {
            get;
            set;
        }
        public ICommand UpdateCommand
        {
            get;
            set;
        }
        public ICommand DeleteCommand
        {
            get;
            set;
        }
        public ICommand CancelCommand
        {
            get;
            set;
        }
        public TradeViewModel(Trade t)
        {
            this.Amount = t.Amount;
            this.CounterParty = t.CounterParty;
            this.Id = t.Id;
            this.InstrumentId = t.InstrumentId;
            this.PortfolioId = t.PortfolioId;
            this.Price = t.Price;
            this.ValueDate = t.ValueDate;
            
            LoadCommands();
        }
        public override bool Equals(object obj)
        {
            TradeViewModel t = obj as TradeViewModel;
            if (obj == BindingOperations.DisconnectedSource || obj == DependencyProperty.UnsetValue )
            {
                return base.Equals(obj);
            }
            else
            {
                return this.Id == t.Id;
            }
        }
        public bool Equals(TradeViewModel t)
        {
            TradeViewModel arg = t as TradeViewModel;
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

        public static bool operator ==(TradeViewModel t1, TradeViewModel t2)
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
        public static bool operator !=(TradeViewModel t1, TradeViewModel t2)
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


        private void LoadCommands()
        {
            ViewCommand = new RelayCommand(EditTrade, CanEditTrade);
            UpdateCommand = new RelayCommand(UpdateTrade, CanUpdateTrade);
            DeleteCommand = new RelayCommand(DeleteTrade, CanDeleteTrade);
            CancelCommand = new RelayCommand(CancelTrade, CanCancelTrade);
        }

        private bool CanCancelTrade(object obj)
        {
            return true;
        }

        private void CancelTrade(object obj)
        {
            dialogService.CloseDialog();
        }

        private bool CanDeleteTrade(object obj)
        {
            return true;
        }

        private async void DeleteTrade(object obj)
        {
            await RepositoryFactory.Trades.DeleteAsync(MakeTrade(this));
            //Messenger.Default.Send<DataUpdate>(new DataUpdate());
            CancelTrade(new object());
        }

        private bool CanUpdateTrade(object obj)
        {
            return true;
        }
        public static Trade MakeTrade(TradeViewModel tvm)
        {
            Trade result = new Trade
            {
                Id = tvm.Id,
                Amount = tvm.Amount,
                PortfolioId = tvm.PortfolioId,
                Price = tvm.Price,
                CounterParty = tvm.CounterParty,
                InstrumentId = tvm.InstrumentId,
                ValueDate = tvm.ValueDate
            };
            return result;
        }
        private async void UpdateTrade(object obj)
        {
            await RepositoryFactory.Trades.AddOrUpdateAsync(MakeTrade(this));
            //Messenger.Default.Send<DataUpdate>(new DataUpdate());
            CancelTrade(new object());
        }

        private void EditTrade(object obj)
        {
            dialogService.ShowDialog(DialogService.DIALOG.TRADEEDITVIEW, this);
        }
        private bool CanEditTrade(object obj)
        {
            return true;
        }
        public TradeViewModel()
        {
            //CHECK FOR DESIGNER
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
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
