using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using FinSys.Wpf.Model;
using FinSyS.Wcf.Proxies;
using FinSys.Wpf.Helpers;

namespace FinSys.Wpf.Services
{
    class PositionsRepositoryWcf : IPositionsRepository
    {
        static object statLock = new object();
        static FinSysClient statProxy = null;
        public PositionsRepositoryWcf()
        {
            //lock (statLock)
            //{
            //    if (statProxy == null)
            //    {
            //        statProxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
            //        statProxy.Register();
            //    }
            //}
        }
        public void AddOrUpdate(Position position)
        {
            Wcf.Contracts.PositionData data = new Wcf.Contracts.PositionData
            {
                Amount=position.Amount,
                InstrumentId=position.InstrumentId,
                PortfolioId=position.PortfolioId,
                Price=position.Price
            };
            FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
            proxy.AddOrUpdatePosition(data);
            proxy.Close();
        }

        public async Task AddOrUpdateAsync(Position position)
        {
            await Task.Run(() =>
            {
                AddOrUpdate(position);
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
        }

        public Task BuildPositions(List<Trade> trades)
        {
            //throw new NotImplementedException();
            return null;
        }

        public async Task<List<Position>> GetPositionsAsync()
        {
            List<Model.Position> pos = await Task.Run(() =>
            {
                List<Model.Position> poss = new List<Model.Position>();

                FinSysClient proxy = new FinSysClient(new System.ServiceModel.InstanceContext(Messenger.Default));
                IEnumerable<Wcf.Contracts.PositionData> data = proxy.GetPositions();

                data.All((p) =>
                {
                    Model.Position position = new Position
                    {
                        Amount=p.Amount,
                        InstrumentId=p.InstrumentId,
                        PortfolioId=p.PortfolioId,
                        Price=p.Price
                    };
                    poss.Add(position);
                    return true;
                });

                proxy.Close();

                return poss;
            })
            .ConfigureAwait(false) //necessary on UI Thread
            ;
            return pos;
        }
    }
}
