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
using System.Windows.Input;

namespace FinSys.Wpf.ViewModel
{
    public class BondCalculatorViewModel : NotifyPropertyChanged
    {
        public BondCalculatorViewModel()
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
            this.InstrumentClasses = new ObservableCollection<InstrumentClass>();
            this.DayCounts = new ObservableCollection<string>();
            ValueDate = DateTime.Today;
            MaturityDate = DateTime.Today.AddYears(1);
            Initializer();
            LoadCommands();
        }

        private void Initializer()
        {
            DayCounts = new ObservableCollection<string>(RepositoryFactory.Calculator.GetDayCountsAsync().Result);
            if (DayCounts.Count > 0)
            {
                SelectedDayCount = dayCounts[0];
            }
            PayFreqs = new ObservableCollection<string>(RepositoryFactory.Calculator.GetPayFreqsAsync().Result);
            if (PayFreqs.Count > 0)
            {
                SelectedPayFreq = payFreqs[0];
            }
            InstrumentClasses = new ObservableCollection<InstrumentClass>(RepositoryFactory.Calculator.GetInstrumentClassesAsync().Result);
            if (instrumentClasses.Count>0)
            {
                SelectedInstrumentClass = instrumentClasses[0];
            }
        }
        public ICommand ChangeClassCommand
        {
            get;
            set;
        }

        public ICommand OpenWindowCommand
        {
            get;
            set;
        }
        DialogService dialogService = new DialogService();

        private void LoadCommands()
        {
            OpenWindowCommand = new RelayCommand(OpenWindow, CanOpenWindow);
            ChangeClassCommand = new RelayCommand(ChangeClass, CanChangeClass);
        }

        private bool CanChangeClass(object obj)
        {
            return true;
        }

        private async void ChangeClass(object obj)
        {
            InstrumentClass instrumentClass = obj as InstrumentClass;
            if (instrumentClass == null)
            {
                return;
            }
            List<Instrument> instruments = new List<Instrument>();
            Instrument instrument = new Instrument
            {
                Name = "Instrument1",
                Class = instrumentClass,
                IntDayCount = (string)SelectedDayCount

            };
            instruments.Add(instrument);
            instruments = await RepositoryFactory.Calculator.GetInstrumentDefaultsAsync(instruments);

            if (instruments != null && instruments.Count >0)
            {
                Instrument instr = instruments[0];
                SelectedDayCount = instr.IntDayCount;
                SelectedPayFreq = instr.IntPayFreq;
            }
        }

        private bool CanOpenWindow(object obj)
        {
            return true;
        }

        private void OpenWindow(object obj)
        {
            dialogService.ShowDialog(DialogService.DIALOG.CALCULATORVIEW, this);
        }
        private ObservableCollection<InstrumentClass> instrumentClasses = new ObservableCollection<InstrumentClass>();
        public ObservableCollection<InstrumentClass> InstrumentClasses
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
                    ChangeClass(selectedInstrumentClass);
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
                    OnPropertyChanged();
                }
            }
        }
        private ObservableCollection<string> payFreqs = new ObservableCollection<string>();
        public ObservableCollection<string> PayFreqs
        {
            get
            {
                return payFreqs;
            }
            set
            {
                payFreqs = value;
                OnPropertyChanged();
            }
        }
        object selectedPayFreq;
        public object SelectedPayFreq
        {
            get
            {
                return selectedPayFreq;
            }
            set
            {
                if (selectedPayFreq != value)
                {
                    selectedPayFreq = value;
                    OnPropertyChanged();
                }
            }
        }

        private DateTime valueDate;
        public DateTime ValueDate
        {
            get
            {
                return valueDate;
            }
            set
            {
                valueDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime maturityDate;
        public DateTime MaturityDate
        {
            get
            {
                return maturityDate;
            }
            set
            {
                maturityDate = value;
                OnPropertyChanged();
            }
        }

    }
}
