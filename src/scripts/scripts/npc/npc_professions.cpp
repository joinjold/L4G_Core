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
SDName: Npc_Professions
SD%Complete: 80
SDComment: Provides learn/unlearn/relearn-options for professions. Not supported: Unlearn engineering, re-learn engineering, re-learn leatherworking.
SDCategory: NPCs
EndScriptData */

#include "precompiled.h"

/*
A few notes for future developement:
- A full implementation of gossip for GO's is required. They must have the same scripting capabilities as creatures. Basically,
there is no difference here (except that default text is chosen with `gameobject_template`.`data3` (for GO type2, different dataN for a few others)
- It's possible blacksmithing still require some tweaks and adjustments due to the way we _have_ to use reputation.
*/

/*
-- UPDATE `gameobject_template` SET `ScriptName` = 'go_soothsaying_for_dummies' WHERE `entry` = 177226;
*/

/*###
# to be removed from here (->ncp_text). This is data for database projects.
###*/
#define TALK_MUST_UNLEARN_WEAPON    "在我帮你之前，你必须忘掉你的武器专业。去冬泉谷的永望镇在那里寻求帮助。"

#define TALK_HAMMER_LEARN           "啊，你曾经是一个经验丰富的老将。 我知道你有能力，你只需要问，我会教你铸锤的方法."
#define TALK_AXE_LEARN              "啊，你曾经是一个经验丰富的老将。 我知道你有能力，你只需要问，我会教你铸斧的方法."
#define TALK_SWORD_LEARN            "啊，你曾经是一个经验丰富的老将。 我知道你有能力，你只需要问，我会教你铸剑的方法."

#define TALK_HAMMER_UNLEARN         "忘记你的铸锤技巧不是轻而易举的事情。如果你选择放弃它，你会忘记所有需要铸锤的方法!"
#define TALK_AXE_UNLEARN            "忘记你的铸斧技能不是轻而易举的事情。如果你选择放弃它，你会忘记所有需要铸斧的方法!"
#define TALK_SWORD_UNLEARN          "忘了你的铸剑技能不是轻而易举的事情。如果你选择放弃它，你会忘记所有需要铸剑的方法!"

/*###
# generic defines
###*/

#define GOSSIP_SENDER_LEARN         50
#define GOSSIP_SENDER_UNLEARN       51
#define GOSSIP_SENDER_CHECK         52

/*###
# gossip item and box texts
###*/

#define GOSSIP_LEARN_POTION         "请教我如何成为药水大师。劳兰娜·萨维尔"
#define GOSSIP_UNLEARN_POTION       "我希望忘却精通药水"
#define GOSSIP_LEARN_TRANSMUTE      "请你教教我如何成为一个转化大师, 萨雷维"
#define GOSSIP_UNLEARN_TRANSMUTE    "我希望忘却转化大师"
#define GOSSIP_LEARN_ELIXIR         "请教我如何成为一个药剂大师师, 罗罗基姆"
#define GOSSIP_UNLEARN_ELIXIR       "我希望忘却药剂大师"

#define BOX_UNLEARN_ALCHEMY_SPEC    "你真的想忘掉你的炼金专业失去了所有相关的法术? \n Cost: "

#define GOSSIP_WEAPON_LEARN         "请你教教我如何锻造一种武器"
#define GOSSIP_WEAPON_UNLEARN       "我愿放弃武器锻造工匠的艺术"
#define GOSSIP_ARMOR_LEARN          "请你教教我如何锻造一种防具"
#define GOSSIP_ARMOR_UNLEARN        "我想忘掉锻造防具工匠的艺术"

#define GOSSIP_UNLEARN_SMITH_SPEC   "我想忘掉我的锻造专业"
#define BOX_UNLEARN_ARMORORWEAPON   "你真的想忘掉你的锻造专业失去了所有相关的法术? \n Cost: "

#define GOSSIP_LEARN_HAMMER         "请你教教我如何成为一个大师级铸锤, Lilith"
#define GOSSIP_UNLEARN_HAMMER       "我想忘掉大师级铸锤"
#define GOSSIP_LEARN_AXE            "请你教教我如何成为一个大师级铸斧, Kilram"
#define GOSSIP_UNLEARN_AXE          "我想忘掉大师级铸斧"
#define GOSSIP_LEARN_SWORD          "请你教教我如何成为一个大师级铸剑, Seril"
#define GOSSIP_UNLEARN_SWORD        "我想忘掉大师级铸剑"

#define BOX_UNLEARN_WEAPON_SPEC     "你真的想忘掉你的武器专业失去了所有相关的法术? \n Cost: "

#define GOSSIP_LEARN_DRAGON         "我绝对相信我想学习龙鳞制皮"
#define GOSSIP_UNLEARN_DRAGON       "我想忘掉龙鳞制皮"
#define GOSSIP_LEARN_ELEMENTAL      "我绝对相信我想学习元素制皮"
#define GOSSIP_UNLEARN_ELEMENTAL    "我想忘掉元素制皮"
#define GOSSIP_LEARN_TRIBAL         "我绝对相信我想学习部族制皮"
#define GOSSIP_UNLEARN_TRIBAL       "我想忘掉部族制皮"

#define BOX_UNLEARN_LEATHER_SPEC    "你真的想忘掉你的制皮专业失去了所有相关的法术? \n Cost: "

#define GOSSIP_LEARN_SPELLFIRE      "请你教教我如何成为一个魔焰裁缝"
#define GOSSIP_UNLEARN_SPELLFIRE    "我希望忘却魔焰裁缝"
#define GOSSIP_LEARN_MOONCLOTH      "请你教教我如何成为一个月布裁缝"
#define GOSSIP_UNLEARN_MOONCLOTH    "我希望忘却月布裁缝"
#define GOSSIP_LEARN_SHADOWEAVE     "请你教教我如何成为一个暗纹裁缝"
#define GOSSIP_UNLEARN_SHADOWEAVE   "我希望忘却暗纹裁缝"

#define BOX_UNLEARN_TAILOR_SPEC     "你真的想忘掉你的裁缝专业失去了所有相关的法术? \n Cost: "

#define GOSSIP_LEARN_GOBLIN         "我绝对肯定我想学地精工程学。"
#define GOSSIP_UNLEARN_GOBLIN       "我想忘掉我的地精工程学专业!"
#define GOSSIP_LEARN_GNOMISH        "我绝对肯定我想学侏儒工程学。"
#define GOSSIP_UNLEARN_GNOMISH      "我想忘掉我的侏儒工程学专业!"

