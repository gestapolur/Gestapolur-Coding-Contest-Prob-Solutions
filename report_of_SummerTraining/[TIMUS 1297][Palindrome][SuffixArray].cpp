/*
  TIMUS 1297
  Suffix Array Doubling Algorithm test
  2012-07-26
  2012-07-27
  gestapolur
  ACCEPTED
  hint: 
  1.add reverse S after S and separate with a minimum value then calculate SA.
  2.find maximum h[ i ] that s[ i - 1 ] and s[ i ] in S and reverse S. 
*/
#include<cstdlib>
#include<cstdio>
#include<cstring>
#define maxn 3000

int n , m , on;
int r[maxn] , sa[maxn];
int wa[maxn],wb[maxn],wv[maxn],bu[maxn];

int cmp( int *tr , int a , int b , int l )
{return ((tr[a]==tr[b])&&(tr[a+l]==tr[b+l]));}

void da( )
{
  int i,j,p,*x=wa,*y=wb,*t;
  //for( i = 0 ; i < m ; ++ i ) bu[ i ] = 0;
  memset( bu , 0 , sizeof( bu ) );
  for(i = 0 ; i < n ; ++ i ) bu[ x[i]=r[i] ]++;
  for(i=1;i<m;i++) bu[i]+=bu[i-1];
  for(i=n-1;i>=0;i--) sa[--bu[x[i]]]=i;
  
  for(j=1,p=1;p<n;j*=2,m=p)
    {
      for(p=0,i=n-j;i<n;i++) y[p++]=i;
      for(i=0;i<n;i++) if(sa[i]>=j) y[p++]=sa[i]-j;
      for(i=0;i<n;i++) wv[i]=x[y[i]];
      //for(i=0;i<m;i++) bu[ i ] = 0;
      memset( bu , 0 , sizeof( bu ) );
      for(i=0;i<n;i++) ++ bu[ wv[ i ] ];
      for(i=1;i<m;i++) bu[i]+=bu[i-1];
      for(i=n-1;i>=0;i--) sa[--bu[wv[i]]]=y[i];
      for(t=x,x=y,y=t,p=1,x[sa[0]]=0,i=1;i<n;i++)
	x[sa[i]]=cmp(y,sa[i-1],sa[i],j)?p-1:p++;
    }
  return;
}
int rank[maxn],height[maxn];
void calheight()
{
     int i,j,k=0;
     for( i = 0 ; i < n ; i ++ ) rank[ sa[ i ] ] = i;
     for( i = 0 ; i < n ; height[ rank[ i ++ ] ] = k )
       for( k?k--:0,j=sa[rank[i]-1]; r[ i + k ] == r[ j + k ] ; k ++ );
     return;
}

inline int min( int a , int b ){ return a < b ? a : b;}

inline bool check( int p , int q , int h )
{
  if( p < q and p < on and q > on and ( p + h - 1 ) == q - ( q - on ) * 2 )
    return true;
  if( p > q and p > on and q < on and ( q + h - 1 ) == p - ( p - on ) * 2 )
    return true;
  return false;
}

void output()
{
  int tmp , preh , idx , tmax = 1 , rec = 0;
  bool sign;
  for( int i = 1 ; i < n ; ++ i )
    {
      idx = i;
      do{
	sign = check( sa[ i ] , sa[ idx - 1 ] , height[ idx ] );
	preh = height[ idx -- ];
      }while( not sign and idx and height[ idx ] <= preh and 
	      ( preh > tmax  or ( preh == tmax and min( sa[ i ] , sa[ idx - 1 ] ) < rec )));
      if( sign 
	  and (preh > tmax or ( preh == tmax and min( sa[ i ] , sa[ idx - 1 ] ) < rec )) )
	{ tmax = preh; rec = idx;}
    }
  if( tmax > 1 )
    for( int i = sa[ rec ] ; i < sa[ rec ] + tmax ; ++ i )
      printf( "%c" , r[ i ] );
    else
      printf( "%c" , r[ 0 ] );
  printf( "\n" );
  return ;
}

char str[ maxn ];
void init()
{
  memset( r , 0 , sizeof( r ) );
  scanf( "%s" , str );
  m = 0;
  n = strlen( str );
  on = n;
  r[ n ] = 0;
  for( int i = 0 ; i < n ; ++ i )
    {
      r[ i ] = str[ i ];
      r[ i + n + 1 ] = str[ n - i - 1 ]; 
      m <= r[ i ] ? m = r[ i ] + 1 : m;
    }
  n <<= 1;
  
  if( ( n & 1 ) ^ 1 )
    r[ ++ n ] = -1;
  else
    r[ n ] = -1;
  return ;
}

int main()
{
  init();
  da();
  calheight();
  output();
  return 0;
}
