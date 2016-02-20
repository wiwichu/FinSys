// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("cashflowsController", cashflowsController)
    ;
    
    function cashflowsController($http, $location
        ) {

        var vm = this;
        vm.errorMessage = "";
        vm.staticData = [];
        vm.instrumentClass = [];
        vm.selectedInstrumentClass = "";
        vm.opened = false;
        vm.isBusy = true;
        vm.isBusy = false;
        vm.cashFlows = [];
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
                vm.cashFlows = vm.cashFlows.concat(newObjects);
            }
        };
    }
})();