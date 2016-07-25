(function () {
    'use strict';

    angular
        .module('app-calculator')
        .factory('alertService',['$uibModal', helpService]);

    function helpService($uibModal) {
        var shinyNewServiceInstance = { test: "test" };
        //return shinyNewServiceInstance;
        return showAlert;
        //{
        //    showHelp: showHelp
        //};
        function showAlert(title,message,details)
        {
            var data = {
                title: title,
                message: message,
                details: details
            };
            var options = {
                templateUrl: "/templates/alertDialog.html",
                controller: function () {
                    this.data = data;
                },
                controllerAs: "model"
            }
            $uibModal.open(options);
        };
    }
})();
