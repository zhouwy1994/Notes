======================Study on UnitTet===========================


***********************************************************CMocka*********************************************
1.�ڴ�й¶���ڴ����
�ڴ�й¶(memory leak)����������ϵͳ������ڴ��ڳ������֮��û���ͷ�
�ڴ����(memory overflow)�����������ڴ�ʱ��ϵͳû���㹻���ڴ��ṩ�����յ������
2.����ʱ�����Ҫdefine������ʹ��-Dѡ�� eg:gcc -c malloc -o allo.o -D UNIT_TESTING
3.��Ҫʹ��cmocka�Ŀ⺯��������Դ�ļ��а�������ͷ�ļ�
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>s
#include <cmocka.h>
4.nm gcc���߿��Բ鿴�г�Ŀ���ļ��ķ����嵥 eg:nm -a allo.o 

cmocka��ʹ��
����ʱ��ָ��cmocka�⣬gcc source.c -lcmocka -L /usr/local/lib
Ҳ�����ڱ����ʱ�����cmocka.c

�����Ҫʹ�õ�cmocka������ڴ��⹤�ߣ��ڱ���ʱԴ�ļ���Ӧ���stdlib.h��ֱ��ʹ��cmocka��ͷ�ļ�
����ʱָ��-D UNIT_TESTING

cmocka��main�������еĲ��Ժ�������ӦΪvoid **state,��Ӧ��Ϊvoid,���Ժ�����ָtest_fun��comcka_unit_test(test_fun)
��̬�����Ĳ��Է�������Դ�ļ���ʹ��
#ifdef UNITTEST 
#define static
#endif//UNITTEST
��static�ÿգ�Ȼ���ٲ����ļ�ͷ�ļ���extern unit_test();����Ӧ��
����������ֵ��ǰԤ�貢ѹջwill_return(fun_c, value)
��fun_c��ʹ��mock_type(type)����ջ�е�ֵ,PS��typeΪC�����г����������ͣ�int double��
will_return �� mock_type���ǳɶԳ���
һ�㶼����ģ�⺯����
����ϵͳ����open read write connect
��ʱ��Ҫ��ϵͳ���ý���ģ��
��ʱ���ú���ָ��ָ��̬����ţ�dynamic library symbol)ϵͳ�����ڵµ�ַ��ʵ��ϵͳ����
void*dlsym(void*handle,constchar*symbol)
��dlopen����������ָ��ģʽ��ָ���Ķ�̬���ӿ��ļ���������һ�������dlsym�����ĵ��ý��̡�ʹ��dlclose������ж�ش򿪵Ŀ⡣
����ʱ��-ldl�����ӵ���Ӧ��

Unit Test �ܽ�
��Ԫ��������������ز����ٵĻ��ڣ���Ԫ�������ڰ׺в���
������Եķ��ࣺ
��������ṹ���㷨������
1.�׺в��ԣ��ṹ����/����Ա���ԣ�
2.�ںв��ԣ����ܲ���/�����������ԣ�

�����Ƿ�ִ�б������
1.��̬����
2.��̬����

���ڲ��ԵĲ�ͬ�׶�������
1.��Ԫ���ԣ�ģ����ԣ�,�ӿڲ��ԣ�·������
2.���ɲ��� ���ӿڣ�·�������ܣ�����
3.ϵͳ���� ���ܣ����ܣ���׳�ԣ��ȶ��ԣ�ѹ������
4.���ղ��� �����û�ִ��

��Ԫ�����ֳ�Ϊģ����ԣ���Ҫ���������С��Ԫ���в��ԣ��������Ƶ���С��Ԫ
C������	Java����
��Ԫ���Ե�ģ�������ǲ���ִ�еģ���Ҫ����Ĳ�����������

��Ԫ���Ե����ʣ�
1������ģ�飺���Ե��ñ���ģ��ĵ�Ԫ
2��׮���������Ա����⺯�����õĺ���
3��������������Ϊĳ������Ŀ������Ƶ�һ��������롢ִ�������Լ�Ԥ�ڽ����
�Ա����ĳ������·�����ʵ�Ƿ�����ĳ���ض����󡣸�����⣺�������Ǳ�д
�Ĳ��Ժ���test_leak_memory.c

