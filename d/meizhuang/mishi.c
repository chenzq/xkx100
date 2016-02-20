// /d/meizhuang/mishi.c
// Last Modified by winder on Apr. 10 2000
#include <room.h>

inherit ROOM;
int do_press();
int valid_leave();

void create()
{
	set("short","����");
	set("long", @LONG
����һ�䲻��ķ��䣬���������һ���ŵ����(shu jia) �ͺܶ�
��(book)������ܵ����Կ��ż������˵ĺ��ǣ���һ�ߵ��ع�֮�л���
��һ������
LONG);
	set("exits", ([
		"out" : __DIR__"neitang",
	]));
	set("item_desc", ([
		"shu jia" : "����ϰ��Ÿ��ָ������顣\n",
		"book"    : "����һЩ��ƽ�����飬���������Լ�����\n",
	]) );
	set("objects", ([
		__DIR__"obj/tizi" : 1,
	]));

	set("no_clean_up", 0);
	set("coor/x", 3490);
	set("coor/y", -1400);
	set("coor/z", 0);
	setup();
}

void init()
{
	add_action("do_jump", "jump");
}

int do_jump(string arg)
{
	object me;
	me = this_player();

	if( !arg || arg=="" ) return 0;
	if( arg=="shu jia")
	{
		if (me->query_temp("marks/��1") )
		{
			if (me->query_skill("dodge",1)<100)
				write("����ͼ������ܶ���ȥ�������ǲ��˵㡣\n");
			else
			{
				write("������Ծ������ܶ��ˡ�\n");
				message("vision", me->name() + "һ����Ծ������ܶ��ˡ�\n", environment(me), ({me}) );
				me->move(__DIR__"dingduan");
				message("vision", me->name() + "������Ծ��������\n", environment(me), ({me}) );
			}
		}
		else message_vision("$N���ڵ�������������֪������ʲô���顣\n", me);
		return 1;
	}
	return notify_fail("��������������\n");
}

int valid_leave(object me, string dir)
{
	me->delete_temp("marks/��1");
	return ::valid_leave(me, dir);
}