// calculatorController.js
(function () {

    //"use strict";

    angular.module("app-calculator")
    .controller("quickCalcController", quickCalcController)
    ;
    
    function quickCalcController($http, $location,$window, $rootScope
        //, apiDialog
        , $uibModal
        , $q
        ,$timeout
        , helpService, alertService
        ) {

        var vm = this;
        vm.calcText = "Calculate";
        vm.calcFrom = "price";
        vm.errorMessage = "";
        vm.staticData = [];
        vm.instrumentClass = [];
        vm.selectedInstrumentClass = "";
        vm.selectedYieldMethod = "";
        vm.selectedDayCount = "";
        vm.selectedCompoundFrequency = "";
        vm.selectedYieldDayCount = "";
        vm.selectedPayFrequency = "";
        vm.overrideDefaults = false;
        vm.opened = false;
        vm.isBusy = false;
        vm.endOfMonth = false;
        vm.price = 100.00;
        vm.yield = 0.00;
        vm.interestRate = 1.00;
        vm.interest = 0.00;
        vm.dirtyPrice = 100.00;
        vm.interestDays = 0;
        vm.duration = 0.00;
        vm.modDuration = 0.00;
        vm.convexity = 0.00;
        vm.pvbp = 0.00;
        vm.cvxPvbp = 0.00;
        vm.api = "/api/staticdata";
        vm.protocol = $location.protocol() + "://";
        vm.host = $location.host();
        vm.port = $location.port();
        vm.cashFlows = [];
        vm.holidays = [];
        vm.viewDefaults = "View Defaults";
        if (vm.port)
        {
            vm.port = ":" + vm.port;
        }
        vm.instrumentclass = {};
        vm.instrumentClassChanged = function () {
            //alert("Selected Instrument: " + vm.selectedInstrumentClass);
            var deferred = $q.defer();
            vm.isBusy = true;
            vm.api = "/api/calculator/instrumentdefaults";
            vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            vm.instrumentclass.Class = vm.selectedInstrumentClass;
            $http.post(vm.apiPath, vm.instrumentclass)
            .then(function (response) {
                vm.selectedCalcDateAdjust = response.data.holidayAdjust;
                vm.selectedCompoundFrequency = response.data.yieldFrequency;
                vm.selectedDayCount = response.data.dayCount;
                if (vm.payDateAdjust != null && vm.payDateAdjust[0] != null) {
                    var ind = vm.payDateAdjust.lastIndexOf("Next");
                    if (ind == -1) {
                        vm.selectedPayDateAdjust = response.data.holidayAdjust;
                    }
                    else {
                        vm.selectedPayDateAdjust = vm.payDateAdjust[ind];
                    }
                }
                vm.selectedPayFrequency = response.data.payFreq;
                vm.selectedYieldDayCount = response.data.yieldDayCount;
                vm.selectedYieldMethod = response.data.yieldMethod;
                vm.endOfMonth = response.data.endOfMonth;
                deferred.resolve();
            },
           function (err) {
               if (err.data != null) {
                   if (err.data.message != null) {
                       if (err.data.message.length < 200) {
                           vm.errorMessage = "Calculation Failed: " + err.data.message;
                       }
                       else {
                           alertService("An Error has occurred.", "Calculation Failed", err.data.message);
                       }
                   }
                   else {
                       alertService("An Error has occurred.", "Calculation Failed", err.data);
                   }
               }
               else {
                   vm.errorMessage = "Calculation Interrupted";

               }
           })
            .finally(function () {
                vm.isBusy = false;
            });
            return deferred.promise;
        }
        vm.init = function () {
            try {
                if ($rootScope.staticData) {
                    vm.instrumentClass = $rootScope.staticData.instrumentClasses;
                    if ($rootScope.staticData.instrumentClasses != null && $rootScope.staticData.instrumentClasses[0] != null) {
                        var ind = $rootScope.staticData.instrumentClasses.lastIndexOf("Eurobond");
                        if (ind == -1) {
                            vm.selectedInstrumentClass = $rootScope.staticData.instrumentClasses[0];
                        }
                        else {
                            vm.selectedInstrumentClass = $rootScope.staticData.instrumentClasses[ind];
                        }
                    }
                    vm.yieldMethod = $rootScope.staticData.yieldMethods;
                    if (vm.yieldMethod != null && vm.yieldMethod[0] != null) {
                        vm.selectedYieldMethod = vm.yieldMethod[0];
                    }
                    vm.dayCount = $rootScope.staticData.dayCounts;
                    if (vm.dayCount != null && vm.dayCount[0] != null) {
                        vm.selectedDayCount = vm.dayCount[0];
                    }
                    vm.compoundFrequency = $rootScope.staticData.payFrequency;
                    if (vm.compoundFrequency != null && vm.compoundFrequency[0] != null) {
                        vm.selectedCompoundFrequency = vm.compoundFrequency[0];
                    }
                    vm.yieldDayCount = $rootScope.staticData.dayCounts;
                    if (vm.yieldDayCount != null && vm.yieldDayCount[0] != null) {
                        vm.selectedYieldDayCount = vm.yieldDayCount[0];
                    }
                    vm.payFrequency = $rootScope.staticData.payFrequency;
                    if (vm.payFrequency != null && vm.payFrequency[0] != null) {
                        vm.selectedPayFrequency = vm.payFrequency[0];
                    }
                    vm.calcDateAdjust = $rootScope.staticData.holidayAdjust;
                    if (vm.calcDateAdjust != null && vm.calcDateAdjust[0] != null) {
                        vm.selectedCalcDateAdjust = vm.calcDateAdjust[0];
                    }
                    vm.payDateAdjust = $rootScope.staticData.holidayAdjust;
                    if (vm.payDateAdjust != null && vm.payDateAdjust[0] != null) {
                        var ind = vm.payDateAdjust.lastIndexOf("Next");
                        if (ind == -1) {
                            vm.selectedPayDateAdjust = vm.payDateAdjust[0];
                        }
                        else
                        {
                            vm.selectedPayDateAdjust = vm.payDateAdjust[ind];
                        }
                    }
                    vm.instrumentClassChanged();
                }
                else {
                    vm.errorMessage = "Failed to load data: Static Data not Initialized.";
                }
            }
            catch (exception) {
                vm.errorMessage = "Failed to load data: " + exception;
            }
            finally {
                if ($rootScope.cfData != null) {
                    vm.selectedYieldMethod = $rootScope.cfData.yieldmethod;
                    vm.selectedDayCount = $rootScope.cfData.daycount;
                    vm.selectedCompoundFrequency = $rootScope.cfData.frequency;
                }
                else {
                    vm.now = new Date();
                    vm.valueDate = new Date(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
                }
                $rootScope.cfData = null;
                vm.isBusy = false;
                vm.api = "/api/calculator/cashflows";
                vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            }

        }
        vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
        if (!$rootScope.staticData) {
            vm.api = "/api/staticdata";
            $http.get(vm.api)
                .then(function (response) {
                    $rootScope.staticData = response.data;
                    vm.init();
                }, function (error) {
                    //loghere
                })
            .finally(function () {
                vm.isBusy = false;
            });
        }
        else {
            vm.init();
            vm.isBusy = false;
        }
        vm.defaultDates = {};
        vm.calculations = [];
        vm.calculation = {};
        vm.cancelCalc;
        vm.calculate = function () {
            if (vm.calcText == "Cancel") {
                vm.calcText = "Calculate";
                vm.isBusy = false;
                vm.cancelCalc.resolve();
                return;
            }
            vm.cancelCalc = $q.defer();
            vm.calcText = "Cancel";
            vm.isBusy = true;
            vm.errorMessage = "";
            vm.api = "/api/calculator/calculate";
            vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            vm.requestJson = "";
            vm.responseJson = "";
            vm.calculation.Class = vm.selectedInstrumentClass;
            vm.calculation.OverrideDefaults = vm.overrideDefaults;
            vm.calculation.InterestRate = vm.interestRate;
            vm.calculation.MaturityDate = vm.maturityDate;
            vm.calculation.ValueDate = vm.valueDate;
            vm.calculation.YieldIn = vm.yield;
            vm.calculation.PriceIn = vm.price;
            vm.calculation.ExCoupon = vm.exCoup;
            vm.calculation.TradeFlat = vm.tradeFlat;
            vm.calculation.EndOfMonth = vm.endOfMonth;
            if (vm.calcFrom == "price") {
                vm.calculation.CalculatePrice = false;
            }
            else {
                vm.calculation.CalculatePrice = true;
            }
            vm.calculation.IncludeCashflows = vm.includeCashflows
            vm.calculation.UseHolidays = vm.useHolidays;
            vm.calculation.DayCount = vm.selectedDayCount;
            vm.calculation.PayFrequency = vm.selectedPayFrequency;
            vm.calculation.CalcDateAdjust = vm.selectedCalcDateAdjust;
            vm.calculation.PayDateAdjust = vm.selectedPayDateAdjust;
            vm.calculation.YieldDayCount = vm.selectedYieldDayCount;
            vm.calculation.YieldFrequency = vm.selectedCompoundFrequency;
            vm.calculation.YieldMethod = vm.selectedYieldMethod;
            vm.calculation.IssueDate = vm.issueDate;
            vm.calculation.FirstPayDate = vm.firstPayDate;
            vm.calculation.NextToLastDate = vm.nextToLastDate;
            if (vm.useHolidays) {
                vm.calculation.Holidays = angular.copy(vm.holidays);
            }
            else {
                vm.calculation.Holidays = [];
            }
                //for (i = 0; i < 20; i++) {
            //    vm.calculations[i] = vm.calculation;
            //}
            vm.calculations[0] = vm.calculation;
            vm.requestJson = JSON.stringify(vm.calculations, null, 2);
            $http.post(vm.apiPath, vm.calculations
                ,{
                    timeout: vm.cancelCalc.promise
                   // timeout: 10000
                }
            )
           .then(function (response) {
               if (response.data[0].status) {
                   vm.errorMessage = "Calculation Failed: " + response.data[0].status;

               }
               else {
                   vm.interest = response.data[0].accruedInterest;
                   vm.interestDays = response.data[0].interestDays;
                   vm.dirtyPrice = response.data[0].dirtyPrice;
                   vm.previousPay = new Date(response.data[0].previousPay);
                   vm.nextPay = new Date(response.data[0].nextPay);
                   vm.convexity = response.data[0].convexity;
                   vm.cvxPvbp = response.data[0].convexityAdjustedPvbp;
                   vm.duration = response.data[0].duration;
                   vm.modDuration = response.data[0].modifiedDuration;
                   if (vm.calcFrom == "price") {
                       vm.yield = response.data[0].yield;
                   }
                   else {
                       vm.price = response.data[0].cleanPrice;
                   }
                   vm.pvbp = response.data[0].pvbp;
                   vm.issueDate = new Date(response.data[0].issueDate);
                   vm.firstPayDate = new Date(response.data[0].firstPayDate);
                   vm.nextToLastDate = new Date(response.data[0].nextToLastDate);

                   vm.responseJson = JSON.stringify(response.data, null, 2);
                   vm.cashFlows = response.data[0].cashflows;
               }
           },
           function (err) {
               if (err.data != null) {
                   if (err.data.message != null) {
                       if (err.data.message.length < 200) {
                           vm.errorMessage = "Calculation Failed: " + err.data.message;
                       }
                       else {
                           alertService("An Error has occurred.", "Calculation Failed", err.data.message);
                       }
                   }
                   else {
                       alertService("An Error has occurred.", "Calculation Failed", err.data);
                   }
               }
               else {
                   vm.errorMessage = "Calculation Interrupted";

               }
           })
           .finally(function () {
               vm.calcText = "Calculate";
               vm.isBusy = false;
           });
        }
        function toFixed(x) {
            if (Math.abs(x) < 1.0) {
                var e = parseInt(x.toString().split('e-')[1]);
                if (e) {
                    x *= Math.pow(10, e - 1);
                    x = '0.' + (new Array(e)).join('0') + x.toString().substring(2);
                }
            } else {
                var e = parseInt(x.toString().split('+')[1]);
                if (e > 20) {
                    e -= 20;
                    x /= Math.pow(10, e);
                    x += (new Array(e + 1)).join('0');
                }
            }
            return x;
        }

        var api = {
            apiPath: vm.apiPath,
            requestJson: vm.requestJson,
            responseJson: vm.responseJson
        };
        var that = this;
        vm.getApi = function () {

            var options = {
                templateUrl: "/templates/apiDialog.html",
                controller: function () {
                    this.api = {
                        apiPath: vm.apiPath,
                        requestJson: vm.requestJson,
                        responseJson: vm.responseJson
                    };
                },
                controllerAs: "model"
            };
            $uibModal.open(options);
        }
        vm.getHelp = function (helpText) {
            helpService(helpText);
        }
        ///////////////////// datepicker ///////////////////////
        vm.datepickers = {
            maturityDate: false,
            previousPay: false,
            nextPay: false,
            issueDate: false,
            firstPayDate: false,
            nextToLastDate: false,
            valueDate: false
        }
        vm.now = new Date();
        vm.valueDate = new Date(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
        vm.maturityDate = new Date(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
        vm.maturityDate.setFullYear(vm.maturityDate.getFullYear() + 1);

      vm.showWeeks = true;
      vm.toggleWeeks = function () {
        vm.showWeeks = ! vm.showWeeks;
      };

      vm.clear = function () {
        vm.maturityDate = null;
      };

      // Disable weekend selection
      vm.disabled = function(date, mode) {
        return ( mode === 'day' && ( date.getDay() === 0 || date.getDay() === 6 ) );
      };

      vm.toggleMin = function() {
        vm.minDate = ( vm.minDate ) ? null : new Date();
      };
      vm.toggleMin();
      vm.open = function ($event, which) {
          $event.preventDefault();
          $event.stopPropagation();
          $timeout(function () {
              angular.forEach(vm.datepickers, function (value, key) {
                  if (key == which) {
                      vm.datepickers[key] = true;
                  }
                  else {
                      vm.datepickers[key] = false;
                  }

              });
          });
      };
      vm.dateOptions = {
          'year-format': "'yy'",
          'starting-day': 1
      };
      vm.formats = ['yyyy-MM-dd', 'dd-MMMM-yyyy', 'yyyy/MM/dd', 'shortDate'];
      vm.format = vm.formats[0];
        /////////////////////////////////
      vm.openVD = function () {
          $timeout(function () {  vm.opened = true;  });
      };
     }
})();
