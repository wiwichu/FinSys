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
            this.CashFlows = new ObservableCollection<CashFlow>();
        }
        public CashFlowViewModel(ObservableCollection<CashFlow> cashFlowList)
        {
            if (DesignerProperties.GetIsInDesignMode(new System.Windows.DependencyObject()))
            {
                return;
            }
            cashFlows = cashFlowList;
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
                    //ChangeClass(selectedCashFlow);
                    OnPropertyChanged();
                }
            }
        }

    }
}

