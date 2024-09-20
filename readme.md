# CS61C Project 1
## Thoughts after finishing:
1. Memery management:
    1. Initialize one variable instantly after you declare a variable.(Tips: when declare a `struct`, initialize all of its variables!)
    2. A `malloc`, a `free`. Also, don't forget to free the variables of a struct.

2. Algorithm:
    1. Neighbor. How to handle edge case when counting neighbors? A very simple way: `(row + dx + image->rows) % image->rows`. I should have learned it in Data Structure classes but I just can't remind of it.
    2. Handling binary numbers:
        1. Concatenate two number:
        ```C
        uint8_t a = 255;
        uint8_t b = 1;
        uint32_t res = a << 8 | b;
        ```
        2. If one specific bit of a number is 1?
        ```C
        uint32_t x = 0x1808;
        int res = x >> 3 & 1; // Take the forth least bit for example.
        ``` 

3. Side note:
    **Please be careful!!!**, I have a painful debug experience in this project because I occasionally type one `col` into `row` qaq.
