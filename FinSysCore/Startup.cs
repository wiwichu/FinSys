using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.AspNetCore.Http;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.PlatformAbstractions;
using Microsoft.Extensions.Configuration;
using FinSysCore.Services;
using Microsoft.EntityFrameworkCore.Infrastructure;
using FinSysCore.Models;
using AutoMapper;
using FinSysCore.ViewModels;

namespace FinSysCore
{
    public class Startup
    {
        private IConfigurationRoot _config;
        private IHostingEnvironment _env;
        public Startup(IHostingEnvironment env)
        {
            _env = env;
            var builder = new ConfigurationBuilder()
                .SetBasePath(_env.ContentRootPath)
               .AddJsonFile("config.json")
                .AddEnvironmentVariables();
            _config = builder.Build();

        }
        // This method gets called by the runtime. Use this method to add services to the container.
        // For more information on how to configure your application, visit http://go.microsoft.com/fwlink/?LinkID=398940
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddSingleton(_config);
            services.AddDbContext<FinSysContext>();
            services.AddMvc()
                //.AddJsonOptions(opt =>
                //{
                //    opt.SerializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();

                //})
                ;
            services.AddLogging();
            //services.AddEntityFramework()
            //    .AddSqlServer()
            //    .AddDbContext<FinSysContext>()
            //    ;

            services.AddScoped<ICalculatorRepository, CalculatorRepository>();
            if (_env.IsDevelopment())
            {
                services.AddScoped<IMailService, DebugMailService>();
            }
            else
            {
                services.AddScoped<IMailService, DebugMailService>();
                //services.AddScoped<IMailService, RealMailService>();
            }
            services.AddScoped<ICalculatorRepository, CalculatorRepository>();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, ILoggerFactory loggerFactory)
        {
            var logLevelStr = _config["AppSettings:LogLevel"];
            LogLevel logLevel = LogLevel.Information;
            if (!string.IsNullOrEmpty(logLevelStr))
            {
                logLevel = (LogLevel)System.Enum.Parse(typeof(LogLevel), logLevelStr); loggerFactory.AddDebug(LogLevel.Information);
            }
            app.UseStaticFiles();
            Mapper.Initialize(config =>
            {
                config.CreateMap<USTBill, USTBillViewModel>().ReverseMap();
                config.CreateMap<USTBillResult, USTBillResultViewModel>().ReverseMap();
                config.CreateMap<CashFlow, CashFlowDescr>().ReverseMap();
                config.CreateMap<CashFlow, CashFlowViewModel>().ReverseMap();
                config.CreateMap<CashFlowPricing, CashFlowPricingViewModel>().ReverseMap();
                config.CreateMap<DateTime, DateDescr>().ReverseMap();
                config.CreateMap<RateCurve, RateCurveViewModel>().ReverseMap();
                config.CreateMap<DefaultDates, DefaultDatesViewModel>().ReverseMap();
                config.CreateMap<DefaultDatesResult, DefaultDatesResultViewModel>().ReverseMap();
                config.CreateMap<DateTime, Holiday>().ReverseMap();
                config.CreateMap<DateTime, HolidayViewModel>().ReverseMap();
                config.CreateMap<HolidayViewModel, Holiday>().ReverseMap();
                config.CreateMap<DayCount, DayCountViewModel>().ReverseMap();
            });
            app.UseMvc(config =>
            {
                config.MapRoute(
                    name: "Default",
                    template: "{controller}/{action}/{id?}",
                    defaults: new { controller = "App", action = "Index" }
                    );
            });
            loggerFactory.AddConsole();

            if (_env.IsDevelopment())
            {
                loggerFactory.AddDebug(logLevel);
                app.UseDeveloperExceptionPage();
            }
        }
    }
}
