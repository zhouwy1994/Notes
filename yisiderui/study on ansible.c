==========================Study On Ansible================================
ansible是新出现的自动化运维工具，基于Python开发，集合了众多运维工具（puppet、cfengine、chef、func、fabric）的优点，实现了批量系统配置、
批量程序部署、批量运行命令等功能。ansible是基于模块工作的，本身没有批量部署的能力。真正具有批量部署的是ansible所运行的模块，ansible只是
提供一种框架。主要包括：
(1)、连接插件connection plugins：负责和被监控端实现通信；
(2)、host inventory：指定操作的主机，是一个配置文件里面定义监控的主机；
(3)、各种模块核心模块、command模块、自定义模块；
(4)、借助于插件完成记录日志邮件等功能；
(5)、playbook：剧本执行多个任务时，非必需可以让节点一次性运行多个任务。-------摘自百度百科

环境：2台Ubuntu14.04TLS node-01 node-02
1、ansible安装
sudo apt-get install ansible
2、安装成功后会在/etc/ansible目录下生成配置文件ansible.cfg hosts
ansibles.cfg 是配置文件，hosts 是管理主机信息
3、向其他主机推送ssh公钥id_rsa.pub
ssh-copy-id -i .ssh/id_rsa.pub denali@node-01//向node-01推送本机公钥
4.ansible默认通过ssh与托关节点进行通信,所以管理主机与托管节点之间应该免密登陆,也可通过-ask-user -ask-passwd
选项连接时输入密码,但这种方法往往不安全
5.在配置文件/etc/ansible/hosts
组：一些托管节点的集合，一个托管节点可以同时存在于多个组中
组名用[]包含
可在hostname后制定ssh的端口，默认为22，如果多台托管节点命名方式有规律可使用[a:z] or [1-20]这种方式来命名example:mini[1-5]:22
[cluster]
thisNode ansible_host=localhost ansible_connection=local
node-03
node-02
ansible_connection=local ansible连接方式。本地和ssh
ansible_ssh_user=mpdehaan 制定用户名连接
给托管节点设置变量
[atlanta]
host1 http_port=80 maxRequestsPerChild=808
host2 http_port=303 maxRequestsPerChild=909
变量可能会在playbook中用到
Inventory 参数的说明
如同前面提到的,通过设置下面的参数,可以控制 ansible 与远程主机的交互方式,其中一些我们已经讲到过:

ansible_ssh_host
      将要连接的远程主机名.与你想要设定的主机的别名不同的话,可通过此变量设置.

ansible_ssh_port
      ssh端口号.如果不是默认的端口号,通过此变量设置.

ansible_ssh_user
      默认的 ssh 用户名

ansible_ssh_pass
      ssh 密码(这种方式并不安全,我们强烈建议使用 --ask-pass 或 SSH 密钥)

ansible_sudo_pass
      sudo 密码(这种方式并不安全,我们强烈建议使用 --ask-sudo-pass)

ansible_sudo_exe (new in version 1.8)
      sudo 命令路径(适用于1.8及以上版本)

ansible_connection
      与主机的连接类型.比如:local, ssh 或者 paramiko. Ansible 1.2 以前默认使用 paramiko.1.2 以后默认使用 'smart','smart' 方式会根据是否支持 ControlPersist, 来判断'ssh' 方式是否可行.

ansible_ssh_private_key_file
      ssh 使用的私钥文件.适用于有多个密钥,而你不想使用 SSH 代理的情况.

ansible_shell_type
      目标系统的shell类型.默认情况下,命令的执行使用 'sh' 语法,可设置为 'csh' 或 'fish'.

ansible_python_interpreter
      目标主机的 python 路径.适用于的情况: 系统中有多个 Python, 或者命令路径不是"/usr/bin/python",比如  \*BSD, 或者 /usr/bin/python
      不是 2.X 版本的 Python.我们不使用 "/usr/bin/env" 机制,因为这要求远程用户的路径设置正确,且要求 "python" 可执行程序名不可为 python以外的名字(实际有可能名为python26).

      与 ansible_python_interpreter 的工作方式相同,可设定如 ruby 或 perl 的路径....
