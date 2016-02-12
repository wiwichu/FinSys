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

            var instrumentClasses = await _repository.GetInstrumentClassesAsync();
            var dayCounts = await _repository.GetDayCountsAsync();
            var holidayAdjust = await _repository.GetHolidayAdjustAsync();
            var interpolationMethods = await _repository.GetInterpolationMethodsAsync();
            var payFrequency = await _repository.GetPayFreqsAsync();
            var yieldMethods = await _repository.GetYieldMethodsAsync();

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
                    USTBillResultViewModel result = Mapper.Map < USTBillResultViewModel > (await _repository.USTBillCalcAsync(ustb));
                    result.BondEquivalent *= 100;
                    result.Discount *= 100;
                    result.MMYield *= 100;
                    result.Price *= 100;
                    return new JsonResult(result);
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
