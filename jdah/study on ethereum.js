==========================================================Study On Ethereum Virtual Machine =======================================================
				Date:2017-11-14
				Author:Zhouwy
====================================================================================================================================================

genesis.json配置很重要,如果配置不当会出现很多莫名其妙的错误,下面的配置通过验证

1.Ethereum（以太坊）是一个使开发人员能够建立和发布下一代分布式应用的公共区块链平台。 通过其专用加密货币以太币（Ether）提供去中心化
的虚拟机（以太虚拟机”Ethereum Virtual Machine）来处理点对点合约。

2.以太坊虚拟机环境有多种语言开发的版本,使用广泛的为go语言开发版本go-ethereum(geth)，也有c++开发的cpp-ethereum(eth)

3.以太坊开发环境搭建(go-ethereum):一下为go语言版的EVM环境搭建

环境:Ubuntu14.04-LTS

方法一:使用apt-get安装
(1)sudo apt-get install software-properties-common //安装通用软件库
(2)sudo add-apt-repository -y ppa:ethereum/ethereum //安装go-ethereum ppa软件源
(2)sudo apt-get update //更新软件列表
(4)sudo apt-get install ethereum //安装EVM(Ethereum Virtual Machine)

方法二:源码安装:
工具:git,go语言开发环境
(1)下载源码:
	git clone https://github.com/ethereum/go-ethereum
(2)进入到源码目录中，开始编译源码:
	cd go-ethereum
	make geth //先要具备go语言开发环境
(3)运行EVM
	build/bin/geth

附:go语言环境搭建:

环境:ubuntu-14.04-LTS

方法一:使用apt-get安装
(1)sudo apt-get install golang //一键安装

注:直接通过apt-get 安装的软件一般为稳定版，往往不是最新版，如要安装最新版，方法二
方法二:
(1)获取最新版golang package
	wget https://studygolang.com/dl/golang/go1.9.2.linux-amd64.tar.gz
	如果wget不能获得，则使用浏览器下载
(2)解压到/user/local/go
	sudo tar -xzf go1.9.2.linux-amd64.tar.gz -C /usr/local
(3)设置环境变量:
	sudo vim /etc/profile 在配置文件最后加上一下内容:
	GOPATH="/home/$username/GoWork"
	GOROOT="/usr/local/go"
	PATH=$GOROOT/bin:$PATH
注解:GOPATH为go语言工作目录，可用可不用
	 GOROOT:golang的安装目录
	 PATH:环境变量
完成以上步骤已经将golang环境安装完毕，测试("hello world"):
在golang工作目录/home/$username/GoWork新建test.go (不一定在GoWork，任意目录都是可以的)
vim test.go写入以下内容:
package main

import "fmt"

func main() {
    fmt.Println("Hello Golang");
}

保存(:wq)，命令行go build test.go 生成test
运行:./test

环境:Windows7
win下建议一健安装
1.下载以太坊虚拟机:http://upyun-assets.ethfans.org/geth/1-7-2/geth-windows-amd64-1.7.2-1db4ecdc.exe
2.默认安装

go语言开发环境:
https://studygolang.com/dl/golang/go1.9.2.windows-amd64.msi
默认安装

测试是否安装成功:
win + R 输入cmd打开终端
1.geth --help
2.go --help

//==========================================================================================================================================
运行以太坊虚拟机(geth)

如果直接在命令行输入geth，会默认直接进入以太坊公网，直接更新以太坊公共区块链数据，当前节点也作为一个公共节点
只有设置自己的数据目录 --datadir，才会属于自己的私有网络，以下为geth私有节点启动参数:
geth --datadir ./node-01 --networkid 314590 --ipcdisable --port 61910 --rpc --rpcapi 'web3,eth,net' --rpccorsdomain '*' --rpcport 8200 console
参数说明可通过命令行geth --help查看

进入终端后输入web3,可查看所有EVM全局命令(javascripts 全局变量)，以下列出常用几个
eth:区块链相关
net:网络相关
personal:帐户相关
admin:管理相关
miner:挖矿相关

搭建私链步骤:以下步骤搭建一个三节点的私链网络(可在同一台计算机打开n个终端，也可在不同计算机中操作)

以下笔记不太完整，请参看博客http://www.cnblogs.com/zl03jsj/p/6858928.html#3836376
http://www.cnblogs.com/zl03jsj/p/6876064.html#3838183

