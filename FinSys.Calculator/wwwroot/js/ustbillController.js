// ustbillController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("ustbillController", ustbillController)
    ;
    
    function ustbillController($http, $location,$window, $rootScope
        , $uibModal, helpService, $timeout
        ) {

        var vm = this;
        vm.errorMessage = "";
        vm.instrumentClass = [];
        vm.selectedInstrumentClass = "";
        vm.opened = false;
        vm.isBusy = true;
        vm.price = 0.00;
        vm.duration = 0.00;
        vm.modDuration = 0.00;
        vm.convexity = 0.00;
        vm.pvbp = 0.00;
        vm.cvxPvbp = 0.00;
        vm.ustbill = {};
        vm.ustbill.discount = 0.00;
        vm.ustbill.be = 0.00;
        vm.ustbill.mmYield = 0.00;
        $rootScope.cfData = null;
        //vm.api = "/api/staticdata";
        vm.protocol = $location.protocol() + "://";
        vm.host = $location.host();
        vm.port = $location.port();
        vm.cashFlows = [];
        vm.staticData = [];
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
                        vm.selectedYieldMethod = vm.yieldMethod[2];
                    }
                    vm.dayCount = $rootScope.staticData.dayCounts;
                    if (vm.dayCount != null && vm.dayCount[0] != null) {
                        vm.selectedDayCount = vm.dayCount[2];
                    }
                    vm.compoundFrequency = $rootScope.staticData.payFrequency;
                    if (vm.compoundFrequency != null && vm.compoundFrequency[0] != null) {
                        vm.selectedCompoundFrequency = vm.compoundFrequency[0];
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
        vm.goToCashFlows = function()
        {
            if (vm.cashFlows && vm.cashFlows.length>0) {
                vm.cfData = {
                    yieldmethod: vm.selectedYieldMethod,
                    daycount: vm.selectedDayCount,
                    frequency: vm.selectedCompoundFrequency,
                    cashFlows: vm.cashFlows,
                    valueDate: vm.ustbill.valueDate
                };
                $rootScope.cfData = vm.cfData;
            }
            $window.location.href = '#/CashFlows';
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
             },
            function (err) {
                vm.errorMessage = "Calculation Failed: " +  err.data;
            })
            .finally(function () {
                vm.isBusy = false;
            });

        }
        vm.maturityDateHelp = function () {
            helpService("maturitydate");
        }
        var that = this;
        var api = {
            apiPath: vm.apiPath,
            requestJson: vm.requestJson,
            responseJson: vm.responseJson
        };
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
            valueDate: false
        }
        vm.valueDate = new Date();
        vm.maturityDate = new Date();
        vm.maturityDate.setFullYear(vm.maturityDate.getFullYear() + 1);
        vm.showWeeks = true;
        vm.toggleWeeks = function () {
            vm.showWeeks = !vm.showWeeks;
        };
        vm.clear = function () {
            vm.maturityDate = null;
        };
        // Disable weekend selection
        vm.disabled = function (date, mode) {
            return (mode === 'day' && (date.getDay() === 0 || date.getDay() === 6));
        };
        vm.toggleMin = function () {
            vm.minDate = (vm.minDate) ? null : new Date();
        };
        vm.toggleMin();
        vm.open = function ($event, which) {
            $event.preventDefault();
            $event.stopPropagation();
            $timeout(function ()
            {
                angular.forEach(vm.datepickers, function (value, key) {
                    if (key == which)
                    {
                        vm.datepickers[key] = true;
                    }
                    else
                    {
                        vm.datepickers[key] = false;
                    }

                });
            });
        };
        vm.dateOptions = {
            'year-format': "'yy'",
            'starting-day': 1
        };
        vm.formats = ['dd-MMMM-yyyy', 'yyyy/MM/dd', 'shortDate'];
        vm.format = vm.formats[0];
        /////////////////////////////////
        vm.openVD = function () {
            $timeout(function () { vm.opened = true; });
        };
    }
})();
