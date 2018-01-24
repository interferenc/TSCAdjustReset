# TSCAdjustReset.kext

This kernel extension fixes the consenquences of unsyncronised TSC when booting Mac OS on an X299 board with Skylake-X CPUs.

This kext is based on [VoodooTSCSync](http://forge.voodooprojects.org/p/voodootscsync/). That kext writes the same TSC value to all cores, and while that works, the end result is that all cores are adjusted. And it does that multiple times.

On x299 and Skylake-X, the CPU has an invariant TSC, meaning it will NOT get out of sync. The problem with x299/Sklylake-X is that something (probably the BIOS, or even the CPU itself) writes to the TSC of some of the cores, and thus the TSCs are not in sync upon cold or warm boot. The IA32\_TSC\_ADJUST MSR holds the value of how much each core was adjusted. Writing 0 this register rolls back any previous changes. So TSCAdjustReset.kext does exactly that. It can even be unloaded after it did its job.