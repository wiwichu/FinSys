// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("calculatorController", calculatorController);

    function calculatorController() {

        var vm = this;

        vm.instrumentClass = [{
            name: "German Bund",
            created: new Date()
        },
        {
            name: "US Discount",
            created: new Date()
        }
,
        {
            name: "US TBond",
            created: new Date()
        }
        ];
           

    }
})();