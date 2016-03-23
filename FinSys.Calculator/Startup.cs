using Microsoft.AspNet.Builder;
using Microsoft.AspNet.Hosting;
using Microsoft.Extensions.DependencyInjection;
using FinSys.Calculator.Services;
using Microsoft.Extensions.Configuration;
using Microsoft.Extensions.PlatformAbstractions;
using Newtonsoft.Json.Serialization;
using Microsoft.Extensions.Logging;
using AutoMapper;
using FinSys.Calculator.Models;
using FinSys.Calculator.ViewModels;
using System;
using FinSys.Calculator.Logging;

namespace FinSys.Calculator
{
    public class Startup
    {
        public static IConfigurationRoot Configuration;
        public Startup(IApplicationEnvironment appEnv)
        {
            var builder = new ConfigurationBuilder()
                .SetBasePath(appEnv.ApplicationBasePath)
                .AddJsonFile("config.json")
                .AddEnvironmentVariables();
            Configuration = builder.Build();

        }
        // This method gets called by the runtime. Use this method to add services to the container.
        // For more information on how to configure your application, visit http://go.microsoft.com/fwlink/?LinkID=398940
        public void ConfigureServices(IServiceCollection services)
        {
            services.AddMvc()
                .AddJsonOptions(opt =>
                {
                    opt.SerializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();

                })
                ;
            services.AddLogging();
            services.AddEntityFramework()
                .AddSqlServer()
                .AddDbContext<FinSysContext>();

            services.AddScoped<ICalculatorRepository, CalculatorRepository>();
#if DEBUG
            services.AddScoped<IMailService, DebugMailService>();
#else
            services.AddScoped<IMailService, RealMailService>();
#endif
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app,ILoggerFactory loggerFactory)
        {
            var logLevelStr = Startup.Configuration["AppSettings:LogLevel"];
            LogLevel logLevel = LogLevel.Verbose;
            if (!string.IsNullOrEmpty(logLevelStr))
            {
                logLevel = (LogLevel)System.Enum.Parse(typeof(LogLevel), logLevelStr); loggerFactory.AddDebug(LogLevel.Information);
            }
#if DEBUG
            loggerFactory.AddDebug(logLevel);
#else
            loggerFactory.AddProvider(new EFLoggerProvider(logLevel,new FinSysContext()));

#endif
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
                    defaults: new {controller="App",action= "Index" }
                    );
            });
        }

        // Entry point for the application.
        public static void Main(string[] args) => WebApplication.Run<Startup>(args);
    }
}
