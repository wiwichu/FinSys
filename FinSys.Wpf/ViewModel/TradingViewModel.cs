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
        private ObservableCollection<Portfolio> portfolios = new ObservableCollection<Portfolio>();
        private ObservableCollection<Portfolio> portPosTrade = new ObservableCollection<Portfolio>();
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
                portPosTrade = new ObservableCollection<Portfolio>(portfoliosRepo.GetPortfoliosAsync().Result);
                portPosTrade.All((o) =>
                {
                    o.Positions = new ObservableCollection<Position>(RepositoryFactory.Positions.GetPositionsAsync().Result.Where((p) =>
                    {
                        if (p.Portfolio == o.Id)
                        {
                            p.Trades = new ObservableCollection<Trade>(RepositoryFactory.Trades.GetTradesAsync().Result.Where((t) =>
                            {
                                if (p.Portfolio == t.Portfolio && p.Instrument == t.Instrument)
                                {

                                    return true;
                                }
                                else
                                {
                                    return false;
                                }
                            }));
                            return true;
                        }
                        else
                        {
                            return false;
                        }
                    }));
                    return true;
                });
                portfolios = new ObservableCollection<Portfolio>(portfoliosRepo.GetPortfoliosAsync().Result);
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
