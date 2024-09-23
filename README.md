# UTF8_C
Unions in C can be very confusing for beginers. It's a compund type, but unlike structs they can only store one variable (with fidelity) at a time, this means that assigning to a variable might, and probably will, change all the others. This happens because variables declared under the same union share a single memory location with the size of the biggest variable type, making it impossible to store independent values.

For a long time I thought unions had no use in present-day programming problems. That was until I saw a YouTube video about UTF-8. When I saw all that messy bit shifting I thought there had to be a way to simplify that. And there was: Unions! Since you can create unions with any type, you can use an array of smaller integers to fill the space of a bigger integer.

This is the main idea implemented in this repository. Here, we use the logical segmentation of a 32-bit integer — a codepoint — into four 8-bit integers — its octets. This allows us to pick the full information or just the part of interest for the algorithm, thus simplifying the process of manipulating bits and making the code much more readable and intuitive.
