```
Contents of the first 32 bytes of each sector:

 Byte 0x00 -  0x07: Byte offset of this disk block
 Byte 0x08 -  0x0f: Timestamp: number of milliseconds since 1/1/1970
 Byte 0x10        : Data Validation key from 1 - 126
 Byte 0x11        : Checksum of timestamp
 Byte 0x12 -  0x13: Reserved
 Byte 0x14 -  0x1b: SD or FSD name in ASCII hexadecimal
 Byte 0x1c -  0x1f: Process-id when written
 Byte 0x20 - 0x1ff: 480 bytes of compression data pattern
 ```
