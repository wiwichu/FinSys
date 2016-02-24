// cashflowsController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("cashflowsController", cashflowsController)
    ;
    
    function cashflowsController($http, $location, $rootScope, uiGridConstants
        ) {

        var vm = this;
        vm.errorMessage = "";
        vm.opened = false;
        vm.isBusy = true;
        vm.cashFlows = [];
        vm.curveData = [];
        if ($rootScope.cfData != null) {
            vm.cashFlows = $rootScope.cfData.cashFlows;
            vm.valueDate = $rootScope.cfData.valueDate;
        }
        else {
            vm.valueDate = new Date();
        }
        $rootScope.cfData = null;
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
                $scope.gridApi = gridApi;
                var cellTemplate = 'ui-grid/selectionRowHeader';   // you could use your own template here
                $scope.gridApi.core.addRowHeaderColumn({ name: 'rowHeaderCol', displayName: '', width: 30, cellTemplate: cellTemplate });
            }
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
                $scope.gridApi = gridApi;
                var cellTemplate = 'ui-grid/selectionRowHeader';   // you could use your own template here
                $scope.gridApi.core.addRowHeaderColumn({ name: 'rowHeaderCol', displayName: '', width: 30, cellTemplate: cellTemplate });
            }
        };
        vm.isBusy = false;
        vm.api = "/api/staticdata";
        vm.protocol = $location.protocol() + "://";
        vm.host = $location.host();
        vm.port = $location.port();
        vm.cashFlows = [];
        if (vm.port) {
            vm.port = ":" + vm.port;
        }
        vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
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
            vm.isBusy = false;
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
        vm.payFrequencyChanged = function () {
            alert("Selected Pay Frequency: " + vm.selectedPayFrequency);
        }
        vm.payFrequencySelected = function (selectedItem) {
            alert("Selected Pay Frequency: " + selectedItem);
        }
        vm.interpolationMethodChanged = function () {
            alert("Selected Interpolation Method: " + vm.selectedInterpolationMethod);
        }
        vm.interpolationMethodSelected = function (selectedItem) {
            alert("Selected Interpolation Method: " + selectedItem);
        }
        vm.useCurve = function () {
        };
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