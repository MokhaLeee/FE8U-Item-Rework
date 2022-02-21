# C-Style Study on FE8U Items by [Mokha](https://github.com/MokhaLeee) (W.I.P.) 

A study for rebuilding FE8U item system modularly.

* Map-Main
	>+ Usability on Item Menu
	>+ Item Menu Effect
	>+ Action Routine (such as map animes, etc.)
* Prep-Screen
	>+ Prep-screen item effect proc

the c-lib and gbafe.h are used as decomp-version, you can get which at [FE-CLib-Decompatible](https://github.com/boviex/FE-CLib-Decompatible.git)

You can directly assemble Main.event through [Event Assembler](https://github.com/StanHash/EventAssembler.git). For compiling wizardry(src), refer to [FE-CHAX by StanH](https://github.com/StanHash/FE-CHAX).


---
Q: ERROR when assemble Buildfile through EA, which told me `Undefined identifier: _LP___gnu_thumb1_case_uqi`

A: Change optimize-options of gcc from `Os` to `O1` or `O2`.