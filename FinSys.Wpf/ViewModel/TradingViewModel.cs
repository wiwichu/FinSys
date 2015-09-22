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
        private ObservableCollection<Position> positions = new ObservableCollection<Position>();
        private IPositionsRepository positionsRepo = RepositoryFactory.Positions;
        private ManualResetEvent initialized = new ManualResetEvent(false);
        public TradingViewModel()
        {
            //positions = new ObservableCollection<Position>(positionsRepo.GetPositionsAsync().Result);       
            Task.Run(() => // avoids blocking UI thread.
            {
                positions = new ObservableCollection<Position>(positionsRepo.GetPositionsAsync().Result);
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

    }
}
