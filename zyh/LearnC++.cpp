1.Gcc����c/c++����ʱ,Ĭ���Ƕ�̬���ӿ⣬����뾲̬���ӣ��ɼ�ѡ��-Wl,-Bstatic��ѡ����Ҫ��̬���ӵĿ⣬����::���Ҫ�ָ���̬���ӷ�ʽ
-Wl,-Bdynamic����Ȼ����ȫ�þ�̬���ӷ�ʽ��*�еľ�̬�Ȿ���������������̬��,pthread,dl�ȣ��������-Wl,-Bstatic��ʽ���б���,��ʱ��Ҫ����̬���������Ķ�̬�����-Wl,-Bdynamic��*
��̬����stdc++��ʹ��ѡ��-static-libstdc++
2.����linux��64λϵͳ������һ��lib64Ŀ¼���κ�linuxϵͳ������libĿ¼����ʵlib64��libĿ¼����Ķ����󲿷���һ���ģ�����lib64��lib�ж�����libc.so.6����ֻ��lib64�ﶼ��64λ�⣬��64λ
����̬���ӣ���lib����Ŀ���32λ�������ӵĿ�
linuxϵͳ��/lib -> usr/lib�������ӣ�lib64 -> usr/lib64�������ӣ�bin -> usr/bin��������) sbin -> usr/sbin�������ӣ�
3.linux��c/c++�ر���:libc.so(c) libstdc++.so(c++)
4.�鿴linux�¿�ִ�г����������Ŀ��ļ�����汾��Ϣ������:
(1)objdump -p /path/exceable_pargram | grep NEEDED
(2)objdump -p /path/exceable_pargram ����Version References:����ϸ��GLIBC�汾��Ϣ
(3)strings /path/execable_pargram | grep GLIBC �鿴GLIBC�汾

5.�鿴���ļ���32λ����64λ file /path/execable_pargram

6.gcc4.8 gcc8.2�л�����

7.vistual studio2017֧�����cmake����(linux��windows)������:
(1)��vs2017-->�ļ�---->��----->CMake(�����ļ���<����CMakeLists.txt���ļ���>)--->ѡ��CMakeLists.txt
(2)�ڴ������(�Ŷ�)�·���һ��������--->ѡ���������--->����CMakeSettings.json---->����ļ�������Ŀ���õĹؼ�
(3)�༭CMakeSettings.json�е�$remoteMachineName(Զ��������ip)��$remoteCMakeListsRoot(Զ��CMake���̵�rootĿ¼����rootĿ¼������Ŀ���̵���Ŀ¼)
(4)$cmakeExecutable(Զ������cmake��������·��)��$buildRoot(�����Ĺ���Ŀ¼��ʹ��Ĭ��)��$installRoot(������װĿ¼)��$remoteBuildRoot(Զ�̹���Ŀ¼��Ӧ������buildRoot��Ӧ������һ������)
(5)$remoteInstallRoot(Զ�̰�װĿ¼����ű���֮��Ŀ�ִ���ļ�,Ӧ������installRoot��Ӧ������һ������)
(6)����ֵʹ��Ĭ��
(7)���cmake���ж�����ɶ���ѡ����������ɱ������

(8)�һ�CMakeLists.txt,"���Ժ���������"��ѡ����Ҫ��������ͻᵯ����Ӧ�����launch.vs.json�����������������ѡ��,args,������������

8.�ֲ�ʽ֮���ʱ��ͬ�������ntpserver��ʽ

9.c++17Ҳ���˺ܶ������ԣ�����ѧϰһ�£���Ŀǰ��������ʵ�õĿ�filesystem������ʱ��Ҫ����-lstdc++fs����ʵ��Щ�ⶼ�Ǵ�boost��ֲ������

