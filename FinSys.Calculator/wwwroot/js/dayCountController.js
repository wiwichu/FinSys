(function () {
    'use strict';

    angular
        .module('app')
        .controller('dayCountController', dayCountController);

    dayCountController.$inject = ['$location']; 

    function dayCountController($location) {
        /* jshint validthis:true */
        var vm = this;
        vm.title = 'dayCountController';

        activate();

        function activate() { }
    }
})();
