#include <iostream>
using namespace std;

int solve(int pos,int n,int st[],int sp[],int used[],int order[],double avg)
{
    if(pos==n)
    {
        for(int i=0;i<n;i++) cout<<order[i]+1<<" ";
        cout<<endl;
        return 1;
    }
    int count=0;
    for(int i=0;i<n;i++)
    {
        if(used[i]) continue;
        if(pos>=n-2 && st[i]<avg) continue;
        if(pos>0)
        {
            int p=order[pos-1];
            if(sp[p]<st[i]-st[p]) continue;
            if(sp[i]>=st[p]-st[i]) continue;
        }
        used[i]=1;
        order[pos]=i;
        count+=solve(pos+1,n,st,sp,used,order,avg);
        used[i]=0;
    }
    return count;
}

int main()
{
  int n;
  cout<<"Enter number of runners: ";
  cin>>n;
  int st[20],sp[20],used[20]={0},order[20];
  double avg=0;
  for(int i=0;i<n;i++)
  {
    cout<<"Stamina and speed of runner "<<i+1<<": ";
    cin>>st[i]>>sp[i];
    avg+=st[i];
  }
  avg=avg/n;
  int c=solve(0,n,st,sp,used,order,avg);
  if(c==0) cout<<"No valid running order"<<endl;
  return 0;
}