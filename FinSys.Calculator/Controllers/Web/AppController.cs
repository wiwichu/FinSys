using FinSys.Calculator;
using FinSys.Calculator.Models;
using FinSys.Calculator.Services;
using FinSys.Calculator.ViewModels;
using Microsoft.AspNet.Mvc;
using System;
using System.Linq;

namespace FinSys.Controllers.Web
{
    public class AppController : Controller
    {
        private IMailService _mailService;
        private ICalculatorRepository _calculatorRepository;
        private FinSysContext _context;
        public AppController(IMailService service, ICalculatorRepository calculatorRepository, FinSysContext context)
        {
            _mailService = service;
            _calculatorRepository = calculatorRepository;
            _context = context;
            Log log = new Log
            {
                User = "x",
                Message = "AppController Constructor",
                LogTime = DateTime.Now,
                Severity = "Info",
                Topic = "x"
            };
            _context.Logs.Add(log);
            _context.SaveChanges();
        }
        public IActionResult Index()
        {
            var logs = _context.Logs.OrderBy(l => l.User).ToList();
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
        public IActionResult CashFlows()
        {
            return View();
        }
        [HttpPost]
        public IActionResult Contact(ContactViewModel model)
        {
            if (ModelState.IsValid)
            {
                var email = Startup.Configuration["AppSettings:SiteEmailAddress"];

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
