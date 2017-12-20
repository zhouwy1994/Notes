============================================================Study On UnionStream =================
										周武毅 2017/10/17
==================================================================================================

dispatcher_process_func m_p_msg_process_func; //消息分发器
消息分发器，UnionStream中比较重要的一个重要函数，客户端与服务器进行通信时，接受到的消息经过NET_MSG_H封装并加密之后的
一段字符，接收端收到消息并解密，将MSG里面的pClient(消息来自的客户端)，cmd，pBuffer，pBufferLength传入消息分发器，在由消息分发器解析命令，
以判断调用哪个函数去执行命令，可能消息分发器里还存在另一个分发器

消息封装:
NET_MSG_S(request_oo_database_open_user, REQUEST_DATABASE_OPEN_USER)
link_list_add_node_net_msg_attribute_6((*pPMsg)->m_msg->m_p_attributes,
(*pPMsg)->m_msg, "user_name", BASE_DATA_TYPE_STRING, NULL, NULL, NULL);
link_list_add_node_net_msg_attribute_6((*pPMsg)->m_msg->m_p_attributes,
(*pPMsg)->m_msg, "password", BASE_DATA_TYPE_STRING, NULL, NULL, NULL);
link_list_add_node_net_msg_attribute_6((*pPMsg)->m_msg->m_p_attributes,
(*pPMsg)->m_msg, "ident", BASE_DATA_TYPE_INT, NULL, NULL, NULL);
link_list_add_node_net_msg_attribute_6((*pPMsg)->m_msg->m_p_attributes,
(*pPMsg)->m_msg, "admin_req", BASE_DATA_TYPE_BOOL, NULL, NULL, NULL); //是否是管理员请求
link_list_add_node_net_msg_attribute_6((*pPMsg)->m_msg->m_p_attributes,
(*pPMsg)->m_msg, "version", BASE_DATA_TYPE_STRING, NULL, NULL, NULL);
link_list_add_node_net_msg_attribute_6((*pPMsg)->m_msg->m_p_attributes,
(*pPMsg)->m_msg, "multi_key", BASE_DATA_TYPE_LONGLONG, NULL, NULL, NULL);
link_list_add_node_net_msg_attribute_6((*pPMsg)->m_msg->m_p_attributes,
(*pPMsg)->m_msg, "sender", BASE_DATA_TYPE_INT, NULL, NULL, NULL);
msg_attribute_set_string(net_msg_get_attribute((*pPMsg)->m_msg, "version"), "");
msg_attribute_set_int(net_msg_get_attribute((*pPMsg)->m_msg, "sender"), MSG_SENDER_CLIENT);
(*pPMsg)->m_msg->m_recv_cmd = REPLY_DATABASE_OPEN_USER;
}

以下是NET_MSG_S的定义，请注意最后结尾是没有'}'的，所以上面的部分都回加到init_函数内
#define NET_MSG_S(name, cmd) void destroy_##name##_msg_t(name##_msg_t** pPMsg){ \
	net_msg_with_out_stream_destroy(&(*pPMsg)->m_msg); \
} \
void destroy_##name##_msg_t_with_out_stream(name##_msg_t** pPMsg){ \
	net_msg_with_out_stream_destroy(&(*pPMsg)->m_msg); \
} \
void serialize_##name##_msg_t(name##_msg_t* pMsg){ \
	serialize_net_msg(pMsg->m_msg); \
} \
void de_serialize_##name##_msg_t(name##_msg_t** pPMsg, const char* pBuffer, int length){ \
	init_##name##_msg_t(pPMsg); \
	de_serialize_net_msg((*pPMsg)->m_msg, pBuffer, length); \
} \
void init_##name##_msg_t(name##_msg_t** pPMsg){ \
	CALLOC(*pPMsg, name##_msg_t); \
	net_msg_init(&(*pPMsg)->m_msg, cmd, 0);

函数:serialize_request_smart_contract_box_users_msg_t(pAddUserReq); //将net_msg_t结构体虚拟化成seng可以发送的消息体，
存在于pAddUserReq->m_msg->m_p_stream->m_buf中

C2S 模式发送消息:
sy_client_get_net_protocol_send_msg(oo_database_client_get_p_client(pDataBaseClient))(oo_database_client_get_p_client(pDataBaseClient),
		pInsertRowReq->m_msg->m_p_stream->m_buf, pInsertRowReq->m_msg->m_p_stream->m_length));

