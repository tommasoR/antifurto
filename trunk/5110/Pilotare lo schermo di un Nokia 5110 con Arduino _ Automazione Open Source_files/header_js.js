jQuery(document).ready(function(){
	jQuery("#backtotop").hide();		
	jQuery(function () {
		jQuery(window).scroll(function () {
			if (jQuery(this).scrollTop() > 50) {
				jQuery('#backtotop').fadeIn();
			} else {
				jQuery('#backtotop').fadeOut();
			}
		});	
		jQuery('#backtotop').click(function () {
			jQuery('body,html').animate({
				scrollTop: 0
			}, 600);
			return false;
		});
	});
});
jQuery(window).load(function(e){
	jQuery('#supernova_slider_wrapper').css({'visibility':'visible'});
	jQuery('#top_most').css({'visibility':'visible'});
		jQuery('#supernova_slider_wrapper').hide();
		jQuery('.loader').hide();
		jQuery('#supernova_slider_wrapper').fadeIn('slow');
		jQuery('#top_most').fadeIn('slow');		
	});