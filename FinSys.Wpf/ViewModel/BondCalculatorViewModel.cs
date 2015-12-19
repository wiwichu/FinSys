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
            this.PayFreqs = new ObservableCollection<string>();
            ValueDate = DateTime.Today;
            MaturityDate = DateTime.Today.AddYears(1);
            FirstPayDate = DateTime.Today.AddYears(1);
            IssueDate = DateTime.Today.AddYears(-1);
            NextToLastPayDate = DateTime.Today.AddYears(-1);
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
        public ICommand DefaultDatesCommand
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
            DefaultDatesCommand = new RelayCommand(DefaultDates, CanDefaultDatesClass);
        }

        private async void DefaultDates(object obj)
        {
            InstrumentClass ic = SelectedInstrumentClass as InstrumentClass;
            Instrument instrument = new Instrument
            {
                Name = "Instrument1",
                Class = ic,
                IntDayCount = (string)SelectedDayCount,
                IntPayFreq = (string)SelectedPayFreq,
                MaturityDate = maturityDate,
                IssueDate = issueDate,
                FirstPayDate = firstPayDate,
                NextToLastPayDate = nextToLastPayDate
            };
            Calculations calculations = new Calculations
            {
                ValueDate = valueDate,
                Convexity = 0,
                Duration = 0,
                Interest = 0,
                ExCoupDays = 0,
                IsExCoup = false,
                NextPayDate = maturityDate,
                PrepayModel = 0,
                PreviousPayDate = issueDate,
                PriceIn = 0,
                PriceOut = 0,
                YieldIn = 0,
                YieldOut=0,
                ServiceFee = 0,
                Pvbp = 0
            };

            Instrument instr = null;
            Calculations calcs = null;
            KeyValuePair<Instrument, Calculations> kvp = new KeyValuePair<Instrument, Calculations>(instr, calcs);
            try
            {
                //instr = await RepositoryFactory.Calculator.GetDefaultDatesAsync(instrument, ValueDate);
                kvp = await RepositoryFactory.Calculator.GetDefaultDatesAsync(instrument, calculations);
            }
            catch (InvalidOperationException ex)
            {
                dialogService.ShowMessageBox(ex.Message);
                return;
            }

            instr = kvp.Key;
            calcs = kvp.Value;

            MaturityDate = instr.MaturityDate;
            IssueDate = instr.IssueDate;
            FirstPayDate = instr.FirstPayDate;
            NextToLastPayDate = instr.NextToLastPayDate;
        }

        private bool CanDefaultDatesClass(object obj)
        {
            return true;
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
                IntDayCount = (string)SelectedDayCount,
                IntPayFreq = (string)SelectedPayFreq,
                MaturityDate = maturityDate,
                IssueDate = issueDate,
                FirstPayDate = firstPayDate,
                NextToLastPayDate = nextToLastPayDate
            };
            instruments.Add(instrument);
            try
            {
                instruments = await RepositoryFactory.Calculator.GetInstrumentDefaultsAsync(instruments);
            }
            catch (InvalidOperationException ex)
            {
                dialogService.ShowMessageBox(ex.Message);
                return;
            }
            if (instruments != null && instruments.Count >0)
            {
                Instrument instr = instruments[0];
                SelectedDayCount = instr.IntDayCount;
                SelectedPayFreq = instr.IntPayFreq;
                MaturityDate = instr.MaturityDate;
                IssueDate = instr.IssueDate;
                FirstPayDate = instr.FirstPayDate;
                NextToLastPayDate = instr.NextToLastPayDate;
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
        private bool endOfMonthPay;
        public bool EndOfMonthPay
        {
            get
            {
                return endOfMonthPay;
            }
            set
            {
                endOfMonthPay = value;
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
        private DateTime issueDate;
        public DateTime IssueDate
        {
            get
            {
                return issueDate;
            }
            set
            {
                issueDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime firstPayDate;
        public DateTime FirstPayDate
        {
            get
            {
                return firstPayDate;
            }
            set
            {
                firstPayDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime nextToLastPayDate;
        public DateTime NextToLastPayDate
        {
            get
            {
                return nextToLastPayDate;
            }
            set
            {
                nextToLastPayDate = value;
                OnPropertyChanged();
            }
        }
        private double interestRate;
        public double InterestRate
        {
            get
            {
                return interestRate;
            }
            set
            {
                interestRate = value;
                OnPropertyChanged();
            }
        }

    }
}