#define BOX_UNLEARN_GOBLIN_SPEC     "你真的想忘掉你的地精工程专业并失去所有相关法术?"
#define BOX_UNLEARN_GNOMISH_SPEC    "你真的想忘掉你的侏儒工程专业并失去所有相关法术?"

/*###
# spells defines
###*/

#define S_WEAPON                9787	//武器锻造
#define S_ARMOR                 9788	//防具锻造
#define S_HAMMER                17040	//大师级铸锤
#define S_AXE                   17041	//大师级铸斧
#define S_SWORD                 17039	//大师级铸剑

#define S_LEARN_WEAPON          9789	//武器锻造
#define S_LEARN_ARMOR           9790	//防具锻造
#define S_LEARN_HAMMER          39099	//大师级铸锤
#define S_LEARN_AXE             39098	//大师级铸斧
#define S_LEARN_SWORD           39097	//大师级铸剑

#define S_UNLEARN_WEAPON        36436	//遗忘
#define S_UNLEARN_ARMOR         36435	//遗忘
#define S_UNLEARN_HAMMER        36441	//遗忘
#define S_UNLEARN_AXE           36439	//遗忘
#define S_UNLEARN_SWORD         36438	//遗忘

#define S_REP_ARMOR             17451	
#define S_REP_WEAPON            17452

#define REP_ARMOR               46	//
#define REP_WEAPON              289
#define REP_HAMMER              569
#define REP_AXE                 570
#define REP_SWORD               571

#define S_DRAGON                10656	//龙鳞制皮
#define S_ELEMENTAL             10658	//元素制皮
#define S_TRIBAL                10660	//部族制皮

#define S_LEARN_DRAGON          10657
#define S_LEARN_ELEMENTAL       10659
#define S_LEARN_TRIBAL          10661

#define S_UNLEARN_DRAGON        36434	//遗忘
#define S_UNLEARN_ELEMENTAL     36328	//遗忘
#define S_UNLEARN_TRIBAL        36433	//遗忘

#define S_GOBLIN                20222	//地精工程师
#define S_GNOMISH               20219	//侏儒工程师

#define S_LEARN_GOBLIN          20221	//地精工程师
#define S_LEARN_GNOMISH         20220	//侏儒工程师

#define S_SPELLFIRE             26797	//魔焰裁缝	
#define S_MOONCLOTH             26798	//月布裁缝
#define S_SHADOWEAVE            26801	//暗纹裁缝

#define S_LEARN_SPELLFIRE       26796	
#define S_LEARN_MOONCLOTH       26799
#define S_LEARN_SHADOWEAVE      26800

#define S_UNLEARN_SPELLFIRE     41299	//遗忘魔焰裁缝
#define S_UNLEARN_MOONCLOTH     41558	//遗忘月布裁缝
#define S_UNLEARN_SHADOWEAVE    41559	//遗忘暗纹裁缝

#define S_TRANSMUTE             28672	
#define S_ELIXIR                28677
#define S_POTION                28675

#define S_LEARN_TRANSMUTE       28674	//转化大师
#define S_LEARN_ELIXIR          28678	//药剂大师
#define S_LEARN_POTION          28676	//药水大师

#define S_UNLEARN_TRANSMUTE     41565	//遗忘转化大师
#define S_UNLEARN_ELIXIR        41564	//遗忘药剂大师
#define S_UNLEARN_POTION        41563	//遗忘药水大师

/*###
# formulas to calculate unlearning cost
###*/

void RemoveProffesionQuest(uint32 entry, Player *player)
{
    for(uint8 slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot )
    {
        uint32 quest = player->GetQuestSlotQuestId(slot);
        if(quest == entry)
        {
            player->SetQuestSlot(slot,0);

            // we ignore unequippable quest items in this case, its' still be equipped
            player->TakeQuestSourceItem( quest, false );
        }
     }

     player->SetQuestStatus( entry, QUEST_STATUS_NONE);
     player->getQuestStatusMap()[entry].m_rewarded = false;
}

int32 DoLearnCost(Player *player)                           //tailor, alchemy
{
    return 200000;
}

int32 DoHighUnlearnCost(Player *player)                     //tailor, alchemy
{
    return 1500000;
}

int32 DoMedUnlearnCost(Player *player)                      //blacksmith, leatherwork
{
    uint32 level = player->getLevel();
    if(level < 51)
        return 250000;
    else if (level < 66)
        return 500000;
    else
        return 1000000;
}

int32 DoLowUnlearnCost(Player *player)                      //blacksmith
{
    uint32 level = player->getLevel();
    if (level < 66)
        return 50000;
    else
        return 100000;
}

/*###
# unlearning related profession spells
###*/

bool EquippedOk(Player* player, uint32 spellId)
{
    SpellEntry const* spell = GetSpellStore()->LookupEntry(spellId);

    if( !spell )
        return false;

    for(int i=0; i<3; i++)
    {
        uint32 reqSpell = spell->EffectTriggerSpell[i];
        if( !reqSpell )
            continue;

        Item* pItem;
        for(int j = EQUIPMENT_SLOT_START; j < EQUIPMENT_SLOT_END; j++)
        {
            pItem = player->GetItemByPos( INVENTORY_SLOT_BAG_0, j );
            if( pItem )
                if( pItem->GetProto()->RequiredSpell == reqSpell )
            {
                //player has item equipped that require specialty. Not allow to unlearn, player has to unequip first
                debug_log("TSCR: player attempt to unlearn spell %u, but item %u is equipped.",reqSpell,pItem->GetProto()->ItemId);
                return false;
            }
        }
    }
    return true;
}

