-------------------Study on git--------------------------------
				Wuyi Zhou
				2017-05-11
---------------------------------------------------------------

���������ְ汾����������commit ֮ǰ��Ҫupdate
git update command:git pull

######Gitѧϰ�ʼ�#############
0��Git��һ��ֲ�ʽ�汾������

�ֲ�ʽVS����ʽ����ֻ����汾������Version Control System��
����ʽ������ʽϵͳ����Ҫ�����������������У����й������辭�����봦���������޸�֮�����ϴ������봦������
�ŵ㣺���й������������봦����������������ͳһ��
ȱ�㣺����ʱ���������������봦�����쳣��Ӱ�쵽���й����ڵ�
�ֲ�ʽ��ÿһ�������ڵ㶼�Ƚ϶�����ÿһ���ڵ㶼��һ������ϵͳ���������Լ����ն˹������������ϴ������봦������
�ȷ�˵�����Լ������ϸ����ļ�A�����ͬ��Ҳ�����ĵ����ϸ����ļ�A����ʱ��������֮��ֻ��Ѹ��Ե��޸����͸��Է����Ϳ��Ի��࿴���Է����޸��ˡ�

1����װGit
ubuntu:���ڰ汾��sudo apt-get install git-core
ubuntu:�°汾��sudo apt-get install git
redhat�棺sudo yum install -y git

��װ��ɺ�git config --global user.name "Wuyi Zhou"
			git config --global user.mail "wuyi.zhou@Istual.com"
��Ϊ��ΪGit�Ƿֲ�ʽ�汾����ϵͳ�����ԣ�ÿ�������������Ա����ţ�������ֺ�Email��ַ.
PS��git config�����--global���������������������ʾ����̨���������е�Git�ֿⶼ��ʹ��������ã���ȻҲ���Զ�ĳ���ֿ�ָ����ͬ���û�����Email��ַ��

2�������汾��
�汾���ֽвֿ⣨repository��
�汾���������һ��Ŀ¼�����Ŀ¼����������ļ������Ա�Git����������ÿ���ļ����޸ġ�ɾ����Git���ܸ��٣��Ա��κ�ʱ�̶�����׷����ʷ�������ڽ���
ĳ��ʱ�̿��ԡ���ԭ����
(1)����Ŀ¼���汾�⣩
	mkdir learngit
	cd learngit
	pwd
(2)��ʼ���汾��
	git init
PS:���еİ汾������ֻ�ܸ�����ͨ�ı��ļ���TXT�������ڶ������ļ����汾������ֻ�ܸ���һЩ�򵥵����ԣ���������޸���ǰ��������ǰ�ȣ�micrsoft ��word
���ڶ������ļ��������ļ����ʹ��ͳһ�ı����ʽ��UTF-8����windows���±��򿪺���save�󶼲�����UTF-8.����ʹ��notepad++
(3)����һ���ı��ļ�(һ������learngitĿ¼)
	touch readme.txt
(4)д������ echo "Git is a sersion control system" >> readme.txt
(���ļ�����ֿ�)
���ļ�����ֿ��Ϊ����
4.1��git add radme.txt(��ӱ䶯)
4.2��git commit -m "���ļ��䶯������"(�ύ�䶯)
PS�����ļ��ı䶯����������ò�Ҫȱʡ
(5)ʵʱ�鿴�ֿ�״̬git status

3���ļ��䶯
��readme.txt�ļ����Ķ���
Ҫ��ʱ���Ķ��ύ�ֿ⣬git add readme.txt
					  git commit -m "�ļ��䶯����"
Ҳ��������git diff readme.txt �鿴�ļ�����䶯diff(difference����)
PS:git diff Ҫ���ύ֮ǰ�ſɲ鿴�䶯��һ��commit,readme.txt��������״̬�ļ�

