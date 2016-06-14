using FinSys.Wpf.Services;
using System.Windows.Controls;

namespace FinSys.Wpf.View
{
    /// <summary>
    /// Interaction logic for TradingView.xaml
    /// </summary>
    public partial class TradingView : UserControl
    {
        public TradingView()
        {
            RepositoryFactory.BuildPositions();

            InitializeComponent();
        }
    }
}
