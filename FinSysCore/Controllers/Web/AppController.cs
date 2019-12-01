using FinSysCore.Models;
using FinSysCore.Services;
using FinSysCore.ViewModels;
using Microsoft.AspNetCore.Mvc;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.Logging;

namespace FinSys.Controllers.Web
{
    public class AppController : Controller
    {
        private IMailService _mailService;
        private ICalculatorRepository _calculatorRepository;
        private ILogger _logger;
        private FinSysContext _context;
        private IConfigurationRoot _config;
        public AppController(ILoggerFactory loggerFactory,
            IMailService service, 
            ICalculatorRepository calculatorRepository, 
            FinSysContext context,
            IConfigurationRoot config)
        {
            _config = config;
            _logger = loggerFactory.CreateLogger<AppController>();
            _mailService = service;
            _calculatorRepository = calculatorRepository;
            _context = context;
            _logger.LogInformation("AppController Constructor");
        }
        public IActionResult Index()
        {
            //var logs = _context.Logs.OrderBy(l => l.User).ToList();
            //return View();
            return Redirect(Url.Content("/App/Calculators#/"));
        }
        public IActionResult Back()
        {
            var back = Request.Headers["Referer"];
            return Redirect(back);
        }
        public IActionResult Calculators()
        {
            return View();
        }
        public IActionResult About()
        {
            return View();
        }
        public IActionResult Contact()
        {
            return View();
        }
        public IActionResult USTBill()
        {
            return View();
        }
        public IActionResult CustomCalc()
        {
            return View();
        }
        public IActionResult QuickCalc()
        {
            return View();
        }
        public IActionResult CashFlows()
        {
            return View();
        }
        [HttpPost]
        public IActionResult Contact(ContactViewModel model )
        {
            if (ModelState.IsValid)
            {
                var email = _config["AppSettings:SiteEmailAddress"];

                if(string.IsNullOrWhiteSpace(email))
                {
                    ModelState.AddModelError("", "Could not send email, configuration problem.");
                }

                if(_mailService.SendMail(email,
                    email,
                    $"Contact Page from {model.Name} ({model.Email})",
                    model.Message))
                {
                    ModelState.Clear();

                    ViewBag.Message = "Mail Sent, Thanks!";
                }
            }
            return View();
        }
    }
}
