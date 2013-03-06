/*
  POJ 2536
  KM TEST
  2012-07-20
  ACCEPTED
  hint: use s * v ? dist( i , j ) to avoid floating accuracy fault.
*/
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<cstring>
#define MAXN 102
#define INF ( 1 << 30 ) - 1

int pn , n , m , s , v;
int w[ MAXN ][ MAXN ];
int lx[ MAXN ] , ly[ MAXN ];
int linky[ MAXN ] , slack[ MAXN ];
bool visx[ MAXN ] , visy[ MAXN ];

double gx[ MAXN ] , gy[ MAXN ];
double hx[ MAXN ] , hy[ MAXN ];

double dist( double x1 , double y1 , double x2 , double y2 )
{ return sqrt( ( x1 - x2 ) * ( x1 - x2 ) + ( y1 - y2 ) * ( y1 - y2 ) ); }

void init()
{
  int i , j ;
  double d , sd;

  memset( w , 0 , sizeof( w ) );
  memset( lx , 0 , sizeof( lx ) );
  memset( ly , 0 , sizeof( ly ) );
  memset( linky , 0 , sizeof( linky ));

  for( i = 1 ; i <= n ; ++ i )
    scanf( "%lf %lf" , &gx[ i ] , &gy[ i ] );
  for( i = 1 ; i <= m ; ++ i )
    scanf( "%lf %lf" , &hx[ i ] , &hy[ i ] );

  sd = double( v * s );
  for( i = 1 ; i <= n ; ++ i )
    for( j = 1 ; j <= m ; ++ j )
      {
	d = dist( gx[ i ] , gy[ i ] , hx[ j ] , hy[ j ] );
	//printf( "%d %d %lf %lf\n" , i , j , d , sd );
	if( sd > d )
	  w[ i ][ j ] = 1;
      }

  pn = n;
  n = n > m ? n : m;
  return ;
}

void out()
{
  int cnt = 0 , i;
  /*
  for( i = 1 ; i <= n ; ++ i )
    printf( "%d " , linky[ i ] );
  printf( "\n" );
  */
  for( i = 1 ; i <= n ; ++ i )
    if( linky[ i ] )
      cnt += w[ linky[ i ] ][ i ];
  printf( "%d\n" , pn - cnt );
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
      lx[ i ] = w[ i ][ j ] > lx[ i ] ? w[ i ][ j ] : lx[ i ];

  for( x = 1 ; x <= n ; ++ x )
    {
      for( i = 1 ; i <= n ; ++ i )
	slack[ i ] = INF;
      while( true )
	{
	  memset( visx , false , sizeof( visx ) );
	  memset( visy , false , sizeof( visy ) );
	  if( find( x ) ) break;
	  int d = INF;
	  for( i = 1 ; i <= n ; ++ i )
	    if( not visy[ i ] and d > slack[ i ])
	      d = slack[ i ];
	  for( i = 1 ; i <= n ; ++ i )
	    {
	      if( visx[ i ] )
		lx[ i ] -= d;
	      if( visy[ i ] )
		ly[ i ] += d;
	      else
		slack[ i ] -=d;
	    }
	}
    }
  return ;
}

  int main()
{
  while( scanf( "%d %d %d %d" , &n , &m , &s , &v ) not_eq EOF )
    {
      init();
      //printf( "input d\n" );
      KM();
      //printf( "KM d\n" );
      out();
    } 
  return 0;
}
