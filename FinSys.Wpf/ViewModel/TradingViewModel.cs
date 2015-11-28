using FinSys.Wpf.Helpers;
using FinSys.Wpf.Messages;
using FinSys.Wpf.Model;
using FinSys.Wpf.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Input;

namespace FinSys.Wpf.ViewModel
{
    class TradingViewModel : NotifyPropertyChanged
    {

        private ObservableCollection<PortfolioViewModel> portfolios = new ObservableCollection<PortfolioViewModel>();
        public TradingViewModel()
        {
            Initialize();
            RegisterWithMessenger();
        }


        private bool CanNewTrade(object obj)
        {
            return true;
        }

        async public Task Initialize()
        {
            ManualResetEvent mre = new ManualResetEvent(false);
            Task < ObservableCollection<PortfolioViewModel>> t1 = Task.Run(() => // avoids blocking UI thread.
            {
                try
                {
                    Repositories.repositoriesInitialized.WaitOne(10000);
                    ObservableCollection<PortfolioViewModel> pvm = new ObservableCollection<PortfolioViewModel>(
                    RepositoryFactory.Portfolios.GetPortfoliosAsync().Result
                    .Select((p) =>
                    {
                        PortfolioViewModel portvm = new PortfolioViewModel(p);
                        portvm.Positions = new ObservableCollection<PositionViewModel>();

                        return portvm;

                    }).ToList());
                    return pvm;
                }
                finally
                {
                    mre.Set();
                }
            });
            mre.WaitOne(20000);
            Portfolios = await t1;
        }
        public int SelectedPositionIndex { get; set; }
        public ObservableCollection<PortfolioViewModel> Portfolios
        {
            get { return portfolios; }
            set
            {
                portfolios = value;
                OnPropertyChanged();
            }
        }
        private async Task GetPositionsAsync(PortfolioViewModel pvm)
        {
            Task< ObservableCollection < PositionViewModel >> t1 = Task.Run(() =>
                { 
                    return new ObservableCollection<PositionViewModel>(RepositoryFactory.Positions.GetPositionsAsync().Result
                    .Where((p) => pvm.Id == p.PortfolioId)
                        .Select((p) => new PositionViewModel(p)));
                }
            );

            pvm.Positions = t1.Result;
        }
        object _SelectedPortfolio;
        public static object LastSelectedPortfolio
        {
            get;
            set;
        }

        public object SelectedPortfolio
        {
            get
            {
                return _SelectedPortfolio;
            }
            set
            {
                if (_SelectedPortfolio != value)
                {
                    if (value != null)
                    {
                        LastSelectedPortfolio = value;
                    }
                    PortfolioViewModel pvm = _SelectedPortfolio as PortfolioViewModel;
                    if (pvm != null)

                    {
                        pvm.UnregisterWithMessenger();
                    }
                    _SelectedPortfolio = value;
                    pvm = _SelectedPortfolio as PortfolioViewModel;
                    if (pvm != null)

                    {
                        pvm.RegisterWithMessenger();
                    }
                    LoadData();
                    OnPropertyChanged();
                }
            }
        }
        public TradeViewModel NewTradeViewModel
        {
            get
            {
                return new TradeViewModel(new Trade());
            }
        }
        public BondCalculatorViewModel NewBondCalculatorViewModel
        {
            get
            {
                return new BondCalculatorViewModel();
            }
        }

        private async Task LoadData()
        {
            PortfolioViewModel pvm = _SelectedPortfolio as PortfolioViewModel;
            if (pvm != null)
            {
                await GetPositionsAsync(pvm);
            }

        }

        public override void RegisterWithMessenger()
        {
            Messenger.Default.Register<DataUpdate>(this, async (d) =>
            {
                object selectedPortfolio = SelectedPortfolio;
                await Initialize();
                await LoadData();
                OnPropertyChanged("Portfolios");
                OnPropertyChanged("SelectedPortfolio");
                if (Portfolios.Contains(LastSelectedPortfolio))
                {
                    TradingViewModel tvm = SelectedPortfolio as TradingViewModel;
                    if (tvm != null)
                    {
                        tvm.UnregisterWithMessenger();
                    }
                    SelectedPortfolio = LastSelectedPortfolio;
                    tvm = SelectedPortfolio as TradingViewModel;
                    if (tvm != null)
                    {
                        tvm.RegisterWithMessenger();
                    }

                }
                Messenger.Default.Send<PortfolioUpdate>(new PortfolioUpdate());
            });
            Messenger.Default.Register<DataBuilt>(this, async (d) =>
            {
                object selectedPortfolio = SelectedPortfolio;
                await Initialize();
                if (Portfolios.Contains(LastSelectedPortfolio))
                {
                    SelectedPortfolio = LastSelectedPortfolio;
                    await LoadData();
                    OnPropertyChanged("SelectedPortfolio");
                    OnPropertyChanged("Portfolios");

                }
            });
        }

        public override void UnregisterWithMessenger()
        {
            Messenger.Default.UnRegister(this);
        }

        public int SelectedPortfolioIndex { get; set; }

    }
}