void ProfessionUnlearnSpells(Player *player, uint32 type)
{
    switch (type)
    {
        case 36436:                                         // S_UNLEARN_WEAPON
            player->removeSpell(36125);                     // Light Earthforged Blade
            player->removeSpell(36128);                     // Light Emberforged Hammer
            player->removeSpell(36126);                     // Light Skyforged Axe
            break;
        case 36435:                                         // S_UNLEARN_ARMOR
            player->removeSpell(36122);                     // Earthforged Leggings
            player->removeSpell(36129);                     // Heavy Earthforged Breastplate
            player->removeSpell(36130);                     // Stormforged Hauberk
            player->removeSpell(34533);                     // Breastplate of Kings
            player->removeSpell(34529);                     // Nether Chain Shirt
            player->removeSpell(34534);                     // Bulwark of Kings
            player->removeSpell(36257);                     // Bulwark of the Ancient Kings
            player->removeSpell(36256);                     // Embrace of the Twisting Nether
            player->removeSpell(34530);                     // Twisting Nether Chain Shirt
            player->removeSpell(36124);                     // Windforged Leggings
            break;
        case 36441:                                         // S_UNLEARN_HAMMER
            player->removeSpell(36262);                     // Dragonstrike
            player->removeSpell(34546);                     // Dragonmaw
            player->removeSpell(34545);                     // Drakefist Hammer
            player->removeSpell(36136);                     // Lavaforged Warhammer
            player->removeSpell(34547);                     // Thunder
            player->removeSpell(34567);                     // Deep Thunder
            player->removeSpell(36263);                     // Stormherald
            player->removeSpell(36137);                     // Great Earthforged Hammer
            break;
        case 36439:                                         // S_UNLEARN_AXE
            player->removeSpell(36260);                     // Wicked Edge of the Planes
            player->removeSpell(34562);                     // Black Planar Edge
            player->removeSpell(34541);                     // The Planar Edge
            player->removeSpell(36134);                     // Stormforged Axe
            player->removeSpell(36135);                     // Skyforged Great Axe
            player->removeSpell(36261);                     // Bloodmoon
            player->removeSpell(34543);                     // Lunar Crescent
            player->removeSpell(34544);                     // Mooncleaver
            break;
        case 36438:                                         // S_UNLEARN_SWORD
            player->removeSpell(36258);                     // Blazefury
            player->removeSpell(34537);                     // Blazeguard
            player->removeSpell(34535);                     // Fireguard
            player->removeSpell(36131);                     // Windforged Rapier
            player->removeSpell(36133);                     // Stoneforged Claymore
            player->removeSpell(34538);                     // Lionheart Blade
            player->removeSpell(34540);                     // Lionheart Champion
            player->removeSpell(36259);                     // Lionheart Executioner
            break;
        case 36434:                                         // S_UNLEARN_DRAGON
            player->removeSpell(36076);                     // Dragonstrike Leggings
            player->removeSpell(36079);                     // Golden Dragonstrike Breastplate
            player->removeSpell(35576);                     // Ebon Netherscale Belt
            player->removeSpell(35577);                     // Ebon Netherscale Bracers
            player->removeSpell(35575);                     // Ebon Netherscale Breastplate
            player->removeSpell(35582);                     // Netherstrike Belt
            player->removeSpell(35584);                     // Netherstrike Bracers
            player->removeSpell(35580);                     // Netherstrike Breastplate
            break;
        case 36328:                                         // S_UNLEARN_ELEMENTAL
            player->removeSpell(36074);                     // Blackstorm Leggings
            player->removeSpell(36077);                     // Primalstorm Breastplate
            player->removeSpell(35590);                     // Primalstrike Belt
            player->removeSpell(35591);                     // Primalstrike Bracers
            player->removeSpell(35589);                     // Primalstrike Vest
            break;
        case 36433:                                         // S_UNLEARN_TRIBAL
            player->removeSpell(35585);                     // Windhawk Hauberk
            player->removeSpell(35587);                     // Windhawk Belt
            player->removeSpell(35588);                     // Windhawk Bracers
            player->removeSpell(36075);                     // Wildfeather Leggings
            player->removeSpell(36078);                     // Living Crystal Breastplate
            break;
        case 41299:                                         // S_UNLEARN_SPELLFIRE
            player->removeSpell(26752);                     // Spellfire Belt
            player->removeSpell(26753);                     // Spellfire Gloves
            player->removeSpell(26754);                     // Spellfire Robe
            break;
        case 41558:                                         // S_UNLEARN_MOONCLOTH
            player->removeSpell(26760);                     // Primal Mooncloth Belt
            player->removeSpell(26761);                     // Primal Mooncloth Shoulders
            player->removeSpell(26762);                     // Primal Mooncloth Robe
            break;
        case 41559:                                         // S_UNLEARN_SHADOWEAVE
            player->removeSpell(26756);                     // Frozen Shadoweave Shoulders
            player->removeSpell(26757);                     // Frozen Shadoweave Boots
            player->removeSpell(26758);                     // Frozen Shadoweave Robe
            break;
    }
}

/*###
# start menues alchemy
###*/

bool HasAlchemySpell(Player *player)
{
    if(player->HasSpell(S_TRANSMUTE) || player->HasSpell(S_ELIXIR) || player->HasSpell(S_POTION))
        return true;
    return false;
}

bool GossipHello_npc_prof_alchemy(Player *player, Creature *_Creature)
{
    if (_Creature->isQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );
    if (_Creature->isVendor())
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    if(_Creature->isTrainer())
        player->ADD_GOSSIP_ITEM(2, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    uint32 eCreature = _Creature->GetEntry();
    bool hadPrevAlchemyProf = false;
    QueryResultAutoPtr speci_result = RealmDataDatabase.PQuery("SELECT COUNT(*) FROM character_quest_specialization WHERE guid = '%u' AND spezi_quest = '1' AND done = 1", player->GetGUID());
    if (speci_result)
    {
        Field* fields = speci_result->Fetch();
        hadPrevAlchemyProf = fields[0].GetInt32();
    }

    if (player->HasSkill(SKILL_ALCHEMY) && player->GetBaseSkillValue(SKILL_ALCHEMY)>=350 && player->getLevel() > 67)
    {
        if (player->GetQuestRewardStatus(10899) || player->GetQuestRewardStatus(10902) || player->GetQuestRewardStatus(10897) || hadPrevAlchemyProf)
        {
            switch (eCreature)
            {
                case 22427:                                 //Zarevhi
                    if (!HasAlchemySpell(player))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_TRANSMUTE,    GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 1);
                    if (player->HasSpell(S_TRANSMUTE))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_TRANSMUTE,  GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 4);
                    break;
                case 19052:                                 //Lorokeem
                    if (!HasAlchemySpell(player))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_ELIXIR,       GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 2);
                    if (player->HasSpell(S_ELIXIR))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_ELIXIR,     GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 5);
                    break;
                case 17909:                                 //Lauranna Thar'well
                    if (!HasAlchemySpell(player))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_POTION,       GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 3);
                    if (player->HasSpell(S_POTION))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_POTION,     GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 6);
                    break;
            }
        }
    }

    player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
    return true;
}

