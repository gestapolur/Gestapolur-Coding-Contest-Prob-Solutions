/*
  POJ 1274 
  test KM
  2012-07-18
  ACCEPTED
*/
import java.io.*;
import java.util.*;

public class poj1274 {
    
    public static final int MAXN = 302;
    public static final int INF = ( 1 << 30 ) - 1;
    public static int n , m;
    public static int lx[] = new int[ MAXN ];
    public static int ly[] = new int[ MAXN ];
    public static int linky[] = new int[ MAXN ];
    static boolean visx[] = new boolean[ MAXN ];
    static boolean visy[] = new boolean[ MAXN ];
    public static int w[][] = new int[ MAXN ][ MAXN ];
    static int slack[] = new int[ MAXN ];
    static Scanner in = new Scanner(System.in);
    static PrintStream out = System.out;
    
    public static void init(){
	int fav , tmp;
	n = in.nextInt();
	m = in.nextInt();
	Arrays.fill( linky , -1 );
	Arrays.fill( lx , 0 );
	Arrays.fill( ly , 0 );
	tmp = n > m ? n : m;
	for( int i = 1 ; i <= tmp ; ++ i )
	    for( int j = 1 ; j <= tmp ; ++ j )
		w[ i ][ j ] = 0;
	for( int i = 1 ; i <= n ; ++ i ){
	    fav = in.nextInt();
	    while( fav -- > 0 ){
		tmp = in.nextInt();
		w[ i ][ tmp ] = 1;
	    }
	}
	n = n > m ? n : m;
    }

    public static void out(){
	int cnt = 0;
	/*
	for( int i = 1 ; i <= n ; ++ i )
	    out.printf( "%d " , linky[ i ] );
	out.println();
	*/
	
	for( int i = 1 ; i <= n ; ++ i )
	    if( linky[ i ] > 0 && w[ linky[ i ] ][ i ] > 0 )
		++ cnt;
	out.println( cnt );
    }
    
    public static boolean find( int x ){
	visx[ x ] = true;
	for( int y = 1 ; y <= n ; ++ y ){
	    if( visy[ y ] == true )
		continue;
	    int t = lx[ x ] + ly[ y ] - w[ x ][ y ];

	    if( t == 0 ){
		visy[ y ] = true;
		if( linky[ y ] == -1 || find( linky[ y ] ) ){
		    linky[ y ] = x;
		    return true;
		}
	    }
	    else if( slack[ y ] > t )
		slack[ y ] = t;
	}
	return false;
    }

    public static void KM(){
	Arrays.fill( lx , INF );
	for( int i = 1 ; i <= n ; ++ i )
	    for( int j = 1 ; j <= n ; ++ j )
		lx[ i ] = w[ i ][ j ] > lx[ i ] ? w[ i ][ j ] : lx[ i ]; 

	for( int x = 1 ; x <= n ; ++ x ){
	    for( int i = 1 ; i <= n ; ++ i )
		slack[ i ] = INF;
	    while( true ){
		Arrays.fill( visx , false );
		Arrays.fill( visy , false );
		if( find( x ) )
		    break;
		int d = INF;
		for( int i = 1 ; i <= n ; ++ i )
		    if( visy[ i ] == false && d > slack[ i ] ) 
			d = slack[ i ];
		for( int i = 1 ; i <= n ; ++ i )
		    if( visx[ i ] == true )
			lx[ i ] -= d;
		for( int i = 1 ; i <= n ; ++ i )
		    if( visy[ i ] == true )
			ly[ i ] += d;
		    else
			slack[ i ] -= d;
	    }
	}
    } 
    

    public static void main( String args[] ) 
	throws Exception {
	while( in.hasNextInt() ){
	    init();
	    KM();
	    out();
	}
    }

}
/*
testdata
3 4
3 1 2 3
2 4
3 2 3 4

out : 3

4 3
1 1
2 1 2
2 1 3
2 2 3

out : 3
*/