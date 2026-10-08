import sys

def find_count_subarrays(nums, n):
    # Flat fixed-size list for O(1) direct memory indexing without hashing overhead
    remainder_counts = [0] * n

    # BASE CASE: A prefix sum of 0 leaves a remainder of 0.
    remainder_counts[0] = 1
    
    prefix_sum = 0
    total_counts = 0

    for i in nums:
        prefix_sum += i

        # Calculate remainder
        rem = prefix_sum % n

        # Add the previous frequency count directly from our array slot
        total_counts += remainder_counts[rem]

        # Increment the bucket count
        remainder_counts[rem] += 1

    return total_counts


if __name__ == "__main__":
    # input_data is a flat list of string tokens, e.g., ['100', '1', '1', '1'...]
    input_data = sys.stdin.read().split()
    if input_data:
        # FIXED: Extract the first item using [0] to get the total number of items 'n'
        n = int(input_data[0])
        
        # Map the remaining string tokens into an integer generator stream
        nums = (int(x) for x in input_data[1:n+1])

        # Execute and print the final result
        print(find_count_subarrays(nums, n))
