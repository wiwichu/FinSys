// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("calculatorController", calculatorController);

    function calculatorController($http) {

        var vm = this;
        vm.errorMessage = "";
        vm.staticData = [];
        vm.instrumentClass = [];
        vm.selectedInstrumentClass = "";
        vm.isBusy = true;
        $http.get("/api/staticdata")
            .then(function (response) {
                vm.instrumentClass = response.data.instrumentClasses;
                //vm.selectedInstrumentClass = response.data.instrumentClasses[0];
            }, function (error) {
                vm.errorMessage = "Failed to load data: " + error;
            })
        .finally(function () {
            vm.isBusy = false;
        });
        vm.instrumentClassChanged = function () {
            alert("Selected Instrument: " + vm.selectedInstrumentClass);
        }
        vm.instrumentClassSelected = function (selectedItem) {
            alert("Selected Instrument: " + selectedItem);
        }
    }

})();