// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("calculatorController", calculatorController)
    ;
    
    function calculatorController($http, $location,$window, $rootScope
        //, apiDialog
        , $uibModal
        ,$q
        ) {

        var vm = this;
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
        vm.isBusy = true;
        vm.endOfMonth = false;
        vm.price = 100.00;
        vm.yield = 0.00;
        vm.interestRate = 0.00;
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
                vm.selectedPayDateAdjust = response.data.holidayAdjust;
                vm.selectedPayFrequency = response.data.payFreq;
                vm.selectedYieldDayCount = response.data.yieldDayCount;
                vm.selectedYieldMethod = response.data.yieldMethod;
                vm.endOfMonth = response.data.endOfMonth;
                deferred.resolve();
            },
            function (err) {
                vm.errorMessage = "Calculation Failed: " + err.data;
                deferred.reject("Calculation Failed: " + err.data);
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
                        //vm.selectedInstrumentClass = $rootScope.staticData.instrumentClasses[0];
                        vm.selectedInstrumentClass = "Eurobond";
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
                        vm.selectedPayDateAdjust = vm.payDateAdjust[0];
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
                    vm.valueDate = new Date();
                }
                $rootScope.cfData = null;
                vm.isBusy = false;
                vm.api = "/api/calculator/cashflows";
                vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
                vm.isBusy = false;
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
        vm.setDates = function () {
            vm.isBusy = true;
            vm.api = "/api/calculator/defaultDates";
            vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            vm.defaultDates.IntDayCount = vm.selectedDayCount;
            vm.defaultDates.IntPayFreq = vm.selectedPayFrequency;
            vm.defaultDates.MaturityDate = vm.maturityDate;
            vm.defaultDates.ValueDate = vm.valueDate;
            vm.defaultDates.EndOfMonthPay = vm.endOfMonth;
            vm.defaultDates.HolidayAdjust = vm.selectedCalcDateAdjust;
            vm.defaultDates.Holidays = vm.holidays;
            $http.post(vm.apiPath, vm.defaultDates)
            .then(function (response) {
                vm.maturityDate = new Date(response.data.maturityDate);
                vm.issueDate = new Date(response.data.issueDate);
                vm.firstPayDate = new Date(response.data.firstPayDate);
                vm.nextToLastDate = new Date(response.data.nextToLastPayDate);
            },
            function (err) {
                vm.errorMessage = "Calculation Failed: " + err.data;
            })
            .finally(function () {
                vm.isBusy = false;
            });

        }
        vm.setDefaults = function () {
            vm.instrumentClassChanged().then(function(){
                vm.setDates();
            },
            function (err) {
                vm.errorMessage = "Calculation Failed: " + err.data;
            })
            .finally(function () {
                vm.isBusy = false;
            });
        }

        vm.holidayGridOptions = {
            data: 'vm.holidays',
            enableSelectAll: true,
            exporterCsvFilename: 'holidays.csv', enableGridMenu: true,
            exporterCsvLinkElement: angular.element(document.querySelectorAll(".custom-csv-link-location")),
            enablePaginationControls: true,
            enableRowSelection: true,
            enableRowHeaderSelection: true,
            selectionRowHeaderWidth: 35,
            multiSelect: true,
            paginationPageSize: 25, showGridFooter: true,
            showColumnFooter: true,
            columnDefs: [
                { name: 'HoliDate', field: 'holiDate', type: 'date', cellFilter: 'date:"yyyy-MM-dd"' },
            ],
            importerDataAddCallback: function (grid, newObjects) {
                vm.holidays = newObjects;
            },
            onRegisterApi: function (gridApi) {
                vm.holidayGridApi = gridApi;
            }
        };
        vm.addHolidays = function () {
            vm.holidays.push({
                "HoliDate": new Date()
            });
        };
        vm.deleteSelectedHolidays = function () {
            angular.forEach(vm.holidayGridApi.selection.getSelectedRows(), function (data, index) {
                vm.holidays.splice(vm.holidays.lastIndexOf(data), 1);
            });
        };
        vm.goToCashFlows = function ()
        {
            $rootScope.cfData = vm.cashFlows;
            $window.location.href = '/App/CashFlows';
        }
        vm.calculations = [];
        vm.calculation = {};
     vm.calculate = function () {
        vm.isBusy = true;
        vm.errorMessage = "";
        vm.api = "/api/calculator/calculate";
        vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
        vm.requestJson = "";
        vm.responseJson = "";
        vm.calcFrom = "price";
        vm.calculation.OverrideDefaults = vm.overrideDefaults;
        vm.calculation.InterestRate = vm.interestRate;
        vm.calculation.MaturityDate = vm.maturityDate;
        vm.calculation.ValueDate = vm.valueDate;
        vm.calculation.YieldIn = vm.yield;
        vm.calculation.PriceIn = vm.price;
        vm.calculation.ExCoupon = vm.exCoup;
        vm.calculation.TradeFlat = vm.tradeFlat;
        if (vm.calcFrom == "price")
        {
            vm.calculation.CalculatePrice = false;
        }
         else
        {
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
        vm.calculation.Holidays = vm.holidays;
        vm.calculations[0] = vm.calculation;
         $http.post(vm.apiPath, vm.calculations)
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
                    vm.price = response.data[0].price;
                }
                vm.pvbp = response.data[0].pvbp;
                vm.issueDate = new Date(response.data[0].issueDate);
                vm.firstPayDate = new Date(response.data[0].firstPayDate);
                vm.nextToLastDate = new Date(response.data[0].nextToLastDate);

                vm.requestJson = JSON.stringify(vm.calculations, null, 2);
                vm.responseJson = JSON.stringify(response.data, null, 2);
                vm.cashFlows = response.data[0].cashFlows;
            }
        },
        function (err) {
            vm.errorMessage = "Calculation Failed: " +  err.data;
        })
        .finally(function () {
            vm.isBusy = false;
        });

        //alert("Calculation USTBill");
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
        vm.previousPay = new Date(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
      vm.nextPay = new Date(vm.maturityDate.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
      vm.issueDate = new Date(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
      vm.issueDate.setFullYear(vm.issueDate.getFullYear() - 3);
      vm.firstPayDate = new Date(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
      vm.firstPayDate.setFullYear(vm.firstPayDate.getFullYear() - 2);
      vm.nextToLastDate = new Date(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);

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

      vm.open = function($event, which) {
        $event.preventDefault();
        $event.stopPropagation();

        $timeout(function () { vm.datepickers[which] = true; });
      };

      vm.dateOptions = {
        'year-format': "'yy'",
        'starting-day': 1
      };

      vm.formats = ['dd-MMMM-yyyy', 'yyyy/MM/dd', 'shortDate'];
      vm.format = vm.formats[0];
        /////////////////////////////////
      vm.openVD = function () {
          $timeout(function () {  vm.opened = true;  });
      };
     }
})();
