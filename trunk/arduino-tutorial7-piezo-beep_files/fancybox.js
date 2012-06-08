$(document).ready(function() {
   $("a.thickbox").fancybox({
      'speedIn' : 600,
      'speedOut' : 500,
      'transitionIn': 'elastic',
      'transitionOut': 'elastic',
      'easingIn' : 'swing',
      'easingOut' : 'swing',
     'autoDimensions': false,
     'width': 620,
      'height': 400,
     'hideOnContentClick': true,
     'titleShow': false
   });
   $("a.thickbox").attr('rel','group');
   $("a.thickbox img").parent().fancybox({
      'overlayShow' : true,
      'speedIn' : 600,
      'speedOut' : 500,
      'transitionIn': 'elastic',
      'transitionOut': 'elastic',
      'easingIn' : 'swing',
      'easingOut' : 'swing'
   });       
});
