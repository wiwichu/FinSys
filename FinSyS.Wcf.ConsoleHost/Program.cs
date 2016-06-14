using FinSys.Wcf.Services;
using System;
using System.Collections.Generic;
using System.Linq;
using System.ServiceModel;
using System.Text;
using System.Threading.Tasks;

namespace FinSyS.Wcf.ConsoleHost
{
    class Program
    {
        static void Main(string[] args)
        {
            ServiceHost hostFinSysManager = new ServiceHost(typeof(FinSysManager));
            hostFinSysManager.Open();

            Console.WriteLine("Service started. Press [Enter] to exit.");
            Console.ReadLine();
            hostFinSysManager.Close();
        }
    }
}
