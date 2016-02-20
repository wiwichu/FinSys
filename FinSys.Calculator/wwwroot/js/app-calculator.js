// all-calculator.js
(function () {

    "use strict";
    angular.module("app-calculator", [
        "ngRoute",
        "ui.bootstrap",
        "ui.grid",
        "ui.grid.importer"
    ])
    .config(function ($routeProvider) {
        $routeProvider.when("/", {
            templateUrl: "/views/homeView.html"
        });
        $routeProvider.when("/about", {
            templateUrl: "/views/custCalcView.html"
        });
        //$routeProvider.when("/CustomCalc", {
        //    controller: "calculatorController",
        //    controllerAs: "vm",
        //    templateUrl: "/views/custCalcView.html"
        //});

        //$routeProvider.otherwise({ redirectTo: "/" });
    });

})();