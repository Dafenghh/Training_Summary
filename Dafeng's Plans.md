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
[20190317F][18]    |树上莫队 留意team1,5代码|
[cjk 2019A T3][20] |贪心，大样例的线段树写得好辛苦（因为菜）  |[√][21]


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