4���汾����(Snapshots����)
����ÿһ��commit�ύ�䶯֮��git log���Ὣ�䶯��Ϣ��¼����־��Ҳ����-m "������Ϊcommit log ���ص�����"
��ͨ������git log�鿴��ʷ�䶯�¼�Ҳ�ɼҲ���--pretty=oneline
zhouwy@ubuntu-1:~/learngit$ git log --pretty=oneline
8e7c6adc1a1bfaa98a89d31a090dff65603b39b9 add of name
6cf7c74d2650ee541cab5ccebd631acaee0a4f7f I'm Write a readme.txt
cf468226542df35df84a8ca7f28d69a84b730342 wrote a readme file
������ִ�������
8e7c6adc1a1bfaa98a89d31a090dff65603b39b9���Ƶ���commit id(�汾��)
Git����HEADָ�뱣�浱ǰ�汾�ã�֮ǰ�İ汾��HEAD^��ʾ����һ���汾HEAD^,����һ��HEAD^^,��100��HEAD~100
���������ָ���wrote a readme file״̬git reset����
zhouwyubuntu-1:~/learngit$ git reset --hard HEAD^^
HEAD is now at cf46822 wrote a readme file
readme.txt�ļ��ͻָ�ԭ����
��ʱgit log��������Ϣ��wrote a readme file֮ǰ�İ汾�������ˣ������ʱ���Ǻ���ˣ���ص�֮ǰ�İ汾�ˣ���ô�࣬commit id����
commit id �ǿ��յ�Ψһid������id�����˿��գ��Ϳ��Իָ�
git reset --hard `commit id`�Ϳɻ�ȥ�ˣ����û��commit id��ô�죬����git reflogר�ż�¼�����commit id

5�����������ݴ���
������������learngitĿ¼(������)
�ݴ�����learngitĿ¼�µ�.git�ļ��оͽ�Git�İ汾�⣬�汾��������һ��stage(index)�ݴ���������GitΪ�����Զ������ĵ�һ����֧master��
�Լ�ָ��master��һ��ָ���HEAD��
|------|         |------------------------------------
|learng|         |		.git
| it   |         |   |------|		|--------     -----
| work |		 |	 |stage |commit |		|<----|HEAD|
| space|---------+-->| 		|------>|master	|	  -----
|      |         |   |		|		|		|
|      |		 |   |------|		|-------|
|      |		 |
--------		 |------------------------------------|
ǰ�潲�����ǰ��ļ���Git�汾������ӵ�ʱ���Ƿ�����ִ�еģ�
(1)����git add���ļ���ӽ�ȥ��ʵ���Ͼ��ǰ��ļ��޸���ӵ��ݴ�����
(2)����git commit�ύ���ģ�ʵ���Ͼ��ǰ��ݴ��������������ύ����ǰ��֧��
Git��ʼ���ǽ�����һ��MASTER��֧
git add ֻ�ǽ��ļ������ݴ�����commit�Ž��ļ������֧

********************************************************************************************************************************************************
Git��һ����ѡ���Դ�ķֲ�ʽ�汾����ϵͳ(Distributed Version Control System)���������ݸ�Ч�ش����κλ�С������Ŀ��
Study Environment:Ubuntu 14.04-Server
******************************************************************************************************************************************
															һ�����ذ汾�����
******************************************************************************************************************************************
1.Install Git
//sudo apt-get install git
2.Initialization Global value
git config --global user.name "wuyi.zhou"
git config --global user.mail "wuyi.zhou@istuary.com"

