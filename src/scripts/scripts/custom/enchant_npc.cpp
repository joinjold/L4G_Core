/*
##################################################################
#Verzuaberungs NPC wie er auf AT war                             #
#F黵 den NPC in der Datenbank:                                     #    
INSERT INTO `creature_template` (`entry`, `modelid_A`, `modelid_H`, `name`, `subname`, `minlevel`, `maxlevel`, `minhealth`, `maxhealth`, `minmana`, `maxmana`, `armor`, `faction_A`, `faction_H`, `type`, `ScriptName`) VALUES ('1000033', '17870', '17870', 'Verzauberungskunst', 'BETA', '70', '70', '10000', '10000', '10000', '10000', '10000', '35', '35', '10', 'enchant_npc');
UPDATE `creature_template` SET `npcflag`='1', `scale`='0.5'     WHERE (`entry`='1000033');                                                                    
##################################################################
*/

#include "precompiled.h"
#include <cstring>
#include "Chat.h"
#include "Player.h"

bool GossipHello_enchant_npc(Player *Player, Creature *Creature)
{
    if (Player->isInCombat())
    {
        Creature->Say("你在战斗中！",LANG_UNIVERSAL, 0);
        return true;
    }

    Player->ADD_GOSSIP_ITEM(9,"头部附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+1 );
    Player->ADD_GOSSIP_ITEM(9,"肩膀附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+2 );
    Player->ADD_GOSSIP_ITEM(9,"披风附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+3 );
    Player->ADD_GOSSIP_ITEM(9,"胸部附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+4 );
    Player->ADD_GOSSIP_ITEM(9,"手腕附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+5 );
    Player->ADD_GOSSIP_ITEM(9,"手部附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+6 );
    Player->ADD_GOSSIP_ITEM(9,"腿部附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+7 );
    Player->ADD_GOSSIP_ITEM(9,"脚部附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+8 );
    Player->ADD_GOSSIP_ITEM(9,"戒指1 附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+9 );
    Player->ADD_GOSSIP_ITEM(9,"戒指2 附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+10 );
    Player->ADD_GOSSIP_ITEM(9,"双手武器附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+11 );
    Player->ADD_GOSSIP_ITEM(9,"主手武器附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+12 );
    //Player->ADD_GOSSIP_ITEM(9,"Waffenhand Verzauberungen 2",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+13 );
    Player->ADD_GOSSIP_ITEM(9,"副手附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+14 );
    Player->ADD_GOSSIP_ITEM(9,"远程武器附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+16 );
    Player->ADD_GOSSIP_ITEM(9,"盾牌附魔 ",GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF+17 );
    Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    return true;
}

bool GossipSelect_enchant_npc(Player* Player, Creature* Creature, uint32 sender, uint32 action)
{
    if (Player->isInCombat())
    {
        Creature->Say("你在战斗中!",LANG_UNIVERSAL, 0);
        return true;
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+1)
    {
        Player->ADD_GOSSIP_ITEM(9,"+34 攻击强度 +16 命中 ",EQUIPMENT_SLOT_HEAD,35452);//凶暴秘药*永久性地为一件头部装备附加攻击强度提高34点、命中等级提高16的效果。无法与其它附加于指定装备的魔法效果重叠。
        Player->ADD_GOSSIP_ITEM(9,"+17 力量 +16 智力 ",EQUIPMENT_SLOT_HEAD,37891); //流放者秘药
        Player->ADD_GOSSIP_ITEM(9,"+22 法术强度 +14 法术命中 ",EQUIPMENT_SLOT_HEAD,35447);//强能秘药
        Player->ADD_GOSSIP_ITEM(9,"+35 治疗 +12 法强 +7法力/5秒 ",EQUIPMENT_SLOT_HEAD,35445);//恢复秘药 永久性地为一件头部装备附加治疗效果提高最多35点、法术伤害提高最多12点、每5秒恢复7点法力值的效果。无法与其它附加于指定装备的魔法效果重叠。
        Player->ADD_GOSSIP_ITEM(9,"+18 耐力 +20 PVP韧性 ",EQUIPMENT_SLOT_HEAD,35453);//脚斗士秘药
        Player->ADD_GOSSIP_ITEM(9,"+16 招架 +17 躲闪 ",EQUIPMENT_SLOT_HEAD,35443);//防御者秘药
        Player->ADD_GOSSIP_ITEM(9,"+20 火焰抗性 ",EQUIPMENT_SLOT_HEAD,35456);//火焰防护秘药
        Player->ADD_GOSSIP_ITEM(9,"+20 奥术抗性  ",EQUIPMENT_SLOT_HEAD,35455);//奥术防护秘药
        Player->ADD_GOSSIP_ITEM(9,"+20 暗影抗性 ",EQUIPMENT_SLOT_HEAD,35458);//暗影防护秘药
        Player->ADD_GOSSIP_ITEM(9,"+20 自然抗性 ",EQUIPMENT_SLOT_HEAD,35454);//自然防护秘药
        Player->ADD_GOSSIP_ITEM(9,"+20 冰霜抗性 ",EQUIPMENT_SLOT_HEAD,35457);//冰霜防护秘药
        Player->ADD_GOSSIP_ITEM(9,"+8 所有抗性 ",EQUIPMENT_SLOT_HEAD,37889);//多彩防护秘药
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+2)
    {
        Player->ADD_GOSSIP_ITEM(9,"+30 攻击强度 +10 爆击 ",EQUIPMENT_SLOT_SHOULDERS,35417);//强力复仇铭文 
        Player->ADD_GOSSIP_ITEM(9,"+26 攻击强度 +14 爆击 ",EQUIPMENT_SLOT_SHOULDERS,29483);//天灾的威严 
        Player->ADD_GOSSIP_ITEM(9,"+20 攻击强度 +15 爆击 ",EQUIPMENT_SLOT_SHOULDERS,35439);//强力利刃铭文 
        Player->ADD_GOSSIP_ITEM(9,"+18 法术强度 +10 爆击 ",EQUIPMENT_SLOT_SHOULDERS,35406);//强力戒律铭文
        Player->ADD_GOSSIP_ITEM(9,"+15 法术强度 +14 爆击 ",EQUIPMENT_SLOT_SHOULDERS,29467);//天灾的力量
        Player->ADD_GOSSIP_ITEM(9,"+15 爆击 +12 法术强度 ",EQUIPMENT_SLOT_SHOULDERS,35437);//强力宝珠铭文
        Player->ADD_GOSSIP_ITEM(9,"+33 治疗 +11 法强 +4法力/5秒",EQUIPMENT_SLOT_SHOULDERS,35404);//强力信仰铭文 永久性地为一件肩部装备附加治疗效果提高最多33点、法术伤害提高最多11点、每5秒恢复4点法力值的效果。无法与其它附加于指定装备的魔法效果重叠。
        Player->ADD_GOSSIP_ITEM(9,"+31 治疗 +11 法强 +5法力/5秒",EQUIPMENT_SLOT_SHOULDERS,29475);//天灾的活力 永久性地为一件肩部装备附魔，使其获得法术治疗效果提高最多31点、法术伤害提高最多11点，以及每5秒回复5点法力值的属性。
        Player->ADD_GOSSIP_ITEM(9,"+22 治疗 +6法力/5秒 ",EQUIPMENT_SLOT_SHOULDERS,35435);//强力神谕铭文 永久性地为一件肩部装备附加每5秒恢复6点法力值、治疗效果提高最多22点的效果。无法与其它附加于指定装备的魔法效果重叠。
        Player->ADD_GOSSIP_ITEM(9,"+16 耐力，+100 护甲 ",EQUIPMENT_SLOT_SHOULDERS,29480);//天灾的坚韧
        Player->ADD_GOSSIP_ITEM(9,"+15 招架，+10 躲闪 ",EQUIPMENT_SLOT_SHOULDERS,35433);//强力骑士铭文
        Player->ADD_GOSSIP_ITEM(9,"+15 招架 +10 躲闪 ",EQUIPMENT_SLOT_SHOULDERS,35402);//强力护卫铭文 永久性地为一件肩部装备附加躲闪等级提高15、防御等级提高10的效果。无法与其它附加于指定装备的魔法效果重叠。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+3)
    {
        Player->ADD_GOSSIP_ITEM(9,"+12 敏捷 ",EQUIPMENT_SLOT_BACK,34004);//强效敏捷
        Player->ADD_GOSSIP_ITEM(9,"+20 法术穿透 ",EQUIPMENT_SLOT_BACK,34003);//PvP强度 永久性地为一件披风附魔，使它获得法术穿透提高20的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 火焰抗性 ",EQUIPMENT_SLOT_BACK,25081);//给一条披风永久性地附魔，使装备它的人物获得火焰抗性提高15点的效果。
        Player->ADD_GOSSIP_ITEM(9,"+15 奥术抗性 ",EQUIPMENT_SLOT_BACK,34005);//永久性地为一件披风附魔，使它获得奥术抗性提高15点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 暗影抗性 ",EQUIPMENT_SLOT_BACK,34006);//永久性地为一件披风附魔，使它获得暗影抗性提高15点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 自然抗性 ",EQUIPMENT_SLOT_BACK,25082);//给一条披风永久性地附魔，使装备它的人物获得自然抗性提高15点的效果。
        Player->ADD_GOSSIP_ITEM(9,"+7 所有抗性 ",EQUIPMENT_SLOT_BACK,27962);//永久性地为一件披风附魔，使它获得所有抗性提高7点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 躲闪 ",EQUIPMENT_SLOT_BACK,25086);//躲闪 
        Player->ADD_GOSSIP_ITEM(9,"+12 躲闪 ",EQUIPMENT_SLOT_BACK,47051);//强效躲闪 永久性地为一件披风附魔，使它获得防御等级+12的效果。该物品等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+120 护甲 ",EQUIPMENT_SLOT_BACK,27961);//永久性地为一件披风附魔，使它获得护甲值提高120点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"获得潜行 ",EQUIPMENT_SLOT_BACK,25083);//潜行  给一条披风永久性地附魔，使装备它的角色人物获得潜行能力提高的效果。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+4)
    {
        Player->ADD_GOSSIP_ITEM(9,"+15 PVP韧性 ",EQUIPMENT_SLOT_CHEST,33992);//特效韧性
        Player->ADD_GOSSIP_ITEM(9,"+6 所有属性 ",EQUIPMENT_SLOT_CHEST,27960);//优异属性 永久性地为一件胸甲附魔，使它获得所有属性提高6点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 精神 ",EQUIPMENT_SLOT_CHEST,33990);//特效全能 永久性地为一件胸甲附魔，使它获得精神提高15点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 躲闪 ",EQUIPMENT_SLOT_CHEST,46594);//躲闪 永久性地为一件胸甲附魔，使它获得防御等级+15的效果。该物品等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+150 生命值 ",EQUIPMENT_SLOT_CHEST,27957);//优异生命 永久性地为一件胸甲附魔，使它获得生命值提高150点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+150 法力值 ",EQUIPMENT_SLOT_CHEST,27958);//优异法力 永久性地为一件胸甲附魔，使它获得法力值提高150点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+5)
    {
        Player->ADD_GOSSIP_ITEM(9,"+24 攻击强度 ",EQUIPMENT_SLOT_WRISTS,34002);//永久性地为一副护腕附魔，使它们获得攻击强度提高24点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 法术强度 ",EQUIPMENT_SLOT_WRISTS,27917);//永久性地为一副护腕附魔，使它们获得法术伤害提高最多$27918s点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+30 治疗效果 +10 法术强度 ",EQUIPMENT_SLOT_WRISTS,27911);//永久性地为一副护腕附魔，使它获得法术治疗效果提高最多30点、法术伤害提高最多10点的效果。该物品等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 耐力 ",EQUIPMENT_SLOT_WRISTS,27914);//永久性地为一副护腕附魔，使它们获得耐力提高$27916s点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 躲闪 ",EQUIPMENT_SLOT_WRISTS,27906);//永久性地为一副护腕附魔，使它们获得防御等级提高12的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 力量 ",EQUIPMENT_SLOT_WRISTS,27899);//永久性地为一副护腕附魔，使它们获得力量提高12点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 智力  ",EQUIPMENT_SLOT_WRISTS,34001);//永久性地为一副护腕附魔，使它们获得智力提高12点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+4 所有属性 ",EQUIPMENT_SLOT_WRISTS,27905);//永久性地为一副护腕附魔，使它们获得所有属性提高4点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+6法力/5秒 ",EQUIPMENT_SLOT_WRISTS,27913);//永久性地为一副护腕附魔，使它们获得每5秒回复$27912s点法力值的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+9 精神 ",EQUIPMENT_SLOT_WRISTS,20009);//永久性地为一副护腕附魔，使它们获得精神+9的效果。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+6)
    {
        Player->ADD_GOSSIP_ITEM(9,"+26 攻击强度 ",EQUIPMENT_SLOT_HANDS,33996);//永久性地为一双手套附魔，使它们获得攻击强度提高26点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 力量 ",EQUIPMENT_SLOT_HANDS,33995);//永久性地为一双手套附魔，使它们获得力量提高15点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 敏捷 ",EQUIPMENT_SLOT_HANDS,25080);//永久性地为一双手套附魔，使装备它的人物获得敏捷提高15点的效果。
        Player->ADD_GOSSIP_ITEM(9,"+20 法术伤害和治疗 ",EQUIPMENT_SLOT_HANDS,33997);//永久性地为一双手套附魔，使它获得法术伤害和治疗提高最多20点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+35 法术治疗 +12 法术伤害 ",EQUIPMENT_SLOT_HANDS,33999);//永久性地为一双手套附魔，使它获得法术治疗效果提高最多35点、法术伤害提高最多12点的效果。该物品等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 法术命中 ",EQUIPMENT_SLOT_HANDS,33994);//永久性地为一双手套附魔，使它们获得法术命中等级提高15的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+10 法术爆击 ",EQUIPMENT_SLOT_HANDS,33993);//永久性地为一双手套附魔，使它们获得法术爆击等级提高10的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+7)
    {
        Player->ADD_GOSSIP_ITEM(9,"+50 攻击强度 +12 暴击 ",EQUIPMENT_SLOT_LEGS,29535);//
        Player->ADD_GOSSIP_ITEM(9,"+40 耐力 +12 敏捷 ",EQUIPMENT_SLOT_LEGS,35495);//永久性地在一件腿部装备上附加一块虚空裂蹄腿甲片，使其获得耐力提高40点、敏捷提高12点的效果。
        Player->ADD_GOSSIP_ITEM(9,"+35 法术强度 +20 耐力 ",EQUIPMENT_SLOT_LEGS,31372);//永久性地在一件腿部装备上附加一条魔法丝线，使其获得法术伤害提高最多35点、耐力值提高20点的效果。
        Player->ADD_GOSSIP_ITEM(9,"+66 治疗效果 +22 法术强度 +20 耐力 ",EQUIPMENT_SLOT_LEGS,31370);//永久性地在一件腿部装备上附加一条魔法丝线，使其获得法术治疗效果提高最多66点、法术伤害提高最多22点、耐力值提高20点的效果。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+8)
    {
        Player->ADD_GOSSIP_ITEM(9,"+移动速度 +6 敏捷 ",EQUIPMENT_SLOT_FEET,34007);//永久性地为一双靴子附魔，使它们获得移动速度略微提升以及敏捷提高6点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+移动速度 +9 耐力 ",EQUIPMENT_SLOT_FEET,34008);//永久性地为一双靴子附魔，使它们获得移动速度略微提升以及耐力提高9点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+5% 诱捕和抵抗 +10 命中 ",EQUIPMENT_SLOT_FEET,27954);//永久性地为一双靴子附魔，使它们获得对诱捕和定身效果的抵抗几率提高5%、以及命中等级提高10的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 敏捷 ",EQUIPMENT_SLOT_FEET,27951);//永久性地为一双靴子附魔，使它们获得敏捷提高12点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 耐力 ",EQUIPMENT_SLOT_FEET,27950);//永久性地为一双靴子附魔，使它们获得耐力提高12点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+4 生命/5秒 ",EQUIPMENT_SLOT_FEET,27948);//永久性地为一双靴子附魔，使它们获得每5秒回复4点生命值和法力值的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+9)
    {
        Player->ADD_GOSSIP_ITEM(9,"+4 所有属性 ",EQUIPMENT_SLOT_FINGER1,27927);//永久性地为一只戒指附魔，使它获得所有属性提高$19988s点的效果。只有附魔师自己的戒指才能附魔，且对戒指附魔会使它变为灵魂绑定物品。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 法术强度 ",EQUIPMENT_SLOT_FINGER1,27924);//永久性地为一只戒指附魔，使它获得法术伤害和治疗提高最多12点的效果。只有附魔师自己的戒指才能附魔，且对戒指附魔会使它变为灵魂绑定物品。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+20 治疗 +7 法术强度 ",EQUIPMENT_SLOT_FINGER1,27926);//永久性地为一只戒指附魔，使它获得法术治疗效果提高最多$27925s点、法术伤害提高最多$27925s2点的效果。只有附魔师自己的戒指才能附魔，且对戒指附魔会使它变为灵魂绑定物品。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+2 物理伤害 ",EQUIPMENT_SLOT_FINGER1,27920);//永久性地为一只戒指附魔，使它获得物理伤害提高2点的效果。只有附魔师自己的戒指才能附魔，且对戒指附魔会使它变为灵魂绑定物品。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+10)
    {
        Player->ADD_GOSSIP_ITEM(9,"+4 所有属性 ",EQUIPMENT_SLOT_FINGER2,27927);
        Player->ADD_GOSSIP_ITEM(9,"+12 法术强度 ",EQUIPMENT_SLOT_FINGER2,27924);
        Player->ADD_GOSSIP_ITEM(9,"+20 治疗 +7 法术强度 ",EQUIPMENT_SLOT_FINGER2,27926);
        Player->ADD_GOSSIP_ITEM(9,"+2 物理伤害",EQUIPMENT_SLOT_FINGER2,27920);
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+11)
    {
        Player->ADD_GOSSIP_ITEM(9,"+70 攻击强度 ",EQUIPMENT_SLOT_MAINHAND,27971);//永久性地为一把双手近战武器附魔，使它获得攻击强度提高70点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+35 敏捷 ",EQUIPMENT_SLOT_MAINHAND,27977);//永久性地为一把双手近战武器附魔，使它获得敏捷提高35点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+9 物理伤害 ",EQUIPMENT_SLOT_MAINHAND,20030);//永久性地为一把双手近战武器附魔，使它获得伤害+9的效果。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+12)
    {
        Player->ADD_GOSSIP_ITEM(9,"猫鼬 ",EQUIPMENT_SLOT_MAINHAND,27984);//永久性地为一把近战武器附魔，使它有一定几率令你的敏捷提高120点，攻击速度略微提升。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"斩杀 ",EQUIPMENT_SLOT_MAINHAND,42974);//永久性地为一把近战武器附魔，使它有一定几率获得无视目标的$42976s1点护甲值的效果。该物品等级不得低于60级。
        Player->ADD_GOSSIP_ITEM(9,"+20 力量 ",EQUIPMENT_SLOT_MAINHAND,27972);//永久性地为一把近战武器附魔，使它获得力量提高20点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+20 敏捷 ",EQUIPMENT_SLOT_MAINHAND,42620);//永久性地为一把武器附魔，使其获得敏捷+20的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+40 法术强度 ",EQUIPMENT_SLOT_MAINHAND,27975);//永久性地为一把近战武器附魔，使它获得法术伤害和治疗提高最多40点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+81 治疗效果 +27 法术强度 ",EQUIPMENT_SLOT_MAINHAND,34010);//永久性地为一把近战武器附魔，使它获得法术治疗效果提高最多81点、法术伤害提高最多27点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+20 精神 ",EQUIPMENT_SLOT_MAINHAND,23803);//永久性地为一件近战武器附魔，使其获得+20精神的效果。
        Player->ADD_GOSSIP_ITEM(9,"+7 物理伤害 ",EQUIPMENT_SLOT_MAINHAND,27967);//永久性地为一把近战武器附魔，使它获得伤害提高7点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+50 奥术/火焰-法术伤害 ",EQUIPMENT_SLOT_MAINHAND,27981);//永久性地为一把近战武器附魔，使其获得最多50点火焰和奥术伤害加成的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->ADD_GOSSIP_ITEM(9,"下一页 -> ",GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+13);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+13)
    {
        Player->ADD_GOSSIP_ITEM(9,"+30 智力 ",EQUIPMENT_SLOT_MAINHAND,27968);//永久性地为一把近战武器附魔，使它获得智力提高30点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"作战专家 ",EQUIPMENT_SLOT_MAINHAND,28004);//永久性地为一把近战武器附魔，使它有一定几率在命中目标后为附近的小队成员恢复180到300点生命值的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"生命偷取 ",EQUIPMENT_SLOT_MAINHAND,20032);//永久性地为一把近战武器附魔，使它可从敌人那儿偷取生命值。对60级以上玩家的效果降低。
        Player->ADD_GOSSIP_ITEM(9,"十字军 ",EQUIPMENT_SLOT_MAINHAND,20034);//永久性地为一把近战武器附魔，使它获得在攻击时经常性地为你回复$20007s2点生命值，并使你的力量提高$20007s1点，持续$20007d。对60级以上玩家的效果降低。
        Player->ADD_GOSSIP_ITEM(9,"死亡霜冻 ",EQUIPMENT_SLOT_MAINHAND,46578);//永久性地为一把武器附魔，使你的伤害性法术和近战武器攻击有一定几率对目标造成额外的150点冰霜伤害，并使其近战、远程和施法速度降低15%，持续8秒。该物品等级不得低于60级。
        Player->ADD_GOSSIP_ITEM(9,"烈焰武器 ",EQUIPMENT_SLOT_MAINHAND,13898);//永久性地为一把近战武器附魔，使它获得附加$13897s1点火焰伤害的效果。
        Player->ADD_GOSSIP_ITEM(9,"冰寒 ",EQUIPMENT_SLOT_MAINHAND,20029);//永久性地为一把近战武器附魔，使它能释放冰寒，使目标的移动和攻击速度减慢。对60级以上玩家的效果降低。
        Player->ADD_GOSSIP_ITEM(9,"魔法激荡 ",EQUIPMENT_SLOT_MAINHAND,28003);//永久性地为一把近战武器附魔，使其获得在施法时有3%的几率在10秒内为所有小队成员恢复100点法力值的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"精金武器链 ",EQUIPMENT_SLOT_MAINHAND,42687);//在你的武器上附加一条锁链，使缴械效果的持续时间缩短$43588s1%，你的招架等级提高15。不与其它同类效果叠加。该武器等级不得低于60级。
        Player->ADD_GOSSIP_ITEM(9,"+54 冰霜/暗影-法术伤害 ",EQUIPMENT_SLOT_MAINHAND,27982);//永久性地为一把近战武器附魔，使其获得最多54点冰霜和暗影伤害加成的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+14)
    {
        Player->ADD_GOSSIP_ITEM(9,"猫鼬 ",EQUIPMENT_SLOT_OFFHAND,27984);//永久性地为一把近战武器附魔，使它有一定几率令你的敏捷提高120点，攻击速度略微提升。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"斩杀 ",EQUIPMENT_SLOT_OFFHAND,42974);//永久性地为一把近战武器附魔，使它有一定几率获得无视目标的$42976s1点护甲值的效果。该物品等级不得低于60级。
        Player->ADD_GOSSIP_ITEM(9,"+20 力量 ",EQUIPMENT_SLOT_OFFHAND,27972);//永久性地为一把近战武器附魔，使它获得力量提高20点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+20 敏捷 ",EQUIPMENT_SLOT_OFFHAND,42620);//永久性地为一把武器附魔，使其获得敏捷+20的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+7 物理伤害 ",EQUIPMENT_SLOT_OFFHAND,27967);//永久性地为一把近战武器附魔，使它获得伤害提高7点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->ADD_GOSSIP_ITEM(9,"下一页 -> ",GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+15);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+15)
    {
        Player->ADD_GOSSIP_ITEM(9,"作战专家 ",EQUIPMENT_SLOT_OFFHAND,28004);//永久性地为一把近战武器附魔，使它有一定几率在命中目标后为附近的小队成员恢复180到300点生命值的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"生命偷取 ",EQUIPMENT_SLOT_OFFHAND,20032);//永久性地为一把近战武器附魔，使它可从敌人那儿偷取生命值。对60级以上玩家的效果降低。
        Player->ADD_GOSSIP_ITEM(9,"十字军 ",EQUIPMENT_SLOT_OFFHAND,20034);//永久性地为一把近战武器附魔，使它获得在攻击时经常性地为你回复$20007s2点生命值，并使你的力量提高$20007s1点，持续$20007d。对60级以上玩家的效果降低。
        Player->ADD_GOSSIP_ITEM(9,"死亡霜冻 ",EQUIPMENT_SLOT_OFFHAND,46578);//永久性地为一把武器附魔，使你的伤害性法术和近战武器攻击有一定几率对目标造成额外的150点冰霜伤害，并使其近战、远程和施法速度降低15%，持续8秒。该物品等级不得低于60级。
        Player->ADD_GOSSIP_ITEM(9,"烈焰武器 ",EQUIPMENT_SLOT_OFFHAND,13898);//永久性地为一把近战武器附魔，使它获得附加$13897s1点火焰伤害的效果。
        Player->ADD_GOSSIP_ITEM(9,"冰寒 ",EQUIPMENT_SLOT_OFFHAND,20029);//永久性地为一把近战武器附魔，使它能释放冰寒，使目标的移动和攻击速度减慢。对60级以上玩家的效果降低。
        Player->ADD_GOSSIP_ITEM(9,"精金武器链 ",EQUIPMENT_SLOT_OFFHAND,42687);//在你的武器上附加一条锁链，使缴械效果的持续时间缩短$43588s1%，你的招架等级提高15。不与其它同类效果叠加。该武器等级不得低于60级。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+16)
    {
        Player->ADD_GOSSIP_ITEM(9,"+28 暴击 ",EQUIPMENT_SLOT_RANGED,30260);//在弓或枪械上加装永久性的瞄准镜，使其爆击等级提高28。
        Player->ADD_GOSSIP_ITEM(9,"+30 命中 ",EQUIPMENT_SLOT_RANGED,22779);//在弓或枪械上加装永久性的瞄准镜，使其命中等级提高30。
        Player->ADD_GOSSIP_ITEM(9,"+12 攻击强度 ",EQUIPMENT_SLOT_RANGED,30252);//在弓或枪械上加装永久性的瞄准镜，使其攻击伤害提高12点。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+17)
    {
        Player->ADD_GOSSIP_ITEM(9,"+12 PVP韧性  ",EQUIPMENT_SLOT_OFFHAND,44383);//永久性地为一面盾牌附魔，使它获得韧性等级提高12的效果。该物品等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+18 耐力 ",EQUIPMENT_SLOT_OFFHAND,34009);//永久性地为一面盾牌附魔，使它获得耐力提高18点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+12 智力 ",EQUIPMENT_SLOT_OFFHAND,27945);//永久性地为一面盾牌附魔，使它获得智力提高12点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+5 所有抗性 ",EQUIPMENT_SLOT_OFFHAND,27947);//永久性地为一面盾牌附魔，使它获得对所有魔法的抗性提高5点的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+15 盾牌格挡 ",EQUIPMENT_SLOT_OFFHAND,27946);//永久性地为一面盾牌附魔，使它获得格挡等级提高15的效果。该装备等级不得低于35级。
        Player->ADD_GOSSIP_ITEM(9,"+9 精神 ",EQUIPMENT_SLOT_OFFHAND,20016);//永久性地为一面盾牌附魔，使它获得精神+9的效果。
        Player->ADD_GOSSIP_ITEM(9,"+8 Frost resistance ",EQUIPMENT_SLOT_OFFHAND,11224);//
        Player->ADD_GOSSIP_ITEM(9,"+30 护甲 ",EQUIPMENT_SLOT_OFFHAND,13464);//永久性地为一面盾牌附魔，使它获得护甲+30的效果。
        Player->ADD_GOSSIP_ITEM(9,"+26-38 盾刺伤害 ",EQUIPMENT_SLOT_OFFHAND,29454);//在你的盾牌上加装一根魔钢盾刺，每次使用这块盾牌格挡都会对攻击者造成26到38点伤害。
        Player->ADD_GOSSIP_ITEM(9,"<- 返回 ",0,0);
        Player->PlayerTalkClass->SendGossipMenu(1,Creature->GetGUID());
    }
    else if (action == GOSSIP_ACTION_INFO_DEF+0)
        GossipHello_enchant_npc(Player,Creature);
    else
    {
        Player->EnchantItem(action,sender);
        GossipHello_enchant_npc(Player,Creature);
    }
    return true;
}

void AddSC_enchant_npc()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="enchant_npc";
    newscript->pGossipHello =           &GossipHello_enchant_npc;
    newscript->pGossipSelect =          &GossipSelect_enchant_npc;
    newscript->RegisterSelf();
}