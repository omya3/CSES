import sys

def binary_exp(base, exp, MOD):
    if exp == 0:
        return 1
    
    res = 1
    base = base % MOD

    while exp > 0:
        if exp & 1:
            res = (res * base) % MOD
        
        exp = exp >> 1
        base = (base * base) % MOD

    return res

def solve():
    # FIXED: Read all tokens at once to prevent multi-line input extraction bugs
    input_data = sys.stdin.read().split()
    if not input_data:
        return
        
    t = int(input_data[0])
    MOD = 10**9 + 7
    results = []
    
    # FIXED: Step through the flat list in pairs of 2 (base and exponent)
    pointer = 1
    for _ in range(t):
        base = int(input_data[pointer])
        exp = int(input_data[pointer+1])
        pointer += 2
        
        # Calculate and queue the result string
        results.append(str(binary_exp(base, exp, MOD)))
        
    # FIXED: Output all answers at once separated by a clean newline
    print('\n'.join(results))

if __name__ == "__main__":
    solve()
