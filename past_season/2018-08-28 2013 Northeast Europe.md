# 2013 Northeast Europe
Date: 2018-08-28

## Practice Link
https://vjudge.net/contest/248154

## 流水账
开场，赛波敲签到题F，立辉想H。达烽敲B。16min过了F。77min过了H。B题WA了4发，赛波提出了优化精度的做法，1h38min过了。然后赛波敲J，2h18min 1A。接着我们就挂机比较久了。立辉和赛波敲交互I，达烽敲K。4h21min过了I。达烽一直WA，然后不断改细节错误，4h58min AC。
## 个人总结
### 徐达烽
今天一共贡献7发罚时……B浮点数的精度处理+K的细节。今天是K想到了思路就上机敲了，敲了比较久还留下好几处bug。最后都改对很刺激。但比赛时应该先把自己的思路在草稿纸上写清楚，这样敲得更顺，也会少些错误。
### 梁赛波
今天签到题F打的有点迷，可能没睡醒WA了之后看不出sb错还浪费了队友的时间来debug。可能以前被一些很夸张的文本处理题虐过，J这种在字符串上一个指针for来for去的题打的比较顺手，交互题I比较迷，我先想了一个二分套二分的做法，打起来发现有点问题，后来又想了个假算法，被队友hack掉了，然后队友就A了。最后是K，队友的做法是很多直觉上正确然后拼接起来又很多细节的做法，我最不擅长的题就是这种了，如果这题给我打，旁边没人看着我，我大概会打着打着就睡着了。所以听了一遍队友的做法之后我也没有看出什么重要的bug，只是大概确认正确性和提醒颜色或人数很少时的边界情况了。
### 谢立辉
今天开场看的就是H题，看完题面总觉得在哪做过，隐约记得是记录每一个位啥的，按着这个思路下去H其实是一道很简单的题，虽然我写得很迷就是了。。。然后就是F了，交互题从来没在赛时写对过。。。赛波一开始想的二分套二分，写着写着就轮到达峰去写K，所以放下了一会，期间听说是找到了hack数据。。。然后我想到了一个很迷的做法，复杂度未知，次数未知，是否可以有限步内结束也未知。。。反正也没事做，顺手敲了一发把极限数据过了。。。交上去一下就过了test59[doge],然后又过了test200，然后就蜜汁AC了。。。果然做人还是要有梦想的。。。

## 要补的题+题解
### A题

