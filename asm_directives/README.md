
#notes on Assembly

![Project Image](https://github.com/Gawasinspire/stm32f429/asm_directives/blob/master/asm_logo.png)


> Cheatsheet to refresh intermediate's ASM language snippets.

---

### Table of Contents

- [Description](#description)
- [Syntax](#how-to-use)
- [Directives](#additional-resources)
- [More on Directives](#additional-resources)
- [License](#license)
- [Author Info](#author-info)

---

## Description

> Cheatsheet to refresh intermediate's ASM language snippets specifically focussed on Thumb instruction set and cortex_m4 controllers. Tested on stm32f429ZITx.

The [README.md] (https://github.com/Gawasinspire/stm32f429/asm_directives/README.md)
 is for future project reference.

## ASM Syntax

Intructions have four fields separated by space or tabs.

 **label**      **opcode**      **operand**;        **comment**

 *Label*,*comment* non essential but, improves readability.
 
 label: ex., init, main...

 comment: ex., mov r0 r1

 opcode: operational code specified according to instruction set(THUMB). ex., mov, add, push,..

 operand: operation variable, values.

## Directives

* They *assist* and *control* assembly process.
* They are also called pseudo-ops.
* They are not part of the instruction set.
* They change the way code is assembled.


## More on Directives

* Thumb- placed at the top of the file to file that code is generated with thumb instructions.
*code - Denotes the section for the machine instructions. (ROM).
*Data - Denotes the section for the global variables. (RAM).
*Area - Instructs the assembler to assemble a new code.
*Space - Reserves a block of memory and fills it with zeros.
*Align - Used to ensure next object aligns property.
*Export - to make an object accessible from another file.
*Global - Same meaning as Export.
*Import - to access an "exported" object.
*End - placed at the end of each line.
*DCB - Places byte (8-bits) sized constant in memory.
*DCW - Places a half-word (16-bits) sized constant into memory.
*EQU - To give a symbolic name to a numeric constant.
*|.text| - Makes assembly callable by c.

## License
Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.


## Author info
Gawasinspire@github.com

[Back To The Top](#README.md)
