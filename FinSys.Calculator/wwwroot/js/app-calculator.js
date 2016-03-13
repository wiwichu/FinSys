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
        "ui.grid.edit",
        "ui.grid.resizeColumns",
        "ui.grid.autoResize"
    ])
    .config(function ($routeProvider, $locationProvider) {
        $routeProvider.when("/", {
            templateUrl: "/views/calculatorsView.html"
        });
        $routeProvider.when("/USTBill", {
            controller: "ustbillController",
            controllerAs: "vm",
            templateUrl: "/views/usTBillView.html"
        });
        $routeProvider.when("/CashFlows", {
            controller: "cashflowsController",
            controllerAs: "vm",
            templateUrl: "/views/cashFlowsView.html"
        });
        $routeProvider.when("/CustomCalc", {
            controller: "calculatorController",
            controllerAs: "vm",
            templateUrl: "/views/custCalcView.html"
        });
        $routeProvider.when("/About", {
            controller: "cashflowsController",
            controllerAs: "vm",
            templateUrl: "/views/aboutView.html"
        });
        $routeProvider.when("/Contact", {
            controller: "cashflowsController",
            controllerAs: "vm",
            templateUrl: "/views/contactView.html"
        });
        $routeProvider.when("/DayCount", {
            controller: "dayCountController",
            controllerAs: "vm",
            templateUrl: "/views/dayCountView.html"
        });
        $routeProvider.when("/Guide", {
            controller: "guideController",
            controllerAs: "vm",
            templateUrl: "/views/guideView.html"
        });
 
        $routeProvider.otherwise({ redirectTo: "/" });

        //$locationProvider.html5Mode({
        //    enabled: true
        //    ,requireBase: false
        //    ,rewriteLinks: false
        //});
    })
    .filter('decimal', function () {
        return function (text) {
            var parts = parseFloat(text).toFixed(8).split('.');
            parts[0] = parts[0].replace(/\B(?=(\d{3})+(?!\d))/g, ',');
            return parts.join('.');
        }
    });
})();