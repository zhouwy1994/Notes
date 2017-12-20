-------------------Study on git--------------------------------
				Wuyi Zhou
				2017-05-11
---------------------------------------------------------------

不管是哪种版本控制器，在commit 之前都要update
git update command:git pull

######Git学习笔记#############
0、Git是一款分布式版本控制器

分布式VS集中式：（只限与版本控制器Version Control System）
集中式：集中式系统必需要在有网络的情况下运行，所有工作必需经由中央处理器处理，修改之后再上传到中央处理器。
优点：所有工作都经由中央处理器，工作起来有统一性
缺点：工作时必需联网，且中央处理器异常将影响到所有工作节点
分布式：每一个工作节点都比较独立（每一个节点都是一个完整系统），可在自己的终端工作，后面再上传到中央处理器，
比方说你在自己电脑上改了文件A，你的同事也在他的电脑上改了文件A，这时，你们俩之间只需把各自的修改推送给对方，就可以互相看到对方的修改了。

1、安装Git
ubuntu:早期版本：sudo apt-get install git-core
ubuntu:新版本：sudo apt-get install git
redhat版：sudo yum install -y git

安装完成后：git config --global user.name "Wuyi Zhou"
			git config --global user.mail "wuyi.zhou@Istual.com"
因为因为Git是分布式版本控制系统，所以，每个机器都必须自报家门：你的名字和Email地址.
PS：git config命令的--global参数，用了这个参数，表示你这台机器上所有的Git仓库都会使用这个配置，当然也可以对某个仓库指定不同的用户名和Email地址。

2、创建版本库
版本库又叫仓库（repository）
版本库可以理解成一个目录，这个目录里面的所有文件都可以被Git管理起来，每个文件的修改、删除，Git都能跟踪，以便任何时刻都可以追踪历史，或者在将来
某个时刻可以“还原”。
(1)建立目录（版本库）
	mkdir learngit
	cd learngit
	pwd
(2)初始化版本库
	git init
PS:所有的版本控制器只能跟踪普通文本文件（TXT），对于二进制文件，版本控制器只能跟踪一些简单的属性，例如最后修改日前，创建日前等，micrsoft 的word
属于二进制文件，所有文件最好使用统一的编码格式（UTF-8），windows记事本打开后再save后都不再是UTF-8.建议使用notepad++
(3)建立一个文本文件(一定放在learngit目录)
	touch readme.txt
(4)写入内容 echo "Git is a sersion control system" >> readme.txt
(把文件放入仓库)
将文件放入仓库分为两步
4.1、git add radme.txt(添加变动)
4.2、git commit -m "对文件变动的描述"(提交变动)
PS：对文件的变动描述内容最好不要缺省
(5)实时查看仓库状态git status

3、文件变动
当readme.txt文件被改动后
要及时将改动提交仓库，git add readme.txt
					  git commit -m "文件变动描述"
也可用命令git diff readme.txt 查看文件具体变动diff(difference区别)
PS:git diff 要在提交之前才可查看变动，一旦commit,readme.txt将是最新状态文件

4、版本回退(Snapshots技术)
我们每一次commit提交变动之后，git log都会将变动信息记录在日志，也就是-m "此内容为commit log 记载的内容"
可通过命令git log查看历史变动事件也可家参数--pretty=oneline
zhouwy@ubuntu-1:~/learngit$ git log --pretty=oneline
8e7c6adc1a1bfaa98a89d31a090dff65603b39b9 add of name
6cf7c74d2650ee541cab5ccebd631acaee0a4f7f I'm Write a readme.txt
cf468226542df35df84a8ca7f28d69a84b730342 wrote a readme file
以上是执行命令后
8e7c6adc1a1bfaa98a89d31a090dff65603b39b9类似的是commit id(版本号)
Git中用HEAD指针保存当前版本好，之前的版本用HEAD^表示，上一个版本HEAD^,上上一个HEAD^^,上100：HEAD~100
如果我们想恢复回wrote a readme file状态git reset命令
zhouwyubuntu-1:~/learngit$ git reset --hard HEAD^^
HEAD is now at cf46822 wrote a readme file
readme.txt文件就恢复原样了
此时git log看见的信息，wrote a readme file之前的版本都不在了，如果此时我们后悔了，像回到之前的版本了，怎么班，commit id啊，
commit id 是快照的唯一id，有了id就有了快照，就可以恢复
git reset --hard `commit id`就可回去了，如果没有commit id怎么办，命令git reflog专门记录命令和commit id