1.Client:首先将自己的Client作为参数发送到Server，这样方便Server获得Client信息，以便于回复处理后的消息
2:消息的buffer
3:消息的长度
一般消息都封装成struct net_msg_t 类型，消息主体放到stream->m_buf,消息长度放到m_length

C2S 模式接收消息:
sy_client_peer_recv_msg_content_union_protocol(oo_database_client_get_p_client(pDataBaseClient),
			&pRecvContent, &recvLength))
接受消息函数一般都根据需求(需要接受的消息类型)进行封装，不论怎么封装里面总是包含
1. union_sy_recv_msg_header //接受消息头部
2. union_sy_recv_msg_header_completed //接收消息头部完成
3. union_sy_recv_msg_body //接受消息主体
4. union_sy_recv_msg_completed //接收消息主体完成

而头部与消息主体的封装，一般在 send函数内部
接受到消息后一般要进行解密sy_client_get_decryption_func，check_valid_modify_msg 检查校验篡改， 才可正常识别

树形数据结构:
typedef struct tree_n_t {
	tree_node_t* m_root;
	tree_node_t* m_end;
	init_func m_init_data_func;
	destroy_func m_destroy_data_func;
	BOOL m_is_asy;
	CRITICAL_SECTION m_asy_section; //线程锁
	void* m_p_attach_data;
}tree_n_t;

typedef struct tree_node_t {
	void* m_data; //任意数据类型
	vector_array_t* m_children; //tree_node_t*
	tree_node_t* m_parent;
	tree_n_t* m_tree;
	int m_generation; //辈分 等于父辈+1
	int m_index; //序列值 在同一辈分中的序列 也就是在link_list中的序列
}tree_node_t;

每个节点都拥有若干个孩子节点，用数组vertor_array_t 表示，一个节点可以拥有一个父亲但是可以有多个孩子
vector_array_get_element_lexer_tree_node(
			pLexerTree->m_tree->m_root->m_children, syntaxUnitIndex); //获取root的所有孩子节点
孩子节点，索引index

存在一个问题，智能合约盒子添加的用户并没有插入数据库，只是在智能合约层面上存在用户，box命令并没有查询数据库，重启
SmartContract后用户消失

消息分发，接受消息函数union_sy_recv_msg_completed，完成此函数证明接受网络消息已经完成，在该函数结尾有一个通用的消息分发函数
int ret = dispatcher_process_net_servser(pOperatorData->m_p_socket->m_p_client, packageType, pOperatorData->m_buffer, length);
上面函数在common/net/net_server_dispatcher.c中，以下是该函数的尾部
case REQUEST_SOCKET_KEY:
		process_request_socket_key(pClient, pBuffer, length);
		break;
	case REPLY_SOCKET_KEY:
		ret = process_reply_socket_key(pClient, pBuffer, length);
		break;
	default:
		//printf("pClient:%p\n", pClient);
		ret = sy_client_get_msg_process_func(pClient)(pClient, cmd, pBuffer, length);
		break;
	}
	return ret;
}
ret = sy_client_get_msg_process_func(pClient)(pClient, cmd, pBuffer, length);
这条才是最重要的，它会根据不同Client得到各自的消息分发函数，再将命令分发出去

Database结构
User:用户 -----> Schema 数据库 ---->Table表 -----> Attribute 属性(字段)
用户:
typedef struct language_runtime_db_user_t {
	char* m_p_user_name; //用户名
	char* m_p_password; //密码
	hash_map_t* m_db_schemas; //用户所有数据库 const char* pSchemaName, language_runtime_db_schema_t* pSchema
}language_runtime_db_user_t;
数据库:
typedef struct language_runtime_db_schema_t {
	char* m_p_schema_name; //库名称
	language_runtime_db_user_t* m_p_user; //所属用户
	hash_map_t* p_db_tables; //数据库所有数据表 const char* pTableName, language_runtime_db_table_t* pTable
}language_runtime_db_schema_t;
表:
typedef struct language_runtime_db_table_t {
	char* m_p_table_name; //表名称
	language_runtime_db_schema_t* m_p_schema; //所属数据库
	hash_map_t* p_db_attributes; //数据表所有属性 const char* pAttributeName, language_runtime_db_attribute_t* pAttribute
}language_runtime_db_table_t;
属性(字段)：
typedef struct language_runtime_db_attribute_t {
	char* m_p_attribute_name; //属性名称
	language_runtime_db_table_t* m_p_table; //所属数据表
	char* m_info; //属性信息
}language_runtime_db_attribute_t;

