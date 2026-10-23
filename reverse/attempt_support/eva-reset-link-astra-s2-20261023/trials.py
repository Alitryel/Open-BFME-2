from pathlib import Path
import subprocess,json,re
root=Path("build/s2-eva")
source=Path("Code/GameEngine/Source/GameClient/EvaRva001DF42D.cpp")
base=(root/"baseline.cpp.txt").read_text()
start=base.index("void Rva001DCD3C::rva001DCD3C()")
end=base.index("// Eva status is",start)
body=base[start:end]
prefix=base[:start];suffix=base[end:]
intrinsic="#include <xmmintrin.h>\n"
variants={"control":base}
# A volatile read of a constant source tests memory ordering without marking
# the destination object volatile or passing a receiver subobject to a helper.
vbody=body.replace(" m_00 = -1.0f;\n m_04 = -1.0f;"," float minusOne = evaMinusOne;\n m_00 = minusOne;\n m_04 = minusOne;")
variants["volatile_constant"]=prefix+"static const volatile float evaMinusOne = -1.0f;\n"+vbody+suffix
# Intrinsic stores have known non-escaping address effects, unlike a user helper.
b=body.replace(" m_00 = -1.0f;\n m_04 = -1.0f;"," __m128 minusOne = _mm_set_ss(-1.0f);\n _mm_store_ss(&m_00, minusOne);\n _mm_store_ss(&m_04, minusOne);")
variants["intrinsic_negative_stores"]=intrinsic+prefix+b+suffix
b=body
for field in ("m_08.x","m_08.y","m_08.z","m_14.x","m_14.y","m_14.z","m_24.x","m_24.y","m_24.z"):
 b=b.replace(f" {field} = 0.0f;",f" _mm_store_ss(&{field}, _mm_setzero_ps());")
variants["intrinsic_zero_stores"]=intrinsic+prefix+b+suffix
b=b.replace(" m_00 = -1.0f;\n m_04 = -1.0f;"," __m128 minusOne = _mm_set_ss(-1.0f);\n _mm_store_ss(&m_00, minusOne);\n _mm_store_ss(&m_04, minusOne);")
variants["intrinsic_all_float_stores"]=intrinsic+prefix+b+suffix
# Receiver-local values are already fixed by preceding stores. These expressions
# preserve all values without a call or a volatile destination.
b=body.replace(" m_20 = false;"," m_20 = m_00 > 0.0f;").replace(" m_21 = false;"," m_21 = m_04 > 0.0f;")
variants["known_float_flag_tests"]=prefix+b+suffix
b=body.replace(" m_08.x = 0.0f;"," m_08.x = m_00 + 1.0f;").replace(" m_14.x = 0.0f;"," m_14.x = m_04 + 1.0f;")
variants["known_float_zero_expressions"]=prefix+b+suffix
targets=[("?rva001DCD3C@Rva001DCD3C@@QAEXXZ","0x001DCD3C","80"),("?iniParseNewEvaEvent@Eva@@SAXPAVINI@@@Z","0x001DF42D","635"),("?iniParseEvaEventForwardReference@Eva@@SAXPAVINI@@@Z","0x001DF6A8","484")]
results=[]
try:
 for name,text in variants.items():
  source.write_text(text)
  (root/(name+".cpp.txt")).write_text(text)
  outcome={"variant":name,"functions":[]}
  for symbol,rva,size in targets:
   cmd=["python3","tools/explain_mismatch.py",symbol,"--rva",rva,"--size",size,"--source",str(source),"--context","85"]
   proc=subprocess.run(cmd,text=True,stdout=subprocess.PIPE,stderr=subprocess.STDOUT)
   log=proc.stdout
   (root/(name+"-"+rva+".log")).write_text(log)
   summary=[l for l in log.splitlines() if l.startswith(("compiled symbol size:","classification:","unresolved:","OK:"))]
   outcome["functions"].append({"rva":rva,"exit":proc.returncode,"summary":summary})
   if proc.returncode and "Traceback" in log: break
  results.append(outcome)
  (root/"results.json").write_text(json.dumps(results,indent=2)+"\n")
  print(json.dumps(outcome),flush=True)
finally:
 source.write_bytes((root/"baseline.cpp.txt").read_bytes())
