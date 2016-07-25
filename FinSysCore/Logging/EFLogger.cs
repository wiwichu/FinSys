﻿using FinSysCore.Models;
using FinSysCore.Services;
using Microsoft.EntityFrameworkCore;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.Logging
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
                LogTime = DateTime.UtcNow.ToLocalTime(),
                Severity = Enum.GetName(typeof(LogLevel), logLevel),
                Topic = "Log"
            };
            lock(logLock)
            {
                //_context.Logs.Add(log);
                //_context.SaveChanges();
                using (FinSysContext localContext = _context)
                {
                    localContext.Logs.Add(log);
                    localContext.SaveChanges();
                }
            }
        }

        public void Log<TState>(LogLevel logLevel, EventId eventId, TState state, Exception exception, Func<TState, Exception, string> formatter)
        {
            throw new NotImplementedException();
        }

        public IDisposable BeginScope<TState>(TState state)
        {
            throw new NotImplementedException();
        }
    }
}
