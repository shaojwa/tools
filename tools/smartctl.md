```
[SDS_Admin@node112 ~]$ sudo smartctl -i /dev/sdad
smartctl 6.5 2016-05-07 r4318 [x86_64-linux-4.14.0-49.hl25.x86_64] (local build)
Copyright (C) 2002-16, Bruce Allen, Christian Franke, www.smartmontools.org

=== START OF INFORMATION SECTION ===
Vendor:               AVAGO
Product:              MR9460-8i
Revision:             5.20
User Capacity:        8,001,020,755,968 bytes [8.00 TB]
Logical block size:   512 bytes
Physical block size:  4096 bytes
Logical Unit id:      0x600062b20791b2c02aa1c685f91ba657
Serial number:        0057a61bf985c6a12ac0b29107b26200
Device type:          disk
Local Time is:        Thu Sep 29 23:35:23 2022 CST
SMART support is:     Unavailable - device lacks SMART capability.
```

```
[SDS_Admin@node80 ~]$ sudo smartctl -i /dev/sda
smartctl 6.5 2016-05-07 r4318 [x86_64-linux-5.10.38-21.hl05.el7.x86_64] (local build)
Copyright (C) 2002-16, Bruce Allen, Christian Franke, www.smartmontools.org

=== START OF INFORMATION SECTION ===
Device Model:     Micron_5200_MTFDDAK480TDC
Serial Number:    20122711DEE3
LU WWN Device Id: 5 00a075 12711dee3
Firmware Version: D1MH027
User Capacity:    480,103,981,056 bytes [480 GB]
Sector Sizes:     512 bytes logical, 4096 bytes physical
Rotation Rate:    Solid State Device
Form Factor:      2.5 inches
Device is:        Not in smartctl database [for details use: -P showall]
ATA Version is:   ACS-3 T13/2161-D revision 5
SATA Version is:  SATA 3.2, 6.0 Gb/s (current: 6.0 Gb/s)
Local Time is:    Thu Sep 29 23:47:39 2022 CST
SMART support is: Available - device has SMART capability.
SMART support is: Enabled
```
#### 检测是否健康
```
[SDS_Admin@node80 ~]$ sudo smartctl -H /dev/sda
smartctl 6.5 2016-05-07 r4318 [x86_64-linux-5.10.38-21.hl05.el7.x86_64] (local build)
Copyright (C) 2002-16, Bruce Allen, Christian Franke, www.smartmontools.org

=== START OF READ SMART DATA SECTION ===
SMART overall-health self-assessment test result: PASSED
```

#### 查看完整信息
可以查看通电时间： 9 Power_On_Hours 
```
[SDS_Admin@node80 ~]$ sudo smartctl -A /dev/sda
smartctl 6.5 2016-05-07 r4318 [x86_64-linux-5.10.38-21.hl05.el7.x86_64] (local build)
Copyright (C) 2002-16, Bruce Allen, Christian Franke, www.smartmontools.org

=== START OF READ SMART DATA SECTION ===
SMART Attributes Data Structure revision number: 16
Vendor Specific SMART Attributes with Thresholds:
ID# ATTRIBUTE_NAME          FLAG     VALUE WORST THRESH TYPE      UPDATED  WHEN_FAILED RAW_VALUE
  1 Raw_Read_Error_Rate     0x002f   100   100   050    Pre-fail  Always       -       0
  5 Reallocated_Sector_Ct   0x0032   100   100   001    Old_age   Always       -       0
  9 Power_On_Hours          0x0032   100   100   000    Old_age   Always       -       13070
 12 Power_Cycle_Count       0x0032   100   100   001    Old_age   Always       -       9935
170 Unknown_Attribute       0x0033   100   100   010    Pre-fail  Always       -       0
171 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       0
172 Unknown_Attribute       0x0032   100   100   001    Old_age   Always       -       0
173 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       66
174 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       9934
183 Runtime_Bad_Block       0x0032   100   100   000    Old_age   Always       -       0
184 End-to-End_Error        0x0032   100   100   000    Old_age   Always       -       0
187 Reported_Uncorrect      0x0032   100   100   000    Old_age   Always       -       0
188 Command_Timeout         0x0032   100   100   000    Old_age   Always       -       9721
194 Temperature_Celsius     0x0022   070   054   000    Old_age   Always       -       30 (Min/Max 14/46)
195 Hardware_ECC_Recovered  0x0032   100   100   000    Old_age   Always       -       0
196 Reallocated_Event_Count 0x0032   100   100   000    Old_age   Always       -       0
197 Current_Pending_Sector  0x0032   100   100   000    Old_age   Always       -       0
198 Offline_Uncorrectable   0x0030   100   100   000    Old_age   Offline      -       0
199 UDMA_CRC_Error_Count    0x0032   100   100   000    Old_age   Always       -       0
202 Unknown_SSD_Attribute   0x0030   100   100   001    Old_age   Offline      -       0
206 Unknown_SSD_Attribute   0x000e   100   100   000    Old_age   Always       -       0
246 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       68093877528
247 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       2127933704
248 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       610351498
180 Unused_Rsvd_Blk_Cnt_Tot 0x0033   100   100   000    Pre-fail  Always       -       4118
210 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       0
211 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       1190
212 Unknown_Attribute       0x0032   100   100   000    Old_age   Always       -       78

```
