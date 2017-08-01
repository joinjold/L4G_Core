/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* ScriptData
SDName: Burning_Steppes
SD%Complete: 100
SDComment: Quest support: 4224, 4866, 3701
SDCategory: Burning Steppes
EndScriptData */

/* ContentData
npc_ragged_john
EndContentData */

#include "precompiled.h"

/*######
## npc_ragged_john
######*/

#define GOSSIP_HELLO    "公务，约翰。我需要一些有关温德索尔元帅的信息。告诉我你最后一次见到他。"
#define GOSSIP_SELECT1  "你要做什么?"
#define GOSSIP_SELECT2  "从某种义意上说，矮人，我不希望与你交恶。"
#define GOSSIP_SELECT3  "反对者?"
#define GOSSIP_SELECT4  "有趣...继续约翰."
#define GOSSIP_SELECT5  "温莎就是这样死的。"
#define GOSSIP_SELECT6  "他是怎么死的？"
#define GOSSIP_SELECT7  "好吧，他在哪儿？等一下!你醉了吗？"
#define GOSSIP_SELECT8  "为什么他在黑石深渊？"
#define GOSSIP_SELECT9  "300？所以黑铁杀死了他，把他拖进了深渊？"
#define GOSSIP_SELECT10 "啊。。反对者"
#define GOSSIP_SELECT11 "谢谢，狼狈不堪的约翰。你的故事非常振奋人心，内容丰富。"

struct npc_ragged_johnAI : public ScriptedAI
{
    npc_ragged_johnAI(Creature *c) : ScriptedAI(c) {}

    void Reset() {}

    void MoveInLineOfSight(Unit *who)
    {
        if( who->HasAura(16468,0) )
        {
            if( who->GetTypeId() == TYPEID_PLAYER && m_creature->IsWithinDistInMap(who, 15) && who->isInAccessiblePlacefor(m_creature) )
            {
                DoCast(who,16472);
                ((Player*)who)->AreaExploredOrEventHappens(4866);
            }
        }

        ScriptedAI::MoveInLineOfSight(who);
    }

    void EnterCombat(Unit *who) {}
};

CreatureAI* GetAI_npc_ragged_john(Creature *_Creature)
{
    return new npc_ragged_johnAI (_Creature);
}

