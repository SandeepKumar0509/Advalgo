## Write a program to find the ith smallest element of an array using Randomized Select.   ##


import random
import sys

# Increase recursion depth for larger test arrays
# Randomized Select is typically an iterative algorithm or uses tail recursion 
# but for demonstration we use Python's recursion limit.
sys.setrecursionlimit(2000)

def randomized_partition(A, p, r):
    """
    Selects a random pivot and partitions the array A[p..r] around it.
    This is the core partitioning step inherited from Quicksort.
    
    Args:
        A (list): The array/sub-array to partition.
        p (int): Starting index.
        r (int): Ending index.
        
    Returns:
        int: The final index of the pivot element.
    """
    # 1. Choose a random index between p and r (inclusive)
    i = random.randint(p, r)
    
    # 2. Swap the random element with the last element A[r]
    # This ensures the standard PARTITION logic works with a random pivot.
    A[r], A[i] = A[i], A[r]
    
    # Standard Lomuto partition scheme (using A[r] as the pivot)
    pivot = A[r]
    j = p - 1
    
    for k in range(p, r):
        # If current element is less than or equal to the pivot
        if A[k] <= pivot:
            j += 1
            # Swap A[j] and A[k]
            A[j], A[k] = A[k], A[j]
            
    # Put the pivot element (originally A[r]) into its correct place
    A[j + 1], A[r] = A[r], A[j + 1]
    
    return j + 1

def randomized_select(A, p, r, i):
    """
    Finds the i-th smallest element in the sub-array A[p..r] in 
    expected O(n) time.
    
    Args:
        A (list): The array/sub-array to search within.
        p (int): Starting index.
        r (int): Ending index.
        i (int): The desired rank (1-based, where 1 is the smallest).
        
    Returns:
        int/float: The value of the i-th smallest element.
    """
    if p == r:
        # Base case: sub-array has only one element
        return A[p]

    # Partition the array around a random pivot.
    q = randomized_partition(A, p, r)
    
    # j is the rank of the pivot A[q] within the sub-array A[p..r].
    # Since A[p..q] contains q - p + 1 elements, the rank is q - p + 1.
    j = q - p + 1

    if i == j:
        # Case 1: The pivot is the i-th smallest element.
        return A[q]
    elif i < j:
        # Case 2: The i-th smallest element is in the left sub-array A[p..q-1].
        # The target rank 'i' remains the same.
        return randomized_select(A, p, q - 1, i)
    else:
        # Case 3: The i-th smallest element is in the right sub-array A[q+1..r].
        # We must adjust the target rank to account for the j elements we discarded 
        # (the elements in A[p..q]).
        return randomized_select(A, q + 1, r, i - j)

# --- Example Usage ---

# Test array
data = [3, 2, 9, 0, 7, 5, 4, 8, 1, 6]
n = len(data)

# The array state is modified in place during the partitioning, 
# so we pass a copy for fresh runs.
data_copy = list(data)

# Find the 3rd smallest element (i=3)
i_target = 3
result_3rd = randomized_select(data_copy, 0, n - 1, i_target)

# Reset and find the median (5th smallest for an array of size 10)
data_copy = list(data)
i_target = 5
result_median = randomized_select(data_copy, 0, n - 1, i_target)

# Reset and find the 9th smallest element (i=9)
data_copy = list(data)
i_target = 9
result_9th = randomized_select(data_copy, 0, n - 1, i_target)


# Verification (sorted array is [0, 1, 2, 3, 4, 5, 6, 7, 8, 9])
print(f"Original Array: {data}")
print("-" * 30)
print(f"The 3rd smallest element (i=3) is: {result_3rd} (Should be 2)")
print(f"The 5th smallest element (i=5, Median) is: {result_median} (Should be 4)")
print(f"The 9th smallest element (i=9) is: {result_9th} (Should be 8)")
print("-" * 30)

# Example for a larger, unsorted array
data_large = [random.randint(1, 1000) for _ in range(50)]
n_large = len(data_large)

# Find the 15th smallest element
i_target_large = 15
result_large = randomized_select(list(data_large), 0, n_large - 1, i_target_large)

# Verify the result by sorting the original array
data_large.sort()
verification = data_large[i_target_large - 1]

print(f"Random Array Size: {n_large}")
print(f"The {i_target_large}th smallest element is: {result_large}")
print(f"Verification (from sorted array): {verification}")