5、工作区和暂存区
工作区：就是learngit目录(简单明了)
暂存区：learngit目录下的.git文件夹就叫Git的版本库，版本库里面有一个stage(index)暂存区，还有Git为我们自动创建的第一个分支master，
以及指向master的一个指针叫HEAD。
|------|         |------------------------------------
|learng|         |		.git
| it   |         |   |------|		|--------     -----
| work |		 |	 |stage |commit |		|<----|HEAD|
| space|---------+-->| 		|------>|master	|	  -----
|      |         |   |		|		|		|
|      |		 |   |------|		|-------|
|      |		 |
--------		 |------------------------------------|
前面讲了我们把文件往Git版本库里添加的时候，是分两步执行的：
(1)是用git add把文件添加进去，实际上就是把文件修改添加到暂存区；
(2)是用git commit提交更改，实际上就是把暂存区的所有内容提交到当前分支。
Git初始化是建立了一个MASTER分支
git add 只是将文件放入暂存区，commit才将文件加入分支

********************************************************************************************************************************************************
Git是一款免费、开源的分布式版本控制系统(Distributed Version Control System)，用于敏捷高效地处理任何或小或大的项目。
Study Environment:Ubuntu 14.04-Server
******************************************************************************************************************************************
															一、本地版本库操作
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
git init 这条命令就是将当前目录创建成一个版本库
4.向版本库里面添加文件
//git add readme.c
5.向版本库里提交修改
//git commit -m "提交说明"
6.查看版本库状态
//git status
7.查看具体文件变更
//git diff
8.每次修改之后需要add与commit
9.查看最初到末尾的所有提交日志
//git log
PS：可加上--pretty=oneline参数来精简显示
10.回到之前版本(版本回退)，git使用HEAD来表示当前版本，每一个commit都有一个对应的ID来恢复到之前版本
//git reset --hard HEAD^ //HEAD^表示上一版本 HEAD^^表示上两个版本依次类推 也可用数值来表示HEAD~100回到之前100版本
PS：可通过每个commit版本号回退`
11.如果回退之后需要回到之前版本，这是通过HEAD是不能回去了，只有通过ID回去，通过命令git reflog 命令查看历史命令，里面包含了原始版本的ID
在通过git set --hard commit ID 回去

12.HEAD说明:
其实HEAD类似C语言中的指针，它总是指向最新commit，为什么git版本回退很快速，就是因为只需要移动HEAD的指向，下图可知：
HEAD------------------>three
					   two
					   one
执行git set --hard HEAD^ 后HEAD指向two
					   three
HEAD------------------>two
					   one
"one","two","three" is commit name or commit ID.

14.工作区(Working space)、版本库(Repositry)暂存区(Temporary spae)、分支(Branch)
git的工作模式，我们之前所建立的Directory "learn_gits"为工作区
git init之后产生的.git目录为版本库
.git(版本库)里面有一个主分支(master)和一个暂存区(Temporary)
我们之强重要的两个命令 git add 和 git commit 的工作目的
git add readme.c是将readme.c添加到暂存区
git commit 是将readme.c提交到分支(master)
learn_git                         Repositry(.git)
    |               ---------------------------------------|
----------          |----------|           |---------|     |
|        |          ||		   |           |         |     |
|        |	git add ||	Tmp    |add commit |         |     |
|Work	 |---------->|   space |---------->|  master |     |
|space	 |	        ||         |           |         |     |
|--------|			|-----------           |---------|     |
                    |---------------------------------------
一旦提交后工作区就是干净的git status显示以下信息
On branch master
nothing to commit, working directory clean

15由于git属于版本控制器，只负责管理修改. git commit 只负责提交暂存区里的内容，add diff也只是和暂存区里面的内容进行比较
16.git diff 将所有文件的变动修改进行比较,如果只是比较某个文件的变动git diff HEAD --readme.c
git diff 不加参数时之和暂存区里面比较，如果暂存区已经提交，就和最新的版本比较也就是HEAD
如果需要将工作区的文件与历史版本比较时git diff HEAD^ -- filename
HEAD^为需要对比的历史版本
17.如果你在写代码时不在状态，清醒的时候发现之前写的代码真是一坨shi,这时你就想把它恢复到你不在状态之前的版本
//git checkout -- readme.c
这时有几种情况会发生:
(1)你这份代码至开始到现在一直都没有add过，这时checkout就会提示错误，没有与之对比的版本
(2)修改之前已经add到暂存区，但未及时commit的，就会恢复到暂存区的状态
(3)已经commit分支，add暂存区里面没有备份，就会恢复到最新的版本
PS：checkout里面的--参数很重要如果没有--参数就变成切换到另一分支
18.将暂存区里的代码回到工作区git reset HEAD filenme，所以reset两个功能回退版本，和恢复暂存区修改
19.只要是在本地版本库修改怎么错都是可以恢复，但是如果将道歉版本推送到远程库，那就惨了
20.如果你不小心删除(rm)工作区中某一个文件，只要版本库里面已经有commit，可通过checkout -- filenmae 来恢复
21.如果一个文件已经没有利用价值，可通过git rm 将其从分支删除彻底删除

******************************************************************************************************************************************
															二、远程库操作
******************************************************************************************************************************************
Git区别于其他版本控制系统的就在于Git可以将一台服务器作为公共版本库，任何有权限的开发者都可通过克隆版本库方式将

远程的版本库克隆到本地，服务器可以自己搭建，也可用GitHub，这是一个公共的专门负责托管Git仓库的服务器

1.如需使用GitHub首先得注册帐号

2.git不同节点之间的通信都是依靠ssh密钥，所以必须在需通信的两端配置ssh Key

3.在自己的开发机器上配置ssh Key，在主目录下的.ssh目录里面查找看是否有id_rsa和id_rsa.pub两个文件，如果有则不管，

如果没有该文件ssh-keygen -t rsa -C "wuyi.zhou@istuary.com",一路回车，不用配置密码

4.第2步：登陆GitHub，打开“Account settings”，“SSH Keys”页面：然后，点“Add SSH Key”，填上任意Title，在Key文本框里粘

贴id_rsa.pub文件的内容，点击ADD key 这时远程的github就可以通过这个ssh key与本机的git通信了，在git上推送的文件别人

时可见的，但只有自己能够修改，要想人不知，就叫保护费，私人仓库

5.github可以添加多个ssh 可以在家、公司不同电脑修改代码

6.在github上新建一个Repositry,并将它与本地库关联

git remote add origin https://github.com/zhouwy1994/learning.git origin关联名可以改变,首先建一个README.md的文件,文件内容

为#远程库的名称,再使用git pull 更新代码

7.将自己的版本库里的分支推送到Github上git push -u origin master；-u选项只是初次push才会添加，目的是将本地的master与

远端的master分支关联起来，之后再推送代码直接git push origin master就行

8.远程库与本地库一样,最终进入版本库的是branch里的内容，也就算commit后的内容

9.克隆远程库，一般就是s克隆公共的开发代码 git clone https://github.com/zhouwy1994/gitskill.git

10.Git提供多种传输协议，https、ssh、git(默认),https传输较慢，一般使用ssh(前提是提前添加了ssh key)

11.分支管理，在你还没完成代码编写之前你的工作可以创建一个分支来进行工作，待工作完成之后再合并到主分支

12.严格来说HEAD并不是指向当前commit，而是指向当前分支,每一个分支又指向当前最新提交(commit)，HEAD---->master------>commit

13.当我们创建一个新分支dev时，系统就会产生一个dev指针指向master的最新commit，此时的HEAD指向了DEV，对新分支修改时，master

指针不移动，dev移动HEAD指向dev也跟着移动


14.当我们完成了dev分支上的所有动作之后，就必须合并到master主分支，怎样合并呢，就是将master指针指向dev当前的提交commit，就这么

简单，完成合并后可以delete Dev分支，删除Dev分支也比较简单，就是将Dev指针直接删除，将HEAD指向master

15，为什么Git分支操作会如此之快，就是因为它就算指针之间的操作

16.创建分支git branch dev

17.切换到dev分支ckeckout dev，与上面的命令结合:checkout -b dev 创建并切换到dev分支

19.显示当前所有分支git branch 带*号的表示当前工作的分支

20.在分支dev分支的所有工作其他分支不可见包括主分支

21.合并分区，git merge dev将dev合并到主分支，合并后将所有的修改加入master，由于只有一条分支，所以合并起来

非常快速，就是指针移动

22.删除分支 git branch -d dev

23.上面的情况属于最简单的情况，也就是切换到分支dev后不再对master分支作修改，合并时只需要将dev的改动添加到master就行

如果在修改dev的同时也在修改master，那合并时就会发生冲突，这时就会在冲突的文件里面将所有的修改都添加进文件，git将这些修改作了区别

用<<<<<< ===== >>>>>等表示不同分支的修改，这时就需要手动进行修改，然后将修改的内容重新提交

24。可使用命令git log --graph --pretty=oneline --abbrev-commit 查看合并的内容

25.git merge --no-ff dev //--no-ff 可保留分支信息，后面删除分支后还可查看合并历史

26.当你在分支做出修改时发现另外一个分支上有bug，必须在短时间之内解决这时你在当前分区的工作还没有完成，所以不能切换到bug分支

git提供了一个stash的命令可以将当前工作分支隐藏，运行git stash 之后再使用git status 查看状态时当前分支是干净的这时就可以切换分支

了，待bug分支修复完成合并之后，chkeckout 切换回之前分支，使用命令git stash list查看所有隐藏的分支工作区，使用命令git stash apply

或者git stash pop 前者在恢复之后stssh备份还在，需要使用git stash  drop删除，可使用stash pop 来恢复工作区，恢复之后stssh的备份
即不在

27.已经修改但还未合并的分支默认不能删除，必须使用-D参数强制删除 git branch -D dev

28.查看远程库信息，使用git remote -v；

29.本地新建的分支如果不推送到远程，对其他人就是不可见的；

30.从本地推送分支，使用git push origin branch-name，如果推送失败，先用git pull抓取远程的新提交；

31.在本地创建和远程分支对应的分支，使用git checkout -b branch-name origin/branch-name，本地和远程分支的名称最好一致；****

因为从远程库克隆的只有master分支，如果想协同开发dev必须在本地建一个分支与远程的dev分支相对应

32.建立本地分支和远程分支的关联，使用git branch --set-upstream branch-name origin/branch-name；只有关联了才能pull

33.从远程抓取分支，使用git pull，如果有冲突，要先处理冲突。

34.git push origin --delete <branchName>删除远程分支，首先用git branch -a查看所有分支红色的代表远程分支

35.git show 查看每次commit修改的内容

36.git log -p 查看某个文件修改历史

37.git log -p -2 查看近两次的更新内容

38.查看远程分支 git branch -a  
39.git rm file才能删除
7.将自己的版本库里的分支推送到Github上git push -u origin master；-u选项只是初次push才会添加，目的是将本地的master与
39.察看两个分支的文件内容不同 git diff dev1 dev2
40.1.查看 dev 有，而 master 中没有的：
git log dev ^master 
同理查看 master 中有，而 dev 中没有的内容：
git log master ^dev
41.2.查看 dev 中比 master 中多提交了哪些内容：
git log master..dev
注意，列出来的是两个点后边（此处即dev）多提交的内容。同理，想知道 master 比 dev 多提交了什么：
git log dev..master

版本回退(回到最新commit)
git reset --hard HEAD~1(commit_id)(git log)

--hard 不保留当前修改
 --soft 保留当前修改
然会强制推送至远端
git push -f -u origin dev
44.与远端的git进行交互
git rebase -i HEAD~1
45
git checkout . #本地所有修改的。没有的提交的，都返回到原来的状态
git stash #把所有没有提交的修改暂存到stash里面。可用git stash pop回复。

git 修改了没事，修改了哪个就comit哪个，不影响其他的

git pull远程分支覆盖本分支
git fetch --all //将远程拉到本地但是不覆盖  
git reset --hard origin/master //强制回退版本到主分支
git pull //将代码pull合并
git stash

保存当前的工作现场，这时候就可以切换到其它分支进行工作，或者在当前分支上，完成其它紧急工作。
Git stash的使用与分支无关，即不同分支的git stash会产生stash list。可以通过
git stash list
查看所有stash的内容。如果需要提取某一个stash可以通过
git stash pop stash@{num}
num就是要恢复的工作编号。
清除所有的stashed状态，
git stash clear












