(function($){
    $.widget("ud.ud_google_plus_signup", {
        options: {
            clientid: null,
            serverurl: null,
            returnurl: null
        },
        _create: function(){
            $.extend(this.options, this.element.data());

            if(this.options.clientid && this.options.serverurl) {
                var additionalParams = {
                    'callback': $.proxy(this._signinCallback, this),
                    'clientid': this.options.clientid,
                    'scope': 'https://www.googleapis.com/auth/plus.login https://www.googleapis.com/auth/plus.profile.emails.read',
                    'cookiepolicy': 'single_host_origin',
                    'redirecturi': 'postmessage',
                    'requestvisibleactions': 'http://schemas.google.com/AddActivity'
                    //'apppackagename': 'com.udemy.android',
                };

                $('.google-btn', this.element).on('click', function() {
                    // Additional params including the callback, the rest of the params will
                    // come from the page-level configuration.
                    gapi.auth.signIn(additionalParams);

                    _gaq.push(['_trackEvent', 'User', 'Signup', 'Google Plus Signup Button']);
                })
            }
        },
        _signinCallback: function (authResult) {
            if (authResult['status']['signed_in']) {
                // Send this authResult to server and register this user
                $.ajax({
                    type: 'post',
                    dataType: 'json',
                    url: this.options.serverurl,
                    data : {
                        accessToken: authResult['access_token'],
                        returnUrl: this.options.returnurl
                    },
                    success: function(response) {
                        //var result = JSON.parse(response);
                        if(response.error) {
                            $(".form-errors", this.element).removeClass("hidden");
                        } else {
                            $(location).attr('href', response.url);
                        }
                    }
                });
            }
        },
        destroy: function(){
        }
    });
})(jQuery);
