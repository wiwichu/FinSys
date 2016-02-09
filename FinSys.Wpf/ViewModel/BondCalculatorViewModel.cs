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
        DialogService dialogService = new DialogService();

        public BondCalculatorViewModel()
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
            this.InstrumentClasses = new ObservableCollection<string>();
            this.DayCounts = new ObservableCollection<string>();
            this.PayFreqs = new ObservableCollection<string>();
            this.YieldDayCount = new ObservableCollection<string>();
            this.YieldFrequency = new ObservableCollection<string>();
            this.YieldMethod = new ObservableCollection<string>();
            ValueDate = DateTime.Today;
            MaturityDate = DateTime.Today.AddYears(1);
            FirstPayDate = DateTime.Today.AddYears(1);
            IssueDate = DateTime.Today.AddYears(-1);
            NextToLastPayDate = DateTime.Today.AddYears(-1);
            CleanPrice = 100;
            Initializer();
            LoadCommands();
            
        }

        private void Initializer()
        {
            HolidayAdjusts = new ObservableCollection<string>(RepositoryFactory.Calculator.GetHolidayAdjustAsync().Result);
            if (HolidayAdjusts.Count > 0)
            {
                SelectedHolidayAdjust = holidayAdjusts[0];
            }
            PayHolidayAdjusts = new ObservableCollection<string>(RepositoryFactory.Calculator.GetHolidayAdjustAsync().Result);
            if (PayHolidayAdjusts.Count > 0)
            {
                SelectedPayHolidayAdjust = payHolidayAdjusts[0];
            }
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
            YieldDayCount = new ObservableCollection<string>(RepositoryFactory.Calculator.GetDayCountsAsync().Result);
            if (YieldDayCount.Count > 0)
            {
                SelectedYieldDayCount = yieldDayCount[0];
            }
            YieldFrequency = new ObservableCollection<string>(RepositoryFactory.Calculator.GetPayFreqsAsync().Result);
            if (YieldFrequency.Count > 0)
            {
                SelectedYieldFrequency = yieldFrequency[0];
            }
            YieldMethod = new ObservableCollection<string>(RepositoryFactory.Calculator.GetYieldMethodsAsync().Result.Where((c) => c != "MBS"));
            if (YieldMethod.Count > 0)
            {
                SelectedYieldMethod = yieldMethod[0];
            }           InstrumentClasses = new ObservableCollection<string>(RepositoryFactory.Calculator.GetInstrumentClassesAsync().Result.Where((c) => c != "MBS"));
 
            if (instrumentClasses.Count>0)
            {
                SelectedInstrumentClass = instrumentClasses[0];
            }
            Holidays = new ObservableCollection<Holiday>();
            //Holidays.Add(new Holiday());

        }
        public ICommand CalculateCommand
        {
            get;
            set;
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

        private void LoadCommands()
        {
            OpenWindowCommand = new RelayCommand(OpenWindow, CanOpenWindow);
            ChangeClassCommand = new RelayCommand(ChangeClass, CanChangeClass);
            DefaultDatesCommand = new RelayCommand(DefaultDates, CanDefaultDatesClass);
            CalculateCommand = new RelayCommand(Calculate, CanCalculate);
            CashFlowCommand = new RelayCommand(OpenCashFlow, CanOpenCashFlow);
        }

        private bool CanCalculate(object obj)
        {
            return true;
        }

        private async void Calculate(object obj)
        {
            Instrument instrument = new Instrument
            {
                Name = "Instrument1",
                Class = (string)SelectedInstrumentClass,
                IntDayCount = (string)SelectedDayCount,
                IntPayFreq = (string)SelectedPayFreq,
                MaturityDate = maturityDate,
                IssueDate = issueDate,
                FirstPayDate = firstPayDate,
                NextToLastPayDate = nextToLastPayDate,
                EndOfMonthPay = endOfMonthPay,
                InterestRate = interestRate/100,
                HolidayAdjust = (string)SelectedHolidayAdjust
            };
            Calculations calculations = new Calculations
            {
                ValueDate = valueDate,
                Convexity = 0,
                Duration = 0,
                Interest = 0,
                ExCoupDays = 0,
                IsExCoup = IsExCoup,
                TradeFlat = TradeFlat,
                NextPayDate = maturityDate,
                PrepayModel = 0,
                PreviousPayDate = issueDate,
                PriceIn = CleanPrice/100,
                PriceOut = 0,
                YieldIn = yieldDiscount/100,
                YieldOut = 0,
                ServiceFee = 0,
                Pvbp = 0,
                PvbpConvexityAdjusted = 0,
                YieldDayCount = (string)selectedYieldDayCount,
                YieldFreq = (string)selectedYieldFrequency,
                YieldMethod = (string)selectedYieldMethod,
                CalculatePrice = calculatePrice,
                PayHolidayAdjust = (string)SelectedPayHolidayAdjust
            };

            Instrument instr = null;
            Calculations calcs = null;
            KeyValuePair<Instrument, Calculations> kvp = new KeyValuePair<Instrument, Calculations>(instr, calcs);
            try
            {
                kvp = await RepositoryFactory.Calculator.CalculateAsync(instrument, calculations,Holidays);
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
            EndOfMonthPay = instr.EndOfMonthPay;
            PreviousPayDate = calcs.PreviousPayDate.Date.ToShortDateString();
            NextPayDate = calcs.NextPayDate.Date.ToShortDateString();
            Convexity = calcs.Convexity;
            Duration = calcs.Duration;
            Pvbp = calcs.Pvbp;
            PvbpConvexityAdjusted = calcs.PvbpConvexityAdjusted ;
            Interest = calcs.Interest*100;
            ModifiedDuration = calcs.ModifiedDuration;
            if (CalculatePrice)
            {
                CleanPrice = calcs.PriceOut*100;
            }
            else
            {
                YieldDiscount = calcs.YieldOut*100;
            }
            DirtyPrice = CleanPrice + Interest;
            InterestDays = calcs.InterestDays;
            CashFlows = new ObservableCollection<CashFlow>(
                calcs.Cashflows.Select((c)=> new CashFlow
                {
                    AdjustedDate = c.AdjustedDate,
                    Amount = c.Amount,
                    PresentValue = c.PresentValue,
                    ScheduledDate = c.ScheduledDate,
                    DiscountRate = c.DiscountRate
                }));
        }

        private async void DefaultDates(object obj)
        {
            Instrument instrument = new Instrument
            {
                Name = "Instrument1",
                Class = (string)SelectedInstrumentClass,
                IntDayCount = (string)SelectedDayCount,
                IntPayFreq = (string)SelectedPayFreq,
                MaturityDate = maturityDate,
                IssueDate = issueDate,
                FirstPayDate = firstPayDate,
                NextToLastPayDate = nextToLastPayDate,
                EndOfMonthPay = endOfMonthPay,
                HolidayAdjust = (string)SelectedHolidayAdjust
            };
            Calculations calculations = new Calculations
            {
                ValueDate = valueDate,
                Convexity = 0,
                Duration = 0,
                Interest = 0,
                ExCoupDays = 0,
                IsExCoup = isExCoup,
                TradeFlat = tradeFlat,
                NextPayDate = maturityDate,
                PrepayModel = 0,
                PreviousPayDate = issueDate,
                PriceIn = 0,
                PriceOut = 0,
                YieldIn = 0,
                YieldOut=0,
                ServiceFee = 0,
                Pvbp = 0,
                PvbpConvexityAdjusted = 0,
                YieldDayCount = (string)selectedYieldDayCount,
                YieldFreq = (string)selectedYieldFrequency,
                YieldMethod = (string)selectedYieldMethod,
                PayHolidayAdjust = (string)SelectedPayHolidayAdjust
            };

            Instrument instr = null;
            Calculations calcs = null;
            KeyValuePair<Instrument, Calculations> kvp = new KeyValuePair<Instrument, Calculations>(instr, calcs);
            try
            {
                //instr = await RepositoryFactory.Calculator.GetDefaultDatesAsync(instrument, ValueDate);
                kvp = await RepositoryFactory.Calculator.GetDefaultDatesAsync(instrument, calculations,Holidays);
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
            EndOfMonthPay = instr.EndOfMonthPay;
            PreviousPayDate = calcs.PreviousPayDate.Date.ToShortDateString();
            NextPayDate = calcs.NextPayDate.Date.ToShortDateString();
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
            Instrument instrument = new Instrument
            {
                Name = "Instrument1",
                Class = (string)SelectedInstrumentClass,
                IntDayCount = (string)SelectedDayCount,
                IntPayFreq = (string)SelectedPayFreq,
                MaturityDate = maturityDate,
                IssueDate = issueDate,
                FirstPayDate = firstPayDate,
                NextToLastPayDate = nextToLastPayDate,
                EndOfMonthPay = endOfMonthPay,
                HolidayAdjust = (string)SelectedHolidayAdjust
            };
            Calculations calculations = new Calculations
            {
                ValueDate = valueDate,
                Convexity = 0,
                Duration = 0,
                Interest = 0,
                ExCoupDays = 0,
                IsExCoup = isExCoup,
                TradeFlat = tradeFlat,
                NextPayDate = maturityDate,
                PrepayModel = 0,
                PreviousPayDate = issueDate,
                PriceIn = CleanPrice / 100,
                PriceOut = 0,
                YieldIn = yieldDiscount / 100,
                YieldOut = 0,
                ServiceFee = 0,
                Pvbp = 0,
                PvbpConvexityAdjusted = 0,
                YieldDayCount = (string)selectedYieldDayCount,
                YieldFreq = (string)selectedYieldFrequency,
                YieldMethod = (string)selectedYieldMethod,
                CalculatePrice = calculatePrice,
                PayHolidayAdjust = (string)SelectedPayHolidayAdjust
            };

            Instrument instr = null;
            Calculations calcs = null;
            KeyValuePair<Instrument, Calculations> kvp = new KeyValuePair<Instrument, Calculations>(instr, calcs);
            try
            {
                kvp = await RepositoryFactory.Calculator.GetInstrumentDefaultsAsync(instrument, calculations);
            }
            catch (InvalidOperationException ex)
            {
                dialogService.ShowMessageBox(ex.Message);
                return;
            }

            instr = kvp.Key;
            calcs = kvp.Value;

            SelectedDayCount = instr.IntDayCount;
            SelectedPayFreq = instr.IntPayFreq;
            SelectedYieldDayCount = calcs.YieldDayCount;
            SelectedYieldFrequency = calcs.YieldFreq;
            SelectedYieldMethod = calcs.YieldMethod;
            EndOfMonthPay = instr.EndOfMonthPay;
            SelectedHolidayAdjust = instr.HolidayAdjust;
            SelectedPayHolidayAdjust = instr.HolidayAdjust;
        }

        private bool CanOpenWindow(object obj)
        {
            return true;
        }

        private void OpenWindow(object obj)
        {
            dialogService.ShowDialog(DialogService.DIALOG.CALCULATORVIEW, this);
        }

        private ObservableCollection<Holiday> holidays = new ObservableCollection<Holiday>();
        public ObservableCollection<Holiday> Holidays
        {
            get
            {
                return holidays;
            }
            set
            {
                holidays = value;
                OnPropertyChanged();
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
        private ObservableCollection<string> holidayAdjusts = new ObservableCollection<string>();
        public ObservableCollection<string> HolidayAdjusts
        {
            get
            {
                return holidayAdjusts;
            }
            set
            {
                holidayAdjusts = value;
                OnPropertyChanged();
            }
        }
        object selectedHolidayAdjust;
        public object SelectedHolidayAdjust
        {
            get
            {
                return selectedHolidayAdjust;
            }
            set
            {
                if (selectedHolidayAdjust != value)
                {
                    selectedHolidayAdjust = value;
                    OnPropertyChanged();
                }
            }
        }
        private ObservableCollection<string> payHolidayAdjusts = new ObservableCollection<string>();
        public ObservableCollection<string> PayHolidayAdjusts
        {
            get
            {
                return payHolidayAdjusts;
            }
            set
            {
                payHolidayAdjusts = value;
                OnPropertyChanged();
            }
        }
        object selectedPayHolidayAdjust;
        public object SelectedPayHolidayAdjust
        {
            get
            {
                return selectedPayHolidayAdjust;
            }
            set
            {
                if (selectedPayHolidayAdjust != value)
                {
                    selectedPayHolidayAdjust = value;
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
        private string previousPayDate;
        public string PreviousPayDate
        {
            get
            {
                return previousPayDate;
            }
            set
            {
                previousPayDate = value;
                OnPropertyChanged();
            }
        }
        private string nextPayDate;
        public string NextPayDate
        {
            get
            {
                return nextPayDate;
            }
            set
            {
                nextPayDate = value;
                OnPropertyChanged();
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
        private bool isExCoup;
        public bool IsExCoup
        {
            get
            {
                return isExCoup;
            }
            set
            {
                isExCoup = value;
                OnPropertyChanged();
            }
        }
        private bool tradeFlat;
        public bool TradeFlat
        {
            get
            {
                return tradeFlat;
            }
            set
            {
                tradeFlat = value;
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
        private double cleanPrice;
        public double CleanPrice
        {
            get
            {
                return cleanPrice;
            }
            set
            {
                cleanPrice = value;
                OnPropertyChanged();
            }
        }
        private double interest;
        public double Interest
        {
            get
            {
                return interest;
            }
            set
            {
                interest = value;
                OnPropertyChanged();
            }
        }
        private double dirtyPrice;
        public double DirtyPrice
        {
            get
            {
                return dirtyPrice;
            }
            set
            {
                dirtyPrice = value;
                OnPropertyChanged();
            }
        }
        private int interestDays;
        public int InterestDays
        {
            get
            {
                return interestDays;
            }
            set
            {
                interestDays = value;
                OnPropertyChanged();
            }
        }
        private double yieldDiscount;
        public double YieldDiscount
        {
            get
            {
                return yieldDiscount;
            }
            set
            {
                yieldDiscount = value;
                OnPropertyChanged();
            }
        }
        private double duration;
        public double Duration
        {
            get
            {
                return duration;
            }
            set
            {
                duration = value;
                OnPropertyChanged();
            }
        }
        private double modifiedDuration;
        public double ModifiedDuration
        {
            get
            {
                return modifiedDuration;
            }
            set
            {
                modifiedDuration = value;
                OnPropertyChanged();
            }
        }
        private double convexity;
        public double Convexity
        {
            get
            {
                return convexity;
            }
            set
            {
                convexity = value;
                OnPropertyChanged();
            }
        }
        private double pvbp;
        public double Pvbp
        {
            get
            {
                return pvbp;
            }
            set
            {
                pvbp = value;
                OnPropertyChanged();
            }
        }
        private double pvbpConvexityAdjusted;
        public double PvbpConvexityAdjusted
        {
            get
            {
                return pvbpConvexityAdjusted;
            }
            set
            {
                pvbpConvexityAdjusted = value;
                OnPropertyChanged();
            }
        }
        private bool calculatePrice;
        public bool CalculatePrice
        {
            get
            {
                return calculatePrice;
            }
            set
            {
                calculatePrice = value;
                OnPropertyChanged();
            }
        }

        private ObservableCollection<string> yieldDayCount = new ObservableCollection<string>();
        public ObservableCollection<string> YieldDayCount
        {
            get
            {
                return yieldDayCount;
            }
            set
            {
                yieldDayCount = value;
                OnPropertyChanged();
            }
        }
        object selectedYieldDayCount;
        public object SelectedYieldDayCount
        {
            get
            {
                return selectedYieldDayCount;
            }
            set
            {
                if (selectedYieldDayCount != value)
                {
                    selectedYieldDayCount = value;
                    OnPropertyChanged();
                }
            }
        }
        private ObservableCollection<string> yieldFrequency = new ObservableCollection<string>();
        public ObservableCollection<string> YieldFrequency
        {
            get
            {
                return yieldFrequency;
            }
            set
            {
                yieldFrequency = value;
                OnPropertyChanged();
            }
        }
        object selectedYieldFrequency;
        public object SelectedYieldFrequency
        {
            get
            {
                return selectedYieldFrequency;
            }
            set
            {
                if (selectedYieldFrequency != value)
                {
                    selectedYieldFrequency = value;
                    OnPropertyChanged();
                }
            }
        }

        private ObservableCollection<string> yieldMethod = new ObservableCollection<string>();
        public ObservableCollection<string> YieldMethod
        {
            get
            {
                return yieldMethod;
            }
            set
            {
                yieldMethod = value;
                OnPropertyChanged();
            }
        }
        object selectedYieldMethod;
        public object SelectedYieldMethod
        {
            get
            {
                return selectedYieldMethod;
            }
            set
            {
                if (selectedYieldMethod != value)
                {
                    selectedYieldMethod = value;
                    OnPropertyChanged();
                }
            }
        }
        public ICommand CashFlowCommand
        {
            get;
            set;
        }

        private void OpenCashFlow(object obj)
        {
            var cfm = new CashFlowViewModel(cashFlows,ValueDate);
            cfm.SelectedYieldMethod = SelectedYieldMethod;
            cfm.SelectedYieldFrequency = SelectedYieldFrequency;
            cfm.SelectedYieldDayCount = SelectedDayCount;
            dialogService.ShowDialog(DialogService.DIALOG.CASHFLOWVIEW, cfm);
        }

        private bool CanOpenCashFlow(object obj)
        {
            return true;
        }


        private ObservableCollection<CashFlow> cashFlows = new ObservableCollection<CashFlow>();
        public ObservableCollection<CashFlow> CashFlows
        {
            get
            {
                return cashFlows;
            }
            set
            {
                cashFlows = value;
                OnPropertyChanged();
            }
        }


    }
}