bool GossipHello_npc_ragged_john(Player *player, Creature *_Creature)
{
    if (_Creature->isQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );

    if (player->GetQuestStatus(4224) == QUEST_STATUS_INCOMPLETE)
        player->ADD_GOSSIP_ITEM( 0, GOSSIP_HELLO, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    player->SEND_GOSSIP_MENU(2713, _Creature->GetGUID());
    return true;
}

bool GossipSelect_npc_ragged_john(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
            player->SEND_GOSSIP_MENU(2714, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+1:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
            player->SEND_GOSSIP_MENU(2715, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 3);
            player->SEND_GOSSIP_MENU(2716, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT4, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 4);
            player->SEND_GOSSIP_MENU(2717, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT5, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            player->SEND_GOSSIP_MENU(2718, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT6, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 6);
            player->SEND_GOSSIP_MENU(2719, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT7, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 7);
            player->SEND_GOSSIP_MENU(2720, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT8, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 8);
            player->SEND_GOSSIP_MENU(2721, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+8:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT9, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 9);
            player->SEND_GOSSIP_MENU(2722, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+9:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT10, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 10);
            player->SEND_GOSSIP_MENU(2723, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+10:
            player->ADD_GOSSIP_ITEM( 0, GOSSIP_SELECT11, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 11);
            player->SEND_GOSSIP_MENU(2725, _Creature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+11:
            player->CLOSE_GOSSIP_MENU();
            player->AreaExploredOrEventHappens(4224);
            break;
    }
    return true;
}

#define NPC_SHANI_PROUDTUSK 9136 

bool GOUse_go_proudtuskremains(Player *player, GameObject* _GO)
{
    if (!GetClosestCreatureWithEntry(_GO, NPC_SHANI_PROUDTUSK, 30.0f))
    {
        float x,y,z;
        player->GetNearPoint(x,y,z, 0.0f, 5.0f, frand(0, 2*M_PI));
        player->SummonCreature(NPC_SHANI_PROUDTUSK, x,y,z, 0.0f, TEMPSUMMON_TIMED_DESPAWN, 120000);
    }
    else
        return true;
    return false;
}

/*######
## Script for Quest: Broodling Essence
######*/

// Spells
#define SPELL_DRACO_INCARCINATRIX_900   16007
#define SPELL_CREATE_BROODLING_ESSENCE  16027
#define SPELL_FIREBALL                    13375

struct mob_broodlingessenceAI : public ScriptedAI
{

    mob_broodlingessenceAI(Creature *c) : ScriptedAI(c) {}

    bool onSpellEffect;
    uint32 Fireball_Timer;

    void Reset()
    {
        Fireball_Timer = 0;
        onSpellEffect = false;
    }

    void EnterCombat(Unit *who){}

    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if(spell->Id == SPELL_DRACO_INCARCINATRIX_900)
        {
            onSpellEffect = true;
        }
    }

    void JustDied(Unit* killer)
    {
        if(onSpellEffect)
        {
            me->CastSpell(me, SPELL_CREATE_BROODLING_ESSENCE, true);
            me->RemoveCorpse();
        }
    }

    void UpdateAI(const uint32 diff)
    {
        //Return since we have no target
        if (!UpdateVictim() )
            return;

        //Fireball_Timer
        if (Fireball_Timer < diff)
        {
            DoCast(m_creature->getVictim(),SPELL_FIREBALL);
            Fireball_Timer = 10000;
        }
        else
            Fireball_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_broodlingessence(Creature *_Creature)
{
    return new mob_broodlingessenceAI (_Creature);
}

/*######
## go_thaurissan_relic
######*/
const char* RelicQuotes[] =
{
    "蝎子…你将因这次入侵而受到惩罚。",
    "你的存在是公认的。",
    "帮助我们，局外人。",
    "他不能被打败。",
    "离开这个地方。",
    "不要玷污这些废墟，凡人。"
};

const char* RelicEmotes[] =
{
    "象征着火焰的辐射从文物才粉碎了地球。",
    "废墟变成尘土。你的头与新发现的智慧跳动。邪恶的东西潜伏在山的中心。",
    "文物碎尘。一个八个暗铁矮人做某种仪式的幻象充满了你的头脑。",
    "圣物烧成一无所有。它的记忆现在是你自己的。这个城市被一个不属于这个世界的人毁灭了。",
    "文物发出火焰炽热的弧。有一个记忆：一个孤独的暗铁矮人被七具尸体包围，跪在一团火焰前。",
    "你被一道耀眼的光芒吞噬。一个完全由火焰组成的生物是你唯一能记住的东西。"
};

bool GOUse_go_thaurissan_relic(Player *player, GameObject* _GO)
{
    if (_GO == nullptr || player == nullptr || !_GO->IsInWorld() || !player->IsInWorld())
        return false;

    if (player->GetQuestStatus(3701) == QUEST_STATUS_INCOMPLETE)
    {
        uint8 id = urand(0, (sizeof(RelicQuotes)/sizeof(char*)) -1);
        
        WorldPacket data(SMSG_MESSAGECHAT, 200);        //whisper packet - with name
        _GO->BuildMonsterChat(&data,CHAT_MSG_MONSTER_WHISPER,RelicQuotes[id],LANG_UNIVERSAL, "一个痛苦的声音", player->GetGUID());
        player->SendPacketToSelf(&data);

        _GO->MonsterTextEmote(RelicEmotes[id], player->GetGUID());

        player->CastedCreatureOrGO(_GO->GetEntry(), _GO->GetGUID(), 0);

        _GO->SetRespawnTime(120);
    }

    return true;
}

void AddSC_burning_steppes()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="npc_ragged_john";
    newscript->GetAI = &GetAI_npc_ragged_john;
    newscript->pGossipHello =  &GossipHello_npc_ragged_john;
    newscript->pGossipSelect = &GossipSelect_npc_ragged_john;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_proudtuskremains";
    newscript->pGOUse = &GOUse_go_proudtuskremains;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_broodlingessence";
    newscript->GetAI = &GetAI_mob_broodlingessence;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_thaurissan_relic";
    newscript->pGOUse = &GOUse_go_thaurissan_relic;
    newscript->RegisterSelf();
}

