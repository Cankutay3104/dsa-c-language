// LeetCode "167. Two Sum II - Input Array Is Sorted" Solution

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int *left = &numbers[0];
    int *right = &numbers[numbersSize-1];
    int sum = 0;
    
    while (left < right){
        sum = *left + *right;
        if (sum < target){ left++; }
        else if (sum > target) { right--; }
        else break;
    }
    
    *returnSize = 2;

    int *result = malloc(sizeof(int) * 2);
    result[0] = left-numbers + 1;
    result[1] = right-numbers + 1;
    return result;
}