# FIXED: Added the mandatory sys library module to support stream operations
import sys

def pow_divide_n_conquer(base, power, MOD):

    if power == 0:
        return 1
    
    res = 1
    base = base % MOD
    while power > 0:

        if power & 1:
            res = (res * base) % MOD
        
        # This works perfectly now! It successfully reduces the exponent
        power = power >> 1

        base = (base * base) % MOD
    return res
            

if __name__ == "__main__":
    # Highly optimized stream reader to handle 10^5 calculations quickly
    input_data = sys.stdin.read().split()
    if input_data:
        n = int(input_data[0])
        
        MOD1 = 10**9 + 6  # Exponent clock level (n - 1)
        MOD2 = 10**9 + 7  # Final baseline clock level (n)
        
        results = []
        pointer = 1
        
        for _ in range(n):
            a = int(input_data[pointer])
            b = int(input_data[pointer+1])
            c = int(input_data[pointer+2])
            pointer += 3
            
            # Step A: Evaluate upper tower using MOD1
            new_pow = pow_divide_n_conquer(b, c, MOD1)
            
            # Step B: Evaluate final base layer using MOD2
            ans = pow_divide_n_conquer(a, new_pow, MOD2)
            
            results.append(str(ans))
            
        # Flush output text at once for maximum competitive programming speed
        print('\n'.join(results))
