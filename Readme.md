## QuikVM

### Introduction

This is the nex and improved version of the QuikVM. I re-wrote it from scratch to make it more powerful and more flexible (the last one particularly did not have any support for floating point types, and the design would have made it hard to do so). Like the original, this contains the virtual machine with the corresponding assembler. It is binary compatible with the originall, although that could (and will likely) change.

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

