import os, sys

repoRoot = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))
python = sys.executable
dbcCodeGenFile = os.path.join(repoRoot, "tools", "dbcCodeGen", "dbcCodeGen.py")

dbcFile = os.path.join(repoRoot, "stersmithNucleoMvp", "scripts", "EIM.dbc")
targetDir = os.path.join(repoRoot, "stersmithNucleoMvp", "app", "generated")
os.system(f"{python} {dbcCodeGenFile} --dbcFile {dbcFile} --targetDir {targetDir} --alias EIM --node EIM")
