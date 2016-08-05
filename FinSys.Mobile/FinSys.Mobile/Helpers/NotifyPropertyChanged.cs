using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Helpers
{
    public class NotifyPropertyChanged : INotifyPropertyChanged
    {


        public event PropertyChangedEventHandler PropertyChanged = delegate { };
        protected void OnPropertyChanged([CallerMemberName] string caller = "")
        {
            PropertyChanged(this, new PropertyChangedEventArgs(caller));
        }
    }
}
