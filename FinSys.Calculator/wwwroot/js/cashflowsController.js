// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("cashflowsController", cashflowsController)
    ;
    
    function cashflowsController($http, $location, $rootScope, uiGridConstants
        ) {

        var vm = this;
        vm.errorMessage = "";
        vm.staticData = [];
        vm.instrumentClass = [];
        vm.selectedInstrumentClass = "";
        vm.opened = false;
        vm.isBusy = true;
        vm.cashFlows = [];
        if ($rootScope.cfData != null) {
            vm.cashFlows = $rootScope.cfData.cashFlows;
            vm.valueDate = $rootScope.cfData.valueDate;
        }
        else {
            vm.valueDate = new Date();
        }
        $rootScope.cfData = null;
        vm.gridOptions = {
            data: 'vm.cashFlows',
            enableSelectAll: true,
            exporterCsvFilename: 'myFile.csv', enableGridMenu: true,
            exporterCsvLinkElement: angular.element(document.querySelectorAll(".custom-csv-link-location")),
            enablePaginationControls: true,
            enableRowSelection: true,
            enableRowHeaderSelection: true,
            selectionRowHeaderWidth: 35,
            multiSelect: true,
            paginationPageSize: 25, showGridFooter: true,
            showColumnFooter: true,
            columnDefs: [
                { name: 'Scheduled Date', field: 'scheduledDate', type: 'date', cellFilter: 'date:"yyyy-MM-dd"', footerCellFilter: 'date', aggregationType: uiGridConstants.aggregationTypes.max },
                { name: 'Adjusted Date', field: 'adjustedDate', type: 'date', cellFilter: 'date:"yyyy-MM-dd"', footerCellFilter: 'date', aggregationType: uiGridConstants.aggregationTypes.max },
                { name: 'Amount', field: 'amount',type: 'number', aggregationType: uiGridConstants.aggregationTypes.sum },
                { name: 'Present Value', field: 'presentValue', type: 'number',enableCellEdit: false, aggregationType: uiGridConstants.aggregationTypes.sum },
                {name: 'Discount Rate',field:'discountRate',type: 'number'}
            ],
            importerDataAddCallback: function (grid, newObjects)
            {
                //vm.cashFlows = [];
                //vm.cashFlows = vm.cashFlows.concat(newObjects);
                vm.cashFlows = newObjects;
            },
            onRegisterApi: function (gridApi) {
                $scope.gridApi = gridApi;
                var cellTemplate = 'ui-grid/selectionRowHeader';   // you could use your own template here
                $scope.gridApi.core.addRowHeaderColumn({ name: 'rowHeaderCol', displayName: '', width: 30, cellTemplate: cellTemplate });
            }
        };
        vm.isBusy = false;
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