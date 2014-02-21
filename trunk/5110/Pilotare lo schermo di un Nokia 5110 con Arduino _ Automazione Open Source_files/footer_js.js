var site = function() {
		this.navLi = jQuery('#nav li').children('ul').hide().end();
		this.init();};
	site.prototype = {
		init : function() {
		this.setMenu();},
		setMenu : function() {
			$.each(this.navLi, function() {
				if ( jQuery(this).children('ul')[0] ) {
					jQuery(this).append('<span />').children('span').addClass('hasChildren') }});
			this.navLi.hover(function() {
				jQuery(this).find('> ul').stop(true, true).slideDown('slow','easeOutBounce');}, 
			function(){
				jQuery(this).find('> ul').stop(true, true).hide();});} }
var topsite = function() {
		this.navLi = jQuery('#top_nav li').children('ul').hide().end();
		this.init();};
	topsite.prototype = {
		init : function() {
		this.setMenu();},
		setMenu : function() {
			$.each(this.navLi, function() {
				if ( jQuery(this).children('ul')[0] ) {
					jQuery(this).append('<span />').children('span').addClass('hasChildren') }});
			this.navLi.hover(function() {
				jQuery(this).find('> ul').stop(true, true).slideDown('slow','easeOutBounce');}, 
			function(){
				jQuery(this).find('> ul').stop(true, true).hide();});} }				
jQuery(document).ready(function(e) { 
		new site();   
		new topsite(); 
	});
	