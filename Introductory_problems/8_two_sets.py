import sys

def solve():
    # Read the integer 'n' from standard input efficiently
    n = int(sys.stdin.read().strip())
    
    # Mathematical rule: a sequential list from 1 to n can only be split into 
    # two equal sums if the total sum is even. This happens only when n % 4 is 0 or 3.
    if n % 4 != 0 and n % 4 != 3:
        print("NO")
        return
        
    print("YES")
    set1 = set()
    set2 = set()
    
    # -------------------------------------------------------------
    # CASE 1: n is a perfect multiple of 4 (e.g., 4, 8, 12, 16...)
    # -------------------------------------------------------------
    if n % 4 == 0:
        # Loop 1: Takes the outermost shells (the crust) and puts them in set1.
        # It runs from 1 up to a quarter of the array length (n // 4).
        for i in range(1, n // 4 + 1):
            set1.add(i)          # Smallest remaining element from the front
            set1.add(n - i + 1)  # Largest remaining element from the back
            
        # Loop 2: Takes the innermost elements (the core) and puts them in set2.
        # It picks up exactly where Loop 1 left off and runs until the exact middle (n // 2).
        for i in range(n // 4 + 1, n // 2 + 1):
            set2.add(i)          # Medium-small element from the front half
            set2.add(n - i + 1)  # Medium-large element from the back half

    # -------------------------------------------------------------
    # CASE 2: n leaves a remainder of 3 (e.g., 3, 7, 11, 15...)
    # -------------------------------------------------------------
    else:
        # We manually separate the first three elements to form a balanced base:
        # 1 + 2 = 3. So, {1, 2} goes to set1 and {3} goes to set2.
        set1.add(1)
        set1.add(2)
        set2.add(3)
        
        # Now, the remaining numbers from 4 up to n form a perfect multiple of 4.
        # We shift your pairing logic to map across the remaining range [4, n].
        # 'shift' maps our 'i' loops correctly to ignore the first 3 elements.
        k = n - 3  # The remaining length of the array
        
        # Symmetrical crust logic for the remaining elements
        for i in range(1, k // 4 + 1):
            set1.add(3 + i)          # Front element shifted past the first 3 items
            set1.add(n - i + 1)      # Back element moving inward
            
        # Symmetrical core logic for the remaining elements
        for i in range(k // 4 + 1, k // 2 + 1):
            set2.add(3 + i)          # Front element shifted past the first 3 items
            set2.add(n - i + 1)      # Back element moving inward

    # Print the final sizes and space-separated elements efficiently
    print(len(set1))
    print(" ".join(map(str, sorted(list(set1)))))
    print(len(set2))
    print(" ".join(map(str, sorted(list(set2)))))

if __name__ == '__main__':
    solve()
