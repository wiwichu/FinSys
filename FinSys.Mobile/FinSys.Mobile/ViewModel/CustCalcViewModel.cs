using FinSys.Mobile.Helpers;
using FinSys.Mobile.Model;
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
