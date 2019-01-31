/*
首先长度不同肯定先删长度小的串，对于长度相同的串，肯定每次选删掉之后使得剩下的串字典序尽可能大，每一步都在上一步的基础上再扩展
剩下的问题相当于如何快速求出当前串的若干对后缀之间的LCP，后缀数组可能复杂度或常数过大无法通过
实际上只需要知道删除某个长度为len的串后剩下的串和原串的LCP，这样也能快速比较后缀之间的字典序，这个可以求f[],其中f[i]表示suffix[i]和suffix[i+len]的LCP，这个可以从后往前线性地扫一遍得出
这样可能会产生一个问题，某两个后缀如果和原串的LCP一样，那这两个后缀感觉不能只通过LCP后一个字母比较得出字典序大小关系
但是实际上这样的两个后缀一定是完全相同的，画一画就知道了，它们不属于LCP的部分就是共享的一段后缀
时间复杂度O(\sum_{}LEN^2),LEN表示每组数据中初始拼接起来的字符串长度
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=6005;
int n,f[maxn*10],pos[maxn];
string str[maxn];
vector<int> all[11];
void update(vector<int> &n,string &m){
  int x=0;
  if(n.size()<m.size()){
    n.resize(m.size());
  }
  for(int i=0;i<m.size() || x;i++){
    x+=i<m.size()
      ?m[(int)m.size()-1-i]-'0'
      :0;
    if(i==n.size())n.push_back(0);
    n[i]+=x;
    x=n[i]/10;
    n[i]%=10;
  }
  if(x)n.push_back(x);
}
bool better(pair<char,int> x,pair<char,int> y){
  if((x.first>0)!=(y.first>0))return x.first>y.first;
  return x.second==y.second
        ?x.first>y.first
        :(x.second<y.second)^(x.first<0);
}
int main(){
  // freopen("../input.txt","r",stdin);
  int _;cin>>_;
  for(int Case=1;Case<=_;Case++){
    cin>>n;
    str[0]="";
    for(int i=1;i<=10;i++){
      all[i].clear();
    }
    for(int i=1;i<=n;i++){
      cin>>str[i];
      pos[i]=str[0].size();
      str[0]+=str[i];
      all[str[i].size()].push_back(i);
    }
    vector<int> ans;
    for(int len=1;len<=10;len++){
      for(;all[len].size();){
        f[str[0].size()]=0;
        for(int i=(int)str[0].size()-1;i>=len;i--){
          if(str[0][i]==str[0][i-len]) f[i]=f[i+1]+1;
          else f[i]=0;
        }
        vector<pair<char,int> > val(all[len].size());
        for(int i=0;i<all[len].size();i++){
          int p=pos[all[len][i]];
          assert(p+f[p+len]+len<=str[0].size());
          char y=(p+f[p+len]+len==str[0].size())
                ?0
                :(str[0][p+f[p+len]+len]);
          y-=str[0][p+f[p+len]];
          assert(y!=0);
          val[i]=make_pair(y,p+f[p+len]);

        }
        for(int i=0;i<all[len].size();i++){
          if(better(val[i],val.back())){
            swap(val[i],val.back());
            swap(all[len][i],all[len].back());
          }
        }
        int k=all[len].back();
        all[len].pop_back();
        str[0].erase(pos[k],len);
        update(ans,str[0]);
        for(int i=k+1;i<=n;i++){
          pos[i]-=len;
        }
      }
    }
    reverse(ans.begin(),ans.end());
    cout<<"Case #"<<Case<<": ";
    for(int i=0;i<ans.size();i++){
      cout<<(char)(ans[i]+'0');
    }
    cout<<endl;
  }
  return 0;
}