import trials,itertools,concurrent.futures,json
base=trials.bank
specs=[]
for mode,opaque,li in itertools.product(['goto','goto-result','if-wrap','goto-deadline'],[False,True],[False,True]):
 s=base
 # Separate the currency/sign lifetimes from the shared locale/grouping tail.
 if not opaque:s=s.replace('template <> _String_base<wchar_t, allocator<wchar_t> >::~_String_base();','')
 if li:s=s.replace('locale::~locale()','inline locale::~locale()')
 start=s.index('#pragma inline_depth(0)\n  string_type __curr_sym')
 s=s[:start]+'  {\n'+s[start:]
 if mode in ('goto','goto-result','goto-deadline'):
  s=s.replace('    return __s;','    goto money_exit;')
  # Keep the success return inside its complete lifetime; only early exits jump.
  pos=s.rfind('  return __s;\n}')
  s=s[:pos]+s[pos:].replace('  return __s;\n}','  return __s;\n  }\nmoney_exit:\n  return __s;\n}',1)
  if mode=='goto-result':
   s=s.replace('  locale __loc =','  _MoneyOut __ret;\n  locale __loc =',1)
   s=s.replace('    goto money_exit;','    { __ret=__s; goto money_exit; }')
   s=s.replace('money_exit:\n  return __s;','money_exit:\n  return __ret;')
  if mode=='goto-deadline':
   s=s.replace('  return __s;\n  }\nmoney_exit:', '  }\nmoney_exit:')
 else:
  s=s.replace('  if (__digits.size() == 0) \n#pragma inline_depth(0)\n    return __s;\n#pragma inline_depth(255)','  if (__digits.size() != 0) {')
  s=s.replace('  if (__cp == __digits_first)\n#pragma inline_depth(1)\n    return __s;\n#pragma inline_depth(255)','  if (__cp != __digits_first) {')
  pos=s.rfind('  return __s;\n}')
  s=s[:pos]+s[pos:].replace('  return __s;\n}','  }\n  }\n  }\n  return __s;\n}',1)
 specs.append((f'cf-{mode}-op{int(opaque)}-li{int(li)}',s))
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as p:r=list(p.map(trials.run,specs))
(trials.scratch/'control.json').write_text(json.dumps(r,indent=2)+'\n')
