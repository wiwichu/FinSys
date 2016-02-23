// layoutController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("layoutController", layoutController)
    ;
    
    function layoutController($window) {

        var vm = this;
        vm.back = function () {
            $window.history.back();
        };
    }
})();
