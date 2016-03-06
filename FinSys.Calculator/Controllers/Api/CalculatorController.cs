using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNet.Mvc;
using FinSys.Calculator.Services;
using FinSys.Calculator.ViewModels;
using System.Net;
using AutoMapper;
using FinSys.Calculator.Models;
using System.Collections.Concurrent;

// For more information on enabling Web API for empty projects, visit http://go.microsoft.com/fwlink/?LinkID=397860

namespace FinSys.Calculator.Controllers.Api
{
    [Route("api/calculator")]
    public class CalculatorController : Controller
    {
        private ICalculatorRepository _repository;
        public CalculatorController(ICalculatorRepository repository)
        {
            _repository = repository;
        }
        // GET: api/values
        [HttpGet]
        public async Task<JsonResult> Get()
        {

            var instrumentClasses = await _repository.GetInstrumentClassesAsync().ConfigureAwait(false);
            var dayCounts = await _repository.GetDayCountsAsync().ConfigureAwait(false);
            var holidayAdjust = await _repository.GetHolidayAdjustAsync().ConfigureAwait(false);
            var interpolationMethods = await _repository.GetInterpolationMethodsAsync().ConfigureAwait(false);
            var payFrequency = await _repository.GetPayFreqsAsync().ConfigureAwait(false);
            var yieldMethods = await _repository.GetYieldMethodsAsync().ConfigureAwait(false);

            IDictionary<string, IEnumerable<object>> staticData = new Dictionary<string, IEnumerable<object>>();
            staticData.Add("instrumentClasses", instrumentClasses);
            staticData.Add("dayCounts", dayCounts);
            staticData.Add("holidayAdjust", holidayAdjust);
            staticData.Add("interpolationMethods", interpolationMethods);
            staticData.Add("payFrequency", payFrequency);
            staticData.Add("yieldMethods", yieldMethods);

            return Json(staticData);
        }

        // GET api/values/5
        [HttpGet("{id}")]
        public string Get(int id)
        {
            return "value";
        }

