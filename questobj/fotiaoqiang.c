// fotiaoqiang.c
#include <ansi.h>
inherit ITEM;
inherit F_FOOD;

void create()
{
	set_name(RED"����ǽ"NOR, ({"fotiaoqiang"}));
	set("taskobj", 1);
	set_weight(1000);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "һ��������ķ���ǽ���Ǹ�����һ���ˡ�\n");
		set("unit", "��");
		set("value", 0);
	}
}
