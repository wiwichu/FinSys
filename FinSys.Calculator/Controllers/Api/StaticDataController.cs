using FinSys.Calculator.Services;
using Microsoft.AspNet.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Controllers.Api
{
    [Route("api/staticdata")]
    public class StaticDataController : Controller
    {
        private ICalculatorRepository _repository;
        public StaticDataController(ICalculatorRepository repository)
        {
            _repository = repository;
        }
        [HttpGet("")]
        public async Task<JsonResult> Get()
        {
            
            var instrumentClasses = await _repository.GetInstrumentClassesAsync();
            var dayCounts = await _repository.GetDayCountsAsync();
            var holidayAdjust = await _repository.GetHolidayAdjustAsync();
            var interpolationMethods = await _repository.GetInterpolationMethodsAsync();
            var payFrequency = await _repository.GetPayFreqsAsync();
            var yieldMethods = await _repository.GetYieldMethodsAsync();
            
            IDictionary<string,IEnumerable<object>> staticData = new Dictionary<string, IEnumerable<object>>();
            staticData.Add("instrumentClasses",instrumentClasses);
            staticData.Add("dayCounts",dayCounts);
            staticData.Add("holidayAdjust",holidayAdjust);
            staticData.Add("interpolationMethods", interpolationMethods);
            staticData.Add("payFrequency", payFrequency);
            staticData.Add("yieldMethods", yieldMethods);

            return Json(staticData);
        }
    }
}
