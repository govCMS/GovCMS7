/*
* Author: Jack Taranto
*/

(function($){
    $.fn.extend({
        jumpMenu: function() {

          return this.each(function() {
              var menu = $(this);

              // Create the select
              var menuClasses = menu.attr('class');
              menu.after('<label for="main-menu-select" class="jump-menu-label element-invisible">Menu</label><select id="main-menu-select" class="jump-menu ' + menuClasses + '"></select>');

              var jumpMenu = menu.siblings('select.jump-menu');
							jumpMenu.append('<option value="" selected="selected">Sections</option>');
              menu.children('li').each(function(){
                var title = $(this).children('a').text();
                var href = $(this).children('a').attr('href');
                jumpMenu.append('<option value="' + href + '">' + title + '</option>');
                // now for submenus
                $(this).children('ul').children('li').each(function(){

                  var title =  '- ' + $(this).children('a').text();
                  var href = $(this).children('a').attr('href');
                  jumpMenu.append('<option value="' + href + '">' + title + '</option>');
                })

              })

              $('select.jump-menu').change(function() {
                if ($(this).val().substr(0,1) == '/' || $(this).val().substr(0,4) == 'http') {
                  window.location = $(this).val();
                }
              })

              menu.remove();

          });

					alert('after...');

        }
    });
})(jQuery);