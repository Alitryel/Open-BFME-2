// cl: /MD
// ??0ChangeStanceGroupOrder@@QAE@PAVRva0036E346@@H@Z @0x00546AD0 31B evidence: stores vtable 0x0086A36C; base holder ctor rowed 0x00548A25; int at +0x18 from second arg; caller 0x00355A86 news int-sized; sibling default at 0x00546AEF in ChangeStanceGroupOrderCtor.cpp.
// Holder overload of ChangeStanceGroupOrder (naming via vtable).
class Rva0036E346;

class GroupOrder
{
public:
	GroupOrder(Rva0036E346 *holder);

protected:
	void *m_vtable; // +0
private:
	unsigned char m_pad04[0x18 - 4];
};

// The retail table at RVA 0x0086A36C: 14 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GChangeStanceGroupOrder@@UAEPAXI@Z")();
void __identifier("??1BfmeRadarMapPoint@@QAE@XZ")();
void __identifier("?getClassName@ChangeStanceGroupOrder@@UAEPBDXZ")();
void __identifier("?xfer@ChangeStanceGroupOrder@@UAEXPAVXfer@@@Z")();
void __identifier("?rva00546BED@ChangeStanceGroupOrder@@UAEXW4ObjectID@@@Z")();
void __identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?get_allocator@?$_List_base@PAVSuperweaponInfo@@V?$allocator@PAVSuperweaponInfo@@@_STL@@@_STL@@QBE?AV?$allocator@PAVSuperweaponInfo@@@2@XZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?Get_File_Handle@FileClass@@UAEPAXXZ")();
void __identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z")();
void __identifier("?getClassKey@ChangeStanceGroupOrder@@UAE?AW4NameKeyType@@XZ")();
void __identifier("?rva00546B34@ChangeStanceGroupOrder@@UAEPAV1@XZ")();
}
extern const void *const g_0086A36C[14] = {
	(const void *)&__identifier("??_GChangeStanceGroupOrder@@UAEPAXI@Z"), // slot 0 0x00546B75
	(const void *)&__identifier("??1BfmeRadarMapPoint@@QAE@XZ"), // slot 1 0x000B3FD0
	(const void *)&__identifier("?getClassName@ChangeStanceGroupOrder@@UAEPBDXZ"), // slot 2 0x00546BC7
	(const void *)&__identifier("?xfer@ChangeStanceGroupOrder@@UAEXPAVXfer@@@Z"), // slot 3 0x00546B91
	(const void *)&__identifier("?rva00546BED@ChangeStanceGroupOrder@@UAEXW4ObjectID@@@Z"), // slot 4 0x00546BED
	(const void *)&__identifier("?_bfme_ro_v50@RenderObjClass@@UAE_NH@Z"), // slot 5 0x005CB9FA
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 6 0x0047A69C
	(const void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"), // slot 7 0x0047A69C
	(const void *)&__identifier("?get_allocator@?$_List_base@PAVSuperweaponInfo@@V?$allocator@PAVSuperweaponInfo@@@_STL@@@_STL@@QBE?AV?$allocator@PAVSuperweaponInfo@@@2@XZ"), // slot 8 0x0021983A
	(const void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"), // slot 9 0x005CB9FF
	(const void *)&__identifier("?Get_File_Handle@FileClass@@UAEPAXXZ"), // slot 10 0x0036CC7A
	(const void *)&__identifier("?rva0050B5F1@Rva0050B5F1@@QAE_NHH@Z"), // slot 11 0x0050B5F1
	(const void *)&__identifier("?getClassKey@ChangeStanceGroupOrder@@UAE?AW4NameKeyType@@XZ"), // slot 12 0x00546B6B
	(const void *)&__identifier("?rva00546B34@ChangeStanceGroupOrder@@UAEPAV1@XZ"), // slot 13 0x00546B34
};

class ChangeStanceGroupOrder : public GroupOrder
{
public:
	ChangeStanceGroupOrder(Rva0036E346 *holder, int val);
private:
	int m_18;
};

ChangeStanceGroupOrder::ChangeStanceGroupOrder(Rva0036E346 *holder, int val)
	: GroupOrder(holder)
{
	m_18 = val;
	*(const void **)this = g_0086A36C;
}
