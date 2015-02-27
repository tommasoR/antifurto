
(function($) {

	$(function() {
		if(!seen_cookie_message()) {
			show_cookie_message();
			set_seen_cookie_message();
		}

		$('.icc_dismiss_button').click(function(){
			hide_cookie_message();
		});
		$('.icc_delete_button').click(function(){
			remove_cookies();
			window.location.replace("https://duckduckgo.com/");
		});
	});

	function seen_cookie_message() {
		return $.cookie('icc_cookie_message') == 'yes';
	}
	function set_seen_cookie_message() {
		$.cookie('icc_cookie_message', 'yes', { expires: 365 });
	}

	function remove_cookies() {
		$.each($.cookie(), function(key, value){ 
			$.removeCookie(key);
		});
	}

	function show_cookie_message() {
		// Create a margin at the top of the page
		$('html').css('margin-top', $('#icc_message').height());

		// Handle the fixed header in TwentyFourteen
		if( $('.masthead-fixed #masthead').length ) {
			$('.masthead-fixed #masthead').css('margin-top', $('#icc_message').height());
			$('#icc_message').css({'position': 'fixed', 'z-index': 4});
		}

		$('#icc_message').show();
	}

	function hide_cookie_message() {
		$('html').animate({'margin-top': 0});
		$('.masthead-fixed #masthead').animate({'margin-top': 0});
		$('#icc_message').hide();
	}

})(jQuery);