10.std::static_point_cast��dynmic_point_cast��const_point_castר������ת������ָ��
class Base {};
class Driver::Base{};
std::shared_ptr<Base> basePtr {std::make_shared<Base>()}
std::shared_ptr<Driver> driverPtr {std::make_shared<Driver>()}
����ת��:
auto ptr {static_point_cast<Base>(driverPtr)}
static_point_castֻ�ʺ�����������ת��������ת��û�����Ͱ�ȫ��飬static_castҲ������ת����ָ��ʱԭ����ͬ
����ת��
auto ptr1 {dynamic_point_cast<Driver>(ptr)}
dynamic_point_cast����������ת��ʱ��static_point_castЧ����ͬ������������ת��ʱ�����Ͱ�ȫ��飬������ͼ�鲻ͨ�����Ϊnullptr,dynamic_castת����ָ��ʱЧ����ͬ
����dynamic_point_cast��dynamic_cast�����л�����ת��ʱ�����������麯��

const_point_cast����ת��const����

11.std::weak_ptr,һֱ��Ϊ��ָ��û��ʲô�ô������㺯������һ��ָ��ֵ�����ֲ��뷵����ָ�룬���Ƿ���shared_ptr���������ü������㲻���ָ����������ڿ���Ȩת�Ƴ�ȥ��
���ǾͿ��Խ�shared_ptrתΪweak_ptr��Ϊ��������ֵ�����������������ü����������ڱ�Ҫ����¿���ͨ��lock��������ȡshared_ptrֵ

12.c++�еĶ�д��ʵ�֣���д��:�������߳�ͬʱ��ȡ��������Ȩ��ֻ��һ���߳��ܹ���ȡд��������Ȩ��������������ʱ��д�����ܱ����У�д��������ʱ���������ܳ���
ʵ��:
typedef std::shread_lock<shared_mutex> read_lock;
typedef std::unique_lock<shared_mutex> write_lock;
std::shared_mutex smutex; // shared_mutexҲ��ʹ��shared_timed_mutex���,timed_mutex���ж�ʱ����try_lock_for,try_lock_until
��ȡ����
read_lock rlk(smutex);
д������
write_lock wlk(smutex);

13.���ݿ���ʹ���ODB��https://www.codesynthesis.com/����c++�������ݿ��ORM�������ϵӳ�䣩�����Է������ݿⲻ��дSQL��䣬�����ݿ����
ӳ�������������(ODB ֧�������������ݿ� sqlite_orm)

14.��Ϣ���У�RabbitMQ(���ʿͻ���rabbit-c(c),SimpleAmqpClient(c++��rabbit-c�ķ�װ)),��Ϣ����Ҫѧϰ

15.MinGW-w64(Minimalist(����) GNU for Windows)��װ��MinGW��windows���GUN�����׼�������gcc��g++,gdb���бȽ϶�Ŀ��ù���
��װ����:
(1)����http://mingw-w64.org/doku.php/downloadѡ��MingW-W64-builds
(2)���ص�mingw-w64-install.exeֱ�Ӵ�
(3)Versionѡ�����°桢Architecture(i686<32bit>,x86_64<64bit>)��Threads<posix(unix/linux),win32>(ʹ���Ǹ������߳̿�)��
Exception(�쳣����<seh<�°棬ֻ֧��64bit����><sjlj �ϰ�֧��32bit>>)��Build revision
(4)��MinGW��binĿ¼���뻷������Ŀ¼
(5)ok

16.void func(const std::string &param);
func("Hello Word") //������ȷ����
void func(std::string param);
func("Hello World") //������ȷ����
void func(std::string &param);
func("Hello World") //�����Ե��ã���Ϊ"Hello World"����һ����Ч��std::string����

17.ODBѧϰ�ʼ�
���Ҫʹ��һ�·�ʽ
#pragma db object(person)
#pragma db member(person::id_) id
��ʹ�ó�Ա����Ҫ�й������ʽӿڣ����������й���,������һ�����ݳ�Ա(���ֶ�) std::string name_;
(1)cosnt std::string& name(void) const;
void name(const std:string& name);
(2)cosnt std::string& getName(void) const;
void setName(const std::string& name); // ע������ĸСд
odb��ʹ��boost������֧��ʱ����odb���벽����Ҫ��--profile boost,����ʱ���˼�-lboost_**����Ҫ����-lodb-boost
odb nullҪʹ��odb::nullable<T> mem;

