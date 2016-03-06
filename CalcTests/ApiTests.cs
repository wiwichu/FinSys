using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Net.Http;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using System.Net.Http.Headers;
using System.Threading.Tasks;

namespace CalcTests
{
    [TestClass]
    public class ApiTests
    {
        const string apiBase = "http://localhost:8000";
        const string calcApi = "api/calculator/calculate";
        [TestMethod]
        public async Task ApiCalculator()
        {
            string uri = apiBase + "/" + calcApi;
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = new CalculatorViewModel
                {
                    OverrideDefaults = true,
                    InterestRate = 5,
                    MaturityDate = new DateTime(2009, 3, 20),
                    ValueDate = new DateTime(2006, 9, 10),
                    YieldIn = 5.5,
                    PriceIn = 95,
                    CalculatePrice = true,
                    DayCount = "30/360 US",
                    PayFrequency = "Semi-Annually",
                    CalcDateAdjust = "Same",
                    PayDateAdjust = "Same",
                    YieldDayCount = "30/360 US",
                    YieldFrequency = "Semi-Annually",
                    YieldMethod = "ISMA",
                    IssueDate = new DateTime(2003, 3, 20),
                    FirstPayDate = new DateTime(2004, 3, 10),
                    NextToLastDate = new DateTime(2008, 9, 10),
                    Holidays = new List<DateTime>().ToArray(),
                    IncludeCashflows = false,
                    EndOfMonth = false,
                    ExCoupon = false,
                    TradeFlat = true,
                    UseHolidays = false,
                    Id = Convert.ToString(++id)
                };

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(uri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                Assert.IsTrue(Math.Abs(98.83315770 - results[0].CleanPrice) < .0000005);
            }
        }
        [TestMethod]
        public async Task Api_BondFlatPriceFromYtmLongLastCoupon_1()
        {
            string uri = apiBase + "/" + calcApi;
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = new CalculatorViewModel
                {
                    OverrideDefaults = true,
                    InterestRate = 5,
                    MaturityDate = new DateTime(2009, 3, 20),
                    ValueDate = new DateTime(2006, 9, 10),
                    YieldIn = 5.5,
                    PriceIn = 95,
                    CalculatePrice = true,
                    DayCount = "30/360 US",
                    PayFrequency = "Semi-Annually",
                    CalcDateAdjust = "Same",
                    PayDateAdjust = "Same",
                    YieldDayCount = "30/360 US",
                    YieldFrequency = "Semi-Annually",
                    YieldMethod = "ISMA",
                    IssueDate = new DateTime(2003, 3, 20),
                    FirstPayDate = new DateTime(2004, 3, 10),
                    NextToLastDate = new DateTime(2008, 9, 10),
                    Holidays = new List<DateTime>().ToArray(),
                    IncludeCashflows = false,
                    EndOfMonth = false,
                    ExCoupon = false,
                    TradeFlat = true,
                    UseHolidays = false,
                    Id = Convert.ToString(++id)
                };

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(uri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                Assert.IsTrue(Math.Abs(98.83315770 - results[0].CleanPrice) < .0000005);
            }
        }
    }
    internal class CalculatorViewModel
    {
        public string Id { get; set; }
        [Required]
        public double InterestRate { get; set; }
        [Required]
        public DateTime MaturityDate { get; set; }
        [Required]
        public bool EndOfMonth { get; set; }
        [Required]
        public DateTime ValueDate { get; set; }
        [Required]
        public bool CalculatePrice { get; set; }
        [Required]
        public double YieldIn { get; set; }
        [Required]
        public double PriceIn { get; set; }
        [Required]
        public bool ExCoupon { get; set; }
        [Required]
        public bool TradeFlat { get; set; }
        [Required]
        public bool IncludeCashflows { get; set; }
        [Required]
        public bool UseHolidays { get; set; }
        public IEnumerable<DateTime> Holidays { get; set; }
        [Required]
        public string DayCount { get; set; }
        [Required]
        public string PayFrequency { get; set; }
        [Required]
        public string CalcDateAdjust { get; set; }
        [Required]
        public string PayDateAdjust { get; set; }
        [Required]
        public string YieldDayCount { get; set; }
        [Required]
        public string YieldFrequency { get; set; }
        [Required]
        public string YieldMethod { get; set; }
        [Required]
        public bool OverrideDefaults { get; set; }
        [Required]
        public DateTime IssueDate { get; set; }
        [Required]
        public DateTime FirstPayDate { get; set; }
        [Required]
        public DateTime NextToLastDate { get; set; }
    }
    internal class CalculatorResultViewModel
    {
        public string Id { get; set; }
        public string Status { get; set; }
        public string Message { get; set; }
        [Required]
        public double Yield { get; set; }
        [Required]
        public double CleanPrice { get; set; }
        [Required]
        public double AccruedInterest { get; set; }
        [Required]
        public int InterestDays { get; set; }
        [Required]
        public double DirtyPrice { get; set; }
        [Required]
        public DateTime PreviousPay { get; set; }
        [Required]
        public DateTime NextPay { get; set; }
        [Required]
        public double Duration { get; set; }
        [Required]
        public double ModifiedDuration { get; set; }
        [Required]
        public double Convexity { get; set; }
        [Required]
        public double Pvbp { get; set; }
        [Required]
        public double ConvexityAdjustedPvbp { get; set; }
        [Required]
        public IEnumerable<CashFlowViewModel> Cashflows { get; set; }
        [Required]
        public DateTime IssueDate { get; set; }
        [Required]
        public DateTime FirstPayDate { get; set; }
        [Required]
        public DateTime NextToLastDate { get; set; }
    }
    public class CashFlowViewModel
    {
        [Required]
        public DateTime ScheduledDate { get; set; } = DateTime.Now;
        [Required]
        public double Amount { get; set; }
        [Required]
        public double PresentValue { get; set; }
        [Required]
        public DateTime AdjustedDate { get; set; } = DateTime.Now;
        [Required]
        public double DiscountRate { get; set; }
    }

}
