# HW&SW environment

## hardware specifications

### processors

```plaintext
Architecture:        x86_64
CPU op-mode(s):      32-bit, 64-bit
Byte Order:          Little Endian
CPU(s):              28
On-line CPU(s) list: 0-27
Thread(s) per core:  1
Core(s) per socket:  14
Socket(s):           2
NUMA node(s):        2
Vendor ID:           GenuineIntel
CPU family:          6
Model:               79
Model name:          Intel(R) Xeon(R) CPU E5-2690 v4 @ 2.60GHz
Stepping:            1
CPU MHz:             3199.929
CPU max MHz:         3500.0000
CPU min MHz:         1200.0000
BogoMIPS:            5200.53
Virtualization:      VT-x
L1d cache:           32K
L1i cache:           32K
L2 cache:            256K
L3 cache:            35840K
NUMA node0 CPU(s):   0-13
NUMA node1 CPU(s):   14-27
Flags:               fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush dts acpi mmx fxsr sse sse2 ss ht tm pbe syscall nx pdpe1gb rdtscp lm constant_tsc arch_perfmon pebs bts rep_good nopl xtopology nonstop_tsc aperfmperf eagerfpu pni pclmulqdq dtes64 monitor ds_cpl vmx smx est tm2 ssse3 fma cx16 xtpr pdcm pcid dca sse4_1 sse4_2 x2apic movbe popcnt tsc_deadline_timer aes xsave avx f16c rdrand lahf_lm abm 3dnowprefetch ida arat epb pln pts dtherm intel_pt tpr_shadow vnmi flexpriority ept vpid fsgsbase tsc_adjust bmi1 hle avx2 smep bmi2 erms invpcid rtm cqm rdseed adx smap xsaveopt cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local
```

### memory

The output of `lshw --memory` is shown.

```plaintext
01: None 00.0: 10102 Main Memory
  [Created at memory.74]
  Unique ID: rdCR.CxwsZFjVASF
  Hardware Class: memory
  Model: "Main Memory"
  Memory Range: 0x00000000-0x3ee85bdfff (rw)
  Memory Size: 256 GB
  Config Status: cfg=new, avail=yes, need=no, active=unknown
```

I tried to run `dmidecode -t memory | grep Bank` to detect the memory configuration, but failed since `/dev/mem` is not available on the AI cluster container.

## software versions

- distro: ubuntu: `18.04`
- linux kernel: `3.10.0-514.16.1.el7.x86_64`
- gcc: `7.5.0`
- openmp: `4.5`
- cmake: `3.10.2`
- GNU make: `4.1`

other used software

- aria2: for downloading the testdata fron SNAP website, `1.33.1`
- fish shell: for task automating, `2.7.1`
- python: `3.6.9`
- python pypi package scipy: `1.5.4`
- python pypi package networkx: `2.5.1`
- gzip: `1.6`
- PaRMAT: git commit hash `adcb03042484c779402fe542fc06bfa6df7d7cb9`

## compiling and linking options

See `src/CMakeLists.txt`.

```plaintext
g++
-std=c++17
-Wall -Wextra
-fopenmp
-O3
src/{file}.cpp -o bin/{file}.o
```

```plaintext
g++
-fopenmp
bin/{file.o} -o bin/{file}
```
