```
[SDS_Admin@node19 ~]$ sudo dmidecode -t processor
# dmidecode 3.4
Getting SMBIOS data from sysfs.
SMBIOS 3.2.0 present.

Handle 0x002B, DMI type 4, 48 bytes
Processor Information
        Socket Designation: CPU01
        Type: Central Processor
        Family: ARM
        Manufacturer: HiSilicon
        ID: 10 D0 1F 48 00 00 00 00
        Signature: Implementor 0x48, Variant 0x1, Architecture 15, Part 0xd01, Revision 0
        Version: HUAWEI Kunpeng 920 7260
        Voltage: 0.9 V
        External Clock: 100 MHz
        Max Speed: 2600 MHz
        Current Speed: 2600 MHz
        Status: Populated, Enabled
        Upgrade: Unknown
        L1 Cache Handle: 0x0028
        L2 Cache Handle: 0x0029
        L3 Cache Handle: 0x002A
        Serial Number: 68880C9401F04224
        Asset Tag: To be filled by O.E.M.
        Part Number: To be filled by O.E.M.
        Core Count: 64
        Core Enabled: 32
        Thread Count: 64
        Characteristics:
                64-bit capable
                Multi-Core
                Execute Protection
                Enhanced Virtualization
                Power/Performance Control
```
注意这个：
```
Core Count: 64
Core Enabled: 32
```