2.Create An Directory 
mkdir learn_git
//cd learn_git
3.Initialization git
//git init
git init ����������ǽ���ǰĿ¼������һ���汾��
4.��汾����������ļ�
//git add readme.c
5.��汾�����ύ�޸�
//git commit -m "�ύ˵��"
6.�鿴�汾��״̬
//git status
7.�鿴�����ļ����
//git diff
8.ÿ���޸�֮����Ҫadd��commit
9.�鿴�����ĩβ�������ύ��־
//git log
PS���ɼ���--pretty=oneline������������ʾ
10.�ص�֮ǰ�汾(�汾����)��gitʹ��HEAD����ʾ��ǰ�汾��ÿһ��commit����һ����Ӧ��ID���ָ���֮ǰ�汾
//git reset --hard HEAD^ //HEAD^��ʾ��һ�汾 HEAD^^��ʾ�������汾�������� Ҳ������ֵ����ʾHEAD~100�ص�֮ǰ100�汾
PS����ͨ��ÿ��commit�汾�Ż���`
11.�������֮����Ҫ�ص�֮ǰ�汾������ͨ��HEAD�ǲ��ܻ�ȥ�ˣ�ֻ��ͨ��ID��ȥ��ͨ������git reflog ����鿴��ʷ������������ԭʼ�汾��ID
��ͨ��git set --hard commit ID ��ȥ

12.HEAD˵��:
��ʵHEAD����C�����е�ָ�룬������ָ������commit��Ϊʲôgit�汾���˺ܿ��٣�������Ϊֻ��Ҫ�ƶ�HEAD��ָ����ͼ��֪��
HEAD------------------>three
					   two
					   one
ִ��git set --hard HEAD^ ��HEADָ��two
					   three
HEAD------------------>two
					   one
"one","two","three" is commit name or commit ID.

14.������(Working space)���汾��(Repositry)�ݴ���(Temporary spae)����֧(Branch)
git�Ĺ���ģʽ������֮ǰ��������Directory "learn_gits"Ϊ������
git init֮�������.gitĿ¼Ϊ�汾��
.git(�汾��)������һ������֧(master)��һ���ݴ���(Temporary)
����֮ǿ��Ҫ���������� git add �� git commit �Ĺ���Ŀ��
git add readme.c�ǽ�readme.c��ӵ��ݴ���
git commit �ǽ�readme.c�ύ����֧(master)
learn_git                         Repositry(.git)
    |               ---------------------------------------|
----------          |----------|           |---------|     |
|        |          ||		   |           |         |     |
|        |	git add ||	Tmp    |add commit |         |     |
|Work	 |---------->|   space |---------->|  master |     |
|space	 |	        ||         |           |         |     |
|--------|			|-----------           |---------|     |
                    |---------------------------------------
һ���ύ���������Ǹɾ���git status��ʾ������Ϣ
On branch master
nothing to commit, working directory clean

15����git���ڰ汾��������ֻ��������޸�. git commit ֻ�����ύ�ݴ���������ݣ�add diffҲֻ�Ǻ��ݴ�����������ݽ��бȽ�
16.git diff �������ļ��ı䶯�޸Ľ��бȽ�,���ֻ�ǱȽ�ĳ���ļ��ı䶯git diff HEAD --readme.c
git diff ���Ӳ���ʱ֮���ݴ�������Ƚϣ�����ݴ����Ѿ��ύ���ͺ����µİ汾�Ƚ�Ҳ����HEAD
�����Ҫ�����������ļ�����ʷ�汾�Ƚ�ʱgit diff HEAD^ -- filename
HEAD^Ϊ��Ҫ�Աȵ���ʷ�汾
17.�������д����ʱ����״̬�����ѵ�ʱ����֮ǰд�Ĵ�������һ��shi,��ʱ���������ָ����㲻��״̬֮ǰ�İ汾
//git checkout -- readme.c
��ʱ�м�������ᷢ��:
(1)����ݴ�������ʼ������һֱ��û��add������ʱcheckout�ͻ���ʾ����û����֮�Աȵİ汾
(2)�޸�֮ǰ�Ѿ�add���ݴ�������δ��ʱcommit�ģ��ͻ�ָ����ݴ�����״̬
(3)�Ѿ�commit��֧��add�ݴ�������û�б��ݣ��ͻ�ָ������µİ汾
PS��checkout�����--��������Ҫ���û��--�����ͱ���л�����һ��֧
18.���ݴ�����Ĵ���ص�������git reset HEAD filenme������reset�������ܻ��˰汾���ͻָ��ݴ����޸�
19.ֻҪ���ڱ��ذ汾���޸���ô���ǿ��Իָ��������������Ǹ�汾���͵�Զ�̿⣬�ǾͲ���
20.����㲻С��ɾ��(rm)��������ĳһ���ļ���ֻҪ�汾�������Ѿ���commit����ͨ��checkout -- filenmae ���ָ�
21.���һ���ļ��Ѿ�û�����ü�ֵ����ͨ��git rm ����ӷ�֧ɾ������ɾ��

******************************************************************************************************************************************
															����Զ�̿����
******************************************************************************************************************************************
Git�����������汾����ϵͳ�ľ�����Git���Խ�һ̨��������Ϊ�����汾�⣬�κ���Ȩ�޵Ŀ����߶���ͨ����¡�汾�ⷽʽ��

Զ�̵İ汾���¡�����أ������������Լ����Ҳ����GitHub������һ��������ר�Ÿ����й�Git�ֿ�ķ�����

1.����ʹ��GitHub���ȵ�ע���ʺ�

2.git��ͬ�ڵ�֮���ͨ�Ŷ�������ssh��Կ�����Ա�������ͨ�ŵ���������ssh Key

3.���Լ��Ŀ�������������ssh Key������Ŀ¼�µ�.sshĿ¼������ҿ��Ƿ���id_rsa��id_rsa.pub�����ļ���������򲻹ܣ�

���û�и��ļ�ssh-keygen -t rsa -C "wuyi.zhou@istuary.com",һ·�س���������������

4.��2������½GitHub���򿪡�Account settings������SSH Keys��ҳ�棺Ȼ�󣬵㡰Add SSH Key������������Title����Key�ı�����ճ

��id_rsa.pub�ļ������ݣ����ADD key ��ʱԶ�̵�github�Ϳ���ͨ�����ssh key�뱾����gitͨ���ˣ���git�����͵��ļ�����

ʱ�ɼ��ģ���ֻ���Լ��ܹ��޸ģ�Ҫ���˲�֪���ͽб����ѣ�˽�˲ֿ�

5.github������Ӷ��ssh �����ڼҡ���˾��ͬ�����޸Ĵ���

6.��github���½�һ��Repositry,�������뱾�ؿ����

git remote add origin https://github.com/zhouwy1994/learning.git origin���������Ըı�,���Ƚ�һ��README.md���ļ�,�ļ�����

Ϊ#Զ�̿������,��ʹ��git pull ���´���

7.���Լ��İ汾����ķ�֧���͵�Github��git push -u origin master��-uѡ��ֻ�ǳ���push�Ż���ӣ�Ŀ���ǽ����ص�master��

Զ�˵�master��֧����������֮�������ʹ���ֱ��git push origin master����

8.Զ�̿��뱾�ؿ�һ��,���ս���汾�����branch������ݣ�Ҳ����commit�������

9.��¡Զ�̿⣬һ�����s��¡�����Ŀ������� git clone https://github.com/zhouwy1994/gitskill.git

10.Git�ṩ���ִ���Э�飬https��ssh��git(Ĭ��),https���������һ��ʹ��ssh(ǰ������ǰ�����ssh key)

11.��֧�������㻹û��ɴ����д֮ǰ��Ĺ������Դ���һ����֧�����й��������������֮���ٺϲ�������֧

12.�ϸ���˵HEAD������ָ��ǰcommit������ָ��ǰ��֧,ÿһ����֧��ָ��ǰ�����ύ(commit)��HEAD---->master------>commit

13.�����Ǵ���һ���·�֧devʱ��ϵͳ�ͻ����һ��devָ��ָ��master������commit����ʱ��HEADָ����DEV�����·�֧�޸�ʱ��master

ָ�벻�ƶ���dev�ƶ�HEADָ��devҲ�����ƶ�


14.�����������dev��֧�ϵ����ж���֮�󣬾ͱ���ϲ���master����֧�������ϲ��أ����ǽ�masterָ��ָ��dev��ǰ���ύcommit������ô

�򵥣���ɺϲ������delete Dev��֧��ɾ��Dev��֧Ҳ�Ƚϼ򵥣����ǽ�Devָ��ֱ��ɾ������HEADָ��master

15��ΪʲôGit��֧���������֮�죬������Ϊ������ָ��֮��Ĳ���

16.������֧git branch dev

17.�л���dev��֧ckeckout dev���������������:checkout -b dev �������л���dev��֧

19.��ʾ��ǰ���з�֧git branch ��*�ŵı�ʾ��ǰ�����ķ�֧

20.�ڷ�֧dev��֧�����й���������֧���ɼ���������֧

21.�ϲ�������git merge dev��dev�ϲ�������֧���ϲ������е��޸ļ���master������ֻ��һ����֧�����Ժϲ�����

�ǳ����٣�����ָ���ƶ�

22.ɾ����֧ git branch -d dev

23.��������������򵥵������Ҳ�����л�����֧dev���ٶ�master��֧���޸ģ��ϲ�ʱֻ��Ҫ��dev�ĸĶ���ӵ�master����

������޸�dev��ͬʱҲ���޸�master���Ǻϲ�ʱ�ͻᷢ����ͻ����ʱ�ͻ��ڳ�ͻ���ļ����潫���е��޸Ķ���ӽ��ļ���git����Щ�޸���������

��<<<<<< ===== >>>>>�ȱ�ʾ��ͬ��֧���޸ģ���ʱ����Ҫ�ֶ������޸ģ�Ȼ���޸ĵ����������ύ

24����ʹ������git log --graph --pretty=oneline --abbrev-commit �鿴�ϲ�������

25.git merge --no-ff dev //--no-ff �ɱ�����֧��Ϣ������ɾ����֧�󻹿ɲ鿴�ϲ���ʷ

26.�����ڷ�֧�����޸�ʱ��������һ����֧����bug�������ڶ�ʱ��֮�ڽ����ʱ���ڵ�ǰ�����Ĺ�����û����ɣ����Բ����л���bug��֧

git�ṩ��һ��stash��������Խ���ǰ������֧���أ�����git stash ֮����ʹ��git status �鿴״̬ʱ��ǰ��֧�Ǹɾ�����ʱ�Ϳ����л���֧

�ˣ���bug��֧�޸���ɺϲ�֮��chkeckout �л���֮ǰ��֧��ʹ������git stash list�鿴�������صķ�֧��������ʹ������git stash apply

����git stash pop ǰ���ڻָ�֮��stssh���ݻ��ڣ���Ҫʹ��git stash  dropɾ������ʹ��stash pop ���ָ����������ָ�֮��stssh�ı���
������

27.�Ѿ��޸ĵ���δ�ϲ��ķ�֧Ĭ�ϲ���ɾ��������ʹ��-D����ǿ��ɾ�� git branch -D dev

28.�鿴Զ�̿���Ϣ��ʹ��git remote -v��

29.�����½��ķ�֧��������͵�Զ�̣��������˾��ǲ��ɼ��ģ�

30.�ӱ������ͷ�֧��ʹ��git push origin branch-name���������ʧ�ܣ�����git pullץȡԶ�̵����ύ��

31.�ڱ��ش�����Զ�̷�֧��Ӧ�ķ�֧��ʹ��git checkout -b branch-name origin/branch-name�����غ�Զ�̷�֧���������һ�£�****

��Ϊ��Զ�̿��¡��ֻ��master��֧�������Эͬ����dev�����ڱ��ؽ�һ����֧��Զ�̵�dev��֧���Ӧ

32.�������ط�֧��Զ�̷�֧�Ĺ�����ʹ��git branch --set-upstream branch-name origin/branch-name��ֻ�й����˲���pull

33.��Զ��ץȡ��֧��ʹ��git pull������г�ͻ��Ҫ�ȴ����ͻ��

34.git push origin --delete <branchName>ɾ��Զ�̷�֧��������git branch -a�鿴���з�֧��ɫ�Ĵ���Զ�̷�֧

35.git show �鿴ÿ��commit�޸ĵ�����

36.git log -p �鿴ĳ���ļ��޸���ʷ

37.git log -p -2 �鿴�����εĸ�������

38.�鿴Զ�̷�֧ git branch -a  
39.git rm file����ɾ��
7.���Լ��İ汾����ķ�֧���͵�Github��git push -u origin master��-uѡ��ֻ�ǳ���push�Ż���ӣ�Ŀ���ǽ����ص�master��
39.�쿴������֧���ļ����ݲ�ͬ git diff dev1 dev2
40.1.�鿴 dev �У��� master ��û�еģ�
git log dev ^master 
ͬ��鿴 master ���У��� dev ��û�е����ݣ�
git log master ^dev
41.2.�鿴 dev �б� master �ж��ύ����Щ���ݣ�
git log master..dev
ע�⣬�г��������������ߣ��˴���dev�����ύ�����ݡ�ͬ����֪�� master �� dev ���ύ��ʲô��
git log dev..master

�汾����(�ص�����commit)
git reset --hard HEAD~1(commit_id)(git log)

--hard ��������ǰ�޸�
 --soft ������ǰ�޸�
Ȼ��ǿ��������Զ��
git push -f -u origin dev
44.��Զ�˵�git���н���
git rebase -i HEAD~1
45
git checkout . #���������޸ĵġ�û�е��ύ�ģ������ص�ԭ����״̬
git stash #������û���ύ���޸��ݴ浽stash���档����git stash pop�ظ���

git �޸���û�£��޸����ĸ���comit�ĸ�����Ӱ��������

git pullԶ�̷�֧���Ǳ���֧
git fetch --all //��Զ���������ص��ǲ�����  
git reset --hard origin/master //ǿ�ƻ��˰汾������֧
git pull //������pull�ϲ�
git stash

���浱ǰ�Ĺ����ֳ�����ʱ��Ϳ����л���������֧���й����������ڵ�ǰ��֧�ϣ������������������
Git stash��ʹ�����֧�޹أ�����ͬ��֧��git stash�����stash list������ͨ��
git stash list
�鿴����stash�����ݡ������Ҫ��ȡĳһ��stash����ͨ��
git stash pop stash@{num}
num����Ҫ�ָ��Ĺ�����š�
������е�stashed״̬��
git stash clear












