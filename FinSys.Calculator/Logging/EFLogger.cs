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
        private FinSysContext _context;
        private LogLevel _logLevel;
        public EFLogger(FinSysContext context, LogLevel logLevel)
        {
            _context = context;
            _logLevel = logLevel;
        }
        public IDisposable BeginScopeImpl(object state)
        {
            return null;
        }

        public bool IsEnabled(LogLevel logLevel)
        {
            return ((int)logLevel >= (int)this._logLevel);
        }
        private object logLock = new object();
        public void Log(LogLevel logLevel, int eventId, object state, Exception exception, Func<object, Exception, string> formatter)
        {
            Log log = new Log
            {
                User = "Guest",
                Message = formatter(state, exception),
                LogTime = DateTime.Now,
                Severity = Enum.GetName(typeof(LogLevel), logLevel),
                Topic = "Log"
            };
            _context.Logs.Add(log);
            _context.SaveChanges();
        }
    }
}
