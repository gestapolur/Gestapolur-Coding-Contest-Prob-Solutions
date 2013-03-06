/*
  POJ 2584
  TEST KM
  2012-07-20
  ACCEPTED
*/
#include<iostream>
#include<string>
#include<cstring>
#define MAXN 202
#define INF ( 1 << 30 ) - 1
using namespace std;

bool sync_with_stdio( bool sync = false );

int w[ MAXN ][ MAXN ];
int lx[ MAXN ] , ly[ MAXN ];
int linky[ MAXN ] , slack[ MAXN ];
bool visx[ MAXN ] , visy[ MAXN ];

const char siz[ 6 ] = { ' ' , 'S' , 'M' , 'L' , 'X' , 'T' };

int n , m , pn;
int perf[ 6 ][ 22 ];
//S M L X T
void init()
{
  string str;
  char pr[ 22 ][ 2 ];
  int i , j , tn;

  memset( linky , 0 , sizeof( linky ) );
  memset( perf , 0 , sizeof( perf ) );
  memset( w , 0 , sizeof( w ) );
  memset( lx , 0 , sizeof( lx ) );
  memset( ly , 0 , sizeof( ly ) );

  cin>>n;
  
  for( i = 1 ; i <= n ; ++ i )
    cin>>pr[ i ];
  
  for( i = 1 ; i <= n ; ++ i )
    {
      j = 1;
      while( siz[ j ] not_eq pr[ i ][ 0 ] ) ++ j;
      do{
	switch ( siz[ j ] )
	  {
	  case 'S':
	    perf[ 1 ][ ++ perf[ 1 ][ 0 ] ] = i;
	    break;
	  case 'M':
	    perf[ 2 ][ ++ perf[ 2 ][ 0 ] ] = i;
	    break;
	  case 'L':
	    perf[ 3 ][ ++ perf[ 3 ][ 0 ] ] = i;
	    break;
	  case 'X':
	    perf[ 4 ][ ++ perf[ 4 ][ 0 ] ] = i;
	    break;
	  default:
	    perf[ 5 ][ ++ perf[ 5 ][ 0 ] ] = i;
	  }
	if( siz[ j ] == pr[ i ][ 1 ] ) break;
	++ j;
      }while( 1 );
    }

  m = 0;
  for( i = 1 ; i <= 5 ; ++ i )
    {
      cin>>tn;
      while( tn -- )
	{
	  ++ m;
	  for( j = 1 ; j <= perf[ i ][ 0 ] ; ++ j )
	      w[ perf[ i ][ j ] ][ m ] = 1;
	}
    }
  cin>>str;
  pn = n;
  n = n > m ? n : m;
  return ;
}

void out()
{
  int i , cnt;
  cnt = 0;
  for( i = 1 ; i <= n ; ++ i )
    if( linky[ i ] )
      cnt += w[ linky[ i ] ][ i ];
  if( cnt not_eq pn )
    cout<<"I'd rather not wear a shirt anyway...\n";
  else
    cout<<"T-shirts rock!\n";
  return ;
}

bool find( int x )
{
  visx[ x ] = true;
  for( int y = 1 ; y <= n ; ++ y )
    {
      if( visy[ y ] )
	continue;
      int t = lx[ x ] + ly[ y ] - w[ x ][ y ];
      if( t == 0 )
	{
	  visy[ y ] = true;
	  if( linky[ y ] == 0 or find( linky[ y ] ) )
	    {
	      linky[ y ] = x;
	      return true;
	    }
	}
      else if( slack[ y ] > t )
	slack[ y ] = t;
    }
  return false;
}

void KM()
{
  int i , j , x;

  for( i = 1 ; i <= n ; ++ i )
    for( j = 1 ; j <= n ; ++ j )
      lx[ i ] = lx[ i ] > w[ i ][ j ] ? lx[ i ] : w[ i ][ j ];
  for( x = 1 ; x <= n ; ++ x )
    {
      for( i = 1 ; i <= n ; ++ i )
	slack[ i ] = INF;
      while( true )
	{
	  memset( visx , false , sizeof( visx ) );
	  memset( visy , false , sizeof( visy ) );
	  if( find( x ) )
	    break;
	  int d = INF;
	  for( i = 1 ; i <= n ; ++ i )
	    if( not visy[ i ] )
	      d = d < slack[ i ] ? d : slack[ i ];
	  for( i = 1 ; i <= n ; ++ i )
	    {
	      if( visx[ i ] )
		lx[ i ] -= d;
	      if( visy[ i ] )
		ly[ i ] += d;
	      else
		slack[ i ] -= d;
	    }
	}
    }
  
  return ;
}

int main()
{
  string str;
  while( cin>>str )
    {
      if( str == "ENDOFINPUT" ) return 0;
      init();
      KM();
      out();
    }
  return 0;
}
