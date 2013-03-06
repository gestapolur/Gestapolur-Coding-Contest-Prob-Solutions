/*
  TIMUS 1517
  ACCEPTED
  SA DC3 TEST
  2012-07-27
  hint: 
  1.add B after A separate with a minimum value, calculate SA
  2.find maximum h[ i ] that sa[ i ] and sa[ i - 1 ] are in different string.
*/
#include<cstdio>
#include<cstring>
#define maxn 2000013
#define F(x) ((x)/3+((x)%3==1?0:tb))
#define G(x) ((x)<tb?(x)*3+1:((x)-tb)*3+2)

int wa[maxn],wb[maxn],wv[maxn],ws[maxn];
int c0(int *r,int a,int b)
{return r[a]==r[b]&&r[a+1]==r[b+1]&&r[a+2]==r[b+2];}
int c12(int k,int *r,int a,int b)
{if(k==2) return r[a]<r[b]||r[a]==r[b]&&c12(1,r,a+1,b+1);
 else return r[a]<r[b]||r[a]==r[b]&&wv[a+1]<wv[b+1];}
void sort(int *r,int *a,int *b,int n,int m)
{
     int i;
     for(i=0;i<n;i++) wv[i]=r[a[i]];
     for(i=0;i<m;i++) ws[i]=0;
     for(i=0;i<n;i++) ws[wv[i]]++;
     for(i=1;i<m;i++) ws[i]+=ws[i-1];
     for(i=n-1;i>=0;i--) b[--ws[wv[i]]]=a[i];
     return;
}
void dc3(int *r,int *sa,int n,int m)
{
     int i,j,*rn=r+n,*san=sa+n,ta=0,tb=(n+1)/3,tbc=0,p;
     r[n]=r[n+1]=0;
     for(i=0;i<n;i++) if(i%3!=0) wa[tbc++]=i;
     sort(r+2,wa,wb,tbc,m);
     sort(r+1,wb,wa,tbc,m);
     sort(r,wa,wb,tbc,m);
     for(p=1,rn[F(wb[0])]=0,i=1;i<tbc;i++)
     rn[F(wb[i])]=c0(r,wb[i-1],wb[i])?p-1:p++;
     if(p<tbc) dc3(rn,san,tbc,p);
     else for(i=0;i<tbc;i++) san[rn[i]]=i;
     for(i=0;i<tbc;i++) if(san[i]<tb) wb[ta++]=san[i]*3;
     if(n%3==1) wb[ta++]=n-1;
     sort(r,wb,wa,ta,m);
     for(i=0;i<tbc;i++) wv[wb[i]=G(san[i])]=i;
     for(i=0,j=0,p=0;i<ta && j<tbc;p++)
     sa[p]=c12(wb[j]%3,r,wa[i],wb[j])?wa[i++]:wb[j++];
     for(;i<ta;p++) sa[p]=wa[i++];
     for(;j<tbc;p++) sa[p]=wb[j++];
     return;
}

int n , m , hn;
int r[maxn * 3 ] , sa[maxn * 3 ];
int rank[maxn],height[maxn];
void calheight()
{
     int i,j,k=0;
     for(i=1;i<=n;i++) rank[sa[i]]=i;
     for(i=0;i<n;height[rank[i++]]=k)
     for(k?k--:0,j=sa[rank[i]-1];r[i+k]==r[j+k];k++);
     return;
}

char str[ maxn ];
void init()
{
  m = 0;
  scanf("%d" , &hn );
  getchar();
  n = 2 * hn + 1;
  for( int i = 0 ; i < hn ; ++ i )
    {
      r[ i ] = str[ i ] = getchar();
      m <= r[ i ] ? (m = r[ i ] + 1 ):m;
    }
  getchar();
  for( int i = 0 ; i < hn ; ++ i )
    {
      r[ hn + i + 1 ] = str[ hn + i + 1 ] = getchar();
      m <= r[ hn + i + 1 ] ? (m = r[ hn + i + 1 ] + 1 ):m;
    }
  getchar();
  r[ n ] = 0;
  r[ hn ] = 1;
  return ;
}

void out()
{
  int ans = 0 , res = 0;
  for( int i = 1 ; i <= n ; ++ i )
    if( ( ( sa[ i ] > hn and sa[ i - 1 ] < hn ) or ( sa[ i ] < hn and sa[ i - 1 ] > hn ) ) and ans < height[ i ] )
      { ans = height[ i ]; res = sa[ i ];}

  str[ ans + res ] = 0;
  printf( "%s\n" , str + res );
  return ;
}

int main()
{
  init();
  dc3( r , sa , n + 1 , m );
  calheight();
  out();
  return 0;
}
