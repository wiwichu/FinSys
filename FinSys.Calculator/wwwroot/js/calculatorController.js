// calculatorController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("calculatorController", calculatorController)
    .controller('DatePickerController', DatePickerController);
    
    DatePickerController.$inject = ['$scope'];
 
    function DatePickerController($scope) {
        $scope.open = function ($event) {
            $event.preventDefault();
            $event.stopPropagation();
 
            $scope.opened = true;
        };
        $scope.ReleaseDate = new Date();
    }

    function calculatorController($http) {

        var vm = this;
        vm.errorMessage = "";
        vm.staticData = [];
        vm.instrumentClass = [];
        vm.selectedInstrumentClass = "";
        vm.opened = false;
        vm.isBusy = true;
        vm.price = 0.00;
        vm.discount = 0.00;
        vm.be = 0.00;
        vm.mmYield = 0.00;
        vm.duration = 0.00;
        vm.modDuration = 0.00;
        vm.convexity = 0.00;
        vm.pvbp = 0.00;
        vm.cvxPvbp = 0.00;
        $http.get("/api/staticdata")
            .then(function (response) {
                vm.instrumentClass = response.data.instrumentClasses;
                if (response.data.instrumentClasses != null && response.data.instrumentClasses[0] != null)
                {
                    vm.selectedInstrumentClass = response.data.instrumentClasses[0];
                }
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
        vm.calcUSTBill = function (selectedItem) {
            alert("Calculation USTBill");
        }
        ///////////////////// datepicker ///////////////////////
              vm.datepickers = {
        maturityDate: false,
        valueDate: false
      }
      vm.maturityDate = new Date();
      vm.valueDate = new Date();

      vm.showWeeks = true;
      vm.toggleWeeks = function () {
        vm.showWeeks = ! vm.showWeeks;
      };

      vm.clear = function () {
        vm.maturityDate = null;
      };

      // Disable weekend selection
      vm.disabled = function(date, mode) {
        return ( mode === 'day' && ( date.getDay() === 0 || date.getDay() === 6 ) );
      };

      vm.toggleMin = function() {
        vm.minDate = ( vm.minDate ) ? null : new Date();
      };
      vm.toggleMin();

      vm.open = function($event, which) {
        $event.preventDefault();
        $event.stopPropagation();

        $timeout(function () { vm.datepickers[which] = true; });
      };

      vm.dateOptions = {
        'year-format': "'yy'",
        'starting-day': 1
      };

      vm.formats = ['dd-MMMM-yyyy', 'yyyy/MM/dd', 'shortDate'];
      vm.format = vm.formats[0];
        /////////////////////////////////
      vm.openVD = function () {
          $timeout(function () {  vm.opened = true;  });
      };
     }
})();