======================================================================Study On Solidity=========================================================================
				Date:2017-11-20
				Autor:Zhouwy
================================================================================================================================================================

Solidity Simple Syntax Example:
=================================================================================
pragma solidity ^0.4.0;

contract SimpleStorage {
	uint storedData;
	
	function set(uint x) {
		storedData = x;
	}
	function get() contract returns(uint) {
		return storedData;
	}
}
================================================================================
上面是一个简单的智能合约例子,第一行声明solidity语言版本，确定编译器版本

每个合约必须包含contract关键字，simpleStorage,合约名，因该与合约文件名保持一致，所以一个合约文件应该只包含一个合约
如果需要建一个库，则需要用关键字library
合约名:SimpleStorage,应该与合约文件名保持一致
uint 变量类型(unsigned int)后面可跟位数 uint32 uint64
storedData:变量名
function 函数关键字(keyword)
如果函数有返回，需要声明返回类型关键字(returns)
return:返回结果

Example2:
================================================================================
pragma solidity ^0.4.0;

contract Coin {
    // The keyword "public" makes those variables
    // readable from outside.
    address public minter;
    mapping (address => uint) public balances;

    // Events allow light clients to react on
    // changes efficiently.
    event Sent(address from, address to, uint amount);

    // This is the constructor whose code is
    // run only when the contract is created.
    function Coin() {
        minter = msg.sender;
    }

    function mint(address receiver, uint amount) {
        if (msg.sender != minter) return;
        balances[receiver] += amount;
    }

    function send(address receiver, uint amount) {
        if (balances[msg.sender] < amount) return;
        balances[msg.sender] -= amount;
        balances[receiver] += amount;
        Sent(msg.sender, receiver, amount);
    }
}
================================================================================

合约名:Coin
function Coin:合约构造函数，全程只运行一次
address public miner:声明一个公共变量，外部可以访问，定义了这样一个变量，合约会自动生成一个函数如下:
function miner() returns (address) {
	return miner;
}
所以就不必再定义一个访问公共变量的函数接口，编译器也不允许
mapping (address => uint) public balance; : 这是一个复杂的类型，类似于一个哈希表数据结构，key type:address value uint
访问时可直接通过balance[address]取出value,当定义一个这种函数时，编译器会自动生成下面的访问接口:
function balance(address _accounts) returns(uint) {
	return balance[_accounts];
}
event Sent:事件，可以在函数中触发这个事件，还没研究透彻，我们可以跟踪事件用yixia1函数
Coin.Sent().watch({}, '', function(error, result) {
    if (!error) {
        console.log("Coin transfer: " + result.args.amount +
            " coins were sent from " + result.args.from +
            " to " + result.args.to + ".");
        console.log("Balances now:\n" +
            "Sender: " + Coin.balances.call(result.args.from) +
            "Receiver: " + Coin.balances.call(result.args.to));
    }
})

msg(包含tx 和 block)是一个常用的全局变量，它包含了一些访问BlockChain的属性，其中msg.sender始终表示外部调用地址
事实上，任何人都可以调用mint、send函数，但是mint如果不是合约创建帐户调用将什么也不会发生，只要你拥有足够的Coin你都可以发送给任何人

EVM是一个基于堆栈调用的虚拟机，由于EVM的堆栈被限制在1024个，且每个栈的大小为256B，由于堆栈有限，所以在编写智能合约时使用循环优于递归

导入外部合约or库文件
import "Lib.sol"
如果只是想导入库中的某个符号
import * as SymbolName from "Lib.sol" //javascripts syntax
or
import "Lib.sol" as SymbolName; //solidity Syntax

以别名的形式导入:
import {symbol1 as alias, symbol2} from "Lib.sol"; //导入sunbol1全局符号并设置别名symbol2

目前学习，import只支持导入library,不支持contract,后面继续观察

solc.exe --help察看所有编译参数
solidity 注释
// This is a single-line comment.

/*
This is a
multi-line comment.
*/
natspec 注释:
/**
  * natspec 注释:一般用来说明函数
  *
  */
/** @title Shape calculator. */
contract shapeCalculator {
    /** @dev Calculates a rectangle's surface and perimeter.
      * @param w Width of the rectangle.
      * @param h Height of the rectangle.
      * @return s The calculated surface.
      * @return p The calculated perimeter.
      */
    function rectangle(uint w, uint h) returns (uint s, uint p) {
        s = w * h;
        p = 2 * (w + h);
    }
}

==================================================================
Solidity 的结构
solidity 语言中的合约名类似于面向对象语言中的class,里面可以定义状态变量，函数，函数修饰符，事件、结构类型和枚举类型。此外，合同可以从其他合同中继承(高级语言的特性);

1.状态变量
状态变量是永久存储在契约存储中的值。
pragma solidity ^0.4.0;

contract SimpleStorage {
    uint storedData; // State variable
    // ...
}
2.函数
函数是solidity中的基本执行单位
pragma solidity ^0.4.17;

contract SimpleAuction {
    function bid() payable { // Function
        // ...
    }
}
3.函数修饰符
函数修饰符可用于以声明的方式修改函数的语义
pragma solidity ^0.4.17;

