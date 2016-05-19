using FinSys.Mobile.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Xamarin.Forms;

namespace FinSys.Mobile.View
{
    public partial class CustCalc : ContentPage
    {
        public CustCalc()
        {
            InitializeComponent();
            BindingContext = new CustCalcViewModel();
        }
        public void OnCashFlow(object o, EventArgs e)
        {
            Navigation.PushAsync(new CashFlow());
        }
    }
}
