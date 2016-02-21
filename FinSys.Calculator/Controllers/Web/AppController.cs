using FinSys.Calculator;
using FinSys.Calculator.Services;
using FinSys.Calculator.ViewModels;
using Microsoft.AspNet.Mvc;
using System;

namespace FinSys.Controllers.Web
{
    public class AppController : Controller
    {
        private IMailService _mailService;
        private ICalculatorRepository _calculatorRepository;
        public AppController(IMailService service, ICalculatorRepository calculatorRepository)
        {
            _mailService = service;
            _calculatorRepository = calculatorRepository;
        }
        public IActionResult Index()
        {
            return View();
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
