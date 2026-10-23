# 0x405E3D OldSchoolHelpBoxContentSource::createContent - session 2026-10-19 22:54-23:00 PT (hans-agent-oct5)
Bank: 3291 vs 3287 B, struct 2, mem 35, reg 3. Real diffs are all in the sciences size tests (+0xBA..+0x155).
Retail keeps the button in EAX and does the shared end reload into ECX (`mov ecx,[eax+0xa8]`). Its ==1 test is `and ecx,~3; cmp ecx,4`, and it reads sciences[0] through EAX with no reload.
Ours copies the button to ECX and keeps the byte-difference in EAX (`and al,0xfc`, 1 byte shorter), then reloads `mov eax,[esi+0xc]` for [0].
Probes: `.size()==1` at the else-if gives reg 3->1 but 3295 B / struct 3. Signed end-begin==1, front(), *begin() and `>=2`: inert or worse.
