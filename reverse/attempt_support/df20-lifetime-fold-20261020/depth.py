import trials,itertools,concurrent.futures,json
specs=[]
for shape,depth,ctorinline in itertools.product(['cf-goto-op0-li1','baseline'],[1,2,3,4,5,6,8,12],[False,True]):
 s=(trials.scratch/(shape+'.cpp')).read_text()
 if shape=='baseline':s=s.replace('template <> _String_base<wchar_t, allocator<wchar_t> >::~_String_base();','')
 # Ending pragma is taken as the function inline depth. Test interaction with
 # nested destructor expansion now that grouping/locale have their own scope.
 at=s.rfind('}')
 s=s[:at]+f'\n#pragma inline_depth({depth})\n'+s[at:]
 if ctorinline:
  s=s.replace('template <> basic_string<wchar_t>::basic_string(const basic_string<wchar_t>&);', 'template <> inline basic_string<wchar_t>::basic_string(const basic_string<wchar_t>&s) : _String_base<wchar_t,allocator<wchar_t> >(s.get_allocator()) { _M_range_initialize(s._M_start,s._M_finish); }')
 specs.append((f'depth-{shape}-d{depth}-ci{int(ctorinline)}',s))
with concurrent.futures.ThreadPoolExecutor(max_workers=8) as p:r=list(p.map(trials.run,specs))
(trials.scratch/'depth.json').write_text(json.dumps(r,indent=2)+'\n')