��Ԫ���Ե�Ŀ��

1.Ϊģ���������ж����
֤�����Ի����ͱ��ⵥԪ�ǿ��õ�
3.Ϊ������Զ����
֤����ƹ��˵�����ж�Ӧ�Ĺ��ܺ�����ָ���Ƿ��ܹ�ʵ��
5.Ϊ������Զ����
֤�����û������Ӧ����������
7.Ϊ����������������
��ϵͳ�����ܡ���ȫ�ԡ������ԵĽǶ�Ϊ������ЩҪ���ϵͳ�ƶ��Ĳ�������
9.Ϊ���븲�Ƕ����

��Ԫ���Ե�����
1.ģ��ӿڲ���
2.ģ��ֲ����ݽṹ����
3.ģ��߽���������
4.ģ�������ж���ִ��ͨ·����
5.ģ��ĸ���������ͨ·����
6.ģ��ķǷ�����
7.�������ò���	
8.ϵͳ���ݲ���

���븲�ǣ�
�����д��뱻ִ�еı���
���븲�ǵĶ���
1.�������ǣ�ÿһ�������Ƿ�ִ��
2.��串��(�и���)��ÿһ������Ƿ�ִ��
3.��֧���ǣ�ÿһ���ж���֧�Ƿ�ִ��
4.��������
5.·�����ǣ�������ϸ��ǣ��������������е�ÿһ����϶�����һ��

��Ԫ���Թ��ߣ�cmocka
��Դ�밲װ
���븲���ʣ�gcov
sudo apt-get -y install python-pip
sudo pip install gcovr

cmocka��ʹ��
1.�ڴ������飺cmkckaʹ��_test_malloc _test_alloc _test_free�ȴ���malloc alloc free�ȣ�����ڴ�й¶
2.ģ�⺯���еķ���ֵ��ģ�������mocka���ص㣬Ҳ���ó���
3.����������ֵ��
4.��ͬ���͵ĺ궨����֤
5.ϵͳ����ģ��
6.ǿ���assert������֤

cmocka API��
1.Running Tests ���������Ե����к���
2.Standard Assertions �Ա�׼assert��һ���滻��������ֹ���Ա�assert���
3.Checking Parameters ���ڶԺ��������ļ��
4.Mock Objects ����mock���󣬳�����mock�����ķ��أ�ʵ�ַ�ʽ��Checking Parameter����
5.Dynamic Memory Allocation ���ڶ��ڴ�ļ��
6.Assert Macros �����˳��õĶ���
��Ԫ���Ե����ⶨλ
1.Assert�����Ԥ�ڲ���
��������ݲ��Խ������Դ��Ͳ��������𲽶�λ
2.�δ���
����������м�printf�𲽽��е���
gdb����
3.�ڴ�й¶
����������ڴ��������ͷŵĴ����𲽶�λ

��Ը����Ӧ��ע��
�����޸�Դ�룬������ͷ�ļ�

GlusterFS Source
expect_assert_failure(fun);����������Ժ���func���û�ʧ�ܷ���
һ����REQUIRE(p) ENSURE(p)���ʹ��,��������Ҳ��һ�ֶ���
����ĳ������ʱ,һ��Ҫ���䷵��ֵ���ж����ж�,�ж���ʵ��ִ��Ԥ�ڵĽ��

test_func_unittest.c�о�����func��ͷ�ļ�����cmockaͷ�ļ�����ͷ

mock����ָ�����͵���mock_type(type); ��ע�뺯��will_return(func, val);
��������������mock()����ע�뺯��will_return_always(func, val)���

