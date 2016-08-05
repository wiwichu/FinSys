using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace FinSys.Wpf.Services
{
    public static class Repositories
    {
        public static ManualResetEvent repositoriesInitialized = new ManualResetEvent(false);
        public static object repositoryLock = new object();
    }
}
