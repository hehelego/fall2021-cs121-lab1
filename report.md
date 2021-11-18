# CS121@2021fall Lab1 Report

## Testing Enviroment

## Test dataset

## Algorithm Description

## Appendix

### encountered problems

#### using inline member function from a static library

According to [stackoverflow: inlining function inside a static library](https://stackoverflow.com/questions/53114164/inlining-class-methods-inside-a-static-library),
we have to get rid of static/dynamic linking.

### HW/SW Enviornment

The benchmark was done on my laptop.  
It is a Lenovo Ideapad S540 equiped with a AMD Ryzen 4800U processor (8 physical cores with hyperthreading feature enabled) and 16GB DDR4 memory (configured in 2x8 dual channel mode).  
Arch linux is installed on the machine, all the involved softwares are up-to-date (latest stable release).

```plaintext
uname -a

Linux sp-ideapad 5.15.2-arch1-1 #1 SMP PREEMPT Fri, 12 Nov 2021 19:22:10 +0000 x86_64 GNU/Linux
```

```plaintext
lscpu

Architecture:                    x86_64
CPU op-mode(s):                  32-bit, 64-bit
Address sizes:                   48 bits physical, 48 bits virtual
Byte Order:                      Little Endian
CPU(s):                          16
On-line CPU(s) list:             0-15
Vendor ID:                       AuthenticAMD
Model name:                      AMD Ryzen 7 4800U with Radeon Graphics
CPU family:                      23
Model:                           96
Thread(s) per core:              2
Core(s) per socket:              8
Socket(s):                       1
Stepping:                        1
Frequency boost:                 enabled
CPU max MHz:                     1800.0000
CPU min MHz:                     1400.0000
BogoMIPS:                        3594.00
Flags:                           fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl nonstop_tsc cpuid extd_apicid aperfmperf rapl pni pclmulqdq monitor ssse3 fma cx16 sse4_1 sse4_2 movbe popcnt aes xsave avx f16c rdrand lahf_lm cmp_legacy svm extapic cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw ibs skinit wdt tce topoext perfctr_core perfctr_nb bpext perfctr_llc mwaitx cpb cat_l3 cdp_l3 hw_pstate ssbd mba ibrs ibpb stibp vmmcall fsgsbase bmi1 avx2 smep bmi2 cqm rdt_a rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local clzero irperf xsaveerptr rdpru wbnoinvd arat npt lbrv svm_lock nrip_save tsc_scale vmcb_clean flushbyasid decodeassists pausefilter pfthreshold avic v_vmsave_vmload vgif v_spec_ctrl umip rdpid overflow_recov succor smca
Virtualization:                  AMD-V
L1d cache:                       256 KiB (8 instances)
L1i cache:                       256 KiB (8 instances)
L2 cache:                        4 MiB (8 instances)
L3 cache:                        8 MiB (2 instances)
NUMA node(s):                    1
NUMA node0 CPU(s):               0-15
Vulnerability Itlb multihit:     Not affected
Vulnerability L1tf:              Not affected
Vulnerability Mds:               Not affected
Vulnerability Meltdown:          Not affected
Vulnerability Spec store bypass: Mitigation; Speculative Store Bypass disabled via prctl and seccomp
Vulnerability Spectre v1:        Mitigation; usercopy/swapgs barriers and __user pointer sanitization
Vulnerability Spectre v2:        Mitigation; Full AMD retpoline, IBPB conditional, IBRS_FW, STIBP conditional, RSB filling
Vulnerability Srbds:             Not affected
Vulnerability Tsx async abort:   Not affected
```

```plaintext
hwinfo --cpu

01: None 00.0: 10103 CPU
  [Created at cpu.462]
  Unique ID: rdCR.j8NaKXDZtZ6
  Hardware Class: cpu
  Arch: X86-64
  Vendor: "AuthenticAMD"
  Model: 23.96.1 "AMD Ryzen 7 4800U with Radeon Graphics"
  Features: fpu,vme,de,pse,tsc,msr,pae,mce,cx8,apic,sep,mtrr,pge,mca,cmov,pat,pse36,clflush,mmx,fxsr,sse,sse2,ht,syscall,nx,mmxext,fxsr_opt,pdpe1gb,rdtscp,lm,constant_tsc,rep_good,nopl,nonstop_tsc,cpuid,extd_apicid,aperfmperf,rapl,pni,pclmulqdq,monitor,ssse3,fma,cx16,sse4_1,sse4_2,movbe,popcnt,aes,xsave,avx,f16c,rdrand,lahf_lm,cmp_legacy,svm,extapic,cr8_legacy,abm,sse4a,misalignsse,3dnowprefetch,osvw,ibs,skinit,wdt,tce,topoext,perfctr_core,perfctr_nb,bpext,perfctr_llc,mwaitx,cpb,cat_l3,cdp_l3,hw_pstate,ssbd,mba,ibrs,ibpb,stibp,vmmcall,fsgsbase,bmi1,avx2,smep,bmi2,cqm,rdt_a,rdseed,adx,smap,clflushopt,clwb,sha_ni,xsaveopt,xsavec,xgetbv1,xsaves,cqm_llc,cqm_occup_llc,cqm_mbm_total,cqm_mbm_local,clzero,irperf,xsaveerptr,rdpru,wbnoinvd,arat,npt,lbrv,svm_lock,nrip_save,tsc_scale,vmcb_clean,flushbyasid,decodeassists,pausefilter,pfthreshold,avic,v_vmsave_vmload,vgif,v_spec_ctrl,umip,rdpid,overflow_recov,succor,smca
  Clock: 2405 MHz
  BogoMips: 3594.00
  Cache: 512 kb
  Units/Processor: 16
  Config Status: cfg=new, avail=yes, need=no, active=unknown


(15 duplicate ones omitted)
```

```plaintext
hwinfo --memory

01: None 00.0: 10102 Main Memory
  [Created at memory.74]
  Unique ID: rdCR.CxwsZFjVASF
  Hardware Class: memory
  Model: "Main Memory"
  Memory Range: 0x00000000-0x3a4620fff (rw)
  Memory Size: 15 GB
  Config Status: cfg=new, avail=yes, need=no, active=unknown
```

### softwares dependices

- `fish` 3.3.1
- `python` 3.9.7
- `aria2` 1.36.0
- `gcc` 11.1.0
- `openmp` 13.0.0-1
- `cmake` 3.21.4
- `valgrind` 3.17.0
