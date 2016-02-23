// all-calculator.js
(function () {

    "use strict";
    angular.module("app-calculator", [
        "ngRoute",
        "ui.bootstrap",
        "ui.grid",
        "ui.grid.importer",
        'ui.grid.selection',
        "ui.grid.exporter",
        "ui.grid.edit"
    ])
    .config(function ($routeProvider) {
        $routeProvider.when("/", {
            templateUrl: "/views/calculatorsView.html"
        });
        $routeProvider.when("/USTBill", {
            controller: "calculatorController",
            controllerAs: "vm",
            templateUrl: "/views/usTBillView.html"
        });
        $routeProvider.when("/CashFlows", {
            controller: "cashflowsController",
            controllerAs: "vm",
            templateUrl: "/views/cashFlowsView.html"
        });
        //$routeProvider.when("/CustomCalc", {
        //    controller: "calculatorController",
        //    controllerAs: "vm",
        //    templateUrl: "/views/custCalcView.html"
        //});

        $routeProvider.otherwise({ redirectTo: "/" });
    });

})();