using FinSys.Wpf.Helpers;
using FinSys.Wpf.Messages;
using FinSys.Wpf.Model;
using FinSys.Wpf.Services;
using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;

namespace FinSys.Wpf.ViewModel
{
    class PortfolioViewModel : NotifyPropertyChanged
    {
        public PortfolioViewModel(Portfolio p)
        {
            this.Id = p.Id;
            this.Positions = new ObservableCollection<PositionViewModel>();

        }
        public PortfolioViewModel()
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
        }
        public override void RegisterWithMessenger()
        {
            UnregisterWithMessenger();
            Messenger.Default.Register<PortfolioUpdate>(this, (d) =>
            {
                LoadData();
                OnPropertyChanged("Positions");
                OnPropertyChanged("SelectedPosition");
                if (Positions.Contains(LastSelectedPosition))
                {
                    PortfolioViewModel pvm = SelectedPosition as PortfolioViewModel;
                    if (pvm != null)
                    {
                        pvm.UnregisterWithMessenger();
                    }
                    SelectedPosition = LastSelectedPosition;
                    pvm = SelectedPosition as PortfolioViewModel;
                    if (pvm != null)
                    {
                        pvm.RegisterWithMessenger();
                    }
                }
                Messenger.Default.Send<PositionUpdate>(new PositionUpdate());
            });
        }

        public override void UnregisterWithMessenger()
        {
            Messenger.Default.UnRegister(this);
        }
        public override bool Equals(object obj)
        {
            PortfolioViewModel portfolio = obj as PortfolioViewModel;
            if (obj == BindingOperations.DisconnectedSource || obj == DependencyProperty.UnsetValue )
            {
                return base.Equals(obj);
            }
            else
            {
                return this.Id == portfolio.Id;
            }
        }
        public bool Equals(PortfolioViewModel p)
        {
            PortfolioViewModel arg = p as PortfolioViewModel;
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

        public static bool operator ==(PortfolioViewModel p1, PortfolioViewModel p2)
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
        public static bool operator !=(PortfolioViewModel p1, PortfolioViewModel p2)
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
        private ObservableCollection<PositionViewModel> positions = new ObservableCollection<PositionViewModel>();
        public ObservableCollection<PositionViewModel> Positions
        {
            get
            {
                return positions;
            }
            set
            {
                positions = value;
                OnPropertyChanged();
            }
        }
        public static object LastSelectedPosition
        {
            get;
            set;
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
                    if (value != null)
                    {
                        LastSelectedPosition = value;
                    }
                    PositionViewModel pvm = _SelectedPosition as PositionViewModel;
                    if (pvm != null)

                    {
                        pvm.UnregisterWithMessenger();
                    }
                    _SelectedPosition = value;
                    pvm = _SelectedPosition as PositionViewModel;
                    if (pvm != null)

                    {
                        pvm.RegisterWithMessenger();
                    }
                    LoadData();
                    OnPropertyChanged();
                }
            }
        }
        private void LoadData()
        {
            PositionViewModel pvm = _SelectedPosition as PositionViewModel;
            if (pvm != null)
            {
                GetPositionsAsync(pvm);
            }

        }
        public int SelectedPositionIndex { get; set; }
        private async void GetPositionsAsync(PositionViewModel pvm)
        {
            Task<ObservableCollection<TradeViewModel>> t1 = Task.Run(() =>
            {
                return new ObservableCollection<TradeViewModel>(RepositoryFactory.Trades.GetTradesAsync().Result
                .Where((t) => pvm.PortfolioId == t.PortfolioId && pvm.InstrumentId == t.InstrumentId)
                    .Select((p) => new TradeViewModel(p)));
            }
            );

            pvm.Trades = await t1;
        }

    }
}