void SendActionMenu_npc_prof_alchemy(Player *player, Creature *_Creature, uint32 action)
{
    switch(action)
    {
        case GOSSIP_ACTION_TRADE:
            player->SEND_VENDORLIST( _Creature->GetGUID() );
            break;
        case GOSSIP_ACTION_TRAIN:
            player->SEND_TRAINERLIST( _Creature->GetGUID() );
            break;
            //Learn Alchemy
        case GOSSIP_ACTION_INFO_DEF + 1:
            if(!player->HasSpell(S_TRANSMUTE) && player->GetMoney() >= DoHighUnlearnCost(player))
            {
                player->CastSpell(player, S_LEARN_TRANSMUTE, true);
                player->ModifyMoney(-DoHighUnlearnCost(player));
                RealmDataDatabase.PExecute("DELETE FROM character_quest_specialization WHERE guid = '%u' AND spezi_quest = '1'", player->GetGUID());
            }
            else
                player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if(!player->HasSpell(S_ELIXIR) && player->GetMoney() >= DoHighUnlearnCost(player))
            {
                player->CastSpell(player, S_LEARN_ELIXIR, true);
                player->ModifyMoney(-DoHighUnlearnCost(player));
                RealmDataDatabase.PExecute("DELETE FROM character_quest_specialization WHERE guid = '%u' AND spezi_quest = '1'", player->GetGUID());
            }
            else
                player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            if(!player->HasSpell(S_POTION) && player->GetMoney() >= DoHighUnlearnCost(player))
            {
                player->CastSpell(player, S_LEARN_POTION, true);
                player->ModifyMoney(-DoHighUnlearnCost(player));
                RealmDataDatabase.PExecute("DELETE FROM character_quest_specialization WHERE guid = '%u' AND spezi_quest = '1'", player->GetGUID());
            }
            else
                player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            player->CLOSE_GOSSIP_MENU();
            break;
            //Unlearn Alchemy
        case GOSSIP_ACTION_INFO_DEF + 4:
            _Creature->CastSpell(player, S_UNLEARN_TRANSMUTE, true);
            RemoveProffesionQuest(10899, player);
            RemoveProffesionQuest(10907, player);
            RealmDataDatabase.PExecute("INSERT INTO character_quest_specialization (guid, spezi_quest, done) VALUES ('%u', 1, 1)", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            _Creature->CastSpell(player, S_UNLEARN_ELIXIR, true);
            //player->ModifyMoney(-DoHighUnlearnCost(player));
            RemoveProffesionQuest(10902, player);
            RemoveProffesionQuest(10906, player);
            RealmDataDatabase.PExecute("INSERT INTO character_quest_specialization (guid, spezi_quest, done) VALUES ('%u', 1, 1)", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            _Creature->CastSpell(player, S_UNLEARN_POTION, true);
            //player->ModifyMoney(-DoHighUnlearnCost(player));
            RemoveProffesionQuest(10897, player);
            RemoveProffesionQuest(10905, player);
            RealmDataDatabase.PExecute("INSERT INTO character_quest_specialization (guid, spezi_quest, done) VALUES ('%u', 1, 1)", player->GetGUID());
            player->CLOSE_GOSSIP_MENU();
            break;
    }
}

void SendConfirmLearn_npc_prof_alchemy(Player *player, Creature *_Creature, uint32 action)
{
    if(action)
    {
        uint32 eCreature = _Creature->GetEntry();
        switch(eCreature)
        {
            case 22427:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_TRANSMUTE, GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 19052:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_ELIXIR,    GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 17909:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_POTION,    GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
        }
    }
}

void SendConfirmUnlearn_npc_prof_alchemy(Player *player, Creature *_Creature, uint32 action)
{
    if(action)
    {
        uint32 eCreature = _Creature->GetEntry();
        switch(eCreature)
        {
            case 22427:                                     //Zarevhi
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_TRANSMUTE, GOSSIP_SENDER_CHECK, action, BOX_UNLEARN_ALCHEMY_SPEC, DoHighUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 19052:                                     //Lorokeem
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_ELIXIR, GOSSIP_SENDER_CHECK, action,    BOX_UNLEARN_ALCHEMY_SPEC, DoHighUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 17909:                                     //Lauranna Thar'well
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_POTION, GOSSIP_SENDER_CHECK, action,    BOX_UNLEARN_ALCHEMY_SPEC, DoHighUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
        }
    }
}

bool GossipSelect_npc_prof_alchemy(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    switch(sender)
    {
        case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_alchemy(player, _Creature, action); break;
        case GOSSIP_SENDER_LEARN:   SendConfirmLearn_npc_prof_alchemy(player, _Creature, action); break;
        case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_prof_alchemy(player, _Creature, action); break;
        case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_alchemy(player, _Creature, action); break;
    }
    return true;
}

/*###
# start menues blacksmith
###*/

bool HasWeaponSub(Player *player)
{
    if (player->HasSpell(S_HAMMER) || player->HasSpell(S_AXE) || player->HasSpell(S_SWORD))
        return true;
    return false;
}

bool GossipHello_npc_prof_blacksmith(Player *player, Creature *_Creature)
{
    if (_Creature->isQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );
    if (_Creature->isVendor())
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    if(_Creature->isTrainer())
        player->ADD_GOSSIP_ITEM(2, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    uint32 eCreature = _Creature->GetEntry();
    //WEAPONSMITH & ARMORSMITH
    if(player->GetBaseSkillValue(SKILL_BLACKSMITHING)>=225)
    {
        switch (eCreature)
        {
            case 11145:                                     //Myolor Sunderfury
            case 11176:                                     //Krathok Moltenfist
                if(!player->HasSpell(S_ARMOR) && !player->HasSpell(S_WEAPON) && player->GetReputationMgr().GetRank(REP_ARMOR) >=  REP_FRIENDLY)
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_ARMOR_LEARN,   GOSSIP_SENDER_MAIN,          GOSSIP_ACTION_INFO_DEF + 1);
                if(!player->HasSpell(S_WEAPON) && !player->HasSpell(S_ARMOR) && player->GetReputationMgr().GetRank(REP_WEAPON) >= REP_FRIENDLY)
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_WEAPON_LEARN,  GOSSIP_SENDER_MAIN,          GOSSIP_ACTION_INFO_DEF + 2);
                break;
            case 11146:                                     //Ironus Coldsteel
            case 11178:                                     //Borgosh Corebender
                if(player->HasSpell(S_WEAPON))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_WEAPON_UNLEARN,    GOSSIP_SENDER_UNLEARN,   GOSSIP_ACTION_INFO_DEF + 3);
                break;
            case 5164:                                      //Grumnus Steelshaper
            case 11177:                                     //Okothos Ironrager
                if(player->HasSpell(S_ARMOR))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_ARMOR_UNLEARN,     GOSSIP_SENDER_UNLEARN,   GOSSIP_ACTION_INFO_DEF + 4);
                break;
        }
    }
    //WEAPONSMITH SPEC
    if(player->HasSpell(S_WEAPON) && player->getLevel() > 49 && player->GetBaseSkillValue(SKILL_BLACKSMITHING)>=250)
    {
        switch (eCreature)
        {
            case 11191:                                     //Lilith the Lithe
                if(!HasWeaponSub(player))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_HAMMER,       GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 5);
                if(player->HasSpell(S_HAMMER))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_HAMMER,     GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 8);
                break;
            case 11192:                                     //Kilram
                if(!HasWeaponSub(player))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_AXE,          GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 6);
                if(player->HasSpell(S_AXE))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_AXE,        GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 9);
                break;
            case 11193:                                     //Seril Scourgebane
                if(!HasWeaponSub(player))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_SWORD,        GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 7);
                if(player->HasSpell(S_SWORD))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_SWORD,      GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 10);
                break;
        }
    }

    player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
    return true;
}

