import sys

def common_divisors(num):
    # Set MAX_X dynamically based on the highest number in your input list
    MAX_X = max(num)
    
    # Create the frequency array up to the maximum element
    captain = [0] * (MAX_X + 1)

    for i in num:
        # Use += 1 to correctly handle duplicate inputs
        captain[i] += 1

    # Loop from the highest number down to 1 (Reverse Sieve)
    for i in range(MAX_X, 0, -1):
        multiples_found = 0
        
        # Leap forward through the multiples of candidate 'i'
        for p in range(i, MAX_X + 1, i):
            if captain[p] > 0:
                multiples_found += captain[p]
                
        # If 2 or more elements share this factor, we found our maximum GCD
        if multiples_found >= 2:
            return i  

    return 1

if __name__ == "__main__":
    # sys.stdin.read().split() returns a list of string tokens, e.g., ['5', '3', '14', '15', '7', '9']
    input_data = sys.stdin.read().split()
    if input_data:
        # FIXED: Extract the first item using [0] to get the total number of items 'n'
        n = int(input_data[0])
        
        # Map the remaining string tokens from index 1 onwards into integer array elements
        num = list(map(int, input_data[1:n+1]))
            
        print(common_divisors(num))
