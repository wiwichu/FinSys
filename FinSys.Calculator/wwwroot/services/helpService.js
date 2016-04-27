﻿(function () {
    'use strict';

    angular
        .module('app-calculator')
        .factory('helpService',['$uibModal', helpService]);

    function helpService($uibModal, $timeout) {
        var shinyNewServiceInstance = { test: "test" };
        //return shinyNewServiceInstance;
        return showHelp;
        //{
        //    showHelp: showHelp
        //};
        function showHelp(helpTopic)
        {
            var help = {
                title: "No Help",
                text: "No Help Available.",
                link: "#/Guide#guideStart"
            };
            switch (helpTopic)
            {
                case "customCalcForm":
                    {
                        help = {
                            title: "Use Holidays",
                            text: "Form for custom calculations.",
                            link: "#/Guide#custCalc"
                        };
                        break;
                    }
                case "instrumentClass":
                    {
                        help = {
                            title: "Instrument Class",
                            text: "Class for applying instrument defaults.",
                            link: "#/Guide#CustCalcClass"
                        };
                        break;
                    }
                case "custCalcInterestRate":
                    {
                        help = {
                            title: "Interest Rate",
                            text: "Rate of interest paid on the instrument.",
                            link: "#/Guide#CustCalcInterestRate"
                        };
                        break;
                    }
                case "useHolidays":
                    {
                        help = {
                            title: "Use Holidays",
                            text: "Adjust calculations for holidays entered.",
                            link: "#/Guide#HolidayInput"
                        };
                        break;
                    } 
                case "custCalcMaturityDate":
                {
                    help = {
                        title: "Maturity Date",
                        text: "Date on which the instrument matures.",
                        link: "#/Guide#CustCalcMaturityDate"
                    };
                    break;
                }
                case "custCalcEndOfMonth":
                    {
                        help = {
                            title: "End of Month",
                            text: "Indicates the instrument pays on the end of month.",
                            link: "#/Guide#CustCalcEndOfMonth"
                        };
                        break;
                    }
                case "custCalcCalculateFrom":
                    {
                        help = {
                            title: "Calculate From",
                            text: "Sets whether calculations are done from Yield or Price.",
                            link: "#/Guide#CustCalcCalculateFrom"
                        };
                        break;
                    }
                case "custCalcYield":
                    {
                        help = {
                            title: "Yield or Discount",
                            text: "Yield or Discount corresponding to Price.",
                            link: "#/Guide#CustCalcYield"
                        };
                        break;
                    }
                case "custCalcDirtyPrice":
                    {
                        help = {
                            title: "Dirty Price",
                            text: "Invoice price of the trade.",
                            link: "#/Guide#CustCalcDirtyPrice"
                        };
                        break;
                    }
                case "custCalcExCoup":
                    {
                        help = {
                            title: "Ex-Coupon",
                            text: "Indicates that negative accrued interest will be calculated back from the next pay date.",
                            link: "#/Guide#CustCalcExCoupon"
                        };
                        break;
                    }
                case "custCalcTradeFlat":
                    {
                        help = {
                            title: "Trade Flat",
                            text: "Indicates that accrued interest will not be included in the invoice price.",
                            link: "#/Guide#CustCalcTradeFlat"
                        };
                        break;
                    }
                case "custCalcAccruedInterest":
                    {
                        help = {
                            title: "Accrued Interest",
                            text: "Accrued interest on the trade as a per cent of nominal.",
                            link: "#/Guide#CustCalcAccruedInterest"
                        };
                        break;
                    }
                case "custCalcMaturityDate":
                    {
                        help = {
                            title: "Maturity Date",
                            text: "Date on which the instrument matures.",
                            link: "#/Guide#CustCalcMaturityDate"
                        };
                        break;
                    }
                case "valuedate":
                {
                    help = {
                        title: "Value Date",
                        text: "Also called Settlement Date. Base date used for calculating accrued interest and yield.",
                        link: "#/Guide#CustCalcValueDate"
                    };
                    break;
                }
                case "daycount":
                    {
                        help = {
                            title: "Day Count",
                            text: "Rules for calculating days in a period and payment factor.",
                            link: "#/Guide#daycount"
                        };
                        break;
                    }
                case "cashflowForm":
                    {
                        help = {
                            title: "CashFlows",
                            text: "Displays and allows pricing of cash flows.",
                            link: "#/Guide#cashFlows"
                        };
                        break;
                    }
                case "custCalcIncludeCashflows":
                    {
                        help = {
                            title: "Include CashFlows",
                            text: "Causes cashflows to be included in the calculation result.",
                            link: "#/Guide#CustCalcIncludeCashflows"
                        };
                        break;
                    }
                case "custCalcPreviousPay":
                    {
                        help = {
                            title: "Previous Pay Date",
                            text: "The last payment before the Value Date.",
                            link: "#/Guide#CustCalcPreviousPay"
                        };
                        break;
                    }
                case "custCalcNextPay":
                    {
                        help = {
                            title: "Next Pay Date",
                            text: "The next payment after the Value Date.",
                            link: "#/Guide#CustCalcNextPay"
                        };
                        break;
                    }
                case "custCalcInterestDays":
                    {
                        help = {
                            title: "Interest Days",
                            text: "The number of days from the previous pay date to the value date.",
                            link: "#/Guide#CustCalcInterestDays"
                        };
                        break;
                    }
                case "custCalcDuration":
                    {
                        help = {
                            title: "Macaulay Duration",
                            text: "The time to cashflows weighted by their present values.",
                            link: "#/Guide#CustCalcDuration"
                        };
                        break;
                    }
                case "custCalcModifiedDuration":
                    {
                        help = {
                            title: "Modified Duration",
                            text: "Measures the price sensitivity of a bond to interest rates.",
                            link: "#/Guide#CustCalcModifiedDuration"
                        };
                        break;
                    }
                case "custCalcConvexity":
                    {
                        help = {
                            title: "Convexity",
                            text: "Measures the change in duration for interest rates change.",
                            link: "#/Guide#CustCalcConvexity"
                        };
                        break;
                    }
                case "custCalcPVBP":
                    {
                        help = {
                            title: "PVBP",
                            text: "Price change for a basis point change in yield.",
                            link: "#/Guide#CustCalcPVBP"
                        };
                        break;
                    }
                case "custCalcConvexityPVBP":
                    {
                        help = {
                            title: "Convexity Adjusted PVBP",
                            text: "PVBP adjusted for convexity.",
                            link: "#/Guide#CustCalcConvexityPVBP"
                        };
                        break;
                    }
                case "custCalcDayCount":
                    {
                        help = {
                            title: "Calculation Day Count",
                            text: "Day Count Rule for calculating interest.",
                            link: "#/Guide#CustCalcDayCount"
                        };
                        break;
                    }
                case "custCalcPayFreq":
                    {
                        help = {
                            title: "Pay Frequency",
                            text: "Frequency of interest payments.",
                            link: "#/Guide#CustCalcPayFreq"
                        };
                        break;
                    }
                case "custCalcCompoundFreq":
                    {
                        help = {
                            title: "Compound Frequency",
                            text: "Frequency of yield compounding.",
                            link: "#/Guide#CustCalcCompoundFreq"
                        };
                        break;
                    }
                case "custCalcYieldDayCount":
                    {
                        help = {
                            title: "Yield Day Count",
                            text: "Day Count Rule for calculating yield.",
                            link: "#/Guide#CustCalcYieldDayCount"
                        };
                        break;
                    }
                case "custCalcCalcDateAdjust":
                    {
                        help = {
                            title: "Calculation Date Adjustment",
                            text: "Holiday Adjust Rule for calcuation dates.",
                            link: "#/Guide#CustCalcCalcDateAdjust"
                        };
                        break;
                    }
                case "custCalcPayDateAdjust":
                    {
                        help = {
                            title: "Payment Date Adjustment",
                            text: "Holiday Adjust Rule for payment dates.",
                            link: "#/Guide#CustCalcPayDateAdjust"
                        };
                        break;
                    }
                case "custCalcYieldMethod":
                    {
                        help = {
                            title: "Yield Method",
                            text: "Method for calculating yield.",
                            link: "#/Guide#CustCalcYieldMethod"
                        };
                        break;
                    }
                case "custCalcOverrideDates":
                    {
                        help = {
                            title: "OverrideDates",
                            text: "Override default dates with entered values.",
                            link: "#/Guide#CustCalcOverrideDates"
                        };
                        break;
                    }
                case "custCalcIssueDate":
                    {
                        help = {
                            title: "Issue Date",
                            text: "Date instrument was issued.",
                            link: "#/Guide#CustCalcIssueDate"
                        };
                        break;
                    }
                case "custCalcFirstPayDate":
                    {
                        help = {
                            title: "First Pay Date",
                            text: "First payment on the instrument.",
                            link: "#/Guide#CustCalcFirstPayDate"
                        };
                        break;
                    }
                case "custCalcNextToLastPayDate":
                    {
                        help = {
                            title: "Next to Last Pay Date",
                            text: "Last payment on the instrument before maturity.",
                            link: "#/Guide#CustCalcNextToLastPayDate"
                        };
                        break;
                    }
                case "cashFlowGrid":
                    {
                        help = {
                            title: "Cash Flow Grid",
                            text: "Editable Grid of cash flows.",
                            link: "#/Guide#CashFlowGrid"
                        };
                        break;
                    }
                case "cashFlowYieldMethod":
                    {
                        help = {
                            title: "Yield Method",
                            text: "Method for discounting to present value.",
                            link: "#/Guide#CashFlowYieldMethod"
                        };
                        break;
                    }
                case "cashFlowYieldDayCount":
                    {
                        help = {
                            title: "Yield Day Count",
                            text: "Day Count Rule for discounting payments.",
                            link: "#/Guide#CashFlowYieldDayCount"
                        };
                        break;
                    }
                case "cashFlowCompoundFreq":
                    {
                        help = {
                            title: "Compound Frequency",
                            text: "Frequency of discounting for present value.",
                            link: "#/Guide#CashFlowCompoundFreq"
                        };
                        break;
                    }
                case "cashFlowValueDate":
                {
                    help = {
                        title: "Value Date",
                        text: "Date to which payments are discounted..",
                        link: "#/Guide#CashFlowValueDate"
                    };
                    break;
                }
            }
            var options = {
                templateUrl: "/templates/helpDialog.html",
                controller: function ( $uibModalInstance) {
                    this.help = help;
                },
                controllerAs: "model"
            }
            var  theModal = $uibModal.open(options);
        };
    }
})();
