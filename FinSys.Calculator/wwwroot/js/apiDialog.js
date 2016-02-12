(function (module) {
    var apiDialog = function (
        $uibModal
        ) {
        return function (api) {
            var options = {
                templateUrl: "templates/apiDialog.html",
                controller: function () {
                    this.api = api;
                },
                controllerAs: "model"
            };
           $uibModal.open(options);
        };
    };
    module.factory("apiDialog", apiDialog)
}(angular.module("app-calculator")));