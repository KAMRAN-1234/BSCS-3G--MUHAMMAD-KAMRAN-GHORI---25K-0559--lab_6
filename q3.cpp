#include <iostream>
using namespace std;

struct Mess
{
    int n,th,r,e;
    int mn[20],mx[20],cat[20],pr[20],al[20];
    int pool[3],tot[3],ra[20],rb[20];
};

int extra(Mess &m)
{
    int s=0;
    for(int c=0;c<3;c++)
        if(m.tot[c]>m.pool[c]) s+=m.tot[c]-m.pool[c];
    return s;
}

bool solve(Mess &m,int i)
{
    if(i==m.n)
    {
        bool lo=false,hi=false;
        int high=0,low=0;
        for(int k=0;k<m.n;k++)
        {
            if(m.al[k]==m.mn[k]) lo=true;
            if(m.al[k]==m.mx[k]) hi=true;
            if(m.pr[k]>=2) high+=m.al[k];
            else low+=m.al[k];
        }
        if(!lo || !hi || high-low<m.th) return false;
        for(int k=0;k<m.r;k++)
            if(m.al[m.ra[k]]>=m.al[m.rb[k]]) return false;
        return true;
    }
    for(int v=m.mn[i];v<=m.mx[i];v++)
    {
        bool ok=true;
        for(int j=0;j<i;j++)
        {
            if(m.cat[j]==m.cat[i] && m.al[j]==v) ok=false;
            if(m.pr[j]>m.pr[i] && m.al[j]<v) ok=false;
            if(m.pr[j]<m.pr[i] && m.al[j]>v) ok=false;
        }
        if(!ok) continue;
        m.al[i]=v;
        m.tot[m.cat[i]]+=v;
        if(extra(m)<=m.e && solve(m,i+1)) return true;
        m.tot[m.cat[i]]-=v;
    }
    return false;
}

int main()
{
  Mess m={};
  cout<<"Enter number of students: ";
  cin>>m.n;
  for(int i=0;i<m.n;i++)
  {
    cout<<"Student "<<i+1<<" (min max category[1-3] priority[1-3]): ";
    cin>>m.mn[i]>>m.mx[i]>>m.cat[i]>>m.pr[i];
    m.cat[i]--;
  }
  cout<<"Breakfast, Lunch, Dinner tokens: ";
  cin>>m.pool[0]>>m.pool[1]>>m.pool[2];
  cout<<"Priority threshold: ";
  cin>>m.th;
  cout<<"Emergency tokens available: ";
  int R;
  cin>>R;
  cout<<"Number of restrictions: ";
  cin>>m.r;
  for(int i=0;i<m.r;i++)
  {
    cout<<"Student a gets less than student b (a b): ";
    cin>>m.ra[i]>>m.rb[i];
    m.ra[i]--;
    m.rb[i]--;
  }
  bool found=false;
  for(int e=0;e<=R && !found;e++)
  {
      m.e=e;
      found=solve(m,0);
  }
  if(!found)
  {
      cout<<"No valid allocation"<<endl;
      return 0;
  }
  for(int i=0;i<m.n;i++)
      cout<<"Student "<<i+1<<": "<<m.al[i]<<endl;
  cout<<"Breakfast total: "<<m.tot[0]<<endl;
  cout<<"Lunch total: "<<m.tot[1]<<endl;
  cout<<"Dinner total: "<<m.tot[2]<<endl;
  int unused=0;
  for(int c=0;c<3;c++)
      if(m.tot[c]<m.pool[c]) unused+=m.pool[c]-m.tot[c];
  cout<<"Emergency tokens used: "<<extra(m)<<endl;
  cout<<"Unused tokens: "<<unused<<endl;
  return 0;
}