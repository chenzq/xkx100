//jmqmen.c

inherit ROOM;

void create()
{
	set("short", "巨木旗大门");
	set("long", @LONG
这里是明教巨木旗的大门，庄严古朴，门前对插四面镶绿游龙旗。
碧绿的大门敞开着，似乎看不出有何设防。从门里望进去，只有一片苍
翠的树林。
LONG );
	set("exits", ([
		"enter"  : __DIR__"jmqshulin1",
		"west"   : __DIR__"tojmq3",
	]));
	set("no_clean_up", 0);
	set("outdoors", "mingjiao");
	set("coor/x", -52050);
	set("coor/y", 860);
	set("coor/z", 50);
	setup();
	replace_program(ROOM);
}