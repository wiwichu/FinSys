// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("cashflowsController", cashflowsController)
    ;
    
    function cashflowsController($http, $location,$rootScope
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
            enableGridMenu: true,
            columnDefs: [
                {name: 'Scheduled Date', field:'scheduledDate'},
                {name: 'Adjusted Date',field:'adjustedDate'},
                {name: 'Amount',field:'amount'},
                {name: 'Present Value', field:'presentValue'},
                {name: 'Discount Rate',field:'discountRate'}
            ],
            importerDataAddCallback: function(grid,newObjects)
            {
                vm.cashFlows = [];
                vm.cashFlows = vm.cashFlows.concat(newObjects);
            }
        };
        vm.isBusy = false;
    }
})();