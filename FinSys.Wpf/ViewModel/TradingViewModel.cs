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
    class TradingViewModel : NotifyPropertyChanged
    {
        private ObservableCollection<Position> positions = new ObservableCollection<Position>();
        private IPositionsRepository positionsRepo = RepositoryFactory.Positions;
        public TradingViewModel()
        {
            positions = new ObservableCollection<Position>(positionsRepo.GetPositionsAsync().Result);
        }
    }
}
