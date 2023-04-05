# fun-c
A lightweight generic functional library for C.

### Functionality
- [x] Lambda
- [x] Anonymous function
- [x] For each
- [ ] Collecting
- [x] Reducing
- [x] Filtering
- [x] Mapping
- [x] Matching
  - [x] Any
  - [x] All
  - [x] None
- [x] Prettier piping
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
