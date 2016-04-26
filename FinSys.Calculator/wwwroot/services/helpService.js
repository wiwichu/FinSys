(function () {
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
                case "useHolidays":
                    {
                        help = {
                            title: "Use Holidays",
                            text: "Adjust calculations for holidays entered.",
                            link: "#/Guide#HolidayInput"
                        };
                        break;
                    } 
                case "maturitydate":
                {
                    help = {
                        title: "Maturity Date",
                        text: "Date on which the instrument matures.",
                        link: "#/Guide#maturitydate"
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
                case "custCalcCleanPrice":
                    {
                        help = {
                            title: "Clean Price",
                            text: "Clean price of the trade as a per cent of nominal.",
                            link: "#/Guide#CustCalcCleanPrice"
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
