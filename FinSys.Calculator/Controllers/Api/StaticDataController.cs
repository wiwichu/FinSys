using FinSys.Calculator.Services;
using Microsoft.AspNet.Mvc;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSys.Calculator.Controllers.Api
{
    public class StaticDataController : Controller
    {
        private ICalculatorRepository _repository;
        public StaticDataController(ICalculatorRepository repository)
        {
            _repository = repository;
        }
        [HttpGet("api/staticdata")]
        public async Task<JsonResult> Get()
        {
            
            var instrumentClasses = await _repository.GetInstrumentClassesAsync();
            var dayCounts = await _repository.GetDayCountsAsync();
            IDictionary<string,IEnumerable<object>> staticData = new Dictionary<string, IEnumerable<object>>();
            staticData.Add("instrumentClasses",instrumentClasses);
            staticData.Add("dayCounts",dayCounts);

            return Json(staticData);
        }
    }
}
