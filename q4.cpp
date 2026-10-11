#include <iostream>
using namespace std;

struct Rescue
{
    int n,m,cap,hr;
    int p[20][20],u[20][20],sel[20][20],best[20][20];
    int rowSel[20],rowNeed[20];
    int bestPeople,bestUnits;
    bool found;
};

void solve(Rescue &r,int idx,int units,int people,int hc)
{
    if(idx==r.n*r.m)
    {
        if(!r.found || people>r.bestPeople || (people==r.bestPeople && units<r.bestUnits))
        {
            for(int i=0;i<r.n;i++)
                for(int j=0;j<r.m;j++)
                    r.best[i][j]=r.sel[i][j];
            r.bestPeople=people;
            r.bestUnits=units;
            r.found=true;
        }
        return;
    }
    int i=idx/r.m,j=idx%r.m;
    if(r.p[i][j]!=-1)
    {
        int high=r.p[i][j]>=r.hr;
        int need=r.u[i][j];
        if(high) need+=hc;
        if(units+need<=r.cap)
        {
            r.sel[i][j]=1;
            r.rowSel[i]++;
            solve(r,idx+1,units+need,people+r.p[i][j],hc+high);
            r.sel[i][j]=0;
            r.rowSel[i]--;
        }
    }
    if(j==r.m-1 && r.rowNeed[i] && r.rowSel[i]==0) return;
    solve(r,idx+1,units,people,hc);
}

int main()
{
  Rescue r={};
  cout<<"Enter rows and columns: ";
  cin>>r.n>>r.m;
  cout<<"People matrix:"<<endl;
  for(int i=0;i<r.n;i++)
    for(int j=0;j<r.m;j++)
    {
      cin>>r.p[i][j];
      if(r.p[i][j]>0) r.rowNeed[i]=1;
    }
  cout<<"Rescue units matrix:"<<endl;
  for(int i=0;i<r.n;i++)
    for(int j=0;j<r.m;j++)
      cin>>r.u[i][j];
  cout<<"Team capacity: ";
  cin>>r.cap;
  cout<<"High risk limit (people): ";
  cin>>r.hr;
  solve(r,0,0,0,0);
  if(!r.found)
  {
      cout<<"No valid allocation exists"<<endl;
      return 0;
  }
  cout<<"Selected positions:"<<endl;
  for(int i=0;i<r.n;i++)
    for(int j=0;j<r.m;j++)
      if(r.best[i][j]) cout<<"("<<i<<","<<j<<")"<<endl;
  cout<<"People rescued: "<<r.bestPeople<<endl;
  cout<<"Units used: "<<r.bestUnits<<endl;
  cout<<"Units remaining: "<<r.cap-r.bestUnits<<endl;
  return 0;
}