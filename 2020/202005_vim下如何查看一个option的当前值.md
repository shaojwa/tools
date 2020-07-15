比如 hls, nohls这几个都是选项，其实内部对应的应该是一个字段，可以通过` set hls?` 查看当前设置。

只要是设置，那么不管 set hls?还是 set nohls? 返回的都是 hlsearch，如果没设置，这两个查询返回的都是nohlsearch。
