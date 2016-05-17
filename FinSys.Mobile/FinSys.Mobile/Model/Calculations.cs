using FinSys.Mobile.Helpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FinSys.Mobile.Model
{
    public class Calculations : NotifyPropertyChanged
    {
        private DateTime valueDate;
        public DateTime ValueDate
        {
            get
            {
                return valueDate;
            }
            set
            {
                valueDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime previousPayDate;
        public DateTime PreviousPayDate
        {
            get
            {
                return previousPayDate;
            }
            set
            {
                previousPayDate = value;
                OnPropertyChanged();
            }
        }
        private DateTime nextPayDate;
        public DateTime NextPayDate
        {
            get
            {
                return nextPayDate;
            }
            set
            {
                nextPayDate = value;
                OnPropertyChanged();
            }
        }
        private double interest;
        public double Interest
        {
            get
            {
                return interest;
            }
            set
            {
                interest = value;
                OnPropertyChanged();
            }
        }
        private double priceIn;
        public double PriceIn
        {
            get
            {
                return priceIn;
            }
            set
            {
                priceIn = value;
                OnPropertyChanged();
            }
        }
        private double priceOut;
        public double PriceOut
        {
            get
            {
                return priceOut;
            }
            set
            {
                priceOut = value;
                OnPropertyChanged();
            }
        }
        private double yieldIn;
        public double YieldIn
        {
            get
            {
                return yieldIn;
            }
            set
            {
                yieldIn = value;
                OnPropertyChanged();
            }
        }
        private double yieldOut;
        public double YieldOut
        {
            get
            {
                return yieldOut;
            }
            set
            {
                yieldOut = value;
                OnPropertyChanged();
            }
        }
        private double duration;
        public double Duration
        {
            get
            {
                return duration;
            }
            set
            {
                duration = value;
                OnPropertyChanged();
            }
        }
        private double modifiedDuration;
        public double ModifiedDuration
        {
            get
            {
                return modifiedDuration;
            }
            set
            {
                modifiedDuration = value;
                OnPropertyChanged();
            }
        }
        public double convexity;
        public double Convexity
        {
            get
            {
                return convexity;
            }
            set
            {
                convexity = value;
                OnPropertyChanged();
            }
        }
        private double pvbp;
        public double Pvbp
        {
            get
            {
                return pvbp;
            }
            set
            {
                pvbp = value;
                OnPropertyChanged();
            }
        }
        private string payHolidayAdjust;
        public string PayHolidayAdjust
        {
            get
            {
                return payHolidayAdjust;
            }
            set
            {
                payHolidayAdjust = value;
                OnPropertyChanged();
            }
        }
        private double pvbpConvexityAdjusted;
        public double PvbpConvexityAdjusted
        {
            get
            {
                return pvbpConvexityAdjusted;
            }
            set
            {
                pvbpConvexityAdjusted = value;
                OnPropertyChanged();
            }
        }
        private bool tradeFlat;
        public bool TradeFlat
        {
            get
            {
                return tradeFlat;
            }
            set
            {
                tradeFlat = value;
                OnPropertyChanged();
            }
        }
        private bool isExCoup;
        public bool IsExCoup
        {
            get
            {
                return isExCoup;
            }
            set
            {
                isExCoup = value;
                OnPropertyChanged();
            }
        }
        private int exCoupDays;
        public int ExCoupDays
        {
            get
            {
                return exCoupDays;
            }
            set
            {
                exCoupDays = value;
                OnPropertyChanged();
            }
        }
        private int interestDays;
        public int InterestDays
        {
            get
            {
                return interestDays;
            }
            set
            {
                interestDays = value;
                OnPropertyChanged();
            }
        }
        private double serviceFee;
        public double ServiceFee
        {
            get
            {
                return serviceFee;
            }
            set
            {
                serviceFee = value;
                OnPropertyChanged();
            }
        }
        private int prepayModel;
        public int PrepayModel
        {
            get
            {
                return prepayModel;
            }
            set
            {
                prepayModel = value;
                OnPropertyChanged();
            }
        }
        private bool calculatePrice;
        public bool CalculatePrice
        {
            get
            {
                return calculatePrice;
            }
            set
            {
                calculatePrice = value;
                OnPropertyChanged();
            }
        }
        private string yieldDayCount;
        public string YieldDayCount
        {
            get
            {
                return yieldDayCount;
            }
            set
            {
                yieldDayCount = value;
                OnPropertyChanged();
            }
        }
        private string yieldFreq;
        public string YieldFreq
        {
            get
            {
                return yieldFreq;
            }
            set
            {
                yieldFreq = value;
                OnPropertyChanged();
            }
        }
        private string yieldMethod;
        public string YieldMethod
        {
            get
            {
                return yieldMethod;
            }
            set
            {
                yieldMethod = value;
                OnPropertyChanged();
            }
        }
    }
}
