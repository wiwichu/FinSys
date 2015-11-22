using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;
using FinSys.Wcf.Contracts;
using FinSys.Wpf.Messages;

namespace FinSys.Wpf.Helpers
{
    class Messenger : IFinSysServiceCallback
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
            public object Recipient { get { return recipient; } }
            public override bool Equals(object obj)
            {
                MessengerKey t = obj as MessengerKey;
                if (obj == BindingOperations.DisconnectedSource || obj == DependencyProperty.UnsetValue )
                {
                    return base.Equals(obj);
                }
                else
                {
                    return this.Context == t.Context && this.Recipient == t.Recipient;
                }
            }
            public bool Equals(MessengerKey t)
            {
                MessengerKey arg = t as MessengerKey;
                if (arg != null)
                {
                    return arg.Recipient == this.Recipient && arg.Context == t.Context;
                }
                else
                {
                    return base.Equals(t);
                }
            }
            public override int GetHashCode()
            {
                if (this.Context == null)
                {
                    return this.recipient.GetHashCode();
                }
                else
                {
                    return this.recipient.GetHashCode() ^ this.Context.GetHashCode();
                }
            }

            public static bool operator ==(MessengerKey t1, MessengerKey t2)
            {
                try
                {
                    return t1.Equals(t2);
                }
                catch (NullReferenceException)
                {
                    return false;
                }
            }
            public static bool operator !=(MessengerKey t1, MessengerKey t2)
            {
                try
                {
                    return !t1.Equals(t2);
                }
                catch (NullReferenceException)
                {
                    return false;
                }
            }



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
            //foreach (MessengerKey recipient in Dictionary.Keys)
            Dictionary.Keys.Where((k) => k.Context == context).All((k) =>
            {
                object callback;
                if (Dictionary.TryGetValue(k, out callback))
                {
                    Action<T> action = callback as Action<T>;
                    if (action != null)
                    {
                        action(message);
                    }
                }
                return true;
            }
            );
        }

        public void DataUpdated()
        {
            Send<DataUpdate>(new DataUpdate());
        }
    }
}
