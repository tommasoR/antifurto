function isCompatible(){if(navigator.appVersion.indexOf('MSIE')!==-1&&parseFloat(navigator.appVersion.split('MSIE')[1])<6){return false;}return true;}var startUp=function(){mw.config=new mw.Map(true);mw.loader.addSource({"local":{"loadScript":"/wiki/load.php","apiScript":"/wiki/api.php"}});mw.loader.register([["site","1413524095",[],"site"],["noscript","1413524095",[],"noscript"],["startup","1425030862",[],"startup"],["filepage","1413524095"],["user.groups","1413524095",[],"user"],["user","1413524095",[],"user"],["user.cssprefs","1425030862",["mediawiki.user"],"private"],["user.options","1425030862",[],"private"],["user.tokens","1413524095",[],"private"],["mediawiki.language.data","1424440747",["mediawiki.language.init"]],["skins.chick","1413524095"],["skins.cologneblue","1413524095"],["skins.modern","1413524095"],["skins.monobook","1413524095"],["skins.nostalgia","1413524095"],["skins.simple","1413524095"],["skins.standard","1413524095"],["skins.vector","1413524095"],["jquery",
"1413524095"],["jquery.appear","1413524095"],["jquery.arrowSteps","1413524095"],["jquery.async","1413524095"],["jquery.autoEllipsis","1413524095",["jquery.highlightText"]],["jquery.badge","1413524095"],["jquery.byteLength","1413524095"],["jquery.byteLimit","1413524095",["jquery.byteLength"]],["jquery.checkboxShiftClick","1413524095"],["jquery.client","1413524095"],["jquery.collapsibleTabs","1413524095"],["jquery.color","1413524095",["jquery.colorUtil"]],["jquery.colorUtil","1413524095"],["jquery.cookie","1413524095"],["jquery.delayedBind","1413524095"],["jquery.expandableField","1413524095",["jquery.delayedBind"]],["jquery.farbtastic","1413524095",["jquery.colorUtil"]],["jquery.footHovzer","1413524095"],["jquery.form","1413524095"],["jquery.getAttrs","1413524095"],["jquery.highlightText","1413524095",["jquery.mwExtension"]],["jquery.hoverIntent","1413524095"],["jquery.json","1413524095"],["jquery.localize","1413524095"],["jquery.makeCollapsible","1425012225"],["jquery.mockjax",
"1413524095"],["jquery.mw-jump","1413524095"],["jquery.mwExtension","1413524095"],["jquery.placeholder","1413524095"],["jquery.qunit","1413524095"],["jquery.qunit.completenessTest","1413524095",["jquery.qunit"]],["jquery.spinner","1413524095"],["jquery.jStorage","1413524095",["jquery.json"]],["jquery.suggestions","1413524095",["jquery.autoEllipsis"]],["jquery.tabIndex","1413524095"],["jquery.tablesorter","1425012822",["jquery.mwExtension"]],["jquery.textSelection","1413524095",["jquery.client"]],["jquery.validate","1413524095"],["jquery.xmldom","1413524095"],["jquery.tipsy","1413524095"],["jquery.ui.core","1413524095",["jquery"],"jquery.ui"],["jquery.ui.widget","1413524095",[],"jquery.ui"],["jquery.ui.mouse","1413524095",["jquery.ui.widget"],"jquery.ui"],["jquery.ui.position","1413524095",[],"jquery.ui"],["jquery.ui.draggable","1413524095",["jquery.ui.core","jquery.ui.mouse","jquery.ui.widget"],"jquery.ui"],["jquery.ui.droppable","1413524095",["jquery.ui.core","jquery.ui.mouse",
"jquery.ui.widget","jquery.ui.draggable"],"jquery.ui"],["jquery.ui.resizable","1413524095",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.selectable","1413524095",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.sortable","1413524095",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.accordion","1413524095",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.autocomplete","1413524095",["jquery.ui.core","jquery.ui.widget","jquery.ui.position"],"jquery.ui"],["jquery.ui.button","1413524095",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.ui.datepicker","1413524095",["jquery.ui.core"],"jquery.ui"],["jquery.ui.dialog","1413524095",["jquery.ui.core","jquery.ui.widget","jquery.ui.button","jquery.ui.draggable","jquery.ui.mouse","jquery.ui.position","jquery.ui.resizable"],"jquery.ui"],["jquery.ui.progressbar","1413524095",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],[
"jquery.ui.slider","1413524095",["jquery.ui.core","jquery.ui.widget","jquery.ui.mouse"],"jquery.ui"],["jquery.ui.tabs","1413524095",["jquery.ui.core","jquery.ui.widget"],"jquery.ui"],["jquery.effects.core","1413524095",["jquery"],"jquery.ui"],["jquery.effects.blind","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.bounce","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.clip","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.drop","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.explode","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fade","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.fold","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.highlight","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.pulsate","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.scale","1413524095",["jquery.effects.core"],"jquery.ui"],[
"jquery.effects.shake","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.slide","1413524095",["jquery.effects.core"],"jquery.ui"],["jquery.effects.transfer","1413524095",["jquery.effects.core"],"jquery.ui"],["mediawiki","1413524095"],["mediawiki.api","1413524095",["mediawiki.util"]],["mediawiki.api.category","1413524095",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.edit","1413524095",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.parse","1413524095",["mediawiki.api"]],["mediawiki.api.titleblacklist","1413524095",["mediawiki.api","mediawiki.Title"]],["mediawiki.api.watch","1413524095",["mediawiki.api","user.tokens"]],["mediawiki.debug","1413524095",["jquery.footHovzer"]],["mediawiki.debug.init","1413524095",["mediawiki.debug"]],["mediawiki.feedback","1413524095",["mediawiki.api.edit","mediawiki.Title","mediawiki.jqueryMsg","jquery.ui.dialog"]],["mediawiki.htmlform","1413524095"],["mediawiki.notification","1413524095",["mediawiki.page.startup"]],[
"mediawiki.notify","1413524095"],["mediawiki.searchSuggest","1425012225",["jquery.autoEllipsis","jquery.client","jquery.placeholder","jquery.suggestions"]],["mediawiki.Title","1413524095",["mediawiki.util"]],["mediawiki.Uri","1413524095"],["mediawiki.user","1413524095",["jquery.cookie","mediawiki.api"]],["mediawiki.util","1425012224",["jquery.client","jquery.cookie","jquery.mwExtension","mediawiki.notify"]],["mediawiki.action.edit","1413524095",["jquery.textSelection","jquery.byteLimit"]],["mediawiki.action.edit.preview","1413524095",["jquery.form","jquery.spinner"]],["mediawiki.action.history","1413524095",[],"mediawiki.action.history"],["mediawiki.action.history.diff","1413524095",[],"mediawiki.action.history"],["mediawiki.action.view.dblClickEdit","1413524095",["mediawiki.util"]],["mediawiki.action.view.metadata","1425012449"],["mediawiki.action.view.rightClickEdit","1413524095"],["mediawiki.action.watch.ajax","1413524095",["mediawiki.page.watch.ajax"]],["mediawiki.language",
"1413524095",["mediawiki.language.data","mediawiki.cldr"]],["mediawiki.cldr","1413524095",["mediawiki.libs.pluralruleparser"]],["mediawiki.libs.pluralruleparser","1413524095"],["mediawiki.language.init","1413524095"],["mediawiki.jqueryMsg","1413524095",["mediawiki.util","mediawiki.language"]],["mediawiki.libs.jpegmeta","1413524095"],["mediawiki.page.ready","1413524095",["jquery.checkboxShiftClick","jquery.makeCollapsible","jquery.placeholder","jquery.mw-jump","mediawiki.util"]],["mediawiki.page.startup","1413524095",["jquery.client","mediawiki.util"]],["mediawiki.page.watch.ajax","1425015813",["mediawiki.page.startup","mediawiki.api.watch","mediawiki.util","mediawiki.notify","jquery.mwExtension"]],["mediawiki.special","1413524095"],["mediawiki.special.block","1413524095",["mediawiki.util"]],["mediawiki.special.changeemail","1413524095",["mediawiki.util"]],["mediawiki.special.changeslist","1413524095",["jquery.makeCollapsible"]],["mediawiki.special.movePage","1413524095",[
"jquery.byteLimit"]],["mediawiki.special.preferences","1413524095"],["mediawiki.special.recentchanges","1413524095",["mediawiki.special"]],["mediawiki.special.search","1425013834"],["mediawiki.special.undelete","1413524095"],["mediawiki.special.upload","1425016382",["mediawiki.libs.jpegmeta","mediawiki.util"]],["mediawiki.special.javaScriptTest","1413524095",["jquery.qunit"]],["mediawiki.tests.qunit.testrunner","1413524095",["jquery.qunit","jquery.qunit.completenessTest","mediawiki.page.startup","mediawiki.page.ready"]],["mediawiki.legacy.ajax","1413524095",["mediawiki.util","mediawiki.legacy.wikibits"]],["mediawiki.legacy.commonPrint","1413524095"],["mediawiki.legacy.config","1413524095",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.IEFixes","1413524095",["mediawiki.legacy.wikibits"]],["mediawiki.legacy.protect","1413524095",["mediawiki.legacy.wikibits","jquery.byteLimit"]],["mediawiki.legacy.shared","1413524095"],["mediawiki.legacy.oldshared","1413524095"],[
"mediawiki.legacy.upload","1413524095",["mediawiki.legacy.wikibits","mediawiki.util"]],["mediawiki.legacy.wikibits","1413524095",["mediawiki.util"]],["mediawiki.legacy.wikiprintable","1413524095"],["ext.cite","1413524095",["jquery.tooltip"]],["jquery.tooltip","1413524095"],["ext.geshi.local","1413524095"],["contentCollector","1413524095",[],"ext.wikiEditor"],["jquery.wikiEditor","1425015824",["jquery.client","jquery.textSelection","jquery.delayedBind"],"ext.wikiEditor"],["jquery.wikiEditor.iframe","1413524095",["jquery.wikiEditor","contentCollector"],"ext.wikiEditor"],["jquery.wikiEditor.dialogs","1413524095",["jquery.wikiEditor","jquery.wikiEditor.toolbar","jquery.ui.dialog","jquery.ui.button","jquery.ui.draggable","jquery.ui.resizable","jquery.tabIndex"],"ext.wikiEditor"],["jquery.wikiEditor.dialogs.config","1425015824",["jquery.wikiEditor","jquery.wikiEditor.dialogs","jquery.wikiEditor.toolbar.i18n","jquery.suggestions","mediawiki.Title"],"ext.wikiEditor"],[
"jquery.wikiEditor.highlight","1413524095",["jquery.wikiEditor","jquery.wikiEditor.iframe"],"ext.wikiEditor"],["jquery.wikiEditor.preview","1413524095",["jquery.wikiEditor"],"ext.wikiEditor"],["jquery.wikiEditor.previewDialog","1413524095",["jquery.wikiEditor","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.publish","1413524095",["jquery.wikiEditor","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.templateEditor","1413524095",["jquery.wikiEditor","jquery.wikiEditor.iframe","jquery.wikiEditor.dialogs"],"ext.wikiEditor"],["jquery.wikiEditor.templates","1413524095",["jquery.wikiEditor","jquery.wikiEditor.iframe"],"ext.wikiEditor"],["jquery.wikiEditor.toc","1413524095",["jquery.wikiEditor","jquery.wikiEditor.iframe","jquery.ui.draggable","jquery.ui.resizable","jquery.autoEllipsis","jquery.color"],"ext.wikiEditor"],["jquery.wikiEditor.toolbar","1413524095",["jquery.wikiEditor","jquery.wikiEditor.toolbar.i18n"],"ext.wikiEditor"],[
"jquery.wikiEditor.toolbar.config","1413524095",["jquery.wikiEditor","jquery.wikiEditor.toolbar.i18n","jquery.wikiEditor.toolbar","jquery.cookie","jquery.async"],"ext.wikiEditor"],["jquery.wikiEditor.toolbar.i18n","1413524095",[],"ext.wikiEditor"],["ext.wikiEditor","1413524095",["jquery.wikiEditor"],"ext.wikiEditor"],["ext.wikiEditor.dialogs","1413524095",["ext.wikiEditor","ext.wikiEditor.toolbar","jquery.wikiEditor.dialogs","jquery.wikiEditor.dialogs.config"],"ext.wikiEditor"],["ext.wikiEditor.highlight","1413524095",["ext.wikiEditor","jquery.wikiEditor.highlight"],"ext.wikiEditor"],["ext.wikiEditor.preview","1425015824",["ext.wikiEditor","jquery.wikiEditor.preview"],"ext.wikiEditor"],["ext.wikiEditor.previewDialog","1413524095",["ext.wikiEditor","jquery.wikiEditor.previewDialog"],"ext.wikiEditor"],["ext.wikiEditor.publish","1425015824",["ext.wikiEditor","jquery.wikiEditor.publish"],"ext.wikiEditor"],["ext.wikiEditor.templateEditor","1413524095",["ext.wikiEditor",
"ext.wikiEditor.highlight","jquery.wikiEditor.templateEditor"],"ext.wikiEditor"],["ext.wikiEditor.templates","1413524095",["ext.wikiEditor","ext.wikiEditor.highlight","jquery.wikiEditor.templates"],"ext.wikiEditor"],["ext.wikiEditor.toc","1413524095",["ext.wikiEditor","ext.wikiEditor.highlight","jquery.wikiEditor.toc"],"ext.wikiEditor"],["ext.wikiEditor.tests.toolbar","1413524095",["ext.wikiEditor.toolbar"],"ext.wikiEditor"],["ext.wikiEditor.toolbar","1413524095",["ext.wikiEditor","jquery.wikiEditor.toolbar","jquery.wikiEditor.toolbar.config"],"ext.wikiEditor"],["ext.wikiEditor.toolbar.hideSig","1413524095",[],"ext.wikiEditor"],["ext.categoryTree","1413524095"],["ext.categoryTree.css","1413524095"],["ext.FancyBoxThumbs","1413524095"]]);mw.config.set({"wgLoadScript":"/wiki/load.php","debug":false,"skin":"vector","stylepath":"/wiki/skins","wgUrlProtocols":
"http\\:\\/\\/|https\\:\\/\\/|ftp\\:\\/\\/|irc\\:\\/\\/|ircs\\:\\/\\/|gopher\\:\\/\\/|telnet\\:\\/\\/|nntp\\:\\/\\/|worldwind\\:\\/\\/|mailto\\:|news\\:|svn\\:\\/\\/|git\\:\\/\\/|mms\\:\\/\\/|\\/\\/","wgArticlePath":"/wiki/$1","wgScriptPath":"/wiki","wgScriptExtension":".php","wgScript":"/wiki/index.php","wgVariantArticlePath":false,"wgActionPaths":{},"wgServer":"http://www.seeedstudio.com","wgUserLanguage":"en","wgContentLanguage":"en","wgVersion":"1.20.3","wgEnableAPI":true,"wgEnableWriteAPI":true,"wgMainPageTitle":"Main Page","wgFormattedNamespaces":{"-2":"Media","-1":"Special","0":"","1":"Talk","2":"User","3":"User talk","4":"Wiki","5":"Wiki talk","6":"File","7":"File talk","8":"MediaWiki","9":"MediaWiki talk","10":"Template","11":"Template talk","12":"Help","13":"Help talk","14":"Category","15":"Category talk"},"wgNamespaceIds":{"media":-2,"special":-1,"":0,"talk":1,"user":2,"user_talk":3,"wiki":4,"wiki_talk":5,"file":6,"file_talk":7,"mediawiki":8,"mediawiki_talk":9,"template":10,
"template_talk":11,"help":12,"help_talk":13,"category":14,"category_talk":15,"image":6,"image_talk":7,"project":4,"project_talk":5},"wgSiteName":"Wiki","wgFileExtensions":["png","gif","jpg","jpeg","doc","xls","mpp","pdf","ppt","tiff","bmp","docx","xlsx","pptx","ps","zip","rar","txt","svg"],"wgDBname":"seeedc6_wikidb2","wgFileCanRotate":true,"wgAvailableSkins":{"chick":"Chick","simple":"Simple","myskin":"MySkin","nostalgia":"Nostalgia","standard":"Standard","vector":"Vector","cologneblue":"CologneBlue","monobook":"MonoBook","modern":"Modern"},"wgExtensionAssetsPath":"/wiki/extensions","wgCookiePrefix":"seeedc6_wikidb2","wgResourceLoaderMaxQueryLength":-1,"wgCaseSensitiveNamespaces":[],"wgWikiEditorToolbarClickTracking":false,"wgWikiEditorMagicWords":{"redirect":"#REDIRECT","img_right":"right","img_left":"left","img_none":"none","img_center":"center","img_thumbnail":"thumbnail","img_framed":"framed","img_frameless":"frameless"}});};if(isCompatible()){document.write(
"\x3cscript src=\"/wiki/load.php?debug=false\x26amp;lang=en\x26amp;modules=jquery%2Cmediawiki\x26amp;only=scripts\x26amp;skin=vector\x26amp;version=20130407T064622Z\"\x3e\x3c/script\x3e");}delete isCompatible;
/* cache key: seeedc6_wikidb2:resourceloader:filter:minify-js:7:0dc31702f8124902718864dea8720b32 */