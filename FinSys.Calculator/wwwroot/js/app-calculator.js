// all-calculator.js
(function () {

    "use strict";
    angular.module("app-calculator", [
        "ngRoute",
        "ui.bootstrap"
    ])
    .config(function ($routeProvider) {
        $routeProvider.when("/", {
            controller: "calculatorController",
            controllerAs: "vm",
            templateUrl: "/views/custCalcView.html"
        });

        $routeProvider.otherwise({ redirectTo: "/" });
    });

})();