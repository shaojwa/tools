Logical byte address在每个扇区的前8个字节:
```
===> Logical byte address miscompare. Expecting 0x0ed9e000, receiving 0x23bde000
```
示例：
```
0x000*  00000000 0ed9e000 ........ ........   00000000 23bde000 00000183 7a322e1a
0x010   17..0000 31647366 20202020 00000000   71780000 31647366 20202020 000c4d40
0x020*  389e28ad 5e271335 708996b2 44ca72ac   28bdabe6 2594c631 13e5658d 00e6c3b2
0x030*  2b2ef52b 21a3b8b4 7278ef73 106fd4fe   025638b0 04c078ca 3324607c 3a8ae50c
0x040*  52bb6dec 3e891b46 6cb0f74c 265505e1   66d6558a 31fd6c67 38f22e6e 369b993e
```

 在扇区的前32个字节中有记录的：
 ```
Byte 0x00 -  0x07: Byte offset of this disk block
Byte 0x08 -  0x0f: Timestamp: number of milliseconds since 1/1/1970
Byte 0x10        : Data Validation key from 1 - 126
Byte 0x11        : Checksum of timestamp
Byte 0x12 -  0x13: Reserved
Byte 0x14 -  0x1b: SD or FSD name in ASCII hexadecimal
Byte 0x1c -  0x1f: Process-id when written
Byte 0x20 - 0x1ff: 480 bytes of compression data pattern
```
