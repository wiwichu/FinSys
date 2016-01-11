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
    public class CashFlowViewModel : NotifyPropertyChanged
    {
        DialogService dialogService = new DialogService();

        public CashFlowViewModel()
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
            this.YieldDayCount = new ObservableCollection<string>();
            this.YieldFrequency = new ObservableCollection<string>();
            this.YieldMethod = new ObservableCollection<string>();
            this.RateCurves = new ObservableCollection<RateCurve>();
            ValueDate = DateTime.Today;
            this.CashFlows = new ObservableCollection<CashFlow>();
        }
        public CashFlowViewModel(ObservableCollection<CashFlow> cashFlowList,DateTime valueDateArg)
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
            this.YieldDayCount = new ObservableCollection<string>();
            this.YieldFrequency = new ObservableCollection<string>();
            this.YieldMethod = new ObservableCollection<string>();
            this.RateCurves = new ObservableCollection<RateCurve>();
            ValueDate = valueDateArg;
            cashFlows = cashFlowList;
            Initialize();
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

        public ICommand CalculateCommand
        {
            get;
            set;
        }


        private void Initialize()
        {
            CashFlows = cashFlows;
            YieldDayCount = new ObservableCollection<string>(RepositoryFactory.Calculator.GetDayCountsAsync().Result);
            if (YieldDayCount.Count > 0)
            {
                SelectedYieldDayCount = yieldDayCount[(int)day_counts.date_act_actISDA_day_count];
            }
            YieldFrequency = new ObservableCollection<string>(RepositoryFactory.Calculator.GetPayFreqsAsync().Result);
            if (YieldFrequency.Count > 0)
            {
                SelectedYieldFrequency = yieldFrequency[(int)frequency.frequency_annually];
            }
            YieldMethod = new ObservableCollection<string>(RepositoryFactory.Calculator.GetYieldMethodsAsync().Result.Where((c) => c != "MBS"));
            if (YieldMethod.Count > 0)
            {
                SelectedYieldMethod = yieldMethod[(int)yield_method.py_ty_yield_meth];
            }
            CalculateCommand = new RelayCommand(Calculate, CanCalculate);
        }

        private bool CanCalculate(object obj)
        {
            return true;
        }

        private async void Calculate(object obj)
        {
            try
            {

                List<CashFlow> result = await RepositoryFactory.Calculator.PriceCashFlows(
                    CashFlows.ToList(),
                    (string)selectedYieldMethod,
                    (string)selectedYieldFrequency,
                    (string)selectedYieldDayCount,
                    valueDate,
                    rateCurves.ToList()
                    );

                CashFlows = new ObservableCollection<CashFlow>( result);
            }
            catch (InvalidOperationException ex)
            {
                dialogService.ShowMessageBox(ex.Message);
                return;
            }
        }

        private ObservableCollection<CashFlow> cashFlows = new ObservableCollection<CashFlow>();
        /// <summary>
        /// 
        /// </summary>
        public ObservableCollection<CashFlow> CashFlows
        {
            get
            {
                return cashFlows;
            }
            set
            {
                cashFlows = value;
                double flows = cashFlows.Sum((c) => c.Amount);
                TotalCashflows = cashFlows.Sum((c) => c.Amount);
                PresentValue = cashFlows.Sum((c) => c.PresentValue);
                OnPropertyChanged();
            }
        }
        object selectedCashFlow;
        public object SelectedCashFlow
        {
            get
            {
                return selectedCashFlow;
            }
            set
            {
                if (selectedCashFlow != value)
                {
                    selectedCashFlow = value;
                    OnPropertyChanged();
                }
            }
        }

        private ObservableCollection<RateCurve> rateCurves = new ObservableCollection<RateCurve>();
        /// <summary>
        /// 
        /// </summary>
        public ObservableCollection<RateCurve> RateCurves
        {
            get
            {
                return rateCurves;
            }
            set
            {
                rateCurves = value;
                OnPropertyChanged();
            }
        }
        object selectedRateCurve;
        public object SelectedRateCurve
        {
            get
            {
                return selectedRateCurve;
            }
            set
            {
                if (selectedRateCurve != value)
                {
                    selectedRateCurve = value;
                    OnPropertyChanged();
                }
            }
        }
        private double presentValue;
        public double PresentValue
        {
            get
            {
                return presentValue;
            }
            set
            {
                presentValue = value;
                OnPropertyChanged();
            }
        }
        private double totalCashflows;
        public double TotalCashflows
        {
            get
            {
                return totalCashflows;
            }
            set
            {
                totalCashflows = value;
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

    }
}

