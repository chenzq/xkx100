inherit NPC;
#include <ansi.h>

void create()
{
       set_name("��ɽ����", ({ "hengshan dizi", "dizi" }) );
       set("gender", "����" );
       set("age", 26);
       set("long",
               "����һ������ĺ�ɽ���ӡ�\n");
       set("combat_exp", 12500);
       set("attitude", "friendly");
 
       setup();
 carry_object("/clone/misc/cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
	 

	if (!ob || !present(ob, environment())) return;
	switch( random(3) ) {
		case 0:
			say( "��ɽ�ɵ���˵������λ" + RANK_D->query_respect(ob)
            + "������ɽ���𣬿��Կ�"BRED"(help henshan)"NOR"��\n");
			break;
		case 1:
			say( "��ɽ�ɵ���˵����������ϰ��ɽ�������ľ�ѧ--�ٱ�ǧ�ú�ɽ����ʮ��ʽ��һ������
���ɴ˾�������Ц�����ֵ����벻Զ�ӣ�\n");
			break;
		case 2:
			say( "��ɽ�ɵ���˵�������Ǻ�ɽ����������ף�Ī�����Ÿ�������̩����\n");
			break;
	}

}