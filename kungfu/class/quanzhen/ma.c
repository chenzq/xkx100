// ma.c ����
// last modified 01/05/05

#include <ansi.h>
inherit NPC;

string ask_me();
string ask_ling();
string ask_array();
string ask_shu();
int do_qixing(object me, object ob);

void create()
{
        set_name("����", ({"ma yu", "ma"}));
        set("gender", "����");
        set("age", 42);
        set("class", "quanzhen");
        set("nickname",MAG"������"NOR);
        set("long",
                "�������������Ĵ���ӣ�ȫ������֮�ף����������������ˡ�\n"
                "����ü��Ŀ���Ͱ����ף���Ц�ſ����㡣\n"
                "���������Ҫ��ȫ������ս���ʦ��\n");
        set("attitude", "peaceful");
        set("shen_type",1);
        set("str", 28);
        set("int", 32);
        set("con", 31);
        set("dex", 30);

        set("title","ȫ������֮��");

//       set("env/wimpy", 60);
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
        	(: exert_function, "powerup" :),
                (: exert_function, "recover" :),
                (: exert_function, "recover" :),
                (: perform_action, "strike.ju" :),                
                (: perform_action, "whip.wuguang" :),                                
                (: perform_action, "sword.ding" :),
                (: perform_action, "sword.sanqing" :),  
		(: command("wield changjian") :),
        }));

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 1600);
        set("max_jing", 1600);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jiali", 100);

        set("combat_exp", 500000);
        set("score", 300000);

        set_skill("array", 100);
        set_skill("force", 150);
        set_skill("xiantian-qigong", 150);    //��������
        set_skill("sword", 140);
        set_skill("quanzhen-jian",210);  //ȫ�潣
        set_skill("dodge", 120);
        set_skill("jinyan-gong", 180);   //���㹦
        set_skill("parry", 150);
        set_skill("unarmed", 140);
        set_skill("strike", 120);
        set_skill("haotian-zhang", 180);    //�����
        set_skill("cuff", 120);
        set_skill("chunyang-quan", 180);    //����ȭ
        set_skill("whip", 120);
        set_skill("duanyun-bian", 180);    //����ȭ
        set_skill("literate", 100);
        set_skill("taoism", 110);

        map_skill("force", "xiantian-qigong");
        map_skill("sword", "quanzhen-jian");
        map_skill("dodge", "jinyan-gong");
        map_skill("parry", "duanyun-bian");
        map_skill("whip", "duanyun-bian");
        map_skill("strike", "haotian-zhang");
        map_skill("cuff", "chunyang-quan");
        prepare_skill("cuff", "chunyang-quan");
        prepare_skill("strike", "haotian-zhang");

        create_family("ȫ���", 2, "����");

        set("book_count",1);
        set("shu_count",1);
        set("inquiry", ([
                "ȫ���" :  "��ȫ��������µ����������ڡ�\n",
                "ȫ����" :  (: ask_ling :),
                "����"   :  (: ask_ling :),
                "���㹦" :   (: ask_me :),
                "����ͼ��" : (: ask_me :),
                "�������" : (: ask_array :),
                "����������" : (: ask_array :),
                "�ؼ�"      : (: ask_shu :),
                "�޷��ܾ�"   : (: ask_shu :),
                "shu" : (: ask_shu :),
                ]) );

        setup();

        carry_object("/clone/weapon/changbian")->wield();
        carry_object("/clone/weapon/changjian");
        carry_object(__DIR__"obj/greenrobe")->wear();
}

string ask_me()
{
        mapping fam;
        object ob;

        if (!(fam=this_player()->query("family"))||fam["family_name"]!="ȫ���")
                return RANK_D->query_respect(this_player()) +
                "�뱾�̺��޹ϸ��ҽ̵��书�伮�ɲ��ܽ����㡣";
        if (query("book_count") < 1)
                return "�������ˣ�����ͼ���Ѿ�����ȡ���ˡ�";
        add("book_count", -1);
        ob = new("/clone/book/jinyantu");
        ob->move(this_player());
        return "�ðɣ��Ȿ������ͼ�ס����û�ȥ�ú��ж���";
}

