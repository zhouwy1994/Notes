处理器架构：51/52 ARM x86 PPC(power pc)  MIPS
计算机冯诺依曼体系：输入(input)、输出(output)、存储器、运算器(ALU)、控制器(CU)
汇编语言：最原始的计算机语言，每一条代码对应一条指令码
计算机的三级存储设备: cache 主存储器 辅助存储器
RICS:精简指令集：
四级：寄存器(register)
寄存器和cache集成在cpu    cache(高速缓冲存储器)
ARM主要的两个工作模式8种：User and svc 当CPU启动时进入SVC模式(特权模式)
ARM的工作状态3个:ARM Thunmb java stream
ARM:contex A之前37 A之后40
一个CPRS 和5个SPSR 一个PC(程序计数器) AND 30个通用寄存器
ARM3级流水线:取指令、译码、执行 并行执行，在执行的时候可以取
下一条指令
重要：PC是正在取址的指令地址，而不是正在执行的地址（不论有多少
级流水线，都是按照三级流水线执行）所以PC - 8 才是正在执行指令的
地址
if else跳转会打断流水线，三目运算符不跳转
v1, v2, v3指令集架构
CPRS(当前程序状态寄存器)
N:负数或小于标志位
Z:零标志位
C:进位或借位标志位
V：溢出标志位
I:IRQ中断禁止标志位(1 禁止 0允许)
F：FIQ中断禁止标准(1 禁止 0允许)
T：Thumb 状态标志位(1 Thumb状态)
M0-M4模式标志位

ARM汇编指令
汇编指令原型：
MOV {<cond>}{S} <Rd>, <shift_operand>
ARM指令中：<>的内容必须写，{}里的内容选写
操作数个数只能少，不能多 Rd 和 Rn 不能省略
condition：条件码
MOV R0, R0 ;//NON 
MOV R0, R0, R0 ;ERROR 错误，参数超出范围，最多只能为两个
Rd d:dest目的 目标位置
Rn n:通用寄存器
shift_operand:移位码 可将最后一个参数移位后赋值给前一个值，也可以不移动
{S}表示可在指令后面加S，来更新相应的CPSR寄存器 如：MOVS R0, #0XFFFFFFFB
CPSR的值为0x800000D3 N位置1 证明结果出现负数

汇编指令原型：
MVN {<cond>}{S} <Rd>, <shift_operand>
取反变负

汇编指令原型：
AND {<cond>}{S} <Rd>, <Rn>, <shift_operand>
三个操作数
当只有两个操作数时也可以
汇编指令原型：
EOR {<cond>}{S} <Rd>, <Rn>, <shift_operand>
异或 两相同的数相异或清零变量
汇编指令原型：
RSB {<cond>}{S} <Rd>, <Rn>, <shift_operand>
反向相减（实现常数减寄存器的值）
ADD SUB 
ADC SBC RSC
格式： {<cond>}{S} <Rd>, <Rn>, <shift_operand>
ADC SBC 要加上或将去C条件标志位
格式：TST{<cond>} <Rd>, <shift_operand>

TST类似于CMP指令，不产生放到目标寄存器的结果，而是将两个数运算的结果反映
到状态标志位，与CMP一样，该指令不需要S后缀
TST详解:*******TST 可以说和AND是一样的，只不过TST不保存运算结果，TST指令事两个
操作数相与，如果相与结果为零，则置位CPSR中的zero位，该命令常用作测试目标寄存器
上的某位是否置位
R0 = 0xfffffffc
TST R0, #0x1
0xfffffffc & 0x00000001 = 0
则CPRS的zero位置1
格式：TEQ{<cond>} <Rd>, <shift_operand>
TEQ 类似于 TST。区别是这里的概念上的计算是 EOR(逻辑异或) 而不是 AND。
格式：CMP{<cond>} <Rd>, <shift_operand>
CMP 允许把一个寄存器的内容如另一个寄存器的内容或立即值进行比较，更改
状态标志来允许进行条件执行。它进行一次减法，但不存储结果，而是正确的更改标志。
可以看出CMP与SUBC的区别在于CMP不存储运算结果
格式：CMN{<cond>} <Rd>, <shift_operand>
CMN 同于 CMP，但它允许你与小负值(操作数 2 的取负的值)进行比较
格式：ORR {<cond>}{S} <Rd>, <Rn>, <shift_operand>
逻辑或
格式：BIC {<cond>}{S} <Rd>, <Rn>, <shift_operand>
指定位清零:BIC R0, R0, #0X1011
将0x1011取反与R0相与就能将R0的指定位清零
格式：MLA {<cond>}{S} <Rd>, <Rn>, <Rm>, <Rs>
	Rd = Rn * Rm + Rs
MLA : 带累加的乘法
MLA {<cond>}{S} <Rd>, <Rn>,<Rs>
Rd = Rn * Rm 
MUL : 乘法
以上两个都只保存低32位的值
UMULL(unsigned multiply long)
格式：MLA {<cond>}{S} <RdLo>, <RnHi>, <Rm>, <Rs>
无符号长整形乘法，结果为64位，保存在 <RdLo>, <RnHi>两个寄存器中
UMLAL：无符号长整形乘法累加
SMULL：有符号长整形乘法
SMLAL：有符号长整形乘法累加

Load/Store
Load/Store内存访问指令表示在ARM寄存器和存储器之间的数据传输，主要有三类
1、单寄存器Load/Store指令进行单项数据传送，传输数据项可以是字节，半字，字类型
LDR{条件}    Rd, <地址>
一般格式:LDR R1, [R0, R2, LSL #2] 将R0 + R2 * 4 的地址数据传送到R1 R0与R1的值不变
STR{条件}    Rd, <地址>
一般格式:STR R1, [R0] 将R1的内容存储在地址为R0的地址中
LDRB：加载字节
LDRH：加载半字
LDRBT：在用户模式下将一个字节加载到寄存器
2、多寄存器Load/Store指令，这类指令可以传送内存区域上的一块；
LDM：加载存储器上的一片数据到指定寄存器
STM: 将指定寄存器中的数据存储在指定存储上
命令格式:LDM {code}<模式> Rn{!}, reglist{^}  
LDM {code}<模式> Rn{!}, reglist{^}  
有8种模式：
注：前面4种用于数据块的传输，后面4种用于堆栈操作
（1）IA  每次传送后地址加4
（2）IB  每次传送前地址加4
（3）DA  每次传送后地址减4
（4）DB  每次传送前地址减4
（5）FD  满递减堆栈
（6）FA  满递增堆栈
（7）ED  空递减堆栈
（8）EA  空递增堆栈
LDMIA R1!, {R2~R9};加载R0指向的地址上的多字数据，保存到R2~R9中，R0值更新;用于加载数据
LDMFD SP!, {R0~R7};恢复现场，异常处理返回；处理堆栈


3、单寄存器交换指令，这类指令允许寄存器和内存区域上的数据交换
SWP{<cond>} <Rd>, <Rm>, [<Rn>]
执行过程：将内存地址Rn里的数据加载到Rd中，再将Rm中的数据加载到Rn中，一般如果要进行数据交换
Rd和Rm要为同一个寄存器
SWP : 单一数据交换
SWPB交换字节

跳转指令：
 B{条件}  <地址>
B 是最简单的分支。一旦遇到一个 B 指令，ARM 处理器将立即跳转到给定的地址，从那里继续执行。
注意存储在分支指令中的实际的值是相对当前的 R15 的值的一个偏移量；而不是一个绝对地址。它
的值由汇编器来计算
BL : 带连接的分支
BL{条件}  <地址>
BL 是另一个分支指令。就在分支之前，在寄存器 14 中装载上 R15 的内容。你可以重新装载 R14 
到 R15 中来返回到在这个分支之后的那个指令，它是子例程的一个基本但强力的实现。它的作用
在屏幕装载器
BX跳转并切换状态
BX {<cond>} <Rm>
执行以上代码，程序跳到Rm指定的地址，Rm的0位复制到CPSR的T标准位 [31:1]位移动进PC
BLX带状态切换的连接跳转指令

状态操作指令
MRS R<-----PSR
MSR PSR<-------R
PSR的32位4个8位的域
[31:24]条件标志位域用f表示
[23:16]状态位域s
[15:8]扩展位域x
[7:0]控制位域c
如果想单独改变某个位域：
MSR CPSR_c, #0x03
协处理器指令：
CDP 协处理器数据操作
LDC 装载协处理器寄存器
STC 将ARM寄存器存储到协处理器
MCR 从ARM寄存器传数据到协处理器寄存器
MRC 从协处理器寄存器传数据到ARM寄存器
异常产生指令：SWI软中断产生指令，产生软中断，处理器进入管理模式
BKPT 断点中断指令，处理器产生软件断点
下面是可获得的条件代码的列表: 
EQ : 等于 
如果一次比较之后设置了 Z 标志。 　 
NE : 不等于 
如果一次比较之后清除了 Z 标志。 　 
VS : 溢出设置 
如果在一次算术操作之后设置了 V 标志，计算的结果不适合放入一个 32bit 目标寄存器中。 　 
VC : 溢出清除 
如果清除了 V 标志，与 VS 相反。 　 
HI : 高于(无符号) 
如果一次比较之后设置了 C 标志并清除了 Z 标志。  
LS : 低于或同于(无符号) 
如果一次比较操作之后清除了 C 标志或设置了 Z 标志。 　 
PL : 正号 
如果一次算术操作之后清除了 N。出于定义‘正号’的目的，零是正数的原因是它不是负数...  
MI : 负号 
如果一次算术操作之后设置了 N 标志。  
CS : 进位设置 
如果一次算术操作或移位操作之后设置了 C 标志，操作的结果不能表示为 32bit。你可以把 C 标志当作结果的第 33 位。  
CC : 进位清除 
与 CS 相反。  
GE : 大于或等于(有符号) 　 
GT : 大于(有符号) 　 
LE : 小于或等于(有符号) 
LT : 小于(有符号) 
AL : 总是 
缺省条件，所以不用明显声明。 
压栈是将寄存器的数据存储到内存，出栈就是将内存的数据加载到寄存器
R0~R3默认用来传参，调用函数时
在汇编中实现跳转，B只能跳转-32M~32M
要实现长跳转，直接改变PC值MOV PC, #0X12345678
ARM指令码的的机器码格式
|31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|9|8|7|6|5|4|3|2|1|0|

第二操作数：可以是ARM通用寄存器、也可以是一个立即数、
可以是一个移位码
RISC：精简指令集，：所有指令长度都一致
CISC：复杂指令集：指令长度不一致

ARM中的立即数是由一个8位的数左移或右移偶数位得到，所以不是所有的数都是立即数
如果不知道是不是立即数的情况下，使用伪指令LDR R0, =0XFFF; 0XFFF不是立即数，但是R0的数会变成0XFFF
LDR R0, =0XFFF ; 0xfff叫基地址
STMFD SP!, {R3~R7, LR}//保护现场
LDMFD SP!, {R3~R7, LR}//恢复现场
SP 在代码开始必须初始化//LDR SP, =0X4000000;
在调用子程序时，需在子程序中将LR压栈，所以ARM要正确封装一个函数，必须要进行现场保护以及恢复
ARM在遇到异常时，将进行模式切换，并将PC设置成为特定的异常向量
MOVS PC, LR 将LR的值改变PC， 并将CPRS的值改变成SPRS的值，切换到正常模式
应用代码都是在USER模式下运行，在特权模式下执行的才是底层代码
在ARM编程中一定要用汇编代码做初始化启动代码，初始化向量表和栈指针
PWM的手动装载高于自动装载，要自动装载时必须关闭手动装载























































































