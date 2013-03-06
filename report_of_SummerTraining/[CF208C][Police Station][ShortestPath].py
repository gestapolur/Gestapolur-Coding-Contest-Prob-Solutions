#CF208C
#ACCEPTED
#2012-07-24
#gestapolur
#hint: run twice shortest path algorithm to count the number of shortest paths from 1 to i and n to i.
w = [ [ 0 for i in range( 102 ) ] for j in range( 102 ) ]
inf = 2141483647
mark = [ inf for i in range( 102 ) ]
intr = [ False for i in range( 102 ) ]
f = [ 0 for i in range( 102 ) ]
rmark = [ inf for i in range( 102 ) ]
rintr = [ False for i in range( 102 ) ]
rf = [ 0 for i in range( 102 ) ]
n = 0
m = 0

def init():
    global n , m , w
    tmp = []
    tmp = raw_input().split(' ')
    n = int(tmp[ 0 ])
    m = int(tmp[ 1 ])
    for i in range( 0 , m ):
        tmp = raw_input().split(' ')
        u = int( tmp[ 0 ] )
        v = int( tmp[ 1 ] )
        w[ u ][ v ] = 1
        w[ v ][ u ] = 1

def dijkstra():
    global mark , f , intr
    mark[ 1 ] = 0
    f[ 1 ] = 1

    for i in range( 1 , n ):
        k = 0
        tmin = inf
        for j in range( 1 , n + 1 ):
            if intr[ j ] == False and tmin > mark[ j ]:
                tmin = mark[ j ]
                k = j
        intr[ k ] = True
        for j in range( 1 , n + 1 ):
            if w[ k ][ j ] == 1 and mark[ j ] > mark[ k ] + w[ k ][ j ]:
                mark[ j ] = mark[ k ] + w[ k ][ j ]
                f[ j ] = f[ k ]
            elif w[ k ][ j ] == 1 and mark[ j ] == mark[ k ] + w[ k ][ j ]:
                f[ j ] += f[ k ]

def r_dijkstra():
    global rmark , rf , rintr
    rmark[ n ] = 0
    rf[ n ] = 1

    for i in range( 1 , n ):
        k = 0
        tmin = inf
        for j in range( 1 , n + 1 ):
            if rintr[ j ] == False and tmin > rmark[ j ]:
                tmin = rmark[ j ]
                k = j
        rintr[ k ] = True
        for j in range( 1 , n + 1 ):
            if w[ k ][ j ] == 1 and rmark[ j ] > rmark[ k ] + w[ k ][ j ]:
                rmark[ j ] = rmark[ k ] + w[ k ][ j ]
                rf[ j ] = rf[ k ]
            elif w[ k ][ j ] == 1 and rmark[ j ] == rmark[ k ] + w[ k ][ j ]:
                rf[ j ] += rf[ k ]

def count():
    snum = f[ n ]
    f[ n ] = 1
    rf[ 1 ] = 1
    tmax = snum
    rec = 0
    for i in range( 2 , n ):
        cnt = 0
        for j in range( 1 , n + 1 ):
            if w[ i ][ j ] == 1 and mark[ i ] + rmark[ j ] + 1 == mark[ n ]:
                cnt = cnt + f[ i ] * rf[ j ];
        if tmax < cnt * 2:
            tmax = cnt * 2
            rec = i

    print '%.12f' % float(float(tmax)/float(snum))
    
init()
dijkstra()
r_dijkstra()
count()