string ask_shu()
{
	object ob;
	
	if (this_player()->query("family/master_id")!="ma yu")
		return RANK_D->query_respect(this_player()) + 
		"���ҵ��ӣ���֪�˻��Ӻ�̸��";
	if (query("shu_count") < 1)
		return "�������ˣ����ɵ��ؼ����ڴ˴���";
	add("shu_count", -1);
	ob = new("/clone/book/whip");
	ob->move(this_player());
	command("rumor "+this_player()->query("name")+"�õ��޷��ܾ�����\n");
	return "�ðɣ��Ȿ���޷��ܾ������û�ȥ�ú����С�";
}

string ask_ling()
{
	mapping fam, skl; 
	object ob, me = this_player();
	string *skillname;
	int i;
	
	if (!(fam = me->query("family")) || fam["family_name"] != "ȫ���")
		return RANK_D->query_respect(me) + 
		"�뱾�̺��޹ϸ𣬲�֪�˻��Ӻ�̸��";

	skl = me->query_skills();
	skillname  = sort_array( keys(skl), (: strcmp :) );

	for(i=0; i<sizeof(skl); i++) {
		if (skl[skillname[i]] < 30) 
		return RANK_D->query_respect(me) + "����������������ȡȫ���";
	}

	ob = new("/d/quanzhen/obj/quanzhen-ling");
	ob->move(me);
	message_vision("$N���һ��ȫ���\n", me);

	return "�ðɣ�ƾ����ȫ���������������ʦ����ս��";
}