为了在本地网络运行多个以太坊节点的实例,必须确保一下几点: 
1. 每个实例都有独立的数据目录(–datadir) 
2. 每个实例运行都有独立的端口.(eth和rpc两者都是)(–port 和 –rpcprot) 
3. 在集群的情况下, 实例之间都必须要知道彼此. (peer encode)
4. 唯一的ipc通信端点,或者禁用ipc.第一个节点**

1:建立节点数据目录(datadir):该目录是当前节点区块链信息(公钥 秘钥)的保存目录，是节点正常工作的基础
mkdir node-0{1..3} //建立节点数据目录
2.建立创世纪区块文件,是一个json格式的文件:
vim genesis.json 
在创世纪区块的json文件中填入以下内容, 并保存.
{
    "config": {
        "chainId": 12345,
        "homesteadBlock": 0,
        "eip155Block": 0,
        "eip158Block": 0
    },
    "coinbase" : "0x0000000000000000000000000000000000000000",
    "difficulty" : "0x400",
    "extraData" : "0x123456",
    "gasLimit" : "0xffffffff",
    "nonce" : "0x0000000000000042",
    "mixhash" : "0x0000000000000000000000000000000000000000000000000000000000000000",
    "parentHash" : "0x0000000000000000000000000000000000000000000000000000000000000000",
    "timestamp" : "0x00",
    "alloc": { }
}
各自段含义:
mixhash：与nonce配合用于挖矿，由上一个区块的一部分生成的hash。注意他和nonce的设置需要满足以太坊的Yellow paper, 4.3.4. Block Header Validity,
nonce: nonce就是一个64位随机数，用于挖矿，注意他和mixhash的设置需要满足以太坊的Yellow paper, 4.3.4. Block Header Validity
difficulty: 设置当前区块的难度，如果难度过大，cpu挖矿就很难，这里设置较小难度
alloc: 用来预置账号以及账号的以太币数量，因为私有链挖矿比较容易，所以我们不需要预置有币的账号，需要的时候自己创建即可以。
coinbase: 矿工的账号，随便填
timestamp: 设置创世块的时间戳
parentHash: 上一个区块的hash值，因为是创世块，所以这个值是0
extraData: 附加信息，随便填，可以填你的个性信息，必须为十六进制的偶位字符串
gasLimit: 该值设置对GAS的消耗总量限制，用来限制区块能包含的交易信息总和，因为我们是私有链，所以填最大。

3.初始化区块链节点
geth --datadir ./node-01 init ./genesis.json
geth --datadir ./node-02 init ./genesis.json
geth --datadir ./node-03 init ./genesis.json

注意：所有节点(实例)都是基于同一个创世块(genesis.json),且datadir一定不能相同

4.启动第一个节点
geth --datadir ./node --minerthreads 1 --ethash.dagdir "F:\Ethash" --networkid 314590 --ipcdisable --port 61910 --rpc --rpcapi 'web3,eth,net' --rpccorsdomain '*' --rpcport 8200 console
各参数说明如下：
identity ：区块链的标示，随便填写，用于标示目前网络的名字
init ：指定创世块文件的位置，并创建初始块
datadir ：设置当前区块链网络数据存放的位置
port：网络监听端口,默认是8080
rpc：启动rpc通信，可以进行智能合约的部署和调试。它在geth中通常被默认激活。
rpcapi： 设置允许连接的rpc的客户端，一般为db,eth,net,web3
networkid： 设置当前区块链的网络ID，用于区分不同的网络，是一个数字
console：启动命令行模式，可以在Geth中执行命令
此外，还可以使用如下参数：
nodiscover : 使用这个命令可以确保你的节点不会被非手动添加你的人发现。否则，你的节点可能被陌生人的区块链无意添加，如果他和你有相同的初始文件和网络ID。
maxpeers : 如果你不希望其他人连接到你的测试链，可以使用maxpeers 0。反之，如果你确切知道希望多少人连接到你的节点，你也可以通过调整数字来实现。
rpcapi : 这个命令可以决定允许什么API通过RPC进入。在默认情况下，geth可以在RPC激活web3界面。请注意在RPC/IPC界面提供API，会使每个可以进入这个界面（例如dapp’s）的人都有权限访问这个API。注意你激活的是哪个API。Geth会默认激活IPC界面上所有的API，以及RPC界面上的db,eth,net和web3 API。
rpccorsdomain : 这个可以指示什么URL能连接到你的节点来执行RPC定制端任务。务必谨慎，输入一个特定的URL而不是wildcard ( * )，后者会使所有的URL都能连接到你的RPC实例。