void SendActionMenu_npc_prof_blacksmith(Player *player, Creature *_Creature, uint32 action)
{
    switch(action)
    {
        case GOSSIP_ACTION_TRADE:
            player->SEND_VENDORLIST( _Creature->GetGUID() );
            break;
        case GOSSIP_ACTION_TRAIN:
            player->SEND_TRAINERLIST( _Creature->GetGUID() );
            break;
            //Learn Armor/Weapon
        case GOSSIP_ACTION_INFO_DEF + 1:
            if(!player->HasSpell(S_ARMOR))
            {
                player->CastSpell(player, S_LEARN_ARMOR, true);
                //_Creature->CastSpell(player, S_REP_ARMOR, true);
            }
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if(!player->HasSpell(S_WEAPON))
            {
                player->CastSpell(player, S_LEARN_WEAPON, true);
                //_Creature->CastSpell(player, S_REP_WEAPON, true);
            }
            player->CLOSE_GOSSIP_MENU();
            break;
            //Unlearn Armor/Weapon
        case GOSSIP_ACTION_INFO_DEF + 3:
            if(HasWeaponSub(player))
            {
                                                            //unknown textID (TALK_MUST_UNLEARN_WEAPON)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                                                            //Temporary, not offilike
                _Creature->MonsterSay(TALK_MUST_UNLEARN_WEAPON,0,player->GetGUID());
            }
            else if( EquippedOk(player,S_UNLEARN_WEAPON) )
            {
                if( player->GetMoney() >= DoLowUnlearnCost(player) )
                {
                    player->CastSpell(player, S_UNLEARN_WEAPON, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_WEAPON);
                    player->ModifyMoney(-DoLowUnlearnCost(player));
                    _Creature->CastSpell(player, S_REP_ARMOR, true);

                    RemoveProffesionQuest(player->GetTeam() == ALLIANCE ? 5284 : 5302, player);
                    player->CLOSE_GOSSIP_MENU();
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
            {
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
                player->CLOSE_GOSSIP_MENU();
            }
            break;
        case GOSSIP_ACTION_INFO_DEF + 4:
            if( EquippedOk(player,S_UNLEARN_ARMOR) )
            {
                if( player->GetMoney() >= DoLowUnlearnCost(player) )
                {
                    player->CastSpell(player, S_UNLEARN_ARMOR, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_ARMOR);
                    player->ModifyMoney(-DoLowUnlearnCost(player));
                    RemoveProffesionQuest(player->GetTeam() == ALLIANCE ? 5283 : 5301, player);
                    _Creature->CastSpell(player, S_REP_WEAPON, true);
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
            //Learn Hammer/Axe/Sword
        case GOSSIP_ACTION_INFO_DEF + 5:
            player->CastSpell(player, S_LEARN_HAMMER, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            player->CastSpell(player, S_LEARN_AXE, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 7:
            player->CastSpell(player, S_LEARN_SWORD, true);
            player->CLOSE_GOSSIP_MENU();
            break;
            //Unlearn Hammer/Axe/Sword
        case GOSSIP_ACTION_INFO_DEF + 8:
            if( EquippedOk(player,S_UNLEARN_HAMMER) )
            {
                if( player->GetMoney() >= DoMedUnlearnCost(player))
                {
                    player->CastSpell(player, S_UNLEARN_HAMMER, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_HAMMER);
                    player->ModifyMoney(-DoMedUnlearnCost(player));
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 9:
            if( EquippedOk(player,S_UNLEARN_AXE) )
            {
                if( player->GetMoney() >= DoMedUnlearnCost(player))
                {
                    player->CastSpell(player, S_UNLEARN_AXE, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_AXE);
                    player->ModifyMoney(-DoMedUnlearnCost(player));
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 10:
            if( EquippedOk(player,S_UNLEARN_SWORD) )
            {
                if( player->GetMoney() >= DoMedUnlearnCost(player))
                {
                    player->CastSpell(player, S_UNLEARN_SWORD, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_SWORD);
                    player->ModifyMoney(-DoMedUnlearnCost(player));
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
    }
}

void SendConfirmLearn_npc_prof_blacksmith(Player *player, Creature *_Creature, uint32 action)
{
    if(action)
    {
        uint32 eCreature = _Creature->GetEntry();
        switch(eCreature)
        {
            case 11191:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_HAMMER, GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID (TALK_HAMMER_LEARN)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 11192:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_AXE,    GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID (TALK_AXE_LEARN)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 11193:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_SWORD,  GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID (TALK_SWORD_LEARN)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
        }
    }
}

void SendConfirmUnlearn_npc_prof_blacksmith(Player *player, Creature *_Creature, uint32 action)
{
    if(action)
    {
        uint32 eCreature = _Creature->GetEntry();
        switch(eCreature)
        {
            case 11146:                                     //Ironus Coldsteel
            case 11178:                                     //Borgosh Corebender
            case 5164:                                      //Grumnus Steelshaper
            case 11177:                                     //Okothos Ironrager
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_SMITH_SPEC, GOSSIP_SENDER_CHECK, action, BOX_UNLEARN_ARMORORWEAPON, DoLowUnlearnCost(player),false);
                                                            //unknown textID (TALK_UNLEARN_AXEORWEAPON)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;

            case 11191:
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_HAMMER, GOSSIP_SENDER_CHECK, action,    BOX_UNLEARN_WEAPON_SPEC, DoMedUnlearnCost(player),false);
                                                            //unknown textID (TALK_HAMMER_UNLEARN)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 11192:
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_AXE, GOSSIP_SENDER_CHECK, action,       BOX_UNLEARN_WEAPON_SPEC, DoMedUnlearnCost(player),false);
                                                            //unknown textID (TALK_AXE_UNLEARN)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 11193:
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_SWORD, GOSSIP_SENDER_CHECK, action,     BOX_UNLEARN_WEAPON_SPEC, DoMedUnlearnCost(player),false);
                                                            //unknown textID (TALK_SWORD_UNLEARN)
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
        }
    }
}

bool GossipSelect_npc_prof_blacksmith(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    switch(sender)
    {
        case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_blacksmith(player, _Creature, action); break;
        case GOSSIP_SENDER_LEARN:   SendConfirmLearn_npc_prof_blacksmith(player, _Creature, action); break;
        case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_prof_blacksmith(player, _Creature, action); break;
        case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_blacksmith(player, _Creature, action); break;
    }
    return true;
}

/*bool QuestComplete_npc_prof_blacksmith( Player *player, Creature *_Creature, Quest const *_Quest )
{
    if ( (_Quest->GetQuestId() == 5283) || (_Quest->GetQuestId() == 5301) )             //armorsmith
        _Creature->CastSpell(player, 17451, true);

    if ( (_Quest->GetQuestId() == 5284) || (_Quest->GetQuestId() == 5302) )             //weaponsmith
        _Creature->CastSpell(player, 17452, true);

    return true;
}*/

/*###
# start menues leatherworking
###*/

bool GossipHello_npc_prof_leather(Player *player, Creature *_Creature)
{
    if (_Creature->isQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );
    if (_Creature->isVendor())
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    if(_Creature->isTrainer())
        player->ADD_GOSSIP_ITEM(2, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    uint32 eCreature = _Creature->GetEntry();

    if(player->HasSkill(SKILL_LEATHERWORKING) && player->GetBaseSkillValue(SKILL_LEATHERWORKING)>=250 && player->getLevel() > 49 )
    {
        switch (eCreature)
        {
            case 7866:                                      //Peter Galen
            case 7867:                                      //Thorkaf Dragoneye
                if(player->HasSpell(S_DRAGON))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_DRAGON,      GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 1);
                break;
            case 7868:                                      //Sarah Tanner
            case 7869:                                      //Brumn Winterhoof
                if(player->HasSpell(S_ELEMENTAL))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_ELEMENTAL,   GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 2);
                break;
            case 7870:                                      //Caryssia Moonhunter
            case 7871:                                      //Se'Jib
                if(player->HasSpell(S_TRIBAL))
                    player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_TRIBAL,      GOSSIP_SENDER_UNLEARN, GOSSIP_ACTION_INFO_DEF + 3);
                break;
        }
    }

    player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
    return true;
}

void SendActionMenu_npc_prof_leather(Player *player, Creature *_Creature, uint32 action)
{
    switch(action)
    {
        case GOSSIP_ACTION_TRADE:
            player->SEND_VENDORLIST( _Creature->GetGUID() );
            break;
        case GOSSIP_ACTION_TRAIN:
            player->SEND_TRAINERLIST( _Creature->GetGUID() );
            break;
            //Unlearn Leather
        case GOSSIP_ACTION_INFO_DEF + 1:
            if( EquippedOk(player,S_UNLEARN_DRAGON) )
            {
                if( player->GetMoney() >= DoMedUnlearnCost(player) )
                {
                    player->CastSpell(player, S_UNLEARN_DRAGON, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_DRAGON);
                    player->ModifyMoney(-DoMedUnlearnCost(player));
                    RemoveProffesionQuest(player->GetTeam() == ALLIANCE ? 5141 : 5145, player);
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);

            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if( EquippedOk(player,S_UNLEARN_ELEMENTAL) )
            {
                if(player->GetMoney() >= DoMedUnlearnCost(player) )
                {
                    player->CastSpell(player, S_UNLEARN_ELEMENTAL, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_ELEMENTAL);
                    player->ModifyMoney(-DoMedUnlearnCost(player));
                    RemoveProffesionQuest(player->GetTeam() == ALLIANCE ? 5144 : 5146, player);
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            if( EquippedOk(player,S_UNLEARN_TRIBAL) )
            {
                if(player->GetMoney() >= DoMedUnlearnCost(player))
                {
                    player->CastSpell(player, S_UNLEARN_TRIBAL, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_TRIBAL);
                    player->ModifyMoney(-DoMedUnlearnCost(player));
                    RemoveProffesionQuest(player->GetTeam() == ALLIANCE ? 5143 : 5148, player);
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
    }
}

void SendConfirmUnlearn_npc_prof_leather(Player *player, Creature *_Creature, uint32 action)
{
    if(action)
    {
        uint32 eCreature = _Creature->GetEntry();
        switch(eCreature)
        {
            case 7866:                                      //Peter Galen
            case 7867:                                      //Thorkaf Dragoneye
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_DRAGON, GOSSIP_SENDER_CHECK, action,    BOX_UNLEARN_LEATHER_SPEC, DoMedUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 7868:                                      //Sarah Tanner
            case 7869:                                      //Brumn Winterhoof
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_ELEMENTAL, GOSSIP_SENDER_CHECK, action, BOX_UNLEARN_LEATHER_SPEC, DoMedUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 7870:                                      //Caryssia Moonhunter
            case 7871:                                      //Se'Jib
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_TRIBAL, GOSSIP_SENDER_CHECK, action,    BOX_UNLEARN_LEATHER_SPEC, DoMedUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
        }
    }
}

bool GossipSelect_npc_prof_leather(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    switch(sender)
    {
        case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_leather(player, _Creature, action); break;
        case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_prof_leather(player, _Creature, action); break;
        case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_leather(player, _Creature, action); break;
    }
    return true;
}

/*###
# start menues tailoring
###*/

bool HasTailorSpell(Player *player)
{
    if (player->HasSpell(S_MOONCLOTH) || player->HasSpell(S_SHADOWEAVE) || player->HasSpell(S_SPELLFIRE))
        return true;
    return false;
}

bool GossipHello_npc_prof_tailor(Player *player, Creature *_Creature)
{
    if (_Creature->isQuestGiver())
        player->PrepareQuestMenu( _Creature->GetGUID() );
    if (_Creature->isVendor())
        player->ADD_GOSSIP_ITEM(1, GOSSIP_TEXT_BROWSE_GOODS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE);
    if (_Creature->isTrainer())
        player->ADD_GOSSIP_ITEM(2, GOSSIP_TEXT_TRAIN, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRAIN);

    uint32 eCreature = _Creature->GetEntry();
                                                            //TAILORING SPEC
    if (player->HasSkill(SKILL_TAILORING) && player->GetBaseSkillValue(SKILL_TAILORING)>=350 && player->getLevel() > 59)
    {
        if (player->GetQuestRewardStatus(10831) || player->GetQuestRewardStatus(10832) || player->GetQuestRewardStatus(10833))
        {
            switch (eCreature)
            {
                case 22213:                                 //Gidge Spellweaver
                    if (!HasTailorSpell(player))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_SPELLFIRE,    GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 1);
                    if (player->HasSpell(S_SPELLFIRE))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_SPELLFIRE,  GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 4);
                    break;
                case 22208:                                 //Nasmara Moonsong
                    if (!HasTailorSpell(player))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_MOONCLOTH,    GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 2);
                    if (player->HasSpell(S_MOONCLOTH))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_MOONCLOTH,  GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 5);
                    break;
                case 22212:                                 //Andrion Darkspinner
                    if (!HasTailorSpell(player))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_SHADOWEAVE,   GOSSIP_SENDER_LEARN,    GOSSIP_ACTION_INFO_DEF + 3);
                    if (player->HasSpell(S_SHADOWEAVE))
                        player->ADD_GOSSIP_ITEM( 0, GOSSIP_UNLEARN_SHADOWEAVE, GOSSIP_SENDER_UNLEARN,  GOSSIP_ACTION_INFO_DEF + 6);
                    break;
            }
        }
    }

    player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
    return true;
}

void SendActionMenu_npc_prof_tailor(Player *player, Creature *_Creature, uint32 action)
{
    switch(action)
    {
        case GOSSIP_ACTION_TRADE:
            player->SEND_VENDORLIST( _Creature->GetGUID() );
            break;
        case GOSSIP_ACTION_TRAIN:
            player->SEND_TRAINERLIST( _Creature->GetGUID() );
            break;
            //Learn Tailor
        case GOSSIP_ACTION_INFO_DEF + 1:
            if(!player->HasSpell(S_SPELLFIRE) && player->GetMoney() >= DoLearnCost(player))
            {
                player->CastSpell(player, S_LEARN_SPELLFIRE, true);
                player->ModifyMoney(-DoLearnCost(player));
            }
            else
                player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 2:
            if(!player->HasSpell(S_MOONCLOTH) && player->GetMoney() >= DoLearnCost(player))
            {
                player->CastSpell(player, S_LEARN_MOONCLOTH, true);
                player->ModifyMoney(-DoLearnCost(player));
            }
            else
                player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 3:
            if(!player->HasSpell(S_SHADOWEAVE) && player->GetMoney() >= DoLearnCost(player))
            {
                player->CastSpell(player, S_LEARN_SHADOWEAVE, true);
                player->ModifyMoney(-DoLearnCost(player));
            }
            else
                player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            player->CLOSE_GOSSIP_MENU();
            break;
            //Unlearn Tailor
        case GOSSIP_ACTION_INFO_DEF + 4:
            if( EquippedOk(player,S_UNLEARN_SPELLFIRE) )
            {
                if( player->GetMoney() >= DoHighUnlearnCost(player) )
                {
                    player->CastSpell(player, S_UNLEARN_SPELLFIRE, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_SPELLFIRE);
                    player->ModifyMoney(-DoHighUnlearnCost(player));
                    RemoveProffesionQuest(10832, player);
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 5:
            if( EquippedOk(player,S_UNLEARN_MOONCLOTH) )
            {
                if( player->GetMoney() >= DoHighUnlearnCost(player) )
                {
                    player->CastSpell(player, S_UNLEARN_MOONCLOTH, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_MOONCLOTH);
                    player->ModifyMoney(-DoHighUnlearnCost(player));
                    RemoveProffesionQuest(10831, player);
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF + 6:
            if( EquippedOk(player,S_UNLEARN_SHADOWEAVE) )
            {
                if( player->GetMoney() >= DoHighUnlearnCost(player) )
                {
                    player->CastSpell(player, S_UNLEARN_SHADOWEAVE, true);
                    ProfessionUnlearnSpells(player, S_UNLEARN_SHADOWEAVE);
                    player->ModifyMoney(-DoHighUnlearnCost(player));
                    RemoveProffesionQuest(10833, player);
                }
                else
                    player->SendBuyError( BUY_ERR_NOT_ENOUGHT_MONEY, _Creature, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
    }
}

void SendConfirmLearn_npc_prof_tailor(Player *player, Creature *_Creature, uint32 action)
{
    if(action)
    {
        uint32 eCreature = _Creature->GetEntry();
        switch(eCreature)
        {
            case 22213:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_SPELLFIRE, GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 22208:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_MOONCLOTH,    GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 22212:
                player->ADD_GOSSIP_ITEM( 0, GOSSIP_LEARN_SHADOWEAVE,  GOSSIP_SENDER_CHECK, action);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
        }
    }
}

void SendConfirmUnlearn_npc_prof_tailor(Player *player, Creature *_Creature, uint32 action)
{
    if(action)
    {
        uint32 eCreature = _Creature->GetEntry();
        switch(eCreature)
        {
            case 22213:                                     //Gidge Spellweaver
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_SPELLFIRE, GOSSIP_SENDER_CHECK, action, BOX_UNLEARN_TAILOR_SPEC, DoHighUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 22208:                                     //Nasmara Moonsong
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_MOONCLOTH, GOSSIP_SENDER_CHECK, action, BOX_UNLEARN_TAILOR_SPEC, DoHighUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
            case 22212:                                     //Andrion Darkspinner
                player->ADD_GOSSIP_ITEM_EXTENDED( 0, GOSSIP_UNLEARN_SHADOWEAVE, GOSSIP_SENDER_CHECK, action,BOX_UNLEARN_TAILOR_SPEC, DoHighUnlearnCost(player),false);
                                                            //unknown textID ()
                player->SEND_GOSSIP_MENU(_Creature->GetNpcTextId(), _Creature->GetGUID());
                break;
        }
    }
}

bool GossipSelect_npc_prof_tailor(Player *player, Creature *_Creature, uint32 sender, uint32 action )
{
    switch(sender)
    {
        case GOSSIP_SENDER_MAIN:    SendActionMenu_npc_prof_tailor(player, _Creature, action); break;
        case GOSSIP_SENDER_LEARN:   SendConfirmLearn_npc_prof_tailor(player, _Creature, action); break;
        case GOSSIP_SENDER_UNLEARN: SendConfirmUnlearn_npc_prof_tailor(player, _Creature, action); break;
        case GOSSIP_SENDER_CHECK:   SendActionMenu_npc_prof_tailor(player, _Creature, action); break;
    }
    return true;
}

/*###
# start menues for GO (engineering and leatherworking)
###*/

bool HasLeatherSpec(Player* player)
{
    return (player->HasSpell(S_ELEMENTAL) || player->HasSpell(S_DRAGON) || player->HasSpell(S_TRIBAL));
}

bool HasEngineerSpec(Player* player)
{
    return (player->HasSpell(S_GNOMISH) || player->HasSpell(S_GOBLIN));
}

bool GossipHello_go_soothsaying_for_dummies(Player *player, GameObject* go)
{
    if (player->HasSkill(SKILL_LEATHERWORKING) && player->GetBaseSkillValue(SKILL_LEATHERWORKING) >= 225 && player->getLevel() > 39)
    {
        if (!HasLeatherSpec(player))
        {
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_DRAGON, GOSSIP_SENDER_CHECK, GOSSIP_ACTION_INFO_DEF+1);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_ELEMENTAL, GOSSIP_SENDER_CHECK, GOSSIP_ACTION_INFO_DEF+2);
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_TRIBAL, GOSSIP_SENDER_CHECK, GOSSIP_ACTION_INFO_DEF+3);
            player->SEND_GOSSIP_MENU(8326, go->GetGUID());
            return true;
        }
    }

    if (player->HasSkill(SKILL_ENGINERING) && player->GetBaseSkillValue(SKILL_ENGINERING) >= 200 && player->getLevel() > 39)
    {
        if (player->GetQuestRewardStatus(3643) || player->GetQuestRewardStatus(3641) || player->GetQuestRewardStatus(3639))
        {
            if (!HasEngineerSpec(player))
            {
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_GNOMISH, GOSSIP_SENDER_CHECK, GOSSIP_ACTION_INFO_DEF+4);
                player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_LEARN_GOBLIN, GOSSIP_SENDER_CHECK, GOSSIP_ACTION_INFO_DEF+5);
                player->SEND_GOSSIP_MENU(30000, go->GetGUID());
                return true;
            }
            if (player->HasSpell(S_GNOMISH))
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_GNOMISH, GOSSIP_SENDER_CHECK, GOSSIP_ACTION_INFO_DEF+6, BOX_UNLEARN_GNOMISH_SPEC, DoHighUnlearnCost(player), false);
            if (player->HasSpell(S_GOBLIN))
                player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, GOSSIP_UNLEARN_GOBLIN, GOSSIP_SENDER_CHECK, GOSSIP_ACTION_INFO_DEF+7, BOX_UNLEARN_GNOMISH_SPEC, DoHighUnlearnCost(player), false);
        }
    }
    player->SEND_GOSSIP_MENU(30000, go->GetGUID());
    return true;
}

void SendActionMenu_go_soothsaying_for_dummies(Player *player, GameObject* go, uint32 action)
{
    switch(action)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            if(!player->HasSpell(S_DRAGON))
                player->CastSpell(player, S_LEARN_DRAGON, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            if (!player->HasSpell(S_ELEMENTAL))
                player->CastSpell(player, S_LEARN_ELEMENTAL, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+3:
            if (!player->HasSpell(S_TRIBAL))
                player->CastSpell(player, S_LEARN_TRIBAL, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+4:
            if (!player->HasSpell(S_GNOMISH))
                player->CastSpell(player, S_LEARN_GNOMISH, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+5:
            if (!player->HasSpell(S_GOBLIN))
                player->CastSpell(player, S_LEARN_GOBLIN, true);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+6:
            if(EquippedOk(player,20219)) // Gnomish Engineer
            {
                if(player->GetMoney() >= DoLowUnlearnCost(player))
                {
                    player->removeSpell(20219);
                    ProfessionUnlearnSpells(player, 20219);
                    player->ModifyMoney(-DoLowUnlearnCost(player));
                }
                else
                    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, NULL, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
        case GOSSIP_ACTION_INFO_DEF+7:
            if(EquippedOk(player,20222)) // Gnomish Engineer
            {
                if(player->GetMoney() >= DoLowUnlearnCost(player))
                {
                    player->removeSpell(20222);
                    ProfessionUnlearnSpells(player, 20222);
                    player->ModifyMoney(-DoLowUnlearnCost(player));
                }
                else
                    player->SendBuyError(BUY_ERR_NOT_ENOUGHT_MONEY, NULL, 0, 0);
            }
            else
                player->SendEquipError(EQUIP_ERR_CANT_DO_RIGHT_NOW,NULL,NULL);
            player->CLOSE_GOSSIP_MENU();
            break;
    }
}

bool GossipSelect_go_soothsaying_for_dummies(Player *player, GameObject* go, uint32 sender, uint32 action)
{
    switch(sender)
    {
        case GOSSIP_SENDER_CHECK:    SendActionMenu_go_soothsaying_for_dummies(player, go, action); break;
    }
    return true;
}

void AddSC_npc_professions()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="npc_prof_alchemy";
    newscript->pGossipHello =  &GossipHello_npc_prof_alchemy;
    newscript->pGossipSelect = &GossipSelect_npc_prof_alchemy;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="npc_prof_blacksmith";
    newscript->pGossipHello =  &GossipHello_npc_prof_blacksmith;
    newscript->pGossipSelect = &GossipSelect_npc_prof_blacksmith;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="npc_prof_leather";
    newscript->pGossipHello =  &GossipHello_npc_prof_leather;
    newscript->pGossipSelect = &GossipSelect_npc_prof_leather;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="npc_prof_tailor";
    newscript->pGossipHello =  &GossipHello_npc_prof_tailor;
    newscript->pGossipSelect = &GossipSelect_npc_prof_tailor;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="go_soothsaying_for_dummies";
    newscript->pGOUse =  &GossipHello_go_soothsaying_for_dummies;
    newscript->pGossipSelectGO = &GossipSelect_go_soothsaying_for_dummies;
    newscript->RegisterSelf();
}

