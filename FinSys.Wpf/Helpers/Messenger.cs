using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Wpf.Helpers
{
    class Messenger
    {
        private class MessengerKey
        {
            private object recipient;
            private object context;
            public MessengerKey(object recipient, object context)
            {
                this.recipient = recipient;
                this.context = context;
            }
            public object Context { get { return context; } }

        }
        private static readonly ConcurrentDictionary<MessengerKey, object> Dictionary = new ConcurrentDictionary<MessengerKey, object>();
        private static Messenger instance = new Messenger();
        public static Messenger Default
        {
            get { return instance; }
        }
        public void Register<T>(object recipient, Action<T> action)
        {
            Register(recipient, action, null);
        }
        public void Register<T>(object recipient, Action<T> action, object context)
        {
            var key = new MessengerKey(recipient, context);
            Dictionary.TryAdd(key, action);
        }
        public void UnRegister(object recipient)
        {
            UnRegister(recipient, null);
        }
        public void UnRegister(object recipient,  object context)
        {
            object action;
            var key = new MessengerKey(recipient, context);
            Dictionary.TryRemove(key, out action);
        }
        public void Send<T>(T message)
        {
            Send(message, null);
        }

        private void Send<T>(T message, object context)
        {
            foreach (MessengerKey recipient in Dictionary.Keys)
            {
                if (recipient.Context == context)
                {
                    object callback;
                    if (Dictionary.TryGetValue(recipient,out callback))
                    {
                        Action<T> action = callback as Action<T>;
                        if (action != null)
                        {
                            action(message);
                        }
                    }
                }
            }
        }
    }
}
