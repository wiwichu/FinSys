using FinSys.Wpf.Helpers;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Model
{
    class Portfolio : NotifyPropertyChanged
    {
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
        private ObservableCollection<Position> positions = new ObservableCollection<Position>();
        public ObservableCollection<Position> Positions
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
    }
}
