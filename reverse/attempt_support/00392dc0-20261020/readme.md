# RVA 0x00392DC0: WorldBuilder structure lead, allocation still blocked

Result: blocked. The bank `reverse/attempts/0x00392dc0.cpp` (score 0.93) stays in place. Symbol `?rva00392DC0@BuildAssistant@@QAE_NPAVObject@@PBVThingTemplate@@PBUCoord3D@@PAVPlayer@@IPAPAV2@@Z`, 1116 bytes, native boundary 0x00392DC0..0x0039321C ending in `ret 0x18`. Input checkout 424004534feb5639dd4ce6c465de82a93003bbde, bank flags unchanged (`/O1 /G7 /arch:SSE /MD /EHsc`). Model claude-opus-5-5.

## New evidence: the WorldBuilder debug twin

`python tools/wb_show.py 0x00392DC0 --max-lines 1200` serves an unnamed WorldBuilder debug body at WB VA 0x00F96810 (1917 bytes, callgraph evidence, score 4.0). No earlier verdict cites it. Its callees map one to one onto this body's callees (tile getters 0x392CC5/CF9/D1D/D49/D71, the tile destructor 0x39205C, PartitionManager 0x625340, ThingTemplate::isEquivalentTo, Object::setBuilder 0x28AFE7, teleportTo, setStatus, Drawable::fadeIn, findObjectByID, Money::withdraw, 0x39BAD2). WB is a different build (its Object offsets differ: id +0x7C, body +0x25C, dead flag +0x445; its setStatus and model-condition calls use mask temporaries where retail calls 0x23DD69 and 0x1E431E directly), so it is a structural guide, not byte evidence. The facts it supplies, read from the literal debug code:

1. The refresh branch tests `old && old->isEffectivelyDead()` and then calls `old->getTemplate()->isEquivalentTo(tiles.rva00392CC5(i))` with `Thing::getTemplate` in the expression, not through a named local. WB calls it out of line (defined in Thing.h with a debug assert at line 92); retail inlines it to the +4 load.
2. The build branch is `if (made) { ... }`, pushes `made->getID()` through a reference temporary, and calls the slot 0x44 behaviour method as one nested expression, `behavior->s17(producer->s14() * i)`: debug pushes the product straight from `imul`.
3. The kind-of test is inside the condition, after the `behavior` and `producer` checks: `!made->getTemplate()->isKindOf(156)` (template +0x108 bit 156, so +0x11B mask 0x10 in retail).
4. The price is a named unsigned local, `price = tile->rva0033A69A(player, builder, -1)`, converted to float into the object.
5. After the loop, one behaviour variable is reused: parent's behaviour, then the builder's behaviour (WB local_5c), and in the second outer loop the created object's behaviour, then the builder's (WB local_6c).
6. The tile record constructor initialises count, array, flagC, flagD, status, cost, objectID in that order.

## Candidates built from that structure

Both are saved here as `.cpp.txt` and measured with `tools/align_diff.py` (fresh object each time):

| Source | Emitted | Structural | Memory (of which zero DIR32) | Register | Frame |
| --- | ---: | ---: | ---: | ---: | --- |
| existing bank | 1111 | 10 | 14 (9) | 6 | 0x70 |
| `wb_structure_mult_local.cpp.txt` (WB structure, multiplier in its own statement) | 1111 | 8 | 16 (9) | 6 | 0x70 |
| `wb_structure_nested_call.cpp.txt` (WB structure, nested call as WB has it) | 1120 | 9 | 32 (3) | 22 | 0x74 |

The multiplier-local candidate removes two structural regions (the in-condition template read now sits where retail has it) but adds two memory differences: the template temporary at +0x220 is ECX instead of EDX. Under the seat's rule that is not closer, so it is not banked. The nested-call candidate is the one WB supports; it reproduces retail's behaviour-vtable preload, but the vtable then has no callee-saved register and spills to a new stack slot, which grows the frame by four and shifts every local.

## The one remaining cause

Every remaining difference in both candidates comes from the construction index `i`. Retail keeps `i` in EDI only at the loop top and in the build branch before the body block, keeps its home in the dead `what` slot [ebp+0xC], uses that slot directly in the refresh tail (`push [ebp+0xC]` at +0x127) and the build tail (`imul eax,[ebp+0xC]` at +0x23B, `push [ebp+0xC]` at +0x2AF), and reloads it at the latch (`mov edi,[ebp+0xC]` at +0x2E3). That frees EDI for the old template (+0x12A) and the behaviour vtable (+0x234), and the unsigned price scratch then shares [ebp-0x18] with the insert result. Our compile keeps `i` in EDI everywhere except the body block, puts the old template in EBX (free there in retail too), and either spills the vtable (nested call) or loads it late into EDX (separate statement). The +0x380 EAX/ECX copy order for the second outer loop's object is independent of this and also remains.

The retail latch reload is rare: the byte pattern `mov r,[ebp+d]; inc r; ...; mov [ebp+d],r` occurs six times in game.dat. The three matched owners are NAT::generatePortNumbers 0x005A678E (index evicted by a scalar-replaced struct while ESI, EDI and EBX are all in use), Pathfinder 0x0052F2EC and W3DRadar::buildTerrainTexture 0x0004FAFF (outer index evicted inside inner loops; register freeness there was not checked). They are the nearest matched examples of the shape and worth reading before the next trial.

## Hypotheses tested this run (all measured, none closes it)

Raw logs and sources are in `build/w392/` of the seat (`<name>.cpp`, `<name>.align.txt`, `<name>.sbs.txt`).

- Control flow respellings are byte-identical to the bank: refresh branch ending in `continue`, `if (made) {}` instead of `continue`, one `&&` chain for the refresh test.
- Shared or moved declarations are byte-identical: one `Object *` for old and made, one behaviour variable across branches, index declared at function top (signed and unsigned), per-iteration index copy.
- Index representation is inert: address taken through an inline reference or pointer helper, index as a one-member struct field.
- Compile flags: `/EHs` and dropping `/G7` are identical; `/O2` is far worse.
- Inline `getTemplate()` accessor in the expression is identical to the named template local (both load the template before the getter call, as retail does); a direct field read in the expression moves the load after the call (worse).
- Operand order `i * producer->s14()` is identical to the nested call.
- Diagnostics only (not landable): up to eight extra uses of the old template never evict `i` (the template takes ESI and `old` moves to EBX); one to five dummy branches in the loop do not evict `i`; removing one index use is inert, removing two drops `i` entirely to memory and hands EBX to the zero constant, with no intermediate state like retail's; a volatile read of `i` in the multiplier is not retail's shape either.

## What the next attempt needs

A source-level reason for cl 7.1 to split `i` out of EDI in the refresh tail while EBX is free. Priority tuning of `i` alone cannot produce retail's shape (it jumps from fully enregistered to fully in memory). Leads not yet tested: controlled small trials of a loop with an if/else where one arm needs a callee-saved temporary across a call, to find what makes cl evict the loop index instead of taking a free register; and whether retail's zero constant (EBX at entry, rematerialised after the loop at +0x2F3) holds EBX across the loop body in retail's allocation. Start from `wb_structure_nested_call.cpp.txt`, which is the WB-faithful body; if the index allocation is fixed there, it is expected to remove the frame growth and most remaining differences.
