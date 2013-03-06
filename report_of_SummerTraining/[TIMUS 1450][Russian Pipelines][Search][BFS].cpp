/*
  TIMUS1450
  write by gestapolur
  2012-08-08
  ACCEPTED
*/
#include<cstring>
#include<cstdio>
#include<queue>
#define MAXN 503
#define MAXE 124750
using std::queue;

int n , m;
short int vs , vt;
short int u[ MAXE ] , v[ MAXE ];
int w[ MAXE ] , next[ MAXE ];
int head[ MAXN ] , d[ MAXN ];
bool in[ MAXN ];
long long ans;

void bfs()
{
  int p , cnt = 0 , e;
  queue<int>q = queue<int>();
  q.push( vs );
  in[ vs ] = true;
  do{
    p = q.front();
    q.pop();
    in[ p ] = false;
    
    for( e = head[ p ] ; e ; e = next[ e ] )
      if( d[ v[ e ] ] < d[ p ] + w[ e ] )
	{
	  d[ v[ e ] ] = d[ p ] + w[ e ];
	  
	  if( not in[ v[ e ] ] )
	    {
	      q.push( v[ e ] );
	      in[ v[ e ] ] = true;
	    } 
	}
  }while( not q.empty() );
  
  ans = d[ vt ];
  return ;
}


void init()
{
  scanf( "%d%d" , &n , &m );
  for( int i = 1 ; i <= m ; ++ i )
    {
      scanf( "%hd%hd%d" , &u[ i ] , &v[ i ] , &w[ i ] );
      next[ i ] = head[ u[ i ] ];
      head[ u[ i ] ] = i;
    }
  scanf( "%hd%hd" , &vs , &vt );
  return ;
}

void out()
{
  if( not ans )
    printf("No solution\n");
  else
    printf("%Ld\n" , ans );
  return ;
}

int main()
{
  init();
 
  bfs();
  
  out();

  return 0;
}
