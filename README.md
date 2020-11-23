Ods2 - a library to read/write/update OpenDocument Spreadsheet (.ods) files.
Supports the most commonly used formula functions (including evaluation).

##### API usage
See sample/examples[1-2].cc

Also, the file sample/Invoice.ods was generated with Ods2, the source code
for the code that generated it is in sample/Invoice.cpp

##### How to build
Built exactly as my other project - QOds, see how_to_build.html

##### License, etc
Library updates might break API compatibility with previous updates to allow
for easier development of this library.

Licensed under the GPLv3, see LICENSE for details.
For questions, feature requests, etc: f35f22fan AT gmail.com

---

##### Implemented Formula Functions:

Column 1 | Column 2   | Column 3 | Column 4
-------- | ---------- | -------- | ---------
☑️AVERAGE()    | ☑️MAX()            | ☑️MIN()          | ☑️SUMIF()
☑️COUNT()      | ☑️CONCATENATE()    | ☑️DATE()         | ☑️NOW()
☑️QUOTIENT()   | ☑️MOD()            | ☑️POWER()        | ☑️IF()
☑️PRODUCT()    | ☑️COUNTA()         | ☑️COUNTBLANK()   | ☑️COUNTIF()
☑️SUM()        | ☑️TODAY()          | ☑️ROUND()        | ☑️ROUNDDOWN()
☑️ROUNDUP()    | ⬜ DAY()            | ⬜ MONTH()        | ⬜ YEAR()

---
BTC/₿: bc1qzs8ux6m0t4jj98furra8pvx2ll80qchr5v4ru6
