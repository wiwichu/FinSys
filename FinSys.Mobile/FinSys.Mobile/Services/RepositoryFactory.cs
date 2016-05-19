using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Services
{
    static class RepositoryFactory
    {
        private static ICalculatorRepository calculator = null;
        static RepositoryFactory()
        {
            calculator = new CalculatorRepository();
        }
        public static ICalculatorRepository Calculator
        {
            get
            {
                return calculator;
            }
        }
    }
}
