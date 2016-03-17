using FinSys.Calculator.Models;
using FinSys.Calculator.Services;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Logging
{
    public class EFLogger : ILogger
    {
        private Log _log;
        private ICalculatorRepository _repository;
        private LogLevel _logLevel;
        public EFLogger(Log log, ICalculatorRepository repository, LogLevel logLevel)
        {
            _log = log;
            _repository = repository;
        }
        public IDisposable BeginScopeImpl(object state)
        {
            return null;
        }

        public bool IsEnabled(LogLevel logLevel)
        {
            return ((int)logLevel >= (int)this._logLevel);
        }

        public void Log(LogLevel logLevel, int eventId, object state, Exception exception, Func<object, Exception, string> formatter)
        {
            throw new NotImplementedException();
        }
    }
}
