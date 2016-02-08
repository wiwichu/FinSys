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

    function calculatorController($http,$location) {

        var vm = this;
        vm.errorMessage = "";
        vm.staticData = [];
        vm.instrumentClass = [];
        vm.selectedInstrumentClass = "";
        vm.opened = false;
        vm.isBusy = true;
        vm.price = 0.00;
        vm.duration = 0.00;
        vm.modDuration = 0.00;
        vm.convexity = 0.00;
        vm.pvbp = 0.00;
        vm.cvxPvbp = 0.00;
        vm.ustbill = {};
        vm.ustbill.discount = 0.00;
        vm.ustbill.be = 0.00;
        vm.ustbill.mmYield = 0.00;
        vm.api = "/api/staticdata";
        vm.protocol = $location.protocol() + "://";
        vm.host = $location.host();
        vm.port = $location.port();
        if (vm.port)
        {
            vm.port = ":" + vm.port;
        }
        vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
        $http.get(vm.api)
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
            vm.isBusy = true;
            vm.errorMessage = "";
            vm.api = "/api/calculator/ustbill";
            vm.protocol = $location.protocol() + "://";
            vm.host = $location.host();
            vm.port = $location.port();
            if (vm.port) {
                vm.port = ":" + vm.port;
            }
            vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            vm.ustbill.maturityDate = vm.maturityDate;
            vm.ustbill.valueDate = vm.valueDate;
            switch (vm.ustbill.calcfrom)
            {
                case 'price':
                    vm.ustbill.calcsource = vm.price;
                    break;
                case 'discount':
                    vm.ustbill.calcsource = vm.discount;
                    break;
                case 'be':
                    vm.ustbill.calcsource = vm.be;
                    break;
                case 'mmyield':
                    vm.ustbill.calcsource = vm.mmYield;
                    break;
                default:
                    vm.errorMessage = "Invalid Calculation Choice";
                    return;
                    break;
            }
            $http.post(vm.apiPath, vm.ustbill)
            .then(function (response) {
                vm.ustbill.be = response.data.bondEquivalent;
                vm.convexity = response.data.convexity;
                vm.cvxPvbp = response.data.convexityAdjustedPvbp;
                vm.ustbill.discount = response.data.discount;
                vm.duration = response.data.duration;
                vm.ustbill.mmYield = response.data.mmYield;
                vm.modDuration = response.data.modifiedDuration;
                vm.price = response.data.price;
                vm.pvbp = response.data.pvbp;
            },
            function (err) {
                vm.errorMessage = "Calculation Failed: " +err;
            })
            .finally(function () {
                vm.isBusy = false;
            });

            //alert("Calculation USTBill");
        }
        vm.getApi = function () {
            alert(vm.apiPath);
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