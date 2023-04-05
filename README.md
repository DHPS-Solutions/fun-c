# fun-c
A lightweight functional library for C.

When running the performance test for int arrays, it performs about 10% faster than the non functional equivalent (no clue how???), please explain if you know. Note this is after running 1000 times with no compiler optimization.

### Functionality
- [x] Lambda
- [x] Anonymous function
- [ ] For each
  - [x] Integer
  - [ ] Generic
- [ ] Collecting
- [ ] Reducing
  - [x] Integer
  - [ ] Generic
- [ ] Filtering
  - [x] Integer
  - [ ] Generic
- [ ] Mapping
  - [x] Integer
  - [ ] Generic
- [ ] Matching
  - [ ] Any
    - [x] Integer
    - [ ] Generic
  - [ ] All
    - [x] Integer
    - [ ] Generic
- [ ] Prettier piping
  - [x] Integer
  - [ ] Generic
- Adding more goals as more comes to mind.

### Naming conventions and semantics
Macro's:
  - All caps name.
  - Multiline do ... while(0)

Functions:
  - Static functions are prefixed with "\__".
  - Newline for first bracket.

Structs:
  - Snake case name suffixed with a "\_t"
  - No typedef

General:
  - Use booleans
  - Follow this, mostly: https://userpages.umbc.edu/~rostamia/cbook/CodingStyle.html.
