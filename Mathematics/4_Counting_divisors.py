import sys

def sieve(query):
    MAX = 1000000
    
    # FIXED: Added +1 to allocation size so index 1,000,000 is safely available
    divisors = [0] * (MAX + 1)
    
    # FIXED: Started range at 1 to prevent step-size 0 crash (ZeroDivisionError)
    for i in range(1, MAX + 1):
        for p in range(i, MAX + 1, i):
            divisors[p] += 1

    results = []

    for q in query:
        # FIXED: Look up the value from our sieve AND convert to a string
        results.append(str(divisors[q]))
    
    print('\n'.join(results))

if __name__ == "__main__":
    # FIXED: Fast input reading to process all lines at once
    input_data = sys.stdin.read().split()
    if input_data:
        t = int(input_data[0])
        
        # Build the query array out of the remaining inputs
        query = []
        for i in range(1, t + 1):
            query.append(int(input_data[i]))
        
        sieve(query)