启动成功后日志输出:
INFO [11-09|14:58:25] UDP listener up  self=enode://cf60b86a529f5e50310a5d54e8d73b7a5569f96d64159fc21a122554f37f64b1024c979fa72150cb3c4da4fe26f0531684f853009d942f93606f322c2a16d0b6@[::]:61000
INFO [11-09|14:58:25] RLPx listener up  self=enode://cf60b86a529f5e50310a5d54e8d73b7a5569f96d64159fc21a122554f37f64b1024c979fa72150cb3c4da4fe26f0531684f853009d942f93606f322c2a16d0b6@[::]:61000

encode:其他节点可以根据encode加入到Peer
也可通过console命令admin.nodeInfo.encode获得
可通过net.peerCount命令查看当前集群中的节点

启动第二个节点(实例):
geth --datadir ./node --minerthreads 1 --ethash.dagdir "F:\Ethash" --networkid 314590 --ipcdisable --port 61910 --rpc --rpcapi 'web3,eth,net' --rpccorsdomain '*' --rpcport 8200 console --bootnodes \
"enode://cf60b86a529f5e50310a5d54e8d73b7a5569f96d64159fc21a122554f37f64b1024c979fa72150cb3c4da4fe26f0531684f853009d942f93606f322c2a16d0b6@172.18.188.3:61000" console

各参数说明如下：
bootnodes:需要要连接的主机的地址，也就是node-01的encode,注意后面要指定node-01的ip
上面的命令中,--bootndoes 是设置当前节点启动后,直接通过设置--bootndoes 的值来链接第一个节点, --bootnoedes 的值可以通过在第一个节的命令行中,输入:admin.nodeInfo.enode命令打印出来.
也可以不设置 --bootnodes, 直接启动,启动后进入命令行, 通过命令admin.addPeer(enodeUrlOfFirst Instance)把它作为一个peer添加进来.


在挖矿过程中,不因该删除任何与geth有关的数据,虽然不会出现运行错误,但是交易会出现其他错误



