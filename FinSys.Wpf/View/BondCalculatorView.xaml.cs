﻿using FinSys.Wpf.ViewModel;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;

namespace FinSys.Wpf.View
{
    /// <summary>
    /// Interaction logic for BondCalculator.xaml
    /// </summary>
    public partial class BondCalculatorView : Window
    {
        public BondCalculatorView()
        {
            InitializeComponent();
            Loaded += BondCalculatorView_Loaded;
        }

        private void BondCalculatorView_Loaded(object sender, RoutedEventArgs e)
        {
            BondCalculatorViewModel vm = DataContext as BondCalculatorViewModel;
            if (vm != null)
            {
                vm.DefaultDatesCommand.Execute(new object());
            }
        }
    }
}