在Ansible中,Patterns 是指我们怎样确定由哪一台主机来管理. 意思就是与哪台主机进行交互. 但是在:doc:playbooks 中它指的是对应主机应用特定的配置或执行特定进程.
ansible命令用法：
ansible <pattern_goes_here> -m <module_name> -a <arguments>
<pattern_goes_here>：需要执行命令的托管节点组或者单个IP，可用正则表达式或all *
module_name：执行的模块ping service....ansible有上百个模块默认为command模块
arguments 执行的命令或设置参数
ansible cluster -m service -a "name=httpd state=restarted"
(这其实是一个概念性的名字,是相对于写 Ansible playbook 来说的.类似于在命令行敲入shell命令和 写shell scripts两者之间的关系)...

如果我们敲入一些命令去比较快的完成一些事情,而不需要将这些执行的命令特别保存下来, 这样的命令就叫做 ad-hoc 命令.
ad-hoc:执行单条命令
playbook:脚本式执行
执行ansible有必要执行下列命令
ssh-agent bash
ssh-add ~/.ssh/id_rsa
多进程执行bash需要在ansible后加-f processnum实现
ansible的command模块不支持shell命令模式，不支持管道符等shell功能，如果需要使用shell，可使用shell模块
example：ansible cluster -m shell -a 'echo $PATH | grep bin'
-a 之后的"" 与 ''石有区别的''中PATH变量是托管节点的PATH ""中的PATH是管理主机的PATH

ansible模块：

1.File-Transfer
这是 /usr/bin/ansible 的另一种用法.Ansible 能够以并行的方式同时 SCP 大量的文件到多台机器. 命令如下:
$ ansible atlanta -m copy -a "src=/etc/hosts dest=/tmp/hosts"
使用 file 模块也可以创建目录,与执行 mkdir -p 效果类似:
$ ansible webservers -m file -a "dest=/path/to/c mode=755 owner=mdehaan group=mdehaan state=directory"
2.Managing-Packages
Ansible 提供对 yum 和 apt 的支持.这里是关于 yum 的示例.
确认一个软件包已经安装,但不去升级它:
$ ansible webservers -m yum -a "name=acme state=present"

3.Users and Groups
使用 ‘user’ 模块可以方便的创建账户,删除账户,或是管理现有的账户:
$ ansible all -m user -a "name=foo password=<crypted password here>"
$ ansible all -m user -a "name=foo state=absent"

4.Deploying From Source Control
直接使用 git 部署 webapp:
$ ansible webservers -m git -a "repo=git://foo.example.org/repo.git dest=/srv/myapp version=HEAD"
5.Managing Services
启动某个服务在所有的webservers上:
$ ansible webservers -m service -a "name=httpd state=started"
或是在所有的webservers上重启某个服务(译者注:可能是确认已重启的状态?):
$ ansible webservers -m service -a "name=httpd state=restarted"
停止某个服务已经:
$ ansible webservers -m service -a "name=httpd state=stopped"

======================================Playbook==========================================================
playbook 使用的脚本为YAML格式，YAML格式的脚本类似于XML JOSN易于阅读，以initClusetr.yml讲解
---
- hosts: thisNode
  tasks:
    - name: Verifying
      fail: msg="Missing parameters"
      when: memberIPAddrs is undefined
- hosts: thisNode
  tasks:
    - name: "Add the other IP's to hosts"
      add_host:
        name: "{{item}}"
        curr_address: "{{item}}"
        groups: "precheckTmpGroup"
        ansible_connection: "ssh"
        ansible_user: "{{ansible_user_id}}" # The user who is running the playbook
        ansible_become: True
        record_host_keys: True
        host_key_checking: False
      with_items: '{{memberIPAddrs}}'
