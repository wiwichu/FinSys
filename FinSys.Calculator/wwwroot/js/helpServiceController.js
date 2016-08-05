(function () {
    'use strict';

    angular
        .module('app-calculator')
        .controller('helpServiceController', helpServiceController);

    helpServiceController.$inject = ['$location']; 

    function helpServiceController($window) {
            this.help = help;
            this.linkAndClose = function ()
            {
                $window.location.href = help.link;
                $close();
            }
    }
})();
