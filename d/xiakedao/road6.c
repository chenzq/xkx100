// road6.c ɽ·

inherit ROOM;

void create()
{
        set("short", "ɽ·");
        set("long", @LONG
������һ����ʯ��᾵�ɽ���ϣ�����ͨ�����͵�����̨��Ψһ
·�����Ա����������£�̧ͷ��Լ�ɼ������������е�ɽ�壬һ��
ɽ·��ɽ���С�
LONG );
        set("outdoors", "xiakedao");
        set("exits", ([
                "southup" : __DIR__"road7",
                "northdown" : __DIR__"road5",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -3110);
	set("coor/y", -22120);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}