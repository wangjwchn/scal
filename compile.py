import os, sys

HOW_TO_COMPILE = "V=1 BUILDTYPE=Release make -j"

def execute(cmd, show=False):
    print(cmd)
    show = True
    os.system(f"{cmd} {''if show else ' > /dev/null 2>&1'}")
    pass

execute(f"chmod +x ./compile.sh && ./compile.sh")
execute(HOW_TO_COMPILE)
