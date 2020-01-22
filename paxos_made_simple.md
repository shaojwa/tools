# 摘要

paxos算法是为了实现一种能容错的分布式系统，这是一种简单的并且显而易见的分布式算法。核心是共识算法：synod。

# 共识算法

## 问题

假设有一个进程集合，集合中的每个进程都可以提议一个值，一致性算法保证的是，只有一个值被选择。如果没有值被提议，那么没有value被选择。
如果有一个值被选择，那么进程应该能学习到这个值。针对共识的安全性需求是：

* （1）只有一个提议的值可能被选择，并且也只有一个值被选择。
* （2）一直值只有被确定选择之后，才能被其他进程学习到。

我们不会去指定精确的存活要求（不保证某些节点一直都在），但是我们需要保证某个提议值最终会被选择。并且被选择之后，进程可以学习到。
算法中，进程有三种角色的代理：proposers，accepters 和，learners。

注意，在具体实现中，一个进程会承担多个角色。

假设一个进程可以通过发送消息与另外一个进程通信。我们采用惯用的异步，非拜占庭模型，在这个模型中：

（1）进程以任意的速度运行，可能停止，可能重启。因为所有的角色都可能在一个值被选择之后停止，然后重启。 

（2） 消息的延时时不确定，也可能丢失，也可能乱序，可能重复，但是内容不会被损坏。

## 两个阶段

先选择一个值，然后学习到这个值。

## 选择一个值

最简单的选择一个值的办法是，只有一个accepter，proposer提议一个值，accepter选择第一个收到的提议的值。尽管简单，但是不满足要求，因为
accepter的故障挂机会导致后续的流程无法继续。

问题：一个acceptor挂掉之后，可以再起一个，为什么会影响后续的流程是什么，学习值么？检测到挂了，可以再起一个新的，会有什么问题？

我们选择另外一个方法，我们采用多个accepter，一个proposer给多个accepter发送提议，如果多个accepter接受这个值，那这个值就被接受。
比如9个节点，5个接受了值a，5个接受了值b，在一个节点只能接受一个值的前提下，a一定是等于b的。

问题：为什么集合大小要大于一半acceptor的值才被选中，因为这样才可以保证整个集群中只有一个值被选中，不然可能存在多个不同的值被选中。

在不考虑挂机以及消息丢失的情况下，如果我们希望就算只有一个值被提议，这个值也能被接受的话，就有如下要求：

(P1) 一个accepter 必须（注意是必须）接受它第一个收到的值，注意第一个收到的proposal值必须要接受，第二个可以不接受。

但这会导致一个问题，多个不同的proposer会提议不同的值，而这些不同的值可能会被不同的acceptor接受，而没有任何一个值达到半数。就算是两个值被提议，只要一个acceptor挂掉，也有可能导致没有一个值被多数的acceptor接受。所以acceptor必须允许接受多个提议的值。所以我们必须跟踪每一个可能被接受的提议（proposal）。用不同的数值标记不同的提议（proposal），这个编号是全局唯一的，不同的proposal有不同的编号。

所以，可以有多个proposal被chosen，但是请注意我们的目标是，只有一个value被chosen，多个proposal不要紧，只要多个proposal对应的值相同就可以。所以，这就是我们得到的第二个要求：

(P2)  如果一个值为v，标号为n的提议被选中（注意），那么所有被选择（注意）的序号大于n的提议的值都必须是v。

所以，编号可以不同，m对应proposal被选中之后，后被选中的proposal的值必须也是v。如何实现？

一个proposal要被选中，它必须先至少被一个acceptor接受吧，所以如果P2满足，充分条件是左右被acceptor的编号大于n的proposal的值必须是v。此时要求已经从新的proposal被选中，提前到proposal被接受，条件其实变强了。概括下就是下面这条：

(P2a) 如果一个值为v，标号为n的提议被选中（注意是选中），那么所有被接受（注意是接受）的序号大于n的提议的值都必须是v。 

