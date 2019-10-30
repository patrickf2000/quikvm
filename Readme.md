## VM2

### Introduction

This is the second incarnation of my virtual machine program. The original one had several flaws, most notably its inability to process floating point integers. This VM (and its assembler) is designed to be more flexible and have more instructions.

Note: The emphasis is not on speed at the moment, but rather flexibility. If you notice some bad designs, that's probably because it is :)

### Instructions
These are the supported instructions:   

* I_LOAD   
* I_PRINT   
* I_VAR   
* I_STORE   
* I_LOAD_VAR   
* I_INPUT   
* I_CMP   
* I_ADD   
* I_SUB   
* I_MUL   
* I_DIV   
* I_MOD   
* I_POP   
* D_LOAD   
* D_PRINT   
* D_VAR   
* D_STORE   
* D_LOAD_VAR   
* D_INPUT   
* S_LOAD   
* S_PRINT   
* S_POP   
* JMP   
* JE   
* JNE   
* JG   
* JL   
* JGE   
* JLE   
* LBL   
* EXIT   

