//ROOM: /d/yanziwu/zuijing2.c

inherit ROOM;

void create()
{
	set("short", "׺��¥����");
	set("long",@LONG
���ǰ���ͬ��Ů�����������ң�С����С���϶�����С���ӵ�����
����͸���ϱ����ȴ������Կ���̫�����̲����죬�׷���㡣
LONG );
	set("exits", ([
		"down"   : __DIR__"zuijing",
	]));
	set("no_clean_up", 0);
	set("coor/x", 830);
	set("coor/y", -1540);
	set("coor/z", 20);
	setup();
	replace_program(ROOM);
}