此时，依然需要保持P1规则，来保证某个proposal被选中。因为proposal是异步的，所以一个proposal被选中时，可能存在某个acceptor（假设称为c）压根就没收到任何的proposal。加入一个新的proposor突然醒来，并发布一个更高编号的带有不同value的proposal，那么P1规则就会让那个从来没收到任何proposal的acceptor（就是前文提到的c）接受这个值，此刻，违反了P2a规则。因此要保持P1和P2a，需要将P2a加强为P2b：

(P2b) 如果一个值为v，标号为n的提议被选中（注意是选中），那么所有被发布（注意是发布）的序号大于n的提议的值都必须是v。 

至此，proposal中value的选择已经提前到发布阶段（issue），毕竟任何proposal得先发布，才可能被acceptor。所以，P2b能退出P2a，P2a能推出P2，毕竟从P2，到P2a，到P2b是逐步加强的条件。

为了发现如何满足P2b，我们先来想怎么去证明它，我们可以假设，某个编号为m，值为v的proposal已经被选中，并且任何以高于版本m（假设为n > m）proposal的value也是v。那么，我们可以在n上通过归纳法来简单得证明。在【每个以序号m..n-1发布的proposal的值为v】的前提下，我们可以证明，编号为n的的proposal的值是v。

因为编号为m的proposal如果要被chosen，那么一定存在某个集合C，集合由所有接受这个proposal的acceptor构成，且是个大多数集合。结合之前的归纳假设，那么m被选中的猜想可以推出：

每一个C中的accpetor，已经已经接受了某个编号在m..(n-1)之间的proposal，且任何一个被接受的编号在m..n-1的proposal的值一定是v。

因为任何一个多数集合（命名为S），一定至少包含一个C中的成员，那么，只要保证下面这个条件，我们就可以得出这个结论：一个编号为n的proposal的值一定是v：

(P2c)，任何一个v和n，如果一个proposal（编号为n，值为v）想要发布，那么请保证以下条件：一定存在一个多数集合S，这个集合中的acceptor满足两种可能（a）要么没有acceptor接受过编号小于n的proposal（b）要么，这些acceptor中接收到的编号小于n的最大的编号的proposal的值是v。

P2b只是要求如果v被选中（假设编号为n），那么任何编号大于n的proposal在发布的时候值必须为v。其实这只是一个要求，而不是具体可实现的算法，到了P2c，已经尝试通过步骤来满足这个要求，P2c给出了如何满足P2b的更加可操作的方案。这里似乎P2c并不比P2b强？？？？

所以，想要做到v被选中之后发布的任何的proposal的值也是v，那么一种可行的方案就是：保证这一点，需要存在这么一个大多数S：
（a）要么S中压根就没收到过小于n的proposal（是不是意味着没收到过任何proposal？？？）
（b）要么S中的元素可以收到过其他值的proposal，但是编号最大的那个proposal必须是v

为什么要求编号最大呢？等下再说，要实现P2c，一个proposer就必须得学习到小于n的最大的已经被标记过的proposal。

如果存在这样的编号，那么这个proposal可能已经被某个多数集中的每个acceptor接受，或者将要被这个多数集中的acceptor接受。

学习到已经被某接受的proposal是容易的，但是预判将来被会不会被接受是困难的，为了避免预测未来，proposer需要转变思路：

他求实现一个承诺：没有这种accpetance，什么意思，主动要求acceptor不接受小于n的proposal，只要有一个多数集合。集合中的acceptor承诺不再接受小于n的proposal。

问题：这样就能保证P2C了么？好像和P2c并不等价哈？增么保证小于n的最大编号的proposal的值是v呢？

这就产生了下面的proposal发布算法：

* 一个proposer选择一个新的n，并发送一个请求给某个acceptor集合，要求他们回应两点（a）不再接受编号小于n的proposal，这点前面已经说过。（b）如果有，请返回编号小于n的编号最大的proposal。这个请求被称作准备请求（prepare requsest）。

