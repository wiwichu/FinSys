using FinSys.Wpf.Helpers;
using FinSys.Wpf.View;
using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;

namespace FinSys.Wpf.Services
{
    public class DialogService
    {
        public enum DIALOG
        {
            TRADEEDITVIEW,
            CALCULATORVIEW
        }

        private static ConcurrentDictionary<DIALOG, Window> dialogMap = new ConcurrentDictionary<DIALOG, Window>();
        private Window view = null;
        public void ShowDialog(DIALOG dialog, NotifyPropertyChanged viewModel)
        {
            switch (dialog)
            {
                case DIALOG.TRADEEDITVIEW:
                    view = new TradeEditView();
                    if (viewModel != null)
                    {
                        view.DataContext = viewModel;
                    }
                    break;
                case DIALOG.CALCULATORVIEW:
                    view = new BondCalculatorView();
                    if (viewModel != null)
                    {
                        view.DataContext = viewModel;
                    }
                    break;
            }
            view.ShowDialog();
        }
        public void CloseDialog()
        {
            if (view != null)
            {
                view.Close();
            }
        }
    }
}
