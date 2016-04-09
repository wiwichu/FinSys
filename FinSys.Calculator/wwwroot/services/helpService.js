﻿(function () {
    'use strict';

    angular
        .module('app-calculator')
        .factory('helpService',['$uibModal', helpService]);

    function helpService($uibModal, $timeout) {
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
                    break;
                }
                case "daycount":
                    {
                        help = {
                            title: "Day Count",
                            text: "Rules for calculating days in a period and payment factor.",
                            link: "#/Guide#daycount"
                        };
                        break;
                    }
            }
            var options = {
                templateUrl: "/templates/helpDialog.html",
                controller: function ( $uibModalInstance) {
                    this.help = help;
                },
                controllerAs: "model"
            }
            var  theModal = $uibModal.open(options);
        };
    }
})();
