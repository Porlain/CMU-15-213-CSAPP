// bias = 2^(k-1) - 1

// V = 2^E * M

// A:
    // 7.0 = 0b111.000…

    // M = 0b1.11, f = 0b0.11, E = 2, e = bias + E, V = 7.0

    // 0 10....01 110....

// B:
// bigest odd number, M must be 0b1.111111…., f = 0b0.11111111…(n bits 1)

// E = n, V = 0b11111111…(n+1 bits 1) = 2^(n+1) - 1
// 0 bias+n 11111....
// C:0 11...101 00000.....




// https://dreamanddead.github.io/CSAPP-3e-Solutions/chapter2/2.85/