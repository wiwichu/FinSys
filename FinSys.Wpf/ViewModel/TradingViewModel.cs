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
        public TradingViewModel()
        {
            Task< ObservableCollection < PortfolioViewModel > > t1 = Task.Run(() => // avoids blocking UI thread.
            {
                TradesRepository tp = new TradesRepository(); // initialize data
                ObservableCollection < PortfolioViewModel > pvm = new ObservableCollection<PortfolioViewModel>(
                RepositoryFactory.Portfolios.GetPortfoliosAsync().Result
                .Select((p) =>
                {
                    PortfolioViewModel portvm = new PortfolioViewModel(p);
                    portvm.Positions = new ObservableCollection<PositionViewModel>();

                    return portvm;
                    
                }).ToList());
                return pvm;
            });
            portfolios = t1.Result;
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
        private async void GetPositionsAsync(PortfolioViewModel pvm)
        {
            Task< ObservableCollection < PositionViewModel >> t1 = Task.Run(() =>
                { 
                    return new ObservableCollection<PositionViewModel>(RepositoryFactory.Positions.GetPositionsAsync().Result
                    .Where((p) => pvm.Id == p.Portfolio)
                        .Select((p) => new PositionViewModel(p)));
                }
            );

            pvm.Positions = await t1;
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
                    PortfolioViewModel pvm = _SelectedPortfolio as PortfolioViewModel;
                    if (pvm != null)
                    {
                        GetPositionsAsync(pvm);
                    }
                    OnPropertyChanged();
                }
            }
        }
        public int SelectedPortfolioIndex { get; set; }

    }
}