- hosts: precheckTmpGroup
  vars:
    - cluster_hosts: []
  tasks:
    - block:
      - name: Setting up the hosts (standard)
        set_fact:
           cluster_hosts: "{{cluster_hosts + [{\"HostName\":hostvars[item]['ansible_hostname'], \"IPAddr\":item}]}}"
        with_items: "{{memberIPAddrs}}"
        when: backendNetwork is undefined
      - name: Setting up the hosts (backendNetwork)
        set_fact:
           cluster_hosts: "{{cluster_hosts + [{\"HostName\":hostvars[item]['ansible_hostname'], \"IPAddr\":hostvars[item]['ansible_all_ipv4_addresses'] | ipaddr(backendNetwork) | first}]}}"
        with_items: "{{memberIPAddrs}}"
		when: backendNetwork is defined
      - name: Add marker line
        lineinfile:
          dest: /etc/hosts
          line: "# DESTROY CLUSTER DELETES EVERYTING AFTER THIS LINE"
      - name: "Update hosts file"
        shell: grep "{{item['HostName']}}" /etc/hosts || /usr/sbin/mungehosts -a "{{item['IPAddr']}} {{item['HostName']}}"
        with_items: "{{cluster_hosts}}"
      - name: "Updating inventory file(s) of specified node(s)"
        lineinfile: dest="/etc/ansible/hosts"
                    line="{{item['HostName']}}"
        when: item.HostName != "{{ansible_hostname}}"
        with_items: "{{cluster_hosts}}"
      - name: "Refresh inventory"
        meta: refresh_inventory


对于 Ansible, 每一个 YAML 文件都是从一个列表开始. 列表中的每一项都是一个键值对, 通常它们被称为一个 “哈希” 
或 “字典”. 所以, 我们需要知道如何在 YAML 中编写列表和字典.
YAML的基本语法如下
1.每一个yml文件都以"---"开头
2.列表中的所有成员都开始于相同的缩进级别, 并且使用一个 "- " 作为开头(一个横杠和一个空格):
3.一个字典是由一个简单的 键: 值 的形式组成(这个冒号后面必须是一个空格):
---
- hosts: thisNode
  tasks:
    - name: Verifying
4.你需要使用引号来包裹任何包含冒号':'的哈希值
5.此外, Ansible 使用 “{{ var }}” 来引用变量. 如果一个值以 “{” 开头, YAML 将认为它是一个字典, 所以我们必须引用它, 像这样:
foo: "{{ variable }}"
6.playbook 由一个或多个 ‘plays’ 组成.它的内容是一个以 ‘plays’ 为元素的列表.
在 play 之中,一组机器被映射为定义好的角色.在 ansible 中,play 的内容,被称为 tasks,即任务.在基本层次的应用中
,一个任务是一个对 ansible 模块的调用,这在前面章节学习过.-hosts:到下一个-hosts之间的内容plays
7.plays的组成：
(1)host and username
- hosts: webservers
  remote_user: root
(2)Tasks 列表
tasks:
    - name: test connection
      ping:
      remote_user: yourname
每一个plays都包含了一个tasks列表，是在hosts指定的主机或组需要执行的操作
且是顺序执行上一个tasks执行完毕后才执行下一个tasks,如果上一个tasks执行失败，找到执行失败的某个主机，这个失败的主机将退出playbook的执行
不影响其他主机
(3)Handlers: 在发生改变时执行的操作
playbook可重复执行，第二次执行只执行被修改的地方，notify下列出handlers，handlers在plays退出时执行
- name: template configuration file
  template: src=template.j2 dest=/etc/foo.conf
  notify:
     - restart memcached
     - restart apache
handlers:
    - name: restart memcached
      service:  name=memcached state=restarted
    - name: restart apache
      service: name=apache state=restarted
	  