���븲���ʹ���:gcovr
��ʵglusterfs������make check����ʱ�Ѿ�����-lcmock --coverage�Ȳ������Ա�����Ĵ���ֱ��
��������븲����
gcovrʹ��
gcovrֻ��ͨ����ִ�г���ȥ���Դ��븲���ʣ�����˵ֻ�д����ǲ��ܲ��Դ��븲���ʵ�
Ҳ�������еĿ�ִ�г��򶼿���Ϊ����
ֻ��ͨ���ض��Ĳ�����������Ķ������ļ��ſɲ���
source:coverage.c
���Ҫ����coverage.c�ĸ�����
���� gcc  -fprofile-arcs -ftest-coverage -fPIC -O0 coverage.c -o main
�Ϳ����ɿ�ִ�г���main
��ʱ�Ϳ���gcovr���������Ը�����
�鿴��ǰĿ¼�µĴ��븲���ʣ����Խ���ų�unittest���룩
sudo gcovr -r .  -e .*unittest.* 
�鿴��ǰĿ¼�µķ�֧�����ʣ����Խ���ų�unittest���룩
sudo gcovr -r . �Cb -e .*unittest.* 
���ΪHTML��ʽ�ĸ�����������Խ���ų�unittest���룩
sudo gcovr -r . -e .*unittest.* --html -o thunderfs_unittest_general.html
���ΪHTML��ʽ����ϸ��������Խ���ų�unittest���룩
sudo gcovr -r . -e .*unittest.* --html --html-details -o thunderfs_unittest_detail.html 












***********************************************************GoogleTest*********************************************
GoogleTest:���gtest,��google���c/c++��һ��UnitTest���ߣ����Windows��Linux��Mac��֧�֣���һ����ѿ�Դ�ĵ�Ԫ����framework
��ȡgtestԴ��:git clone  git@github.com:google/googletest.git
Ŀ¼feature:
make:���Unix/Linuxƽ̨�Ĳ��Կ⣬����Ŀ¼make�������ɾ�̬��.a�ļ�������֮����Ա�������
msvc:��Ҫ���Windowsƽ̨��VistualC++
xcode:��Ҫ���Macƽ̨��Xcode
codegear:Borland C++ Builder���Զ����߽ű������Ƽ�ʹ�ã���һ��C++ƽ̨
CMakeLists.txt��Google Test��Ŀ¼�е�CMake���Ƽ�����
include:gtest��ͷ�ļ�Ŀ¼����Ҫ��
src:��Ԫ��������Ҫ��Դ�ļ�����Ҫ��
test:
samples:gtest�����ļ���������������samples~sample10



������make/Makefile�ļ������ݣ����������ݿɴ�ŷ�����gtest��ʹ���Լ�������ԭ��:
# A sample Makefile for building Google Test and using it in user
# tests.  Please tweak it to suit your environment and project.  You
# may want to move it to your project's root directory.
#
# SYNOPSIS:
#
#   make [all]  - makes everything. //make��������Ŀ���ļ�
#   make TARGET - makes the given target. //��make��ͬtarget����ָ����Ŀ���ļ�
#   make clean  - removes all files generated by make. //�����ǰĿ¼���ɵ������ļ�Makefile�ļ�����

# Please tweak the following variable definitions as needed by your
# project, except GTEST_HEADERS, which you can use in your own targets
# but shouldn't modify. 
#����GTEST_HEADERS�����⣬���������㶼�����޸ģ������ʹ�ã����ǲ�Ӧ���޸�Ŀ�������

# Points to the root of Google Test, relative to where this file is.
# Remember to tweak this if you move this file.
#..��gtest�ĸ�Ŀ¼������ֻ����Ե�ǰĿ¼���ԣ�������Projice Dirtroy�ı���
#��Ŀ¼ҲҪ������Ӧ���޸�
GTEST_DIR = .. 

#��Ŀ¼���û���Դ�ļ�Ŀ¼�����Ŵ����Դ�ļ�(xxx_src.cc)��Ҳ���Էŵ�Ԫ���Ե�Դ�ļ�(zzz_unittest.cc)
# Where to find user code.
USER_DIR = ../samples

# Flags passed to the preprocessor.
# Set Google Test's header directory as a system directory, such that
# the compiler doesn't generate warnings in Google Test headers.
#��־���ݸ�Ԥ�������� ��Google Test��ͷĿ¼����ΪϵͳĿ¼���Ա������������Google����ͷ�����ɾ��档
CPPFLAGS += -isystem $(GTEST_DIR)/include

# Flags passed to the C++ compiler.
#C++����ѡ����Լ��޸�
CXXFLAGS += -g -Wall -Wextra -pthread

