#include <iostream>
using namespace std;

void gen(int pos,int d,int n,int target,int sum,int used,string code,string tc,bool &found)
{
    if(pos==n)
    {
        if(sum==target)
        {
            cout<<code<<endl;
            if(code==tc) found=true;
        }
        return;
    }
    if(d>9 || sum>target) return;
    if(!(used&(1<<d)) && !(pos==0 && d==0))
        gen(pos+1,0,n,target,sum+d,used|(1<<d),code+char('0'+d),tc,found);
    gen(pos,d+1,n,target,sum,used,code,tc,found);
}

int main()
{
  int n,target;
  string tc;
  cout<<"Enter N: ";
  cin>>n;
  cout<<"Enter target sum: ";
  cin>>target;
  cout<<"Enter target code: ";
  cin>>tc;
  bool found=false;
  cout<<"Valid codes:"<<endl;
  gen(0,0,n,target,0,0,"",tc,found);
  if(found)
      cout<<"Target code can be formed"<<endl;
  else cout<<"Target code cannot be formed"<<endl;
  return 0;
}