* 如果这个propos而收到一个大多数集合的回应，那么这个proposal 就可以发起一个序号为n，只为v的请求，其中v的值怎么得到呢？v就是受到的多数集合中编号最大的proposal的值。（或者如果响应者没有上报proposal时，proposer就自己选择一个），这个请求叫 accept request。

以上是proposer的算法，其实我们有疑问：
收到一个多数集的回应不再接受小于n的proposal以及得到所有响应的编号最大的proposal的值就解决问题？我没懂

对acceptor来说，会收到两种请求，prepare request，以及 accept request，其中，prepare请求是一定会回应的，但是accept request 必须在它没有承诺不接受的时候才会回应。所以有：

(P1a)： 一个acceptor会接受一个编号为n的proposal，当且仅当它没有回应过编号大于n的proposal的prepare请求。P1a包含P1，P1a是P1的增强，P1说的是第一个值一定会接受，所以，是不是说，一个节点受限收到的是accept请求，而不是prepare请求时，一定会接受accept请求。

以上算法已经是完整的值选择算法，只要保证proposal的编号是唯一的。下面是对这个算法的一个小的优化：


假设一个acceptor收到的一个编号为n的prepare request，但在此之前，它已经回应一个编号大于n的prepare request，也就是说已经答应不再accept 编号为n的的proposal，所以它其实已经没有必要回应这个编号为n的prepare request，因为它不会accept 这个 proposal，此时我们让这个acceptor忽略这个prepare request。我们也会忽略已经接受大proposal的prepare request。

基于这个优化，一个acceptor只需要记住已经accept的编号最高的proposal，和已经回应的prepare request的最高的编号。（我：也就是说，你可以之前accept过一个编号为m的proposal，然后保证后续不再accept 小于n的 prepare request。这里n应该是大于m的，但是我不确定）

因为P2c约束必须得到满足，就算是发生故障。所以一个acceptor必须记住以上两个信息，就算它挂机后重启。

但是proposer是可以随时放弃一个proposal，也不会记住任何东西，只要它不会用同样的序号发送不同的proposal。

将proposer的行为和acceptor的行为合并在一起，我们就知道，算法分为两个阶段：

第一阶段：

（a）一个proposer先会选择一个编号n，然后项一个acceptor多数集发送一个prepare request。
（b）此时acceptor有几种情况。第一，没有回应过任何 prepare request，那么一定会回应这个编号为n的prepare request。第二，回应过编号小于n的prepare requst，那么在此回应这个编号为n的prepare request。第三，回应过编号为n的prepare request，忽略这个prepare request。第四， 回应过编号大于n的prepare request，忽略这个prepare request。并回应这个acceptor接受过的编号最大的proposal，注意，这一点很重要，不然可能会影响proposer发送的accept request中的v值。

第二阶段：

（a）这个proposer收到它发出的prepare request 的回应，且回应的acceptor满足多数集。那么它就会发送accept request。这个accept request中有编号n和值v，这个v是收到的所有accpet多数集中回应的response中编号最大的proposal的v值。
（b）acceptor会接收这个accept request，除非在收到这个accept request之前它又回应过其他的prepare request（很显然，这个prepare request的编号一定是大于n的）


一个proposer是可以发起多个proposal的，只要遵循算法。也可以中途的任何时间放弃某一个propsal。正确性是可以保持的，尽管某些请求或者响应会在proposal被放弃之后很长时间才到达目的地。

当某个proposer开始尝试一个更高编号的proposal时，放弃一个proposal也许是一个好主意。（这个放弃，是单单指这个尝试发布更高版本的proposer么，还是其他的proposer？）所以，当一个acceptor因为收到更高版本的prepare request而放弃低版本的prepare request 和 accpet request时，应该通知proposer，这样这个proposer就可以放弃这个proposer。这只是一个性能上的优化，不会影响正确性。

