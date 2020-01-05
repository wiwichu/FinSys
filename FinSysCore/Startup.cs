using System;
using Microsoft.AspNetCore.Builder;
using Microsoft.AspNetCore.Hosting;
using Microsoft.Extensions.DependencyInjection;
using Microsoft.Extensions.Logging;
using Microsoft.Extensions.Configuration;
using FinSysCore.Services;
using FinSysCore.Models;
using FinSysCore.ViewModels;
using FinSysCore.Logging;
using Microsoft.EntityFrameworkCore;
using AutoMapper;

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
            var mappingConfig = new MapperConfiguration(mc =>
            {
                mc.AddProfile(new MappingProfile());
            });

            IMapper mapper = mappingConfig.CreateMapper();
            services.AddSingleton(mapper); services.AddSingleton(_config);
            services.AddDbContext<FinSysContext>();
            services.AddMvc().AddMvcOptions(opt =>
            {
                opt.EnableEndpointRouting = false;
            })
                //.AddJsonOptions(opt =>
                //{
                //    opt.SerializerSettings.ContractResolver = new CamelCasePropertyNamesContractResolver();

                //})
                ;
            services.AddLogging(opt =>
             {
                 opt.AddConsole();
                 if (_env.IsDevelopment())
                 {
                     opt.AddDebug();
                 }
             });
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
            services.AddControllers().AddNewtonsoftJson();
        }

        // This method gets called by the runtime. Use this method to configure the HTTP request pipeline.
        public void Configure(IApplicationBuilder app, 
            ILoggerFactory loggerFactory,
            FinSysContext context)
        {
            var logLevelStr = _config["AppSettings:LogLevel"];
            var logSqlStr = _config["AppSettings:LogSqlBool"] ?? "False";
            var logSqlBool = false;
            try
            {
                logSqlBool = bool.Parse(logSqlStr);
            }
            catch (FormatException )
            {
                //use defaul false value if string is malformed.
            }
            LogLevel logLevel = LogLevel.Information;
            if (!string.IsNullOrEmpty(logLevelStr))
            {
                logLevel = (LogLevel)System.Enum.Parse(typeof(LogLevel), logLevelStr);
            }
            app.UseStaticFiles();
            app.UseMvc(config =>
            {
                config.MapRoute(
                    name: "Default",
                    template: "{controller}/{action}/{id?}",
                    defaults: new { controller = "App", action = "Index" }
                    );
            });
            //loggerFactory.AddConsole();

            if (_env.IsDevelopment())
            {
                //loggerFactory.AddDebug(LogLevel.Information);
                //loggerFactory.AddDebug(logLevel);
                app.UseDeveloperExceptionPage();
            }
            if (logSqlBool)
            {
                loggerFactory.AddProvider(new EFLoggerProvider(logLevel, context));
            }
        }
    }
}
