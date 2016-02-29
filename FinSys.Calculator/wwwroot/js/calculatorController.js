// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("calculatorController", calculatorController)
    ;
    
    function calculatorController($http, $location,$window, $rootScope
        //, apiDialog
        , $uibModal
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
        vm.opened = false;
        vm.isBusy = true;
        vm.price = 0.00;
        vm.yield = 0.00;
        vm.interestRate = 0.00;
        vm.interest = 0.00;
        vm.dirtyPrice = 0.00;
        vm.interestDays = 0;
        vm.duration = 0.00;
        vm.modDuration = 0.00;
        vm.convexity = 0.00;
        vm.pvbp = 0.00;
        vm.cvxPvbp = 0.00;
        vm.ustbill = {};
        vm.ustbill.discount = 0.00;
        vm.ustbill.be = 0.00;
        vm.ustbill.mmYield = 0.00;
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
         vm.init = function () {
            try {
                if ($rootScope.staticData) {
                    vm.instrumentClass = $rootScope.staticData.instrumentClasses;
                    if ($rootScope.staticData.instrumentClasses != null && $rootScope.staticData.instrumentClasses[0] != null) {
                        vm.selectedInstrumentClass = $rootScope.staticData.instrumentClasses[0];
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
        vm.instrumentClassChanged = function () {
            alert("Selected Instrument: " + vm.selectedInstrumentClass);
        }
        vm.instrumentClassSelected = function (selectedItem) {
            alert("Selected Instrument: " + selectedItem);
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
                { name: 'HoliDate', field: 'holiDate', type: 'date', cellFilter: 'date:"yyyy-MM-dd"', footerCellFilter: 'date' },
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
        vm.calcUSTBill = function (selectedItem) {
            vm.isBusy = true;
            vm.errorMessage = "";
            vm.api = "/api/calculator/ustbill";
            vm.protocol = $location.protocol() + "://";
            vm.host = $location.host();
            vm.port = $location.port();
            if (vm.port) {
                vm.port = ":" + vm.port;
            }
            vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            vm.ustbill.maturityDate = vm.maturityDate;
            vm.ustbill.valueDate = vm.valueDate;
            switch (vm.ustbill.calcfrom)
            {
                case 'price':
                    vm.ustbill.calcsource = vm.price;
                    break;
                case 'discount':
                    vm.ustbill.calcsource = vm.discount;
                    break;
                case 'be':
                    vm.ustbill.calcsource = vm.be;
                    break;
                case 'mmyield':
                    vm.ustbill.calcsource = vm.mmYield;
                    break;
                default:
                    vm.errorMessage = "Invalid Calculation Choice";
                    return; 
                    break;
            }
            vm.requestJson = "";
            vm.responseJson = "";
            $http.post(vm.apiPath, vm.ustbill)
            .then(function (response) {
                vm.ustbill.be = response.data.bondEquivalent;
                vm.convexity = response.data.convexity;
                vm.cvxPvbp = response.data.convexityAdjustedPvbp;
                vm.ustbill.discount = response.data.discount;
                vm.duration = response.data.duration;
                vm.ustbill.mmYield = response.data.mmYield;
                vm.modDuration = response.data.modifiedDuration;
                vm.price = response.data.price;
                vm.pvbp = response.data.pvbp;
                vm.requestJson = JSON.stringify(vm.ustbill,null,2);
                vm.responseJson = JSON.stringify(response.data, null, 2);
                vm.cashFlows = response.data.cashFlows;
                vm.cfData= {
                            cashFlows : vm.cashFlows,
                            valueDate: vm.ustbill.valueDate
                };
                $rootScope.cfData = vm.cfData;
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
        valueDate: false
      }
      vm.maturityDate = new Date();
      vm.previousPay = new Date();
      vm.nextPay = new Date();
      vm.valueDate = new Date();

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
