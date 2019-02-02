/*
预处理pass[i][j][k]表示前i轮第j个人至少经过一次k的概率即可算出答案
计算pass[][][]可以考虑反面，即一次都没有经过k的概率，这个可以通过枚举第一步走多少步转移
*/
#include <bits/stdc++.h>
using namespace std;
const int maxn=505;
int n;
double p[6][7],pos[maxn][6][maxn],pass[maxn][6][maxn],ans[6];
int main(){
  // freopen("input.txt","r",stdin);
  scanf("%d",&n);
  for(int i=0;i<6;i++){
    for(int j=1;j<=6;j++){
      scanf("%lf",&p[i][j]);
    }
  }
  for(int man=0;man<6;man++){
    for(int d=0;d<n;d++){
      pass[0][man][d]=1.0;
    }
  }
  for(int r=1;r<=500;r++){
    for(int man=0;man<6;man++){
      for(int d=0;d<n;d++){
        for(int x=1;x<=6;x++){
          if(x%n==d)continue;
          pass[r][man][d]+=p[man][x]*pass[r-1][man][(d-x%n+n)%n];
        }
      }
    }
  }
  for(int r=0;r<=500;r++){
    for(int man=0;man<6;man++){
      for(int d=0;d<n;d++){
        pass[r][man][d]=1.0-pass[r][man][d];
      }
    }
  }
  for(int r=1;r<=500;r++){
    for(int man=0;man<6;man++){
      for(int d=0;d<n;d++){
        double prob=pass[r][man][d]-pass[r-1][man][d];

        for(int i=0;i<man;i++){
          prob*=(1.0-pass[r][i][d]);
        }
        for(int i=man+1;i<6;i++){
          prob*=(1.0-pass[r-1][i][d]);
        }
        ans[man]+=prob;
      }
    }
  }
  for(int i=0;i<6;i++){
    printf("%.3lf\n",ans[i]);
  }
  return 0;
}