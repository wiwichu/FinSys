using FinSysCore.Models;
using Microsoft.Extensions.Logging;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore.Logging
{
    public class EFLoggerProvider : ILoggerProvider
    {
        //private FinSysContext _context;
        private LogLevel _logLevel;
        public EFLoggerProvider(LogLevel logLevel
            //, FinSysContext context
            )
        {
            //_context = context;
            _logLevel = logLevel;
        }
        public ILogger CreateLogger(string categoryName)
        {
            //return new EFLogger(_context, _logLevel);
            return null;
        }

        public void Dispose()
        {
            //throw new NotImplementedException();
        }
    }
}
