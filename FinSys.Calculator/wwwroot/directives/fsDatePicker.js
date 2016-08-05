(function() {
    'use strict';

    angular
        .module('app-calculator')
        .directive('fsDatePicker', fsDatePicker);

    fsDatePicker.$inject = ['$window'];
    
    function fsDatePicker ($window) {
        // Usage:
        //     <fsDatePicker></fsDatePicker>
        // Creates:
        // 
        var directive = {
            templateUrl: "/templates/fsDatePicker.html",
            link: link,
            restrict: 'E'
        };
        return directive;

        function link(scope, element, attrs) {
        }
    }

})();