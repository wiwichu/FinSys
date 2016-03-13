(function () {
    'use strict';

    angular
        .module('app-calculator')
        .factory('helpService',['$uibModal', helpService]);

    function helpService($uibModal) {
        var shinyNewServiceInstance = { test: "test" };
        //return shinyNewServiceInstance;
        return showHelp;
        //{
        //    showHelp: showHelp
        //};
        function showHelp(helpTopic)
        {
            var help = {
                title: "No Help",
                text: "No Help Available.",
                link: "#/Guide"
            };
            switch (helpTopic)
            {
                case "maturitydate" :
                {
                    help = {
                        title: "Maturity Date",
                        text: "Date on which the instrument matures.",
                        link: "#/Guide#maturitydate"
                    };
                }
            }
            var options = {
                templateUrl: "/templates/helpDialog.html",
                controller: function () {
                    this.help = help;
                },
                controllerAs: "model"
            }
            $uibModal.open(options);
        };
    }
})();
