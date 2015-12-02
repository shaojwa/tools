
* 16位windows 操作系统中，向窗口发送一个消息总是按照同步分方式执行。
* Windows允许一个进程至多建立10000个不同类型的用户对象（User Object）。对象的所有权属于进程，尽管对象由线程调用API创建。但是有两个例外，窗口和挂钩（hook），他们分别由创建窗口和安装挂钩的线程所拥有。这个所谓的所有权有什么意义？其中一个意义在于，这个对象的生命周期和谁同步。如果对象属于线程，比如窗口或挂钩，那么当线程结束时，操作系统会自动删除窗口或卸载挂钩。其他的对象属于进程，那如果对象没有明确删除，那只能等线程退出后对象才被删除（资源被释放）。
* 这种所属关系对于窗口来说的另外一个意义在于，创建窗口的线程也必须是为窗口处理消息的线程。所以只要一个线程创建了一个窗口，就必然有线程独立的消息队列和消息循环。
* THREADINFO这个结构是窗口消息系统的基础。该结构保有四大消息队列。
> 登记消息队列(posted-message queue)
> 发送消息队列(send-message queue)
> 应答消息队列(reply-message queue)
> 虚拟输入队列(virtualized-input queue)

* 针对窗口句柄的消息投放
> PostMessage(HWND hwnd, ...)
向线程的posted-message队列发送消息。
> SendMessage(HWND hwnd, ...)
向线程的send-message队列发送消息。该函数可以向统一线程，本进程的其他线程，以及其他进程的线程发送消息，只要是其他线程发送消息，调用线程都将被挂起，等待接受线程处理完毕。很显然，接受线程如果出错无法返回，那么调用线程将一直被挂起，为避免这种情况，可以调用如下四个函数以编写保护性代码：SendMessageTimeout, SendMessageCallback,SendNotifyMessagehe ReplyMessage()。

* 针对线程的消息投放
> PostThreadMessage(dwThreadId, ...)
向线程的posted-message队列发送消息。
针对线程的消息投放中，MSG结构的hwnd字段将设定为NULL，当线程主消息循环中需要做一些特殊处理的时候会调用该接口。这种不是指派给某个窗口的消息，消息循环就不应该调用DispatchMessage函数。
> PostQuitMessage()可以终止线程的消息循环。
