// duanjia-sword.c �μҽ� ����һ��
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>
#define PNAME "������һ����"
inherit F_SSERVER;
int perform(object me, object target)
{
	object weapon;
	int damage;
	string msg;
	int flag;
	string fskill,sskill,bskill,pfname,pskill;

	sskill = explode(__FILE__,"/")[<2];
	pfname = explode(__FILE__,"/")[<1][0..<3];
  if (userp(me) && !wizardp(me) &&
   !me->query("perform/"+pfname) &&
   !me->query("can_perform/"+sskill+"/"+pfname) &&
   !me->query_temp("murong/xingyi") &&
   !SCBORN_D->valid_perform(me,sskill,pfname) )
   return notify_fail("����ʹ�õ��⹦��û�����ֹ��ܡ�\n");

	if( !objectp(target) ) {flag =1;target = offensive_target(me);}
	
	if( !target || !target->is_character() || target == me ||	
	  	!me->is_fighting(target) ||
  	!living(target) || target->query_temp("noliving") )
		return notify_fail(PNAME"ֻ�ܶ�ս���еĶ���ʹ�á�\n");
		
	if (!objectp(weapon = me->query_temp("weapon")) ||
		(string)weapon->query("skill_type") != "sword")
		return notify_fail("��ʹ�õ��������ԡ�\n");

	fskill = "kurong-changong";
	bskill = "sword";
	if (SCBORN_D->valid_perform(me,sskill,pfname))
		fskill = me->query_skill_mapped("force");
	if( me->query_temp("murong/xingyi") )
	{
		sskill = "douzhuan-xingyi";
		fskill = "shenyuan-gong";
		bskill = "parry";
	}
	if( (int)me->query_skill(fskill, 1) < 70 )
		return notify_fail("���"+to_chinese(fskill)+"��Ϊ�����ߣ��޷�ʹ��"+PNAME+"��\n");
	if( (int)me->query_skill(sskill, 1) < 70 )
		return notify_fail("���"+to_chinese(sskill)+"������죬����ʹ��"+PNAME+"��\n");
	if( (int)me->query("neili") < 300 )
		return notify_fail("����������̫��������ʹ��"PNAME"��\n");
			
	if( (int)me->query("max_neili") < 300 )
		return notify_fail("��������Ϊ̫��������ʹ��"PNAME"��\n");
			
	msg = CYN "$N"CYN"һԾ��������һ�������һ�������Ľ���������$n"CYN"��\n"NOR;

	if (random(me->query_skill("force")) > target->query_skill("force")/2 )
	{
		if (!target->is_busy())
		target->start_busy((int)me->query_skill("sword")/30);
		
		damage = me->query_skill("force",1)+me->query_skill("sword",1);
		target->receive_damage("qi", damage,me);
		target->receive_wound("qi", damage/4,me);
		me->add("neili", -damage);
		msg += HIR"ֻ��$N�˽���һ������$n,\n$nֻ��һ���������Ķ�������ͷһ����Ѫ���������\n"NOR;
		me->start_busy(2);
	} else 
	{
		msg += CYN"����$p�͵������һԾ,������$P�Ĺ�����Χ��\n"NOR;
		me->add("neili", -100);
		me->start_busy(4);
	}
	message_combatd(msg, me, target);

	return 1;
}
string name() {return replace_string(replace_string(PNAME,"��",""),"��","");}

int help(object me)
{
	write(WHT"\n"+to_chinese(explode(__FILE__,"/")[<2])+"֮"+name()+WHT"��"NOR"\n");
	write(@HELP

	ʹ�ù�Ч��
		���˶Է���Ѫ
		���ͶԷ�����

	����Ҫ��
		��������70��
		�μҽ�70��
		����300
HELP
	);
	return 1;
}
