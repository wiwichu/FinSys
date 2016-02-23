﻿// calculatorController.js
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
            vm.cashFlows = $rootScope.cfData;
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
                vm.cashFlows = [];
                vm.cashFlows = vm.cashFlows.concat(newObjects);
            },
            onRegisterApi: function (gridApi) {
                $scope.gridApi = gridApi;
                var cellTemplate = 'ui-grid/selectionRowHeader';   // you could use your own template here
                $scope.gridApi.core.addRowHeaderColumn({ name: 'rowHeaderCol', displayName: '', width: 30, cellTemplate: cellTemplate });
            }
        };
        vm.isBusy = false;
    }
})();