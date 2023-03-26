line or list
```
(gdb) list *0x400e33
0x400e33 is in std::operator+<char, std::char_traits<char>, std::allocator<char> >(
    char const*,std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
    (/usr/include/c++/4.8.2/bits/basic_string.tcc:692).
687           return *this;
688         }
689
690       template<typename _CharT, typename _Traits, typename _Alloc>
691         basic_string<_CharT, _Traits, _Alloc>
692         operator+(const _CharT* __lhs,
693                   const basic_string<_CharT, _Traits, _Alloc>& __rhs)
694         {
695           __glibcxx_requires_string(__lhs);
696           typedef basic_string<_CharT, _Traits, _Alloc> __string_type;
(gdb)
```

or
```
(gdb) info line *0x400e33
Line 692 of "/usr/include/c++/4.8.2/bits/basic_string.tcc"
   starts at address 0x400e33 <std::operator+<char, std::char_traits<char>, std::allocator<char> >(
        char const*, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)>
   and ends at 0x400e48 <std::operator+<char, std::char_traits<char>, std::allocator<char> >(
        char const*, std::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)+21>.
```
