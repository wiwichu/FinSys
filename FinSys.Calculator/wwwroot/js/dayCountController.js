(function () {
    'use strict';

    angular
        .module('app-calculator')
        .controller('dayCountController', dayCountController);

    function dayCountController($http, $location, $rootScope, uiGridConstants,$uibModal) {
        /* jshint validthis:true */
        var vm = this;
        vm.title = 'dayCountController';
        vm.isBusy = true;
        vm.dayCounts =
                       [
                { rule: "30E/360", days: 0, factor: 0 },
                { rule: "30/360 ISDA(Muni)", days: 0, factor: 0 },
                { rule: "ACT/360", days: 0, factor: 0 },
                { rule: "ACT/365", days: 0, factor: 0 },
                { rule: "ACT/365CD", days: 0, factor: 0 },
                { rule: "30E/360", days: 0, factor: 0 },
                { rule: "ACT/ACT(UST)", days: 0, factor: 0 },
                { rule: "ACT/365L", days: 0, factor: 0 },
                { rule: "ACT/ACT(ISDA)", days: 0, factor: 0 },
                { rule: "30/360 German", days: 0, factor: 0 },
                { rule: "30E+/360", days: 0, factor: 0 },
                { rule: "30/360 US", days: 0, factor: 0 },
                { rule: "ACT/365A", days: 0, factor: 0 },
                { rule: "ACT/366", days: 0, factor: 0 },
                { rule: "ACT/360CD", days: 0, factor: 0 },
                       ];

        vm.protocol = $location.protocol() + "://";
        vm.host = $location.host();
        vm.port = $location.port();
        if (vm.port) {
            vm.port = ":" + vm.port;
        }
        vm.init = function () {
            try {
                if ($rootScope.staticData) {
                    vm.dayCount = $rootScope.staticData.dayCounts;
                    if (vm.dayCount != null && vm.dayCount[0] != null) {
                        vm.selectedDayCount = vm.dayCount[0];
                    }
                }
                else {
                    vm.errorMessage = "Failed to load data: Static Data not Initialized.";
                }
            }
            catch (exception) {
                vm.errorMessage = "Failed to load data: " + exception;
            }
            finally {
                 $rootScope.cfData = null;
                vm.api = "/api/calculator/daycounts";
                vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
                vm.isBusy = false;
            }

        }
        vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
        if (!$rootScope.staticData) {
            vm.api = "/api/staticdata";
            $http.get(vm.api)
                .then(function (response) {
                    $rootScope.staticData = response.data;
                    vm.init();
                }, function (error) {
                    //loghere
                })
            .finally(function () {
                vm.isBusy = false;
            });
        }
        else {
            vm.init();
            vm.isBusy = false;
        }
        vm.cfGridOptions = {
            data: 'vm.dayCounts',
            enableSelectAll: true,
            exporterMenuPdf: false,
            exporterCsvFilename: 'dayCounts.csv', enableGridMenu: true,
            exporterCsvLinkElement: angular.element(document.querySelectorAll(".custom-csv-link-location")),
            enablePaginationControls: true,
            enableRowSelection: true,
            enableRowHeaderSelection: true,
            selectionRowHeaderWidth: 35,
            multiSelect: true,
            paginationPageSize: 25, showGridFooter: true,
            showColumnFooter: true,
            columnDefs: [
                { name: 'Rule', field: 'rule', type: 'date', cellFilter: 'date:"yyyy-MM-dd"' },
                { name: 'Days', field: 'days', type: 'number' },
                { name: 'Factor', field: 'factor', type: 'number' }
            ],
            importerDataAddCallback: function (grid, newObjects) {
                vm.cashFlows = newObjects;
            },
            onRegisterApi: function (gridApi) {
                vm.cfGridApi = gridApi;
            }
        };
        vm.calculate = function () {
            vm.isBusy = true;
            vm.errorMessage = "";
            vm.api = "/api/calculator/dayCounts";
            vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            angular.forEach(vm.dayCounts, function (value, key) {
                value.startDate = new Date(vm.startDate);
                value.endDate = new Date(vm.endDate);
                value.status = "";
                value.message = "";
            }); vm.requestJson = "";
            vm.responseJson = "";
            $http.post(vm.apiPath, vm.dayCounts)
           .then(function (response) {
               if (response.data[0].status) {
                   vm.errorMessage = "Calculation Failed: " + response.data[0].status;
               }
               vm.dayCounts = response.data;
               vm.requestJson = JSON.stringify(vm.dayCounts, null, 2);
               vm.responseJson = JSON.stringify(response.data, null, 2);
           },
           function (err) {
               vm.errorMessage = "Calculation Failed: " + err.data;
           })
           .finally(function () {
               vm.isBusy = false;
           });
        }
        var api = {
            apiPath: vm.apiPath,
            requestJson: vm.requestJson,
            responseJson: vm.responseJson
        };
        vm.getApi = function () {

            var options = {
                templateUrl: "/templates/apiDialog.html",
                controller: function () {
                    this.api = {
                        apiPath: vm.apiPath,
                        requestJson: vm.requestJson,
                        responseJson: vm.responseJson
                    };
                },
                controllerAs: "model"
            };
            $uibModal.open(options);
        }

        ///////////////////// datepicker ///////////////////////
    vm.datepickers = {
        startDate: false,
        endDate: false
    }
    vm.startDate = new UtcDate(vm.now.getFullYear(), vm.now.getMonth(), vm.now.getDate(), 0, 0, 0, 0);
    vm.endDate = new UtcDate();

    vm.showWeeks = true;
    vm.toggleWeeks = function () {
        vm.showWeeks = ! vm.showWeeks;
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
