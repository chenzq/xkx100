// cleartemp.c
// Last modified by winder 2003.10.31
inherit F_CLEAN_UP;

#include <ansi.h>
#include <localtime.h>
#define TEMP_DIR		"/temp/"



int help(object me);

int main(object me, string arg)
{
	string flogin;
	string fuser;

	if (! wizardp(me)) return 0;
	if (! arg) return help(me);

	seteuid(getuid());
	arg = arg[0..0] + "/" + arg + __SAVE_EXTENSION__;
	flogin = TEMP_DIR + "login/" + arg;
	fuser  = TEMP_DIR + "user/"  + arg;

	if (file_size(flogin) < 0 && file_size(fuser) < 0)
	{
		write("这个玩家在暂存区中没有临时档案。\n");
		return 1;
	}

	rm(flogin);
	rm(fuser);
	if (file_size(flogin) >= 0 || file_size(fuser) >= 0)
	{
		write("清除暂存区中玩家(" + arg + ")的文件失败了。");
		return 1;
	}

	write("成功的清除暂存中玩家(" + arg + ")的档案。\n");
	return 1;
}

int help(object me)
{
	write(@HELP
指令格式：cleartemp <玩家ID>

    这是清除暂存区中的玩家临时档案的命令，这些临时档案一般是使
用 restore命令从备份区恢复玩家数据时产生的。

相关指令：restore
HELP );
    return 1;
}
