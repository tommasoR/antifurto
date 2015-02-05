(function($){
    $.widget("ud.ud_legacy_formajaxify", {
        options: {},
        displayType: 'json',
        form: null,
        formItems: null,
        _create: function() {

            console.log('legacy init');

            this.form = this.element;
            this.formItems = $("input,select", this.form);

            this.submitBtn = this.form.find('input[type="submit"]');
            this.loader = this.form.find('.js-bottom-loader');
            this.formItems.focus(this.formItemsChangeCallback);

            this.formItems.on("keypress", $.proxy(this, "formItemsKeyPress"));

            $(".form-bottom .signup-btn",this.element).click(this.formSubmit.bind(this));
            $(".form-bottom .login-btn", this.element).click(this.formSubmit.bind(this));
            this.element.submit(this.formSubmit.bind(this));
        },
        destroy: function(){
        },
        formSubmit: function(event) {
            event.preventDefault();
            this.loader.removeClass('hidden');
            $.ajax({
                type: 'post',
                dataType: 'json',
                url: this.form.attr('action'),
                data : this.form.serialize()  + "&displayType=" + this.displayType,
                success: this.successResponse.bind(this)
            });
        },
        successResponse: function(response) {
            if(typeof response.error == "undefined") {
                $(location).attr('href', response.returnUrl);
            } else {
                this.loader.addClass("hidden");
                $(".error", this.form).addClass("none").html("");
                var itemErrors = response.error.data.itemErrors;
                var formErrors = response.error.data.formErrors;
                for(var prop in itemErrors) {

                    // For signup / login forms at home page
                    var formItem = $(".form-item." + prop, this.form);
                    $("#" + prop, formItem).addClass("error");
                    $("span.error-text", formItem).text($("<div/>").html(itemErrors[prop]).text()).addClass("block");

                    // For every other form that is rendered by PHP's $form->render() method.
                    var formItem = $("#form-item-" + prop, this.form);
                    $(".tooltip-reference", formItem).addClass("field-error");
                    $(".tooltip-reference .form-tooltip", formItem)
                        .after("<div class='form-tooltip black-tooltip arrow-left medium error-msg outside-error-msg'>"
                        + "<span class='arrow'></span>"
                        + $("<div/>").html(itemErrors[prop]).text()
                        + "</div>");
                }
                if(formErrors) {
                    $(".form-errors", this.form).text($("<div/>").html(formErrors).text()).removeClass("none");
                }
            }
        },
        formItemsChangeCallback: function(event) {
            var formItem = $(this).parent();

            if(!$(".form-errors", this.form).hasClass("none")) {
                setTimeout(function(){
                    $(".form-errors", this.form).html('').addClass("none");
                }.bind(this), 500);
            }

            $("input", formItem).removeClass("error");
            $("span.error-text",formItem).removeClass("block").html('');
            formItem.siblings('.form-errors').html('').addClass("none");
            $(".tooltip-reference .outside-error-msg", this.form).remove();
            $(".tooltip-reference", this.form).removeClass("field-error");
        },
        formItemsKeyPress: function(event) {
            if(event.which === 13) {
                this.formSubmit(event);
            }
        }
    });
})(jQuery);
