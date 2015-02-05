(function($) {
    $.fn.ud_initialize = function(options) {
        var root = $(this);
        $(".ud-popup", root).ud_popup();
        $(".ud-signup-popup-hook", root).ud_signup_popup_hook();
        $(".ud-legacy-formajaxify", root).ud_legacy_formajaxify();
        $(".ud-google-plus-signup", root).ud_google_plus_signup();

    };
})(jQuery);