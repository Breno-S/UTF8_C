# UTF8_C
Unions in C can be very confusing for beginers. It's a compund type, but unlike structs they can only store one variable at a time. In other words, assigning to a variable will 'change the others'. This happens because variables declared under the same union share a single memory location the size of the biggest variable type, meaning it's impossible to store independent values.

For a long time I thought unions had no use in present-day programming problems. That was until I saw a YouTube video about UTF-8. When I saw all that messy bit shifting I wondered if there was a simpler way to code it. And there was: with UNIONS! Since you can create unions with any type, you can use an array of smaller integers to fill the space of a bigger integer.

This is the main idea implemented in this repository. Here, a 32-bit integer — codepoint — is logically separated into four 8-bit integers — octets. This allows us to pick the full information or only what's useful to the algorithm, thus simplifying bit manipulation and making the code much more readable and intuitive.