# All tests produced by this Makefile.  Remember to add new tests you
# created to the list.
#����������ɵĵ�Ԫ���������ɵ�Ŀ���ļ�(��ִ���ļ�)������ж�����������б���ʽ(�������samples/sample1.cc�ĵ�Ԫ����)
TESTS = sample1_unittest

# All Google Test headers.  Usually you shouldn't change this
# definition.
#����Gtest������ͷ�ļ�����Ӧ��ȥ�޸���
GTEST_HEADERS = $(GTEST_DIR)/include/gtest/*.h \
                $(GTEST_DIR)/include/gtest/internal/*.h

# House-keeping build targets.
#��Ҫ����(����)��Ŀ�꣬����ж������д���б�
all : $(TESTS)

#��Ҫ������ļ�
clean :
	rm -f $(TESTS) gtest.a gtest_main.a *.o

#����������(gtest.a and gtest_main.a.)
# Builds gtest.a and gtest_main.a.

# Usually you shouldn't tweak such internal variables, indicated by a
# trailing _.
#������gtest�����Դ�ļ�����Ӧ��ȥ�޸�
GTEST_SRCS_ = $(GTEST_DIR)/src/*.cc $(GTEST_DIR)/src/*.h $(GTEST_HEADERS)

# For simplicity and to avoid depending on Google Test's
# implementation details, the dependencies specified below are
# conservative and not optimized.  This is fine as Google Test
# compiles fast and for ordinary users its source rarely changes.
#���������ɹ�����(��̬��.a)����Ҫ��ʵ��ϸ�ڣ�����������ڽ���û�ֻ�ù����Լ��Ĳ�����������
#�����ù���gtest��ʵ��ϸ��(gtest.a gtest_main.a)

gtest-all.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest-all.cc

gtest_main.o : $(GTEST_SRCS_)
	$(CXX) $(CPPFLAGS) -I$(GTEST_DIR) $(CXXFLAGS) -c \
            $(GTEST_DIR)/src/gtest_main.cc

gtest.a : gtest-all.o
	$(AR) $(ARFLAGS) $@ $^

gtest_main.a : gtest-all.o gtest_main.o
	$(AR) $(ARFLAGS) $@ $^

# Builds a sample test.  A test should link with either gtest.a or
# gtest_main.a, depending on whether it defines its own main()
# function.
#���²����û�Ӧ���޸ĵĵط��������ǲ��������Ĳ����ı�����̣�һ�������ĵ�Ԫ���ԣ�Ӧ��
#����Դ�ļ�(sample1.cc)�Ͳ�������Դ�ļ�(sample1_unittest.cc)��sample1_unittest.cc��������Ӧ��
#��Ƶ�����
sample1.o : $(USER_DIR)/sample1.cc $(USER_DIR)/sample1.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1.cc

sample1_unittest.o : $(USER_DIR)/sample1_unittest.cc \
                     $(USER_DIR)/sample1.h $(GTEST_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $(USER_DIR)/sample1_unittest.cc

sample1_unittest : sample1.o sample1_unittest.o gtest_main.a
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -lpthread $^ -o $@

*/

Gtest �Ļ�������:
����:

ÿһ�ֵ�Ԫ���Թ��߶����ṩһ�׶��Թ��ߣ����Բ�����һ����򵥸�Ч��ʹ�����
��ֵ�жϷ�ʽ
gtest�Ķ��Խ���ɷ�Ϊ����:
1.�ɹ�
2.������ʧ��
3.����ʧ��(��������ʧ�ܣ�������ִֹ�У����������ִ��)

Google Test���������ƺ������õĺ꣬������ʧ��ʱ��Google Test���ӡ���Ե�Դ�ļ����к�λ���Լ�ʧ����Ϣ��Ҳ�����Զ����ӡ��Ϣ
ASSERT_EQ(x.size(), y.size())
��ASSERT_* ��ͷ���������Թ��ϣ�������ʧ��ʱ����ֹ��ǰ���ܣ���Ҳ����һ�����⣬������ܻ���Ϊ��ֹ���ж�û�û�����Դ�������ڴ�й¶
��EXPECT_* ��ͷ���Ƿ������Թ��ϲ�����ֹ��ǰ���ܡ�ֻ�ǲ�����ʾ��Ϣ��

