(function($){ 
    $.widget("ud.ud_popup", {
        options: {
            // custom params
            autoopen: false,
            timedelay: 0,
            closeable: true,

            // fancybox params
            scrolling: "auto",
            width: "auto",
            height: "auto",
            minWidth: 0,
            minHeight: 0,
            autoDimensions: true,
            autoCenter: true,
            padding: 0,
            autoSize : true,
            fitToView : false,
            href: null,
            wrapCSS: 'static-content-wrapper',
            afterShow: function() {
                var fancyboxInner = $('.fancybox-inner');
                fancyboxInner.ud_initialize();
            }
        },
        _create: function(){
            $.extend(this.options, this.element.data());

            this.options.href = this.attachAjax(this.options.href || this.element.attr('href'));   

            if(!this.options.closeable){
                this.options.closeBtn = false;
                this.options.modal = true;
            }

            this.element.fancybox(this.options);
            
            if(this.options.autoopen) {
                this.element.hide();
                var that = this;
                setTimeout(function() {
                    that.element.trigger("click");
                }, this.options.timedelay);
            }
        },
        destroy: function(){
        },
        attachAjax: function(href){
            if(href === null) {
                return "";
            }
            
            if( href.indexOf("&displayType=ajax")==-1 &&
                href.indexOf("?displayType=ajax")==-1) {
                var separator = "?";
                if(href.indexOf("?")!=-1) {
                    separator = "&";
                }
                return href + separator + 'displayType=ajax';
            } else {
                return href;
            }
        },
        open: function(params){
            if(params.href){
                params.href = this.attachAjax(params.href);
            }
            $.fancybox.open(params);
        },
        close: function(){
            $.fancybox.close(true);
        }
    });
})(jQuery);
