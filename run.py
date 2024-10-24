import os, sys
import platform
import json
from math import sqrt
from multiprocessing import cpu_count

ITERATIONS = 10000000
CONTENTIONS = [0, 5000]
REPEAT_TIME = 5
MAX_CORES = cpu_count()

WHERE_IS_BINS = "./out/Release/"
HOW_TO_COMPILE = "V=1 BUILDTYPE=Release make -j"

BENCHMARKS = {
    'HACKATHONQ':'prodcon-hackathonq',  # Queue, K-FIFO, bounded
    'DPDK':'prodcon-dpdk',              # Queue, FIFO, unbounded
    'BSQ':'prodcon-bs-kfifo'            # Queue, K-FIFO, bounded
}

def execute(cmd, show=False):
    # print(cmd)
    # show = True
    os.system(f"{cmd} {''if show else ' > /dev/null 2>&1'}")
    pass

def run_multi(workload_id, wr_pair):
    for contention in CONTENTIONS:
        for n_writer, n_reader in wr_pair:
            if n_writer + n_reader <= MAX_CORES:
                for bench_id in BENCHMARKS.keys():
                    bin_file = os.path.join(WHERE_IS_BINS, BENCHMARKS[bench_id])
                    print(f"{bench_id},{workload_id},{n_writer},{n_reader},{contention},",end='')
                    sys.stdout.flush()
                    operations = ITERATIONS // (n_writer + n_reader) // (1 if contention==0 else 100)
                    execute(f"{bin_file} -producers={n_writer} -consumers={n_reader} -operations={operations} -c={contention} -prealloc_size=100m", True)

L = list(range(2, MAX_CORES))
I = [1] * len(L)

# execute(f"chmod +x ./compile.sh && ./compile.sh")
# execute(HOW_TO_COMPILE)
run_multi("mpsc", list(zip(L, I)))
run_multi("spmc", list(zip(I, L)))
run_multi("mpmc", list(zip(L, L)))
