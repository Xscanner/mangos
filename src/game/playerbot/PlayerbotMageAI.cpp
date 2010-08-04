
#include "PlayerbotMageAI.h"

class PlayerbotAI;

PlayerbotMageAI::PlayerbotMageAI(Player* const master, Player* const bot, PlayerbotAI* const ai): PlayerbotClassAI(master, bot, ai)
{
    ARCANE_MISSILES         = ai->getMaxKnownRankSpellId(ARCANE_MISSILES_1);
    ARCANE_EXPLOSION        = ai->getMaxKnownRankSpellId(ARCANE_EXPLOSION_1);
    COUNTERSPELL            = ai->getMaxKnownRankSpellId(COUNTERSPELL_1);
    SLOW                    = ai->getMaxKnownRankSpellId(SLOW_1);
    ARCANE_BARRAGE          = ai->getMaxKnownRankSpellId(ARCANE_BARRAGE_1);
    ARCANE_BLAST            = ai->getMaxKnownRankSpellId(ARCANE_BLAST_1);
    ARCANE_POWER            = ai->getMaxKnownRankSpellId(ARCANE_POWER_1);
    DAMPEN_MAGIC            = ai->getMaxKnownRankSpellId(DAMPEN_MAGIC_1);
    AMPLIFY_MAGIC           = ai->getMaxKnownRankSpellId(AMPLIFY_MAGIC_1);
    MAGE_ARMOR              = ai->getMaxKnownRankSpellId(MAGE_ARMOR_1);
    MIRROR_IMAGE            = ai->getMaxKnownRankSpellId(MIRROR_IMAGE_1);
    ARCANE_INTELLECT        = ai->getMaxKnownRankSpellId(ARCANE_INTELLECT_1);
    ARCANE_BRILLIANCE       = ai->getMaxKnownRankSpellId(ARCANE_BRILLIANCE_1);
    DALARAN_INTELLECT       = ai->getMaxKnownRankSpellId(DALARAN_INTELLECT_1);
    DALARAN_BRILLIANCE      = ai->getMaxKnownRankSpellId(DALARAN_BRILLIANCE_1);
    MANA_SHIELD             = ai->getMaxKnownRankSpellId(MANA_SHIELD_1);
    CONJURE_WATER           = ai->getMaxKnownRankSpellId(CONJURE_WATER_1);
    CONJURE_FOOD            = ai->getMaxKnownRankSpellId(CONJURE_FOOD_1);
    FIREBALL                = ai->getMaxKnownRankSpellId(FIREBALL_1);
    FIRE_BLAST              = ai->getMaxKnownRankSpellId(FIRE_BLAST_1);
    FLAMESTRIKE             = ai->getMaxKnownRankSpellId(FLAMESTRIKE_1);
    SCORCH                  = ai->getMaxKnownRankSpellId(SCORCH_1);
    PYROBLAST               = ai->getMaxKnownRankSpellId(PYROBLAST_1);
    BLAST_WAVE              = ai->getMaxKnownRankSpellId(BLAST_WAVE_1);
    COMBUSTION              = ai->getMaxKnownRankSpellId(COMBUSTION_1);
    DRAGONS_BREATH          = ai->getMaxKnownRankSpellId(DRAGONS_BREATH_1);
    LIVING_BOMB             = ai->getMaxKnownRankSpellId(LIVING_BOMB_1);
    FROSTFIRE_BOLT          = ai->getMaxKnownRankSpellId(FROSTFIRE_BOLT_1);
    FIRE_WARD               = ai->getMaxKnownRankSpellId(FIRE_WARD_1);
    MOLTEN_ARMOR            = ai->getMaxKnownRankSpellId(MOLTEN_ARMOR_1);
    ICY_VEINS               = ai->getMaxKnownRankSpellId(ICY_VEINS_1);
    DEEP_FREEZE             = ai->getMaxKnownRankSpellId(DEEP_FREEZE_1);
    FROSTBOLT               = ai->getMaxKnownRankSpellId(FROSTBOLT_1);
    FROST_NOVA              = ai->getMaxKnownRankSpellId(FROST_NOVA_1);
    BLIZZARD                = ai->getMaxKnownRankSpellId(BLIZZARD_1);
    CONE_OF_COLD            = ai->getMaxKnownRankSpellId(CONE_OF_COLD_1);
    ICE_BARRIER             = ai->getMaxKnownRankSpellId(ICE_BARRIER_1);
    SUMMON_WATER_ELEMENTAL  = ai->getMaxKnownRankSpellId(SUMMON_WATER_ELEMENTAL_1);
    FROST_WARD              = ai->getMaxKnownRankSpellId(FROST_WARD_1);
    ICE_LANCE               = ai->getMaxKnownRankSpellId(ICE_LANCE_1);
    FROST_ARMOR             = ai->getMaxKnownRankSpellId(FROST_ARMOR_1);
    ICE_ARMOR               = ai->getMaxKnownRankSpellId(ICE_ARMOR_1);
    ICE_BLOCK               = ai->getMaxKnownRankSpellId(ICE_BLOCK_1);
    COLD_SNAP               = ai->getMaxKnownRankSpellId(COLD_SNAP_1);

    RECENTLY_BANDAGED       = 11196; // first aid check

    // racial
    ARCANE_TORRENT          = ai->getSpellId("arcane torrent"); // blood elf
    GIFT_OF_THE_NAARU       = ai->getSpellId("gift of the naaru"); // draenei
    ESCAPE_ARTIST           = ai->getSpellId("escape artist"); // gnome
    EVERY_MAN_FOR_HIMSELF   = ai->getSpellId("every man for himself"); // human
    BERSERKING              = ai->getSpellId("berserking"); // troll
    WILL_OF_THE_FORSAKEN    = ai->getSpellId("will of the forsaken"); // undead
}

