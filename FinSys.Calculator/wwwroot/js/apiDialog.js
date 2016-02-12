(function (module) {
    var apiDialog = function (
        //$uibModal
        ) {
        return function (api) {

            var options = {
                templateUrl: "/templates/apiDialog.html",
                controller: function () {
                    //this.api = {
                    //    apiPath: vm.apiPath,
                    //    requestJson: vm.requestJson,
                    //    responseJson: vm.responseJson
                    //};
                    this.api = api;
                },
                controllerAs: "model"
            };
           // $uibModal.open(options);

//////////////////
           // var options = {
           //     templateUrl: "templates/apiDialog.html",
           //     controller: function () {
           //         this.api = api;
           //     },
           //     controllerAs: "model"
           // };
           //$uibModal.open(options);
        };
    };
    module.factory("apiDialog", apiDialog)
    //})();
}(angular.module("apiDialog")));