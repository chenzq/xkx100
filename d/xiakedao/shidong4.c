// Room: /xiakedao/shidong4.c

inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
这是一个石洞，四周点着八盏油灯，使得整个房间非常明亮。
山洞中支路甚多，你可要小心，别走错了路。
LONG );
        set("exits", ([
                "east" : __FILE__,
                "west" : __DIR__"shidong5",
                "south" : __FILE__,
                "north" : __DIR__"yingbin",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -3070);
	set("coor/y", -22100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}