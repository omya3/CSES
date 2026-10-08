import sys

def solve():
    """
    CSES Number Spiral Solution
    
    -------------------------------------------------------------------------
    VISUAL GRID DIAGRAM (Layers 1 to 4)
    -------------------------------------------------------------------------
    The grid is built of L-shaped layers (z) where z = max(row, col).
    Notice that EVEN layers increase DOWN and LEFT.
    Notice that ODD layers increase RIGHT and UP.
    
           col=1     col=2     col=3     col=4      ...
         +---------+---------+---------+---------+
    row=1|    1    |    2    |    9    |   10    |  <-- Layer 1 & 3 (Odd max)
         +---------+---------+---------+---------+
    row=2|    4    |    3    |    8    |   11    |  <-- Layer 2 (Even max)
         +---------+---------+---------+---------+
    row=3|    5    |    6    |    7    |   12    |  <-- Layer 4 (Even max)
         +---------+---------+---------+---------+
    row=4|   16    |   15    |   14    |   13    |  
         +---------+---------+---------+---------+
           (z^2)                         (z^2)
         Even Max                      Odd Max
         at (z, 1)                     at (1, z)
    -------------------------------------------------------------------------
    
    Complexity:
      - Time: O(1) per query (Direct mathematical lookup)
      - Space: O(1) auxiliary space
    """
    # Read all tokens from standard input for fast I/O performance
    input_data = sys.stdin.read().split()
    if not input_data:
        return
    
    # Extract total number of queries
    t = int(input_data[0])
    
    output = []
    idx = 1
    
    for _ in range(t):
        y = int(input_data[idx])      # Target Row
        x = int(input_data[idx+1])    # Target Column
        idx += 2
        
        # 1. Determine which L-shaped layer 'z' contains our target cell
        z = max(y, x)
        
        # 2. Match the layer parity (Even vs. Odd) to track the path direction
        if z % 2 == 0:
            # --- EVEN LAYERS ---
            # Path progresses DOWN along row y, then shifts LEFT across column x.
            # Corner cell (z, 1) holds the max layer value: z^2.
            
            if y >= x:
                # Target sits on the vertical downward-facing track.
                # Start at the absolute maximum z^2 and step back by column distance.
                ans = z * z - x + 1
            else:
                # Target sits on the horizontal top track.
                # Start right where the previous shell layer ended: (z-1)^2.
                # Step forward sequentially along the row distance.
                ans = (z - 1) * (z - 1) + y
        else:
            # --- ODD LAYERS ---
            # Path progresses RIGHT across column x, then shifts UP along row y.
            # Corner cell (1, z) holds the max layer value: z^2.
            
            if y >= x:
                # Target sits on the vertical left-side track.
                # Start right where the previous shell layer ended: (z-1)^2.
                # Step forward sequentially along the column distance.
                ans = (z - 1) * (z - 1) + x
            else:
                # Target sits on the horizontal bottom track.
                # Start at the absolute maximum z^2 and step back by row distance.
                ans = z * z - y + 1
                
        output.append(str(ans))
        
    # Flush the results sequentially
    sys.stdout.write('\n'.join(output) + '\n')

if __name__ == '__main__':
    solve()
