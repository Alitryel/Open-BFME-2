import trials,itertools,concurrent.futures,json
base=(trials.scratch/'life-s0-n1-p0-f0-a0.cpp').read_text()
specs=[]
for outer,inter,local,const in itertools.product([0,1],repeat=4):
 s=base
 if const:
  s=s.replace('  bool __is_negative;\n','').replace('  __is_negative =','  const bool __is_negative =')
 def arm(obj,rev):
  return '('+('!__is_negative' if rev else '__is_negative')+' ? '+obj+('.positive_sign()' if rev else '.negative_sign()')+' : '+obj+('.negative_sign()' if rev else '.positive_sign()')+')'
 i=arm('__punct_intl',inter);n=arm('__punct',local)
 expr=('!__intl ? '+n+' : '+i) if outer else ('__intl ? '+i+' : '+n)
 begin=s.index('  string_type __sign ='); end=s.index('#pragma inline_depth(255)',begin)
 s=s[:begin]+'  string_type __sign = '+expr+';\n'+s[end:]
 specs.append((f'sign-o{outer}-i{inter}-l{local}-c{const}',s))
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as p:r=list(p.map(trials.run,specs))
(trials.scratch/'sign-order.json').write_text(json.dumps(r,indent=2)+'\n')