string ask_array()
{
	object room, qizi, obj, ob = this_player(), me = this_object();
	mapping ob_fam, skl; 
	string *skillname;
	int i;

	ob_fam  = ob->query("family");
	skl = ob->query_skills();

	if (sizeof(skl) <= 1)
		return RANK_D->query_respect(ob) + 
		"���������������ʸ��������";
	if (ob->query("score") < 20000)
	        return RANK_D->query_respect(ob) + 
		"�������㣬�����ʸ��������";

	skillname  = keys(skl);
	for(i=0; i<sizeof(skl); i++) {
		if ((skl[skillname[i]] < 80) || (sizeof(skl) == 0))
		return RANK_D->query_respect(ob) + 
		"���������������ʸ��������";
	}
	if( ob->query("qixing") )
		return RANK_D->query_respect(ob) + 
		"��Ȼ����������󣬿ɲ�Ҫ���ϵ��������Ц��";
/*
	if ( ob_fam["family_name"] != "ȫ���" || ob_fam["generation"] != 3)
		return RANK_D->query_respect(ob) + "����û�ʸ��������";
*/
	if ( me->query("assigned_qixing") )
		return RANK_D->query_respect(ob) + "������������ս����������һ��ʱ�������ɡ�";

	me->set("assigned_qixing", ob->query("id")); 		
	command("smile");
	say("\n���ڵ���˵�����ðɣ���ȥ�ټ���ʦ�ܡ��Ժ��ڴ�У���ϵ��㡣\n");
        message_vision("\n���ڵ��������뿪��\n\n", ob);

/* ̷���� */
	if(!( room = find_object("/d/quanzhen/rongwutang")) )
		room = load_object("/d/quanzhen/rongwutang");
  		me->move(room);
	if( !objectp(obj = present("tan chuduan", room) ))
	{
		me->move("/d/quanzhen/shiweishi");
		message_vision("\n���ڵ������˹�����\n\n", ob);
		return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";	
	}
	message("vision","\n���ڵ������˹�������̷����˵�˼��䡣\n", room, obj);
	obj->move("/d/quanzhen/daxiaochang");
	message("vision", "̷���˵��˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* ������ */
	if(!( room = find_object("/d/quanzhen/jingxiushi")) )
		room = load_object("/d/quanzhen/jingxiushi");
  		me->move(room);
	if( !objectp(obj = present("liu chuxuan", room) ))
	{
		me->move("/d/quanzhen/shiweishi");
		message_vision("\n���ڵ������˹�����\n\n", ob);
		return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";	
	}
	message("vision","\n���ڵ������˹�������������˵�˼��䡣\n", room, obj);
	obj->move("/d/quanzhen/daxiaochang");
	message("vision", "���������˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* �𴦻� */
	if(!( room = find_object("/d/quanzhen/laojundian")) )
		room = load_object("/d/quanzhen/laojundian");
  		me->move(room);
	if( !objectp(obj = present("qiu chuji", room) ))
	{
		me->move("/d/quanzhen/shiweishi");
		message_vision("\n���ڵ������˹�����\n\n", ob);
		return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";	
	}
	message("vision","\n���ڵ������˹��������𴦻�˵�˼��䡣\n", room, obj);
	obj->move("/d/quanzhen/daxiaochang");
	message("vision", "�𴦻����˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* ����һ */
	if(!( room = find_object("/d/quanzhen/wanwutang")) )
		room = load_object("/d/quanzhen/wanwutang");
  		me->move(room);
	if( !objectp(obj = present("wang chuyi", room) ))
	{
		me->move("/d/quanzhen/shiweishi");
		message_vision("\n���ڵ������˹�����\n\n", ob);
		return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";	
	}
	message("vision","\n���ڵ������˹�����������һ˵�˼��䡣\n", room, obj);
	obj->move("/d/quanzhen/daxiaochang");
	message("vision", "����һ���˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* �´�ͨ */
	if(!( room = find_object("/d/quanzhen/guangning")) )
		room = load_object("/d/quanzhen/guangning");
  		me->move(room);
	if( !objectp(obj = present("hao datong", room) ))
	{
		me->move("/d/quanzhen/shiweishi");
		message_vision("\n���ڵ������˹�����\n\n", ob);
		return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";	
	}
	message("vision","\n���ڵ������˹��������´�ͨ˵�˼��䡣\n", room, obj);
	obj->move("/d/quanzhen/daxiaochang");
	message("vision", "�´�ͨ���˵�ͷ���첽���˳�ȥ��\n", room, obj);

/* �ﲻ�� */
	if(!( room = find_object("/d/quanzhen/qingjing")) )
		room = load_object("/d/quanzhen/qingjing");
  		me->move(room);
	if( !objectp(obj = present("sun buer", room) ))
	{
		me->move("/d/quanzhen/shiweishi");
		message_vision("\n���ڵ������˹�����\n\n", ob);
		return "���ǶԲ���ȫ���������˲��ڣ��޷����������\n";	
	}
	message("vision","\n���ڵ������˹��������ﲻ��˵�˼��䡣\n", room, obj);
	obj->move("/d/quanzhen/daxiaochang");
	message("vision", "�ﲻ�����˵�ͷ���첽���˳�ȥ��\n", room, obj);
	ob->set_temp("pre_qixing", 1);

        me->move("/d/quanzhen/daxiaochang");
        call_out("waiting", 1, me,1);
	return "�ã���Ҷ������ˡ�\n";
}

int waiting(object me,int wait_time)
{
	object ob;

	if( wait_time == 300 )
	{
		say( "����˵�����������������ˣ����ǻ�ȥ�գ�\n\n");
		call_out("do_back", 0, me);
		ob->add("score",-5000);				
	}
	else if(!objectp(ob = present(me->query("assigned_qixing"),environment(me))))
	{
		wait_time++;
		call_out("waiting", 1, me,wait_time);
	}
	else call_out("preparing", 0, me, ob);

	return 1;
}

int preparing(object me, object ob)
{
	object *obs, room, obj1, obj2, obj3, obj4, obj5, obj6;
	string myname = me->query("name");
	int i;

	if(!( room = find_object("/d/quanzhen/daxiaochang")) )
	room = load_object("/d/quanzhen/daxiaochang");
	if(!objectp( obj1 = present("tan chuduan", environment(me))))
		return notify_fail("��ʦ����ô���ڣ�\n");
	if(!objectp( obj2 = present("liu chuxuan", environment(me))))
		return notify_fail("��ʦ����ô���ڣ�\n");
	if(!objectp( obj3 = present("qiu chuji", environment(me))))
		return notify_fail("��ʦ����ô���ڣ�\n");
	if(!objectp( obj4 = present("wang chuyi", environment(me))))
		return notify_fail("��ʦ����ô���ڣ�\n");
	if(!objectp( obj5 = present("hao datong", environment(me))))
		return notify_fail("��ʦ����ô���ڣ�\n");
	if(!objectp( obj6 = present("sun buer", environment(me))))
		return notify_fail("Сʦ����ô���ڣ�\n");

	me->dismiss_team();
	me->set_leader();
	me->add_team_member(obj1);
	me->add_team_member(obj2);
	me->add_team_member(obj3);
	me->add_team_member(obj4);
	me->add_team_member(obj5);
	me->add_team_member(obj6);

	say( "����˵��������ɵ��ˣ��粻����Ħ��������뼴���뿪��\n");


  obs=me->query_team();
	for(i=0;i<sizeof(obs);i++)
	{
		ob->fight_ob(obs[i]);
		obs[i]->fight_ob(ob);
		if(obs[i] != me)
			message_vision(myname+"����"+obs[i]->query("name")+"������׼����\n",me);
	}
//	command("say chat " + ob->query("title") + ob->query("name") + 
//		"�ڽ���" + NATURE_D->game_time() + "��սȫ���������\n");
	message("channel:snow", HIC"����������[Ma yu]��" + ob->query("title") + ob->query("name") + 
		HIC+"�ڽ���" + NATURE_D->game_time() + "��սȫ���������\n"NOR,users());
	say(HIC"������������һס���Ѽ�ʮ�ꡣ��\n");
	say("̷��������������ͷ��������ߡ���\n");
	say("������������������ͤ�������ӡ���\n");
	say("�𴦻��ӿڵ�������Ҷ����̫���ɡ���\n");
	say("����һ�������������������⡣��\n");
	say("�´�ͨ����������������δ��ǰ����\n");
	say("�ﲻ��������������һЦ�޾а�����\n");
	say("�����վ�������������������죡��\n\n\n"NOR);

	message_vision(myname+ "���������������˵�����ã�ʱ���ѵ������ڿ�ʼ������������󡹣�\n",me);
	message_vision(myname+ "ͻȻ�����ƶ���������ȫ�������ռλ�ã�������ˣ��ұ����ˣ����ǰڵġ���������󷨡�\n",me);
	say("����λ�����̷࣬����λ����诣�������λ�����ᣬ�𴦻�λ����Ȩ��������ɶ�����\n");
	say("����һλ����⣬�´�ͨλ���������ﲻ��λ��ҡ�⣬������ɶ�����\n");
	remove_call_out("do_qixing");
	call_out("do_qixing", 2, me, ob);
	return 1;
}


int do_qixing(object me, object en)
{
	object *obs, weapon, enweapon;
	int i, j, power;
	string err;
	string *where = ({
		"����",
		"���",
		"����",
		"��Ȩ",
		"���",
		"����",
		"ҡ��"
	});

	if(pointerp(obs=me->query_team()) )
	switch (random (4))
	{
		case 0:
message_vision("����������ƺ��ǰ�������������ӣ������ۻ����ң������ʧ��\n",me);
			break;
		case 1:
message_vision("������󷨹����ƶ����������಻����˲�佫����Χ�����ġ�\n",me);
			break;
		case 2:
message_vision("�������Խ��ԽС�����ν������˳�һ��������룬��������Ϣ֮�С�\n",me);
			break;
		case 3:
message_vision("ֻ��������󰵺����а���֮���������˲������������ϵ������޷죬����֮������̾Ϊ��ֹ��\n",me);
			break;
	}
	for(i=0;i<sizeof(obs);i++)
	{
		weapon = obs[i]->query_temp("weapon");
		power = obs[i]->query_skill("force",1)/10;
	  obs[i]->add_temp("apply/attack", power);
	  obs[i]->add_temp("apply/damage", power);
		switch (random(2))
		{
			case 0:
message_vision("\n"+where[i]+"λ�ϵ�"+obs[i]->query("name")+ "������������񹦣���Ȼ����������������ǰһ��, ����", me);
				break;
			case 1:
message_vision("\n"+where[i]+"λ�ϵ�"+obs[i]->query("name")+ "ͦ�������������������ƮƮ��������硣ֻ��", me);
				break;
//	               default:
		}
	  err=catch(COMBAT_D->do_attack(obs[i],en,weapon,0));
	  if (err)
	  {
		  message("channel:debug","������󹥻����� err="+err,users());
	  	return 1;
	  }
		obs[i]->add_temp("apply/attack", -power);
		obs[i]->add_temp("apply/damage", -power);
		if(en->query("qi")*2 <= en->query("max_qi"))
		{
			en->remove_all_enemy();
			remove_call_out("do_end");
			call_out("do_end", 1, me, en, 0);
			return 1;
		}
	}
	j = random(sizeof(me->query_team()));
	enweapon = en->query_temp("weapon");
	if (enweapon)
  	COMBAT_D->do_attack(en,obs[j], enweapon);
	else 
  	COMBAT_D->do_attack(en,obs[j], enweapon);
	if(obs[j]->query("qi")*2 <= obs[j]->query("max_qi"))
	{
		message_vision(HIR+obs[j]->query("name")+"һ��ſ�ڵ��ϣ�ˤ��������\n"NOR,me);
		en->remove_all_enemy();
		remove_call_out("do_end");
		call_out("do_end", 1, me, en, 1);
		return 1;
	}
	else if(obs[j]->query("qi")*3 <= obs[j]->query("max_qi")*2)
	{
		message_vision(obs[j]->query("name")+ "������һ�������ˤ��������\n",me);
	}
	else if(obs[j]->query("qi")*5 <= obs[j]->query("max_qi")*4)
		message_vision(obs[j]->query("name")+"����û��˼��Σ�������վ���˲��ӡ�\n",me);

	remove_call_out("do_qixing");
	call_out("do_qixing", 1, me, en);
	return 1;
}
int do_end(object me, object en, int result)
{
	if( result == 1)
	{
		if(en->query_temp("pre_qixing"))
		{
			en->set("qixing", 1);
		}
		en->delete_temp("pre_qixing");
		en->add("combat_exp",50000);
		en->add("score",30000);
		en->add("potential",10000);	
		message_vision(HIR"\n�������"+en->query("name")+"�����ˡ�\n\n"NOR,me);
		message("channel:snow", HIR"��ͨ�桿"HIY + en->query("name")+"������������ˣ�\n"NOR, users());
	}
	else
	{
		en->delete_temp("pre_qixing");
		message("channel:snow", HIR"��ͨ�桿"HIY + en->query("name")+"û�ܴ����������\n"NOR, users());
    message_vision(HIR"\n$NЦ��Ц�����������Ϊȫ�����֮����\n"NOR,me);
		en->add("score",-3000);	   
	}
	remove_call_out("do_back");
	call_out("do_back", 1, me);
	return 1;
}
int do_back(object me)
{
	object *obs, weapon;
	int i;

	if(pointerp(obs=me->query_team()) )
	{
		for(i=0;i<sizeof(obs);i++)
		{
			if (objectp(weapon = obs[i]->query_temp("weapon"))
				&& (string)weapon->query("skill_type")=="sword")
message_vision("$N�������һ�ݣ�ʹһ�С��ս�ʽ������������һ��������������һ�����˳���������󡹡�\n", obs[i]);
			else
message_vision("$N�������һ�ݣ�ʹһ�С���ɽʽ������ȭ����һȦ������������һ�����˳���������󡹡�\n", obs[i]);

message_vision("$N���˸�鮵���ƶ���ȸ����ˣ�˵��Ϳ첽�뿪�ˡ�\n", obs[i]);
			if (obs[i]->query("name")== "����")
				obs[i]->move("/d/quanzhen/shiweishi");
			if (obs[i]->query("name")== "̷����")
				obs[i]->move("/d/quanzhen/rongwutang");
			if (obs[i]->query("name")== "������")
				obs[i]->move("/d/quanzhen/jingxiushi");
			if (obs[i]->query("name")== "�𴦻�")
				obs[i]->move("/d/quanzhen/laojundian");
			if (obs[i]->query("name")== "����һ")
				obs[i]->move("/d/quanzhen/wanwutang");
			if (obs[i]->query("name")== "�´�ͨ")
				obs[i]->move("/d/quanzhen/guangning");
			if (obs[i]->query("name")== "�ﲻ��")
				obs[i]->move("/d/quanzhen/qingjing");
		}
	}///d/quanzhen/shiweishi
	me->dismiss_team();
}

#include "chu.h";