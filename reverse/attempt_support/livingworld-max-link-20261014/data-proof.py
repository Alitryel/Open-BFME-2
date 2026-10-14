import json,sys
from pathlib import Path
sys.path.insert(0,"tools")
import build,data_check as dc,data_ledger as dl
out=Path("build/army-mover-max-link-20261014")
sources={"Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldAISupport/LivingWorldAIArmyMover.cpp":"", "Code/GameEngine/Source/GameLogic/System/LivingWorld/LivingWorldScoreKeeper.cpp":"scorekeeper-"}
rows=dc.source_rows(sources);ledger=dl.load();original=build.row_object
unread=[]
build.row_object=lambda row:out/(sources[row["source"]]+"object-before.obj")
before=dc.findings(dc.object_facts(rows,unread),ledger)
assert not unread,unread
build.row_object=original
unread=[]
after=dc.findings(dc.object_facts(rows,unread),ledger)
assert not unread,unread
assert before==after and len(after)==3,(before,after)
report={"before_findings":before,"after_findings":after,"no_new_findings":True,"baseline_mutated":False}
(out/"data-proof.json").write_text(json.dumps(report,indent=2)+"\n")
print("PASS: three pre-existing data-name findings unchanged; no unread row or new finding")
