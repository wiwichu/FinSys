(function () {
    'use strict';

    angular
        .module('app-calculator')
        .controller('guideController', guideController);

    function guideController($location, $anchorScroll) {
        /* jshint validthis:true */
        var vm = this;
        vm.title = 'guideController';

        //Redirect to the new location regardless of if it has anchor name
        vm.linkTo = function (id) {
            $location.url(id);
        };
        vm.gotoAnchor = function (x) {
            var newHash = x;
            if ($location.hash() !== newHash) {
                // set the $location.hash to `newHash` and
                // $anchorScroll will automatically scroll to it
                $location.hash(x);
            } else {
                // call $anchorScroll() explicitly,
                // since $location.hash hasn't changed
                $anchorScroll();
            }
        };
    }
})();
