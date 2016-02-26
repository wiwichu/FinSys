// cashflowsController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("cashflowsController", cashflowsController)
    ;
    
    function cashflowsController($http, $location, $rootScope, uiGridConstants,$uibModal
        ) {

        var vm = this;
        vm.errorMessage = "";
        vm.opened = false;
        vm.isBusy = true;
        vm.cashFlows = [];
        vm.curveData = [];
        vm.cfGridOptions = {
            data: 'vm.cashFlows',
            enableSelectAll: true,
            exporterCsvFilename: 'cashFlows.csv', enableGridMenu: true,
            exporterCsvLinkElement: angular.element(document.querySelectorAll(".custom-csv-link-location")),
            enablePaginationControls: true,
            enableRowSelection: true,
            enableRowHeaderSelection: true,
            selectionRowHeaderWidth: 35,
            multiSelect: true,
            paginationPageSize: 25, showGridFooter: true,
            showColumnFooter: true,
            columnDefs: [
                { name: 'Scheduled Date', field: 'scheduledDate', type: 'date', cellFilter: 'date:"yyyy-MM-dd"', footerCellFilter: 'date' },
                { name: 'Adjusted Date', field: 'adjustedDate', type: 'date', cellFilter: 'date:"yyyy-MM-dd"', footerCellFilter: 'date' },
                { name: 'Amount', field: 'amount',type: 'number', aggregationType: uiGridConstants.aggregationTypes.sum },
                { name: 'Present Value', field: 'presentValue', type: 'number',enableCellEdit: false, aggregationType: uiGridConstants.aggregationTypes.sum },
                {name: 'Discount Rate',field:'discountRate',type: 'number'}
            ],
            importerDataAddCallback: function (grid, newObjects)
            {
                vm.cashFlows = newObjects;
            },
            onRegisterApi: function (gridApi) {
                vm.cfGridApi = gridApi;
            }
        };
        vm.addCf = function () {
            vm.cashFlows.push({
                "Scheduled Date": new Date(),
                "Adjusted Date": new Date(),
                "Amount": 0,
                "Present Value": 0,
                "Discount Rate": 0
            });
        };
        vm.deleteSelectedCf = function () {
            angular.forEach(vm.cfGridApi.selection.getSelectedRows(), function (data, index) {
                vm.cashFlows.splice(vm.cashFlows.lastIndexOf(data), 1);
            });
        };
        vm.curveGridOptions = {
            data: 'vm.curveData',
            enableSelectAll: true,
            exporterCsvFilename: 'curve.csv', enableGridMenu: true,
            exporterCsvLinkElement: angular.element(document.querySelectorAll(".custom-csv-link-location")),
            enablePaginationControls: true,
            enableRowSelection: true,
            enableRowHeaderSelection: true,
            selectionRowHeaderWidth: 35,
            multiSelect: true,
            paginationPageSize: 25, showGridFooter: true,
            showColumnFooter: true,
            columnDefs: [
                { name: 'Date', field: 'date', type: 'date', cellFilter: 'date:"yyyy-MM-dd"' },
                { name: 'Rate', field: 'rate', type: 'number' }
            ],
            importerDataAddCallback: function (grid, newObjects) {
                vm.curveData = newObjects;
            },
            onRegisterApi: function (gridApi) {
                vm.curveGridApi = gridApi;
             }
        };
        vm.addCurve = function () {
            vm.curveData.push({
                "Date": new Date(),
                "Rate": 0
            });
        };
        vm.deleteSelectedCurve = function () {
            angular.forEach(vm.curveGridApi.selection.getSelectedRows(), function (data, index) {
                vm.curveData.splice(vm.curveData.lastIndexOf(data), 1);
            });
        };
        vm.isBusy = false;
        vm.api = "/api/staticdata";
        vm.protocol = $location.protocol() + "://";
        vm.host = $location.host();
        vm.port = $location.port();
        if (vm.port) {
            vm.port = ":" + vm.port;
        }
        vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
        vm.cashFlows = [];
        vm.staticData = [];
        vm.selectedYieldMethod = "";
        vm.selectedDayCount = "";
        vm.selectedCompoundFrequency = "";
        vm.selectedInterpolationMethod = "";
        $http.get(vm.api)
            .then(function (response) {
                vm.yieldMethod = response.data.yieldMethods;
                if (vm.yieldMethod != null && vm.yieldMethod[0] != null) {
                    vm.selectedYieldMethod = vm.yieldMethod[0];
                }
                vm.dayCount = response.data.dayCounts;
                if (vm.dayCount != null && vm.dayCount[0] != null) {
                    vm.selectedDayCount = vm.dayCount[0];
                }
                vm.compoundFrequency = response.data.payFrequency;
                if (vm.compoundFrequency != null && vm.compoundFrequency[0] != null) {
                    vm.selectedCompoundFrequency = vm.compoundFrequency[0];
                }
                vm.interpolationMethod = response.data.interpolationMethods;
                if (vm.interpolationMethod != null && vm.interpolationMethod[0] != null) {
                    vm.selectedInterpolationMethod = vm.interpolationMethod[0];
                }
            }, function (error) {
                vm.errorMessage = "Failed to load data: " + error;
            })
        .finally(function () {
            if ($rootScope.cfData != null) {
                vm.cashFlows = $rootScope.cfData.cashFlows;
                vm.valueDate = $rootScope.cfData.valueDate;
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
        });
        vm.yieldMethodChanged = function () {
            alert("Selected Yield Method: " + vm.selectedYieldMethod);
        }
        vm.yieldMethodSelected = function (selectedItem) {
            alert("Selected Yield Method: " + selectedItem);
        }
        vm.dayCountChanged = function () {
            alert("Selected Day Count: " + vm.selectedDayCount);
        }
        vm.dayCountSelected = function (selectedItem) {
            alert("Selected Day Count: " + selectedItem);
        }
        vm.compoundFrequencyChanged = function () {
            alert("Selected Pay Frequency: " + vm.selectedCompoundFrequency);
        }
        vm.compoundFrequencySelected = function (selectedItem) {
            alert("Selected Pay Frequency: " + selectedItem);
        }
        vm.interpolationMethodChanged = function () {
            alert("Selected Interpolation Method: " + vm.selectedInterpolationMethod);
        }
        vm.interpolationMethodSelected = function (selectedItem) {
            alert("Selected Interpolation Method: " + selectedItem);
        }
        vm.getPresentValues = function () {
            vm.cashflowsPricing =
                {
                    CashFlows: vm.cashFlows,
                    Yieldmethod: vm.selectedYieldMethod,
                    DiscountFrequency: vm.selectedCompoundFrequency,
                    DayCount: vm.selectedDayCount,
                    ValueDate: vm.valueDate,
                    RateCurve: vm.curveData,
                    Interpolation: vm.selectedInterpolationMethod,
                    PriceFromCurve: vm.useCurve
                };
            $http.post(vm.apiPath, vm.cashflowsPricing)
           .then(function (response) {
               vm.cashFlows = response.data;
               vm.requestJson = JSON.stringify(vm.cashflowsPricing, null, 2);
               vm.responseJson = JSON.stringify(response.data, null, 2);
           },
           function (err) {
               vm.errorMessage = "Calculation Failed: " + err.data;
           })
           .finally(function () {
               vm.isBusy = false;
           });

        };

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
             valueDate: false
        }
        //vm.valueDate = new Date();
        vm.showWeeks = true;
        vm.toggleWeeks = function () {
            vm.showWeeks = !vm.showWeeks;
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
    }
})();