        // POST api/values
        [HttpPost("ustbill")]
        public async Task<JsonResult> Post([FromBody]USTBillViewModel vm)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    var ustb = Mapper.Map<USTBill>(vm);
                    ustb.CalcSource /= 100;
                    USTBillResultViewModel result = Mapper.Map < USTBillResultViewModel > (await _repository.USTBillCalcAsync(ustb).ConfigureAwait(false));
                    result.BondEquivalent *= 100;
                    result.Discount *= 100;
                    result.MMYield *= 100;
                    result.Price *= 100;
                    JsonResult jResult = new JsonResult(result);
                    return jResult; 
                }
            }
            catch (Exception ex)
            {
                Response.StatusCode = (int)HttpStatusCode.BadRequest;
                return Json(ex.Message);
            }
            Response.StatusCode = (int)HttpStatusCode.BadRequest;
            return Json(new { Message = "Failed", ModelState = ModelState });
        }
        [HttpPost("instrumentdefaults")]
        public async Task<JsonResult> Post([FromBody]InstrumentClassViewModel vm)
        {
            try
            {
                Instrument instr = new Instrument
                {
                    Class = vm.Class,
                    IssueDate = DateTime.Now.AddYears(-1),
                    NextToLastPayDate = DateTime.Now,
                    MaturityDate=DateTime.Now.AddYears(1),
                    FirstPayDate=DateTime.Now
                };
                Calculations calc = new Calculations
                {
                    ValueDate=DateTime.Now
                };
                var res = await _repository.GetInstrumentDefaultsAsync(instr, calc).ConfigureAwait(false);
                Instrument instrResult = res.Key;
                Calculations calcResult = res.Value;

                InstrumentDefaultsViewModel result = new InstrumentDefaultsViewModel
                {
                    PayFreq=instrResult.IntPayFreq,
                    HolidayAdjust=instrResult.HolidayAdjust,
                    DayCount=instrResult.IntDayCount,
                    EndOfMonthPay=instrResult.EndOfMonthPay,
                    YieldDayCount=calcResult.YieldDayCount,
                    YieldFrequency=calcResult.YieldFreq,
                    YieldMethod=calcResult.YieldMethod
                };
                JsonResult jResult = new JsonResult(result);
                return jResult;
            }
            catch (Exception ex)
            {
                Response.StatusCode = (int)HttpStatusCode.BadRequest;
                return Json(ex.Message);
            }
        }
        [HttpPost("calculate")]
        public async Task<JsonResult> Post([FromBody]IEnumerable<CalculatorViewModel> vms)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    CalculatorResultViewModel[] vmsOutArray = new CalculatorResultViewModel[vms.Count()];
                    await Task.Run(() =>
                    {
                        Parallel.ForEach(vms, (vm, pls, index) =>
                        {
                            CalculatorResultViewModel rvm = new CalculatorResultViewModel
                            {
                                Id = vm.Id,
                                Status = "",
                                Message = ""
                        };
                            try
                            {
                                Instrument instr = new Instrument
                                {
                                    Class = "Eurobond",
                                    EndOfMonthPay = vm.EndOfMonth,
                                    FirstPayDate=vm.FirstPayDate,
                                    HolidayAdjust=vm.CalcDateAdjust,
                                    IntDayCount=vm.DayCount,
                                    InterestRate=vm.InterestRate/100,
                                    IntPayFreq=vm.PayFrequency,
                                    IssueDate=vm.IssueDate,
                                    MaturityDate=vm.MaturityDate,
                                    Name="",
                                    NextToLastPayDate=vm.NextToLastDate
                                };
                                Calculations calc = new Calculations
                                {
                                    CalculatePrice=vm.CalculatePrice,
                                    ExCoupDays=0,
                                    IsExCoup=vm.ExCoupon,
                                    PayHolidayAdjust=vm.PayDateAdjust,
                                    PriceIn=vm.PriceIn/100,
                                    ValueDate=vm.ValueDate,
                                    YieldIn=vm.YieldIn/100,
                                    YieldDayCount=vm.YieldDayCount,
                                    YieldFreq=vm.YieldFrequency,
                                    YieldMethod=vm.YieldMethod
                                };
                                if (!vm.OverrideDefaults)
                                {
                                    DefaultDatesViewModel ddvm = new DefaultDatesViewModel
                                    {
                                        EndOfMonthPay = instr.EndOfMonthPay,
                                        HolidayAdjust = instr.HolidayAdjust,
                                        Holidays = vm.Holidays,
                                        IntDayCount = instr.IntDayCount,
                                        IntPayFreq = instr.IntPayFreq,
                                        MaturityDate = instr.MaturityDate,
                                        ValueDate = calc.ValueDate
                                    };
                                    var defaultDates = getDefaultDates(ddvm).Result;

                                    instr.MaturityDate = defaultDates.MaturityDate;
                                    instr.IssueDate = defaultDates.IssueDate;
                                    instr.FirstPayDate = defaultDates.FirstPayDate;
                                    instr.NextToLastPayDate = defaultDates.NextToLastPayDate;
                                }
                                Instrument instrResult = null;
                                Calculations calcResult = null;
                                IEnumerable<Holiday> holidays = Mapper.Map<IEnumerable<Holiday>>(vm.Holidays);
                                var res = _repository.CalculateAsync(instr, calc, holidays, vm.IncludeCashflows);
                                instrResult = res.Result.Key;
                                calcResult = res.Result.Value;
                                rvm = new CalculatorResultViewModel
                                {
                                    Id = vm.Id,
                                    Status = "",
                                    Message = "",
                                    AccruedInterest = calcResult.Interest*100,
                                    Cashflows = Mapper.Map<IEnumerable<CashFlowViewModel>>(calcResult.Cashflows),
                                    CleanPrice = (vm.CalculatePrice ? calcResult.PriceOut : vm.PriceIn / 100) * 100,
                                    Convexity = calcResult.Convexity,
                                    ConvexityAdjustedPvbp = calcResult.PvbpConvexityAdjusted,
                                    DirtyPrice = (calcResult.Interest + (vm.CalculatePrice ? calcResult.PriceOut : vm.PriceIn/100))*100,
                                    Duration=calcResult.Duration,
                                    ModifiedDuration=calcResult.ModifiedDuration,
                                    NextPay=calcResult.NextPayDate,
                                    PreviousPay=calcResult.PreviousPayDate,
                                    Pvbp=calcResult.Pvbp,
                                    Yield=(vm.CalculatePrice ? vm.YieldIn/100:calcResult.YieldOut)*100,
                                    IssueDate=instr.IssueDate,
                                    FirstPayDate=instr.FirstPayDate,
                                    NextToLastDate=instr.NextToLastPayDate
                            };
                            }
                            catch (InvalidOperationException ioEx)
                            {
                                rvm.Status = ioEx.Message;
                            }
                            catch (AggregateException aex)
                            {
                                if (aex.InnerExceptions.Count==1 && aex.InnerExceptions[0] is InvalidOperationException)
                                {
                                    InvalidOperationException ioe = aex.InnerExceptions[0] as InvalidOperationException;
                                    rvm.Status = ioe.Message;
                                }
                                else
                                {
                                    rvm.Status = "Calculation Error";
                                    rvm.Message = aex.Flatten().ToString();
                                }
                            }
                            catch (Exception ex)
                            {
                                rvm.Status = "Calculation Error";
                                rvm.Message = ex.ToString();
                            }
                            finally
                            {
                                vmsOutArray[(int)index] = rvm;
                            }
                        });
                    }).ConfigureAwait(false);
                    var result = vmsOutArray.ToList();
                    JsonResult jResult = new JsonResult(result);
                    return jResult;
                }
            }
            catch (Exception ex)
            {
                Response.StatusCode = (int)HttpStatusCode.BadRequest;
                return Json(ex.Message);
            }
            Response.StatusCode = (int)HttpStatusCode.BadRequest;
            return Json(new { Message = "Failed", ModelState = ModelState });
        }
        private async Task<DefaultDatesResultViewModel> getDefaultDates(DefaultDatesViewModel vm)
        {
            Instrument instr = new Instrument
            {
                Class = "Eurobond",
                IntDayCount = vm.IntDayCount,
                IntPayFreq = vm.IntPayFreq,
                MaturityDate = vm.MaturityDate,
                EndOfMonthPay = vm.EndOfMonthPay,
                HolidayAdjust = vm.HolidayAdjust
            };
            Calculations calc = new Calculations
            {
                ValueDate = vm.ValueDate
            };
            IEnumerable<Holiday> holidays = Mapper.Map<IEnumerable<Holiday>>(vm.Holidays);
            var res = await _repository.GetDefaultDatesAsync(instr, calc, holidays).ConfigureAwait(false);
            Instrument instrResult = res.Key;
            Calculations calcResult = res.Value;

            DefaultDatesResultViewModel result = new DefaultDatesResultViewModel
            {
                MaturityDate = instrResult.MaturityDate,
                IssueDate = instrResult.IssueDate,
                FirstPayDate = instrResult.FirstPayDate,
                NextToLastPayDate = instrResult.NextToLastPayDate
            };

            return result;
        }
        [HttpPost("defaultdates")]
        public async Task<JsonResult> Post([FromBody]DefaultDatesViewModel vm)
        {
            try
            {
                var result = await getDefaultDates(vm);
                JsonResult jResult = new JsonResult(result);
                return jResult;
            }
            catch (Exception ex)
            {
                Response.StatusCode = (int)HttpStatusCode.BadRequest;
                return Json(ex.Message);
            }
        }
        [HttpPost("cashflows")]
        public async Task<JsonResult> Post([FromBody]CashFlowPricingViewModel vm)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    var cf = Mapper.Map<CashFlowPricing>(vm);
                    var cfOut = await _repository.PriceCashFlowsAsync(cf).ConfigureAwait(false);
                    IEnumerable<CashFlowViewModel> result = Mapper.Map<IEnumerable<CashFlowViewModel>>(cfOut);
                    JsonResult jResult = new JsonResult(result);
                    return jResult;
                }
            }
            catch (Exception ex)
            {
                Response.StatusCode = (int)HttpStatusCode.BadRequest;
                return Json(ex.Message);
            }
            Response.StatusCode = (int)HttpStatusCode.BadRequest;
            return Json(new { Message = "Failed", ModelState = ModelState });
        }

        // PUT api/values/5
        [HttpPut("{id}")]
        public void Put(int id, [FromBody]string value)
        {
        }

        // DELETE api/values/5
        [HttpDelete("{id}")]
        public void Delete(int id)
        {
        }
    }
}
