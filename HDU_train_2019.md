# HDU多校2019训练记录+题解+补题进度

## 20190723 第一场

### 总结

#### Dafeng 
今天这场的A，数组开小导致WA, 赛后10min才过。究其原因，我本来是想将第二维表示成
0,1,2的，但写的时候发现表示成1,2,3会更自然，然后就改了……但此时数组已经定义好在上面，忘了改回去……

能过A就很好了呀，明明是开场就想出来的题。

这个教训我，上机之前一定得梳理好思路。敲代码的时候，如果中途对思路进行修改，哪怕是很微小的修改，都有可能导致程序不一致。

M题敲得也有些慢，有些特殊情况没有考虑到。还敲错了一个变量名。没有1A是遗憾。

总之上机码题时，我需要保持住最清醒的状态，力求减少错误。

但今天队友发挥得不错，校内rank也比较好看。

### 题解


#### A Blank  (By dafeng)

$dp[i][j][k][t]$表示前i个位置，从位置i往左看，第一个不同的位置是j，第二个不同的位置是k，第三个不同的位置是t的方案数。转移O(4).


## 补题进度总览表

√代表已完成

O代表正在Focus

-代表题目不存在或者太水

·代表有意向补

点击√可查看代码


# Dafeng (100-199)

Dafeng  |   A    |   B    |   C    |   D    |   E    |   F    |   G    |   H    |   I    |   J    |   K    |   L    | M
:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:
Day1    |[√][100]|        |        |        |[√][101]|        |        |        |        |        |        |        |[√][102]
Day2    |        |        |        |        |        |        |        |        |        |        |        |        |
Day3    |        |        |        |        |        |        |        |        |        |        |        |        |
Day4    |        |        |        |        |        |        |        |        |        |        |        |        |
Day5    |        |        |        |        |        |        |        |        |        |        |        |        |
Day6    |        |        |        |        |        |        |        |        |        |        |        |        |
Day7    |        |        |        |        |        |        |        |        |        |        |        |        |
Day8    |        |        |        |        |        |        |        |        |        |        |        |        |
Day9    |        |        |        |        |        |        |        |        |        |        |        |        |
Day10   |        |        |        |        |        |        |        |        |        |        |        |        |


[100]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day1/A_dafeng.cpp
[101]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day1/E_dafeng.cpp
[102]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day1/M_dafeng.cpp


# Zayin (200-299) 

Zayin   |   A    |   B    |   C    |   D    |   E    |   F    |   G    |   H    |   I    |   J    |   K    |   L    | M
:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:
Day1    |        |        |        |[√][200]|        |        |        |        |        |        |[√][201]|[√][202]|
Day2    |        |        |        |        |        |        |        |        |        |        |        |        |
Day3    |        |        |        |        |        |        |        |        |        |        |        |        |
Day4    |        |        |        |        |        |        |        |        |        |        |        |        |
Day5    |        |        |        |        |        |        |        |        |        |        |        |        |
Day6    |        |        |        |        |        |        |        |        |        |        |        |        |
Day7    |        |        |        |        |        |        |        |        |        |        |        |        |
Day8    |        |        |        |        |        |        |        |        |        |        |        |        |
Day9    |        |        |        |        |        |        |        |        |        |        |        |        |
Day10   |        |        |        |        |        |        |        |        |        |        |        |        |

[200]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day1/D_zayin.cpp
[201]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day1/K_zayin.cpp
[202]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day1/L_zayin.cpp


# wcy1122 (300-399)

wcy1122 |   A    |   B    |   C    |   D    |   E    |   F    |   G    |   H    |   I    |   J    |   K    |   L    | M
:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:|:------:
Day1    |        |        |        |        |        |        |        |        |[√][300]|        |        |        |
Day2    |        |        |        |        |        |        |        |        |        |        |        |        |
Day3    |        |        |        |        |        |        |        |        |        |        |        |        |
Day4    |        |        |        |        |        |        |        |        |        |        |        |        |
Day5    |        |        |        |        |        |        |        |        |        |        |        |        |
Day6    |        |        |        |        |        |        |        |        |        |        |        |        |
Day7    |        |        |        |        |        |        |        |        |        |        |        |        |
Day8    |        |        |        |        |        |        |        |        |        |        |        |        |
Day9    |        |        |        |        |        |        |        |        |        |        |        |        |
Day10   |        |        |        |        |        |        |        |        |        |        |        |        |

[300]: https://github.com/Dafenghh/Training_Summary/blob/master/code/HDU2019/day1/L_wcy1122.cpp

