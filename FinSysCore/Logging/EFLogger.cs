using System;
using FinSysCore.Models;
using Microsoft.Extensions.Logging;

namespace FinSysCore.Logging
{
    public class EFLogger : ILogger
    {
        //private FinSysContext _context;
        private LogLevel _logLevel;
        public EFLogger(
            //FinSysContext context, 
            LogLevel logLevel)
        {
            //_context = context;
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
        [ThreadStatic]
        static int reentrantCount = 0;
        public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception exception, Func<TState, Exception, string> formatter)
        {
            try
            {
                if(reentrantCount > 0)
                {
                    Log log1 = new Log
                    {
                        User = "Guest",
                        Message = formatter(state, exception),
                        LogTime = DateTime.UtcNow.ToLocalTime(),
                        Severity = Enum.GetName(typeof(LogLevel), logLevel),
                        Topic = "Log"
                    };
                    //EF SaveChanges will try to write to ILogger, resulting in endless recursion.
                    //This avoids it, but will also lose EF logs.
                    //A second logger to a file could be used in this case.
                    reentrantCount = 0;
                    return;
                }
                reentrantCount++;
                Log log = new Log
                {
                    User = "Guest",
                    Message = formatter(state, exception),
                    LogTime = DateTime.UtcNow.ToLocalTime(),
                    Severity = Enum.GetName(typeof(LogLevel), logLevel),
                    Topic = "Log"
                };
                //lock (_context)
                //{

                //    try
                //    {
                //        _context.Logs.Add(log);
                //        _context.SaveChanges();
                //        //using (FinSysContext localContext = _context)
                //        //{
                //        //    localContext.Logs.Add(log);
                //        //    localContext.SaveChanges();
                //        //}
                //    }
                //    catch (Exception)
                //    {
                //        //avoid reentrant logging. return to allow backup logging
                //        return;
                //    }
                //}

            }
            finally
            {
                reentrantCount = 0;
            }
        }

        public IDisposable BeginScope<TState>(TState state)
        {
            return null;
        }

        //public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception exception, Func<TState, Exception, string> formatter)
        //{
        //    throw new NotImplementedException();
        //}

        IDisposable ILogger.BeginScope<TState>(TState state)
        {
            return null;
        }
    }
}