PlayerbotMageAI::~PlayerbotMageAI() {}

void PlayerbotMageAI::DoNextCombatManeuver(Unit *pTarget)
{
    PlayerbotAI* ai = GetAI();
    if (!ai)
        return;

    switch (ai->GetScenarioType())
    {
        case PlayerbotAI::SCENARIO_DUEL:
            if (FIREBALL > 0)
                ai->CastSpell(FIREBALL);
            return;
    }

    // ------- Non Duel combat ----------

	//ai->SetMovementOrder( PlayerbotAI::MOVEMENT_FOLLOW, GetMaster() ); // dont want to melee mob

    // Damage Spells (primitive example)
    ai->SetInFront( pTarget );
    Player *m_bot = GetPlayerBot();
	Unit* pVictim = pTarget->getVictim();
	float dist = m_bot->GetDistance( pTarget );

    switch (SpellSequence)
    {
        case SPELL_FROST:
            if (ICY_VEINS > 0 && !m_bot->HasAura(ICY_VEINS, EFFECT_INDEX_0) && LastSpellFrost < 1 && ai->GetManaPercent() >= 3)
            {
                ai->CastSpell(ICY_VEINS, *m_bot);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
            else if (FROSTBOLT > 0 && LastSpellFrost < 2 && !pTarget->HasAura(FROSTBOLT, EFFECT_INDEX_0) && ai->GetManaPercent() >= 16)
            {
                ai->CastSpell(FROSTBOLT, *pTarget);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
			else if (FROST_WARD > 0 && LastSpellFrost < 3 && !m_bot->HasAura(FROST_WARD, EFFECT_INDEX_0) && ai->GetManaPercent() >= 19)
            {
                ai->CastSpell(FROST_WARD, *m_bot);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
            else if (FROST_NOVA > 0 && LastSpellFrost < 4 && dist <= ATTACK_DISTANCE && !pTarget->HasAura(FROST_NOVA, EFFECT_INDEX_0) && ai->GetManaPercent() >= 10)
            {
                ai->CastSpell(FROST_NOVA, *pTarget);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
			else if (ICE_LANCE > 0 && LastSpellFrost < 5 && ai->GetManaPercent() >= 7)
            {
                ai->CastSpell(ICE_LANCE, *pTarget);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
            else if (BLIZZARD > 0 && LastSpellFrost < 6 && ai->GetAttackerCount()>=5 && ai->GetManaPercent() >= 89)
            {
                ai->CastSpell(BLIZZARD, *pTarget);
				ai->SetIgnoreUpdateTime(8);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
            else if (CONE_OF_COLD > 0 && LastSpellFrost < 7 && dist <= ATTACK_DISTANCE && !pTarget->HasAura(CONE_OF_COLD, EFFECT_INDEX_0) && ai->GetManaPercent() >= 35)
            {
                ai->CastSpell(CONE_OF_COLD, *pTarget);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
			else if (DEEP_FREEZE > 0 && LastSpellFrost < 8 && pTarget->HasAura(AURA_STATE_FROZEN, EFFECT_INDEX_0) && !pTarget->HasAura(DEEP_FREEZE, EFFECT_INDEX_0) && ai->GetManaPercent() >= 9)
            {
                ai->CastSpell(DEEP_FREEZE, *pTarget);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
            else if (ICE_BARRIER > 0 && LastSpellFrost < 9 && pVictim == m_bot && !m_bot->HasAura(ICE_BARRIER, EFFECT_INDEX_0) && ai->GetHealthPercent() < 50 && ai->GetManaPercent() >= 30)
            {
                ai->CastSpell(ICE_BARRIER, *m_bot);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
            else if (SUMMON_WATER_ELEMENTAL > 0 && LastSpellFrost < 10 && ai->GetManaPercent() >= 16)
            {
                ai->CastSpell(SUMMON_WATER_ELEMENTAL);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
			else if (ICE_BLOCK > 0 && LastSpellFrost < 11 && pVictim == m_bot && !m_bot->HasAura(ICE_BLOCK, EFFECT_INDEX_0) && ai->GetHealthPercent() < 30)
            {
                ai->CastSpell(ICE_BLOCK, *m_bot);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
			else if (COLD_SNAP > 0 && LastSpellFrost < 12)
            {
                ai->CastSpell(COLD_SNAP, *m_bot);
                SpellSequence = SPELL_FIRE;
                LastSpellFrost = LastSpellFrost +1;
                break;
            }
            LastSpellFrost = 0;
            //SpellSequence = SPELL_FIRE;
            //break;

        case SPELL_FIRE:
			if (FIRE_WARD > 0 && !m_bot->HasAura(FIRE_WARD, EFFECT_INDEX_0) && LastSpellFire < 1 && ai->GetManaPercent() >= 3)
            {
                ai->CastSpell(FIRE_WARD, *m_bot);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
			else if (COMBUSTION > 0 && !m_bot->HasAura(COMBUSTION, EFFECT_INDEX_0) && LastSpellFire < 2)
            {
                ai->CastSpell(COMBUSTION, *m_bot);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (FIREBALL > 0 && LastSpellFire < 3 && ai->GetManaPercent() >= 23)
            {
                ai->CastSpell(FIREBALL, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (FIRE_BLAST > 0 && LastSpellFire < 4 && ai->GetManaPercent() >= 25)
            {
                ai->CastSpell(FIRE_BLAST, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (FLAMESTRIKE > 0 && LastSpellFire < 5 && ai->GetManaPercent() >= 35)
            {
                ai->CastSpell(FLAMESTRIKE, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (SCORCH > 0 && LastSpellFire < 6 && ai->GetManaPercent() >= 10)
            {
                ai->CastSpell(SCORCH, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (PYROBLAST > 0 && LastSpellFire < 7 && !pTarget->HasAura(PYROBLAST, EFFECT_INDEX_0) && ai->GetManaPercent() >= 27)
            {
                ai->CastSpell(PYROBLAST, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (BLAST_WAVE > 0 && LastSpellFire < 8 && ai->GetAttackerCount()>=3 && dist <= ATTACK_DISTANCE && ai->GetManaPercent() >= 34)
            {
                ai->CastSpell(BLAST_WAVE, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (DRAGONS_BREATH > 0 && LastSpellFire < 9 && dist <= ATTACK_DISTANCE && ai->GetManaPercent() >= 37)
            {
                ai->CastSpell(DRAGONS_BREATH, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (LIVING_BOMB > 0 && LastSpellFire < 10 && !pTarget->HasAura(LIVING_BOMB, EFFECT_INDEX_0) && ai->GetManaPercent() >= 27)
            {
                ai->CastSpell(LIVING_BOMB, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            else if (FROSTFIRE_BOLT > 0 && LastSpellFire < 11 && !pTarget->HasAura(FROSTFIRE_BOLT, EFFECT_INDEX_0) && ai->GetManaPercent() >= 14)
            {
                ai->CastSpell(FROSTFIRE_BOLT, *pTarget);
                SpellSequence = SPELL_ARCANE;
                LastSpellFire = LastSpellFire +1;
                break;
            }
            LastSpellFire = 0;
            //SpellSequence = SPELL_ARCANE;
            //break;

        case SPELL_ARCANE:
            if (ARCANE_POWER > 0 && LastSpellArcane < 1 && ai->GetManaPercent() >= 37)
            {
                ai->CastSpell(ARCANE_POWER, *pTarget);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
			else if (ARCANE_MISSILES > 0 && LastSpellArcane < 2 && ai->GetManaPercent() >= 37)
            {
                ai->CastSpell(ARCANE_MISSILES, *pTarget);
				ai->SetIgnoreUpdateTime(3);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
            else if (ARCANE_EXPLOSION > 0 && LastSpellArcane < 3 && ai->GetAttackerCount()>=3 && dist <= ATTACK_DISTANCE && ai->GetManaPercent() >= 27)
            {
                ai->CastSpell(ARCANE_EXPLOSION, *pTarget);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
            else if (COUNTERSPELL > 0 && pTarget->IsNonMeleeSpellCasted(true) && LastSpellArcane < 4 && ai->GetManaPercent() >= 9)
            {
                ai->CastSpell(COUNTERSPELL, *pTarget);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
            else if (SLOW > 0 && LastSpellArcane < 5 && !pTarget->HasAura(SLOW, EFFECT_INDEX_0) && ai->GetManaPercent() >= 12)
            {
                ai->CastSpell(SLOW, *pTarget);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
            else if (ARCANE_BARRAGE > 0 && LastSpellArcane < 6 && ai->GetManaPercent() >= 27)
            {
                ai->CastSpell(ARCANE_BARRAGE, *pTarget);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
            else if (ARCANE_BLAST > 0 && LastSpellArcane < 7 && ai->GetManaPercent() >= 8)
            {
                ai->CastSpell(ARCANE_BLAST, *pTarget);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
            else if (MIRROR_IMAGE > 0 && LastSpellArcane < 8 && ai->GetManaPercent() >= 10)
            {
                ai->CastSpell(MIRROR_IMAGE);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
			else if (MANA_SHIELD > 0 && LastSpellArcane < 9 && ai->GetHealthPercent() < 70 && pVictim == m_bot && !m_bot->HasAura(MANA_SHIELD, EFFECT_INDEX_0) && ai->GetManaPercent() >= 8)
            {
                ai->CastSpell(MANA_SHIELD, *m_bot);
                SpellSequence = SPELL_FROST;
                LastSpellArcane = LastSpellArcane +1;
                break;
            }
            else
            {
                LastSpellArcane = 0;
                SpellSequence = SPELL_FROST;
            }
    }
} // end DoNextCombatManeuver

void PlayerbotMageAI::DoNonCombatActions()
{
    Player * m_bot = GetPlayerBot();
    if (!m_bot)
        return;

    SpellSequence = SPELL_FROST;
	PlayerbotAI* ai = GetAI();

    // buff master
	if (DALARAN_BRILLIANCE > 0)
        (!GetMaster()->HasAura(DALARAN_BRILLIANCE, EFFECT_INDEX_0) && ai->GetManaPercent() >= 81 && ai->CastSpell (DALARAN_BRILLIANCE, *GetMaster()));
	else if (ARCANE_BRILLIANCE > 0)
        (!GetMaster()->HasAura(ARCANE_BRILLIANCE, EFFECT_INDEX_0) && !GetMaster()->HasAura(DALARAN_BRILLIANCE, EFFECT_INDEX_0) && ai->GetManaPercent() >= 97 && ai->CastSpell (ARCANE_BRILLIANCE, *GetMaster()));

    // buff myself
    if (DALARAN_INTELLECT > 0)
        (!m_bot->HasAura(DALARAN_INTELLECT, EFFECT_INDEX_0) && !m_bot->HasAura(DALARAN_BRILLIANCE, EFFECT_INDEX_0) && !m_bot->HasAura(ARCANE_BRILLIANCE, EFFECT_INDEX_0) && ai->GetManaPercent() >= 31 && ai->CastSpell (DALARAN_INTELLECT, *m_bot));
    else if (ARCANE_INTELLECT > 0)
        (!m_bot->HasAura(ARCANE_INTELLECT, EFFECT_INDEX_0) && !m_bot->HasAura(DALARAN_BRILLIANCE, EFFECT_INDEX_0) && !m_bot->HasAura(ARCANE_BRILLIANCE, EFFECT_INDEX_0) && !m_bot->HasAura(DALARAN_INTELLECT, EFFECT_INDEX_0) && ai->GetManaPercent() >= 37 && ai->CastSpell (ARCANE_INTELLECT, *m_bot));

    if (MOLTEN_ARMOR > 0)
        (!m_bot->HasAura(MOLTEN_ARMOR, EFFECT_INDEX_0) && !m_bot->HasAura(MAGE_ARMOR, EFFECT_INDEX_0) && ai->GetManaPercent() >= 31 && ai->CastSpell (MOLTEN_ARMOR, *m_bot));
	else if (MAGE_ARMOR > 0)
        (!m_bot->HasAura(MAGE_ARMOR, EFFECT_INDEX_0) && !m_bot->HasAura(MOLTEN_ARMOR, EFFECT_INDEX_0) && ai->GetManaPercent() >= 31 && ai->CastSpell (MAGE_ARMOR, *m_bot));
	else if (ICE_ARMOR > 0)
        (!m_bot->HasAura(ICE_ARMOR, EFFECT_INDEX_0) && !m_bot->HasAura(MOLTEN_ARMOR, EFFECT_INDEX_0) && !m_bot->HasAura(MAGE_ARMOR, EFFECT_INDEX_0) && ai->GetManaPercent() >= 34 && ai->CastSpell (ICE_ARMOR, *m_bot));
    else if (FROST_ARMOR > 0)
        (!m_bot->HasAura(FROST_ARMOR, EFFECT_INDEX_0) && !m_bot->HasAura(MOLTEN_ARMOR, EFFECT_INDEX_0) && !m_bot->HasAura(MAGE_ARMOR, EFFECT_INDEX_0) && !m_bot->HasAura(ICE_ARMOR, EFFECT_INDEX_0) && ai->GetManaPercent() >= 34 && ai->CastSpell (FROST_ARMOR, *m_bot));

	// buff master's group
    if (GetMaster()->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = GetMaster()->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *tPlayer = sObjectMgr.GetPlayer(uint64 (itr->guid));
            if( !tPlayer || !tPlayer->isAlive() )
                continue;
			// buff
			(!tPlayer->HasAura(ARCANE_INTELLECT, EFFECT_INDEX_0) && !tPlayer->HasAura(DALARAN_BRILLIANCE, EFFECT_INDEX_0) && !tPlayer->HasAura(ARCANE_BRILLIANCE, EFFECT_INDEX_0) && !tPlayer->HasAura(DALARAN_INTELLECT, EFFECT_INDEX_0) && ai->GetManaPercent() >= 37 && ai->CastSpell (ARCANE_INTELLECT, *tPlayer));
			(!tPlayer->HasAura(DALARAN_INTELLECT, EFFECT_INDEX_0) && !tPlayer->HasAura(DALARAN_BRILLIANCE, EFFECT_INDEX_0) && !tPlayer->HasAura(ARCANE_BRILLIANCE, EFFECT_INDEX_0) && ai->GetManaPercent() >= 31 && ai->CastSpell (DALARAN_INTELLECT, *tPlayer));
			(!tPlayer->HasAura(DAMPEN_MAGIC, EFFECT_INDEX_0) && !tPlayer->HasAura(AMPLIFY_MAGIC, EFFECT_INDEX_0) && ai->GetManaPercent() >= 32 && ai->CastSpell (DAMPEN_MAGIC, *tPlayer));
			(!tPlayer->HasAura(AMPLIFY_MAGIC, EFFECT_INDEX_0) && !tPlayer->HasAura(DAMPEN_MAGIC, EFFECT_INDEX_0) && ai->GetManaPercent() >= 32 && ai->CastSpell (AMPLIFY_MAGIC, *tPlayer));
        }
    }

    // conjure food & water
    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    Item* pItem = ai->FindDrink();
	Item* fItem = ai->FindBandage();

    if (pItem == NULL && CONJURE_WATER && ai->GetBaseManaPercent() >= 48)
    {
        ai->TellMaster("I'm conjuring some water.");
        ai->CastSpell(CONJURE_WATER, *m_bot);
		ai->SetIgnoreUpdateTime(3);
        return;
    }
    else if (pItem != NULL && ai->GetManaPercent() < 30)
    {
        ai->TellMaster("I could use a drink.");
        ai->UseItem(*pItem);
        ai->SetIgnoreUpdateTime(30);
        return;
    }

    pItem = ai->FindFood();

    if (pItem == NULL && CONJURE_FOOD && ai->GetBaseManaPercent() >= 48)
    {
        ai->TellMaster("I'm conjuring some food.");
        ai->CastSpell(CONJURE_FOOD, *m_bot);
		ai->SetIgnoreUpdateTime(3);
    }

    // hp check
    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);

    pItem = ai->FindFood();

    if (pItem != NULL && ai->GetHealthPercent() < 30)
    {
        ai->TellMaster("I could use some food.");
        ai->UseItem(*pItem);
        ai->SetIgnoreUpdateTime(30);
        return;
    }
	else if (pItem == NULL && fItem != NULL && !m_bot->HasAura(RECENTLY_BANDAGED, EFFECT_INDEX_0) && ai->GetHealthPercent() < 70)
    {
        ai->TellMaster("I could use first aid.");
        ai->UseItem(*fItem);
        ai->SetIgnoreUpdateTime(8);
        return;
    }

} // end DoNonCombatActions

void PlayerbotMageAI::BuffPlayer(Player* target)
{
    GetAI()->CastSpell(ARCANE_INTELLECT, *target);
}
