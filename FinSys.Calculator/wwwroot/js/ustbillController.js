// ustbillController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("ustbillController", ustbillController)
    ;
    
    function ustbillController($http, $location,$window, $rootScope
        , $uibModal
        ) {

        var vm = this;
        vm.errorMessage = "";
        vm.staticData = [];
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
        vm.api = "/api/staticdata";
        vm.protocol = $location.protocol() + "://";
        vm.host = $location.host();
        vm.port = $location.port();
        vm.cashFlows = [];
        if (vm.port)
        {
            vm.port = ":" + vm.port;
        }
        vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
        $http.get(vm.api)
            .then(function (response) {
                vm.instrumentClass = response.data.instrumentClasses;
                if (response.data.instrumentClasses != null && response.data.instrumentClasses[0] != null)
                {
                    vm.selectedInstrumentClass = response.data.instrumentClasses[0];
                }
            }, function (error) {
                vm.errorMessage = "Failed to load data: " + error;
            })
        .finally(function () {
            vm.isBusy = false;
        });
        vm.instrumentClassChanged = function () {
            alert("Selected Instrument: " + vm.selectedInstrumentClass);
        }
        vm.instrumentClassSelected = function (selectedItem) {
            alert("Selected Instrument: " + selectedItem);
        }
        vm.goToCashFlows = function()
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
            valueDate: false
        }
        vm.maturityDate = new Date();
        vm.valueDate = new Date();
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
            $timeout(function () { vm.opened = true; });
        };
    }
})();
