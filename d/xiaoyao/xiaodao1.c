// xiaodao1.c
// Modified by Winder June.25 2000

inherit ROOM;

void create()
{
	set("short", "�ּ�С��");
	set("long", @LONG
����һ���������ּ�С�����Ӷ���һֱͨ�����ߣ�һ����ȥ������
��·�ľ�ͷ�����԰ٻ����ޡ���������������
LONG
	);
	set("exits", ([
		"east" : __DIR__"qingcaop",
		"west" : __DIR__"xiaodao2",
	]));
 	set("objects", ([
		CLASS_D("xiaoyao")+"/goudu": 1,
	]));
	set("outdoors", "xiaoyao");
// 	set("no_clean_up", 0);
	set("coor/x", 70);
	set("coor/y", -500);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me,string dir)
{
        if(dir=="west" && (!me->query("family") || me->query("family")["family_name"]!="��ң��"))
                return notify_fail("·�м�����һ����С�ơ�������д��������ң�ɵ��ӣ�������롣\n");
        return ::valid_leave(me,dir);
}