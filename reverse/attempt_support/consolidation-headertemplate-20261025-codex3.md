# Consolidation handoff: HeaderTemplate.cpp

Dry run accepted no donors (11 rows; two donors are protected). The in-prefix
`HeaderTemplateManagerGetFontFromTemplate.cpp` and `HeaderTemplateParse.cpp`
both failed with the exact diagnostic `string_base.h(165) : error C2953:
'StringBase' : template class has already been defined`; the seed and other
donors reported the same duplicate `StringBase` declaration. Sol prerequisite;
no source or ledger changes were made.
