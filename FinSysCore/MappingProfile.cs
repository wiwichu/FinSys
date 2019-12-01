using AutoMapper;
using FinSysCore.Models;
using FinSysCore.ViewModels;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace FinSysCore
{
    public class MappingProfile : Profile
    {
        public MappingProfile()
        {
            CreateMap<USTBill, USTBillViewModel>().ReverseMap();
            CreateMap<USTBillResult, USTBillResultViewModel>().ReverseMap();
            CreateMap<CashFlow, CashFlowDescr>().ReverseMap();
            CreateMap<CashFlow, CashFlowViewModel>().ReverseMap();
            CreateMap<CashFlowPricing, CashFlowPricingViewModel>().ReverseMap();
            CreateMap<DateTime, DateDescr>().ReverseMap();
            CreateMap<RateCurve, RateCurveViewModel>().ReverseMap();
            CreateMap<DefaultDates, DefaultDatesViewModel>().ReverseMap();
            CreateMap<DefaultDatesResult, DefaultDatesResultViewModel>().ReverseMap();
            CreateMap<DateTime, Holiday>().ReverseMap();
            CreateMap<DateTime, HolidayViewModel>().ReverseMap();
            CreateMap<HolidayViewModel, Holiday>().ReverseMap();
            CreateMap<DayCount, DayCountViewModel>().ReverseMap();
        }
    }
 }
