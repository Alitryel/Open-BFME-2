import trials,itertools,concurrent.futures,json
specs=[]
for scope,negative,pointers,frac,pattern in itertools.product([0,1],repeat=5):
 s=trials.bank if not scope else (trials.scratch/'cf-goto-op1-li1.cpp').read_text()
 if negative:
  s=s.replace('struct _MoneySignPolicy : random_access_iterator_tag { bool negative; };','struct _MoneySignPolicy : random_access_iterator_tag {};')
  s=s.replace('  _MoneySignPolicy __sign_policy;','  _MoneySignPolicy __sign_policy;\n  bool __is_negative;').replace('__sign_policy.negative','__is_negative')
 if pointers:
  s=s.replace('  string __grouping =', '  string_type::const_iterator __digits_first;\n  string_type::const_iterator __digits_last;\n  string __grouping =')
  s=s.replace('  string_type::const_iterator __digits_first =','  __digits_first =').replace('  string_type::const_iterator __digits_last  =','  __digits_last =')
 if frac:
  s=s.replace('  string __grouping =', '  int __frac_digits;\n  string __grouping =').replace('  int __frac_digits      =','  __frac_digits =')
 if pattern:
  s=s.replace('  size_t __width        =', '  __declspec(align(8)) money_base::pattern __format;\n  size_t __width =')
  s=s.replace('  __declspec(align(8)) money_base::pattern __format =','  __format =')
 label=f'life-s{scope}-n{negative}-p{pointers}-f{frac}-a{pattern}'
 specs.append((label,s))
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as p:r=list(p.map(trials.run,specs))
(trials.scratch/'lifetimes.json').write_text(json.dumps(r,indent=2)+'\n')