ͨ��EXPECT_* ����ѡ����Ϊ���������ڲ����б������һ�����ϡ����ǣ�ASSERT_*�����������Ķ���ʧ��ʱ����ִ�У���Ӧ��ʹ������

����һ��ʧ�ܵ�ASSERT_*���شӵ�ǰ�Ĺ������������������������֮�������ܻᵼ�¿ռ�й©������©�������ʣ������ܻ���ܲ���
ֵ���޸��� - �������ס��������˶��Դ���֮�⻹��һ���Ѽ��������

�����Ҫ�Զ����ʧ����Ϣ��ֻ��ʹ��<<�������������������������н��������:
ASSERT_EQ(x, y) << "x should eq y";
ֻ����ASSERTʧ��ʱ�����ʧ����Ϣ

��������:
Fatal assertion	Nonfatal assertion	Verifies
�ж����(True or Flase)
�����Ķ���					�������Զ���				     ��֤
ASSERT_TRUE(condition);		EXPECT_TRUE(condition);		condition is true
ASSERT_FALSE(condition);	EXPECT_FALSE(condition);	condition is false

������ֵ�Ƚ��ж�:
�����Ķ���				�������Զ���				��֤
ASSERT_EQ(val1 ,val2);	EXPECT_EQ(val1 ,val2);	val1 == val2
ASSERT_NE(val1 ,val2);	EXPECT_NE(val1 ,val2);	val1 != val2
ASSERT_LT(val1 ,val2);	EXPECT_LT(val1 ,val2);	val1 < val2
ASSERT_LE(val1 ,val2);	EXPECT_LE(val1 ,val2);	val1 <= val2
ASSERT_GT(val1 ,val2);	EXPECT_GT(val1 ,val2);	val1 > val2
ASSERT_GE(val1 ,val2);	EXPECT_GE(val1 ,val2);	val1 >= val2

�ַ����Ƚ�

�����еĶ��ԱȽ�������C�ַ��������Ҫ�Ƚ�����string������;EXPECT_EQ��EXPECT_NE�Լ��������档

�����Ķ���						�������Զ���					��֤
ASSERT_STREQ(str1 ,str2);	EXPECT_STREQ(str1, _str_2);			����C�ַ���������ͬ������
ASSERT_STRNE(str1 ,str2);	EXPECT_STRNE(str1 ,str2);			����C�ַ����в�ͬ������
ASSERT_STRCASEEQ(str1 ,str2);	EXPECT_STRCASEEQ(str1 ,str2);	����C�ַ���������ͬ�����ݣ��������
ASSERT_STRCASENE(str1 ,str2);	EXPECT_STRCASENE(str1 ,str2);	����C�ַ������в�ͬ�����ݣ��������������

һ���򵥵Ĳ�������:
gtest�еĲ���������TEST()������ʵ��
Ҫ����һ�����ԣ�

ʹ��TEST()�궨����������Ժ�������Щ�ǲ�����ֵ����ͨC ++�������ڴ˺����У���ͬҪ�������κ���Ч��C ++��䣬
��ʹ�ø���Google Test���������ֵ�����Խ���ɶ��Ծ���; ��������е��κζ���ʧ�ܣ�������������������߲��Ա�����
����������ʧ�ܡ��������ɹ��ˡ�
TEST(test_case_name, test_name) {
 ... test body ...
}
TEST(test_case_name, test_name)����һ�������ǲ������������ƣ��ڶ��������ǲ��������еĲ������ơ����������Ʊ�������Ч��C ++
��ʶ�����������ǲ�Ӧ�����»��ߣ�_������һ������Ӧ���ɱ����Եĺ������Ƽ�Test�ֶΣ��ڶ������������ǲ�������˵��
int Factorial(int n); // Returns the factorial of n ����һ������n�Ľ׳˵ĺ���
������һ����������:
// Tests factorial of 0.
TEST(FactorialTest, HandlesZeroInput) {
  EXPECT_EQ(1, Factorial(0));
}
//�ò�������Ϊ����Factorial��������������Ϊ0ֵ����

Test Fixtures













































