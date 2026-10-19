Paired current-provider legacy link_check: 0 -> 131 matched bytes (+131 B).
The two providers are dx8renderer.cpp and VertexSplitTablePeekShader.cpp.
The former still has independent blockers; the shader provider newly links.
Census c2c5ac8c27, self-strict reusable receipts only, no closed-strict claim.

The donor split-table shader helper in dx8renderer.cpp handles an out-of-range
polygon through GapFiller. Native 1443D0 instead uses the established default
shader value; the rowed owner retains that target-specific body. A declaration
now binds calls to the rowed provider. This is a target behavior correction,
not a new recovered identity.

Removing the donor caller stopped emitting rowed GapFillerClass::Get_Shader_Array
(5FD05E, 11 B). Its address is now retained by the unit's existing source-only
accessor anchor. No pins, aliases, baselines or shared headers changed.

Acceptance: 84/84 byte-exact rows across two units using strict reusable
receipts; 5/5 EH records EXACT; frozen-definition check passes; data_check
--enforce has one existing baselined finding and none outside the baseline;
converged-data check has zero second names or unjudged rows.
