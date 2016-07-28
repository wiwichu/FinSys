using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Net.Http;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Newtonsoft.Json;
using System.Net.Http.Headers;
using System.Threading.Tasks;
using System.Linq;
using System.Collections.Concurrent;

namespace CalcTests
{
    [TestClass]
    public class ApiTests
    {
        const string apiBase = "http://localhost:64074";
        const string calcApi = "api/calculator/calculate";
        const string calcUri = apiBase + "/" + calcApi;
        public TestContext TestContext { get; set; }
        [TestMethod]
        public async Task ApiCalculator()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                vmList.Add(BondFlatPriceFromYtmLongLastCoupon_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BondPriceFromYtmLongLastCoupon_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BondPriceFromYtmLongLastCoupon_2_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BondPriceFromYtmLongLastCoupon_3_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BondYtmFromPriceLongLastCoupon_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BondYtmFromPriceLongLastCoupon_2_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BondYtmFromPriceLongLastCoupon_3_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(Bund30360SemiPriceFromYISMA_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(Bund30360YISMAFromSemiPrice_1_Vm());

                //var badOne = DurationConvexity_1_Vm();
                //badOne.ValueDate = badOne.MaturityDate.AddYears(1);
                //vmList.Add(badOne);

                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BundAct365AnnualPriceFromYISMA_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BundAct365AnnualYISMAFromPrice_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BundAct365AnnualPriceFromMoos_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(BundAct365AnnualMoosFromPrice_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);
                vmList.Add(DurationConvexity_1_Vm());
                vmList[vmList.Count - 1].Id = Convert.ToString(++id);

                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                if (response.StatusCode == System.Net.HttpStatusCode.BadRequest
                    && responseBodyAsText.Contains("Calculation maximum of")
                    && responseBodyAsText.Contains("exceeded")
                    )
                {
                    return;
                }
                //IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = null;
                try
                {
                    var result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                    results = new List<CalculatorResultViewModel>(result);
                }
                catch (JsonSerializationException )
                {
                    string msg = "Cannot convert response to JSon. Response: " + responseBodyAsText;
                    TestContext.WriteLine(msg);
                    throw;
                }
                int resInd = 0;
                BondFlatPriceFromYtmLongLastCoupon_1_Run(results[resInd++]);
                BondPriceFromYtmLongLastCoupon_1_Run(results[resInd++]);
                BondPriceFromYtmLongLastCoupon_2_Run(results[resInd++]);
                BondPriceFromYtmLongLastCoupon_3_Run(results[resInd++]);
                BondYtmFromPriceLongLastCoupon_1_Run(results[resInd++]);
                BondYtmFromPriceLongLastCoupon_2_Run(results[resInd++]);
                BondYtmFromPriceLongLastCoupon_3_Run(results[resInd++]);
                Bund30360SemiPriceFromYISMA_1_Run(results[resInd++]);
                Bund30360YISMAFromSemiPrice_1_Run(results[resInd++]);
                BundAct365AnnualPriceFromYISMA_1_Run(results[resInd++]);
                BundAct365AnnualYISMAFromPrice_1_Run(results[resInd++]);
                BundAct365AnnualPriceFromMoos_1_Run(results[resInd++]);
                BundAct365AnnualMoosFromPrice_1_Run(results[resInd++]);
                DurationConvexity_1_Run(results[resInd++]);
            }
        }
        [TestMethod]
        public async Task Api_BondFlatPriceFromYtmLongLastCoupon_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BondFlatPriceFromYtmLongLastCoupon_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                var result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                //IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BondFlatPriceFromYtmLongLastCoupon_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BondPriceFromYtmLongLastCoupon_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BondPriceFromYtmLongLastCoupon_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BondPriceFromYtmLongLastCoupon_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BondPriceFromYtmLongLastCoupon_2()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BondPriceFromYtmLongLastCoupon_2_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BondPriceFromYtmLongLastCoupon_2_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BondPriceFromYtmLongLastCoupon_3()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BondPriceFromYtmLongLastCoupon_3_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BondPriceFromYtmLongLastCoupon_3_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BondYtmFromPriceLongLastCoupon_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BondYtmFromPriceLongLastCoupon_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BondYtmFromPriceLongLastCoupon_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BondYtmFromPriceLongLastCoupon_2()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BondYtmFromPriceLongLastCoupon_2_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BondYtmFromPriceLongLastCoupon_2_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BondYtmFromPriceLastCoupon_3()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BondPriceFromYtmLongLastCoupon_3_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BondPriceFromYtmLongLastCoupon_3_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_Bund30360SemiPriceFromYISMA_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = Bund30360SemiPriceFromYISMA_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                Bund30360SemiPriceFromYISMA_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_Bund30360YISMAFromSemiPrice_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = Bund30360YISMAFromSemiPrice_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                Bund30360YISMAFromSemiPrice_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BundAct365AnnualPriceFromYISMA_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BundAct365AnnualPriceFromYISMA_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BundAct365AnnualPriceFromYISMA_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BundAct365AnnualYISMAFromPrice_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BundAct365AnnualYISMAFromPrice_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BundAct365AnnualYISMAFromPrice_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BundAct365AnnualPriceFromMoos_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BundAct365AnnualPriceFromMoos_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BundAct365AnnualPriceFromMoos_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_BundAct365AnnualMoosFromPrice_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = BundAct365AnnualMoosFromPrice_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                BundAct365AnnualMoosFromPrice_1_Run(results[0]);
            }
        }
        [TestMethod]
        public async Task Api_DurationConvexity_1()
        {
            int id = 0;
            using (HttpClient client = new HttpClient())
            {
                List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                var cvm1 = DurationConvexity_1_Vm();
                cvm1.Id = Convert.ToString(++id);

                vmList.Add(cvm1);
                var jSon = JsonConvert.SerializeObject(vmList);
                var request = new StringContent(jSon);
                request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                var response = await client.PostAsync(calcUri, request);
                string responseBodyAsText = await response.Content.ReadAsStringAsync();
                IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                DurationConvexity_1_Run(results[0]);
            }
        }

        /// ////////////////////////////////////

        public void BondFlatPriceFromYtmLongLastCoupon_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(98.83315770 - vm.CleanPrice) < .0000005);
        }
        public CalculatorViewModel BondFlatPriceFromYtmLongLastCoupon_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class="Eurobond",
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
                UseHolidays = false
            };

        }
        public void BondPriceFromYtmLongLastCoupon_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(98.83315770 - vm.CleanPrice) < .0000005);
        }
        public CalculatorViewModel BondPriceFromYtmLongLastCoupon_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
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
                TradeFlat = false,
                UseHolidays = false
            };

        }
        public void BondPriceFromYtmLongLastCoupon_2_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(98.83416556 - vm.CleanPrice) < .0000005);
        }
        public CalculatorViewModel BondPriceFromYtmLongLastCoupon_2_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = true,
                InterestRate = 5,
                MaturityDate = new DateTime(2009, 3, 20),
                ValueDate = new DateTime(2006, 9, 11),
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
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void BondPriceFromYtmLongLastCoupon_3_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(99.882445698485 - vm.CleanPrice) < .0000005);
        }
        public CalculatorViewModel BondPriceFromYtmLongLastCoupon_3_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = true,
                InterestRate = 3.75,
                MaturityDate = new DateTime(2008, 6, 15),
                ValueDate = new DateTime(2008, 2, 7),
                YieldIn = 4.05,
                PriceIn = 95,
                CalculatePrice = true,
                DayCount = "30/360 US",
                PayFrequency = "Semi-Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "30/360 US",
                YieldFrequency = "Semi-Annually",
                YieldMethod = "ISMA",
                IssueDate = new DateTime(2005, 10, 15),
                FirstPayDate = new DateTime(2006, 10, 15),
                NextToLastDate = new DateTime(2007, 10, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void BondYtmFromPriceLongLastCoupon_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(5.5 - vm.Yield) < .0000005);
        }
        public CalculatorViewModel BondYtmFromPriceLongLastCoupon_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = true,
                InterestRate = 5,
                MaturityDate = new DateTime(2009, 3, 20),
                ValueDate = new DateTime(2006, 9, 10),
                YieldIn = 0,
                PriceIn = 98.83315770,
                CalculatePrice = false,
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
                TradeFlat = false,
                UseHolidays = false
            };

        }
        public void BondYtmFromPriceLongLastCoupon_2_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(5.5 - vm.Yield) < .0000005);
        }
        public CalculatorViewModel BondYtmFromPriceLongLastCoupon_2_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = true,
                InterestRate = 5,
                MaturityDate = new DateTime(2009, 3, 20),
                ValueDate = new DateTime(2006, 9, 11),
                YieldIn = 0,
                PriceIn = 98.83416556,
                CalculatePrice = false,
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
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void BondYtmFromPriceLongLastCoupon_3_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(4.05 - vm.Yield) < .0000005);
        }
        public CalculatorViewModel BondYtmFromPriceLongLastCoupon_3_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = true,
                InterestRate = 3.75,
                MaturityDate = new DateTime(2008, 6, 15),
                ValueDate = new DateTime(2008, 2, 7),
                YieldIn = 0,
                PriceIn = 99.882445698485,
                CalculatePrice = false,
                DayCount = "30/360 US",
                PayFrequency = "Semi-Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "30/360 US",
                YieldFrequency = "Semi-Annually",
                YieldMethod = "ISMA",
                IssueDate = new DateTime(2005, 10, 15),
                FirstPayDate = new DateTime(2006, 10, 15),
                NextToLastDate = new DateTime(2007, 10, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void Bund30360SemiPriceFromYISMA_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(102.7086 - vm.CleanPrice) < .00005);
        }
        public CalculatorViewModel Bund30360SemiPriceFromYISMA_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = false,
                InterestRate = 7,
                MaturityDate = new DateTime(2013, 11, 15),
                ValueDate = new DateTime(2010, 11, 15),
                YieldIn = 6,
                PriceIn = 100,
                CalculatePrice = true,
                DayCount = "30/360 German",
                PayFrequency = "Semi-Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "30/360 German",
                YieldFrequency = "Semi-Annually",
                YieldMethod = "ISMA",
                IssueDate = new DateTime(2005, 11, 15),
                FirstPayDate = new DateTime(2006, 11, 15),
                NextToLastDate = new DateTime(2012, 11, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void Bund30360YISMAFromSemiPrice_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(6 - vm.Yield) < .00005);
        }
        public CalculatorViewModel Bund30360YISMAFromSemiPrice_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = false,
                InterestRate = 7,
                MaturityDate = new DateTime(2013, 11, 15),
                ValueDate = new DateTime(2010, 11, 15),
                YieldIn = 6,
                PriceIn = 102.7086,
                CalculatePrice = false,
                DayCount = "30/360 German",
                PayFrequency = "Semi-Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "30/360 German",
                YieldFrequency = "Semi-Annually",
                YieldMethod = "ISMA",
                IssueDate = new DateTime(2005, 11, 15),
                FirstPayDate = new DateTime(2006, 11, 15),
                NextToLastDate = new DateTime(2012, 11, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void BundAct365AnnualPriceFromYISMA_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(103.9830 - vm.CleanPrice) < .00005);
        }
        public CalculatorViewModel BundAct365AnnualPriceFromYISMA_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = false,
                InterestRate = 7,
                MaturityDate = new DateTime(2013, 11, 15),
                ValueDate = new DateTime(2009, 2, 18),
                YieldIn = 6,
                PriceIn = 100,
                CalculatePrice = true,
                DayCount = "ACT/365",
                PayFrequency = "Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "ACT/365",
                YieldFrequency = "Annually",
                YieldMethod = "ISMA",
                IssueDate = new DateTime(2006, 11, 15),
                FirstPayDate = new DateTime(2007, 11, 15),
                NextToLastDate = new DateTime(2012, 11, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void BundAct365AnnualYISMAFromPrice_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(6 - vm.Yield) < .00005);
        }
        public CalculatorViewModel BundAct365AnnualYISMAFromPrice_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = false,
                InterestRate = 7,
                MaturityDate = new DateTime(2013, 11, 15),
                ValueDate = new DateTime(2009, 2, 18),
                YieldIn = 6,
                PriceIn = 103.9830,
                CalculatePrice = false,
                DayCount = "ACT/365",
                PayFrequency = "Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "ACT/365",
                YieldFrequency = "Annually",
                YieldMethod = "ISMA",
                IssueDate = new DateTime(2006, 11, 15),
                FirstPayDate = new DateTime(2007, 11, 15),
                NextToLastDate = new DateTime(2012, 11, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void BundAct365AnnualPriceFromMoos_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(103.9487 - vm.CleanPrice) < .00005);
        }
        public CalculatorViewModel BundAct365AnnualPriceFromMoos_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = false,
                InterestRate = 7,
                MaturityDate = new DateTime(2013, 11, 15),
                ValueDate = new DateTime(2009, 2, 18),
                YieldIn = 6,
                PriceIn = 100,
                CalculatePrice = true,
                DayCount = "ACT/365",
                PayFrequency = "Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "ACT/365",
                YieldFrequency = "Annually",
                YieldMethod = "Moosmueller",
                IssueDate = new DateTime(2006, 11, 15),
                FirstPayDate = new DateTime(2007, 11, 15),
                NextToLastDate = new DateTime(2012, 11, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void BundAct365AnnualMoosFromPrice_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(6 - vm.Yield) < .00005);
        }
        public CalculatorViewModel BundAct365AnnualMoosFromPrice_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = false,
                InterestRate = 7,
                MaturityDate = new DateTime(2013, 11, 15),
                ValueDate = new DateTime(2009, 2, 18),
                YieldIn = 6,
                PriceIn = 103.9487,
                CalculatePrice = false,
                DayCount = "ACT/365",
                PayFrequency = "Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "ACT/365",
                YieldFrequency = "Annually",
                YieldMethod = "Moosmueller",
                IssueDate = new DateTime(2006, 11, 15),
                FirstPayDate = new DateTime(2007, 11, 15),
                NextToLastDate = new DateTime(2012, 11, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public void DurationConvexity_1_Run(CalculatorResultViewModel vm)
        {
            Assert.IsTrue(Math.Abs(5.007 - vm.Duration) < .0005);
            Assert.IsTrue(Math.Abs(4.77 - vm.ModifiedDuration) < .005);
            Assert.IsTrue(Math.Abs(27.72 - vm.Convexity) < .005);
        }
        public CalculatorViewModel DurationConvexity_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = false,
                InterestRate = 6.1,
                MaturityDate = new DateTime(2014, 1, 15),
                ValueDate = new DateTime(2008, 1, 15),
                YieldIn = 10,
                PriceIn = 100,
                CalculatePrice = true,
                DayCount = "ACT/ACT(UST)",
                PayFrequency = "Semi-Annually",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "ACT/ACT(UST)",
                YieldFrequency = "Semi-Annually",
                YieldMethod = "US TBond",
                IssueDate = new DateTime(2005, 01, 15),
                FirstPayDate = new DateTime(2006, 01, 15),
                NextToLastDate = new DateTime(2013, 07, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = false,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }
        public CalculatorViewModel CalcStress_1_Vm()
        {
            return new CalculatorViewModel
            {
                Class = "Eurobond",
                OverrideDefaults = true,
                InterestRate = 7,
                MaturityDate = new DateTime(2058, 11, 15),
                ValueDate = new DateTime(2009, 2, 18),
                YieldIn = 6,
                PriceIn = 103.9830,
                CalculatePrice = false,
                DayCount = "ACT/365",
                PayFrequency = "Monthly",
                CalcDateAdjust = "Same",
                PayDateAdjust = "Same",
                YieldDayCount = "ACT/365",
                YieldFrequency = "Monthly",
                YieldMethod = "True Yield",
                IssueDate = new DateTime(2006, 11, 15),
                FirstPayDate = new DateTime(2007, 11, 15),
                NextToLastDate = new DateTime(2057, 11, 15),
                Holidays = new List<DateTime>().ToArray(),
                IncludeCashflows = true,
                EndOfMonth = false,
                ExCoupon = false,
                TradeFlat = false,
                UseHolidays = false
            };
        }

        [TestMethod]
        public async Task Api_CalcStress_1()
        {
            List<Task> tasks = new List<Task>();
            ConcurrentBag<string> statuses = new ConcurrentBag<string>();
            for (int x = 0; x < 13; x++)
            {
                tasks.Add( Task.Run(async () =>
                {
                    try
                    {
                        int id = 0;
                        using (HttpClient client = new HttpClient())
                        {
                            List<CalculatorViewModel> vmList = new List<CalculatorViewModel>();
                            for (int i = 0; i < 1; i++)
                            {
                                var cvm1 = CalcStress_1_Vm();
                                cvm1.Id = Convert.ToString(++id);

                                vmList.Add(cvm1);
                            }
                            var jSon = JsonConvert.SerializeObject(vmList);
                            var request = new StringContent(jSon);
                            request.Headers.ContentType = new MediaTypeHeaderValue("application/json");
                            var response = await client.PostAsync(calcUri, request);
                            string responseBodyAsText = await response.Content.ReadAsStringAsync();
                            if (response.StatusCode != System.Net.HttpStatusCode.OK)
                            {
                                throw new InvalidOperationException(responseBodyAsText);
                            }
                            IEnumerable<CalculatorResultViewModel> result = JsonConvert.DeserializeObject<IEnumerable<CalculatorResultViewModel>>(responseBodyAsText);
                            result.All((c) =>
                            {
                                string status = string.IsNullOrEmpty(c.Status) ? "OK" : c.Status;
                                string statusLine = $"ID:{c.Id} Status: {status}";
                            //statuses.Add(statusLine);
                            TestContext.WriteLine($"ID:{c.Id} Status: {status}");

                                return true;
                            });
                            //List<CalculatorResultViewModel> results = new List<CalculatorResultViewModel>(result);
                        }
                    }
                    catch (Exception ex)
                    {
                        TestContext.WriteLine(ex.ToString());

                    }
                }));
                
            }
            Task.WaitAll(tasks.ToArray());
            //IList<string> sList = statuses.ToList();
            //sList.All((c) =>
            //{
            //    TestContext.WriteLine(c);
            //    return true;
            //});
        }
    }
    public class CalculatorViewModel
    {
        public string Id { get; set; }
        [Required]
        public string Class { get; set; }
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
    public class CalculatorResultViewModel
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