把 abi 内容拿出来先在线压缩，然后在终端 2 中输入：
abi=[{"constant":false,"inputs":[{"name":"a","type":"uint256"}],"name":
"multiply","outputs":[{"name":"d","type":"uint256"}],"payable":false,"t
ype":"function"}]
结果显示：
[{
constant: false,
inputs: [{
name: "a",
type: "uint256"
}],
name: "multiply",
outputs: [{
name: "d",
type: "uint256"
}],
payable: false,
type: "function"
}]
创建合约的实例，在终端 2 中继续输入：
test=eth.contract(abi).at("0x98cd084074fe3f15890c55822070ac8274d8f7f6")
其中  "0x98cd084074fe3f15890c55822070ac8274d8f7f6" 就是合约存储的地址，
可以在  truffleProject/build/contracts/Test.json 中找到.
在终端 2 中输入：
test.multiply.call(3)


npm run dev

合约名,合约文件名,部署变量应该保持一致

//Turffle 架构
Truffle需要以太坊客户端支持，需要支持标准的JSON RPC API
能提供JSON RPC API 的客户端:geth eth testrpc...
testrpc 能实时提供结果反馈，不经过挖矿计算，是一个模拟geth的静态过程，在开发智能合约时刻在testrpc上调试通过，再移植到生产环境
适用正式发布的客户端

Geth (go-ethereum)
WebThree(cpp-ethereum)
Truffle需要定义的合约名称和文件名准确匹配。举例来说，如果文件名为MyContract.sol，那么合约文件须为如下两者之一：
contract MyContract {
  ...
}
// or
library MyContract {
  ...
}
依赖
你可以通过使用import来声明依赖。Truffle将会按正确顺序依次编译合约，并在需要的时候自动关联库。
编译目录
编译的输出位于./build/contracts目录。如果目录不存在会自动创建。这些编译文件对于Truffle框架能否正常工作至关重要。你不应该在正常的编译或发布以外手动修改这些文件。

构建truffle app时构建配置文件信息放在truffle.js中，执行build:后的内容
读写数据

以太坊网络把在网络上读与写数据进行了区分，这个区分对于如何写程序影响很大。
通常来说，写数据被称作交易(transaction)，读数据被称作调用(call)。对于交易与调用，他们分别有如下特性：

交易(Transaction)

交易本质上改变了整个以太坊网络的数据状态。一个交易可以是向另一个帐户发送ether(以太坊网络代币)这样的简单行为，也可以是执行合约函数，添加一个新合约到以太坊网络这样的复杂行为。交易的典型特征是写入(或修改)数据。交易需要花费ether，也被称作gas，交易的执行需要时间。当你通过交易执行一个合约的函数时，你并不能立即得到执行结果，因为交易并不是立即执行的。大多娄情况下，通过执行交易不会返回值；它会返回一个交易的ID.总的来说，交易具有如下特征：

需要gas（Ether）
改变网络的状态
不会立即执行
不会暴露返回结果(仅有交易ID)

调用，则与上述的交易非常不同。调用可以在网络上执行代码，但没有数据会被改变(也许仅仅是些临时变量被改变)。调用的执行是免费的，典型的行为就是读取数据。通过调用执行一个合约函数，你会立即得到结果。总的来说，调用具有如下特征：

免费（不花费gas）
不改变网络状态
立即执行
有返回结果。
如果选择，取决于你想干什么，或者说想写数据，还是读数据。

METHOD:DEPLOYED()

每一个抽象出来的合约接口都有一个deployed()方法，上述例子中，你已经见到过。调用这个函数返回一个实例，这个实例代表的是之前部署到网络的合约所对应的抽象接口的实例。

var meta = MetaCoin.deployed();
警告：这仅对使用truffle deploy部署的合约，且一定是在project configuration中配置发布的才有效。如果不是这样，这个函数执行时会抛出异常。

METHOD:AT()

类似于deployed()，你可以通过一个地址来得到一个代表合约的抽象接口实例。当然这个地址一定是这个合约的部署地址。

var meta = MetaCoin.at("0x1234...")
警告：当你的地址不正确，或地址对应的合约不正确时，这个函数并不会抛出异常。但调用接口时会报错。请保证在使用at()时输入正确的地址。

METHOD:NEW()

你可以通过这个方法来部署一个完全全新的合约到网络中。

MetaCoin.new().then(function(instance) {
  // `instance` is a new instance of the abstraction.
  // If this callback is called, the deployment was successful.
  console.log(instance.address);
}).catch(function(e) {
  // There was an error! Handle it.
});
需要注意的是这是一个交易，会改变网络的状态。

8. 测试合约
框架

Truffle使用Mocha测试框架来做自动化测试，使用Chai来做断言。这两个库的结合可能让人耳目一新，我们基于这两者之上，提供一种方式来编译简单和可管理的合约自动化测试用例。

私链在挖矿时,决定不决定挖矿是自己决定,但是有其中一台在挖矿,那在这个peer里面的所有都会更新block（同步）
启动
geth --datadir ./node --minerthreads 1 --ethash.dagdir "F:\Ethash" --networkid 314590  --port 61910 --rpc --rpcapi 'web3,eth,net' --rpccorsdomain '*' --rpcport 8200 --nodiscover console

web3.eth.contract(Contract.abi).at(Contract.address) 就能定位一个链上的智能合约地址

同一目录下的合约--reset会替换之前的合约
在执行geth客户端命令时不指定数据目录(--datadir)，那么操作的将是默认目录

启动一个以太坊客户端，挖矿时由于日志输出到屏幕，不宜再进行命令操作，这时可以打开一个终端，使用命令geth attach --datadir dir 依附之前启动的客户端运行
geth支持一个称为静态节点的特征，如果你有特定的端点，那么你t直想与静态节点连接。如果断开连接，那么静态节点会再次连接。你可以配置永久性静态节点，方法是将
如下代码放入<datadir>/static-nodes.json中（这应该是与chaindata及keystone处于同一个文件夹中）：
["enode://f252c7603b4e82ca0727684e6273bbbef41033c0f78ba3a5d84b25bb8e4225ad6e344aca4796f2e053d965b0f3540abf580d3a3191b21adb27823d456f837a03@192.168.0.111:61910?discport=0"]


以太坊gas收费是由矿工决定的，矿工可以设置相应的gas阀值，不知道可不可以设置为0，待试验

Ethereum 终端:call不会改变区块链数据，sendTranscation会改变区块链数据
sendTranscation格式:function参数在前，form在后

不幸的是，官方的以太坊文档没有被更新，以反映使用solC编译器编译通过RPC不再可能的事实。这意味着如果你试图按照以太坊官方文档和许多基于官方文档的其他教程的指导，
你将会陷入一个兔子洞。有两种方法来编译合同，我鼓励你们尝试两种方法，这样你们就能明白发生了什么。

1.使用solc编译器 
sudo apt-get install solc
2.使用在线solidity编译器

solc --bin --abi -o ./ contract.sol
以上将生成合约的EVM码(bin)和合约abi(以便交互)

手动部署合约(truffle 为自动部署架构)
编辑下面手动部署
eg: vim muilt.sol
pragma solidity ^0.4.15;

contract Muilt {
	uint public stateVariant;

	function muilt(uint variant) public returns(uint) {
		stateVariant += variant;	
		return stateVariant;
	}
	function Muilt(uint initVar) public {
		stateVariant = initVar;
	}
}


solc --bin --abi -o ./ muilt.sol
生成:Muilt.bin Muilt.abi
手动部署:
可在命令行业可以写成js脚步

var initVar = 10; //初始化值任意设置

var muiltABIHandle = web3.eth.contract([{"constant":false,"inputs":[{"name":"variant","type":"uint256"}],
	"name":"muilt","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability":"nonpayable","type":"function"},
	{"constant":true,"inputs":[],"name":"stateVariant","outputs":[{"name":"","type":"uint256"}],"payable":false,"stateMutability"
	:"view","type":"function"},{"inputs":[{"name":"initVar","type":"uint256"}],"payable":false,"stateMutability":"nonpayable","type":"constructor"}]) //合约ABI
	
var muiltBinHandle = muiltABIHandle.new(initVar, {form:web3.eth.accounts[0], data: '0x6060604052341561000f57600080fd
5b60405160208061013683398101604052808051906020019091905050806000819055505060f5806100416000396000f300606060405260043610
6049576000357c0100000000000000000000000000000000000000000000000000000000900463ffffffff1680631a7c686014604e5780639db87c38
146082575b600080fd5b3415605857600080fd5b606c600480803590602001909190505060a8565b6040518082815260200191505060405180910390f35b3
415608c57600080fd5b609260c3565b6040518082815260200191505060405180910390f35b6000816000808282540192505081905550600054905091905
0565b600054815600a165627a7a723058207d245e0e29613389a7457543a7ac5d72d5058359c4099e953b31a2698998bb140029', gas:'1000000'}, function(err, contract) {
	console.log(e, contract);

   if (typeof contract.address !== 'undefined') {

        console.log('Contract mined! address: ' + contract.address + ' transactionHash: ' + contract.transactionHash);
})
//data:为Muilt.bin EVM执行吗

解锁帐户:personal.unLockAccount()
获得合约地址后:address
取得合约实例:
contractIntance = web3.eth.contract(abi).at(address);

调用函数，contravtIntance.function.call() //不写入区块链
contravtIntance.function.sendTranscation(parma, {from}); //写入区块链

truffle 为solidity的开发架构，他会自动部署，部署成功后只需要
取得合约实例:
contractIntance = web3.eth.contract(abi).at(address);

trufflr获取合约实例:
v3.0版本的语法：

MyContract.setProvider(someWeb3Provider);
MyContract.deployed().then(function(instance) {  
  return instance.someFunction();
}).then(function(result) {
  
});
此方法调用函数，call和没有call修改区块链数据

truffle 架构 无架构
回调函数应该是最后一个参数，而回调函数的第一个参数一般为err

truffle编译的智能合约部署(migrate)之后都在build/contract/下生成一个contract.json
这个文件包含了合约所有的内容，abi 和address,所以我们进入truffle console后直接输入合约名可以得到内容


如果之前部署一份合约，而发现合约有待修改的地方，重新修改合约编译部署，之前错误的合约并不会被销毁，除非合约有自动销毁的操作存在
使用abi + address一样可以使用之前的合约，所以部署合约需要仔细调试方可部署，也可以给合约设置自动销毁函数
合约中存在无限循环最终只会导致gas消耗殆尽，产生out of gas 异常

truffle 调试合同:
truffle debug txID(or Transaction Hash)
最好在truffle develop中开发(truffle 4.0新特性 自带TestRPC 客户端)
Commands:                                                                                                                      
(enter) last command entered (step next)                                                                                       
(o) step over, (i) step into, (u) step out, (n) step next
(;) step instruction, (p) print instruction, (h) print this help, (q) quit

step over:单步跳过(不进入函数)
step into:单步进入
step out:跳出当前函数
step next:下一步不跳出
step instruction：设置指令(没用到)
print instruction：打印指令码(汇编)

以下是安全的合约参考https://github.com/OpenZeppelin/zeppelin-solidity

因为在Windows下.js文件可能是可执行文件，所以当执行truffle init后产生的truffle.js
我们再运行truffle命令有限执行truffle.js文件，所以解决办法有几种
1.推荐使用powershell or gitBash (这两种shell不存在以上问题)
2.修改环境变量PATHEXT，将可执行文件.js删除
3.将truffle.js修改名称truffle-config.js
4.使用truffle命令全名truffle.cmd

Truffle只会编译自上次编译以来发生变化的合约，以减少不必要的编辑。如果您想要覆盖此行为，请使用该--all选项运行上述命令。
导入合约: import "./import.sol" //相对位置，相对于当前合约
我们也可以导入NPM or EthPM的包中的合约，语法如下
import "packageNmae/import.sol"

migrations目录下的迁移文件的数字前缀是必须的以便记录迁移是否成功运行,后面是描述文字


Migrate
*****重要
2_initial_migration.js 中的artifacts.require("SimpleStorage");
在迁移之初，我们告诉Truffle我们希望通过这种artifacts.require()方法进行交互的合同。这个方法与Node类似require，但在我们的
例子中，它特别返回了我们可以在我们的部署脚本的其余部分中使用的合同抽象。指定的名称应与该源文件中的合同定义的名称相匹配。
不要传递源文件的名称，因为文件可以包含多个合同。
所以我们为了方便实现合约抽象层，("SimpleStorage")里面应该包含合约名，而不是合约文件名，这也可能是truffle4.0的新特性


var SimpleStorage = artifacts.require("SimpleStorage");

module.exports = function(deployer) {
  deployer.deploy(SimpleStorage);
};


所有的迁移必须通过module.exports语法导出一个函数
module.exports = function(deployer, network, accounts) {
  // Use the accounts within your migrations.
}
部署函数可使用参数以便控制更多性能
deployer.deploy(SimpleStorage);
DEPLOYER.DEPLOY（合同，参数...选项），可以设置合约的构造函数的参数
您可以选择传递一组合同或一组数组，以加速部署多个合同。另外，最后一个参数是一个可选的对象，它可以观察到一个键overwrite。如果overwrite设置为false，则部署者将不会部署此合同（如果已部署）。
这对于由外部依赖项提供合同地址的某些情况很有用。
部署API有三种使用方法
deployer.deploy(A); //部署单个合约，不需要构造参数
deployer.deploy(A, arg1, arg2, ...);///部署单个合约，附加构造参数
deployer.deploy([
  [A, arg1, arg2, ...],
  B,
  [C, arg1]
]); //构造多个函数，附带构造参数

DEPLOYER.LINK（Lib，Dest）//链接使用到的库
deployer.deploy(LibA);
deployer.link(LibA, B);
deployer.deploy(B);

// Link LibA to many contracts
deployer.link(LibA, [B, C, D]);

DEPLOYER.THEN（FUNCTION（）{...}）
var a, b;
deployer.then(function() {
  // Create a new version of A
  return A.new();
}).then(function(instance) {
  a = instance;
  // Get the deployed instance of B
  return B.deployed():
}).then(function(instance) {
  b = instance;
  // Set the new instance of A's address on B via B's setA() function.
  return b.setA(a.address);
});

合约的测试:
truffle test//指定test目录下的测试文件
truffle test ./path/to/test/file.js //指定测试文件
推荐在客户端TestRPC中运行测试用例

truffle 使用Mocha测试框架(Mocha也是js使用比较多的一种测试框架)
在Mocha中我们可以使用artifacts.require("SimpleStorage"); 请求合约抽象层

以下是一个测试用例:
/ Specifically request an abstraction for MetaCoin
var MetaCoin = artifacts.require("MetaCoin");

contract('MetaCoin', function(accounts) {
  it("should put 10000 MetaCoin in the first account", function() {
    return MetaCoin.deployed().then(function(instance) {
      return instance.getBalance.call(accounts[0]);
    }).then(function(balance) {
      assert.equal(balance.valueOf(), 10000, "10000 wasn't in the first account");
    });
  });
  it("should send coin correctly", function() {
    var meta;

    // Get initial balances of first and second account.
    var account_one = accounts[0];
    var account_two = accounts[1];

    var account_one_starting_balance;
    var account_two_starting_balance;
    var account_one_ending_balance;
    var account_two_ending_balance;

    var amount = 10;

    return MetaCoin.deployed().then(function(instance) {
      meta = instance;
      return meta.getBalance.call(account_one);
    }).then(function(balance) {
      account_one_starting_balance = balance.toNumber();
      return meta.getBalance.call(account_two);
    }).then(function(balance) {
      account_two_starting_balance = balance.toNumber();
      return meta.sendCoin(account_two, amount, {from: account_one});
    }).then(function() {
      return meta.getBalance.call(account_one);
    }).then(function(balance) {
      account_one_ending_balance = balance.toNumber();
      return meta.getBalance.call(account_two);
    }).then(function(balance) {
      account_two_ending_balance = balance.toNumber();

      assert.equal(account_one_ending_balance, account_one_starting_balance - amount, "Amount wasn't correctly taken from the sender");
      assert.equal(account_two_ending_balance, account_two_starting_balance + amount, "Amount wasn't correctly sent to the receiver");
    });
  });
});

测试后面看

合约交互:

一般来说，写入数据称为事务，而读取数据称为调用。事务和调用的处理方式非常不同，并具有以下特点。
事务(Transaction)
事务从根本上改变了网络的状态。
当您通过事务执行合同的功能时，您将无法收到该函数的返回值，因为事务没有立即处理。一般来说，通过事务执行的函数不会返回值; 他们将会返回一个事务ID。所以交易有几个特点：
消耗gas
改变网络的状态
不会立即处理（需要挖矿）
不会公开一个返回值（只有一个事务ID）。
 
 调用(Call)
 是免费的（不花费天然气）
不要改变网络的状态
立即处理
返回值

所以查询操作，用call 修改值使用Transaction

要与合约进行交互必须取得合约抽象层（实例）
truffle console 下取得合约抽象层
Contract.deploy().then(function(instance) {....})
请注意，抽象包含了我们合同中存在的完全相同的函数。它还包含一个指向MetaCoin合约的已部署版本的地址。

获得合约实例:
at()：创建一个MyContract代表您的合同在特定('20bety address')地址的实例。
deployed()：创建一个MyContract代表管理的默认地址(默认地址)的实例MyContract。
new()：将此合约的新版本部署到网络中，获取MyContract代表新部署实例的实例（新实例）。

1.使用语法:new
MetaCoin.new().then(function(instance) {
  // Print the new address
  console.log(instance.address);
}).catch(function(err) {
  // There was an error! Handle it.
});

2.at:
var instance = MetaCoin.at("0x1234...");

3.deployed:
MetaCoin.deployed().then(function(instance) {
  meta = instance;  
  return meta.sendCoin(account_two, 10, {from: account_one});
})

以上的MetaCoin是特殊处理的合约抽象层

每个实例都绑定到Ethereum网络上的一个特定地址，每个实例都有从Javascript函数到契约函数的1到1的映射。
at的地址由自己给定,但是地址要是已经部署成功的地址(可以有多个，常用的就是默认地址)
deployed()是当前已近部署成功的默认地址
new:新部署一份合约，合约之间不能覆盖，这将得到一个新地址
在Transaction中
instance.set(value, {from:account})
后面因该要包含是来自哪个调用from

call应该加上后缀以说明是执行call操作，不修改区块链数据

捕捉事件:catch

truffle-contract 是方便NodeJS 和 浏览器抽象的一个工具
安装
$ npm install truffle-contract
使用
NodeJS使用:
var Web3 = require('web3'); //请求web3包
var provider = new Web3.providers.HttpProvider("http://localhost:8545"); //请求以太坊客户端实例
var contract = require("truffle-contract"); //请求truffle-contract
var ContractConcent = require('../build/contracts/MetaCoin.json');

var MyContract = contract({  //contract是建立一个合约抽象层 ContractConcent
  abi: ...,
  unlinked_binary: ...,
  address: ..., // optional
  // many more
})
MyContract.setProvider(provider); //建立合约抽象层与客户端的联系

建立合约实例:deployed(),at(),new()
浏览器使用:
在你的head元素中，包括Web3，然后包括truffle -contract:
<script type="text/javascript" src="./path/to/web3.min.js"></script>
<script type="text/javascript" src="./dist/truffle-contract.min.js"></script>

或者，您可以使用非缩小版本来更轻松地进行调试。
有了这个用法，truffle-contract可以通过TruffleContract对象来获得：
var MyContract = TruffleContract(...);

truffle -artifactor:A contract packager for Ethereum and Javascript (formerly ether-pudding)
可与truffle-contract配合使用，但好像已经过时
现在直接在require 合约的json格式

Truffle-contract API


EVM在执行指定的语句需要消耗gas,习惯性的八gas当作美元，把以太币的单位wei当作人民币, 而gasPrice比作美元---人民币的汇率
eg：  SataeVariant = x; //修改以太坊的一个状态变量需要消耗gas 4000
当前gasPrice为200000000 那么执行上面一条语句就需要 4000 * 2000000wei，相应的你的以太币余额就减少了这么多

他妈的，truffle4.0存在一个bug,修改合约文件之后，要将build文件夹清空，在运行
truffle migrate --reset --compile-all 新合约内容才可以使用，浪费老子太多时间，遇见问题多google
没事去看看truffle 的issue  https://github.com/trufflesuite/truffle/issues
他妈的就是要多google，向truffle这种开源项目就是bug一大堆，npm install web3 默认安装的是1.0.n
npm正他妈不稳定，因为npm属于运行时联网，所以他安装模块的版本都不稳，绝壁要安装指定版本的模块
npm install web3@0.20.0

web3 0.2.n大部分API都是一部的，结果都是用回调函数中传进，所以要多参考Web3 Javascript-API手册
出了问题不要死弄，找社区帮忙

/*******************/
在使用MyContract的at(),new,deployed()获得合约实例，以上三个函数返回

当使用truffle ynbox webpack启动服务时(truffle server)出现以下错误

return (new fsevents(path)).on('fsevent', callback).start();
TypeError: fsevents is not a constructor
证明是fsevents没有安装，当我尝试去npm install fsevents时又出现了下面错误
npm ERR! notsup Unsupported platform for fsevents@1.1.3: wanted {"os":"darwin","arch":"any"} (current: {"os":"win32","arch":"x64"})
看了半天是应为fsevent默认支持'darwin'(苹果公司开发的架构)，而我os的是win32架构
最后通过npm看来是解决不了问题了，只有git fsevents源码安装
git clone https://github.com/strongloop/fsevents.git
fsevent目录下面的package.json中的
 "os": [
      "darwin"
    ],
修改成win32,Linux系统就修改成linux
运行npm install(在package.json目录下)

js在引号中引用变量值为一下形式：
      "  "+var+"  "
js获取表单内容
html:
<form name="myForm" action="demo_form.php" onsubmit="return validateForm()" method="post">
名字: <input type="text" id="fnameId" name="fname">
<input type="submit" value="提交">
</form>

获取文本域的内容 方法一:
var x = document.forms["myForm"]["fname"].value;
console.log(x);
方法二
document.getElementById("fnameId").value

合约事件交互

contract ClientReceipt {
    event Deposit(
        address indexed _from,
        bytes32 indexed _id,
        uint _value
    );

    function deposit(bytes32 _id) public payable {
        // Any call to this function (even deeply nested) can
        // be detected from the JavaScript API by filtering
        // for `Deposit` to be called.
        Deposit(msg.sender, _id, msg.value);
    }
}

var abi = /* abi as generated by the compiler */;
var ClientReceipt = web3.eth.contract(abi);
var clientReceipt = ClientReceipt.at("0x1234...ab67" /* address */);

var event = clientReceipt.Deposit();

// watch for changes
event.watch(function(error, result){
    // result will contain various information
    // including the argumets given to the `Deposit`
    // call.
    if (!error)
        console.log(result);
});

// Or pass a callback to start watching immediately
var event = clientReceipt.Deposit(function(error, result) {
    if (!error)
        console.log(result);
});

//合约交互时返回的结果，是一个result对象，对象包含tx,logs, receipt
}).then(function(result) {
  // result is an object with the following values:
  //
  // result.tx      => transaction hash, string
  // result.logs    => array of decoded events that were triggered within this transaction
  // result.receipt => transaction receipt object, which includes gas used

  // We can loop through result.logs to see if we triggered the Transfer event.
  for (var i = 0; i < result.logs.length; i++) {
    var log = result.logs[i];




