contract Purchase {
    address public seller;

    modifier onlySeller() { // Modifier
        require(msg.sender == seller);
        _;
    }

    function abort() onlySeller { // Modifier usage
        // ...
    }
}
4.事件
事件是与EVM日志设施的便利接口
pragma solidity ^0.4.17;

contract SimpleAuction {
    event HighestBidIncreased(address bidder, uint amount); // Event

    function bid() payable {
        // ...
        HighestBidIncreased(msg.sender, msg.value); // Triggering event
    }
}

5.结构体类型
Structs是自定义定义的类型，可以组合多个变量
pragma solidity ^0.4.0;

contract Ballot {
    struct Voter { // Struct
        uint weight;
        bool voted;
        address delegate;
        uint vote;
    }
}

6.枚举类型
pragma solidity ^0.4.0;

contract Purchase {
    enum State { Created, Locked, Inactive } // Enum
}
=================================================================================

类型
Solidity是一种静态类型语言，每个变量（声明和本地）在编译时刻都要定义

1.变量类型
布尔类型
bool：只存在两种值 true false
操作符
布尔类型
布尔：可能的常量值 是 真或假

操作符：

！（逻辑非）

&&（逻辑与，“and"）

||   (逻辑或，”or“)

==（相等）

！=（不等）

操作符||和&&可以应用常规短路规则，即 表达式 f(x) || g(y), 如果f(x) 已是真，g(y）将不用计算，即使它有副作用 （真||任意值 均为真，假&&任意布尔值 均为假）。
整型

2.整型
int• / uint•: 是有符号和无符号的整数，关键字uint8 到 uint256 字长8 (从8到256位的无符号整数 )
 uint 和 int 分别是 uint256 和 int256的别名
操作符：

比较 ： <=,<,==,!=,>=,> (计算布尔量)

位操作符： &，|，^(位异或)，~（位取反）

算术操作符：+，-，一元-，一元+，*，/,%(取余数)，**（幂次方）
<< (left shift), >> (right shift)


3.定点数(Fixed Point Numbers)
可以声明但还未使用，fixed有符号定点数， ufixed无符号定点数，定点数表示方法
fixMxN M在8~256之间，表示定点数的总长，M必须被8整除，N在0~80之间，表示小数点位数，fixed 与 ufixed 分别表示fixed256x19 和 ufixed256x19
操作符:
Comparisons: <=, <, ==, !=, >=, > (evaluate to bool)
Arithmetic operators: +, -, unary -, unary +, *, /, % (remainder)

4.Address 类型
address：保存20个字节的值（以太坊地址的大小）。地址类型也有成员，并作为所有合同的基础。eg:"0x583031d1113ad414f02576bd6afabfb302140225"
在以太坊中,地址用十六进制表示，占用20字节，uint32 与为4字节
传参时用""包含
地址存在方法:
<address>.balance (uint256):
balance of the Address in Wei

<address>.transfer(uint256 amount):
send given amount of Wei to Address, throws on failure

<address>.send(uint256 amount) returns (bool):
send given amount of Wei to Address, returns false on failure

<address>.call(...) returns (bool):
issue low-level CALL, returns false on failure

<address>.callcode(...) returns (bool):
issue low-level CALLCODE, returns false on failure

<address>.delegatecall(...) returns (bool):
issue low-level DELEGATECALL, returns false on failure

this地址代表的就是合约本身，合约对象默认继承自地址对象，所以内部有地址的属性。

操作符:
<=, <, ==, !=, >= and >

5.定点字节数组(Fixed-size byte arrays)
bytes1, bytes2, bytes3, ..., bytes32. byte is an alias for bytes1.
类似于C中的char c[N];
固定大小，不可改变
byte 表示 bytes1
比较：<=，<，==，!=，>=，>（计算结果为bool）
位运算符：&，|，^（按位异或）， ~（按位取反）， <<（左移位）， >>（右移位）
索引访问：如果x是类型bytesI，然后x[k]对返回的第一个字节（只读）。0 <= k < I

6.动态字节数组(Dynamically-sized byte array)
动态字节数组

delete运算符，用于将某个变量重置为初始值。对于整数，运算符的效果等同于a = 0。而对于定长数组，则是把数组中的每个元素置为初始值，变长数组则是将长度置为0。对于结构体，也是类似，是将所有的成员均重置为初始值。

数据位置(data localtion):
复杂类型，如数组(arrays)和数据结构(struct)在Solidity中有一个额外的属性，数据的存储位置。可选为memory和storage。
还有一种外部函数参数(不包括返回参数)为calldata
所以只有array和struct才存在数据位置的概念
下面来看下官方的例子说明：

pragma solidity ^0.4.0;

contract C {
    uint[] x; // the data location of x is storage

    // the data location of memoryArray is memory
    function f(uint[] memoryArray) {
        x = memoryArray; // works, copies the whole array to storage
        var y = x; // works, assigns a pointer, data location of y is storage
        y[7]; // fine, returns the 8th element
        y.length = 2; // fine, modifies x through y
        delete x; // fine, clears the array, also modifies y
        // The following does not work; it would need to create a new temporary /
        // unnamed array in storage, but storage is "statically" allocated:
        // y = memoryArray;
        // This does not work either, since it would "reset" the pointer, but there
        // is no sensible location it could point to.
        // delete y;
        g(x); // calls g, handing over a reference to x
        h(x); // calls h and creates an independent, temporary copy in memory
    }

    function g(uint[] storage storageArray) internal {}
    function h(uint[] memoryArray) {}
}
强制的数据位置(Forced data location)

外部函数(External function)的参数(不包括返回参数)强制为：calldata
状态变量(State variables)强制为: storage
默认数据位置（Default data location）

函数参数（括返回参数：memory
所有其它的局部变量：storage

7.数组(Array)
数组可以声明时指定长度，或者是变长的。对storage1的数组来说，元素类型可以是任意的，类型可以是数组，映射类型，数据结构等。但对于memory的数组来说。如果函数是对外可见的，那么函数参数不能是映射类型的数组，只能是支持ABI的类型。

一个类型为T，长度为k的数组，可以声明为T[k](定长数组)，而一个变长的数组则声明为T[]。
你还可以声明一个多维数据，如一个类型为uint的数组长度为5的变长数组，可以声明为uint[][5] x。需要留心的是，相比非区块链语言，多维数组的长度声明是反的。
要访问第三个动态数据的，第二个元素，使用x[2][1]。数组的序号是从0开始的，序号顺序与定义相反。

定长数组的长度不能修改

不定长数组类似于C++中的vector,初始化时数组长度为0，这时不能直通过下标引用，只能通过push方法或者是直接设置长度
bytes和string是一种特殊的数组。bytes类似byte[]，但在外部函数作为参数调用中，会进行压缩打包，更省空间，所以应该尽量使用bytes4。string类似bytes，但不提供长度和按序号的访问方式。

string 与 bytes的区别:
bytes byteStr = "123"   ====== "0x313233" 以十六进制保存
string stringStr = "123"  ====== "123" 以utf-8格式保存
且双方之间不能直接赋值

new关键字在声明一个不定长数组是初始化大小
storage：
uint[] array = new uint[](length)
memory:
uint[] memory = mew uint[](length)
memory数组的长度不能改编


Solidity Function格式如下
function (<parameter types>) {internal|external} [pure|constant|view|payable] [returns (<return types>)]

在智能合约中始终伴随三个全局变量，msg, tx, block

关于address中的两个成员函数说明(搅乱了好久):
transfer:x.transfer(100) 向地址x转入100wei ether(以太币)
send:x.send(100)向地址x转入100wei ether(以太币)
为什么向地址x转入100wei,会有不一样，交易总是要有付钱和收钱两方，却别就在这，transfer得付钱方为合约地址，收钱方为x
所以在调用之前一定要检查合约帐户是否有足够的ether
而send的付钱方为msg.sender，收钱方为x,而且seng没有明确的返回值，只返回true,false，官方不建议使用，在使用send的函数一定要有
payable(可支付)标志符
有了payable之后，msg.value才可用

bytes用来存储任意长度的字节数据，string用来存储任意长度的UTF-8编码的字符串数据。
函数可见性:
public: visible externally and internally (creates a getter function for storage/state variables) //外部内部均可见
private: only visible in the current contract //仅仅当前合约可见
external: only visible externally (only for functions) - i.e. can only be message-called (via this.func) //只有外部可见(仅用于函数)，即只能通过消息调用
internal: only visible internally //仅合约内部可见

函数修饰符:
Modifiers
pure for functions: Disallows modification or access of state - this is not enforced yet.
view for functions: Disallows modification of state - this is not enforced yet.
payable for functions: Allows them to receive Ether together with a call.
constant for state variables: Disallows assignment (except initialisation), does not occupy storage slot.
constant for functions: Same as view.
anonymous for events: Does not store event signature as topic.
indexed for event parameters: Stores the parameter as topic.

modifier
修改器(Modifiers)可以用来轻易的改变一个函数的行为。比如用于在函数执行前检查某种前置条件。
修改器是一种合约属性，可被继承，同时还可被派生的合约重写(override)。下面我们来看一段示例代码：
使用修改器实现的一个防重复进入的例子。

pragma solidity ^0.4.0;
contract Mutex {
    bool locked;
    modifier noReentrancy() {
        if (locked) throw;
        locked = true;
        _;
        locked = false;
    }

    /// This function is protected by a mutex, which means that
    /// reentrant calls from within msg.sender.call cannot call f again.
    /// The `return 7` statement assigns 7 to the return value but still
    /// executes the statement `locked = false` in the modifier.
    function f() noReentrancy returns (uint) {
        if (!msg.sender.call()) throw;
        return 7;
    }
}
例子中，由于call()方法有可能会调回当前方法，修改器实现了防重入的检查。
以上f()在执行前会先执行函数修改器内的内容，当执行预见'_'或修改器执行完毕后方可执行f()函数本身



























