using FinSys.Wpf.Helpers;
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

namespace FinSys.Wpf.ViewModel
{
    class TradingViewModel : NotifyPropertyChanged
    {
        private ObservableCollection<PortfolioViewModel> portfolios = new ObservableCollection<PortfolioViewModel>();
        //private ObservableCollection<Portfolio> portPosTrade = new ObservableCollection<Portfolio>();
        private ObservableCollection<Position> positions = new ObservableCollection<Position>();
        private ObservableCollection<Trade> trades = new ObservableCollection<Trade>();
        private IPortfoliosRepository portfoliosRepo = RepositoryFactory.Portfolios;
        private IPositionsRepository positionsRepo = RepositoryFactory.Positions;
        private ITradesRepository tradesRepo = RepositoryFactory.Trades;
        private ManualResetEvent initialized = new ManualResetEvent(false);
        public TradingViewModel()
        {
            //positions = new ObservableCollection<Position>(positionsRepo.GetPositionsAsync().Result);       
            Task.Run(() => // avoids blocking UI thread.
            {
            portfolios = new ObservableCollection<PortfolioViewModel>();
            foreach (Portfolio p in portfoliosRepo.GetPortfoliosAsync().Result)
            {
                    PortfolioViewModel portvm = new PortfolioViewModel(p);
                    portvm.Positions = new ObservableCollection<PositionViewModel>();

                    portfolios.Add(portvm);
                    foreach (Position pos in RepositoryFactory.Positions.GetPositionsAsync().Result)
                    {
                        if (pos.Portfolio == p.Id)
                        {
                            PositionViewModel pvm = new PositionViewModel(pos);
                            portvm.Positions.Add(pvm);
                            pvm.Trades = new ObservableCollection<TradeViewModel>();
                            foreach (Trade t in RepositoryFactory.Trades.GetTradesAsync().Result)
                            {
                                if (pvm.Portfolio == t.Portfolio && pvm.Instrument == t.Instrument)
                                {
                                    TradeViewModel tvm = new TradeViewModel(t);
                                    pvm.Trades.Add(tvm);
                                }
                            }
                        }
                    }
                }

                // portfolios = new ObservableCollection<Portfolio>(portfoliosRepo.GetPortfoliosAsync().Result); 
                positions = new ObservableCollection<Position>(positionsRepo.GetPositionsAsync().Result);
                trades = new ObservableCollection<Trade>(tradesRepo.GetTradesAsync().Result);
                initialized.Set();
            });     
        }
        public ObservableCollection<Position> Positions
        {
            get { return positions; }
            set
            {
                positions = value;
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
        public ObservableCollection<PortfolioViewModel> Portfolios
        {
            get { return portfolios; }
            set
            {
                portfolios = value;
                OnPropertyChanged();
            }
        }
        object _SelectedPortfolio;
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
                    _SelectedPortfolio = value;
                    OnPropertyChanged();
                }
            }
        }
        public int SelectedPortfolioIndex { get; set; }

        object _SelectedTrade;
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
                    _SelectedTrade = value;
                    OnPropertyChanged();
                }
            }
        }
        public int SelectedTradeIndex { get; set; }

    }
}
