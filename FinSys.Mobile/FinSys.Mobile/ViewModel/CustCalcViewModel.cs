using FinSys.Mobile.Helpers;
using FinSys.Mobile.Services;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.ViewModel
{
    public class CustCalcViewModel : NotifyPropertyChanged
    {
        public CustCalcViewModel()
        {
            Initializer();
        }
        private void Initializer()
        {
            InstrumentClasses = new ObservableCollection<string>(RepositoryFactory.Calculator.GetInstrumentClassesAsync().Result.Where((c) => c != "MBS"));
            if (instrumentClasses.Count > 0)
            {
                if (instrumentClasses.Contains("Eurobond"))
                {
                    SelectedInstrumentClass = "Eurobond";
                }
                else
                {
                    SelectedInstrumentClass = instrumentClasses[0];
                }
            }
            DayCounts = new ObservableCollection<string>(RepositoryFactory.Calculator.GetDayCountsAsync().Result);
            if (dayCounts.Count > 0)
            {
                SelectedDayCount = dayCounts[0];
            }

        }
        private ObservableCollection<string> instrumentClasses = new ObservableCollection<string>();
        public ObservableCollection<string> InstrumentClasses
        {
            get
            {
                return instrumentClasses;
            }
            set
            {
                instrumentClasses = value;
                OnPropertyChanged();
            }
        }
        object selectedInstrumentClass;
        public object SelectedInstrumentClass
        {
            get
            {
                return selectedInstrumentClass;
            }
            set
            {
                if (selectedInstrumentClass != value)
                {
                    selectedInstrumentClass = value;
                    //ChangeClass(selectedInstrumentClass);
                    OnPropertyChanged();
                }
            }
        }
        private ObservableCollection<string> dayCounts = new ObservableCollection<string>();
        public ObservableCollection<string> DayCounts
        {
            get
            {
                return dayCounts;
            }
            set
            {
                dayCounts = value;
                OnPropertyChanged();
            }
        }
        object selectedDayCount;
        public object SelectedDayCount
        {
            get
            {
                return selectedDayCount;
            }
            set
            {
                if (selectedDayCount != value)
                {
                    selectedDayCount = value;
                    //ChangeClass(selectedInstrumentClass);
                    OnPropertyChanged();
                }
            }
        }

    }
}