请求数据库操作函数在database/server/user_option/oo_database_user_option.c中 恢复也在当中



基本数据结构分析:

===============================================================================================================
typedef struct vector_array_t {
	init_func m_init_data_func; //元素初始化函数，可为NULL
	destroy_func m_destroy_data_func; //元素销毁函数，可为NULL
	char* m_buffer; //装载元素的容器，装载的是元素的指针形式
	int m_count; //元素的个数
	int m_buffer_size; //buffer 大小
	BOOL m_raw_memery; //是否是原始内存操作
	BOOL m_is_asy; //是否线程安全
	CRITICAL_SECTION m_asy_section; //线程锁
}vector_array_t;

分析:以上结构实现了类似C++中向量(vector)的数据结构，但是并无push_back,pop_fornt等方法
以上结构最为重要的是buffer，它是一个用来装元素地址的容器，结构如下所示
				  -------------------------------------------------------
char *buffer----->| elementAddr| elementAddr | elementAddr | elementAddr |
				  --------------------------------------------------------
				  <sizeof(vode*)>4byte
取第index位置元素地址:void** pPParam = (void**)((*pPVectorArray)->m_buffer + index * sizeof(void*));
也可用((void**)pVectorArray->m_buffer)[index] 来取得,解析:由于m_buffer为char型指针，如果m_buffer[index]
只会偏移index个地址，如果将char*强转成(void**)则((void**)pVectorArray->m_buffer)[index]将偏移index * sizeof(void*)个地址
void**强转偏移sizeof(void*)个地址,(void*)强转只偏移1个地址

得出结论:buffer就是用来装取元素的地址的容器，以下为该结构几个重要的函数
void vector_array_init(vector_array_t** pPVectorArray, init_func pInitDataFunc, destroy_func pDestroyDataFunc, BOOL isAsy, BOOL isRawMemery)；
初始化函数，initFunc,destroyFunc可以为NULL，是这样初始化元素时就不使用函数，直接CALLOC_raw
void vector_array_destroy(vector_array_t** pPVectorArray);
销毁数组中所有元素(根据销毁函数或则FREE)和数组本身
void vector_array_re_size(vector_array_t* pVectorArray, int length);
重置数组大小，如果指定大小大于数组本身长度，则数组realloc，如果小于数组本身长度，则销毁元素来达到效果，慎用
extern void vector_array_clear(vector_array_t* pVectorArray);
调用vector_array_re_size(vector, 0);
extern BOOL vector_array_delete_by_index(vector_array_t* pVectorArray, int index);
extern int vector_array_get_element_index(vector_array_t* pVectorArray, void* pElement);

外部访问三个重要宏函数:
#define VECTOR_ARRAY_SET_ELEMENT_1_S(name, type, type0) \
type* vector_array_set_element##name##_1(vector_array_t* pVectorArray, int index, type0 arg0)
在指定的index装入元素，需指定初始化元素所要用到的参数类型，调用者不用关心数组的长度有多大，因为长度会
根据指定的index作调整
#define VECTOR_ARRAY_GET_ELEMENT_S(name, type) \
type* vector_array_get_element##name(vector_array_t* pVectorArray, int index)
获取指定位置上的元素，没有参数个数限制，只需指定你需要获取元素的类型type
#define VECTOR_ARRAY_INSERT_ELEMENT_2_S(name, type, type0, type1) \
type * vector_array_insert_element##name##_2(vector_array_t* pVectorArray, int index, type0 arg0, type1 arg1)
在指定位置插入元素，和SET的区别，SET是在有顺序的情况下做赋值操作，而INSERT是破坏原有顺序，需要移动数组
#define VECTOR_ARRAY_FOREACH_1_S(name) int vector_array_foreach##name##_1(vector_array_t* pVectorArray, eacher_func pEacherFunc, void* pData)
遍历数组元素，传入指定动作pEacherFunc以及参数

