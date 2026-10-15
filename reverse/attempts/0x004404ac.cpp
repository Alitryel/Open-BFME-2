// ?rva004404AC@AptMpGameSetup@@QAEX_NH@Z
// partial score=0.9 date=2026-10-15
// cl: /O1 /G7 /arch:SSE /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// FRAGMENT: append to Code/GameEngine/Source/GameClient/GUI/MpGameSetupSlots.cpp (uses its class views; the home's
// cl line lacks /O, so scratch compiles need the region flags above).
// d3 seat4 rewrite from retail + WB 149E9C0: early return when the slot stays invalid, the combo
// lives to the end (dtor after the preview call), found=false inside the local-slot block,
// teamEnable=false stored before HideList, slot == v13() operand order. 526/526B, every
// instruction identical except this/slot register roles (ours this=EDI slot=ESI, retail
// this=ESI slot=EDI). Probe: dropping two slot pushes flips the roles, so slot outweighs
// this by about two refs; a local copy of slot made before the null check also flips them but
// hoists push edi/load above the call. 64-variant grid (param/copy, holder, hero/team locals,
// loop/found scope), nested-if forms, self/idx copies and flags /G6 /Ob1 /Op /SSE2 inert.
// Retail 0x004404AC, 526 bytes (ret 8): enables one slot's widgets by the
// enable flag and the slot's observer state, then, for the local slot,
// tells the +0x60 map preview whether a playable entry exists.
void AptMpGameSetup::rva004404AC(bool enable, int slot)
{
	GameInfo *game = (GameInfo *)m_game->rva0043DA65();
	if (!game)
		return;
	if (slot == -1 || slot >= 8)
		slot = game->v13();
	if (slot == -1 || slot >= 8)
		return;
	bool observer = game->getConstSlot(slot)->isObserver();
	MpGameSetupComboRef combo(m_colorCombo[slot]);
	if (combo.m_window)
	{
		if (observer)
			combo.rva00323736(true);
		combo.m_window->winEnable(enable && !observer);
	}
	if (m_handicap[slot])
		m_handicap[slot]->winEnable(enable && !observer);
	GameWindow *hero = m_hero[slot];
	if (hero)
	{
		if (m_rules.m_00 == 1)
			hero->winEnable(enable && !observer);
		else
		{
			hero->winEnable(false);
			if (Rva00322910(hero))
			{
				GadgetComboBoxSetSelectedPos(hero, 0, false);
				HandleHeroSelection(slot);
			}
		}
		UpdateHeroDisplay(slot);
	}
	if (m_playerTemplate[slot])
		m_playerTemplate[slot]->winEnable(enable);
	GameWindow **team = &m_team[slot];
	if (*team)
	{
		bool locked = m_rules.m_04 == 1;
		bool teamEnable;
		if (enable && !observer && !locked)
			teamEnable = true;
		else
		{
			teamEnable = false;
			GadgetComboBoxHideList(*team);
		}
		(*team)->winEnable(teamEnable);
	}
	if (slot == game->v13())
	{
		bool found = false;
		if (enable && game->getConstSlot(game->v13())->m_hasMap)
		{
			if (!observer)
				found = true;
			else if (game->v12())
			{
				for (int i = 0; i < 8; ++i)
				{
					if (game->getConstSlot(i) && game->getConstSlot(i)->isAI())
					{
						found = true;
						break;
					}
				}
			}
		}
		((AptMapPreview *)&m_60)->rva0057C597(found);
	}
}
