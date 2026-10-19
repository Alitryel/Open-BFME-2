// BuildAssistant::rva0039321C
// partial score=0.95 date=2026-10-19
// Body for Code/GameEngine/Source/Common/System/BuildAssistant.cpp (append; home flags + /I.).
// Also: replace BuildAssistant 'virtual void slot21();' with the rva0039321C declaration (vslot +0x54),
// split GlobalData m_padA74 into m_padA74[0xA94-0xA74]; Int m_maxLineBuildObjects; m_padA98[0xB94-0xA98],
// and insert these TU classes before class BuildAssistant:
/* --- pre.h ---
class Rva003920F7Src;

class Rva003920F7
{
public:
	void rva003920F7(UnsignedInt index, const Rva003920F7Src *src);
};

class Rva0039205C : public Rva003920F7
{
public:
	void rva00392129(UnsignedInt index, Real angle);
	void rva0039215F(UnsignedInt index, const AsciiString &name);
	void rva00392196(UnsignedInt index, Int status);
	void rva00392CAC();

	Int m_count;				// +0x00
	Int m_cost;				// +0x04
	unsigned char m_pad08[4];
	Bool m_0C;				// +0x0C
	Bool m_0D;				// +0x0D
	Int m_status;				// +0x10
};

class Rva00392FE0List
{
public:
	virtual void v00();
	virtual const ThingTemplate *getEntry(Int index);	// +0x04
	virtual void v08();
	virtual const ThingTemplate *getDefault();		// +0x0C
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
	virtual void v20(); virtual void v24(); virtual void v28();
	virtual Real getRange();				// +0x2C
};

class Rva00293330
{
public:
	void *rva00293330(UnsignedInt key);
};

Real normalizeAngle(Real angle);
--- end pre.h --- */
/* BuildAssistant decl: virtual Bool rva0039321C(Rva0039205C *info, Object *first, Object *second, UnsignedInt key, Bool recursed);	// +0x54 */

//-------------------------------------------------------------------------------------------------
// Lay a line of segments from first toward second (BFME wall line). Each
// segment advances by its template's footprint; an existing equivalent
// segment in the way restarts the line from the other end once.
//-------------------------------------------------------------------------------------------------
Bool BuildAssistant::rva0039321C(Rva0039205C *info, Object *first, Object *second, UnsignedInt key, Bool recursed)
{
	if (first == NULL || second == NULL)
		return false;

	Object *from = first;
	Object *to = second;
	if (first->get7C() > second->get7C() && !recursed)
	{
		from = first;
		to = second;
	}

	if (to->rva0028BD17() == NULL)
		return false;

	Rva00392FE0List *list = (Rva00392FE0List *)((Rva00293330 *)from)->rva00293330(key);
	if (list == NULL)
		return false;

	const ThingTemplate *def = list->getDefault();
	if (def == NULL)
		return false;

	Coord3D pos;
	Coord3D dir;
	Real angle;
	Real dist;
	Real range;
	Int money;
	Int i;
	Real total;
	dir.x = from->getPosition()->x;
	dir.y = from->getPosition()->y;
	dir.z = from->getPosition()->z;
	{
	Coord3D delta;
	delta.x = to->getPosition()->x;
	delta.y = to->getPosition()->y;
	delta.x -= dir.x;
	delta.y -= dir.y;
	delta.z = 0.0f;

	{
	Coord2D v;
	v.x = delta.x;
	v.y = delta.y;
	angle = normalizeAngle(v.toAngle() + PI / 2.0f);
	}

	pos.x = dir.x;
	pos.y = dir.y;
	pos.z = dir.z;

	dir.x = delta.x;
	dir.y = delta.y;
	dir.z = 0.0f;
	dir.normalize();

	dist = 0.0f;
	range = list->getRange();
	dist += range;
	pos.x += dir.x * range;
	pos.y += dir.y * range;

	money = from->getControllingPlayer()->getMoney()->countMoney();
	i = 0;
	total = delta.length();
	}
	while (dist < total)
	{
		if (i >= TheWritableGlobalData->m_maxLineBuildObjects - 1)
			break;

		const ThingTemplate *tmpl = list->getEntry(i);
		if (tmpl == NULL)
			tmpl = from->getTemplate();

		Real size = tmpl->getTemplateGeometryInfo().getBoxMinorRadius() - 1.0f;
		Coord3D step;
		step.x = dir.x * size;
		step.y = dir.y * size;
		step.z = 0.0f;
		pos.x += step.x;
		pos.y += step.y;
		pos.z = TheTerrainLogic->getGroundHeight(pos.x, pos.y);

		Bool valid = false;
		Object *obj = ThePartitionManager->rva00625340(&pos, size * 0.25f, 1);
		if (obj)
		{
			if (obj->isEffectivelyDead())
			{
				if (obj->getTemplate()->isEquivalentTo(tmpl))
					valid = true;
			}
			else
			{
				Coord3D offset;
				offset.x = obj->getPosition()->x;
				offset.y = obj->getPosition()->y;
				offset.z = obj->getPosition()->z;
				offset.x -= pos.x;
				offset.y -= pos.y;
				offset.z -= pos.z;
				Real objSize = obj->getGeometryInfo().getBoxMinorRadius();
				if (offset.length() > 1.1f && size * 1.1f >= objSize
					&& obj->getTemplate()->isEquivalentTo(tmpl))
				{
					if (recursed)
						return false;
					info->rva00392CAC();
					return rva0039321C(info, to, from, key, true);
				}
				pos.x += step.x;
				pos.y += step.y;
				dist += size * 2.0f;
				continue;
			}
		}

		info->rva003920F7(i, (const Rva003920F7Src *)&pos);
		info->rva00392129(i, angle);
		info->rva0039215F(i, def->getName());
		info->rva00392196(i, 0);
		info->m_count = i + 1;
		info->m_0D = false;
		info->m_0C = false;
		info->m_status = 10;
		if (valid)
			info->rva00392196(i, 10);

		pos.x += step.x;
		pos.y += step.y;
		info->m_cost += tmpl->rva0033A69A(from->getControllingPlayer(), (Int)from, -1);
		if (info->m_cost > money)
		{
			info->m_status = 7;
			info->rva00392196(i, 7);
		}
		dist += size * 2.0f;
		i++;
		if (i >= TheWritableGlobalData->m_maxLineBuildObjects)
			break;
	}
	return true;
}