注:
char* m_buffer; //装载元素的容器，装载的是元素的指针形式
是怎么达到装载指针的目的
正常逻辑:
char *m_buffer = malloc(100);
m_buffer[1] = 'a'; //这时m_buffer是一个char*所以他的元素是char
((int*)m_buffer)[1] = 12345; //这时m_buffer是一个int*所以他的元素是int
int a;((int**)m_buffer)[1] = &a; //这时m_buffer是一个int**所以他的元素是int*
vector_array_t 中就是利用这一特性来达到char*buffer装载任意类型的数据
type* Data; ((type**)m_buffer)[1] = Data; //这时m_buffer是一个yupe**所以他的元素是type*
======================================================================================================================================
typedef struct link_list_node_t {
	auto_release_t m_auto_release; //自动释放
	void* m_data; //元素地址
	link_list_node_t* m_next;
	link_list_node_t* m_previous;
	BOOL m_raw_memery; //是否是原始内存操作
}link_list_node_t;

typedef struct link_list_t {
	auto_release_t m_auto_release; //自动释放
	init_func m_init_data_func;
	destroy_func m_destroy_data_func;
	link_list_node_t* m_head;
	link_list_node_t* m_tail;
	int m_length;
	BOOL m_raw_memery; //是否是原始内存操作
	BOOL m_is_asy; //是否支持异步操作
	CRITICAL_SECTION m_asy_section; //线程锁
}link_list_t;

分析:
与vector_array不同的是，link_list有一个专门盛放元素地址的link_list_node结构(这是由于双向链表的特殊结构决定的，每个节点必须包含next,previous)
所以就用link_list_node的Data专门存放元素的地址，结构如下
			   --------------       --------------       --------------
link_list----->| head(data) |<----->| node(data) |<----->| end(data) |
			   --------------       --------------       --------------
                link_list_node
重要函数:
void link_list_init(link_list_t* pLinkList, init_func pInitDataFunc, destroy_func pDestroyDataFunc, BOOL isAsy, BOOL isRawMemery)\
初始化链表
void link_list_destroy(link_list_t** pPLinkList);
销毁链表
extern link_list_node_t* get_link_list_node(link_list_t* pLinkList, mask_func pMaskFunc, void* pParams);
根据指定条件(pMaskFunc)获得节点 返回数据类型为link_list_node
extern link_list_node_t* get_link_list_node_by_index(link_list_t* pLinkList, int index);
根据指定index获得节点 返回数据类型为link_list_node
extern BOOL link_list_remove_node(link_list_t* pLinkList, link_list_node_t* pNode, link_list_node_t** pPNextNode);
根据指定node删除节点
extern BOOL link_list_remove_node_by_data(link_list_t* pLinkList, void* pNodeData, remove_func pRemoveFunc, link_list_node_t** pPNextNode); //必须要返回后面一个node 否则会断链
根据指定条件(pRemoveFunc)删除节点
extern BOOL link_list_remove_node_by_index(link_list_t* pLinkList, int index, link_list_node_t** pPNextNode); //必须要返回后面一个node 否则会断链
根据指定index删除节点
以上三个函数在删除节点事均销毁了元素
重要宏函数:

#define LINK_LIST_ADD_NODE_2_S(name, type, type0, type1) \
link_list_node_t* link_list_add_node##name##_2(link_list_t* pLinkList, type0 arg0, type1 arg1)
向链表(尾)添加节点,type 是元素类型，后面跟随构造元素所需要的参数，

#define LINK_LIST_INSERT_NODE_3_S(name, type, type0, type1, type2) \
link_list_node_t* link_list_insert_node##name##_3(link_list_t* pLinkList, int index, type0 arg0, type1 arg1, type2 arg2)
向链表指定位置(index)处插入节点,type 是元素类型，后面跟随构造元素所需要的参数，

#define LINK_LIST_FOREACH_1_S(name) int link_list_foreach##name##_1(link_list_t* pLinkList, eacher_func pEacherFunc, void* pData)
遍历链表，做一些事情pEacherFunc

和vector相比link_list没有GET宏函数，可使用get_link_list_node， get_link_list_node_by_index函数获得

======================================================================================================================================
typedef struct hash_map_element_t {
	auto_release_t m_auto_release; //自动释放
	void* m_key;
	int m_key_length;
	void* m_p_value;
	int m_value_length;
	link_list_t* m_pod_link; //所在的link_list_t
	BOOL m_raw_memery; //是否是原始内存操作

	init_func m_key_init_func;
	destroy_func m_key_destroy_func;
	init_func m_value_init_func;
	destroy_func m_value_destroy_func;

	int m_data_type_flag;
	int m_key_type_flag;
}hash_map_element_t;

