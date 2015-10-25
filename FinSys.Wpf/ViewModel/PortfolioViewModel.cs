using FinSys.Wpf.Helpers;
using FinSys.Wpf.Model;
using FinSys.Wpf.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
                    PositionViewModel pvm = _SelectedPosition as PositionViewModel;
                    if (pvm != null)
                    {
                        GetPositionsAsync(pvm);
                    }
                    OnPropertyChanged();
                }
            }
        }
        public int SelectedPositionIndex { get; set; }
        private async void GetPositionsAsync(PositionViewModel pvm)
        {
            Task<ObservableCollection<TradeViewModel>> t1 = Task.Run(() =>
            {
                return new ObservableCollection<TradeViewModel>(RepositoryFactory.Trades.GetTradesAsync().Result
                .Where((t) => pvm.Portfolio == t.Portfolio && pvm.Instrument == t.Instrument)
                    .Select((p) => new TradeViewModel(p)));
            }
            );

            pvm.Trades = await t1;
        }

    }
}
