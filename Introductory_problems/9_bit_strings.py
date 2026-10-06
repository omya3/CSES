def binary_exp(base, exp, MOD):

    res = 1
    base = base % MOD

    while exp>0:

        if exp&1:
            res = (res*base) %MOD
        
        exp = exp>>1

        base = (base*base) %MOD

    return res

def solve():
    exp = int(input())

    MOD = 10**9 + 7
    print(binary_exp(2, exp, MOD))
    
if __name__ == "__main__":
    solve()