typedef struct hash_map_t {
	auto_release_t m_auto_release; //自动释放
	vector_array_t* m_horzontal; //link_list_t*
	init_func m_key_init_func;
	destroy_func m_key_destroy_func;
	init_func m_value_init_func;
	destroy_func m_value_destroy_func;
	int m_count;
	BOOL m_raw_memery; //是否是原始内存操作
	BOOL m_is_asy; //是否线程安全
	CRITICAL_SECTION m_asy_section; //线程锁
}hash_map_t;

分析:
hash表较上面两种就稍微有点复杂
hash_map_t中就只有一个决定性参数 vector_array_t* m_horzontal
他是用来装link_list_t结构，这样就形成了一个二维结构的哈希表
每一个link_list_t(链表装的是hash_map_element),hash_map_element_t里面装key和value(这才是装实际数据的结构)
实际结构图如下
				  -------------------------------------------------------
hash_map----->| link_list | link_list | link_list | link_list | link_list    -------->vector_array
				  --------------------------------------------------------
					   |           |          |			  |         |
					  \|/         \|/        \|/         \|/       \|/
				   --------- ---------  ---------   ---------   ---------
			       HAElement  HAElement  HAElement   HAElement   HAElement
				   --------- ---------  ---------   ---------   ---------
					   |           |          |			  |         |
					  \|/         \|/        \|/         \|/       \|/
				   --------- ---------  ---------   ---------   ---------
			       HAElement  HAElement  HAElement   HAElement   HAElement
				   --------- ---------  ---------   ---------   ---------
				       |           |          |			  |         |
					  \|/         \|/        \|/         \|/       \|/
				   --------- ---------  ---------   ---------   ---------
			       HAElement  HAElement  HAElement   HAElement   HAElement
				   --------- ---------  ---------   ---------   ---------
插入一个hash元素时的操作方式是，先根据key生成(mapping)一个index，这个index就决定元素会落在哪条链表上，
如果此时这条链表上已经存在key，那么新key就会替换旧key，如果不存在，直接插入链表
获取元素时的过程与添加元素的过程差不多，现通过key maping出index在在相应的link_list上遍历memcpy(findkey, key, leylength);
link_list_node ---->data = hash_map_element ------>value = 查找到的数据

重要宏函数:
#define HASH_MAP_SET_ELEMENT_V_2_S(name, keyType, valueType, type1, type2) valueType* hash_map_set##name##_v_2(hash_map_t* pHashMap, keyType key, type1 arg1, type2 arg2)
添加新元素，或则是替换旧元素
#define HASH_MAP_SET_ELEMENT_P_2_S(name, valueType, type1, type2) valueType* hash_map_set##name##_p_2(hash_map_t* pHashMap, const void* pKey, int keyLength, type1 arg1, type2 arg2)
添加新元素，或则是替换旧元素
以上两个函数的区别在于有没有keyType,不包含keyTyupe则使用const void*

#define HASH_MAP_GET_ELEMENT_P_S(name, valueType) valueType* hash_map_get##name##_p(hash_map_t* pHashMap, const void* pKey, int keyLength)
根据key获取元素
#define HASH_MAP_GET_ELEMENT_V_S(name, keyType, valueType) valueType* hash_map_get##name##_v(hash_map_t* pHashMap, keyType key)
根据key获取元素

V类型的SET对应V类型的GET,P类型的SET对应P类型的GET

#define HASH_MAP_FOREACH_S(name) int hash_map_foreach##name##(hash_map_t* pHashMap, eacher_func pEacherFunc)
遍历链表做一些事情(pEacherFunc),此遍历有两层循环第一层循环 for (i < vector_array->count) {
	for (i < link_list->count) {
		pEacherFunc(do something)
	}
}
======================================================================================================================================

typedef struct tree_node_t {
	void* m_data; //任意数据类型
	vector_array_t* m_children; //tree_node_t*
	tree_node_t* m_parent;
	tree_n_t* m_tree;
	int m_generation; //辈分 等于父辈+1
	int m_index; //序列值 在同一辈分中的序列 也就是在link_list中的序列
}tree_node_t;

