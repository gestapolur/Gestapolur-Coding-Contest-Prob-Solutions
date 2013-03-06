/*
  POJ 1743
  SUFFIX ARRAY TEST
  2012-07-30
  2012-07-31
  2012-08-01
  2012-08-02
  ACCEPTED
  description: output the longest common non-overlapped sequence in a string
  hint: bipartite lenth K if found abs(sa[ i ] - sa[ j ] ) > K then is a possibel answer. 
*/
#include<cstdio>
#include<cstring>
#define MAXN 20005
#define INF 2141483647

int n , ans;
int r[MAXN] , sa[MAXN];
int wa[MAXN],wb[MAXN],wv[MAXN],bu[ MAXN ];

int inline cmp( int *tr , int a , int b , int l )
{return ((tr[a]==tr[b])&&(tr[a+l]==tr[b+l]));}

void da( )
{
  int i,j,p,*x=wa,*y=wb,*t;
  int m = 200;
  memset( bu , 0 , sizeof( bu ) );
  for(i = 0 ; i < n ; ++ i ) bu[ x[i]=r[i] ]++;
  for(i=1;i<m;i++) bu[i]+=bu[i-1];
  for(i=n-1;i>=0;i--) sa[--bu[x[i]]]=i;
  
  for(j=1,p=1;p<n;j*=2,m=p)
    {
      for(p=0,i=n-j;i<n;i++) y[p++]=i;
      for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
      for(i=0;i<n;i++) wv[i]=x[y[i]];
      memset( bu , 0 , sizeof( bu ) );
      for(i=0;i<n;i++) 
	++ bu[ wv[ i ] ];
      for(i=1;i<m;i++) 
	bu[i]+=bu[i-1];
      for(i=n-1;i>=0;i--) sa[--bu[wv[i]]]=y[i];
      for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
	x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
  return;
}

int rank[MAXN],h[MAXN];
void calheight()
{
     int i,j,k=0;
     for( i = 0 ; i < n ; ++ i ) rank[ sa[ i ] ] = i;
     for( i = 0 ; i < n ; h[ rank[ i ++ ] ] = k )
       for( k?k--:0,j=sa[rank[i]-1]; r[ i + k ] == r[ j + k ] ; k ++ );
     return;
}

inline int max( int a , int b )
{ return a > b ? a : b; }

inline int min( int a , int b )
{ return a < b ? a : b; }

inline bool find( int k )
{
  int i = 0 , j , smin , smax , mdel = 0;
  while( i < n )
    {
      j = i + 1;
      smin = sa[ i ] , smax = sa[ i ];
      while( j < n and h[ j ] >= k )
	{
	  smax = max( sa[ j ] , smax );
	  smin = min( sa[ j ] , smin );
	  ++ j;
	}
      mdel = max( smax - smin , mdel );
      if( mdel >= k ) 
	{
	  ans = k;
	  return true;
	}
      i = j;
    }
  return false;
}

void bipart()
{
  int i , j , ls , rs , mid;
  ans = 0;
  ls = 0 , rs = n / 2;
  while( ls < rs )
    {
      mid = ls + rs >> 1;
      if( find( mid ) )
	ls = mid + 1;
      else
	rs = mid;
     
    }
  
  if( ans > 3 )
    printf( "%d\n" , ans + 1 );
  else
    printf( "0\n" );
  return ;
}

void init()
{
  int p , q;
  memset( sa , 0 , sizeof( sa ) );
  memset( h , 0 , sizeof( h ) );
  memset( r , 0 , sizeof( r ) );
  scanf( "%d" , &p );
  for( int i = 1 ; i < n ;++ i )
    {
      scanf( "%d" , &q);
      r[ i - 1 ] = q - p + 100;
      p = q;
    }
  r[ n - 1 ] = 0;
  r[ n ] = 0;
  return ;
}


int main()
{
  while( scanf( "%d" , &n ) )
    {
      if( n == 0 ) return 0;
      init();
      if( n > 9 )
	{
	  da();
	  calheight(); 
	  bipart();
	}
      else
	printf( "0\n" );
    }
  return 0;
}
