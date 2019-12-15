// layoutController.js
(function () {

    "use strict";

    angular.module("app-calculator")
    .controller("layoutController", layoutController)
    ;
    
    function layoutController($http, $location,$window, $rootScope) {

        var vm = this;
        vm.back = function () {
            $window.history.back();
        };
        if (!$rootScope.staticData) {
            vm.api = "/api/staticdata";
            vm.protocol = $location.protocol() + "://";
            vm.host = $location.host();
            vm.port = $location.port();
            vm.staticData = [];
            if (vm.port) {
                vm.port = ":" + vm.port;
            }
            vm.apiPath = vm.protocol + vm.host + vm.port + vm.api;
            $http.get(vm.api)
                .then(function (response) {
                    vm.staticData = response.data;
                    $rootScope.staticData = vm.staticData;

                }, function (error) {
                    //loghere
                })
            .finally(function () {
                //?
            });
        }
    }
})();