typedef struct tree_n_t {
	tree_node_t* m_root;
	tree_node_t* m_end;
	init_func m_init_data_func;
	destroy_func m_destroy_data_func;
	BOOL m_is_asy;
	CRITICAL_SECTION m_asy_section; //线程锁
	void* m_p_attach_data;
}tree_n_t;

分析:树结构应该算是一种基本的结构了
tree_n_t是一个多叉树结构，它里面包含了root与end两个结构
而root与end是tree_node_t结构
最特殊的结构就是tree_node_t
用于挂载数据的m_data
重要的结构m_children 表示该节点的所有子孩子，vector_array结构，访问元素时用vector_array_get_tree(index),含有的孩子个数就是
children->count

void destroy_tree(tree_n_t** pPTree) {
销毁tree
主要宏函数
#define TREE_INIT_1_S(name, type0) TREE_NODE_INIT_1_S(_tree##name##, type0)
初始化树 tree_n_t没有单独的初始化函数，只能靠宏函数来初始化

#define TREE_NODE_ADD_NODE_S(name, type) \
VECTOR_ARRAY_SET_ELEMENT_3_S(name##_tree_node, tree_node_t, tree_node_t*, init_func, tree_n_t*) \
tree_node_t* tree_node_add_node##name(tree_n_t* pTree, tree_node_t* pParentTreeNode) { \
添加节点，主要是定义一个宏函数VEXTOR来添加节点

TREE_INIT_2_S(_raw_string, const char*, int)
TREE_NODE_ADD_NODE_2_S(_raw_string, raw_string_t,  char*, int)


UnionStream 网络消息代码结构:
--client 
 --client.c //构建客户端代码
 --client_dispather //客户端消息分发器，接收服务器回复
--server
 --user_options
  --user_options_dispather.c //服务器消息分发器，只是分发来自客户端的消息请求(req)
 --server_dispather.c //服务器消息分发器，分发来自其他服务器的请求，p2p之间的通信
--message
 --network 
  --message.c //公用的消息结构定义
  --message_process.c //定义的消息处理函数
  
 UnionStream 的server分为三种
 1.master server//负责查询整个集群的IP，负责P2P的打洞
 2.p2p server //p2p节点之间的通信(异步通信)
 3.common server(block server) //与客户端进行交互的阻塞服务器(同步通信)
 以上三个服务器的IP可以相同也可以不同，可以单独分离开来


P2P结构
 typedef struct P2P_point_t { //P2P客户端 P2P的master是少不了的(master一直不能变动 一直在线) 不然没法实现打洞 每个P2P_point_t的server就是具有候选资格的master
							  //我们需要 并且 如果自己的server被推选成了master 虽然说此时的client和server同在一个进程中 但是为了统一化地管理 需要做的是将
							  //其一视同仁地连接上自己的server 这样做并不会因为“共用内存”而引起很大的混乱 因为我们的master的作用仅仅是在做“转发”而已
	auto_release_t m_auto_release; //自动释放
	un_block_client_t* m_master_client; //必须单独存在一个客户端 该客户端是在系统启动时连接master节点的(打洞节点)
	c2s_server_t* m_bussiness_server; //服务器 里面包含和其它端点连接的所有un_block_client 不管是自己主动连接的对方还是对方连接的自己
	finished_func m_connected_all_func; //连接上所有的节点后的回调函数
	dispatcher_process_func m_dispatcher_func; //事件分发函数
	//int m_pulse_type;
	int m_other_points_total_count; //这说的是理想状态下的端点的总数 并非真实的连接数量
	void* m_p_attach_data;
	//BOOL m_is_sy;
	//BOOL m_is_master; //自己是否是master
	int m_hole_port; //打洞端口号
}P2P_point_t;


如果链表中只是需要存取基本数据类型的指针，就用_value就可存取
声明:LINK_LIST_ADD_NODE_H(_param, void*)
存取:link_list_add_node_param_value(thread_get_p_params(pNewThread), "I am first Miner Thread");
取出:char **content = link_list_node_get_p_data(link_list_get_head(pParam));因为链表存取的是双指针
void link_list_add_node##name##_value(link_list_t* pLinkList, type value) { \
	link_list_node_t* pNode = link_list_add_node##name(pLinkList); \
	*(type*)link_list_node_get_p_data(pNode) = value; \
}























