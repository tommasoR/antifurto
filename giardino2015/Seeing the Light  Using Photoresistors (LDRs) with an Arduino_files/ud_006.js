(function($){
    $.widget("ud.ud_signup_popup_hook", {
        options: {
            postId: 0,
            postUrl: 'https://blog.udemy.com/'
        },
        _create: function(){
            $.extend(this.options, this.element.data());

            $.ajax({
                type: "GET",
                url: "https://www.udemy.com/join/signup-popup-hook-for-blog",
                data: {
                    tc: 'blog.popup',
                    utm_source: "blog",
                    utm_medium: "udemyads",
                    utm_content: "post" + this.options.postId,
                    utm_campaign: "content-marketing-blog-popup",
                    returnUrlAfterLogin: this.options.postUrl,
                    displayType: "ajax"
                },
                success: $.proxy(function(data) {
                    var a = $(data);
                    if(a.length !== 0) {
                        var $body = $(document.body).append(a);
                        $body.ud_initialize();
                    }

                }, this),
                error: $.proxy(function() {
                }, this)
            });
        },
        destroy: function(){
        }
    });
})(jQuery);
