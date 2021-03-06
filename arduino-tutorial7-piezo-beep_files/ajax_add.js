$(document).ready(function () {
	$('#add_to_cart').removeAttr('onclick');

	$('#add_to_cart').click(function () {
		$.ajax({
			type: 'post',
			url: 'index.php?route=module/cart/callback',
			dataType: 'html',
			data: $('#product :input'),
			success: function (html) {
				$('#module_cart .middle').html(html);
			},	
			complete: function () {
				var image = $('#image').offset();
				var cart  = $('#module_cart').offset();
	
				$('#image').before('<img src="' + $('#image').attr('src') + '" id="temp" style="position: absolute; top: 40px; left: ' + image.left + 'px;" />');
	
				params = {
					top : cart.top -200 + 'px',
					left : cart.left + 'px',
					opacity : 0.0,
					width : $('#module_cart').width(),  
					height : $('#module_cart').height()
				};		
	
				$('#temp').animate(params, 'slow', false, function () {
					$('#temp').remove();
				});		
								
				$('#module_cart').addClass("highlightcart");
				$("#module_cart_middle").css("background","#F7F7F7");
			}			
		});			
	});			
});