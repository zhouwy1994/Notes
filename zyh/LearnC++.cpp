1.Gcc����c/c++����ʱ,Ĭ���Ƕ�̬���ӿ⣬����뾲̬���ӣ��ɼ�ѡ��-Wl,-Bstatic��ѡ����Ҫ��̬���ӵĿ⣬����::���Ҫ�ָ���̬���ӷ�ʽ
-Wl,-Bdynamic����Ȼ����ȫ�þ�̬���ӷ�ʽ�����еĿ���û�о�̬��ģ����Խ�����ʧ��
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