g++����ʱ����-DDATABASE_MYSQL����

18.libcurlѧϰ(http://blog.csdn.net/JGood)
curl_global_init(); // ��ʼ��ȫ����Դ(ÿ������ֻ����һ��)
CURL *easy_handle = curl_easy_init(); // ��ʼ��һ��easy����,easy_handle����һ������session��һ��easy������Ҫ����option,���ܹ���
curl_easy_setopt(easy_handle, CURLOPT_URL, "sftp://192.168.101.134/root/upload.html"); // ����easy����
curl_easy_perform(easy_handle); // ��ʼִ��(ͬ��)

multi_handle = curl_multi_init(); // multi���첽ִ�з�ʽ������ͨ���������easy_handle
curl_multi_add_handle(multi_handle, easy_handle1); // �������
curl_multi_perform(multi_handle, &running_handle_count); //��ʼִ���첽����

curl_global_cleanup(); // �ͷ�ȫ����Դ(ÿ������ֻ����һ��)

19.c99������,__VA_ARGS__,�ɱ������
#define PRINT(...) printf(__VA_ARGS__)
PRINT("%s:%d", argv[0], argc);


20.std::string convert to c++ base type function std::stoi std::stoll...

21.c++11�����û��Զ�������ֵ,��������
std::chrono::seconds operator"" _S(unsigned long long n) {
	return std::chrono::seconds(n);
}
Ȼ��Ϳ���ʹ��
std::this_thread::sleep_for(1_S); // c++��׼�涨,�û��Զ�������ֵ������»���_,�����»��ߵ�ֻ����c++��׼ʹ�ã���c++14�Ѿ�����s��ms������ֵ

22.gdb ���Գ���ʱ�ƶ�������� gdb --args a.out arg1 arg2 ...

23.boost������һ������ָ��,intrusive_ptr<T>(����ָ��)����ʵ�����Զ�������ָ�븨���࣬��Ҫʵ�������ص�����intrusive_ptr_add_ref(T*)����������
������intrusive_ptr_release(T*) //��С���ü������û������ڴ˻ص�����������Ӧ���������統���ü�����Ϊ0ʱ������Ӧ������intrusive_ptr���������ʱ��
�ص��������ص�����

23.c++��2����ת16���ƣ���ʵ�ְ�
std::string bin_to_hexstr(uint8_t *bin, std::size length) {
	std::stringstream ss;
	std::for_each(bin, bin + length, [&ss](uint8_t ch) {
		ss.fill('0'); // ���㲿����0���
		ss.width(2); // ���ÿ��Ϊ2
		ss << static_cast<uint32_t>(ch);
	});
	
	return ss.str();
}


24.c++�д󲿷������ĳ�Ա�������᷵�ص�����(iterator)����(�̳����׼��iterator)��iterator������һ����Բ�ͬ�������ص����ͣ�����һ����׼�ĵ��������ͣ�
iterator������ͷ�ļ�<iterator>,�����ΪʲôֻҪ�ǵ��������Ͷ��ʺ���algorithm�е������㷨��for(auto)����

25.�����Զ�����������̳б�׼��iterator���ش��������ַ�Ϊ���������������ǰ�ú��õ������ȣ�ÿһ�ֵ������в�ͬ�ķ��ʷ�ʽ

26.STL��resize��reserve������,resize��������size��أ�reserve��������capacity���
resize(n):����n�Ǵ���size()����С��size()������size() == n������Ļᱻ���٣������İ���ʼ��ֵ��ȫ�����߿���ͨ��resize(n, value)��value���
reserve(n):���n > size()�ǻ�������n-size()��capacity,�������ʼ�������n < size()�����κδ���

27.STL�е�������Ϊ������:˳��������������ʽ����������������
˳��������:��һ�ָ�Ԫ��֮����˳���ϵ�����Ա���һ�����Խṹ�Ŀ���Ⱥ����(vector,list,deque)
����ʽ����:��˳����������һ��������ʽ�����Ƿ����Ե����ṹ����׼ȷ��˵�Ƕ������ṹ��(set��map��multiset,multimap)
����������:��������ʹһ�������Ϊ��������һ�������Ϊ��һ�ֻ��ơ���������������һ��**�Ѵ��ڵ�����**����**������һ�ֲ�ͬ�ĳ�������**�Ĺ�����ʽ��ʵ�ֵ�һ�ֻ��ơ�
��ʵ���Ƿ����˽ӿ�ת������������֪��������ʵ����һ������(stack,queue,priority_queue,slist)

28.golang�к������Է��ض��ֵ���ⲿ����ʱ�ɰ�����˳����շ���ֵ��������յķ���ֵ����_ռλ������.c++�п�����tuple����,std::tie��std::igonre
// golang
func vals()(int,int,int)  {
	return 3,7,9
}

a,b,_ : vals();

// c++
std::tuple<int,int,int> vals() {
	return {3,7,9};
}

int a,b;
std::tie(a,b,std::igonre) = vals;

c++17�е�һ��������--�ṹ���󶨸����
auto [a,b,c] = vals();

29.���������ʹ����getchar()��Ϊ���������ķ��������������Ͳ����Ժ�̨����ʽ����(a.out &),unix���������͵ģ�����̨��������getchar()ʱ�����
SIGINT�źţ����³����쳣�˳�


30.boost::enable_shared_from_this��һ�����õ�����ָ�빤�ߣ�������boost::bind�ص���ʹ��this������Ҫ���ĺ����ص���this���ͷţ����Ǵ���һ�ֳ���
����̳���enable_shared_from_this,��������ֱ��ʹ��Base::shared_from_thisʱ�ᱨ��������ΪBase::shared_from_this���ص�ʱshared_ptr<Base>,����
c++���ǲ��������ֱ��ת��Ϊ������,��Ҫʹ��dynamic_point_cast<Driver>����ת��

31.a.һֱ����ʹ��vs���������Ĳ����������<�������л��з�>�����뱨һ��Ѿ���ʹ������ǿ�����--->����---->c/c++--->����ѡ��--->����ѡ����� /utf-8ѡ��ɽ��,������
�ں���Ĺ�����Ҳ���ϴ�ѡ��
b.�����QTʹ��MSVC������Ҳ�������������⣬�������������--->ѡ��--->�ı��༭��--->��Ϊ--->�ļ�����--->Ĭ�ϱ���ѡ��UTF8--->UTF-8 BOMѡ��:���������UTF8�����
�ڰ������ķ��ŵ��ļ���Ӻ궨��:#pragma execution_character_set("UTF-8")�ͽ����(��ֹMingGW����ʶ��ú꣬��ʹ��_MSVC�궨������)

32.����֪��boost�������ӿ�ֱ�ӱ���Դ��ķ����ˣ���Ҫ������BOOST_ALL_NO_LIB��Ȼ��boost_1_69_0/libs/�����Ӧ�Ŀ�Ŀ¼�µ�src�µ��ļ�����
��ĿԴ����һ����룬�Ϳ����ˣ�Ҳ�������ÿһ����������������date_time(BOOST_DATE_TIME_NO_LIB)

33.��ʵvs�ṩ�����б��뷽ʽ���ܶ��������Դ���ҲĬ��֧��cmake��nmake�������̣���ֱ�Ӵ�cmd��powershell�����޷�ʹ��cmake��nmake��cl�ģ�Ҫʹ��
Vistual Studioר�õ������й��ߡ�������VS2017�ı�������������ʾ(ע��32bit����64bit)��,����������²ſ���ʹ��ȫ����vs�µĹ���

34.libcurl�����ʱ���ָ����ENABLE_WINSSLѡ��Ͱ�����ssl�⣬�����ʱ����Ŀ�а���������ҲҪʹ�õ�ssl�⣬���ܾͻ�Ĭ������curl���е�ssl��
�ͻᵼ�����Ӳ��������������ʹ��libcurl�Ļ���Ҫע������ssl�������

35.vs��дwindows����ʱĬ�϶�̬�������п⣬������������û�а�װwindows���п�ļ�����ǲ����������еģ�Ҫ����������̬��һ�𿽱���Ҫ���;�̬����
���п⣬��̬�������пⷽ����
��Ŀ -> ��������->����->MFC��ʹ�� :�ھ�̬����ʹ��MFC������������ã���
��Ŀ -> ��������->C/C++->��������->���п� :ѡ��/MT���������ѡ������֮�󲿷ֻ������ܻ�������


36.c++����redis�������⣬CRedisClient(https://github.com/shawn246/redis_client),��һ�������redis�������ݿ⹤�ߣ�
����Ҳ��Ӧ�Ĵ���bug,��Ҫ�Լ���Ӵ���ѡ��db,��auth����֤��,��CRedisConnection::ConnectToRedis����ӣ�ע������redisCmd.SetArgs
�����m_bShareMem��Ĭ���ǿ����ģ�CRedisCommand redisCmd("cluster", false);��Ҫ��������false��

37.����ѧϰgo���Զ�ά��Ƭ,[][]int,���������ģ�����һ����Ƭ���ͣ�����Ԫ��������[]int(������Ƭ),���������뵽ѧϰ�����c�еĶ�ά����,
int[4][3];֮ǰһֱ����������:����һ4*3�Ķ�λ���飬�������û����������Ϊ��������Ϊǡ��:����һ������3��Ԫ�ص�һά���飬����Ԫ��������
һ��int[4]��һά����


38.Mingw Mingw-w64 TDM-GCC֮�����������ѡ��
��ͬ��:
һ�� ���Ƕ������ڱ�������WindowsӦ�ó���Ĺ�������
���� ���Ƕ��ǻ���gcc�ġ�

1. MinGWӦ�������ȵ����ġ�ֻ֧������32bit���򣬲�����ʹ��
2. MinGW-w64��Ŀ�������ΪMinGW��һ����֧���������������Ѿ�������չ����֧������32bit��64bit�ĳ����Ƽ�ʹ�ã�
3. TDM-GCC�Ƕ�MingGW-w64�Ĺ��ߴ��

39.****����Mingw-w64���ȶ�,�Ҳ����׳���golang�ײ�ҲҪ�õ������Ծ�ѡ��Mingw-w64��Ϊ֮���Windowsƽ̨��gun��������****
���أ�http://www.mingw-w64.org/doku.php/download (mingw-w64-install.exe)
��mingw-w64-install.exe
ѡ��ƽ̨****�ⲽ����Ҫi686,��32λƽ̨
x86_64��64λƽ̨,ƽ̨����Ҫ�����������Ժ��ܹ�ͨ��gcc��������ĳ���λ����Ҳ��golang��cgoƽ̨�ܲ���������32bit��64bit��ǰ��
Ŀǰ������mingw-w64 ��-m32��������32λ����ʧ�ܣ���Ϊmingw-64ֻ����64λ�Ŀ⣬���԰�װmingw-w64 i686����ȡ32λ��


40.���ǽ����һ���������ˣ�golang�������32λ����ʱ��ֻҪ�õ���cgo�ͱ��벻����������ʾ���ͻ������Ϊ���ص�mingw-64��64λ�ģ���û��32λ�Ŀ⣬
����취:
��װMingw-w64��32λ��(i386)
��i686-w64-mingw32-gcc.exe���ڵ�Ŀ¼��ӽ���������
set GOARCH=386
set CGO_ENABLED=1
set CC=i686-w64-mingw32-gcc
set CXX=i686-w64-mingw32-g++
�Ϳ����ˣ�Ϊʲô����CC���ó�gcc?
��Ϊϵͳ��ͬʱ��װ��mingw-w64��64λ���32λ�棬���Ҷ�ͬʱ�����˻���������˭�Ļ�����������ǰ��gcc����˭�ģ�����Ϊ������
64Ϊ��gcc g++:x86_64-w64-mingw32-gcc x86_64-w64-mingw32-g++
32λ��gcc g++:i686-w64-mingw32-gcc i686-w64-mingw32-gc++
��ʱ����


41.����������windows�ģ����ƽ̨��linux,Ҫ��linux64�����32λ���򣬾Ͳ�����windows��ô���ӣ�ֻ��Ҫ��װ32λ�����п⼴�ɣ�
��ʵwindowsҲ����������������gcc -m32 ������ȥ����32λ�⣨Ӧ�û�Ҫͨ��-L����ѡ��ȥ�޶�����û�гɹ�����ubuntu��װ32λ���п�:
sudo apt-get install libc6-dev-i386
centos:
yum install libgcc-dev.i686


42.��������Ū����golang��Gmssl,�ұ������GMSSL�õ���libssl.a libcrypto.a,�����Ծ�̬��ķ�ʽ���ӣ�����һֱ���Ӳ��ϣ����������⵼�µ�
1.Gmssl��������build.go����д���˱������
#cgo darwin CFLAGS: -I/usr/local/include
#cgo darwin LDFLAGS: -L/usr/local/lib -lcrypto -lssl
1.darwin�����޶���ƽ̨,������linux�ϱ��룬Ӧ�øĳ�linux
2.��Ȼ��ָ�������ӿ�·����Ҫ���ӵĿ����ƣ����������Ǳ������.a����Ŀ¼��һ�£����²������ӣ�������Ҫָ����ȷ��Ŀ¼
3.-lssl -lcryptoĬ�����Ӷ�̬�⣬����֮ǰϵͳ������openssl�⣬������ȥ����openssl�Ŀ⣬û��������ȷ��Gmssl��
4.���Ӿ�̬����Ҫָ�����·�� /usr/lib/libssl.a /usr/lib/libcrypto.a������ȷ����
5.libssl.a �� libcrypto.a��˳�����ң�����Ҳ���Ӳ���

43.linux�µ�go env���ú�windows��ͬ,win��ֱ��set GOARCH=386����linux�������ò���Ч�������ڱ���֮ǰָ��:GOARCG=386 go build main.go
���о���42���������⣬����ͨ��CGO_LDFLAGS="/usr/lib/libssl.a /usr/lib/libcrypto.a" go build main.go������

44.������������˼���ʱ�䣬�ڸ���̨дһ������ʱ����Ҫ�õ�����Gmssl�⣬����������Ǹ�nodejsʹ�õģ�node������openssl��ģ�������Ϊ���ԭ��
���µ����⣬Gmssl��openssl��һ����֧��ֻ����Gmsslʵ����һϵ�й����㷨���������ǰ����Ĺ���������һ����(��������ȫ�ֱ�����)��nodeȥ��������������soʱ��so����
���õ��ĺ���Ĭ�����ӵ�openssl�Ķ�̬�����ˣ�����openssl����û�й��ܵ���Բ���ߣ����Ծ����ɲ�����Բ���ߡ����µ���ʧ�ܡ�
��ô��������so����ĺ������ӵ�Gmssl�Ŀ��ϡ��Ͳ�һ���������-Wl,-Bsymbolic
Ӧ�ó���������ӵ�ʱ�򣬶�̬����ȫ�ֱ������壬���ᱻӦ�ó�����ͬ����ȫ�ֱ��������ǡ�����Ҳ������ˣ��ڶ�̬�����޸�A����ʱ��Ӧ�ó����е�AҲ�����˱仯��
Bsymbolic��ʾǿ�Ʋ��ñ��ص�ȫ�ֱ��������������壬�����Ͳ�����ֶ�̬���ӿ��ȫ�ֱ������屻Ӧ�ó���/��̬���ӿ��е�ͬ������������ˣ�






