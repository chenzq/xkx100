
// yellow-cloth.c
// ��ɽ�ջ���

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
	set_name(YEL"�ջ���"NOR, ({ "yellow cloth", "cloth" }) );
	set_weight(3000);
	if( clonep() )
		set_default_object(__FILE__);
	else {
		set("unit", "��");
		set("material", "cloth");
		set("value", 100);
		set("armor_prop/armor", 5);
	}
	setup();
}