其实至此，我还是不能完全确定，这样就能保证在编号为n的proposal选中之后，后续被选中的编号大于n的proposal值也是v么？
另外，如果需要其他的值怎么办？以上过程描述的只是一个值的选举过程，不是全过程，不然新的v如何提议？所以继续看下文。

## 学习一个选中的值

learner需要学习到选中的值，所以必须找到被多数集接受的proposal，最明显的算法是，让每一个acceptor，不管什么时候接受一个proposal，都呼应给所有的learner，给他们发送proposal。这可以让learner尽快找到选中的值。但这要求每一个acceptor去回应每一个learner。所以响应的数量是acceptor 和 learner数量的乘积。

在非拜占庭故障的前提下，一个learner从另外一个learner中学习到值时简单的。我们可以让acceptor将回应发送给特定的某个learner。然后这个learner，当某个值被选中时，通知其他的learner。但是这存在单点故障，优势是，请求数只等于acceptor数量加上learner的数量。

所以，更通用的办法是，让多个特定的learner组成一个集合，来提高稳定性，尽管会增加通信的代价和复杂度。

因为消息的丢失，一个被选中的value可能不被任何的learner学习到。learner可以询问acceptor他们接收的proposal是什么。但是某个acceptor的故障会导致无法确定是否某个多数集已经接受某个proposal。在这种情况下，learner只能在新的proposal被选中时找到（新的proposal的值是否和之前的一样？）。如果一个learner需要知道一个新的值是否被选中，那么它可以让一个proposal发起一个proposal，用之前描述的算法。

## 过程

构造一种两个proposer连续不断的发起更高编号的提议，却没有一个proposer的提议被选中的场景是容易的。因为每个proposal都有两个阶段，proposer p的第二阶段可能因为 proposer q的第一阶段（q的编号比p的高）而中断。此时 p 再用更高的编号发起proposal，这个proposal又会影响到q的第二阶段。所以，只要acceptor会回应编号更高的prepare request，那么低编号的accept request 就无法得到响应。

为了保证过程，一个突出的proposer 需要被选出作为唯一的proposer去发起proposal。如果这个proposer可以同acceptor的多数集通信，并且使用
使用比用过的编号更高的编号，他就能成功发布一个proposal且被选中。如果它学习到更高版本的request，他就会放弃原来的proposal并再次尝试，最终他会选到一个足够高的编号。

如果有足够多的系统正常工作，那么通过选择一个唯一的突出proposer来实现活性（这个活性对应的单词liveness到底是什么意思？？）。

## 实现

paxos算法假设一个进程网络。在它的一致性算法中，每一个进程扮演proposer，acceptor，learner的角色。算法选择一个leader process，这个process突出proposer和突出learner的角色。paxos一致性算法在前文中已经精确描述，所有的请求和响应都按顺序发送（有序号标记的意思）。稳定状态（stable staged），挂机期间保留，被用于维护acceptor必须记住的信息。acceptor，在发送响应之前会先记录它计划做出的响应。

现在，剩下的问题是，描述用来保证俩个proposal不会使用同一个number的机制。不同的proposor从不相交的编号集合中选择编号。所以，两个不同的proposer不会用同一个编号来发布一个proposal，每一个proposer会在稳定状态时记住最高已经尝试发布过的proposal，然后下次发起prepare request（phase1）时，使用更高的编号。

# 用状态机实现

一个实现分布式系统的简单方式是用一个client集合去向中心服务器发布命令（command），服务器可以被描述为一个确定性状态机，它按照某个顺序执行client发送的命令。状态机有一个初始状态，获取一个命令作为输入，执行后有一个输出，并达到一个新的状态。比如，一个分布式英航系统的客户端也许就是取款机，同时，状态机的状态由所有用户的账户状态构成（确定是需要所有用户？？？）。一次取款可以通过执行一条状态机命令来完成，这条命令要求扣除一个账户的余额，当且仅当账户里的余额大于等于取款数额。生成新旧余额作为输出。

