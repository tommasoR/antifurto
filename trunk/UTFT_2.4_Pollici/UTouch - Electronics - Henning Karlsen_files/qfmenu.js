menu=[];

function move(el, num)
{
	el.getElementsByTagName('div')[0].style['right']=parseInt(el.getElementsByTagName('div')[0].style['right'])+num+'px';
	el.style.width=parseInt(el.style.width)+num+'px';
	if(num>0)
		movein(el);
	else
		el.moving=setTimeout(function(){moveout1(el)}, 20);
}

function movein(el)
{
	m1=parseInt(el.getElementsByTagName('div')[0].style['right']);
	if(el.moving)
		clearTimeout(el.moving);
	if (m1<-1)
		move(el, -m1-1);
}

function moveout(el)
{
	if(el.moving)
		clearTimeout(el.moving);
	el.moving=setTimeout(function(){moveout1(el)}, 500);
}

function moveout1(el)
{
	aw=el.bar.offsetWidth;
	m1=el.getElementsByTagName('div')[0];
	if(el.moving)
		clearTimeout(el.moving);
	if (parseInt(m1.style['right'])>aw-m1.offsetWidth+10)
		move(el, -10);
	else 
	{
		m1.style['right']=aw-m1.offsetWidth+'px';
		el.style.width=aw+'px';
	}
}

function make_menus()
{
	document.write('<div id="qfmenu" onmouseover="movein(this);" onmouseout="moveout(this);"><div><table>\n');
	document.write('<tr><td id="qfmenubar" rowspan="' + menu[0].menuItems.length + '" valign="top"><img src="images/qfbar.jpg" alt="Qwik-find menu"></td>\n');
	for (_item_counter = 0; _item_counter < menu[0].menuItems.length; _item_counter++)
	{
		if (_item_counter>0)
			document.write('<tr>');
		if (menu[0].menuItems[_item_counter][1]&&menu[0].menuItems[_item_counter][1]!=='')
			document.write('<td '+(_item_counter==menu[0].menuItems.length-1? 'id="qfmenulastrow" ' : '')+'><a href="'+menu[0].menuItems[_item_counter][1]+'">'+menu[0].menuItems[_item_counter][0]+'</a></td>');
		else
			document.write('<td '+(_item_counter==menu[0].menuItems.length-1? 'id="qfmenulastrow" ' : '')+' class="heading">'+menu[0].menuItems[_item_counter][0]+'</td>');
		document.write('</tr>\n');
	}
	document.write('</table></div></div>');

	menu[0].m=document.getElementById('qfmenu');
	menu[0].m.bar=document.getElementById('qfmenubar');

	m1=menu[0].m.getElementsByTagName('div')[0];
	m1.style['right']=menu[0].m.bar.offsetWidth-m1.offsetWidth+'px';
	menu[0].m.style.width=menu[0].m.bar.offsetWidth+'px';
	menu[0].m.style.height=m1.offsetHeight+'px';
}
