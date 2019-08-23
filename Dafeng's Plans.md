# 达烽的计划

## 1. camp课件

### 1.1 DP by claris
一共13道题，其中11道可提交，1道无题源，1道bzoj圈钱题。

序号|题目|完成情况|备注
:-:|:-:|:-:|:-:
1|[Knapsack][1] |    |
2|[烧桥计划][2]   |    |
3|Road Connectivity(注1) |   |
4|[Rikka with Subsequences][4]|[√][14]|好题！其实是很简单的DP：暴力转移i,j,k O(n^6) --> 分阶段转移，O(n^4)  -->  逐单位转移(流式)，O(n^3)
5|[Non-palidromic cutting][5]|     |
6|[Modern Art Plagiarism][6] |    |
7|[波浪][7]  |   | 
8|[小C的独立集][8]|   |
9|bzoj 3778 共鸣(圈钱题) [替代题][9] |    |
10|[Subsequences][10]  |    |
11|[Independent Set][11]  |    |
12|[Soldier Game][12] |    |
13|[最大连通子块和][13] |    |

注1: XIX Open Cup GP of Udmurtia, 没有题源。




## 2. 紧急刷题列表

Problem            |Comment             |Done
:-----------------:|:------------------:|:----:
[cf464E][15]       |dijk 主席树          |[√][19]
[20190316E][16]    |转完全图匹配         |
[20190317I][17]    |队友过的好题         |
[20190317K][18]    |不算难的题 欧拉回路   |
[20190317F][18]    |树上莫队 留意team1,5代码|[√][26]
[cjk 2019A T3][20] |贪心，大样例的线段树写得好辛苦（因为菜）  |[√][21]
[计蒜客2019复赛C][22]|FWT，待补|
[计蒜客2019复赛F][23]|思维题，待补|
[计蒜客2019复赛G][24]|生成函数，待补|
TCO beijing D|有趣的构造题，一定要补|
srm 761 1A|数学or模拟题?|
srm 761 1C|dp?|
[SEERC 17D][25]|xor下rank，每行两个元素，必须补！|
[HDU2019 4E][27]|三进制FWT|[√][30]
[北京2017 I Colored Nodes][28]|有趣的题目|
[CCPC2018吉林H][29]|必须补完|
## 3. TC刷题计划
http://wronganswer.blog.uoj.ac/blog/2285


## 4.比赛，日常训练总结


### 20190615 TCO beijing onsite
第一次打TCO，也是第一次打TC（从此开始TC之旅吧，尽量不要错过每一场SRM）

热身赛抢到个小米闹钟，很开心。

接着正赛发挥得非常一般，前二题有点慢，第三题纠结了一会儿……水题应该马上切掉了。（一开始我误把room的排名当成全场排名，导致有点放松也是原因之一）。

敲错了模数导致fst，切记不要再犯这样的错误了。

还是有些机会进前10的，手速再快些，D题要想出来怎么做。


### 20190616 计蒜客复赛

卡A题导致败北。想了一个理所当然的做法WA了，然后想到正解，却算错复杂度，算多一个零，5e5，一个log超稳的呀，那时候就应该果断敲了！

如果A题做得顺利些应该还是能进前50的。

听说G题是道生成函数，F题是道思维题。都要补一补。

### 20190622 TC SRM 761
第一场SRM，第一题就不会做……
然后第二题想到了正解，但没有算复杂度，导致一个测试点T了，fst……
于是成功爆零。
要好好算复杂度啊，发现不怎么稳的时候加点剪枝就过了。


### 20190712 CF #571 (Div. 2)

中午加训演练场。

E是道经典的水题，结果没有A，正在调。

### 20190712 CF #573

-41， 开启暑假。

三道水题分别用时17min, 35min, 45min, 然后比赛就剩20min，剩下的C题，也是简单题，没时间搞出来了。

做题速度太慢了！

如果我想打进前100的话，这三题应该用时13min, 15min, 25min.

B题做得最慢，应该和A题花费差不多的时间才对。

这场做得这么慢还有一个原因就是犯了很多低级错误，调试时间花了很久。想题时不够**仔细**。

这个暑假要好好训练，增强稳定性，水题提高速度！

### 20190713 CF edu #67

5h集训……

缺憾就是D题，F题，两道水题做得有点慢。

然后G的网络流没有想出来。虽然这是经典套路（要把24题刷一遍！），但其实如果我在赛场上坚持想下去，想到拆边的话，问题就迎刃而解了。

网络流建图无非拆点、拆边吧。

4+2前可以做下24题，以及复习之前做的例题。

以后做题，遇到一筹莫展的时候，应该**开拓**下思路，想想有哪些路可以尝试走。

[1]: http://opentrains.snarknews.info/~ejudge/team.cgi?contest_id=001519
[2]: https://www.lydsy.com/JudgeOnline/problem.php?id=5424

[4]: https://codeforces.com/gym/102012/problem/D
[5]: https://vjudge.net/problem/URAL-2057
[6]: https://code.google.com/codejam/contest/32005/dashboard#s=p3
[7]: https://www.luogu.org/problemnew/show/P2612
[8]: https://www.lydsy.com/JudgeOnline/problem.php?id=4316
[9]: https://vjudge.net/contest/263647#problem/C
[10]: http://opentrains.snarknews.info/~ejudge/team.cgi?contest_id=010437
[11]: https://vjudge.net/problem/ZOJ-3951
[12]: https://vjudge.net/contest/270330#problem/I
[13]: https://www.lydsy.com/JudgeOnline/problem.php?id=5210
[14]: https://github.com/Dafenghh/Training_Summary/blob/master/code/20181028/d.cpp
[15]: https://codeforces.com/contest/464/problem/E
[16]: https://codeforces.com/group/wmhDiB5PTN/contest/240683
[17]: https://codeforces.com/group/wmhDiB5PTN/contest/240806
[18]: https://codeforces.com/group/wmhDiB5PTN/contest/240806

[19]: https://github.com/Dafenghh/Training_Summary/blob/master/code/dafeng/cf265E.cpp
[20]: https://codingcompetitions.withgoogle.com/kickstart/round/0000000000050e01/0000000000069881
[21]: https://github.com/Dafenghh/Training_Summary/blob/master/code/dafeng/20190324/c.cpp
[22]: https://nanti.jisuanke.com/t/39613
[23]: https://nanti.jisuanke.com/t/39616
[24]: https://nanti.jisuankhttps://vjudge.net/contest/263852#problem/De.com/t/39617
[25]: https://vjudge.net/contest/263852#problem/D
[26]: https://codeforces.com/group/wmhDiB5PTN/contest/240806/submission/55309936
[27]: https://vjudge.net/problem/HDU-6618
[28]: https://vjudge.net/problem/HihoCoder-1635
[29]: https://vjudge.net/problem/HDU-6562
[30]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day4/E_dafeng.cpp