使用单一中央服务器的实现会挂死，知道这台中央服务器挂掉。所以，我们用一个服务器集合来代替单一服务器系统，每一台服务器单独实现状态机（如果状态机由所有用户的账户构成，那么每一台服务器上都存有所有账户的信息）。因为状态机是确定性状态机，所有的服务器会产生相同的状态序列和输出。只要他们执行相同的命令序列，一个client发布一条命令，使用的输出可以由任何一台服务起为这条命令产生。

为了保证所有的服务器会执行相同的命令序列（什么意思？？？），我们实现一个独立的paxos算法实例序列，被第i个实例选择的值，作为序列中的第i个状态机命令（这话有点绕，算法实例有多个，其中一个实例选择的值，作为状态机命令？？ 有点怪异），每一个服务器同时扮演所有角色（proposer，acceptor和learner）在每一个算法实例中。（感觉就是每一个是夫妻上都运行n个paxos算法进程，这个进程同时扮演三种角色）
所以就可以假设每一台服务器上都有(P1，P2...Pn)个进程，被第i个进程选择额值Vpi,作为state-machine-sequence序列的第i个：
(Vp0,Vp1,...,Vpi,...,Vpn)，现在我们假设服务器集合是固定的，所以每一个算法实例所使用的角色集合是相同的。


正常操作下，某一个服务器会被选为leader，他作为杰出proposer（也就是那个唯一可以发布proposal的那个），这个proposer也是所有paxos实例中的杰出proposer。client发送命令给这个leader，leader决定这些命令在序列中的位置。如果leader决定某个client的命令是第135个，leader会
尝试让那个第135号实例选择那个命令作为value（为什么什么意思？？不太理解）。这通常会成功，是如果失败，一般是因为故障，或者其他服务器认为自己是leader-proposer，且认为第135号命令应该是其他命令。但是一致性算法保证最多只有1个命令被选为第135号命令。

这个方法效率上的关键是，在paxos一致性算法中，值的选择直到phase2阶段才确定。回忆一下，在proposer的phase1阶段结束之后，要么是将要propose 的value已经确定（所有acceptor的回应中，编号最高的proposal的value），要么就是proposer可以自由选择任意值（没有acceptor回应proposal）。

我现在来描述Paxos状态机是如何实现这部分正常情况下的工作。然后，我将讨论会出什么问题，我考虑先前的leader如果挂掉后新的leader被选出后会发生什么？（系统启动是一个特殊情况，在这种情况下，没有命令已经被proposed）

新的leader，在所有的的一致性算法实例中也是一个learner。应该知道大部分已经被选择的命令，假设它知道1-134,138和139号命令，这些命令粉分别是1-134号算法实例所选择的值，（我们也会看到这样的一个命令缺口是如何产生的）。新的leader执行实例135-137以及大于139的实例的phase1（我会在下面描述这如何完成），假设这些执行的输出决定实例135和140将要被proposed 的value，而其他实例将要proposal的输出不受约束。然后leader执行实例135和140的phase2，从而选择第135和140号命令。

这个leader 和其他服务器一样，学习到所有的命令，现在可以执行1-135号命令，然后，他不能执行138-140号命令，尽管它知道138-140号命令，但是136-137号命令没有被选中。leader需要获取到另外两个命令作为第136和137号命令。相反，我们马上提议，将一个特殊的命令no-op作为第136和137号命令，是的状态并不会发生变化（什么意思？？？）。（通过执行136和137号实例的phase2阶段，而这两个实例的value是不受随意的，前文已经有描述）一旦这些no-op被选中，第138-140号命令就可以执行。

至此，1-140号命令都已经被选中。leader1也完成了所有大于140的实例的phase1阶段，并且对于这些大于140号实例以上的phase2，leader可以提议任何值，它可以将下一个请求（某个client发起）的命令提议为第141号命令（注意，只是发起提议，作为phase2阶段的value即可），同样142号命令，143号命令都可以这样完成。

