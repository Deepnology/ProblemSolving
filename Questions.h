#ifndef _QUESTIONS_H_
#define _QUESTIONS_H_
/*一勞永逸 必考題 這些基本的東西應該國高中就該學會 全部給我背起來 愈難懂愈精深的東西愈值錢 考試拿獎學金是你過去賺錢的方法*/
/*
1dArray
ConnectRanges{
+ Given a sorted integer array where the range of elements are [0, 99] inclusive, return its missing ranges. For example, given [0, 1, 3, 50, 75], return ["2", "4->49", "51->74", "76->99"]. (MissingRangesInSortedArray.h)
[]
+ Given a sorted integer array without duplicates, return the summary of its ranges. For example, given [0,1,2,4,5,7], return ["0->2","4->5","7"]. (SummaryRangesInSortedArray.h)
[]
}
EnumerateSubArrConsecuPartitions{
+ There are n coins in a line. (Assume n is even). Two players, A and B, take turns to take a coin from one of the ends of the line until there are no more coins left. The player with the larger amount of money wins. 1. Would you rather go first or second? Does it matter? 2. Assume that you go first, describe an algorithm to compute the maximum amount of money you can win. (CoinsInLine.h)
[Recur: maxValPickFront=coins[left]+min(recur(left+2,right), recur(left+1,right-1)), maxValPickRight=coins[right]+min(recur(left,right-2), recur(left+1,right-1)), return max(maxValPickFront,maxValPickBack).][DP2D: dp[left][right]=max(coins[left]+min(dp[left+2][right],dp[left+1][right-1]), coins[right]+min(dp[left][right-2], dp[left+1][right-1])).]
+ Given a string that contains only these two characters: + and -, you and your friend take turns to flip two consecutive "++" into "--". The game ends when a person can no longer make a move and therefore the other person will be the winner. Compute all possible next state of a given string. Determine if a starting player can win with a given string. (FlipGame.h)
[Iterate over the given string and replace available ++ with --.]
[Recur: iterate over the current string from begin, replace available ++ with --, then recur down with the replaced string, if the returned status from recur is false(canNotWin), return true(canWin). Return false after iteration.]
+ Given an unsorted array, remove minimum elements from either side such that 2*min becomes more than max. (MinRemovalOfEndInArrayUntil.h)
[Recur: min=RangeMin(left,right), max=RangeMax(left,right), if(2*min>max)return 0, numRemoveLeft=recur(left+1,right), numRemoveRight=recur(left,right-1), return min(numRemoveLeft,numRemoveRight)+1.][DP2D: dp[left][right]=2*min>max? 0 : min(dp[left+1][right], dp[left][right-1]).]
+ Given an integer array v. Find [i, j] such that v[i] < v[j] and j-i is maximum. (TwoIncrElementsWMaxDistInArr.h)
[Greedy: compute a leftMin array from left to right, compute a rightMax array from right to left, compare leftMin[i] and rightMax[i] from begin, keep track of j-i, advance rightMax[j] if rightMax[j]>leftMin[i], else advance leftMin[i].]
}
FindMissingDuplicate{
IdxSeqArray{
+ Given an array of N numbers taken from 1~N. Some numbers can be repeated multiple times and some other numbers can be absent from the array. Compute the number of occurrence for each number. (FrequencyOfIdxSeqArray.h)
[Move each element (whose val=index+1) to its corresponding position and mark negative when first visit. When non-first visit (must be negative val), decrement it.]
+ Given an array A containing n distinct numbers taken from 0, 1, 2, ..., n, find the one that is missing from the array. (MissingBitIntegerInIdxSeqArray.h)
[XOR all v[i] and i.]
[For each bit j, count zeros and ones from all v[i]. If zeros>ones, the missing bit must be 1. Else, the missing bit must be 0. Remove all v[i] whose bit j is different from the missing bit. Keep track of the missing bits which forms the missing number.]
+ Given an array of size n. All elements of the array are taken from 0~n-1 in which exactly one number is missing and exactly one number has a duplicate. Find the missing and duplicate. (MissingDupPairInIdxSeqArray.h)
[XOR all v[i] and i to get xorOfMissDup. Isolate the rightmost set bit. Divide all v[i] and i into 2 groups. XOR all v[i] and i in one group to get a missORdup.]
+ Given an array of size n. All elements of the array are in range 0~(n-1), with any of these numbers appearing any number of times. Find all the duplicates. (MultiDupInIdxSeqArray.h)
[For each v[i], if v[abs(v[i])] >= 0 which means first visit, mark negative. Else, (negative menas non-first visit), add to res.]
+ Given an array nums containing n + 1 integers where each integer is between 1 and n (inclusive), prove that at least one duplicate number must exist. Assume that there is only one duplicate number, find the duplicate one. The duplicate might repeat. (SingleDupInIdxSeqArray.h)
[Multi-repeats of dup: linked list cycle. Keep track of slow and fast indices. Advance slow one step and fast two steps until they meet. Advance another index from begin and an index from slow both for one step until they meet.]
[Single-repeat of dup: XOR all v[i] and i.]
+ Given an array of numbers nums, in which exactly two elements appear only once and all the other elements appear exactly twice. Find the two elements that appear only once. (TwoDiffDupInIdxSeqArray.h)
[XOR all nums[i] to get xorOfThe2Nums. Isolate the rightmost set bit of xorOfThe2Nums. Divide all nums[i] into 2 groups. XOR all nums[i] in each group to get the 2 nums, respectively.]
}
+ Given an unsorted integer array, find the first missing positive integer. (FirstMissingPositive.h)
[Move correct positives (whose val=index+1) to their corresponding positions. Once this is done, iterate from begin to find the next position where v[i] != i + 1.]
+ Given an array of integers, every element appears twice (even times) except for one (odd times). Find the odd occur number. 
  Given an array of integers, evey number appears even times except two numbers (odd times). Find the two odd occur numbers. 
  Given an array of integers, every number appears three times except for one element which appears only once. Find the one occur number. (OddOccurNum.h)
[Find1OddOccurFromEvenOccurArr: XOR all v[i].]
[Find2OddOccurFromEvenOccurArr: XOR all v[i] to get xorOf2OddOccur. Isolate the rightmost set bit. Divide all v[i] into 2 groups. XOR all v[i] in each group to get the 2 odd occur num.]
[Find1OccurFrom3OccurArr: keep track oneOccurBits and twoOccurBits. For each v[i], twoOccurBits|=(oneOccurBits)&v[i], oneOccurBits^=v[i], threeOccurBits=oneOccurBits&twoOccurBits. Then remove threeOccurBits from oneOccurBits and twoOccurBits.]
}
FixedPositions{
DP{
+ Given an array of prices of stocks. Compute the max profit if you can complete only 1 transaction (1 buy and 1 sell). What if you can complete unlimited transactions? What if you can complete at most 2 transactions? What if you can complete at most k transactions? What if you have to cooldown for 1 day after sell? (BestTimeBuySellStock.h)
[1 transaction: one iteration to keep track of minPrice and maxProfit=max(maxProfit,price[i]-minPrice).]
[unlimited transactions: one iteration to keep track of maxProfit=max(maxProfit,maxProfit+(price[i+1]-price[i])).]
[at most 2 transactions: forward iteration to keep track an array of firstProfit sold at each price i with lowest price. Backward iteration to keep track an array of secondProfit bought at each price with highest price. The max of all (first[i]+second[i]) is the total max price.]
[at most k transactions: if k >= N/2, same as unlimited transactions. For each price[i], for j=1~k, local[i][j]=max(global[i-1][j-1],local[i-1][j]+diff), global[i][j]=max(local[i][j],global[i-1][j]). Where local[i][j]=max(profit of sell at price i w/o buy i, profit of sell at price i w/ buy i), global[i][j]=max(profit of sell at price i, profit of no sell at price i).]
[cooldown 1 day after sell: for each price i, buy[i]=max(buy[i-1],cool[i-1]-prices[i]), sell[i]=max(sell[i-1],buy[i-1]+prices[i]), cool[i]=max(buy[i-1],sell[i-1],cool[i-1]).]
}
Greedy{
+ Given gas stations on a circle, where amount of gas at each station is gas[i] and cost from current station to the next station is cost[i]. Find a gas station that you can start with to travel around the circle once. (GasStation.h)
[BruteForce: for each station, test if starting from the station can finish a route. Greedy: keep track of a global gas amount, if the global gas amount is negative after travel around the circle, there is no solution. Keep track of a local gas amount which is reset to 0 when it becomes negative, and whose next station can be a potential starting station.]
+ Given an array of non-negative integers, you are initially positioned at the first index of the array. Each element in the array represents your maximum jump length at that position. Determine if you are able to reach the last index. How to reach the last index in the minimum number of jumps? (JumpGame.h)
[]
}
LeftRightScan{
+ There are N children standing in a line. Each child is assigned a rating value. Each child must have at least one candy. Children with a higher rating get more candies than their neighbors. Compute the minimum candies to give away. (Candy.h)
[Init a vector of all 1s. Scan from left to right, if v[i] > v[i-1], res[i] = res[i-1]+1. Scan from right to left, if v[i] > v[i+1], res[i] = max(res[i], res[i+1]+1).]
+ Given an array A of N numbers. Compute an array Output[N] such that Output[i] will be equal to multiplication of all the elements of A[N] except A[i].(MultiplicationOfNums.h)
[Init a vector of all 1s. Keep track of a leftProduct (exclude cur). For each v[i] from left to right, res[i]*=leftProduct, leftProduct*=v[i]. Same to scan from the right to left.]
}
MinDist{
+ Given an array of strings. Write a function which finds the distance of any closest pair of equal strings. (ClosestRepetition.h)
[Use a map<string,int> to keep track of last occurrence index of a string.]
+ Given an array of strings and two target strings. Find the minimum distance between the two target strings. What if this method has be called repeatedly many times with different parameters? What if the two target strings can be equal? (MinDistBtw2WordsInFile.h)
[Keep track of the last occurrence indices of the two target strings.]
[Keep a map<string,vector<index>> to map each string to a vector of sorted indices of occurrence. Compute the min pair diff from 2 sorted arrays (greedy approach).]
[First determine if the 2 target strings are equal. If not equal, same as first condition. Otherwise, update the smaller one last occurrence index when seeing the target string in a loop.]
}
}
Histogram{
+ Given a series of n daily price quotes for a stock. Calculate span of stock's price for all n days. Span means the number of all left consecutive days of the given day, including the given day itself, that has a less equal price than the given day. (AllStockSpans.h)
[Keep track of a sorted stack in decreasing order from left to right. The span at each price v[i] is i-stk.top().]
+ Given an array of building heights on a straight line from east to west with windows facing west. Buildings with equal greater height neighbor buildings on their west cannot view sunset. Find all buildings from east to west that can view sunset. (BuildingsViewSunset.h)
[Keep track of a running max from right. Iterate from right, if v[i] > running max, add v[i] to res.][Use a sortedStk<index,height> with height sorted in decreasing order from left to right.]
+ Given n non-negative integers a1, a2, ..., an, where each represents a point at coordinate (i, ai). n vertical lines are drawn such that the two endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together with x-axis forms a container, such that the container contains the most water. (ContainerWMostWater.h)
[Greedy: keep track of a left and right ptr. Cur volume = min(v[left],v[right])*(right-left). Advance left if v[left] is shorter, advance right if v[right] is shorter, advance both if v[left]==v[right] until left==right.]
+ Input: a vector of buildings, where each building is represented as <start, end, height>, and is sorted by start points in ascending order. Output: a vector of highest corner points, which is represented as <point, height>. (DrawSkylineOfBuildings.h)
[Use a map1<point,<height,isStart>> to sort all points. Use another map2<height,count> to keep track of currently covered points. For each point in map1, if it is a start point, insert to map2, else remove from map2. The current highest point is the one with max height in map2.]
+ Given n non-negative integers representing the histogram's bar height where the width of each bar is 1, find the area of largest rectangle in the histogram. (LargestRectHistogram.h)
[Keep a sorted stack in ascending order from left to right. For each v[i], keep popping out stk when stk.top() >= v[i], stk.top() will be the central highest histogram (height), left boundary is next stk element (exclusive), right boundary is i (exclusive), compute area and keep track of max one. Then push v[i] on stk.]
+ Given bandwidth usage at various times and a window length. Compute for each time, the max bandwidth over the window length time interval which ends at that time. Input: an array where each entry is a pair of timestamp and corresponding bandwidth. Output: an array of pairs of timestamp and its corresponding max bandwidth within the window length ending at that timestamp. (MaxBandwidthOverWindowTimeInterval.h)
[Keep track of a Que<index,bandwidth> and a sortedQue<index,bandwidth,count> with bandwidth in decreasing order where front is the max. For each time index, pop out all smallers from back. Push current (index,bandwidth) to back. Remove all front that is out of window length. Record the max bandwidth, which is front of the Que, at current index.]
+ Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it is able to trap after raining. (TrappingRainWater.h)
[Compute a running max left height array for each v[i] from left to right, and running max right height array from right to left. For each v[i], boundary = min(left[i],right[i]), if v[i] < boundary, accumulate (boundary-v[i]).][Compute the highest height. From left to the highest height, keep track of a maxLeftHeight, if v[i] > maxLeftHeight, maxLeftHeight, else, accumulate (maxLeftHeight-v[i]). Same for the right side.]
}
InplaceRemoveReplace{
+ Remove duplicated chars from a string in place. (RemoveDupsFromUnsortedArray.h)
[Quadratic: keep track of a newEnd. For each char v[i], scan the range v[0]~v[newEnd], if found no-duplicate, insert it to v[newEnd++]. Linear: keep track of a CharSet to record visited chars. Keep track of a newEnd. For each char, insert a non-duplicate to v[newEnd++].]
- Given a string which contains only lowercase letters, remove duplicate letters so that every letter appear once and only once. You must make sure your result is the smallest in lexicographical order among all possible results.
[SortedStack: compute the count of each char. Keep a visit[] array that indicates if a char is in the sortedStk, for each char in string, decrement cur char count, continue if cur char is visited, otherwise pop out the last char in sortedStk if cur char is smaller and if the last char's count is non-zero(means it can be added later), then add cur char to back and mark visited.]
+ Given a string. Remove all "b" and replace "a" with "dd" in place. (RemoveReplaceElementFromArr.h)
[First iteration, keep track of newEnd. Assign non-b to newEnd++. Keep track of count of a. Resize the array with count of a. Second iteration from back, keep track of newEnd. Assign non-a to newEnd++. a: assign d to newEnd++, assigne d to newEnd++.]
+ Given an array and a value, remove all instances of that value in place and return the new length. Given a string, remove all 'b' and 'ac' in place. (RemoveSomeElementFromArray.h)
[Keep track of a newEnd. For each element v[i], if v[i]!=tgt, v[newEnd++]=v[i].]
+ Given a string. Replace all spaces with %20. (ReplaceAllSpacesWPercent20.h)
[Compute the count of spaces. Resize the array with countSpaces*2. Assign from the back: non-space, just assign to newEnd--. Space: assign '0' to newEnd--, assign '2' to newEnd--, assigne '%' to newEnd--.]
}
NSum{
+ Given an array S of n integers, are there elements a, b, c, and d in S such that a + b + c + d = target? Find all unique quadruplets in the array which gives the sum of target. (FourSum.h)
[Sort the array. For each num v[i], perform three sum greedy on its right.]
+ Given an array of integers (can be both positive or negative), find the three integers which multiply to give the largest product. (MaxProductOf3.h)
[Find the 3 maximum elements and 2 minimum elements. Max product will be max(max1*max2*max3, max1*min1*min2).]
+ Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? Find all unique triplets in the array which gives the sum of zero. (ThreeSum.h)
[Sort the array. For each num v[i], perform two sum greedy on its right.]
+ Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. Return the sum of the three integers. (ThreeSumClosest.h)
[Sort the array. For each num v[i], perform two sum greedy on its right.]
- Given an array of n integers nums and a target, find the number of index triplets i, j, k with 0 <= i < j < k < n that satisfy the condition nums[i] + nums[j] + nums[k] < target. (ThreeSumSmaller)
[Sort the array. For each num v[i], perform two sum greedy on its right, if sum < target, count += (end-start): fix both "i" and "end", count in all numbers from start to end-1.]
+ Given an array of integers and an integer K, find pair of integers such that their difference equals to K. (TwoDifference.h)
[Sort the array. Keep 2 ptrs from left. If diff is too big, advance the smaller one (also advance the bigger one if smaller == bigger). Else, advance the bigger one.]
+ Given an array of integers, find two numbers such that they add up to a specific target number. What if the array is sorted? 
  Design and implement a TwoSum class. It should support the following operations: add and find. add - Add the number to an internal data structure. find - Find if there exists any pair of numbers which sum is equal to the value. (TwoSum.h)
[BruteForce: enumerate all pairs. Hash table<val, idx>: keep track of visited nums and their indices.]
[Greedy: keep 2 ptrs from left and right. If sum is too big, advance the left one. Else, advane the right one. Until left points to right.]
[Use a map<val,count> to keep track of vals and their count. Find: for each pair p, find if (target-p.first) exists, and if (target-p.first)==val, it must exist at least 2.]
+ Given an abs-sorted array A and a number K, and returns a pair of indices of elements in A that sum up to K. (TwoSumAbsSortedArray.h)
[Case1, 1 positive and 1 negative: keep a potitive num ptr and a negative num ptr from right, perform two sum greedy. Case2, if Case1 not found, and target is positive. 2 positives: keep a positive num ptr from left and a positive num ptr from right, perform two sum greedy. Case3, 2 negatives: keep a negative num ptr from left and a negative num ptr from right, perform two sum greedy.]
}
Rearrange{
+ Given an array, with positive and negative integers, arrange it in such a way that, positive numbers occupy even positions and negative numbers occupy odd position. All the remaining extra positive or negative integers should be stored at the end of the array. Remember, the elements of the array should remain in the same order.(AltPosNegNumArray.h)
[Keep track of curPos, curPosVal, nxtPos, nxtPos, nxtPosVal, curNeg, curNegVal, nxtNeg, nxtNegVal. In a while loop, v[cur] = curPosVal, curPos = nxtPos, curPosVal = nxtPosVal, advance and find nxtPos and nxtPosVal. Then do same thing for curNegVal.]
+ Given an integer array. Rearrange the array into a wave like array, like a1 <= a2 >= a3 <= a4 >= a5 .... What if a1 < a2 > a3 < a4 > a5 ...? (RearrangeToWaveArray.h)
[For even i: swap if v[i]>v[i+1]. For odd i: swap if v[i]<v[i+1].]
[Sort the array (or 3way partition the array with median element). Let left points to end of 1st half, right points to end of 2nd half. Build a new array with interleaving left-- and right--.]
+ Write a function that takes a string as input and reverse only the vowels of a string. (ReverseVowelsOfString.h)
[Keep track of begin of string and end of string. If both begin and end are vowels, swap them and incr begin and decr end, else if begin is vowel, decr end, else incr begin, until begin meets end.]
+ Given a string, reverse the string word by word. (The letters' order in each word is unchanged.) Can you do it in-place? (ReverseWords.h)
[Keep track of begin of word and end of word. Reverse each word at the end of each word. Finally reverse the entire string.]
+ Rotate an array of size N by D elements to the left. (RotateArray.h)
[1. Reverse the entire array. 2. Reverse the front part. 3. Reverse the back part.]
+ Given 2 strings a and b, determine if a is a rotated version of b. (RotatedStr.h)
[Concatenation: Concatenate the string with its copy, then use any string matching algorithm to find substring. 2 Pointers: keep 2 ptrs, advance both ptrs when matching equal chars, if the equalCount==N, return true. Advance the ptr that points to a bigger char with equalCount, then advance both ptrs again until both ptrs reach end. If there exists a match, both ptrs will stop at min lexicographical char.]
+ Define the snakestring of s to be the left-right top-to-bottom sequence in which characters appear when s is written in sinusoidal fashion. The snakestring string for "Hello World!" is "e lHloWrdlo!" (SnakestringStr.h)
[1st row indices: 1 + 4*i. 2nd row indices: 0 + 2*i. 3rd row indices: 3 + 4*i.]
+ Given a string and number of rows. Return the zig zag conversion. (ZigZagConversion.h)
[vSize=numRow*2-2 (Vertical + Slash - head/tail of Slash). For each row, Vertical num index is "rowIndex + vSize*i". Slash num index is "Vertical num index + vSize - rowIndex*2". ]
+ Given two 1d vectors, implement an iterator to return their elements alternately. For example, v1 = [1, 2], v2 = [3, 4, 5, 6], return [1,2,3,4,5,6]. (ZigzagIterator.h)
[Keep track of an itr1 to v1's begin, end1 to v1's end, so for itr2 and end2. Keep track of cur vector. hasNext(): return itr1!=end1 || itr2!=end2. Next(): return interleaved *itr1++ or *itr2++ if both itr1!=end1 && itr2 != end2, otherwise, return the other itr who is != end.]
}
+ Determine if a string has all unique characters. (AllUniqueElements.h)
[Use a CharSet to keep track of 256 chars.]
+ Given an array of integers, find if the array contains any duplicates. 
  Given an array of integers and an integer k, find out whether there there are two distinct indices i and j in the array such that nums[i] = nums[j] and the difference between i and j is at most k.
  Given an array of integers, find out whether there are two distinct indices i and j in the array such that the difference between nums[i] and nums[j] is at most t and the difference between i and j is at most k. (ContainsDuplicate.h)
[Use a set to keep track of visited integers.]
[Use a map<val,index> to keep track of last occur index of visited integers.]
[]
+ Given a array of integers. Find the element that occurs more than once and whose index of first occurrence is smallest. (FirstDupInUnsortedArray.h)
[Use a hashset to keep track of visited entries.]
+ (GeneralizedMajorityElements.h)
[Majority element appears at least N/k times, which means it must appear at least once in every k distinct elements in average. Use a hashmap<val,count> to keep track of at most k distinct entries. For each v[i], insert it to hashmap, and once hashmap has k distinct entries, decrement each entry's count and remove that entry if count is 0. Once got k distinct candidates, iterate again to get count of the entries, where candidate's count > N/k will be the majority.]
+ (HighestAffinityPair.h)
[Use a hashmap<website,sortedSet<username>> to keep track of a list of usernames for each website. Enumerate all possible pairs of websites from the hashmap, then find an intersection of usernames between both sortedSet. keep track of the max intersection size.]
+ Given an array of probabilities of Republican winning individual elections. Array size is the total number of elections. Compute the probability of a Republican majority. (HouseMajority.h)
[Recur: accumulate the prob of "countWin wins from N elections", where countWin is at least N/2. Keep track of counted prob: dp[countWin][N]. Corner case: countWin==0&&N==0, 0 wins from 0 elections, prob must be 1. winProb=recur(countWin-1,N-1)*v[N-1] which means "(countWin-1 wins from N-1 elections) * cur election win prob". loseProb=recur(countWin,N-1)*(1-v[N-1]) which means "(countWin wins from N-1 elections) * cur election lose prob". Return dp[countWin][N]=winProb+loseProb.]
+ (LenOfLastWord.h)
[]
+ A majority element in an array A[] of size n is an element that appears more than n/2 times. Find the majority element. Find all elements that appear more than n/3 times. (MajorityElement.h)
[Keep track of a candidate and its count. For each v[i], if count==0, reset candidate and increment count. Else increment count if v[i] == candidate, else decrement count.]
[Majority element appears at least N/3 times, which means it must appear at least once in every 3 distinct elements in average. Use a hashmap<val,count> to keep track of at most 3 distinct entries. For each v[i], insert it to hashmap, and once hashmap has 4 distinct entries, decrement each entry's count and remove that entry if count is 0. Once got 3 distinct candidates, iterate again to get count of the entries, where candidate's count > N/3 will be the majority.]
+ (MinAndMaxInArrayWMinComp.h)
[For every pair of 2 elements, use minmax to get smaller/bigger ones (1 comparison), then compare the smaller one with the global smallest one, and compare the bigger one with the global biggest one (2 comparisons). In total, n/2 * 3 comparisons.]
+ Given n queries with a serviceTime for each query from a different client, compute an order in which to process queries that minimizes the total waiting time. (MinWaitingTime.h)
[Sort the array in ascending order. The total waiting time from all different clients till ith query is sum of all serviceTime[0]*(N-i-1) + ... + serviceTime[i-1]*1.]
+ Add a peek() method in the derived class with implementation in terms of base::next() and base::hasNext(). (PeekingIterator.h)
[Cache a bool hasPeeked and an int nxtVal.]
+ (SalaryThresholdForSmallerBudget.h)
[Sort all salaries in ascending order. Compute a prefixSum array. Based on the prefixSum array, compute a budgets array where budgets[i]=prefixSum[i]+v[i]*(N-i-1). Find the lower bound of the given budget in the budgets array. The threshold will be v[lb-1]+(budget-budgets[lb-1])/(N-lb-1).]
+ (Vector.h)
[]
*/
/*=====================================================================*/
/*
2dGrid
2dPoints{
+ A group of two or more people wants to meet and minimize the total travel distance. You are given a 2D grid of values 0 or 1, where each 1 marks the home of someone in the group. The distance is calculated using Manhattan Distance, where distance(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|. (BestMeetingPoint.h)
[This problem is converted to find the median value on x-axis and y-axis. For even points, the median can be either the left or right of the middle pair (because sum of distances from other points to both the median points are the same). For odd points, the median is the middle point. The min total distances are the sum of x distances from all points to the median point on the x-axis and the sum of y distances from all points to the median point on the y-axis.]
+ Given n points on a 2D plane, find if there is such a line parallel to y-axis that reflect the given set of points. (LineReflection.h)
[Find the maxX and minX for all points, and midX = (maxX+minX)/2. Record each point's Y value in hashMap<Xval,Yval>. For each point in the set, compute its opposite point's X value ((oppositeX + points[i].first) / 2 = midX), which is equal to 2*midX - points[i].first, then lookup the oppositeX val in hashMap which should be present as well as its Y value.]
+ Given n points on a 2D plane, find the maximum number of points that lie on the same straight line. Find the line throught most points. (MaxPointsOnALine.h)
[Enumerate all point pairs. For each starting point, keep track of map<slope,count> and samePoints.]
[Design a hash function for a line then use hashmap<Line,hashset<Point>> to enumerate all point pairs and insert <Line,Point1> and <Line,Point2> to hashmap. Line struct consists of a slope<b.y-a.y,b.x-a.x> and YIntercept<b.x*a.y-a.x*b.y,b.x-a.x>, in which both pairs' values are after canonical fraction. Line hash function is XOR of both values of its slope and both values of its YIntercept.]
+ You are given a list of pairs of points in the 2D Cartesian plane. Each point has integer x and y coordinates. How would you find the two closest points? (TwoClosestPoints.h)
[Sort the array based on x values. DivideConquerRecur: Keep track of a left and right ptrs. Corner case is less equal than 3 points, use brute force to enumerate all pairs and return the closest pair. Postorder get left and right closest pairs. Then get the closer one of the left and right pairs based on their distances. Collect all points in the current range whose x distance to midPoint is smaller than minLR pair. Sort these pairs based on their y values. Enumerate all point pairs in the collection and compare to minLR, keep track of the min distance. Return the pair with min distance.]
}
CalculateIndex{
+ Give a N*N matrix, print it out diagonally. What if N*M matrix? (IterateMatrixDiagonal.h)
[Left diagonal property: D=row+col. For D in [0...2*(N-1)], for row in [0...D], add v[row][D-row] if both row and D-row are in range.][N*M: For D in [0...N+M-2], for row in [0...D], add v[row][D-row] if both row and D-row are in range.]
+ Given an n x n 2D matrix representing an image. Rotate the image by 90 degrees (clockwise). (RotateImage.h)
[For i in [0...N/2), for j in [i...N-1-i), v[i][j]<-v[N-1-j][i]<-v[N-1-i][N-1-j]<-v[j][N-1-i]<-v[i][j].]
+ Given a 2D rectangular matrix N*M of boolean values. Determine if the matrix is the same when rotated 180 degrees. (RotateMatrix180.h)
[For i in [0...(N+1)/2], for j in [0...M], test v[i][j]==v[N-1-i][M-1-j].]
+ Given a matrix of m x n elements (m rows, n columns), return all elements of the matrix in spiral order. (SpiralMatrix.h)
[]
+ Write a program to solve a Sudoku puzzle by filling the empty cells. (SudokuSolver.h)
[DFSRecur: insert valid [1...9] to each empty cell (row,col) from (0,0) to (N-1,N-1). A valid [1...9] at an empty cell (row,col) is that the numer doesn't repeat in the cell's straight row and col as well as square region. Validate num in square region: regionSize=sqrt(N), rowOffset=row/regionSize, colOffset=col/regionSize, for iRow in [0...regionSize), jCol in [0...regionSize), check if num is repeated in each cell v[regionSize*rowOffset+iRow][region*colOffset+jCol].]
+ Determine if a Sudoku is valid. (ValidSudoku.h)
[Check if all rows have non-repeated nums. Check if all cols have non-repeated nums. Check if all square regions have non-repeated nums. Validate 3x3 square region: for iRow in [0...9), jCol in [0...9), check if each cell at v[(iRow/3)*3+jCol/3][(iRow%3)*3+jCol%3] has a repeated num.]
}
DP{
+ Given a 2D grid, each cell is either a wall 'W', an enemy 'E' or empty '0' (the number zero), return the maximum enemies you can kill using one bomb. The bomb kills all the enemies in the same row and column from the planted point until it hits the wall since the wall is too strong to be destroyed. Note that you can only put the bomb at an empty cell. (BombEnemy.h)
[For each empty cell, need to compute left, up, right, down reachable enemies, if we perform a 2D scan from up to down, left to right, we can simultaneously keep track of the count of enemies from left in each row, as well as using an array to keep track of the count of enemies from up in each column, but we don't have the count of enemies from cur to right and from cur to down, so need to precompute 2D enemy count matrices from right and from down.]
+ Given a NxM board consists of positive and negative health. Compute the minimum initial health to move from [0,0] to [N-1,M-1] while keeping a minimum health 1. (DungeonGame.h)
[Last: dp[N - 1][M - 1] = max(1 - v[N - 1][M - 1], 1). LastCol: dp[row][M - 1] = max(dp[row + 1][M - 1] - v[row][M - 1], 1). LastRow: dp[N - 1][col] = max(dp[N - 1][col + 1] - v[N - 1][col], 1). Others: minDown = max(dp[row + 1][col] - v[row][col], 1), minRight = max(dp[row][col + 1] - v[row][col], 1), dp[row][col] = min(minDown, minRight).]
+ Given glasses with volume 1 liter piled as a pyramid. Given a volume of water to pour on the top glass, compute the volume of water in the given (row,col) glass. (FillPyramidGlasses.h)
[Keep a curRow and a nxtRow. If curRow[col]>1.0, nxtRow[col] += (curRow[col] - 1.0f)/2, nxtRow[col + 1] += (curRow[col] - 1.0f)/2.]
+ Given a m x n grid filled with non-negative numbers, find a path from "top left" to "bottom right" which minimizes the sum of all numbers along its path. (MinPathSum.h)
[First: dp[rowY][colX] = grid[rowY][colX]. TopRow: dp[rowY][colX] = dp[rowY][colX - 1] + grid[rowY][colX]. LeftCol: dp[rowY][colX] = dp[rowY - 1][colX] + grid[rowY][colX]. Others: dp[rowY][colX] = min(dp[rowY - 1][colX], dp[rowY][colX - 1]) + grid[rowY][colX].]
+ Given a triangle, find the minimum path sum from top to bottom. Each step you may move to adjacent numbers on the row below. (MinPathSumInTriangle.h)
[BottomUp from last row. LastRow: dp[rowY][colX] = triangle[rowY][colX]. Others: dp[rowY][colX] = min(dp[rowY + 1][colX], dp[rowY + 1][colX + 1]) + triangle[rowY][colX].]
+ Given numRows, generate the first numRows of Pascal's triangle. Given an index k, return the kth row of the Pascal's triangle. (PascalTriangle.h)
[Pascal triangle's leftmost col and rightmost col are all 1s. Init res array with rowIndex+1 1s for each row. Loop rows from 2, loop cols from left to right, res[row][col] = res[row - 1][col - 1] + res[row - 1][col].]
[Init res array with rowIndex+1 1s. Loop rows from 2, loop cols from right to left, res[col] += res[col - 1].]
+ Given a NxM board. How many unique paths from top left corner to bottom right corner if you can only move down or right? What if obstacles present? (UniquePath.h)
[Recur: find permutations of N 'd' and M 'r'. Math: ((m-1)+(n-1))! / ((m-1)!*(n-1)!). DP: top row && left col: dp[rowY][colX] = 1. Others: dp[rowY][colX] = dp[rowY - 1][colX] + dp[rowY][colX - 1].]
[DP: obstacle: dp[rowY][colX] = 0. top left: dp[rowY][colX] = 1. Others: dp[rowY][colX] = dp[rowY - 1][colX] + dp[rowY][colX - 1].]
}
Path{
DP{
+ Given a 2D N*M matrix with obstacles, find the shortest distance of each non-obstacle to a (nearest) source. (AllShortestPathsInMatrix.h)
[For all pixels, perform BFS at each pixel if it is a source. Init a dist[][] with all INT_MAX. Mark dist[][] at a source to be 0, at an obstacle to be -1. When performing BFS, add adj pixel to queue only when the adj pixel dist[][] is greater than cur pixel dist[][]+1.]
+ Given the mobile numeric keypad. You can only press buttons that are up, left, right, or down to the current button. Given a number of movements n, find out the count of all possible number combinations. (KeyPressCombinationsInMatrix.h)
[Recur: for each valid starting button, perform DFS and accumulate count of combinations.]
[DP3D: init dp[rowY][colX][0]=0, dp[rowY][colX][1]=1. Loop from move=2 to n, if keypad[rowY][colX] is valid, accumulate dp[rowY][colX][move]=dp[rowY][colX][move-1]+dp[rowY-1][colX][move-1]+dp[rowY+1][colX][move-1]+dp[rowY][colX-1][move-1]+dp[rowY][colX+1][move-1]. Accumulate all dp[rowY][colX][n].]
+ Given a NxN matrix which contains all distinct 1 to N^2 numbers. Find the longest increasing adjacent consecutive number sequence in the matrix. (LongestIncrAdjConsecuNumSeqInMatrix.h)
[For each number in the matrix, perform DFS: keep a visitMax[][] to keep track of visited numbers' longest consecutives. visitMax[rowY][colX] = max(recur(rowY-1,colX), recur(rowY+1,colX), recur(rowY,colX-1), recur(rowY,colX+1)).]
+ Given a NxN matrix representing an island. At a given location x, y in the matrix, you can step up, down, left, and right for a particular number of steps. Calculate the probability at location x, y with a number of steps that you still remain inside the matrix. (ProbToStepInsideMatrix.h)
[DFS: keep a prob[rowY][colX][remainStepCount] which means the prob to stay inside with remainStepCount steps. Init prob[][][] with all '-1's. Cur location cur stepCount prob[rowY][colX][stepCount-1] = 0.25*recur(rowY-1,colX,stepCount-1) + 0.25*recur(rowY+1,colX,stepCount-1) + 0.25*recur(rowY,colX-1,stepCount-1) + 0.25*recur(rowY,colX+1,stepCount-1). Corner case is (stepCount==0), return 1.0 (reaches end and still remain inside: prob is 1).]
+ (ShortestDistFromAllBuildings.h)
[BFS to construct a reachableBuildingCount[][] and a sumDistToAllBuildings[][] for each empty land: Perform BFS on each building, keep a visit[][], and a distBFS from building, incr distBFS for each level, pop out elements from queue for only current level, incr reachable[][] and accumulate sumDist[][] for cur element. Record the empty land that is able to reach all buildings and has min sum of distances to all buildings.]
}
+ Given a NxM board consisting of '.'(road) and '#'(obstacle), a start position and end position. Find a path from start to end. (SearchAMaze.h)
[Perform DFS from start: keep a path of (x,y)s, mark visited locations and restore after visit, if current location is equal to end, done.]
+ Given a 2D board and a word, find if the word exists in the grid. (WordSearch.h)
[For each char in board, perform DFS: keep a path of chars, mark visited chars and restore after visit, if the path-word is equal to the target word, found.]
+ Given a 2D board and a list of words from the dictionary, find all words in the board. Each word must be constructed from letters of sequentially adjacent cell, where "adjacent" cells are those horizontally or vertically neighboring. The same letter cell may not be used more than once in a word. (WordSearch2.h)
[Insert all words to a trie. For each char in the board, perform DFS: keep a path of chars, mark visited chars and restore after visit, if found the path-word in tre, delete that word from trie and add it to res. Early return recur when current path-word is not a trie.startWith(path).]
}
SubArea{
+ Given a NxM board consisting of 0s and 1s. Find the max region size of up-down-left-right connected 1s. (AllDistinctSubAreasInMatrix.h)
[For each pixel in the matrix, perform DFS or BFS to mark up-down-left-right connected 1s as 0s and keep track of count of connected 1s.]
+ Given a 2d grid map of '1's (land) and '0's (water), count the number of islands. An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. You may assume all four edges of the grid are all surrounded by water. (NumberOfIslandsInMatrix.h)
[For each pixel in the matrix, perform DFS to mark up-down-left-right connected '1's as '0's. Keep track of the count.]
- Given a list of positions to operate, count the number of islands after each addLand operation (which turns the water at position (row, col) into a land).
[Convert 2d grid into a 1d UnionFind rootIndex array. Init the rootIndex array with m*n -1s (means non-island). When addLand, assign rootIndex[n*row+col]=n*row+col (mark cur as a new root). Union cur position with left, right, up, down positions: find root of left, right, up, down, if root is different (means different islands), rootIndex[cur]=root, cur=root. Keep track of count of number of islands.]
+ Given a NxM board consisting of colors, a target location and a target color. Change all pixels that have same colors and are left-right-up-down connected to the target location. (PaintFillAllSameColorPixels.h)
[DFS or BFS.]
+ Given a 2D board containing 'X' and 'O', capture all regions surrounded by 'X'. A region is captured by flipping all 'O's into 'X's in that surrounded region. (SurroundedRegions.h)
[In the top row, bottom row, left col, right col, find each 'O' and perform DFS to mark up-down-left-right connected 'O's as 'D's. Scan the entire matrix and mark all 'O's as 'X's and mark all 'D's as 'O's.]
}
SubRectangle{
DP{
+ Given a 2D array, find the max subarray sum in it. (MaxSubMatrixSum.h)
[2D Kadane: enumerate all possible row pairs (topRowY,bottomRowY) and accumulate in a 1D row. Perform 1D Kadane algorithm.]
+ Given a non-empty 2D matrix matrix and an integer k, find the max sum of a rectangle in the matrix such that its sum is no larger than k. (MaxSubMatrixSumNoGreaterThanK.h)
[BruteForcePrefixSums: compute prefixSums[i][j] = v[i][j] + prefixSums[i-1][j] + prefixSums[i][j-1] - prefixSums[i-1][j-1]. Enumerate all possible submatrix sum between [ii,jj] and [i,j] includsive = prefixSums[i][j] - prefixSums[ii-1][j] - prefixSums[i][jj-1] + prefixSums[ii-1][jj-1].]
[SortedPrefixSums: enumerate all possible row pairs (topRowY,bottomRowY) and accumulate in a 1D row. Keep track of a set of sorted prefixSums before cur number, find lower bound of (curPrefixSum-K) in the set, if found, which means there exists a leftPrefixSum such that (curPrefixSum-leftPrefixSum) <= K, update res = max(res,(curPrefixSum-*found)).]
}
PreProcess{
+ Given an n x n square matrix, compute all sub-square sums of size k x k where k is smaller than or equal to n. (AllSubSquareSumsInMatrix.h)
[Precompute a colLowerKSum matrix where colLowerKSum[rowY][colX] is sum of matrix[rowY][colX]~matrix[rowY][colX+K-1]. Then compute the result matrix in a manner of computing rowRightKSum, together with colLowerKSum, the result matrix will become lowerRightKSquareSum matrix.]
+ Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle containing all 1's and return its area. Find the largest square containing all 1's and return its area. (MaxRectangle.h)
[Rectangle: for each row from top to bottom, accumulate a histogram array from left to right. Once matrix[rowY][colX]==0, set histogram[colX]=0. Based on current histogram array at current row, compute max rectangle in histogram using a sorted stack. Keep track of the max area of rectangle in histogram.]
[Square: precomute a dp[][] where top row and left col are same as matrix, dp[rowY][colX] = min(dp[rowY-1][colX],dp[rowY][colX-1],dp[rowY-1][colX-1])+1 if matrix[rowY][colX]==1, dp[rowY][colX]=0 otherwise, to represent the max square border length of the upper left area of each pixel. The max dp[rowY][colX] will be the max square board length.]
+ Given a square matrix, where each cell is filled with either black or white. Find the maximum subsquare such that all four borders are filled with black pixels. (MaxSubSquareBorder.h)
[Precompute a boardLen[rowY][colX][numConsecuPixelsBelow,numConsecuPixelsRight] matrix from (N-1,M-1), if board[rowY][colX]==1, boardLen[rowY][colX][numConsecuPixelsBelow]=boardLen[rowY+1][colX][numConsecuPixelsBelow]+1, boardLen[rowY][colX][numConsecuPixelsRight]=boardLen[rowY][colX+1][numConsecuPixelsRight]+1. Use this precomputed matrix, check if square boards are valid starting with length N from top left corner to max right/bottom: top left pixel's below consecu pixel length >= curLen, right consecu pixel length >= curLen; bottom left pixel's right consecu pixel length >= curLen; top right pixel's below consecu pixel length >= curLen.]
}
+ Determine if 2 rectangles intersect. Each rectangle is defined by its bottom left corner and top right corner. Find the total area covered by the 2 rectangles in a 2D plane (the union area of the 2 rectangles). (IntersectRectangle.h)
[Intersect: Horizontal: R1.left <= R2.right && R2.left <= R1.right. Vertical: R1.bottom <= R2.top && R2.bottom <= R1.top.]
[Intersection area: (BottomLeft.x, BottomLeft.y) = (max(BottomLeft1.x,BottomLeft2.x), max(BottomLeft1.y, BottomLeft2.y)). (TopRight.x, TopRight.y) = (min(TopRight1.x,TopRight2.x), min(TopRight1.y, TopRight2.y)).]
+ An image is represented by a binary matrix with 0 as a white pixel and 1 as a black pixel.
The black pixels are connected, i.e., there is only one black region. Pixels are connected horizontally and vertically. Given the location (x, y) of one of the black pixels, return the area of the smallest (axis-aligned) rectangle that encloses all black pixels. (SmallestRectEnclosingBlackPixels.h)
[BruteForce: check each pixel to get black pixel's minLeft, maxRight, minTop, maxBottom.][DFS: DFS from an arbitrary black pixel to traverse all connected black pixels to get minLeft, maxRight, minTop, maxBottom.]
[BinarySearch: vertical direction: find the 1st black pixel from row_0->row_x (lower bound) to get minTop, find the 1st black pixel from row_N->row_x (lower bound) to get maxBottom. Determining if a row contains a black pixel is linear scan. Horizontal direction: find the 1st black pixel from col_0->col_y (lower bound) to get minLeft, find the 1st black pixel from col_M->col_y (lower bound) to get maxRight. Determining if a col contains a black pixel is linear scan.]
}
+ Given Android 9 key lock screen and numbers m and n, where 1 <= m <= n <= 9. Count the total number of patterns of Android lock screen, which consist of minimum of m keys and maximum n keys. Rules for valid pattern: 1. Each pattern must connect at least m keys and at most n keys. 2. All the keys must be distinct. 3. If the line connecting two consecutive keys in the pattern passes through any other keys, the other keys must have previously selected in the pattern. No jumps through non selected key is allowed. 4. The order of keys used matters. (AndroidUnlockPatterns.h)
[Keep a jumps[][] table. Since there are only 3 unique patterns for num 1, 2, 5, we can multiply 4 for the results of 1 and 2. DFS to compute the number of patterns of a particular length: keep track of current number and current length and visited numbers, for next available numbers from 1 to 9, as long as it's not visited and it's not a jump number or it's a jump number but been visited, we can recur down with that number and current length+1 then accumulate the result.]
+ Design a Snake game that is played on a device with screen size = width x height. The snake is initially positioned at the top left corner (0,0) with length = 1 unit. You are given a list of food’s positions in row-column order. When a snake eats the food, its length and the game’s score both increase by 1. (DesignSnakeGame.h)
[Keep a list of snake positions from head to tail. Keep a score integer. When move to U/D/L/R, check if head's U/D/L/R hits the boundary or itself and return -1, otherwise, push head, pop out tail, check if head hits food. If head hits food, erase food from list, add back tail, incr score. Return score.]
+ Implement an iterator to flatten a 2d vector. The class has a "bool hasNext()" method and a "int next()" method. (Flatten2DVector.h)
[Keep a rowItr, rowEndItr, colItr. rowItr points to the next available row, colItr points to the next element in the row pointed by rowItr. hasNext() tests only if rowItr==rowEndItr. next() not only returns the element pointed by colItr, but also advance colItr to the next non-empty element.]
+ Given a NxM board filled with 1(live) or 0(dead). Count each cell's surrounding 8 cells, if count<2||count>3, live->dead, if count==2||count==3, live->live, if count==3, dead->live. Compute the next state of the board. (GameOfLife.h)
[Use a NxM matrix to store the next state while keeping board unchanged. Then swap the next state matrix with board.][InPlace: mark '2' for live->dead(which means it was originally live, so should count in when computing its neighbor's count), mark '3' for dead->live. When counting lives of 8 neighbors, should include cells whose value is either '1'(originally live or live->live) or '2'(live->dead, which means it was originally live).]
+ Given a key board with keys layout. Initial cursor is at [0][0]. You can move the cursor up(u), down(d), left(l), right(r), and enter(!) to input a sequence of chars. Write a function to generate a sequence of movements for a given string. (KeyPressSeqInMatrix.h)
[For each char, compute its (rowY=(char-'a')/numCol,colX=(char-'a')%numCol) location. Keep track of cur location. Compute vertical and horizontal moves from cur location to target location.]
+ (KnightsTourInMatrix.h)
[]
+ The n-queens puzzle is the problem of placing n queens on an n×n chessboard such that no two queens attack each other. Return all configurations. Return the total number of distinct solutions. (NQueens.h)
[Recur: keep track of a path vector of prev Q col indices. For cur Q to be valid, the col index must not repeat prev col indices for vertical, and abs(curColIndex-prevColIndex) must not be equal to abs(curRowIndex-prevRowIndex) for diagonal.]
+ (QuadTree.h)
[]
+ You are given an array x of n positive numbers. You start at point (0,0) and moves x[0] metres to the north, then x[1] metres to the west, x[2] metres to the south, x[3] metres to the east and so on. In other words, after each move your direction changes counter-clockwise. Write a one-pass algorithm with O(1) extra space to determine, if your path crosses itself, or not. (SelfCrossing.h)
["Self Crossing" means the current moving path intersects with one of all old moving paths. There are 3 cases.]
+ Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place. (SetColRowZerosInMatrix.h)
[Scan the 1st row and 1st col to determine if they have to be set 0s. Scan the m x n matrix and set matrix[0][j] and matrix[i][0] to 0 if matrix[i][j]==0. Scan the m x n matrix and set matrix[i][j] to 0 if matrix[i][0]==0 or matrix[0][j]==0. Set 1st row and 1st col to 0s if necessary.]
+ Given two sparse matrices A and B, return the result of AB. You may assume that A's column number is equal to B's row number. (SparseMatrixMultiplication.h)
[i: [0,row size of A], j: [0,col size of A (row size of B)], k: [0,col size of B]. res[i][k]+=A[i][j]*B[j][k].]
+ (TicTacToeGame.h)
[Keep track sum of each row, each col, diag, and revDiag, where player1 add1 and player2 subtract1. Once a sum equals to N or -N, that player wins.]
+ Given a NxM board containing 0s and 1s, and unlimited 2x1 dominos. A domino can be tiled only on 2 consecutive 0s. Count the total number of ways to completely tile dominos on the board. (TileChessboardWDominos.h)
[Recur: keep track of a tiled board.]
*/
/*=====================================================================*/
/*
BinaryTree
EnumerateSubtreeConsecuPartitions{
+ (OptimalBinarySearchTree.h)
[]
+ Given n, how many structurally unique BST's (binary search trees) that store values 1...n? (UniqueBinarySearchTree.h)
[]
- Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.
[]
}
Height{
+ Given a binary tree, determine if it is height-balanced. An example of a height-balanced tree. A height-balanced tree is a tree whose subtrees differ in height by no more than one and the subtrees are height-balanced, too. (BalancedBinaryTree.h)
[]
+ (CompleteBinaryTree.h)
[]
+ Given a binary tree, find all leaves and then remove those leaves. Then repeat the previous steps until the tree is empty. (FindLeavesOfBinaryTree.h)
[]
+ Define a node in a binary tree to be k-balanced if the difference in the number of nodes in its left and right subtrees is no more than k. Given a binary tree, find a node u in the binary tree such that u is not k-balanced, but all of u's descendants are k-balanced. If no such node exists, return null. (KBalancedNodesBinaryTree.h)
[]
+ Given a binary tree, find its maximum depth. The maximum depth is the number of nodes along the longest path from the root node down to the farthest leaf node. (MaxDepthBinaryTree.h)
[]
+ Given a binary tree, find its minimum depth. The minimum depth is the number of nodes along the shortest path from the root node down to the nearest leaf node. (MinDepthBinaryTree.h)
[]
}
LCA{
+ Given a BST and three nodes. Test if the middle node is in between an ancestor node and a descendant node. (InBetweenAncestorDescendantBST.h)
[]
+ (LowestCommonAncestorBinarySearchTree.h)
[]
+ (LowestCommonAncestorBinaryTree.h)
[]
}
LevelOrder{
+ Given a binary tree, imagine yourself standing on the right side of it, return the values of the nodes you can see ordered from top to bottom. (BinaryTreeRightSideView.h)
[]
+ Given a binary tree. Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL. Initially, all next pointers are set to NULL. You may only use constant extra space. You may assume that it is a perfect binary tree. (PopulatingNextRightPtr.h)
[]
- What if the given binary tree is not perfect?
[]
}
PathSum{
+ Given a binary tree, find the maximum path sum. The path may start and end at any node in the tree. (BinaryTreeMaxPathSum.h)
[]
+ Given a binary tree and a sum, determine if the tree has a root-to-leaf path such that adding up all the values along the path equals the given sum. (BinaryTreePathSum.h)
[]
- Given a binary tree and a sum, find all root-to-leaf paths where each path's sum equals the given sum.
[]
+ Consider a binary tree in which each node contains a digit. A root-to-leaf path can be associated with a binary number--the MSB is the one at the root. Design an algorithm to compute the sum of the binary numbers represented by the root-to-leaf paths. (SumRootToLeafBinaryNumBInaryTree.h)
[]
+ Given a binary tree containing digits from 0-9 only, each root-to-leaf path could represent a number. Find the total sum of all root-to-leaf numbers. (SumRootToLeafNums.h)
[]
}
PreNode{
+ Two elements of a binary search tree (BST) are swapped by mistake. Recover the tree without changing its structure. (RecoverAlmostBinarySearchTree.h)
[]
+ Given a binary tree, determine if it is a valid binary search tree (BST). Assume a BST is defined as follows: The left subtree of a node contains only nodes with keys less than the node's key. The right subtree of a node contains only nodes with keys greater than the node's key. Both the left and right subtrees must also be binary search trees. (ValidBinarySearchTree.h)
[]
}
SameSymmetric{
+ Given two binary trees, write a function to check if they are equal or not. Two binary trees are considered equal if they are structurally identical and the nodes have the same value. (SameBinaryTree.h)
[]
- Contain tree: You have two very large binary trees: T1, with millions of nodes, and T2, with hundreds of nodes. Create an algorithm to decide if T2 is a subtree of T1.
[]
+ (SymmetricBinaryTree.h)
[]
}
Standard{
+ (AATree.h)
[]
+ (AVLTree.h)
[]
+ (BinarySearchTree.h)
[]
+ (BTree.h)
[]
+ (ClosestValBST.h)
[]
+ (KdTree.h)
[]
+ (MinFirstBST.h)
[]
+ (RedBlackTree.h)
[]
+ (SplayTree.h)
[]
}
ToBinaryTree{
+ Given inorder and postorder traversal of a tree, construct the binary tree. Note: You may assume that duplicates do not exist in the tree. (ConstructBinaryTreeFrom2Traversals.h)
[]
- Given preorder and inorder traversal of a tree, construct the binary tree. Note: You may assume that duplicates do not exist in the tree.
[]
+ Reconstruct a binary tree from a preorder traversal with marker. (ConstructBinaryTreeFromTraversal.h)
[]
- Reconstruct a binary tree from a postorder traversal with marker.
[]
}
ToBST{
+ Given an array of distinct integers that represents a BST preorder traversal, construct the BST. (ConstructBSTFromTraversal.h)
[]
- Given an array of distinct integers that represents a BST postorder traversal, construct the BST.
[]
+ Convert a BST to a sorted doubly linked list. (ConvertBSTtoCircularDoublyLinkedList.h)
[]
- Convert a sorted doubly linked list into a BST.
[]
+ Given an array where elements are sorted in ascending order, convert it to a height balanced BST. (ConvertSortedArrayToBinarySearchTree.h)
[]
+ Given a singly linked list where elements are sorted in ascending order, convert it to a height balanced BST. (ConvertSortedListToBinarySearchTree.h)
[]
+ Merge two BSTs. (Merge2BalancedBinarySearchTree.h)
[]
}
Traversal{
+ (BinaryTreeInorderSucc.h)
[]
+ Given a binary tree, return the inorder traversal of its nodes' values. Note: Recursive solution is trivial, could you do it iteratively? (BinaryTreeInOrderTraversal.h)
[]
+ Given a binary tree, return the level order traversal of its nodes' values. (ie, from left to right, level by level). (BinaryTreeLevelOrderTraversal.h)
[]
- Given a binary tree, return the bottom-up level order traversal of its nodes' values. (ie, from left to right, level by level from leaf to root).
[]
- Given a binary tree, return the zigzag level order traversal of its nodes' values. (ie, from left to right, then right to left for the next level and alternate between).
[]
+ (BinaryTreePostOrderSucc.h)
[]
+ Given a binary tree, return the postorder traversal of its nodes' values. Note: Recursive solution is trivial, could you do it iteratively? (BinaryTreePostOrderTraversal.h)
[]
+ Given a binary tree, return the preorder traversal of its nodes' values. Note: Recursive solution is trivial, could you do it iteratively? (BinaryTreePreOrderTraversal.h)
[]
+ Given a binary tree, return the vertical order traversal of its nodes' values. (ie, from top to bottom, column by column). If two nodes are in the same row and column, the order should be from left to right. (BinaryTreeVerticalOrderTraversal.h)
[]
+ Implement an iterator over a binary search tree (BST). Your iterator will be initialized with the root node of a BST. Calling next() will return the next smallest number in the BST (in-order successor). Note: next() and hasNext() should run in average O(1) time and uses O(h) memory, where h is the height of the tree. (BSTIterator.h)
[]
+ (DeleteBinaryTree.h)
[]
}
VerifyTraversal{
+ Given a string of comma separated values, verify whether it is a correct preorder traversal serialization of a binary tree. Find an algorithm without reconstructing the tree. Each comma separated value in the string must be either an integer or a character '#' representing null pointer. (VerifyPreOrderTraversalBinaryTree.h)
[]
+ Given an array of numbers, verify whether it is the correct preorder traversal sequence of a binary search tree. You may assume each number in the sequence is unique. (VerifyPreOrderTraversalBST.h)
[]
- Follow up: Could you do it using only constant space complexity?
[]
}
+ (BinaryTreeNodeWithLock.h)
[]
+ Given a binary tree where all the right nodes are either leaf nodes with a sibling (a left node that shares the same parent node) or empty, flip it upside down and turn it into a tree where the original right nodes turned into left leaf nodes. Return the new root. (BinaryTreeUpsideDown.h)
[]
+ Given a binary tree, write a function which forms a linked list from the leaves of the binary tree. The leaves should appear in left-to-right order. (ConnectBinaryTreeLeaves.h)
[]
+ Given a binary tree, count the number of uni-value subtrees. A Uni-value subtree means all nodes of the subtree have the same value. (CountUnivalueSubtrees.h)
[]
+ Given a binary tree, print the nodes on the path from the root to the leftmost leaf in that order, then the leaves from left-to-right, then the nodes from the rightmost leaf up to the root. (ExteriorNodesBinaryTree.h)
[]
+ Given a binary tree, flatten it to a linked list in-place. If you notice carefully in the flattened tree, each node's right child points to the next node of a pre-order traversal. (FlattenBinaryTreeToLinkedList.h)
[]
+ Given a nested list of integers, implement an iterator to flatten it. Each element is either an integer, or a list -- whose elements may also be integers or other lists. (FlattenNestedListIterator.h)
[Use a stack to store pointers to NestedInteger(can be either an integer or a list of NestedIntegers) from right to left in the given array. hasNext(): if the top of the stack is an integer, return true, otherwise, pop the stack and push all elements in the popped list to stack, until the top element is an integer. next(): pop out and return the top integer(must be an integer instead of a list) in the stack.]
+ Given a set of symbols a-z with corresponding frequencies, find a code book that has the smallest average code length. (HuffmanCoding.h)
[]
+ Invert a binary tree. (InvertBinaryTree.h)
[]
+ Given a binary tree, find the largest subtree which is a Binary Search Tree (BST), where largest means subtree with largest number of nodes in it. Note: A subtree must include all of its descendants. (LargestBSTSubtree.h)
[]
+ Given a binary tree, find the size of the largest independent set of nodes. A set of nodes in a tree is independent if there are no edges directly connecting them in a father-children relation. Or a subset of all tree nodes is an independent set if there is no edge between any two nodes of the subset. (LargestIndependentSetBinaryTree.h)
[]
+ Given a binary tree, find the length of the longest consecutive sequence path. The path refers to any sequence of nodes from some starting node to any node in the tree along the parent-child connections. The longest consecutive path need to be from parent to child (cannot be the reverse). (LongestConsecutivePathBinaryTree.h)
[]
+ Given a nested list of integers, return the sum of all integers in the list weighted by their depth from root to leaf. Each element is either an integer, or a list -- whose elements may also be integers or other lists. What if the depth is reversed from leaf to root? (NestedListWeightSum.h)
[DFS.][Compute the max depth using DFS, then DFS.]
+ (TheNearestRestaurantProblem.h)
[]
+ Find two nodes from a binary search tree that sum to a target value. (TwoSumBinarySearchTree.h)
[]
*/
/*=====================================================================*/
/*
BitNumOperation
Bit{
Basic{
+ Count number of 1s of the binary representation of a given integer. (CountSetBits.h)
[n & (n - 1): flip the lowest set bit to 0. Count lowest set bits.]
+ Count number of 1s of the binary representations of a series of numbers from 1 to n. (CountSetBitsFrom1toN.h)
[dp[i] = i & 1 + dp[i >> 1].]
+ Determine the number of bits required to convert integer A to integer B. (DiffBitsBtw2Int.h)
[Count number of 1s of A^B.]
+ Get an integer n and an index. Get/Set/Toggle the bit at the index in n's binary representation. (GetSetToggleBit.h)
[Get: ((n & (1 << index)) > 0). Set1: n | (1 << index). Set0: n & ~(1 << index). Toggle: n ^ (1 << index).]
+ Given an unsigned number with only one bit set (must be power of 2). Find the position of this bit. (IndexOfOnlyOneSetBit.h)
[1. check if pow of 2: n&(n-1)==0. 2. linearly shift or binary search.]
+ Flip all the set bits of a given integer n except the rightmost one. (IsolateRightmostSetBit.h)
[n & -n. n & (~n + 1). n & ~(n - 1). n & (n^(n - 1)).]
+ The mask of trailing zeros is an integer with corresponding trailing 1s. (MaskOfTrailingZeros.h)
[Isolate the rightmost set bit (n & -n), then subtract it by 1. Which is (n & -n) - 1.]
+ Multiply a number n by 7 using bitwise operator. (MultiplyBy7.h)
[8*n-n: (n << 3) - n.]
+ The parity of a binary word is 1 if the number of 1s in the word is odd; otherwise, 0. (ParityOfNum.h)
[Naive: flip 0 for count of set bits. Advanced: XOR upper 16 to lower 16, then upper 8 to lower 8, then upper 4 to lower 4, then use a cached lookup table (contains 2^16 4-bit nums' parity) to check the 4 bit number is parity or not.]
+ Determine if a given integer n is power of 2. (PowOf2.h)
[n & (n - 1): flip the lowest set bit to 0.]
+ Determine if a given integer n is power of 3. (PowOf3.h)
[n <= 0 ? false : n == pow(3, round(log(n) / log(3))).]
+ Determine if a given integer n is power of 4. (PowOf4.h)
[(n & (n - 1)) == 0 && (n & 0x55555555) != 0. isPowOf2 && even0s.]
+ Swap odd and even bits of a given integer n. (SwapOddEvenBits.h)
[((n & 0xaaaaaaaa) >> 1) | ((n & 0x55555555) << 1).]
+ Swap two bits at idx1 and idx2 of a given integer n. (SwapTwoBits.h)
[if (((n >> idx1) & 1) != ((n >> idx2) & 1)) n ^= (1 << idx1) | (1 << idx2).]
+ The tow's complement of a number n behaves like the negative of the original number. (TwosComplement.h)
[~n + 1. ~(n - 1).]
}
MathFunc{
+ Add two numbers a and b without using arithmetic operations. (Add2IntWoArithmeticOp.h)
[while b != 0, compute sum = a^b, carry = a&b << 1, a = sum, b = carry. Return a.]
+ Divide two integers dvd and dvs without using multiplication, division and mod operator. (Divide2IntWoMulDivMod.h)
[1. find i such that dvs*2^i <= dvd < dvs*2^(i+1). 2. subtract dvd by dvs*2^i and add 2^i to res until dvd < dvs. Where *2^i is done by left shifting i bits.]
+ Given two numbers and compute which one is greater without using < or >. (MaxOf2NumWoComp.h)
[Max: a-=b, a&(~a)>>63 (let a AND its complement sign bit), a+=b, return a. Min: a-=b, a&a>>63 (let a AND its sign bit), a+=b, return a.]
+ Multiply two numbers a and b without using * or +. (Mul2IntWoArithmeticOp.h)
[Make sure b >= 0. Keep adding a and b if (b & 1 == 1), and a <<= 1, b >>= 1, while b != 0. Use Add2IntWoArithmeticOp.h.]
}
+ Given a range [m, n] where 0 <= m <= n <= INT_MAX, return the bitwise AND of all numbers in this range, inclusive. (BitwiseANDDofNumRange.h)
[Right shift both m and n to right until they are equal to find common left bits. Common left bits will be kept after bitwise AND. Insert 0s to the right of the common bits.]
+ Given an unsigned 64-bit integer x and return y != x such that y has the same weight as x, and the difference of x and y is as small as possible. (ClosestNumWSameBits.h)
[Swap the first 2 consecutive bits that diff from right.]
+ Find the lenght of longest continuous 0s of the binary representation of a given integer. (LongestContinuousBinaryOs.h)
[Flip the rightmost digit of each continuous 0s segment from 0 to 1: n |= n << 1.]
+ Given a number, return true if n is divisible by 3, else false. (MultipleOf3.h)
[If difference between count of odd set bits and even set bits is multiple of 3, then is the number.]
+ Given a number, return true if n is divisible by 9, else false. (MultipleOf9.h)
[n%9.][sum all digits of n and test if sum is a multiple of 9.]
[Bitwise Recur: keep track of curNum, if curNum==0||curNum==9, return true, if curNum<9, return false, return recur(curNum>>3-curNum&7) (which means floor(n/9) - n%8).]
+ Given an integer, find the next big and next small integer that has same number of 1s in its binary representation. (NextPrevNumWSameBits.h)
[Next big: find ascendingEnd from right, reverse n[ascendingEnd]~n[end], find upper bound<less> of n[ascendingEnd-1] in n[ascendingEnd]~n[end] and swap. Prev small: find descendingEnd from right, reverse n[descendingEnd]~n[end], find upper bound<greater> of n[descendingEnd-1] in n[descendingEnd]~n[end] and swap.]
+ Given an integer, reverse the bits in its binary representation. (ReverseBits.h)
[Iteratively swap 2 bits from the leftmost and rightmost.]
+ Given 2 integers N, M and 2 indices lower, higher. Subsitute the bits in the range [higher, lower] in N with the bits in M. (SetSubstrBits.h)
[Create a mask which looks like 1111100000001111. N &= mask. N |= (M << lower).]
+ Given 2 integers, swap them in place. (SwapInPlace.h)
[a=a^b, b=a^b, a=a^b. a=a-b,b=a+b,a=b-a.]
}
Code{
+ EliasGamma: Encode a series positive numbers by transforming each number into "(numOfBits-1) 0s + binary". (EliasGammaEncodedString.h)
[For i in [0:N-1], binStr=IntToBinStr(nums[i]), binStr.insert(binStr.begin(), binStr.size()-1, '0'), res+=binStr. Return res. IntToBinStr(n): while n!=0, lsb=n%2, n/=2, res=to_string(lsb)+res. Return res.]
- Decode: count consecutive 0s from begin till a first 1, which is the begin of binary. Transform the binary starting from the first 1 with length of "numOfConsecutive0s + 1" into decimal. Remove the transformed binary and repeat.
[While i<N {nxtIdx=i, while nxtIdx<N&&s[nxtIdx]=='0', ++nxtIdx, res.push_back(BinStrToInt(s[i:nxtIdx])), i=nxtIdx.} Return res. BinStrToInt(s): for i in [0:N-1], res=res*2+s[i]-'0'. Return res.]
+ Design an algorithm to encode a list of strings to a string. The encoded string is then sent over the network and is decoded back to the original list of strings. (EncodeDecodeStrings.h)
[Encode: len1#str1len2#str2...lenN#strN. Decode: keep a len integer, accumulate len=len*10+char-'a', skip a '#', append substr(i,len).]
+ The gray code is a binary numeral system where two successive values differ in only one bit. Given a non-negative integer n representing the "total number of bits" in the code, print the sequence of gray code. A gray code sequence must begin with 0. (GrayCode.h)
[res.push_back(0). For i in [0:n-1], curSize=res.size, for j in [curSize-1,0], res.push_back(res[j]|(1<<i)) (pad a '1' bit to the left side of each binary code in the reversed list and then append to the original list). Return res.]
+ RunLengthEncoding: encode successive repeated characters by the repetition count and the character. "aabcccccaaa" should return a2b1c5a3. (RunLengthEncodedString.h)
[Encode: lastChar=s[0], sameCount=1, for i in [1:N-1], if s[i]==lastChar {++sameCount}, else {res+=lastChar, res+=to_string(sameCount), lastChar=s[i], sameCount=1}. res+=lastChar, res+=to_string(sameCount). Return res.]
[Decode: for i in [0:N-1], if isdigit(s[i]), count=count*10+s[i]-'0', else {res.append(count,s[i]), count=0}. Return res.]
+ (TransformRunLengthEncodedStr.h)
}
ConvergeTo1{
+ If n is even, n/=2. If n is odd, n=3*n+1. Repeat it indefinitely and it will reach 1. How would you test the Collatz Conjecture for the first n positive integers? (CollatzConjecture.h)
[For each num i starting from 2, compute its next until its value is smaller than i (which means we have already tested that val). Keep track of those greater equal values, if found a repeat, early return false. Improve: keep a global visited odd num map.]
+ Starting with any positive integer n, replace n by the sum of the squares of its digits, and repeat the process until n equals 1 (where it will stay) (which is a happy number), or it loops endlessly in a cycle which does not include 1. Determine if a given integer is happy. (HappyNumber.h)
[Recur while keep track of visited nums. If found a repeat, early return false.]
}
ConvertBase{
+ Given a string that contains digits in base1. Convert the string to base2. (Base1ToBase2.h)
[For each digit s[i], compute decimal = decimal * b1 + (isDigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10). Compute reminder = decimal % b2, res.push_back(reminder >= 10 ? 'A' + reminder - 10 : '0' + reminder), decimal /= b2, while decimal != 0.]
+ Compute the Excel column encoding and decoding. Decode: A->1, B->2, ..., Z->26, AA->27, AB->28, .... Encode: reverse. (ConvertExcelColumnId.h)
[Encode: for each char c, res = res * 26 + (c - 'A' + 1). Decode: res.insert(res.begin(), (n - 1) % 26 + 'A'), n = (n - 1) / 26, while n != 0.]
+ Given an integer, return a string as an English phrase that describes the integer. (IntegerToEnglish.h)
[For each thousands (3 digits) from right, compute res = From1to999(n%1000) + Thousands[i] + res, n/=1000. 1. Thousands: {"", "Thousand", "Million", "Billion"}. 2. From1to999: If n >= 100, res += Digits[i] + "Hundred", n/=100. If n >= 11 && n <= 19, res += Teens[i], else, if n == 10 || n >= 20, res += Tens[i], n/= 10, if n >= 1 && n <= 9, res += Digits[i].]
+ Convert an integer to a string that represents the digits of the integer. (IntToDecimalStr.h)
[While n!=0, res.insert(res.begin(), n%10), n/=10. Return res.]
- Convert a string that represents the digits of an integer to an integer.
[For i in [0:N-1], res=res*10+s[i]-'0'. Return res.]
+ The Roman numeral representation of positive integers uses the symbols I,V,X,L,C,D,M. Each symbol represents a value: I: 1, V: 5, X: 10, L: 50, C: 100, D: 500, M: 1000. Convert a Roman numeral to an integer. (RomanToInteger.h)
[SymToVal={{'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000}}. Ints={1000,900,500,400,100,90,50,40,10,9,5,4,1}. Romans={"M","CM","D","CD","C","XC","L","XL","X","IX","V","IV","I"}. Pay attention to special cases for 4 and 9.]
[RtoI: for i in [0:N-1], if i<N-1&&SymToVal[s[i]]<SymToVal[s[i+1]], res-=SymToVal[s[i]] (for special cases of 4 and 9), else, res+=SymToVal[s[i]]. Return res.]
- Convert an integer to a Roman numeral.
[ItoR: for i in [0:12] {while curNum>=Ints[i] {curNum-=Ints[i],oss<<Romans[i]}}. Return ossToStr.]
+ Convert a string that represents the digits of an integer to an integer. (StringToInteger.h)
[res=0, for i in [0:N-1], res=res*10+s[i]-'0'. Return res.]
+ Convert an unsigned integer n to binary string. (UIntToBinStr.h)
[Use bit mask. For i in [1<<31:0,i>>=1), if n&i, oss<<1, else, oss<<0. Return ossToStr.]
}
CountNums{
+ Count the number of positive integer less than N that does not contain digit 4. (Count1toNWoDigit4.h)
[Recur. Base case: if (n<4) return n. If (n>=4&&n<=9), return n-1. General: if (msd<4), return msd*pow9 + recur(n%pow10). If (msd==4), return (msd-1)*pow9 + recur(pow10-1). If (msd>4), return (msd-1)*pow9 + recur(n%pow10).]
+ Count the number of "digit-2"s that appear in all the numbers between 0 and n. (NumOf2s.h)
[For each digit in the number: if digitNum < 2: roundDown / 10. If digitNum > 2: roundUp / 10. IF digitNum == 2: roundDown / 10 + right + 1.]
+ Given an integer n, return the number of trailing zeroes in n!. (TrailingZerosInFactorial.h)
[BruteForce: count number of factor 5s in each number from 2 to n. Advanced: total number of factor of 5s in [1...n] = count of nums in [1...n] that has factorOf5 + count of nums in [1...n] that has factorOf25 + count of nums in [1...n] that has factorOf125 + count of nums in [1...n] that has factorOf625 + ....]
}
EnumeratePermutationsCombinations{
+ The digits of a number can be divided into several parts such that the later part is the sum of 2 consecutive former parts. Determine whether a given number is an aggregated number or not. (AggregatedNumber.h)
[Enumerate all possible length combinations of first 2 parts, which can range from 1 to N/2. For each combination, check if it is a valid aggregated number.
For firstLen in [1:N/2], for secondLen in [1:N/2], if valid(firstLen,secondLen) return true. Return false. valid(firstLen,secondLen): first=num[0:firstLen-1], second=num[firstLen:firstLen+secondLen-1], res=first+second, if res.size==num.size, return false, while res.size<num.size {if first[0]=='0'&&first.size>1||second[0]=='0'&&second.size>1, return false, third=Add2(first,second), res+=third, first=second, second=third}, return res.size==num.size&&res==num.]
+ Given a length N, count all possible distinct binary strings of length N such that there are no consecutive 1's. (BinaryStrWoConsecu1s.h)
[DP1D: dpEnd0[i]=num of possible binary strs w/o consecu 1s with len=i-1 ending in 0. dpEnd1[i]=num of possible binary strs w/o consecu 1s with len=i-1 ending in 1. Init dpEnd0[0]=1, dpEnd1[0]=1. For i in [1:n-1], dpEnd0[i]=dpEnd0[i-1]+dpEnd1[i-1], dpEnd1[i]=dpEnd0[i-1]. Return dpEnd0[n-1]+dpEnd1[n-1].]
+ Given a positive integer n, break it into the sum of at least two positive integers and maximize the product of those integers. Return the max sum. (IntegerBreak.h)
[Recur: keep track of curNum, if curNum==1, return 0, if curNum==2, return 1, if curNum==3, return 2, return max(2*max(curNum-2,recur(curNum-2)),3*max(curNum-3,recur(curNum-3))).]
[DP1D: dp[i] = max(2 * dp[i-2], 3 * dp[i-3]).]
[Observation: n%3==1: 3^(n/3-1) * 4, n%3==2: 3^(n/3) * 2, n%3==0: 3^(n/3).]
+ Given a positive integer n, find the least number of perfect square numbers (1, 4, 9, 16, ...) which sum to n. (PerfectSquares.h)
[DP: dp[i]=least num of perfect squares that sum to i. dp[0]=0. For i in [1:n], for j*j in [1:i], dp[i]=min(dp[i],dp[i-j*j]+1). Return dp[n].]
[FourSquareTheorem: every natural number can be represented as the sum of four integer squares, which means res is at most 4 and can still be lesser than 4. Remove all 4's factors from n. If n%8==7, return 4, else, (res can be 3 or 2 or 1) enumerate all pair perfect squares that sum to n, if found any pair, res can be 2 or 1, if not found, res must be 3.
while n%4==0, n/=4. if n%8==7, return 4. else, res=3, for a*a in [0:n], b=sqrt(n-a*a), if a*a+b*b==n {res=!!a+!!b, break}, return res.]
}
Fraction{
+ Convert a decimal (double) to a binary string. (DecimalToBinStr.h)
[fracNum=decimal-intNum. While fracNum>0 {if fracNum==1 {fracStr+="1", break}, r=fracNum*2, if r>=1 {fracStr+="1", fracNum=r-1}, else {fracStr+="0", fracNum=r}}. Early break while if fracStr size is greater than some val. Return fracStr.]
+ Given two integers representing the numerator a and denominator b of a fraction, return the fraction in string format. If the fractional part is repeating, enclose the repeating part in parentheses.(DivisionToDecimalStrWRepeat.h)
[res=to_string(a/b)+".". remainder=a%b. Keep a remainderToRepeatIdx<long,idx>. idx=0, while remainder!=0 {if remainderToRepeatIdx.count(remainder)==0, remainderToRepeatIdx[remainder]=idx, else, {fracStr.insert(remainderToRepeatIdx[remainder],'('),fracStr+=')',break}, remainder*=10, fracStr+=to_string(remainder/b), remainder%=b, ++idx}. Return res+fracStr.]
}
MathFunc{
+ Implement factorial(x). (Factorial.h)
[Recur: if x==0, return 1, return x*recur(x-1).]
[Iterate: res=1, for i in [2:x], res*=i. Return res.]
+ Implement GCD(a,b) with or without using multiplication/division/modulus. (GreatestCommonDivisor.h)
[Use mod: while a {tmp=a, a=b%a, b=tmp}. return b.]
[Use subtract: while a!=b {if a>b, a-=b, else, b-=a}. Return a.]
[WoMulDivMod Recur: If both a and b are even, divide both by 2 with '>>1' and multiply its result by 2 with '<<1', else if one is even one is odd, divide the even num by 2, else both are odd, use subtraction.
if a==0, return b, if b==0, return a, if !(a&1)&&!(b&1), return recur(a>>1,b>>1)<<1, if !(a&1)&&(b&1), return recur(a>>1,b), if (a&1)&&!(b&1), return recur(a,b>>1), if a>b, return recur(a-b,b), return recur(a,b-a).]
- Implement CanonicalFraction(a,b).
[gcd=GCD(a,b), a/=gcd, b/=gcd, return b<0?{-a,-b}:{a,b}.]
+ Implement LCM(a,b). (LeastCommonMultiple.h)
[Use GCD: return a*b/GCD(a,b).]
[Use add: max=max(a,b). while true {if max%a==0&&max%b==0, break, ++max}, return max.]
+ Implement Log2(x). (Log.h)
[Equivalent to find the index of highest bit set. Linear: res=0, while x>>=1, ++res. Return res.]
+ Implement x%y. (Modulus.h)
[Use subtract. posX=abs(x), posY=abs(y), while posX>=posY, posX-=posY. res=x<0?-posX:posX. Return res.]
+ Implement pow(x, n)=x^n. (Pow.h)
[BinaryIterate: res=1, base=x. while n!=0, if n&1, res*=base, n/=2, base*=base. Return res.]
+ Implement "int sqrt(int x)" and "double sqrt(double x)". (Sqrtx.h)
[Int: Binary search the upper bound of sqrt(x), then upper bound - 1 will be floor or exact value of sqrt(x). left=1, right=x, while left<=right, mid=(left+right)/2, if mid*mid<=x, left=mid+1, else, right=mid-1. Return left-1.]
[Double: Binary search the lower bound of sqrt(x), then lower bound will be ceil of exact value of sqrt(x). If comp(x,1)==-1, left=x, right=1, else, left=1, right=x. While comp(left,right)==-1, mid=left+(right-left)*0.5, if comp(mid*mid,x)>=0, right=mid, else, left=mid. Return left. int comp(a,b): diff=(a-b)/b, return diff<-epsilon?-1:diff>epsilon.]
+ Calculate pow(a,b) mod 1337 where a is a positive integer and b is an extremely large positive integer given in the form of an array. (SuperPow.h)
[res=1. For i in [0:N-1], res=binaryPow(res,10)*binaryPow(a,b[i])%1337. Return res. binaryPow(x,n): res=1, base=x%1337. while n!=0, if n&1, res=res*res%1337, n/=2, base=base*base%1337. Return res%1337.]
+ Test if a given number is a perfect square. (ValidPerfectSquare.h)
[Binary search the lower bound. left=1, right=n/2+1, while left<=right, mid=left+(right-left)/2, if mid*mid>=n, right=mid-1, else, left=mid+1. Return left*left==n.]
+ Calculate (x^y)%z without pow(). (XpowYmodZ.h)
[Same as SuperPow.h]
}
MimicArithmetic{
+ Given two binary strings, return their sum (also a binary string). (Add2BinaryStr.h)
[Same as Add2IntStr.h]
+ You are given two linked lists representing two non-negative numbers. The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list. (Add2IntLinkedList.h)
[carry=0. curNode=dummyHead. while curNode1||curNode2 {sum=carry, if curNode1 {sum+=curNode1->val, curNode1=curNode1->next}, if curNode2 {sum+=curNode2->val, curNode2=curNode2->next}, curNode->next=new Node(sum%10), curNode=curNode->next, carry=sum/10}. If carry, curNode->next=new Node(carry). Return dummyHead->next.]
+ Given two numbers represented as strings, return sum of the numbers as a string. (Add2IntStr.h)
[N=max(N1,N2), res(N+1,'0'), carry=0, i1=N1-1, i2=N2-1, for i in [N:0], sum=carry+(i1>=0?num1[i1--]-'0':0)+(i2>=0?num2[i2--]-'0':0), res[i]=sum%10+'0', carry=sum/10. Remove heading 0. Return res.]
+ Write a function that takes a "single digit" stream and returns the whole number incremented by 1. (IncrementDigitStream.h)
[Keep a global digitPrior9 (whose value isn't 9), count9, and curNum that exclude digitPrior9 and count9 of 9s. The incremented num would be curNum+(digitPrior9+1)+(count9 of 0s). On inputting a new digit, if digit==9, ++count9, else (add all digitPrior9 and count9 to curNum), {if digitPrior9, curNum+=digitPrior9-'0', while count9--, curNum+='9', digitPrior9=digit}. Then increment curNum with digitPrior9 and count9.]
+ Given two numbers represented as strings, return multiplication of the numbers as a string. (Multiply2IntStr.h)
[Multiply num1[i] with each digit of num2 from right to left plus the carry, save the sum % 10 in res[i+j+1], save the carry in res[i]. Remove heading 0s: res(N1+N2,'0'), for i in [N1-1:0], carry=0, for j in [N2-1:0] {sum=carry+(res[i+j-1]-'0')+(num1[i]-'0')*(num2[j]-'0'), res[i+j-1]=sum%10+'0', carry=sum/10}, res[i]=carry+'0'. Remove heading 0s. Return res.]
+ Given a number represented as an array of digits, plus one to the number. (PlusOne.h)
[carry=1, for i in [N-1:0], v[i]+=carry, carry=v[i]/10, v[i]=v[i]%10. If carry, insert 1 to front. Return v.]
+ Given a non-negative number represented as a singly linked list of digits, plus one to the number. The digits are stored such that the most significant digit is at the head of the list. (PlusOneLinkedList.h)
[Reverse and plus 1 and reverse: keep track of a curNode and carry. Also need to keep track of a prevNode to add carry to a new node of prevNode->next in case of it requires one more node.]
[Recur: carry=recur(head), if carry, carryNode=new Node(carry), carryNode->next=head, return carryNode. Return head. recur: if head==NULL, return 1, carry=recur(head->next), sum=carry+head->val, head->val=sum%10, carry=sum/10, return carry.]
}
Palindrome{
+ Given a number array composed of [0:9] that represents an integer. Find the next smallest palindrome number that is larger than the given number. (NextPrePalindromeNum.h)
[If all digits in v are 9s, add 1 more digit to v, make head and tail 1s, others 0s, return. Else, keep a left and right ptrs from middle, expand for equal digits, now determine lessEqual if v[left]<v[right], then replace right remaining digits with left remaining digits to make both sides symmetric. If lessEqual, increment the left half digits and move on the carry and update the right side digits as well.]
+ Determine whether an integer is a palindrome. Do this without extra space. (PalindromeNumber.h)
[Compute d=pow(10,digitCount-1). while x>0, if x/d!=x%10, return false, x%=d (remove msb), x/=10 (remove lsb), d/=100. Return true.]
}
Prime{
+ Count the number of prime numbers less than a non-negative number, n. (AllNonGreaterPrimes.h)
[Sieve: for each isPrime[i], if i is a prime, mark all i's multiples as non-prime starting from i^2.]
+ Find all prime factors of a given number. (AllPrimeFactors.h)
[Remove all factors of 2. Then remove all factors of (3+2*i) until (3+2*i)^2<=n.]
+ Determine if a given number is prime. (IsPrime.h)
[Naive: check if n%2==0 then check if n%(3+2*i)==0. Advanced: check if n%2==0, n%3==0, n%(6*i+1)==0, n%(6*i-1)==0.]
+ Return the next big prime number that is equal to or greater than n. (NextPrime.h)
[Check n%(3+2*i)==0. Check n%(6*i+1)==0 and n%(6*i-1)==0.]
}
SpecialNumSeq{
BFSEnumerate{
+ Compute the k smallest real numbers of the form a + b*Sqrt(2) for nonnegative integers a and b. (FirstKAPlusBSqrt2.h)
[1. BFSMinHeap. 2. Keep track of index of max a and max b.]
+ Ugly numbers are numbers whose prime factors are 2, 3, or 5. The sequence 1,2,3,4,5,6,8,9,10,12,15,... shows the first 11 ugly numbers. Find the n-th number. (NthUglyNum.h)
[Keep track of min of (nxtMul2Val, nxtMul3Val, nxtMul5Val) and nxtMul2, nxtMul3, nxtMul5 indices. Update and advance when their nxt val is taken.]
+ A straight-line program for computing X^n is a finite sequence <X, X^i1, X^i2, ..., X^n> where each element after the first is either "the square of some previous element" or "the product of any two previous elements". Given a positive integer n, compute a shortest straight-line program to evaluate X^n. (ShortestStraightLineProgramXPowN.h)
[BFSQueue.]
}
+ BinomialCoefficient: the coefficient of the X^k term in the polynomial expansion of the binomial power (1+X)^n, which is equal to n!/(k!*(n-k)!).(BinomialCoefficient.h)
[Recur: C(n, 0) = C(n, n) = 1, C(n, k) = C(n-1, k-1) + C(n-1, k). DP: dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j].]
+ CatalanNumber: C0 = 1. Cn+1 = Sigma Ci*Cn-i. (CatalanNumber.h)
[Recur. DP.]
+ You are climbing a stair case. It takes n steps to reach to the top. Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top? (ClimbingStairs.h)
[n-th Fibonacci number.]
+ The count-and-say sequence is the sequence of integers beginning as follows: 1, 11, 21, 1211, 111221, .... Which is "1", "One 1s", "Two 1s", "One 2s One 1s", "One 1s, One 2s, Two Ones", .... (CountAndSay.h)
[]
+ Fibonacci Numbers: f(0) = 0, f(1) = 1, f(n) = f(n-1) + f(n-2). Generate the n-th Fibonacci number. Validate if a given number is a Fibonacci number. (FibonacciNumber.h)
[Generate N-th: recur: if (n<=1), return n. return recur(n-1)+recur(n-2). DP: for i = 3 to n, curNum = prevNum1 + prevNum2, prevNum2=prevNum1, prevNum1=curNum, return prevNum1.]
[Validate: A number n is Fibonacci if and only if one or both of (5*n^2+4) or (5*n^2-4) is a perfect square.]
+ You are playing the following Nim Game with your friend: There is a heap of stones on the table, each time one of you take turns to remove 1 to 3 stones. The one who removes the last stone will be the winner. You will take the first turn to remove the stones. Determine whether you can win the game given the number of stones in the heap. (NumGame.h)
[n in [1,3]: starting player must win. n==4: after starting player take 1 to 3, n will be in [1,3] (hence his opponent must win), so starting player must loose. n in [5,7]: starting player can take 1 to 3 to make n==4 (hence his opponent must loose), so starting player must win. n==8: after starting player take 1 to 3, n will be in [5,7] (hence his opponent must win), so starting player must loose.]
+ Generate N positive integer in string comparison order. (StrCompOrderNumSeq.h)
[After observation, it is a preorder DFS traversal order.]
}
+ Given a non-negative integer num, repeatedly add all its digits until the result has only one digit. Return that digit. (AddDigits.h)
[Observation: (n - 1) % 9 + 1.]
+ Given current time of "hour:min", calculate the angle between hour hand (short) and minute hand (long). (ClockAngle.h)
[Short: (360.0/12.0)*hour + (360.0/12.0/60.0)*min. Long: (360.0/60.0)*min.]
+ Given a number "n", find the smallest number "p" such that if we multiply all digits of "p", we get "n". The result "p" should have minimum two digits. (MinNumWSameDigitsProduct.h)
[Find all factors in [9,2] of n. If n can be broken into factors in [9,2], then the min solution should be a number with all the factors in [9,2] in reversed order. Otherwise, there is no solution.]
+ Given a file containing roughly one billion IP addresses, each of which is a 32-bit unsigned integer. Find an IP address that is not in the file? RAM limit is 2 MB (where 1MB = 2^20 bytes). (MissingIPaddress.h)
[Build a hash table of size 2^16 * 4-bytes = 2^20 bytes, where each slot representes the count of corresponding upper 16-bit of an IP integer. Find an IP in the hash table that has less than 2^16 count. Build another hash table of size 2^16 * 4-bytes = 2^20 bytes for IPs that has corresponding upper 16-bit.]
+ Given an integer n, find its next big and prev small integer that has same count of 1s and 0s. (NextPrevNumWSameDigits.h)
[Next big: find ascendingEnd from right, reverse n[ascendingEnd]~n[end], find upper bound<less> of n[ascendingEnd-1] in n[ascendingEnd]~n[end] and swap. Prev small: find descendingEnd from right, reverse n[descendingEnd]~n[end], find upper bound<greater> of n[descendingEnd-1] in n[descendingEnd]~n[end] and swap.]
+ Reverse digits of an integer. (ReverseInteger.h)
[Remove digit from right: res = res*10 + n%10; n/=10. Special condition to check before res*10: abs(res) > 214748364. INT_MAX=2147483647. INT_MIN=-2147483648.]
+ A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down). Write a function to determine if a number is strobogrammatic. The number is represented as a string. Find all strobogrammatic numbers that are of length = n. Write a function to count the total strobogrammatic numbers that exist in the range of low <= num <= high. (StrobogrammaticNumber.h)
[Build a upsideDownMap to map 0->0, 1->1, 6->9, 8->8, 9->6. Iterate with a pair of left and right ptrs from both ends until they meet, early return false when left or right char cannot be found in upsideDownMap or left char cannot be mapped to right char.]
[DFS recur: keep track of current length. base cases: curLen==0 for even N, return {""}; curLen==1 for odd N, return {"0","1","8"}. Postorder add (front,end) upsideDownMapped chars to the result of recur(curLen-2): ("0","0"), ("1","1"), ("6","9"), ("8","8"), ("9","6") and return.]
[Find all strobogrammatic strs with length from lenOfLow to lenOfHigh using DFS recur. Exclude all strs with same length as lenOfLow and strCompare(low) < 0 or with same length as lenOfHigh and strCompare(high) > 0.]
+ There are 100 doors colsed, with index from 1 to 100. The i-th person opens every i door starting from 1st door (toggle i's multiples). When will the door with index n be toggled? Which doors whose final state are open? (TheOpenDoorsProblem.h)
[1. When i is a factor of n. 2. Doors with indices that are perfect squares.]
+ Validate if a given string is numeric. "0" => true, " 0.1 " => true, "abc" => false, "1 a" => false, "2e10" => true. (ValidNumber.h)
[Rules:
1.
'+'/'-' must be no '+'/'-'/'.'/number before it, unless it follows 'E'/'e'.
'+'/'-' must be followed by '.'/number.
(+7.e-9 or +.7e-9)
2.
'E'/'e' must be no 'E'/'e' before it.
'E'/'e' must have a number before it.
'E'/'e' must be followed by '+'/'-'/number.
(+9e-3 or +9.e-3 or +9.e3)
3.
'.' must be no 'E'/'e'/'.' before it.
'.' must either follow a number or be followed by a number.
(9. or 9.e-3 or .9 or .9e-3 or +.9 or +.9e-3)]
*/
/*=====================================================================*/
/*
CompareString
+ Given two words s1 and s2, find the minimum number of steps required to convert word1 to word2. Each operation is counted as 1 step. (EditDistance.h)
[Recur: keep track of startIdx1, startIdx2. If startIdx1==N, return M-startIdx2, else if startIdx2==M, return N-startIdx1, else if s1[startIdx1]==s2[startIdx2], return recur(startIdx1+1,startIdx2+1), else, replace=recur(startIdx1+1,startIdx2+1), insert=recur(startIdx1,startIdx2+1), delete=recur(startIdx1+1,startIdx2), return min(replace,insert,delete).]
[DP2D: for startIdx1 in [0:N], for startIdx2 in [0:M], if startIdx1==0, dp[startIdx1][startIdx2]=startIdx2, else if startIdx2==0, dp[startIdx1][startIdx2]=startIdx1, else, replace=dp[startIdx1-1][startIdx2-1]+s1[startIdx1-1]==s2[startIdx2-1], insert=dp[startIdx1-1][startIdx2]+1, delete=dp[startIdx1][startIdx2-1]+1, dp[startIdx1][startIdx2]=min(replace,insert,delete). Return dp[N][M].]
+ You are required to write a method which takes an anonymous letter L and text from a magazine M. Your method is to return true if and only if L can be written using M, i.e., if a letter appears k times in L, it must appear at least k times in M. (AnonymousLetter.h)
[Build a HashMap<charInL,count> to keep track of char count in L. For each char in M, decrement the count in hashmap and erase if count is 0. Return if hashmap is empty.]
+ Compare two version numbers version1 and version2. If version1 > version2 return 1, if version1 < version2 return -1, otherwise return 0. You may assume that the version strings are non-empty and contain only digits and the '.' character. The '.' character does not represent a decimal point and is used to separate number sequences. Example: 0.1 < 1.1 < 1.2 < 13.37. (CompareVersionNumbers.h)
[Split the 2 num strings into 2 num arrays. len=min(N1,N2). For i in [0:len-1], if v1[i]<v2[i], return -1, else if v1[i]>v2[i], return 1. If N1>N2 {while len<N1 {if v1[len++]!=0, return 1}, return 0}, else if N2<N1 {while len<N2 {if v2[len++]!=0, return -1}, return 0}, else, return 0.]
+ Given two strings s and t, determine if they are isomorphic. Two strings are isomorphic if the characters in s can be replaced to get t. All occurrences of a character must be replaced with another character while preserving the order of characters. No two characters may map to the same character but a character may map to itself. (IsomophicStrings.h) <-> WordPattern.h
[If sizes aren't equal, return false. Keep a sTotMap<char,char> and a tTosMap<char,char>. For i in [0:N-1], if both s[i] and t[i] are not found in sTotMap and tTosMap {insert {s[i],t[i]} and {t[i],s[i]} to sTotMap and tTosMap}, else if one found one not found, return false, else (both found), if sTotMap[s[i]]!=t[i]||tTosMap[t[i]]!=s[i], return false. Return true.]
+ Same as EditDistance.h (LevenshteinDistance.h)
[]
+ Same as EditDistance.h (LevenshteinDistance2.h)
[]
+ The computer has four slots containing balls that are red(R), yellow(Y), green(G) or blud(B). When you guess the correct color for the correct slot, you get a "hit". If you guess a color that exits but is in the wrong slot, you get a "pseudo-hit". For example, the solution is RGGB, but you guess YRGB so you got 2 hits and 1 pseudo hit. Given a solution and a guess, determine the number of hits and pseudo hits. (MasterMindGame.h)
[First scan: count hits and save extra count of RGBY in solution that is non-hit in a HashMap<char,count>. Second scan: for each guess[i], if non-hit and has extra count in solution: increment pseudo-hit and cancel one count.]
+ Given a string array "words", find the maximum value of length(words[i]) * length(words[j]) where the two words do not share common letters. You may assume that each word will contain "only lower case letters". (MaxProductOfWordLength.h)
[Since each word contains only lower case letters, which means we can use 26 bits to represent the appearance of chars in each word by an 32-bit integer. Build charMap[i]: use an integer's all set bits to represent all chars in words[i]. Two words do not share common letters: can be checked using bitwise AND to check if there is common set bits between 2 integers, so enumerate all possible pairs.]
+ Given a dictionary of words. Find the longest and shortest word that can be typed by a single hand on a qwerty-style keyboard. (MinMaxRightLeftHandWord.h)
[Keep an array leftHand<int>[i]==1: char 'a'+i is leftHanded, 0: char'a'+i is rightHanded. (leftHand: qwertasdfgzxcvb. rightHand: yuiophjklnm). For each word in dic, for each char in word, test if each char is leftHanded or rightHanded, keep track of min and max length of found leftHanded and rightHanded words.]
+ Given two strings S and T, determine if they are both one edit distance apart. (OneEditDistance.h)
[2 cases: N1==N2 (must have 1 diff), or N1+1==N2 (must have 0 diff excluding the extra 1 letter in the longer string). If abs(N1-N2)>1, return false. found1stDiff=false, for i in [0:N1-1], if S[i]!=T[j] {if found1stDiff {return false (now found 2nd diff)}, found1stDiff=true, if N1!=N2, --i}, ++i, ++j. Return found1stDiff||N1!=N2.]
+ An abbreviation of a word follows the form <first letter><number><last letter>. Assume you have a dictionary and given a word, find whether its abbreviation is unique in the dictionary. A word's abbreviation is unique if no other word from the dictionary has the same abbreviation. (UniqueWordAbbreviation.h)
[Keep an HashMap<Abbr,HashSet<Word>> and insert all <abbr,word> pairs from input dict. To test if a word has unique abbr, first compute its abbr, then lookup the HashMap.]
*/
/*=====================================================================*/
/*
Design
+ (ChessHashFunc.h)
[]
+ Consider a server that a large number of clients connect to. Each client is identified by unique string. Each client has a certain number of "credits", which is a nonnegative integer value. The server needs to maintain a data structure to which clients can be added, removed, queried, or updated. In addition, the server needs to be able to add C credits to all clients simultaneously. (ClientsCreditsInfo.h)
-insert(s, c), which add client s with credit c, overwriting any existing entry for s: O(logn) time. -remove(s), which removes client s: O(logn) time. -lookup(s), which returns the number of credits associated with client s, or -1 if s is not present: O(1) time. -addAll(C), the effect of which is to increment the number of credits for each client currently present by C: O(1) time. -max(), which returns any one client with the highest number of credits: O(1) time.
[]
+ Design a hit counter which counts the number of hits received in the past 5 minutes. (DesignHitCounter.h)
[Keep a queue<timestamp,hitCount> and a total hit count that covers all hitCount in queue. When a new hit comes, increment total hit count, increment the back pair in queue if it has same timestamp, otherwise, pop front if queue size is 300 and subtract total hit count from front, push back the new timestamp with hitCount 1. When getting hit count, pop front as long as front timestamp is out of range and subtract total hit count, then return total hit count.]
+ Design a Phone Directory which supports the following operations: get: Provide a number which is not assigned to anyone. check: Check if a number is available or not. release: Recycle or release a number. (DesignPhoneDirectory.h)
[Keep a inUse<bool> array to keep track of which number is currently being used. Keep a recycle<number>[rIdx] array to keep track of a list of recycled numbers. Keep a next number that points to the next available number that has never been used. get: return a number at recycle[rIdx--] if available, otherwise return next++ if available, mark inUse[number]. recycle: if inUse[number] is marked, unmark it and assign to recycle[rIdx++]. check: return if inUse[number] is marked.]
+ Design a simplified version of Twitter where users can post tweets, follow/unfollow another user and is able to see the 10 most recent tweets in the user's news feed. (DesignTwitter.h)
[Keep a globalTweetIdx (greater means a more recent tweet), keep a hashMap<userIdx,hashSet<followingUserIdx>> to track each user's followees and a hashMap<userIdx, vector<pair<globalTweetIdx,tweetIdx>>> to track each user's tweets with globalTweetIdx in increasing order. getNewsFeed: use a minHeap<globalTweetIdx,tweetIdx> to keep 10 tweets with max globalTweetIdxs, and scan from that user's all followees' tweets.]
+ Design a data structure that supports all following operations in average O(1) time. insert(val): Inserts an item val to the collection. remove(val): Removes an item val from the collection if present. getRandom: Returns a random element from current collection of elements. The probability of each element being returned is linearly related to the number of same value the collection contains. What if duplicates are allowed? (InsertDeleteGetRandom.h)
[Keep an array of all entrie. GetRandom just returns entries[rand()%entries.size()]. Keep a HashMap<entry,idx> to keep track of the index of each entry in entries array. Insert: push new entry to back in entries array, insert {entry,entries.size()} to HashMap. Remove: pop out the last element in entries, if last element is not equal to the target, find the idx of where target locates in entries array and move last to that idx.]
[Keep an array of all entries including duplicates. GetRandom just returns entries[rand()%entries.size()]. Keep a HashMap<entry,HashSet<idx>> to keep track of a list of indices of each entry in entries array. Insert: push new entry to back in entries array, insert {entry,entries.size()} to HashMap. Remove: pop out the last element in entries, if last element is not equal to the target, find an arbitrary idx of where target locates in entries array and move last to that idx.]
+ Design a logger system that receive stream of messages along with its timestamps, each message should be printed if and only if it is not printed in the last 10 seconds. Given a message and a timestamp (in seconds granularity), return true if the message should be printed in the given timestamp, otherwise returns false. It is possible that several messages arrive roughly at the same time.(LoggerRateLimiter.h)
[Use a hashMap<msg,timeIdx> to keep track of the timestamp of each message. When receving a new msg, if not present in hashMap, insert it and return true, else if present and its timestamp diff is greater equal than 10, update the timestamp and return true, else, don't update the timestamp and return false.]
+ (LRUCache.h)
[]
*/
/*=====================================================================*/
/*
FindSubstrSubseq
PrefixSum{
Kadane{
+ Given an integer array. Find the first K largest sub-array sums. When K == 1, this problem reduces to the normal MaxSubArraySum.h. (KMaxSubArraySum.h)
[KMinPrefixSum: keep a sortedKMinPrefixSum[] in ascending order. for i in [1:N-1] {prefixSum[i]=prefixSum[i-1]+v[i], for j in [0:K-1] {curSortedKSubArrSum[j]=prefixSum[i]-sortedKMinPrefixSum[j]}, merge curSortedKSubArrSum[] with resSortedKSubArrSum[] to get first K max SubArrSums and save to resSortedKSubArrSum[], insert prefixSum[i] to sortedKMinPrefixSum[], return resSortedKSubArrSum[].]
+ Given an array of integers. Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of two sub-arrays is maximum. The sub-arrays should not overlap. (MaxDiff2SubArraySum.h)
[MinMaxPrefixSum: compute a leftInclusivePrefixSum<max,min>[i]=<maxPrefixSum in [0:i],minPrefixSum in [0:i]> from left to right and a rightExclusivePrefixSum<max,min>[i]=<maxPrefixSum in [i+1:N-1],minPrefixSum in [i+1:N-1]> from right to left. For i in [0:N-1], if i==N-1, diffLR=abs(leftInclusivePrefixSum[i].first-0), diffRL=abs(0-rightExclusivePrefixSum[i].second), else, diffLR=abs(leftInclusivePrefixSum[i].first-rightExclusivePrefixSum[i].second), diffRL=abs(rightExclusivePrefixSum[i].first-leftInclusivePrefixSum[i].second), maxDiff=max(maxDiff,diffLR,diffRL), return maxDiff.]
+ Given an array of integer pairs. Find a sub-array such that the 1st element in the pairs are in increasing order and the sum of 2nd element of the pairs are maximum. (MaxIncrSubArraySum.h)
[2Pass: For i in [0:N-1], if i!=0&&v[i].first<v[i-1].first {sum=0, positiveBegin=i}, (the rest are same as MaxSubArraySum.h) sum+=v[i].second, if sum<0 {sum=0, positiveBegin=i+1, continue}, if sum>maxSum {maxSum=sum,begin=positiveBegin,end=i}. If end==-1 (all elements are negative), iterate to find the max negative element.]
+ Given an array that contains both positive and negative integers. Find the maximum product of contiguous subarray. (MaxSubArrayProduct.h)
[DP: maxProduct=v[0], curMaxProduct=v[0], curMinProduct=v[0], for i in [1:N-1], prevMaxProduct=curMaxProduct, prevMinProduct=curMinProduct, curMaxProduct=max(prevMaxProduct*v[i],prevMinProduct*v[i],v[i]), curMinProduct=min(prevMaxProduct*v[i],prevMinProduct*v[i],v[i]), maxProduct=max(maxProduct,curMaxProduct). Return maxProduct.]
[DP 2Pass: maxProduct=v[0], curSubarrProduct=1, for i in [1:N-1], maxProduct=max(maxProduct,curSubarrProduct*v[i]), curSubarrProduct=(v[i]==0?1:curSubarrProduct*v[i]). curSubarrProduct=1. For i in [N-1:0], maxProduct=max(maxProduct,curSubarrProduct*v[i]), curSubarrProduct=(v[i]==0?1:curSubarrProduct*v[i]). Return maxProduct.]
+ Find the contiguous subarray within an array (containing at least one number) which has the largest sum. (MaxSubArraySum.h)
[DP: for i in [0:N-1], curSubArrSum=max(curSubArrSum+v[i],v[i]), maxSubArrSum=max(maxSubArrSum,curSubArrSum), return maxSubArrSum.]
[2Pass: For i in [0:N-1], sum+=v[i], if sum<0 {sum=0, positiveBegin=i+1, continue}, if sum>maxSum {maxSum=sum,begin=positiveBegin,end=i}. If end==-1 (all elements are negative), iterate to find the max negative element.]
+ Given a circular array A, compute its maximum subarray sum in O(n) time, where n is the length of A. Can you devise an algorithm that takes O(n) time and O(1) space? (MaxSubArraySumCircular.h)
[maxNonCircular=maxSubArrSum(A), maxCircular=totalSum-minSubArrSum(A), return max(maxNonCircular,maxCircular).]
[DP1D maxCircular: compute a maxPrefixSumL[] and maxPrefixSumR[]. For i in [0:N-1], if i==0, maxCircular=max(maxCircular,maxPrefixSumR[0]), else if i==N-1, maxCircular=max(maxCircular,maxPrefixSumL[N-1], else, maxCircular=max(maxCircular,maxPrefixSumL[i-1]+maxPrefixSumR[i],maxPrefixSumL[i]+maxPrefixSumR[i+1]), return maxCircular.]
}
LongestShortest{
+ Given 2 binary arrays A and B i.e. containing only 0s and 1s each of size N. Find indices i, j such that sum of elements from i to j in both arrays is equal and j-i (i.e. the length of the set i,j) is the maximum possible value. (LongestEqualSumSubArrFrom2Arr.h)
[PrefixSum: coompute prefixSumA[] and prefixSumB[]. For right in [0:N-1], for left in [0:right], if (left==0&&prefixSumA[right]==prefixSumB[right])||(left!=0&&prefixSumA[right]-prefixSumB[left-1]==prefixsumB[right]-prefixSumB[left-1]), maxLen=max(maxLen,right-left+1), return maxLen.]
+ Given an array nums and a target value k, find the maximum length of a subarray that sums to k. If there isn't one, return 0 instead. (LongestSubArrWEqualSum.h)
[Keep a prefixSumMap<prefixSum,1stIdx>. For i in v[0:N-1], prefixSum+=v[i], if prefixSum==k {maxLen=max(maxLen,i+1)}, else if prefixSumMap.find(prefixSum-k)!=prefixSumMap.end() {maxLen=max(maxLen,i-prefixSumMap[prefixSum-k])}, if prefixSumMap.find(prefixSum)==prefixSumMap.end(), prefixSumMap.insert({prefixSum,i}). Return maxLen.]
+ Design an algorithm that takes as input an array A of n numbers and a key k, and returns a longest subarray of A for which the subarray sum is less than or equal to k. (LongestSubArrWLessEqualSum.h)
[Compute a prefixSum[]. Compute a minPrefixSum[] of prefixSum[] from right to left, where minPrefixSum[i]=min in prefixSum[i:N-1]. Greedy: while left<N&&right<N {curSubArrMinSum=minPrefixSum[right]-prefixSum[left-1], if curSubArrMinSum<=givenSum, maxLen=max(maxLen,right-left+1), ++right, else, ++left}. Return maxLen.]
+ Given an array of n positive integers and a positive integer s, find the minimal length of a subarray of which the sum >= s. If there isn't one, return 0 instead. (ShortestSubArrWGreaterSum.h)
[For right in [0:N-1], if v[right]>=val {return 1}, sum+=v[right], if v[right]<0 {++negCount}, if sum<=0 {sum=0,left=right+1,negCount=0,continue}, if sum>=val {if negCount>0 {accumulate newSum from right to left until greater equal than val to find tgtLeft, subtract negCount from left to tgtLeft, left=tgtLeft, sum=newSum}, else {shrink left by subtracting sum until smaller than val}, minLen=min(minLen,right-left+1)}. Return minLen.]
+ Given an unsorted array of nonnegative integers, find all continuous subarrays which add to a given number. (SubArrayWGivenSum.h)
[For right in [0:N-1], sum+=v[right], advance left to keep a longest window where sum <= val, find all subarrays between left and right and ended at right, record in res<left,right>[]. Return res<left,right>[].]
}
+ Given an integer array, find a subarray whose sum is closest to 0. (ClosestSubArraySum.h)
[BruteForce: enumerate all (left,right) pairs, compute sum in [left,right], keep track of the sum that is closest to 0.]
[PrefixSum: compute a prefixSum[]: prefixSum[i]=sum in v[0:i], prefixSum[end]-prefixSum[start-1]=sum in v[start:end]. Sort the prefixSum array, for i in [0:N-1], absMinSum=min(absMinSum,abs(prefixSum[i]),abs(prefixSum[i+1]-prefixSum[i])), return absMinSum.]
- Find a subarray whose sum is closest to k.
[PrefixSum: compute a prefixSum[]: prefixSum[i]=sum in v[0:i], prefixSum[end]-prefixSum[start-1]=sum in v[start:end]. For left in [0:N-1], for right in [left:N-1], if left==right, absMinSum=min(absMinSum,abs(prefixSum[left]-k)), else, absMinSum=(absMinSum,abs(prefixSum[right]-prefixSum[left]-k)), return absMinSum.]
+ Assume you have an array of length n initialized with all 0's and are given k update operations. Each operation is represented as a triplet: [startIndex, endIndex, inc] which increments each element of subarray A[startIndex ... endIndex] (startIndex and endIndex inclusive) with inc. Return the modified array after all k operations were executed. (RangeAddition.h)
[Init an res array with all 0s. For each range increment, add the increment to res[start] and -increment to res[end+1]. For each num in res, replace it with its prefixSum.]
}
SubArr{
LCP{
+ Write a function to find the longest common prefix string amongst an array of strings s. (LongestCommonPrefix.h)
[allIdentical=true. For charIdx in [0:s[0].size-1], for strIdx in [0:N-1], if charIdx==s[strIdx].size||s[strIdx][charIdx]!=s[0][charIdx] {allIdentical=false, lcp=s[0][0:charIdx-1], break}, if !allIdentical, break. If allIdentical, lcp=s[0]. Return lcp.]
+ Given a list of words and a target word. Find the shortest prefix of the target word that is not of a prefix of any word in the list. (ShortestUniquePrefix.h)
[Compute a set of longest common prefix of each word in the list and the target word. Then find the longest string in the lcp set. Then the longest string along with the next char in the target word will be the answer. If the longest string is equal to the target word, then there will be no answer.]
[Trie: Build a trie of all words in the list. Find the longest prefix of all keys in the trie that is also a prefix of the target word. Then the longest prefix along with the next char in the target word will be the answer. If the longest prefix is equal to the target word, then there will be no answer.]
}
LongestShortest{
+ Write a function that takes an array of integers A and returns the length of a longest subarray of A with the constraint that all its elements are distinct. (LongestSubArrWDistinctEntries.h)
[Use a visitMap<entry,lastIdx> to keep track of last index of distinct visited num. For right in [0:N-1], if v[right] is not in visitMap, insert {v[right],i} to lastIdxMap, else {if visitMap[v[right]]>=left {left=visitMap[v[right]]+1 to exclude v[right]}, visitMap[v[right]]=i}, if right-left+1>maxLen {maxLen=right-left+1, maxLeft=left}. Return {maxLeft,maxLeft+maxLen}.]
- Given a string S, find the length of the longest substring T that contains at most 2 distinct characters.
[Use a visitMap<entry,lastIdx> to keep track of last index of distinct visited char. For right in [0:N-1], if v[right] isn't in visitMap && visitMap's size is 2 {remove the one whose lastIdx is more left, update left to the next right idx of the removed element}, insert {v[right],right} to visitMap, if right-left+1>maxLen {maxLen=right-left+1,maxLeft=left}. Return {maxLeft,maxLeft+maxLen}.]
- Follow-up: find the length of the longest substring T that contains at most K distinct characters.
[Use a foundMap<entry,count> to keep track of count of distinct chars in current window. For right in [0:N-1], if v[right] isn't in foundMap {insert {v[right],right} to foundMap, while foundMap.size()>=K {decrement/remove v[left] from visitMap and advance left}}, else, ++foundMap[v[right]], if right-left+1>maxLen {maxLen=right-left+1,maxLeft=left}. Return {maxLeft,maxLeft+maxLen}.]
+ Given an inetger array that may have duplicated elements. A plateau is a subarray that contains all equal elements. Find the longest plateau length, i.e., the longest subarray that contain all equal elements. (LongestSubArrWEqualElements.h)
[Keep a left and right ptr. While left<N {right=left+1, advance right until v[right]!=v[left], if right-left+1>maxLen {maxLen=right-left+1,maxLeft=left}, left=right}. Return {maxLeft,maxLeft+maxLen}.]
+ Given a string, find the length of the longest substring without repeating characters. (LongestSubStrWoRepeatedChars.h)
[Keep track of a visit<bool>[256] and init visit[]={false}. For right in [0:N-1], if visit[v[right]] {advance left and unmark visit[left] until v[left]==v[right], and then advance once more}, visit[v[right]]=true, if right-left+1>minLen {minLen=right-left+1,minLeft=left}. Return {minLeft,minLeft+minLen}.]
+ Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring. For "(()", the longest valid parentheses substring is "()", which has length = 2. Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4. (LongestValidParentheses.h)
[Stack: use a leftPrenIdxStk to store '(' indices. preInvalidRightPrenIdx=-1. For i in [0:N-1], if v[i]=='(', push i to leftPrenIdxStk, else {if leftPrenIdxStk is empty, preInvalidRightPrenIdx=i, else {pop a '(' from leftPrenIdxStk such that leftPrenIdxStk.top is the prev '(' that hasn't met its ')', maxLen=max(maxLen,i - leftPrenIdxStk.empty()?preInvalidRightPrenIdx:leftPrenIdxStk.top())}}. Return maxLen.]
[2Scans: leftToRight: For i in [0:N-1], ++curMaxLen, if v[i]=='(', ++balance, else, --balance, if balance==0, maxLen=max(maxLen,curMaxLen), else if balance<0 {balance=0,curMaxLen=0}, Return maxLen. rightToLeft: test for ')'. Return max(leftToRight,rightToLeft).]
+ Given a array of words and an array of target words, find the shortest subarray covering all target words. (ShortestSubArrContainEntries.h)
[Save all target words in a wordMap<word,count>. Keep a foundMap<word,count>. For right in [0:N-1], if v[right] isn't in wordMap, continue, else, ++foundMap[v[right]], if foundMap[v[right]]<=wordMap[v[right]], ++foundCount, if foundCount==M {advance left for non-target-words or redundant-target-words (--foundMap[v[right]]), if minLen>right-left+1 {minLen=right-left+1, minLeft=left}.}. Return {minLeft,minLeft+minLen}.]
- What if the input is a stream where we can't keep track of begin ptr? Assume all target words are distinct.
[Save all target words in a wordMap<word,lastIdxQue::itr(end)>. Keep track of a running idx and lastIdxQue<idx>. For each input word, if word is in wordMap {lastIdxQue.erase(wordMap[word]), lastIdxQue.push_back(idx), wordMap[word]=prev(lastIdxQue.end())} if lastIdxQue.size()==M&&idx-lastIdxQue.front()<minLen {record minLen and minLeft}, ++idx. Return {minLeft,minLeft+minLen}.]
+ Given two integer-valued arrays A and Q and computes a minimum length subarray A[i:j] that sequentially covers Q. Assume all elements in Q are distinct. (ShortestSubArrContainAllEntriesInOrder.h)
[Save all target words in a wordMap<word,idx>. Keep a lastIdx[] and curLenTill[], init lastIdx[]=-1, curLenTill[]=MAX. For i in [0:N-1], if v[i] isn't in wordMap, continue, else, curWordIdx=wordMap[v[i]], if curWordIdx==0, curLenTill[0]=1, else if curLenTill[curWordIdx-1]!=MAX {curLenTill[curWordIdx]=(i-lastIdx[curWordIdx-1])+curLenTill[curWordIdx-1]}, lastIdx[curWordIdx]=i, if curWordIdx==M-1&&curLenTill[curWordIdx]<minLen {minLen=curLenTill[M-1],minLeft=i-curLenTill[M-1]-1}. Return {minLeft,minLeft+minLen}.]
+ Given a set T of characters and a string S, find the minimum window in S which will contain all the characters in T in complexity O(n). (ShortestSubstrContainAllChars.h)
[Save all target chars in a charMap<char,count>. Keep a foundMap<char,count>. For right in [0:N-1], if v[right] isn't in charMap, continue, else, ++foundMap[v[right]], if foundMap[v[right]]<=charMap[v[right]], ++foundCount, if foundCount==M {advance left for non-target-chars or redundant-target-chars (--foundMap[v[right]]), if minLen>right-left+1 {minLen=right-left+1, minLeft=left}.}. Return {minLeft,minLeft+minLen}.]
}
Palindrome{
+ Given a string S, find the longest palindromic substring in S. (LongestPalindromeSubstr.h)
[BruteForce: enumerate all possible substrings and check if it is a palindrome and keep track of the longest one.]
[Greedy: for curCenter in [0:N-1], expand(curCenter,curCenter) to find longest odd palindrome, expand(curCenter,curCenter+1) to find longest even palindrome. Keep track of maxLen.]
[Manacher: ]
[DP2D: dp[left][right]==1 means s[left:right] is a palindrome. Keep track of maxLen and maxLeft. For len in [1:N], for left in [0:N-len], right=left+len-1, if len==1, dp[left][right]=1, else if len==2&&s[left]==s[right], dp[left][right]=1, else if s[left]==s[right]&&dp[left+1][right-1], dp[left][right]=1, record maxLen and maxLeft.]
[LCSubstr: Reverse s, then this will become the LCSubstr problem.]
+ Given a list of unique words. Find all pairs of distinct indices (i, j) in the given list, so that the concatenation of the two words, i.e. words[i] + words[j] is a palindrome. (PalindromePairs.h)
[BruteForce: enumerate all possible pairs of words and concatenate each pair and test if it's a palindrome.]
[Use a HashMap<word,index> to lookup each word's index. For each word, we want to check if it can be split as "prefix + palindrome" and lookup the reverse prefix word in the HashMap such that "prefix + palindrome" + reversedPrefix is a palindrome. Also check if it can be split as "palindrome + suffix" and lookup reversed suffix in the HashMap such that reversedPrefix + "palindrome + suffix" is a palindrome.]
+ Given a string S, you are allowed to convert it to a palindrome by adding characters in front of it. Find and return the shortest palindrome you can find by performing this transformation. (ShortestPalindrome.h)
[Greedy: Find the longest prefix palindrome, reverse the suffix then append to front. To find the longest prefix palindrome, for curCenter in [N/2:1], expand(curCenter,curCenter) and expand(curCenter-1,curCenter), once found a palindrome, stop.]
[LPS: concat=s+reverse(s). Compute the LPS (longest common prefix suffix length, which is also longest prefix palindrome length) of concat to get longest prefix palindrome length. Then reverse the suffix and append to front. Compute LPS array where LPS[i]=length of common prefix and suffix of p[0:i]: LPS[0]=0, suffixEnd=1, prefixEnd=0, while suffixEnd<M, if p[suffixEnd]==p[prefixEnd] {LPS[suffixEnd]=++prefixEnd, ++suffixEnd}, else {if prefixEnd!=0, prefixEnd=LPS[prefixEnd], else {LPS[suffixEnd++]=0}}.]
}
RegexMatching{
+ Implement regular expression matching with support for '.', '*', '^' and '$'. '.' matches any single character. '*' matches zero or more occurrences of the preceding regular expression. '^' indicates the match must begin at the start of the string. '$' indicates the match must end at the end of the string. An ESRE r that does not start with ^ or end with $ matches s if there is a substring t of s such that r strictly matches t. (ExtendedSimpleRegexMatching.h)
[Recur: keep a startIdx i for s and startIdx j for p. If p[0]=='^', return recur(1,0), else (test if regex matches any substring), for i in [0:N-1], if recur(i,0), return true. Return false. recur: if j==M, return true, else if j==M-1&&p[j]=='$', return i==N, else if j+1<M&&p[j+1]=='*' {while i<N&&(s[i]==p[j]||p[j]=='.') {if recur(i,j+2) {return true}, ++i}, return recur(i,j+2)}, else {return i<N&&(s[i]==p[j]||p[j]=='.')&&recur(i+1,j+1)}.]
+ Implement regular expression matching with support for '.' and '*'. '.' Matches any single character. '*' Matches zero or more of the preceding element. The matching should cover the entire input string. (RegexMatching.h)
[Recur: keep a startIdx i for input string s, startIdx j for pattern p. If p[j+1] is '*', try match 0 or more s[i] with p[j] and recur down, else, try match s[i] with p[j] and recur down. If j==M, return i==N. If j+1<M&&p[j+1]=='*' {while i<N&&(s[i]==p[j]||p[j]=='.') {if recur(i,j+2) {return true}, ++i}, return recur(i,j+2)}, else {return i<N&&(s[i]==p[j]||p[j]=='.')&&recur(i+1,j+1)}.]
[DP2D: 3 cases for p[j-1]: non-'.'-or-'*', '.', '*'. dp[0][0]=1. For i in [0:N], for j in [1:M], if p[j-1]!='.'&&p[j-1]!='*' {if i>0&&s[i-1]==p[j-1]&&dp[i-1][j-1], dp[i][j]=1}, else if p[j-1]=='.' {if i>0&&dp[i-1][j-1], dp[i][j]=1}, else if j>1 {if dp[i][j-1]||dp[i][j-2], dp[i][j]=1, else if i>0&&(s[i-1]==p[j-2]||p[j-2]=='.')&&dp[i-1][j], dp[i][j]=1}. Return dp[N][M].]
+ Implement wildcard pattern matching with support for '?' and '*'. '?' Matches any single character. '*' Matches any sequence of characters (including the empty sequence). The matching should cover the entire input string. (WildcardMatching.h)
[Recur: keep a startIdx i for input string s, startIdx j for pattern p. If p[j] is '*', try match 0 or more s[i] with ANY CHAR and recur down, else, try match s[i] with p[j] and recur down. If j==M, return i==N. If p[j]=='*' {while i<N {if recur(i,j+1) {return true}, ++i}, return recur(i,j+1)}, else {return i<N&&(s[i]==p[j]||p[j]=='?')&&recur(i+1,j+1)}.]
[DP2D: 3 cases for p[j-1]: non-'?'-or-'*', '?', '*'. dp[0][0]=1. For i in [0:N], for j in [1:M], if p[j-1]!='?'&&p[j-1]!='*' {if i>0&&s[i-1]==p[j-1]&&dp[i-1][j-1], dp[i][j]=1}, else if p[j-1]=='?' {if i>0&&dp[i-1][j-1], dp[i][j]=1]}, else, {if dp[i][j-1]||(i>0&&dp[i-1][j]), dp[i][j]=1}. Return dp[N][M].]
}
SortedQueue{
+ Given an array nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position. Return an array of max values in each sliding window. (SlidingWindowMax.h)
[Keep a sortedQue<val,idx> where val is in descending order. For i in [0:N-1], while sortedQue.back().first<v[i] {sortedQue.popBack()}, push {v[i],i} to back in sortedQue, if i>=k-1 {while i-sortedQue.front().second+1>k, {sortedQue.popFront()}, add sortedQue.front().first to res[]}. Return res.]
+ Given an unsorted integer array. Find all subarrays that the difference between the maximum value and the minimum value in the subarray is <= K. (SubArrWLessEqualMinMaxDiff.h)
[Keep a sortedQueMax<val,idx> where val is in descending order, sortedQueMin<val,idx> where val is in ascending order. For left in [0:N-1], advance right until sortedMaxQue.front.first-sortedMinQue.front.first>K {pop back sortedQueMax whose val<=v[right] then push back {v[right],right}, pop back sortedQueMin whose val>=v[right] then push back {v[right],right}}, for i in [left,right), record {left,i} in res, drop sortedQueMax.front and sortedQueMin.front if whose index==left before advancing right. Return res.]
}
StrStr{
+ Given two strings, a haystack and a needle. Returns the index of the first occurrence of needle in haystack, or -1 if needle is not part of haystack. (ImplementStrStr2.h)
[BruteForce: For i in [0:N-M], for j in [0:M-1] {if s[i+j]!=p[j], break} if j==M {res=i, break}. Return res.]
[BoyerMoore: Save all chars in p to a lastIdxMap<char,idx>. For each s[i:i+M-1], compare s with p from end of p: For i in [0:N-M], skip=0, for j in [M-1:0] {if s[i+j]!=p[j] {skip=max(1,j-lastIdxMap[s[i+j]]), break}}, if skip==0, {res=i, break}, i+=skip. Return res.]
[RabinKarp: msbHashTerm=pow(256,M-1)%PRIME. sHash=(s[0]*pow(256,M-1)+...+s[M-1]*pow(256,0))%PRIME, pHash=(p[0]*pow(256,M-1)+...+p[M-1]*pow(256,0))%PRIME. For each s[i:i+M-1], compare sHash and pHash, if same, then compare chars one by one, if same, return, else, sHash = ((sHash-s[i]*pow(256,M-1)%PRIME)*pow(256,1)+s[i+M]*pow(256,0))%PRIME = ((sHash-s[i]*msbHashTerm)*pow(256,1)+s[i+M]*pow(256,0))%PRIME.]
[KMP: while i<N, if s[i]==p[j] {++i, ++j, if j==M {res=i-M, break}}, else {if j!=0, j=LPS[j-1], else, ++i}. Return res. Compute LPS array where LPS[i]=length of common prefix and suffix of p[0:i]: LPS[0]=0, suffixEnd=1, prefixEnd=0, while suffixEnd<M, if p[suffixEnd]==p[prefixEnd] {LPS[suffixEnd]=++prefixEnd, ++suffixEnd}, else {if prefixEnd!=0, prefixEnd=LPS[prefixEnd], else {LPS[suffixEnd++]=0}}.]
+ Given a text, txt, with length N, a pattern, pat, with length M, and a mismatching threshold k. Find all substrings of txt with length M matching pat with k maximal number of mismatches. (Kmismatch.h)
[BruteForce: For i in [0:N-1], miss=0, j=0, while miss<=k&&j<M {lce=LCE(txt[i:i+M-1],pat[0:M-1],j), kmiss+=lce, j+=lce.size+1, if j<=M {++miss, if miss<=k, kmiss+=txt[i+j-1]}}, if kmiss.size==M, record kmiss in res. Return res.]
+ Same as ImplementStrStr2.h (PatternSearching.h)
[SuffixArray: Build a suffix array of s and sort it. Binary search the lower bound of p in suffixes[]. Return suffixes[lb][0:M-1].]
}
SuffixArray{
+ Given a string s, find the longest substring that has at least one repeat. (LongestRepeatedSubstr.h) <-> ShortestUniqueSubstr.h
[This problem can be solved in linear time and space by building a suffix tree for the string, and finding the "deepest internal node" in the tree. Depth is measured by the number of characters traversed from the root. The string spelled by the edges from the root to such a node is a longest repeated substring.]
[SuffixArray: Build a suffix array of s and sort it. For each adjacent suffix pairs in the sorted suffix array, compute the LCP and keep track of the longest LCP. Return the longest LCP.]
- Find the longest substring that has at least k repeat.
[SuffixArray: Build a suffix array of s and sort it. For each k-adjacent suffix groups in the sorted suffix array, compute the CLP and keep track of the longest LCP. Return the longest LCP.]
[BruteForce: For len in [N:1], enumerate all substr with len and put in a hashMap<str,count>, check if there exists a str in hashMap that has count>=k, once found, return that str.]
+ Given a string s, find its minimum lexicographical cyclic left-shift rotation. (MinLexicographicStrRotation.h)
[SuffixArray: concat=s+s. Build a suffix array of concat and sort it. Return the first suffix from begin whose length >= s.size.]
[Iterate: concat=s+s. minBegin=-1. equalCount=0: keep track of the current equal elements in concat[minBegin:minBegin+equalCount) and concat[i-equalCount:i). For i in [0:N-1], if minBegin==-1, minBegin=i, else if concat[i]<concat[minBegin] {minBegin=i,equalCount=0}, else if concat[i]<concat[minBegin+equalCount] {minBegin=i-equalCount, equalCount=0, if concat[i]==concat[minBegin], equalCount=1}, else if concat[i]==concat[minBegin+equalCount] {++equalCount}, else, {equalCount=0}. Return concat.substr(minBegin,s.size).]
+ Given a string s, find the number of all distinct substrings in s. Equivalent to compute the number of nodes (without root) of a string's corresponding suffix trie. (NumOfDistinctSubstr.h)
[SuffixArray: Build a suffix array of s and sort it. For i in [0:N-1], if i==0, res+=suffixes[i].size, else, res+=(suffixes[i].size-LCP(suffixes[i],suffixes[i-1])) which is the extra node count of suffixes[i]. Return res.]
[BruteForce: Use hashSet<substr>. Enumerate all substrs in s and insert to hashSet. Return hashSet.size.]
+ Given a string s, find the shortest unique substring in s. (ShortestUniqueSubstr.h) <-> LongestRepeatedSubstr.h
[SuffixArray: Build a suffix array of s and sort it. For i in [0:N-1], prevLCP=LCP(suffixes[i-1],suffixes[i]), nextLCP=LCP(suffixes[i],suffixes[i+1]), 3LCP=max(prevLCP,nextLCP), if 3LCP+1<=suffixes[i].size {minLen=min(minLen,3LCP+1), minStr=MinLen(minStr,suffixes[i][0:3LCP+1)}. Return minStr.]
[BruteForce: For len in [1:N], enumerate all substr with len and put in a hashMap<str,count>, check if there exists a str in hashMap that has count==1, once found, return that str.]
}
+ Given a string s, enumerate all possible substrings in s. (AllSubstr.h)
[Iterate: for right in []0:N-1], for left in [0:right], add s.substr(left,right-left+1) to res. Return res.]
[Recur: keep track of left and right. If right==N, return, else, if left>right {recur(0,right+1),return.} add s.substr(left,right-left+1) to res, recur(left+1,right).]
+ Given two strings A and B, compute the length of the longest subarray of characters that is a subarray of A and of B. (LCSubstr.h)
[SuffixArray: concat=A#B. N1=A.size, N2=B.size. Build a suffix array of concat and sort it. For i in [0:N-1], if suffixes[i].size<=N2+1&&suffixes[i+1].size<=N2+1 (adjacent suffixes are both from B), continue, else if suffixes[i].size>N2&&suffixes[i+1].size>N2 (adjacent suffixes are both from A), continue, else, maxLen=max(maxLen,LCP(suffixes[i],suffixes[i+1])). Return maxLen.]
[DP2D: for startIdx1 in [0:N1], for startIdx2 in [0:N2], if startIdx1==0||startIdx2==0, dp[startIdx1][startIdx2]=0, else if A[startIdx1]==B[startIdx2], dp[startIdx1][startIdx2]=dp[startIdx1-1][startIdx2-1]+1, else, dp[startIdx1][startIdx2]=0. Return dp[N1][N2].]
+ Given an integer array, find the longest contiguous increasing subarray. (LISubstr.h)
[Keep a left and right ptr. while left<N, {right=left+1, advance right for increasing neighbors, if right-left+1>maxLen {maxLen=right-left+1,maxLeft=left}, left=right+1}. Return {maxLeft,maxLeft+maxLen}.]
+ Given an integer array, find the longest bitonic subarray. A subarray A[i...j] is bitonic if there is a k with i <= k <= j such that A[i] <= A[i + 1] ... <= A[k] >= A[k + 1] >= .. A[j - 1] >= A[j]. (LongestBitonicSubArray.h)
[incr=v[0]>=v[1]?true:false. For i in [0:N-2], if v[i]==v[i+1], ++count, else if v[i]<v[i+1] {if incr, ++count, else (swtich from decr to incr: reset), incr=!incr,count=2,left=i}, else {if !incr, ++count, else (switch from incr to decr: continue), incr=!incr, ++count}, if i-left+1>maxLen {maxLen=i-left+1,maxLeft=left}. Return {maxLeft,maxLeft+maxLen}.]
+ Given an integer array, find the longest subarray that satisfies the predicate. (LongestSubArrPredicate.h)
[For i in [0:N-1], if !f(v[i]), left=i+1, if i-left+1>maxLen {maxLen=i-left+1,maxLeft=left}. Return {maxLeft,maxLeft+maxLen}.]
+ All DNA is composed of a series of nucleotides abbreviated as A, C, G, and T, for example: "ACGAATTCCG". When studying DNA, it is sometimes useful to identify repeated sequences within the DNA. Write a function to find all the 10-letter-long sequences (substrings) that occur more than once in a DNA molecule. (RepeatedDNASubstr.h)
[Keep a strMap<10CharStr,count>. For i in [0:N-10], if v[i:i+10-1] isn't in strMap, insert {v[i:i+10-1],1} to strMap, else, if strMap[v[i:i+10-1]]==1 {add v[i:i+10-1] to res}, ++strMap[v[i:i+10-1]]. Return res. Since 10CharStr is 10 char of ACGT only, we can design a hash function to transform 10CharStr into a 32 bit integer.]
+ You are given a string, S, and a list of words, L, that are all of the same length. Find all starting indices of substring(s) in S that is a concatenation of each word in L exactly once and without any intervening characters. (SubstrWConcatAllWords.h)
[Save all target words in a wordMap<word,count>. wordCount=L's size. len=L[0]'s size. For i in [0:N-len*wordCount], test if s[i:i+len*wordCount-1] can be decomposed into a list of words that matches wordMap<word,count>.]
}
SubSeq{
LISvariant{
Alternating{
+ Define a sequence of numbers[a0, a1, a2, ..., a(n-1)] to be alternating if ai < a(i+1) for even i and ai > a(i+1) for odd i. Given an array of numbers A of length n, find a longest subsequence [i0, i1, i2, ..., i(k-1)] such that [A[i0], A[i1], A[i2], ..., A[i(k-1)]] is alternating. (LongestAlternatingSubseq.h)
[DP1D O(n^2) time: dpIncr[curEnd]=Len of LIS in v[0:curEnd]. dpDecr[curEnd]=Len of LDS in v[0:curEnd]. Init dpIncr[]=1, dpDecr[]=1, for curEnd in [1:N-1], for curStart in [0:curEnd], if v[curEnd]>v[curStart], dpIncr[curEnd]=max(dpIncr[curEnd],dpDecr[curStart]+1), else if v[curEnd]<v[curStart], dpDecr[curEnd]=max(dpDecr[curEnd],dpIncr[curStart]+1), return max(dpIncr[N-1],dpDecr[N-1]).]
[DP1D O(n) time: Init dpIncr[]=1, dpDecr[]=1. For i in [1:N-1], if v[i]>v[i-1], dpIncr[i]=dpDecr[i-1]+1, dpDecr[i]=dpDecr[i-1], else if v[i]<v[i-1], dpDecr[i]=dpDecr[i-1]+1, dpIncr[i]=dpIncr[i-1], else, dpIncr[i]=dpIncr[i-1], dpDecr[i]=dpDecr[i-1]. Return max(dpIncr[N-1],dpDecr[N-1]).]
+ Define a sequence of numbers[a0, a1, a2, ..., a(n-1)] to be weakly alternating if no three consecutive terms in the sequence are increasing or decreasing. Given an array of numbers A of length n, find a longest subsequence [i0, i1, i2, ..., i(k-1)] such that [A[i0], A[i1], A[i2], ..., A[i(k-1)]] is weakly alternating. (LongestWeaklyAlternatingSubseq.h)
[]
}
Pairs{
+ Given a list of pairs of integers, find the length of the longest increasing subsequence of pairs, where adjacent pairs must satisfy the constraint: leftPair.first < rightPair.first, leftPair.second < rightPair.second. (both the first elements and the second elements in the pairs must be in increasing order, respectively) (LISPairs.h)
[DP1D: dp[curEnd]=Len of LIS in v[0:curEnd]. Init dp[]=1. For curEnd in [1:N-1], for curStart in [0:curEnd-1], if v[curEnd].first>v[curStart].first&&v[curEnd].second>v[curStart].second, dp[curEnd]=max(dp[curEnd],dp[curStart]+1), return dp[N-1].]
+ Given n pairs or numbers, where in every pair, the first number is always smaller than the second number. A pair (c, d) can follow another pair (a, b) if b < c. Chain of pairs can be formed in this fashion. Find the longest chain which can be formed from a given set of pairs. The original order of pairs doesn't need to maintain. (LongestChainOfPairs.h)
[DP1D: Sort the given pairs in increasing order of the first (smaller) element. dp[curEnd]=Len of LIS in v[0:curEnd]. Init dp[]=1. For curEnd in [1:N-1], for curStart in [0:curEnd-1], if v[curEnd].first>v[curStart].second, dp[curEnd]=max(dp[curEnd],dp[curStart]+1), return dp[N-1].]
+ Given a list of pairs of integers. Find the longest sequence of pairs where both the first elements and the second elements in the pairs are in increasing order, respectively. The original order of pairs doesn't need to maintain. (LongestIncreasingPairs.h)
[DP1D: Sort the given pairs in increasing order of first elements, sort second elements in decreasing order when firsts are equal. dp[curEnd]=Len of LIS in v[0:curEnd]. Init dp[]=1. For curEnd in [1:N-1], for curStart in [0:curEnd-1], if v[curEnd].first>v[curStart].first&&v[curEnd].second>v[curStart].second, dp[curEnd]=max(dp[curEnd],dp[curStart]+1), return dp[N-1].]
[Greedy: Sort the given pairs in increasing order of first elements, sort second elements in decreasing order when firsts are equal. Init an empty sorted<int,int>. For idx in [0:N-1], lbItr=lowerBound(sorted.begin(),sorted.end(),{a.first<b.first&&a.second<b.second}), if lbItr==sorted.end(), sorted.push_back(v[idx]), else, *lbItr=v[idx], return sorted.size().]
}
+ You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i), width w(i) and depth d(i) (all real numbers). You want to create a stack of boxes which is as tall as possible, but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each strictly larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side functions as its base. It is also allowable to use multiple instances of the same type of box. (BoxStacking.h)
[DP1D: Create an array of 3 rotations of each box <<height,width>,depth>,<<height,depth>,weight>,<<width,depth>,height> where first two are sorted in decreasing order. Sort the array of the first two's product, i.e., bottom area, in decreasing order. dp[curEnd]=Len of LDS in [0:curEnd]. Init dp[]=1. For curEnd in [1:N-1], for curStart in [0:curEnd-1], if v[curStart].first>v[curEnd].first&&v[curStart].second>v[curEnd].second, dp[curEnd]=max(dp[curEnd],dp[curStart]+1), return dp[N-1].]
+ Given a set of distinct positive integers, find the largest subset such that every pair (Si, Sj) of elements in this subset satisfies: Si % Sj = 0 or Sj % Si = 0. If there are multiple solutions, return any subset is fine. (LargestDivisibleSet.h)
[DP: For Si % Sj = 0, if Sj > Si, it must always be 0, so only Si >= Sj is meaningful to test Si % Sj. Sort the array. After sorting the array, this problem becomes similar to find the LIS. But instead of testing increasing, we test v[end] % v[start] == 0 and dp[start] + 1 > dp[end], where dp[i] represents the length of longest %==0 sequence at i. Also keep a prevIdx array to track the prev index of longest %==0 sequence at i.]
+ Given an array of integers, find the length of the longest bitonic subsequence. A sequence is bitonic if it is initially increasing then decreasing. (LBS.h)
[DP1D: dpLR[curEnd]=Len of LIS in [0:curEnd] from left to right, maxLR[curEnd]=max Len of LIS in [0:curEnd], dpRL[curEnd]=Len of LIS in [curEnd:N-1] from right to left, maxRL[curEnd]=max Len of LIS in [curEnd:N-1]. Run DP1D LIS algorithm to compute dpLR[], maxLR[], dpRL[], maxRL[]. For i in [0:N-1], maxLen=max(maxLen,maxLR[i]+maxRL[i]-1), return maxLen.]
[Greedy: sortedLR.size()=Len of LIS in [0:curEnd] from left to right, maxLR[curEnd]=max Len of LIS in [0:curEnd], sortedRL.size()=Len of LIS in [curEnd:N-1] from right to left, maxRL[curEnd]=max Len of LIS in [curEnd:N-1]. Run Greedy LIS algorithm to compute sortedLR[], maxLR[], sortedRL[], maxRL[]. For i in [0:N-1], maxLen=max(maxLen,maxLR[i]+maxRL[i]-1), return maxLen.]
+ Given an array of integers, find the length of the longest increasing sequence. (LIS.h)
[FindLenInExcludeRecur: keep track of startIdx, curMaxVal, and curIncrCount, if startIdx==N, return curIncrCount, else, incrCountExclude=recur(startIdx+1,curMaxVal,curIncrCount), if v[startIdx]>curMaxVal, incrCountExclude=recur(startIdx+1,v[startIdx],curIncrCount+1), return max(incrCountInclude,incrCountExclude).]
[DP1D: dp[curEnd]=Len of LIS in v[0:curEnd]. Init dp[]=1. For curEnd in [1:N-1], for curStart in [0:curEnd-1], if v[curEnd]>v[curStart], dp[curEnd]=max(dp[curEnd],dp[curStart]+1), return dp[N-1].]
[Greedy: Init an empty sorted<int>. For idx in [0:N-1], lbItr=lowerBound(sorted.begin(),sorted.end(),v[idx]), if lbItr==sorted.end(), sorted.push_back(v[idx]), else, *lbItr=v[idx], return sorted.size().]
+ Define a sequence of numbers[a0, a1, a2, ..., a(n-1)] to be convex if ai < (a(i-1) + a(i+1)) / 2, for 1 <= i <= n-2. Given an array of numbers A of length n, find a longest subsequence [i0, i1, i2, ..., i(k-1)] such that [A[i0], A[i1], A[i2], ..., A[i(k-1)]] is convex. (LongestConvexSubseq.h)
[Convex property can be transformed to ai - a(i-1) < a(i+1) - ai. DP1D: create an array pairs<<startVal,startIdx>,<endVal,endIdx>> that enumerates all pairs of A. Sort all the pairs with pair's diffVal in increasing order and pairs' endIdx in decreasing order with equal diffVal. Init dp[0:N-1]=1. For pair in pairs[0:N^2-1], dp[pair.second.second]=max(dp[pair.second.second],dp[pair.first.second]+1). Return dp[N-1].]
+ Given an array of integers, find the length of the longest non-decreasing sequence. (LongestNondecreasingSubseq.h)
[FindLenInExcludeRecur: keep track of startIdx, curMaxVal, and curIncrCount, if startIdx==N, return curIncrCount, else, incrCountExclude=recur(startIdx+1,curMaxVal,curIncrCount), if v[startIdx]>=curMaxVal, incrCountExclude=recur(startIdx+1,v[startIdx],curIncrCount+1), return max(incrCountInclude,incrCountExclude).]
[DP1D: dp[curEnd]=Len of LIS in v[0:curEnd]. Init dp[]=1. For curEnd in [1:N-1], for curStart in [0:curEnd-1], if v[curEnd]>=v[curStart], dp[curEnd]=max(dp[curEnd],dp[curStart]+1), return dp[N-1].]
[Greedy: Init an empty sorted<int>. For idx in [0:N-1], ubItr=upperBound(sorted.begin(),sorted.end(),v[idx]), if ubItr==sorted.end(), sorted.push_back(v[idx]), else, *ubItr=v[idx], return sorted.size().]
+ Given an array of n positive integers. Find the sum of maximum sum subsequence of the given array such that integers in the subsequence are sorted in increasing order. (MaxSumIncrSubseq.h)
[DP1D: dp[curEnd]=Sum of LIS in v[0:curEnd]. Init dp[]=v[]. For curEnd in [1:N-1], for curStart in [0:curEnd-1], if v[curEnd]>v[curStart], dp[curEnd]=max(dp[curEnd],dp[curStart]+v[curEnd]), return the max in dp[].]
}
+ Given a string S and a string T, count the number of distinct subsequences of T in S. (DistinctSubsequences.h)
[InexcludeRecur: keep track of startIdx1, startIdx2, and memo[startIdx1][startIdx2]. If memo[startIdx1][startIdx2]!=-1, return memo[startIdx1][startIdx2], else if startIdx1==N, return memo[startIdx1][startIdx2]=0, else if startIdx2==M, return memo[startIdx1][startIdx2]=1, else, exclude=recur(startIdx1+1,startIdx2), if S[startIdx1]==T[startIdx2], include=recur(startIdx1+1,startIdx2+1), return memo[startIdx1][startIdx2]=exclude+include.]
[DP2D: for startIdx1 in [0:N], for startIdx2 in [0:M], if startIdx1==0, dp[startIdx1][startIdx2]=0, else if startIdx2==0, dp[startIdx1][startIdx2]=1, else, exclude=dp[startIdx1-1][startIdx2], include=S[startIdx1-1]==T[startIdx2-1]?dp[startIdx1-1][startIdx2-1]:0, dp[startIdx1][startIdx2]=exclude+include. Return dp[N][M].]
+ An arithmetic progression (AP) or arithmetic sequence is a sequence of numbers such that difference between the consecutive terms is constant. Given a set of SORTED numbers, determine if there exists a sequence of 3 elements of arithmetic progression in it. (LAPSubseq.h)
[Greedy: for mid in [1:N-2], left=mid-1, right=mid+1, while left>=0&&right<N, if v[left]+v[right]==2*v[mid], return true, else if v[left]+v[right]<2*v[mid], ++right, else, --left. Return false.]
- Given a set of SORTED numbers, find the length of the longest arithmetic progression (LLAP) in it.
[Greedy with DP2D: dp[left][mid]=LLAP with v[left], v[mid] as first two elements of AP. For i in [0:N-1], init dp[i][N-1]=2. For mid in [N-2:1], left=mid-1, right=mid+1, while left>=0&&right<N {if v[left]+v[right]<2*v[mid], ++right, else if v[left]+v[right]>2*v[mid], dp[left][mid]=2, --left, else, dp[left][mid]=dp[right][mid]+1, llap=max(llap,dp[left][mid]), --left, ++right}, while left>=0 {dp[left][mid]=2,--left}. Return llap.]
+ Given two strings A and B, compute the length of the longest sequence of characters that is a subsequence of A and of B. (LCS.h)
[Recur: keep track of startIdx1 and startIdx2. If startIdx1==N || startIdx2==M, return 0, else, if A[startIdx1]==B[startIdx2], return recur(startIdx1+1,startIdx2+1), else, return max(recur(startIdx1+1,startIdx2),recur(startIdx1,startIdx2+1)).]
[DP2D: for startIdx1 in [0:N], for startIdx2 in [0:M], if startIdx1==0||startIdx2==0, dp[startIdx1][startIdx2]=0, else if A[startIdx1]==B[startIdx2], dp[startIdx1][startIdx2]=dp[startIdx1-1][startIdx2-1]+1, else, dp[startIdx1][startIdx2]=max(dp[startIdx-1][startIdx2],dp[startIdx1][startIdx2-1]). Return dp[N][M].]
+ Given an unsorted array of integers, find the length of the longest consecutive elements sequence. (LongestConsecutiveSeq.h)
[Save all integers to a hashSet<int>. While !hashSet.empty {cur=*hashSet.begin, hashSet.erase(cur), min=cur, max=cur, while hashSet.contains(min-1), hashSet.erase(--min), while hashSet.contains(max+1), hashSet.erase(++max), if max-min>resMax-resMin {resMax=max,resMin=min}.}. Return {resMax,resMin}.]
+ Given a string S, find the longest palindromic subsequence in S. (LongestPalindromeSubseq.h)
[Recur: keep track of left and right, if left==right, return 1, if s[left]==s[right] {if left+1==right, return 2, else, return recur(left+1,right-1)+2}, return max(recur(left+1,right),recur(left,right-1)).]
[DP2D: dp[left][right] means longest palindrome subseq length in s[left:right]. For i in [0:N-1], init dp[i][i]=1. For len in [2:N], for left in [0:N-len], right=left+len-1, if s[left]==s[right]&&len==2, dp[left][right]=2, else if s[left]==s[right], dp[left][right]=dp[left+1][right-1]+2, else, dp[left][right]=max(dp[left+1][right],dp[left][right-1]). Return dp[0][N-1].]
[UseLCS: Reverse the given sequence and store the reverse in another array rev[0..n-1]. Compute LCS of the given sequence and rev[] will be the longest palindromic sequence.]
+ Given a string. Find if there is any sub-sequence that repeats itself. (RepeatedSubseq.h)
[Check every pair of chars in alphabet. DP2D: dp[i]=a list of occurrence indices of char i-'a'. For i in [0:N-1], push back i in dp[s[i]-'a']. For firstChar in [a:z], for secondChar in [a:z], if firstChar==secondChar {if firstChar occurs for at least 4 times, record {firstChar,secondChar} in res}, else {if firstChar occurs at least twice && secondChar occurs at least twice && secondChar last occurrence index > firstChar second occurrence index && secondChar prior to last occurrence index > firstChar first occurrence index, record {firstChar,secondChar} to res}. Return res.]
+ Given an array v of integers. Find 3 integers, i, j, k such that i < j < k and v[i] < v[j] < v[k]. (ThreeIncrElementsInArray.h)
[Keep track of a first smallest, and a second smallest num. For each num in v, update first smallest or second smallest. If found a third smallest, we are done.]
}
*/
/*=====================================================================*/
/*
Graph
Coloring{
+ (BipartiteGraph.h)
[]
+ (VertexColoring.h)
[]
}
ConfigPath{
+ (GeneralTowerOfHanoi.h)
[]
+ (WordLadder.h)
[]
}
Euler{
+ (ConnectAllStrInChain.h)
[]
+ (EulerianGraph.h)
[]
}
FordFulkerson{
+ (MaxBipartiteMatching.h)
[]
+ (MaxFlowInFlowNetwork.h)
[]
+ (MaxNumEdgeDisjointPaths.h)
[]
+ (MinSTCutInFlowNetwork.h)
[]
}
ShortestPath{
+ (AllPairsShortestPaths.h)
[]
+ (HighwayNetworkProposal.h)
[]
+ (IsArbitrageExist.h)
[]
+ (ShortestPathInGraph.h)
[]
}
Tarjan{
+ (BiconnectedGraph.h)
[]
+ (BridgesInGraph.h)
[]
+ (CutVerticesInGraph.h)
[]
+ (StronglyConnectedComponents.h)
[]
+ (TwoExistConnectedGraph.h)
[]
+ (TwoForAllConnectedGraph.h)
[]
}
TopologicalSort{
+ Given a dictionary of a new language where it has same characters as English alphabets, i.e., a-z, but different alphabet order of characters. Given a list of character pairs sorted with the order of the alphabets of the new language. Find out the order of the alphabets of the new language. (AlphabetOrderFromGivenDictionary.h)
[Construct a DAG. The min required distinct pair count = 0+1+2+...+25. Verify if min required distinct pair count is satisfied. Compute topological sort order. Verify if topological sort order is unique.]
+ (CourseSchedule.h)
[]
+ (LongestPathInDAG.h)
[]
+ (MinDelayTaskSchedulingDAG.h)
[]
+ (TeamPhoto.h)
[]
+ (TopologicalSortDAG.h)
[]
}
UnionFind{
+ (CyclicGraph.h)
[]
+ (MinSpanningTree.h)
[]
+ (UnionFindGraphComponent.h)
[]
}
+ (CloneGraph.h)
[]
+ (DiameterOfTree.h)
[]
+ (GraphSearch.h)
[]
+ (KEdgePathsInDigraph.h)
[]
+ (MinCashFlow.h)
[]
+ (MinHeightTreesInGraph.h)
[]
+ In a party of N people, only one person is known to everyone. Such a person may be present in the party, if yes, (s)he doesn't know anyone in the party. We can only ask questions like "does A know B?" Find the celebrity in minimum number of questions. (TheCelebrityProblem.h)
[Construct a digraph, where each edge from vertex i to vertex j means i knows j. After the digrah is built, find the sink vertex, which has 0 out-degree and N-1 in-degrees. O(n^2) time to construct the digraph, O(n) time to find the sink vertex.]
[Use 2 pointers left and right: if left knows right, then left can't be the celebrity, eliminate left; if left doesn't know right, then right can't be the celebrity, eliminate right.]
+ (TravelingSalesman.h)
[]
+ (TreeFromParentChildPairs.h)
[]
- Given a list of airline tickets represented by pairs of departure and arrival airports [from, to], reconstruct the itinerary in order. All of the tickets belong to a man who departs from JFK. If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.
[]
+ (TrianglesInGraph.h)
[]
*/
/*=====================================================================*/
/*
Heap
# (BinaryMinHeap.h)
[Keep a level order array and keep track of the total number of nodes. Left=2*idx+1, Right=2*idx+2, Parent=(idx-1)/2.][Insert: push the new element to the back of array and do BubbleUpRecur.][RemoveMin: move the element in the back of array and do BubbleDownRecur.]
- Find K smallest elements in binary heap represented as an array.
[Use a minHeap<val,idx> to do BFS on the level order array.]
- Compare the Kth smallest element in binary heap represented as an array with a number.
[Keep track of a smallerCount and an equalCount. Do DFS from root and return at levels where current number in array is greater than the given number.]
+ (BinomialMinHeap.h)
[]
+ (FibonacciMinHeap.h)
[]
+ (LeftistMinHeap.h)
[]
+ (PairingMinHeap.h)
[]
+ (SkewMinHeap.h)
[]
+ (Treap.h)
[]
*/
/*=====================================================================*/
/*
Interval
+ Given a data stream input of non-negative integers a1, a2, ..., an, ..., summarize the numbers seen so far as a list of disjoint intervals. (DataStreamAsDisjointIntervals.h)
[Use a set to keep a sorted array of intervals by their start vals. When adding a new val, find the upper bound of the set which gives you the first interval whose start>val. Its prev interval whose start must be <= val, so if prev interval whose end is one less than val or greater, merge val starting from prev interval. Keep merging next intervals as long as current end is one less than or greater than next interval's start.]
+ Given an array of non-overlapping interval pairs sorted by left endpoints in ascending order. Insert a new interval (merge if necessary). (InsertInterval.h)
[1. inserts intervals appeared before newInterval. 2. merges intervals that overlap with newInterval. 3. inserts intervals appearing after newInterval.]
+ Given an array of overlapping interval pairs. Count the total number of intersection points. Find the point that overlaps maximum intervals. (IntersectionOfIntervals.h)
[1. sort intervals by start index. 2. for each interval from left, find "the rightmost interval whose start is covered by current interval's end" via binary search, then intervals between current and the rightmost are intersections]
[1. sort all of the start and end points. 2. for each point from left, increment the intersection count when it is a start, decrement when it is an end. keep track of the max intersection count.]
+ Given an array of interval pairs. Compute a list of minimum number of points that covers all the intervals. (LeastPointsCoveringAllIntervals.h)
[1. sort all the intervals by their start points and end points to get two sorted sets. 2. find the leftmost end point of any interval, record it. 3. remove intervals that are coverred by the leftmost end point (intervals whose start point <= the leftmost end point). 4. repeat the above 2 steps until both the 2 sorted sets are empty.]
+ Given an array of interval pairs. Merge all the overlapping intervals. (MergeIntervals.h)
[1. sort all the intervals by their start points. 2. keep track of a prev running interval. If cur interval has overlap with prev running interval, update pre running interval to cover cur. Else, add prev running interval to res and change prev running interval with cur.]
+ Given a list of line segments which is composed of a closed interval of (start,end) points, height, and color. No overlapped intervals have same height. Compute the color intervals when viewing from above. (ViewFromAboveIntervals.h)
[1. sort all end-points by indices. 2. keep track of currently coverred intervals in a sorted map by height. 3 add current interval to map if it's a start-point, else remove interval from map. 3. keep track of a current top interval.]
*/
/*=====================================================================*/
/*
LinkedList
DeleteNode{
+ Given a sorted linked list, delete all duplicates such that each element appear only once. (RemoveDuplicatesSortedLinkedList.h)
[]
- Given a sorted linked list, delete all nodes that have duplicate numbers, leaving only distinct numbers from the original list.
[]
+ Write code to remove duplicates from an unsorted linked list. How would you solve this problem if a temporary buffer is not allowed? (RemoveDupUnsortedLinkedList.h)
[]
[]
+ Delete a given node from a singly linked list. (RemoveGivenNodeInLinkedList.h)
[]
+ Given a linked list, remove the nth node from the end of list and return its head. (RemoveKthNodeFromEndLinkedList.h)
[]
+ Remove all elements from a linked list of integers that have value val. (RemoveNodesWGivenValLinkedList.h)
[]
}
Len{
+ Given a linked list, determine if it has a cycle in it. Follow up: Can you solve it without using extra space? (LinkedListCycle.h)
[]
- Given a linked list, return the node where the cycle begins. If there is no cycle, return null. Follow up: Can you solve it without using extra space?
[]
+ Write a function that takes a pointer to an arbitrary node in a sorted circular linked list, and returns the median of the linked list. (MedianOfSortedCircularLinkedList.h)
[]
+ Given a list, rotate the list to the right by k places, where k is non-negative. (RotateLinkedList.h)
[]
+ Given two linked lists. Find out whether they are converged to a single linked list or not. If yes, find the point of convergence. (YIntersectionLinkedList.h)
[]
}
Merge{
+ Define the even-odd merge of a linked list to be the list consisting of even-numbered nodes followed by the odd-numbered nodes. Implement even-odd merge of a given linked list. (EvenOddMergeLinkedList.h)
[]
+ Given a singly linked list L: L0->L1->...->Ln-1->Ln, reorder it to: L0->Ln->L1->Ln-1->L2->Ln-2->... You must do this in-place without altering the nodes' values. (FoldLinkedList.h)
[]
+ Merge two sorted DOUBLY linked lists and return it as a new list. The new list should be made by splicing together the nodes of the first two lists. (Merge2SortedLinkedLists.h)
[]
+ Merge k sorted linked lists and return it as one sorted list. (MergeKSortedLinkedLists.h)
[]
+ Given a linked list and a value x, partition it such that all nodes less than x come before nodes greater than or equal to x. You should preserve the original relative order of the nodes in each of the two partitions. (PartitionLinkedList.h)
[]
+ Sort a linked list using merge sort. (SortLinkedList.h)
[]
- Sort a linked list using insertion sort.
[]
}
PostingList{
+ A linked list is given such that each node contains an additional random pointer which could point to any node in the list or null. Return a deep copy of the list. (CopyRandomLinkedList.h)
[]
+ A posting list is a singly linked list with an addition "jump" field at each node. The jump field points to any other node. Given a posting list, iterate through all nodes in jump first order. (JumpFirstOrderPostingsLinkedList.h)
[]
}
Reverse{
+ Test whether a singly linked list is palindromic. (PalindromeLinkedList.h)
[]
+ Reverse a singly linked list. (ReverseLinkedList.h)
[]
- Reverse a linked list from position m to n. Do it in-place and in one-pass.
[]
+ Given a linked list, reverse the nodes of a linked list k at a time and return its modified list. If the number of nodes is not a multiple of k then left-out nodes in the end should remain as it is. You may not alter the values in the nodes, only nodes itself may be changed. Only constant memory is allowed. (ReverseNodesInKGroupLinkedList.h)
[]
+ Given a linked list, swap every two adjacent nodes and return its head. Your algorithm should use only constant space. You may not modify the values in the list, only nodes itself can be changed. (SwapNodesInPairsLinkedList.h)
[]
}
+ Given a doubly linked list and an array of references to nodes on the linked list. Count the block of adjacent nodes from the array of references to nodes. A "block" is defined as a group of nodes on the list that are adjacent to each other. (CountBlockOfAdjNodesLinkedList.h)
[]
+ Given a circular single linked list. Write a program that deletes every K-th node until only one node is left. After K-th node is deleted, start the procedure from (K+1)-th node. (JosephusProblem.h)
[]
+ (List.h)
[]
+ (Skiplist.h)
[]
*/
/*=====================================================================*/
/*
Math
+ Given a building with 100 floors and 2 eggs. Assume the egg breaks if dropped at only floor X and higher floors. Design a strategy to calculate the minimum trials required to find out floor X in the worst case. (We want to guarantee the result minimum trials can find the floor X even in the worst case) (EggDrop.h)
[]
- Given N eggs and a limit of D drops, we want to find out the maximum number of floors that you can test in the worst case. Assume there exists a floor x such that the egg will break if it is dropped from any floor x or heigher but will remain intact if dropped from a floor below x.
[]
+ (MinFiveHourseTimeTrial.h)
[]
+ (MinMatchFindBestAndRunnerup.h)
[]
+ You are given two jugs with capacities x and y litres. There is an infinite amount of water supply available. You need to determine whether it is possible to measure exactly z litres using these two jugs. If z liters of water is measurable, you must have z liters of water contained within one or both buckets by the end. (WaterAndJugProblem.h)
[z must be a multiple of GCD(x, y), as well as "z <= x + y" because we cannot get a greater amount of water than the size of x liter jug + y liter jug.]
*/
/*=====================================================================*/
/*
PermuteCombineSubset
Combination{
ContinAccumuSum_SingleBin{
+ Given a set of integers from 1 to n. Count the number of subsets such that the sum of integers in the subset is a prime number. (CombinationPrimeSum1toN.h)
[Compute CombinationSum NumOfWaysNoRepeatFromDupArr DP2D, after DP2D, for i in [1:targetSum], accumulate dp[i][N] if i is a prime.]
+ Given a set of candidate numbers (C) and a targetSum number (T), find all unique combinations in C where the candidate numbers sums to T. The same repeated number may be chosen from C unlimited number of times. (CombinationSum.h)
[FindAllUniquesAllowRepeatFromNoDupArr. FixRecur: keep track of a startIdx, a curSum and a path, if curSum==0, record path and return, otherwise, for i in [startIdx:N-1], if v[i]>curSum then skip, push v[i] to path and recur(startIdx,curSum-v[i]), pop v[i] from path. (AllowRepeat: recur takes startIdx instead of startIdx+1)]
[FindAllUniquesAllowRepeatFromNoDupArr. InExcludeRecur: keep track of a startIdx, a curSum and a path, if curSum==0, record path and return, if startIdx==N, return, otherwise, (include) if v[i]<=curSum, push v[i] to path and recur(startIdx,curSum-v[i]), pop v[i] from path, (exclude) recur(startIdx+1,curSum) (AllowRepeat: recur takes startIdx instead of startIdx+1)]
[NumOfWaysAllowRepeatFromNoDupArr. DP2D: dp[curSumY][curNumX]=count of ways for curSumY from nums[0]~num[curNumX-1]. For curSumY in [0:targetSum], for curNumX in [0:N], if curSumY==0, dp[][]=1, else if curNumX==0, dp[][]=0, else, countIncludeThis= dp[curSumY-v[curNumX-1]][curNumX] (include v[curNumX-1], curNumX for AllowRepeat), countExcludeThis=dp[curSumY][curNumX-1] (exclude v[curNum-1]), dp[][]=countIncludeThis+countExcludeThis.]
- Given a collection of candidate numbers (C) and a targetSum number (T), find all unique combinations in C where the candidate numbers sums to T. Each number in C may only be used once in the combination.
[FindAllUniquesNoRepeatFromDupArr. FixRecur: keep track of a startIdx, a curSum and a path, if curSum==0, record path and return, otherwise, for i in [startIdx:N-1], if v[i]==v[i-1] then skip, if v[i]>curSum then skip, push v[i] to path and recur(startIdx+1,curSum-v[i]), pop v[i] from path. (NoRepeat: recur takes startIdx+1 instead of startIdx)]
[FindAllUniquesNoRepeatFromDupArr. InExcludeRecur: keep track of a startIdx, a curSum and a path, if curSum==0, record path and return, if startIdx==N, return, otherwise, (include) if v[i]<=curSum, push v[i] to path and recur(startIdx+1,curSum-v[i]), pop v[i] from path, (exclude) compute a stride to skip all duplicates and recur(startIdx+stride,curSum) (NoRepeat: recur takes startIdx+1 instead of startIdx)]
[NumOfWaysNoRepeatFromDupArr. DP2D: dp[curSumY][curNumX]=count of ways for curSumY from nums[0]~num[curNumX-1]. For curSumY in [0:targetSum], for curNumX in [0:N], if curSumY==0, dp[][]=1, else if curNumX==0, dp[][]=0, else, countIncludeThis= dp[curSumY-v[curNumX-1]][curNumX-1] (include v[curNumX-1], curNumX-1 for NoRepeat), countExcludeThis=dp[curSumY][curNumX-1] (exclude v[curNum-1]), dp[][]=countIncludeThis+countExcludeThis.]
- Find the minimum number of coins required to make change for a given sum from a set of coins. (MinCoinChange)
[MinCoinsAllowRepeat. DP1D: dp[curSum]=number of min coins required. dp[0]=0. For curSum in [1:targetSum], for curNum in [0:N-1], if v[curNum]<=curSum && dp[curSum-v[curNum]]+1<dp[curSum], dp[curSum]=dp[curSum-v[curNum]]+1. (similar to LIS)]
+ Given n dices with m faces, numbered from 1 to m. Count the number of ways to get a targetSum. targetSum is the summation of values on each face when all the dices are thrown. (DiceCombinationSum.h)
[DP2D: dp[targetSum][diceCount]=number of ways to get targetSum with diceCount dices. For curSum in [1:min(faceCount,targetSum)], init dp[curSum][1]=1 (1 way for only 1 dice). For curSum in [1:targetSum], for curDice in [2:diceCount], for curFace in [1:min(faceCount,curSum)], dp[curSum][curDice]+=dp[curSum-curDice][curDice-1]. Return dp[targetSum][diceCount].]
+ Solve the knapsack problem when the thief can take a fractional amount of an item. (FractionalKnapsack.h)
[Greedy: Sort all items based on the cp value (val/wt) in descending order. Always pick the item with the highest cp value first until total weight exceeds the knapsack's limit.]
+ Given n items with different weights and values. Given a max weight number that a bag can contain. Count the max value of items that can be packed into the bag. What if each item supply is unlimited? (Knapsack.h)
[MaxValAllowRepeatRecur: keep track of startIdx and curWt. If curWt==0||startIdx==N, return 0, else, curValIncludeCurItem=val[startIdx]+recur(startIdx,curWt-Wt[startIdx]), curValExcludeCurItem=recur(startIdx+1,curWt), if Wt[startIdx]>curWt, return curValExcludeCurItem, else, return max(curValIncludeCurItem,curValExcludeCurItem).]
[MaxValNoRepeatRecur: keep track of startIdx and curWt. If curWt==0||startIdx==N, return 0, else, curValIncludeCurItem=val[startIdx]+recur(startIdx+1,curWt-Wt[startIdx]), curValExcludeCurItem=recur(startIdx+1,curWt), if Wt[startIdx]>curWt, return curValExcludeCurItem, else, return max(curValIncludeCurItem,curValExcludeCurItem).]
[MaxValAllowRepeat. DP2D: dp[curWtY][curItemX]: curMaxVal for items from wt/val[0]~wt/val[curItemX-1] with max curWtY. For curWtY in [0:maxWt], for curItemX in [0:N], if curWtY==0||curItemX==0, dp[][]=0, else if wt[curItemX-1]<=curWt, curValIncludeCurItem=val[curItemX-1]+dp[curWtY-wt[curItemX-1]][curItemX] (include val[curItemX-1], curItemX for AllowRepeat), curValExcludeCurItem=dp[curWtY][curItemX-1], dp[][]=max(curValIncludeCurItem,curValExcludeCurItem), else, dp[][]=curValExcludeCurItem.]
[MaxValNoRepeat. DP2D: dp[curWtY][curItemX]: curMaxVal for items from wt/val[0]~wt/val[curItemX-1] with max curWtY. For curWtY in [0:maxWt], for curItemX in [0:N], if curWtY==0||curItemX==0, dp[][]=0, else if wt[curItemX-1]<=curWt, curValIncludeCurItem=val[curItemX-1]+dp[curWtY-wt[curItemX-1]][curItemX-1] (include val[curItemX-1], curItemX-1 for NoRepeat), curValExcludeCurItem=dp[curWtY][curItemX-1], dp[][]=max(curValIncludeCurItem,curValExcludeCurItem), else, dp[][]=curValExcludeCurItem.]
+ Given a set of numbers. Find all unique combinations of k numbers from the set that add up to a sum. (KSum.h)
[Same as CombinationSum FindAllUniquesNoRepeatFromDupArr with adding one more constraint: K numbers.]
+ Given an array of positive integers. Find the smallest positive integer value that cannot be represented as sum of elements of any subset of given set. (MinNonSubsetSumSortedArray.h)
[Compute the prefix sum by accumulating the elements in sorted A from the smallest until meeting an element that is greater than the prefix sum plus one. The answer will be the prefix sum plus one.]
+ Given a set of non-negative integers, and a value targetSum. Determine if there is a subset of the given set with sum equal to given targetSum. (SubsetSumProblem.h)
[Same as CombinationSum: FindAllUniquesNoRepeatFromDupArr and NumOfWaysNoRepeatFromDupArr.]
}
DiscontinAccumuSum_MultiBin{
+ Given k1 items with size of s1, k2 items with size of s2, k3 items with size of s3. Given unlimited number of bins with capacity of Cap, which should be big enough to accommodate the largest item among s1, s2, or s3. Find the min number of bins required to pack all items. (BinPacking.h)
[EnumerateAll: The worst case is to use a single bin to pack a single item, which requires k1+k2+k3 bins. In this case, enumerate all cases to use k1+k2+k3 bins to pack k1+k2+k3 items, and find the best case with minimum bin numbers. See also BinPacking2.h]
[DP3D: Keep track of "the min number of bins that have been used" and "the max remaining volume among current used bins" for all possible combinations of the 3 kinds of items. Compute current "min number of bins that have been used" and "the min occupied bin volume" from previous 3 cases.
dp[][][].first=min num of bins used, dp[][][].second=min occupied bin volume. For i in [0:k1], for j in [0:k2], for k in [0:k3], update dp[][][]<first,second> with "the smallest total num of bins" or "equal total num of bins with smallest occupied volume of bin" from all 3 cases of dp[i-1][j][k] with adding a k1, dp[i][j-1][k] with adding a k2, dp[i][j][k-1] with adding a k3. Return dp[k1][k2][k3].first.]
+ Given M boxes with different sizes and N items with different volumes. Determine if all the items can be filled into these boxes. (BinPacking2.h)
[Since the order of assigning a task to a particular server doesn't matter, just need to assign all tasks in a fixed order to all available servers with remaining quotas in a fixed order. That is, assign a task to an available server with its memory quota subtracted, do it from the first server to the last in a fixed order, fix that, and repeat for the next task. This will skip repeated permutations in the 1st method.]
[ValidEnumerateAllRecur: keep track of a itemStartIdx, if itemStartIdx==N, return true, else, for curBox in [0:M-1] (always start from the 1st box to enumerate all cases), if items[itemStartIdx]<=boxes[curBox], boxes[curBox]-=items[itemStartIdx], recur(itemStartIdx+1), boxes[curBox]+=items[itemStartIdx].]
[MinBinEnumerateAllRecur: keep track of a itemStartIdx, usedBinCount, and minBinCount, if itemStartIdx==N, record boxWithItems[][] and minBinCount if usedBinCount<minBinCount and return, else, for curBox in [0:M-1] (always start from 1st box to enumerate all cases), if items[itemStartIdx]<=boxes[curBox], boxes[curBox]-=items[itemStartIdx], ++usedBinCount if boxWithItems[curBox] is empty, push items[itemStartIdx] to boxWithItems[curBox], recur(startIdx+1,usedBinCount,minBinCount), pop items[itemStartIdx] from boxWithItems[curBox], --usedBinCount if boxWithItems[curBox] is empty, boxes[curBox]+=items[itemStartIdx].]
+ Given n items with different sizes and an unlimited supply of boxes with same size which is big enough to accommodate the largest item. Find the minimum number of boxes that are needed to pack all items. (FirstFitPacking.h)
[TournamentTree: keep a level order traversal array with size=2*leafNodeCount+1. Each node contains a list of itemIdx, a capacity (indicates max(v[left].capacity,v[right].capacity)) and a left and right child. InsertRecur: keep track of parentIdx, itemIdx, and itemCapacity, compute left=parentIdx*2+1, right=parentIdx*2+2, if left>v.size (parentIdx is a non-leaf), insertRecur(v[left].capacity>=itemCapacity?left:right), v[parentIdx].capacity=max(v[left].capacity,v[right].capacity), else, v[parentIdx].capacity-=itemCapacity, push itemIdx in v[parentIdx]'s item list.]
}
FullLengthInOrder{
+ Given a binary string pattern s that contains '1', '0', and '?', where wildcard '?' can be either '1' or '0'. Find out all possible binary strings. (AllBinaryStrWithWildCard.h)
[EnumerateAllRecur: keep track of a startIdx and path, if startIdx==N, record path and return, else, if s[startIdx]=='?', push '0' to path, recur(startIdx+1), pop '0' from path, push '1' to path, recur(startIdx+1), pop '1' from path, else, push s[startIdx] to path, recur(startIdx+1), pop s[startIdx] from path.]
+ Find all combinations of strings from list of list of strings, N*M. Example: [quick, slow], [brown, red], [fox, dog]. Output: quick brown fox, quick brown do, quick red fox, quick red dog, slow brown fox, slow brown dog, slow red fox, slow red dog. (Combinations2.h)
[EnumerateAllRecur: keep track of a startIdx and path, if startIdx==N, record path and return, else, for curOption in [0:M-1], add strs[startIdx][curOption] to path, recur(startIdx+1), pop strs[startIdx][curOption] from path.]
+ Given an array of house prices. You can rob no concsecutive 2 houses. Find the max price you can rob. What if the array forms a circle? (HouseRobber.h)
[Non-circular: dp[0]=v[0]. dp[1]=max(v[0],v[1]). For i in [2:N-1], dp[i]=max(dp[i-2]+price[i],dp[i-1]). Return dp[N-1].]
[Circular: 1st iteration compute dp1 include first exclude last. 2nd iteration compute dp2 exclude first include last. Return max(dp1[N-1],dp2[N-1]).]
+ Given a number digit string, return all possible letter combinations that the number could represent. Input: Digit string "23", Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]. (LetterCombinationPhoneNum.h)
[FindAllRecur: init a numToChars array. Keep track of startIdx and path, if startIdx==N, record path and return, else, for curCharOption in numToChars[s[startIdx]-'0'], add curCharOption to path, recur(startIdx+1), pop path.]
+ There is a fence with n posts, each post can be painted with one of the k colors. You have to paint all the posts such that no more than two adjacent fence posts have the same color. Return the total number of ways you can paint the fence. (PaintFenceCombinations.h)
[Keep a res array with size=4. res[0]=0. res[1]=k(can choose from k colors). res[2]=k*k(can be either same or diff colors with res[1]). res[3]: if res[1] and res[2] have same colors, k * (k-1) ways; if res[1] and res[2] have diff colors, k*(k-1) * k ways; in total (k-1)*(res[1]+res[2]) ways.]
+ There are a row of n houses, each house can be painted with one of the three colors: red, blue or green. You have to paint all the houses such that no two adjacent houses have the same color. The cost of painting each house with a certain color is represented by a n x 3 cost matrix. Compute the min cost to paint all houses. What if K colors? (PaintHouseCombinations.h)
[dp[i][0]=cost[i][0]+min(dp[i-1][1],dp[i-1][2]), dp[i][1]=cost[i][1]+min(dp[i-1][0],dp[i-1][2]), dp[i][2]=cost[i][2]+min(dp[i-1][0],dp[i-1][1]).]
[O(n*k^2)time: For j in [0:k], for jj in [0:k], if (jj != j)(avoid same colors with prev house) dp[i][j]= min(dp[i-1][jj]+cost[i][j],dp[i][j]). O(n*k)time: keep track of a prevMin(min cost till prev house), prevSec(second min cost till prev house), prevMinIdx(the color used to paint prev house with min cost), for each house i, compute cost of painting current house for using colors j in [0:K-1], cost[i][j]=cost[i][j]+(prevMinIdx ==j?prevSec:prevMin) (for the case of same colors with prev house, use prevSec (prev second min)).]
+ Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses. (ParenthesesCombination.h)
[FindAllRecur: keep track of leftParenCount, rightParenCount and path, if leftParenCount==0&&rightParenCount==0, record path and return, else, if leftParenCount>0, push '(' to path, recur(leftParenCount-1,rightParenCount), pop path, if rightParenCount>0, push ')' to path, recur(leftParenCount,rightParenCount-1), pop path.]
+ A car factory has two assembly lines, each with n stations. Each station takes some process time. A car in one line can be transfered with a transfer time to the next station in another line. Each line has an entry time and an exit time. Find out the minimum time it requires to build a car. (TwoAssemblyLineScheduling.h)
[DP1D: T1[0]=entryTime[0]+stationTime[0][0], T2[0]=entryTime[1]+stationTime[1][0]. For each station i in [1:N-1], T1[i]=min(T1[i-1]+stationTime[0][i],T2[i-1]+transferTime[1][i]+stationTime[0][i]), T2[i]=min(T2[i-1]+stationTime[1][i],T1[i-1]+transferTime[0][i]+stationTime[1][i]). Return min(T1[N-1]+exitTime[0],T2[N-1]+exitTime[1]).]
}
+ Given two integers n and k, return all possible combinations of k numbers out of 1 ... n. What if each number can be repeated for unlimited times? (Combinations.h)
[FindAllNoRepeat: FixRecur: keep track of startIdx, remainCount and path. If remainCount==0, record path and return, else, for curNum in [startIdx:N], push curNum to path, recur(startIdx+1,remainCount-1), pop out curNum from path.]
[FindAllNoRepeat: InExcludeRecur: keep track of startIdx, remainCount and path. If remainCount==0, record path and return, else if startIdx==N, return, else, push curNum to path, recur(startIdx+1,remainCount-1) for including curNum, pop out curNum from path, recur(startIdx+1,remainCount) for excluding curNum.]
[FindAllAllowRepeat: FixRecur: keep track of startIdx, remainCount and path. If remainCount==0, record path and return, else, for curNum in [startIdx:N], push curNum to path, recur(startIdx,remainCount-1), pop out curNum from path.]
[FindAllAllowRepeat: InExcludeRecur: keep track of startIdx, remainCount and path. If remainCount==0, record path and return, else if startIdx==N, return, else, push curNum to path, recur(startIdx,remainCount-1) for including curNum, pop out curNum from path, recur(startIdx+1,remainCount) for excluding curNum.]
- Given two integers n and k, count the number of all possible combinations of k numbers out of 1 ... n. What if each number can be repeated for unlimited times?
[NumOfWaysNoRepeat: Formula: n! / (k! * (n-k)!). DP2D: dp[curNumY][curCountX]=num of ways for curNumY in [1:curNumY) with curCountX-1 nums. For curNumY in [0:n), for curCountX in [0:k), if curNumY==curCountX, dp[][]=1 (use up all available nums so has 1 way), else if curCountX==0, dp[][]=curNumY+1 (has curNumY+1 nums available so has curNumY+1 ways for 1 digit), else, dp[][]=dp[curNumY-1][curCountX-1]+dp[curNumY-1][curCountX] ("less 1 nums less 1 count" + "less 1 num same count"). Return dp[n-1][k-1].]
[NumOfWaysAllowRepeat: Formula: (n+k-1)! / (k! * (n-1)!). DP2D: dp[curNumY][curCountX]=num of ways for curNumY in [1:curNumY) with curCountX-1 nums. For curNumY in [0:n), for curCountX in [0:k), if curNumY==0, dp[][]=1 (has 1 num available so has 1 way), else if curNumX==0, dp[][]=curNumY+1 (has curNumY+1 nums available so has curNumY+1 ways for 1 digit), else, dp[][]=dp[curNumY][curCountX-1]+dp[curNumY-1][curCountX] ("same nums less 1 count" + "less 1 num same count"). Return dp[n-1][k-1].]
+ Given a non-negative integer n, count all numbers with unique digits, x, where 0 <= x < 10^n. (CountNumbersWithUniqueDigits.h)
[DP: len==1: 10 (can choose 0~9), len==2: 9*9 (first 1~9, second: include 0 exclude first, 9), len==3: 9*9*8 (third: include 0 exclude first and second, 8) ..., len==k: 9*9*8*7*...*(9-k+2). Accumulate all from k to 1.]
[Recur: compute the max num pow(10, n). keep track of used digit by using lower 10 bits of an integer. First digit is [1:9], non-first digit is [0:9]. For digit in [1:9] or [0:9], compute next number = 10*prevNum + digit.]
+ Given an integer, return all possible combinations of all its factors. Factors should be greater than 1 and less than n. (FactorCombinations.h)
[DFSrecur: keep track of a curBegin of factors (from 2 to n-1), a curProduct of prev factors, a path of factors for curProduct. Corner cases: curProduct>n, return; curProduct==n, record path. Enumerate curFactor from curBegin to n-1, skip curFactor*curProduct>n, if n%(curFactor*curProduct)==0, add curFactor to path and recur down.]
+ Suppose a jug can only measure volume in a range of [low, high]. Given a list of jugs with different measuring ranges. Given a target range. Determine if a volume in the target range can be obtained from the given jugs. Find all possible sequence of steps to obtain a volume in the target range with the given jugs. (MeasureWithDefectiveJugs.h) (Similar to Subsets.h)
[FindAllAllowRepeatRecur: FixRecur: keep track of startIdx, curL, curH, and path, if curL>=L&&curL<=H, record path, for jug in [startIdx:N-1], if jugs[jug].L+curL>H, skip, push jugs[jug] in path, recur(startIdx,curL+jugs[jug].L,curH+jugs[jug].H), pop path.]
[FindAllAllowRepeatRecur: InExcludeRecur: keep track of startIdx, curL, curH, and path, if curL>=L&&curL<=H, record path, if startIdx==N, return, (include jugs[startIdx]) if jugs[startIdx].L+curL<=H, push jugs[startIdx] to path, recur(startIdx,curL+jugs[startIdx].L,curH+jugs[startIdx].H), pop path, (exclude jugs[startIdx]) recur(startIdx+1,curL,curH).]
+ A decimal number is a sequence of digits, i.e., a sequence over {0,1,2,3,4,5,6,7,8,9}. The sequence has to be of length 1 or more, and the first element in the sequence cannot be 0. Call a decimal number D monotone if D[i] <= D[i+1], 0 <= i < |D|. Given a length K, count the number of possible monotone decimal numbers of length K. (MonotoneDecimalNums.h)
[DP2D: dp[curNumY][curCountX]=num of ways with curCountX+1 digits where each digit is in [0:curNumY+1]. For curNumY in [0:9), for curCountX in [0:9), if curNumY==0, dp[][]=1 (has 1 digit available so has 1 way), else if curCountX==0, dp[][]=curNumY+1 (has curNumY+1 digits available so has curNum+1 ways for 1 digit), else, dp[][]=dp[curNumY][curCountX-1]+dp[curNumY-1][curCountX] ("same digit less 1 count" + "less 1 digit same count"). Return dp[8][tgtLen-1].]
[FindAllAllowRepeat Recur: Keep track of startIdx, remainCount, and path, if remainCount==0, record path and return, for curNum in [startIdx,9], push curNum to path, recur(startIdx,remainCount-1), pop curNum from path.]
+ Given a sorted positive integer array nums and an integer n, add/patch elements to the array such that any number in range [1, n] inclusive can be formed by the sum of some elements in the array. Return the minimum number of patches required. (PatchingArray.h)
[Assume the combination sum of first k numbers in nums can reach any number in [1,total), if we add a nextNum where nextNum<=total, the combination sum of the k+1 numbers can reach any number in [1,total+nextNum). The special case is when nextNum==total, then the combination sum of the k+1 numbers can reach any number in [1,total*2). So if the (k+1)th num in nums is <= total, it goes to the above case. Otherwise, if the (k+1)th num in nums is > total, or there is no (k+1)th num, we need to add a new number "total" such that the new combination sum can reach any number in [1,total*2).]
+ A decimal number is a sequence of digits, i.e., a sequence over {0,1,2,3,4,5,6,7,8,9}. The sequence has to be of length 1 or more, and the first element in the sequence cannot be 0. Call a decimal number D strickly monotone if D[i] < D[i+1], 0 <= i < |D|. Given a length K, count the number of possible strickly monotone decimal numbers of length K. (StricklyMonotoneDecimalNums.h)
[DP2D: dp[curNumY][curCountX]=num of ways with curCountX+1 digits where each digit is in [0:curNumY+1]. For curNumY in [0:9), for curCountX in [0:9), if curNumY==curCountX, dp[][]=1 (use up all available digits so has 1 way), else if curCountX==0, dp[][]=curNumY+1 (has curNumY+1 digits available so has curNum+1 ways for 1 digit), else, dp[][]=dp[curNumY-1][curCountX-1]+dp[curNumY-1][curCountX] ("less 1 digit less 1 count" + "less 1 digit same count"). Return dp[8][tgtLen-1].]
[FindAllNoRepeat Recur: Keep track of startIdx, remainCount, and path, if remainCount==0, record path and return, for curNum in [startIdx,9-remainCount+1], push curNum to path, recur(startIdx+1,remainCount-1), pop curNum from path.]
+ Given a set of distinct integers, S, return all possible subsets. (Subsets.h)
[FindAllNoRepeatFromNoDupArr: FixRecur: keep track of a startIdx and path, record path, for curIdx in [startIdx:N-1], push v[curIdx] in path, recur(curIdx+1), pop v[curIdx] from path.]
[FindAllNoRepeatFromNoDupArr: InExcludeRecur: keep track of a startIdx and path, if startIdx==N-1, record path and return, else, push v[startIdx] in path, recur(startIdx+1) for including v[startIdx], pop v[startIdx] from path, then recur(startIdx+1) for excluding v[startIdx].]
- Given a collection of integers that might contain duplicates, S, return all possible subsets.
[FindAllNoRepeatFromDupArr: Sort the array. FixRecur: keep track of a startIdx and path, record path, for curIdx in [startIdx:N-1], IF v[curIdx]==v[curIdx-1] skip duplicate, push v[curIdx] in path, recur(curIdx+1), pop v[curIdx] from path.]
[FindAllNoRepeatFromDupArr: Sort the array. InExcludeRecur: keep track of a startIdx and path, if startIdx==N-1, record path and return, else, push v[startIdx] in path, recur(startIdx+1) for including v[startIdx], pop v[startIdx] from path, then compute a stride to skip duplicates of v[startIdx], recur(startIdx+stride) for excluding v[startIdx] and all duplicates.]
}
ConsecutivePartition{
+ A sub-array partition of an array is to insert (at least 0, at most N-1) break points in between elements of an array so that the array can be partitioned into one or more sub-arrays. Given an integer array, return all possible sub-array partitions. (AllSubArrayPartitions.h)
[1. For numBreaks in [0:N-1], generate all possible combinations of numBreaks numbers out of breakIdx[1:N-1], see Combinations.h. 2. From 1. we get a list of breakIdx combinations, we split the original array into groups based on each breakIdx array.]
+ A message containing letters from A-Z is being encoded to numbers using the mapping: 'A' -> 1, 'B' -> 2 ..., 'Z' -> 26. Given an encoded message containing number digits, determine the total number of ways to decode it. (DecodeWays.h)
[DP1D: dp[i]=total decode ways of s[0]~s[i-1]. dp[0]=1 (means s[0] has 1 way). For i in [1:N], (including a single s[i-1]) if s[i-1]!='0', dp[i]=dp[i-1], (including s[i-2]~s[i-1]) if i-2>=0&&(s[i-2]=='1'||s[i-2]=='2'&&s[i-2]<='6'), dp[i]+=dp[i-2].]
[FindAllRecur: keep track of a startIdx and path, if startIdx==N, record path and return, else, (including s[startIdx]) if s[startIdx]!='0', push path, recur(startIdx), pop path, (including s[startIdx]~s[startIdx+1]) if startIdx+1<N && s[startIdx]=='1'||(s[startIdx]=='2'&&s[startIdx+1]<='6'), push path, recur(startIdx+2), pop path.]
+ Given an integer array. Find all break points such that the sum of elements from index 0 to index (break point - 1) is equal to the sum of index break point to index N-1. (EqualSum2SubArrPartition.h) <-> EquilibriumIndexOfArray.h
[PrefixSum: compute a prefixSumL[] and prefixSumR[]. For i in [0:N], if (i==0&&prefixSumR[i]==0)||(i==N&&prefixSumL[i-1]==0)||(i!=0&&i!=N&&prefixSumL[i-1]==prefixSumR[i]), record i in res[]. Return res[].]
[Init sumLR=0, sumRL=totalSum. For i in [0:N-1], if sumLR==sumRL, record i in res[], sumLR+=v[i], sumRL-=v[i]. Return res[].]
+ Equilibrium index of an array is an index such that the sum of elements at lower indices is equal to the sum of elements at higher indices. (EquilibriumIndexOfArray.h) <-> EqualSum2SubArrPartition.h
[Init a rightSum = total sum and a leftSum = 0. For each v[i] from left to right, rightSum-=v[i], compare rightSum with leftSum, leftSum+=v[i].]
+ Write a function to generate the generalized abbreviations of a word. Given word = "word", return the following list (order does not matter): ["word", "1ord", "w1rd", "wo1d", "wor1", "2rd", "w2d", "wo2", "1o1d", "1or1", "w1r1", "1o2", "2r1", "3d", "w3", "4"]. (GeneralizedAbbreviation.h)
[Recur: (recursively enumerate front+num+...) keep track of a startIdx, for numBegin in [startIdx:N-1], for numLen in [1:N-numBegin+1], record "s[0:front]+numLen.toStr()+s[numBegin+numLen+1:N-1]", recur(numBegin+numLen.toStr().size()+1).]
+ Given 2 strings. Find out all the interleavings of the 2 strings. (Interleave2Strings.h)
[Recur: keep track of startIdx1, startIdx2, and path, if startIdx1==N1&&startIdx2==N2, record path, else, if startIdx1==N1 {add s2[startIdx2:N2-1] to path, recur(N1,N2), pop path, return}, if startIdx2==N2 {add s1[startIdx1:N1-1] to path, recur(N1,N2), pop path, return}, add s1[startIdx1] to path, recur(startIdx1+1,startIdx2), pop path, add s2[startIdx2] to path, recur(startIdx1,startIdx2+1), pop path.]
+ Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and s2. s3 is said to be interleaving s1 and s2, if it contains all characters of s1 and s2  and order of all characters in individual strings is preserved. (InterleavingString.h)
[If N3!=N1+N2, return false. Recur: keep track of startIdx1, startIdx2, startIdx3, if startIdx3==N3 {if startIdx1==N1&&startIdx2==N2, return true, else return false}, else, return s1[startIdx1]==s3[startIdx3]&&recur(startIdx1+1,startIdx2,startIdx3+1) || s2[startIdx2]==s3[startIdx3]&&recur(startIdx1,startIdx2+1,startIdx3+1).]
[If N3!=N1+N2, return false. DP2D: for startIdx1 in [0:N1], for startIdx2 in [0:N2], if startIdx1==0&&startIdx2==0, dp[startIdx1][startIdx2]=1, else if s1[startIdx1-1]==s3[startIdx1+startIdx2-1]&&dp[startIdx1-1][startIdx2], dp[startIdx1][startIdx2]=1, else if s2[startIdx2-1]==s3[startIdx1+startIdx2-1]&&dp[startIdx1][startIdx2-1], dp[startIdx1][startIdx2]=1. Return dp[N1][N2].]
+ Given an array of words. Find the longest word that can be decomposed into other words. (LongestWordMadeOfOthers.h)
[Sort the array words by length, find the 1st word that can be decomposed into other words. DecomposableRecur: keep all words in a hashMap, keep all other words that are visited in another visitedHashMap, keep track of curWord, for leftLen in [1:N], leftWord=curWord[0:leftLen-1], rightWord=curWord[leftLen:N-1], if hashMap contains leftWord: if hashMap contains rightWord, return true, else if visitedHashMap contains rightWord, return false, else if recur(rightWord), return true. Insert curWord in visitedHashMap and return false.]
+ Given a rod of length N inches and an array of prices that contains prices of all pieces of size smaller than N. Determine the maximum value obtainable by cutting up the rod and selling the pieces. (MaxPriceCutting.h)
[Recur: keep track of remainLen, if remainLen<=0, return 0, else, for curLen in [0:remainLen-1], maxPrice=max(maxPrice,prices[curLen]+recur(remainLen-(curLen+1)), return maxPrice.]
[DP1D: dp[len]=max price of len. dp[0]=0. For curLen in [1:N], for priceLen in [0:curLen-1], dp[curLen]=max(dp[curLen],prices[priceLen]+dp[curLen-(priceLen+1)], return dp[N].]
+ Given a rope of length N meters, cut the rope in different parts of integer lengths in a way that maximizes product of lengths of all parts. You must make at least one cut. Assume the length of rope is more than 2 meters. (MaxProductCutting.h)
[Recur: keep track of remainLen, if remainLen==1||remainLen==0, return 0, else, for curLen in [1:remainLen-1], maxProduct=max(maxProduct,curLen*(remainLen-curLen),curLen*recur(remainLen-curLen)), return maxProduct.]
[DP1D: dp[len]=max price of len. dp[0]=dp[1]=0. For curLen in [1:N], for halfLen in [1:curLen/2], dp[curLen]=max(dp[curLen],halfLen*(curLen-halfLen),halfLen*dp[curLen-halfLen]), return dp[N].]
+ Given an array of integers. Find a subarray(s) in which each subarray has the same smallest sum. Worst case: cannot be partitioned into equal sum subarrays, then the min subarray sum is the total sum of the array. (MinEqualSumSubArrPartition.h)
[BruteForce: enumerate all possible consecutive partitions, test each consecutive partition has equal subarray sum, find the partition that has min equal subarray sum. see AllSubArrayPartition.h]
[Greedy: check if any prefixSum is divisible by the totalSum and is a valid equal sum partition. For i in [0:N-1], prefixSum+=v[i], if prefixSum>totalSum/2 {partitionable=false, break}, if totalSum%prefixSum!=0, continue, else {for j in [i+1:N-1], prefixSum2+=v[i], if prefixSum2>prefixSum {valid=false, break}, else if prefixSum2==prefixSum, prefixSum2=0. if prefixSum2==0 {partitionable=true, break}}. If !partitionable, minSubarrSum=totalSum, else, minSubarrSum=prefixSum. Return minSubarrSum.]
+ Given an array of non-negative integers A and a positive integer k, Divide A into k or fewer partitions (subarrays), such that the maximum sum over (among) all the partitions is minimized. Return the minimized maximum sum over all the partitions. (PaintersPartitionFairWorkload.h)
[Recur: keep track of curLen and curK, if curK==1, return SumRange(0,curLen-1), else if curLen==1, return v[0], else, for leftLen in [1:curLen], minMax=min(minMax,max(recur(leftLen,curK-1),SumRange(leftLen,curLen-1))), return minMax.]
[DP2D Recur: prepare a prefixSum[], keep a dp[curLen][curK], replace SumRange(i,j) with prefixSum[j]-prefixSum[i-1], record each minMax in dp[][].]
[DP2D Iterate: prepare a prefixSum[], keep a dp[curLen][curK], for i in [0:N-1], init dp[i][0]=prefixSum[i], for j in [0:K], init dp[0][j]=v[0], for curK in [1:K-1], for curLen in [1:N-1], for leftLen in [0:curLen], minMax=min(minMax,max(dp[leftLen][curK-1],prefixSum[curLen]-prefixSum[leftLen])), dp[curLen][curK]=minMax, return dp[N-1][K-1].]
[BinarySearchGreedyPartition: keep a lo=0, hi=totalSum, keep 1 entry in between, binary search lb=min limit of each partition, comopute mid=current limit of each partition, prepare an array with size K and test if it is feasible to greedily assign all val in v to the array without exceeding the limit of each bin, lb will be the final lo which is the final min limit of each partition.]
+ Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s. (PalindromePartitioning.h)
[FindAllRecur: keep track of startIdx and path, if startIdx==N, record path and return, else, for curEnd in [startIdx:N-1], if !isPalindrome(startIdx,curEnd), continue, add s[startIdx:curEnd] to path, recur(curEnd+1), pop path.]
[FindAllDP2D: dp[left][right]==1 means s[left:right] is a palindrome. Keep a breakables[][][] where breakables[right] is a vector of "vector of palindrome segments in s[0:right]". For right in [0:N], for left in [0:right], if s[left]==s[right]&&(right-left<2||dp[left+1][right-1]) {dp[left][right]=1, if left==0, add s[left:right] to breakables[left], else, for palindromeSegmentsV in breakables[left-1], add s[left:right] to palindromeSegmentsV, add palindromeSegmentsV to breakables[right]}. Return breakables[N-1].]
- Return the minimum cuts needed for a palindrome partitioning of s.
[DP2D: dp[left][right]==1 means s[left:right] is a palindrome. Keep a dpCut[right] which means min cuts in s[0:right]. For right in [1:N-1], dpCut[right]=right, for left in [0:right], if s[left]==s[right]&&(right-left<2)||dp[left+1][right-1]) {dp[left][right]=1, dpCut[right]=min(dpCut[right],left==0?0:dpCut[left-1]+1}. Return dpCut[N-1].]
+ Given a string containing only digits, restore it by returning all possible valid IP address combinations. Given "25525511135", return ["255.255.11.135", "255.255.111.35"]. (RestoreIPAddress.h)
[FindAllRecur: keep track of a startIdx, groupCount and path, if startIdx==N||groupCount==4, record path only if startIdx==N&&groupCount==4, return, else, for curDigit in [startIdx:N-1], compute curNum=10*curNum+s[curDigit]-'0' and recur(curDigit+1,groupCount+1), early break when curNum>255.]
+ Given a string s1, we may represent it as a binary tree by partitioning it to two non-empty substrings recursively. To scramble the string, we may choose any non-leaf node and swap its two children. Given two strings s1 and s2 of the same length, determine if s2 is a scrambled string of s1. (ScrambleString.h)
[Recur: keep track of startIdx1, startIdx2, len, and memo[startIdx1][startIdx2][len], if memo[startIdx1][startIdx2][len]!=-1, return memo[startIdx1][startIdx2][len], else if len==1, return memo[startIdx1][startIdx2][len]=(s1[startIdx1]==s2[startIdx2]), else, for k in [1:len-1], if (recur(startIdx1,startIdx2,k)&&recur(startIdx1+k,startIdx2+k,len-k))||(recur(startIdx1,startIdx2+len-k,k)&&recur(startIdx1+k,startIdx2,len-k)), return memo[startIdx1][startIdx2][len]=1. Return memo[startIdx1][startIdx2][len]=0.]
[DP3D: for len in [1:N], for startIdx1 in [0:N-len], for startIdx2 in [0:N-len], if len==1, {if s1[startIdx1]==s2[startIdx2], dp[startIdx1][startIdx2][len]=1, continue}, else, for k in [1:len-1], if (dp[startIdx1][startIdx2][k]&&dp[startIdx1+k][startIdx2+k][len-k])||(dp[startIdx1][startIdx2+len-k][k]&&dp[startIdx1+k][startIdx2][len-k]) {memo[startIdx1][startIdx2][len]=1, break}. Return dp[0][0][N].]
+ Given a string that contains only digits 0-9 and a target value, return all possibilities to add binary operators (not unary) +, -, or * between the digits so they evaluate to the target value. (SynthesizeExpression.h)
[FindAllRecur: keep track of a startIdx, a string curNum, a operandPath<int> and operatorPath<char>, early return if curNum[0]=='0' (starting with 0), push back v[startIdx] to curNum, if startIdx==N-1, record operandPath and operatorPath if evaluate to target value, return, else, (include curNum to the next running num) recur(startIdx+1,curNum), (exclude curNum to the next running num) push curNum to operandPath, push '+'/'-'/'*' to operatorPath, recur(startIdx+1,""), pop operatorPath, pop operandPath.
EvaluateFunc: use iterators to perform 1. compute multiplication: erase first operand and update second operand as the result; erase '*' operators. 2. compute addition/subtraction of all operands.]
+ Given a string s and a dictionary of words dict, determine if s can be segmented into a space-separated sequence of one or more dictionary words. (WordBreak.h)
[Recur: keep track of curWord, if curWordLen==0, return true, else, for leftLen in [1:curWordLen], if curWord[0:leftLen-1] can be founded in dict && recur(curWord[leftLen:curWordLen-1]), return true. Return false.]
[DP1D: dp[curLen]==1 means s[0:curLen-1] can be segmented into a serious of dict words or not. Init dp[0]=1. for curLen in [1:N], for leftLen in [0:curLen], if dp[leftLen]&&s[leftLen:curLen-1] is contained in dict, dp[curLen]=1, return dp[N]==1.]
- Given a string s and a dictionary of words dict, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.
[DP2D: dp[curLen]=a list of breakable indices in s[0:curLen-1]. Init dp[0]={0}. For curLen in [1:N], for leftLen in [0:curLen-1], if dp[leftLen] not empty && s[leftLen:curLen-1] contained in dict, push leftLen to dp[curLen]. For curLen in [1:N], for each leftLen in dp[curLen], append all leftWord combinations from breakables[leftWord] with current rightWord s[leftLen:curLen-1], then add each to breakables[curLen], the special case is when leftLen==0 in which case we have only rightWord s[0:curLen-1] without leftWord so just add s[0:curLen-1] to breakables[curLen]. Return breakables[N].]
+ Given a pattern and a string str, find if str follows the same pattern. Here follow means a full match, such that there is a bijection between a letter in pattern and a non-empty word in str. For example, pattern = "abba", str = "dog cat cat dog" should return true. (WordPattern.h) <-> IsomorphicStrings.h
[Split all strs and save in an array. Keep a fwdMap<char,string> and bwdMap<string,char> for bidirectional mappings. For each pair of (char,string) from pattern and str, if both are not found, just insert both, if both are found, compare found with current, otherwise one found the other not found, early return false. Finally return true when all check passed.]
- What if str is not splited by whitespace? For example, pattern = "abab", str = "redblueredblue" should return true.
[Recur: keep an index pBegin to pattern and an index sBegin to str. At current char, enumerate all substrings starting from sBegin with lengths from 1 to end, then for current char anc current substring, find their mappings from fwdMap<char,string> and bwdMap<string,char> and insert/erase to perfrom DFS.]
}
EnumerateSubRangeConsecuPartitions{
+ Given N bombs placed in a circle. Each bomb has a value and a explosion range. When you detonate a bomb, you can get its value, but the bomb will destroy its neighbors in its explosion range. Design an algorithm to find the maximun value of bombs if you can only detonate in a fixed order from left to right. What if you can detonate in an arbitrary order? (BombsInACircle.h)
[FixedOrder: ConstSpace Recur: keep track of fwd and bwd, if fwd>=N, return 0, if fwd>bwd, return 0, if fwd==bwd, return val[fwd], include=val[fwd]+recur(fwd+range[fwd]+1,newBwd(bwd,fwd-range[fwd]-1). exclude=recur(fwd+1,bwd). Return max(include,exclude).]
[FixedOrder: LinearSpace Recur: keep track of a detonated array and startIdx from left to right to include/exclude cur bomb. If startIdx==N, return 0, Compute include only when detonated[cur]==false and make a copy of detonated array and mark all detonated bombs in the copy. Return max(include,exclude).]
[ArbitraryOrder: Compute a permutation array of nums [0:N-1] using include/exclude. In the end of recursion (which results in a particular permutation order), then use LinearSpace Recur to compute max val with that permutation order.]
+ Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent. Find the maximum coins you can collect by bursting the balloons wisely. (BurstBallons.h)
[Recur: keep track of left and right, keep track of dp[left][right], if left>right, return 0, else if dp[left][right]!=-1, return dp[left][right], else, for mid in [left:right], dp[left][right]=max(dp[left][right],nums[left-1]*nums[mid]*nums[right+1]+recur(left,mid-1)+recur(mid+1,right), return dp[left][right].]
[DP2D: dp[left][right]=coins in [left:right]. For len in [1:N], for left in [1:N-len+1], right=left+len-1, for mid in [left:right], dp[left][right]=max(dp[left][right],nums[left-1]*nums[mid]*nums[right+1]+dp[left][mid-1]+dp[mid+1][right]). Return dp[1][N].]
+ A K-palindrome is a string which transforms into a palindrome on removing/inserting at most K characters. Given a string, determine if s is a K-palindrome. (KPalindrome.h)
[Recur: keep track of left, right and remainK, while left<right&&s[left]==s[right] {++left, --right}, if left>=right, return true, (now s[left:right] is non-palindrome), if remainK==0, return false, return recur(left+1,right,remainK-1)||recur(left,right-1,remainK-1).]
- Given a string, count the number of deletions/insertions of characters K to transform it into a palindrome.
[Recur: keep track of left and right, while left<right&&s[left]==s[right] {++left, --right}, if left>=right, return 0, (now s[left:right] is non-palindrome), return min(recur(left+1,right),recur(left,right-1))+1.]
[DP2D: for len in [2:N], for left in [0:N-len], right=left+len-1, dp[left][right]=s[left]==s[right]?dp[left+1][right-1]:min(dp[left+1][right],dp[left][right-1])+1.]
+ Given an array that contains dimensions of matrices. Find the minimum number of multiplications needed to multiply the chain of matrices. (A[i-1],A[i]) forms a dimension pair of a matrix A[i]. The count of multiplications of 2 matrices A[i] (A[i-1],A[i]) and A[i+1] (A[i],A[i+1]) is A[i-1]*A[i]*A[i+1]. The result matrix A[i+1] has dimension (A[i-1],A[i+1]). (MatrixChainMultiplication.h)
[Recur: keep track of left and right, if left==right, return 0, else, for mid in [left:right-1], curCount=recur(left,mid)+recur(mid+1,right)+v[left-1]*v[mid]*v[right], keep track of a minCount=min(minCount,curCount), return minCount.]
[DP2D: dp[left][right]=min count of multiplication in [left:right]. For i in [1:N-1], init dp[i][i]=0 ([i:i] means 0 matrix). For len in [2:N], for left in [1:N-len+1], right=left+len-1, for mid in [left:right-1], curCost=dp[left][mid]+dp[mid+1][right]+v[left-1]*v[mid]*v[right], keep track of a minCost=min(minCost,curCost), dp[left][right]=minCost. Return dp[1][N-1]. len==1 means 1 matrix.]
+ Given an array of N integers, and an array of (N-1) operations in set (+,-,*). The two arrays form a mathematical expression of arithmetics. Use parentheses to find the maximum sum of the mathematical expression. (MaxSumParenthesizeArithmeticExpr.h)
[DP2D: dp[left][right]<int,int>=<maxSum,minSum> in [left:right]. For i in [0:N-1], init dp[i][i]<int,int>=<v[i],v[i]>. For len in [2:N], for left in [0:N-len+1], right=left+len-1, for mid in [left:right-1], compute maxTmax=dp[left][mid].first*dp[mid+1][right].first, maxTmin, minTmax, minTmin, maxPmax, minPmin, maxSubtmin, maxSubtminRev, minSubtmax, minSubmaxRev, if op[mid]=='+', max=maxPmax, min=minPmin, else if op[mid]=='*', max=max(maxTmax,maxTmin,minTmax,minTmin), min=min(maxTmax,maxTmin,minTmax,minTmin), else if op[mid]=='-', max=max(maxSubtmin,maxSubtminRev), min=min(minSubtmax,minSubtmaxRev), dp[left][right]={max,min}. Return dp[0][N-1].first.]
+ Given a polygon with N vertices and N edges. There is an integer number (could be negative) on every vertex and an operation in set (*,+) on every edge. Every time we remove an edge from the polygon and merge the two vertices linked by the edge to a new vertex with value (v1 op v2). The last case would be two vertices with two edge, and the result is the bigger one. Return the max result value that can be gotten from a given polygon. (MaxVerticesSumOfPolygon.h)
[DP2D: dp[left][right]<int,int>=<maxSum,minSum> in [left:right]. For i in [0:N-1], init dp[i][i]={v[i],v[i]}. For len in [2:N], for left in [0:N-len+1], right=left+len-1, for mid in [left:right-1], compute maxTmax=dp[left][mid].first*dp[mid+1][right].first, maxTmin, minTmax, minTmin, maxPmax, minPmin, if e[mid]=='*', max=max(maxTmax,maxTmin,minTmax,minTmin), min=min(maxTmax,maxTmin,minTmax,minTmin), else if e[mid]=='+', max=maxPmax, min=minPmin, dp[left][right].first=max(dp[left][right].first,max), dp[left][right].second=min(dp[left][right].second,min), return dp[0][N-1].]
+ A triangulation of a convex polygon is formed by drawing diagonals between non-adjacent vertices (corners) such that the diagonals never intersect. Given an array of (x,y) coordinates, find the cost of triangulation with the minimum cost. The cost of a triangulation is sum of the weight of its component triangles. Weight of each triangle is its perimeter (sum of lengths of all sides). (MinCostPolygonTriangulation.h)
[Recur: keep track of left and right, if left+1==right, return 0, else, for mid in [left+1:right-1], minCostLeftPol=recur(left,mid), minCostRightPol=recur(mid,right), costCurTriangle=SumDist(left,mid,right), totalCost=minCostLeftPol+minCostRightPol+costCurTriangle, keep track of a minTotalCost, return minTotalCost.]
[DP2D: dp[left][right]=min total cost in [left:right]. For len in [3:N], for left in [0:N-len+1], right=left+len-1, keep track of a minTotalCost, for mid in [left+1:right-1], totalCost=dp[left][mid]+dp[mid][right]+SumDist(left,mid,right), update minTotalCost=min(minTotalCost,totalCost), dp[left][right]=minTotalCost. Return dp[0][N-1].]
+ Given a string of numbers and operators, return all possible results from computing all the different possible ways to group numbers and operators. The valid operators are +, - and *. (ParenthesizeArithmeticExpr.h)
[Split s into operands<int> and operators<char>. Recur: keep track of left, right, if left==right, return {operands[left]}, else if right-left==1, return {eval(operands[left],operands[right],operators[left])}, else, for mid in [left:right], resLeft=recur(left,mid), resRight=recur(mid+1,right), compute all combinations of resLeft[i] and resRight[j] into res (eval(resLeft[i],resRight[j],operator[mid])), return res.]
+ Given a boolean expression which contains symbols(T, F) and operators(&, |, ^), count the number of ways we can parenthesize the expression to yield a result of True or False. (ParenthesizeBoolExpr.h)
[Recur: keep track of operandLeft, operandRight and curRes, if operandLeft==operandRight, if (exp[operandLeft]&&curRes)||(!exp[operandLeft]&&!curRes), return 1, else return 0, else, if curRes==true, for operatorIdx in [operandLeft+1:operandRight-1], operatorIdx+=2, if exp[operatorIdx]=='&', count+=recur(operandLeft,operatorIdx-1,true)*recur(operatorIdx+1,operandRight,true), else if exp[operatorIdx]=='|', count+=recur(operandLeft,operatorIdx-1,true)*recur(operandRight,operatorIdx+1,true)+recur(operandLeft,operatorIdx-1,true)*recur(operatorIdx+1,operandRight,false)+recur(operandLeft,operatorIdx-1,false)*recur(operatorIdx+1,operandRight,true)
, else if exp[operatorIdx]=='^', count+=recur(operandLeft,operatorIdx-1,true)*recur(operatorIdx+1,operandRight,false)+recur(operandLeft,operatorIdx-1,false)*recur(operatorIdx+1,operandRight,true), else if curRes==false, do the samething, then return count.]
[DP3D Recur: keep a dp[operandLeft][operandRight]<int,int>=pairs of count of expressions in exp[operandLeft:operandRight] of <eval==true,eval==false>. Recursion is same as above.]
}
NonConsecutivePartition{
+ Given a set of numbers. Determine if it can be partitioned into 2 subsets such that the sums of elements in both subsets are the same. (BalancedPartitionWEqual2Sum.h)
[Equivalent to determine if there is a subset that sums to totalSum/2. See CombinationSum: FindAllUniqueNoRepeatFromDupArr, NumOfWaysNoRepeatFromDupArr.]
+ Given a set of numbers. Divide it into 2 subsets such that the difference between the sums of the 2 subsets is minimal. Return the sums of the 2 subsets. What if the 2 subsets have to be equal sized? (BalancedPartitionWMin2SumDiff.h)
[DP1D: dp[curSum]==true means a valid combination sum curSum of any elements in the array. Init dp[0]=true (a sum of 0 is a combination sum of 0 element). For curNum in [0:N-1], for curSum in [totalSum:v[i]], dp[curSum]=dp[curSum]|dp[curSum-v[i]], if dp[curSum]==true which means curSum is a vaild combination sum of some elements, update minHalfSumDiff if curSum is closer to totalSum/2.]
[Recur: Keep track of a startIdx, curSum, halfCount, minSumDiff, and path. If halfCount==0, update path if abs(totalSum/2-curSum)<minSumDiff, else, for i in [startIdx,N-halfCount+1], curSum+=v[i], push v[i] to path, recur(startIdx+1,curSum,halfCount-1), pop v[i] from path, curSum-=v[i].]
+ Given an array of even task durations. Divide the array into subsets where each subset has exactly 2 tasks, such that the maximum subset sum of the 2-task durations over all subsets is minimized. (Fair2TaskAssignment.h)
[Sort the array. The 2-task partition will be {v[0],v[N-1]}, {v[1],v[N-2]}, ..., {v[N/2-1],v[N/2]}.]
+ Given an array of integers in the range of [0,9] inclusive. Partition and rearrange the integers into 2 groups such that the sum of the 2 numbers represented by each group is minimum. Return the minimum sum. (MinSumOf2IntFromADigitArr.h)
[Sort the array. One number will be digits from the even indices and the other will be digits from the odd indices. Return the sum of the 2 numbers.]
}
Permutation{
+ Given n and k, return the kth permutation sequence of the set [1,2,3,...,n]. (KthPermutationSequence.h)
[permuCount=factorial(n), digitCount=n, K=0-based, num[]={1,2,3,...,n}. For digitCount in [n:1], permuCount/=digitCount, numIdx=K/permuCount, record and remove num[numIdx], K%=permuCount.]
+ Given a list of non negative integers, arrange them such that they form the largest number. For example, given [3, 30, 34, 5, 9], the largest formed number is 9534330. Return the string format of formed number. (MaxPermutedConcatNum.h)
[Sort the array based on string concatenation of 2 strings: concat1=toString(num1)+toString(num2), concat2=toString(num2)+toString(num1), return concat1<concat2.]
+ Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers. If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order). The replacement must be in-place, do not allocate extra memory. (NextPermutation.h)
[Find ascendingEnd from back in ascending order. Reverse(num[ascendingEnd],num[N-1]). If ascendingEnd>0, pivot=ascendingEnd-1, ascendingUpperBound=upperBound(num[ascendingEnd],num[N-1],num[pivot],less<int>()), swap(num[pivot],num[ascendingUpperBound]).]
+ Given a collection of numbers, return all possible permutations. (Permutations2.h)
[FindAllFromNoDupArr, n!: keep track of startIdx, if startIdx==N, record num array and return, else, for curNum in [startIdx:N-1], swap(num[startIdx],num[curNum]), recur(startIdx+1), swap(num[startIdx],num[curNum]).]
- Given a collection of numbers that might contain duplicates, return all possible unique permutations.
[FindAllUniqueFromDupArr, n!/((dupCount_1)!*(dupCount_2)!*(dupCount_3)!*...*(dupCount_DistinctNumCount)!): keep track of startIdx, if startIdx==N, record num array and return, else, keep a visitedHashSet, for curNum in [startIdx:N-1], skip visitedHashSet[num[curNum]], add num[curNum] to visitedHashSet, swap(num[startIdx],num[curNum]), recur(startIdx+1), swap(num[startIdx],num[curNum]).]
+ Write a program to test whether the letters forming a string s can be permuted to form a palindrome. Given a string s, return all the palindromic permutations (without duplicates) of it. Return an empty list if no palindromic permutation could be form. (PermutedPalindrome.h)
[Use a HashTable<char,count> to keep track of char count. Compute the total number of "oddCount" in the HashTable, if oddCount <= 1, return true, else return false.]
[Use a HashTable<char,count> to keep track of char count. Determine if the string can form a palindrome using "oddCount". Collect all evenCount chars with their evenCount/2 duplicates in a half string. Collect all oddCount chars with their (oddCount-1)/2 duplicates in the half string. Record the mid char for the sole oddCount char. Sort the half string and find all unique permutations of it, then for each permutation of half, append mid+reverseOfHalf.]
+ Implement previous permutation, which rearranges numbers into the lexicographically previous less permutation of numbers. The replacement must be in-place, do not allocate extra memory. (PreviousPermutation.h)
[Find descendingEnd from back in descending order. Reverse(num[descendingEnd],num[N-1]). If descendingEnd>0, pivot=descendingEnd-1, descendingUpperBound=upperBound(num[descendingEnd],num[N-1],num[pivot],greater<int>()), swap(num[pivot],num[descendingUpperBound]).]
+ Given two arrays, src, tgt, containing two permutations of numbers 0...n-1. Rearrange src so that it equals tgt. The only allowed operation is "swap a number with 0". (Swap0ConvertPermutation.h)
[Find srcZeroIdx in src. For tgtIdx in [0:N-1], find srcIdx in [0:N-1] such that tgt[tgtIdx]==src[srcIdx], then move src[srcIdx] to src[tgtIdx] by: swap(src[srcZeroIdx],src[tgtIdx]), srcZeroIdx=tgtIdx, swap(src[srcZero],src[srcIdx]), srcZeroIdx=srcIdx.]
[Insert all src[] to a srcIdxMap<entry,index> which maps entry to index. For tgtIdx in [0:N-1], find srcIdx in [0:N-1] which is srcIdxMap[tgt[tgtIdx]], then move src[srcIdx] to src[tgtIdx] by: swap(src[srcZeroIdx],src[tgtIdx]), update srcIdxMap, srcZeroIdx=tgtIdx, swap(src[srcZero],src[srcIdx]), update srcIdxMap.]
}
+ (AllWalprimes.h)
[]
*/
/*=====================================================================*/
/*
Random
BinarySearch{
+ Given a positive integer N, and a sorted num array, K, containing integers [1, N]. Generate a random number with probability 1/(N-K.size()) from 1~N exclude all integers in K. Expected O(log(K.length)) time, O(1) space. (Rand1toNExcludeKSortedNum.h)
[Binary search a random number among interval nums: rand()%(N-K.size())+1, which is also the "accumulated interval nums count". Keep using the "accu interval nums count" to compare in mind. Find the lower bound of the random accumulated interval nums count: interval nums accumulated count till i = K[i] - (i+1). (i+1: transform to 1-based).
After found the lower bound of accumulated interval nums count, if lb==N, accuIntervalNumCountAtN=K.back()-N, extraMore=randAccuIntervalNumCount-accuIntervalNumCountAtN, resNum=K.back()+extraMore. Otherwise, accuIntervalNumCountAti=K[lb]-(lb+1), extraLess=accuIntervalNumCountAti-randAccuIntervalNumCount, resNum=K[lb]-1-extraLess. Insert resNum to K[lb].]
- Compute random numbers from 1 to N without duplicates without using hash table.
[Same as above.]
+ Given n numbers, each with some frequency of occurrence. Return a random number with probability proportional to its frequency of occurrence. (RandomFromProbDist.h)
[Compute an accumulated prob array. Binar search the lower bound of a given prob in the accu prob array.]
}
ModuloBias{
+ Compute a rand7 with a given rand5 func. (Rand7FromRand5.h)
[Since we want to get rand7, we need to use rand()%7, but it has modulo bias, to get rid of modulo bias, we have to make the RAND_MAX of a random func to be a multiple of 7. Since we have rand5, we can get uniform rand1~25 by "5*(rand5()-1)+rand5()", and repeat calling this until its val is <21, which is a multiple of 7, then %7 will be a uniform rand7.]
+ Modulo bias is the problem when using rand()%number to get a rand from 0~number when RAND_MAX is not a multiple of number. Write code to get a random from 0~number without modulo bias. (RandWoModuloBias.h)
[Repeat calling rand() when number<RAND_MAX && randNum >= RAND_MAX-(RAND_MAX%number). When randNum < RAND_MAX-(RAND_MAX%number), get randNum%number, which is our answer.]
}
Offline{
+ Let A be an array whose entries are all distinct. Implement an algorithm that takes A and an integer k and returns a subset of k elements of A. All subsets should be equally likely. (OfflineSampling.h)
[For the first k elements in the array, swap v[i] with an random pick from v[i] to v[N-1]: swap(v[i], rand()%(N-i)+i).]
+ Compute a random permutation of a given number n. (RandomPermutation.h)
[Prepare an array of [1...n]. Perform offline sampling: for each element, swap v[i] with an random pick from v[i] to v[N-1]: swap(v[i], rand()%(N-i)+i).]
+ Given N, compute a random subset of {0,1,2,3,...,N-1} with size k. All subsets should be equally likely and, in addition, all permutations of elements of the array should be equally likely. Time complexity should be O(k). Your algorithm can use O(k) space in addition to the k element array for the result. (RandomSubset.h)
[Since time complexity is limited to O(k), we can't construct an array A with N elements. Mimic offline sampling. Keep a HashMap<idx,idx> to track of "first k indices from begin and their mapped indices", as well as "other k indices and their mapped indices that were swapped with the first k indices". For first k indices, compute its mapped randIdx=rand()%(N-i)+i, then insert {randIdx,i} and {i,randIdx} to HashMap or swap their values if already existed.]
}
Online{
+ Given a stream of numbers, generate a random number from the stream. You are allowed to use only O(1) space and the input is in the form of stream, so can't store the previously seen numbers. (RandomFromStream.h)
[Keep a reservoir array of size 1 and save the first element from input stream. Keep track of the total count of elements from input stream. Iterate over the rest elements and compute a randIdx=rand()%totalCount, if randIdx<1, swap reservoir[0] with current element.]
+ Randomly choose k samples from a list of n items, where n is either a very large or unknown number. Typically n is large enough that the list doesn't fit into main memory. (ReservoirSampling.h)
[Keep a reservoir array of size k and save the first k elements from input stream. Keep track of the total count of elements from input stream. Iterate over the rest elements and compute a randIdx=rand()%totalCount, if randIdx<k, swap reservoir[randIdx] with current element.]
+ Given an array, write a program to generate a random permutation of array elements. (ShuffleArray.h)
[For each element v[i], compute a randIdx=rand()%(i+1), and swap v[i] with v[randIdx].]
}
+ (AliasMethod.h)
[]
+ Given a lambda, compute a random number from exponential distribution. (RandomFromExponentialDist.h)
[Get a random number in [0:1) by rand()/RAND_MAX. Then compute -(log(1-randNum)/lambda), which is our answer.]
+ Given a low and high number, compute a random number in [low:high] using rand2. (UniformRandFromRand2.h)
[Compute the difference of high-low. Repeat computing a digit 0/1 from rand2 and OR it to the LSB of an integer until the integer is >= difference. Return the integer+low.]
+ (UniformRandom.h)
[]
*/
/*=====================================================================*/
/*
RMQLCA
GraphTreeLCA{
+ (LowestCommonAncestorDP2D.h)
[]
+ (LowestCommonAncestorEulerTourRMQ.h)
[]
+ (LowestCommonAncestorSectionDad.h)
[]
+ (LowestCommonAncestorUnionFind.h)
[]
}
+ (CartesianTree.h)
[]
+ (RangeMinQueryDP2D.h)
[]
+ (RangeMinQuerySegmentTree.h)
[]
+ (RangeMinQuerySparseTable.h)
[]
+ Given an integer array nums, return the number of range sums that lie in [lower, upper] inclusive. Range sum S(i, j) is defined as the sum of the elements in nums between indices i and j (i <= j), inclusive. (RangeSumCount.h)
[Use multiset to keep sorted prefixSums. For each integer, accumulate the distance btw lowerBound of (curPrefixSum-upper) and upperBound of (curPrefixSum-lower), then insert curPrefixSum to the sorted prefixSum multiset.]
+ (RangeSumQueryBinaryIndexedTree.h)
[]
+ Given an integer array nums, find the sum of the elements between indices i and j (i <= j), inclusive. The nums in array can be modified. (RangeSumQuerySegmentTree.h)
[Recur: keep track of left and right of input array, keep track of curIdx (leftChild=2*curIdx+1, rightChild=2*curIdx+2) of segmentTree array, when seeing a leaf (left==right), return segmentTree[curIdx]=v[left], otherwise, return segmentTree[curIdx]=leftChildSum+rightChildSum.]
+ Given a 2D inetger matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2). The nums in matrix can be modified. (RangeSumQuerySegmentTree2D.h)
[rowRecur: keep track of topRowY and bottomRowY of matrix, keep track of rowY (topChild=rowY*2+1, bottomChild=rowY*2+2) of segmentTree]
[colRecur: keep fixed rowY, topRowY, bottomRowY from rowRecur. keep track of leftColX and rightColX of matrix, keep track of colX (leftChild=colX*2+1, rightChild=colX*2+2) of segmentTree]
[when seeing a leaf (topRowY==bottomRowY && leftColX==rightColX), return segmentTree[rowY][colX]=matrix[topRowY][leftColX]]
[otherwise, it must be a parent node with 2 leaves, return segmentTree[rowY][colX]=topChildSum+bottomChildSum or segmentTree[rowY][colX]=leftChildSum+rightChildSum]
+ Given a 2D matrix matrix, find the sum of the elements inside the rectangle defined by its upper left corner (row1, col1) and lower right corner (row2, col2). (RangeSumQueryWPrefixSums.h)
[Immutable2D. Build prefixSums matrix: prefixSums[i][j] = matrix[i][j] + prefixSums[i-1][j] + prefixSums[i][j-1] - prefixSums[i-1][j-1]. Submatrix sum between [row1,col1], [row2,col2] inclusive is prefixSums[row2][col2] - prefixSums[row1-1][col2] - prefixSums[row2][col1-1] + prefixSums[row1-1][col1-1].]
[Mutable2D. Build rowPrefixSums matrix: rowPrefixSums[i][j] = matrix[i][j] + rowPrefixSums[i][j-1]. Update: rowPrefixSums[row][col~M-1] += (val - (rowPrefixSums[row][col]-rowPrefixSums[row][col-1])). Query: res += (rowPrefixSums[row1~row2][col2] - rowPrefixSums[row1~row2][col1-1]).]
[Mutable1D. Build prefixSums array: prefixSums[i] = v[i] + prefixSums[i-1]. Update: prefixSums[i~N-1] += (prefixSums[i]-prefixSums[i-1]). Query: prefixSums[i]-prefixSums[i-1].]
*/
/*=====================================================================*/
/*
SortSearchSelect
BinarySearch{
+ Search a sorted array for first occurrence of k (lower bound), Search a sorted array for the first element greater than k (upper bound). (BinarySearch.h)
+ Given an array of n distinct integers sorted in ascending order, write a function that returns a Fixed Point in that array, if there is any Fixed Point present in array, else, return -1. Fixed Point in an array is an index i such that arr[i] is equal to i. What if duplicates present? (BinarySearchFixedPoint.h)
+ Let A be a sorted array. The length of A is not known in advance; access A[i] for i beyond the end of the array throws an exception. Design an algorithm that takes A and a key k and returns an index i such that A[i] = k; return -1 if k doesn't appear in A. (BinarySearchUnknownLength.h)
+ Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad. (FirstBadVersion.h)
[Binary search the lower bound which is the first bad version.]
+ Guess a number in [1, 2, ..., N]. Every time you guess wrong, I'll tell you whether the number is higher or lower. -1: My number is lower. 1: My number is higher. 0: You got it. (GuessNumberHigherOrLower.h)
[Binary search the lower bound.]
+ Implement interpolation search on a sorted array. (InterpolationSearch.h)
+ A peak element is an element that is greater than its neighbors. Given an input array where "num[i] != num[i+1]", find a peak element and return its index. The array may contain multiple peaks, in that case return the index to any one of the peaks is fine. You may imagine that "num[-1] = num[n] = INT_MIN". For example, in array [1, 2, 3, 1], 3 is a peak element and your function should return the index number 2. (LocalMaximumInUnsortedArray.h)
+ Given an unsorted integer array A, with A[0] >= A[1] and A[N-2] <= A[N-1]. Call an index i a local minimum if A[i] is less than or equal to its neighbors. How would you efficiently find a local minimum, if one exists? (LocalMinimalInUnsortedArrah.h)
+ Given a sorted array of integers, find the starting and ending position of a given target value. Your algorithm's runtime complexity must be in the order of O(log n). If the target is not found in the array, return [-1, -1]. (SearchForRange.h)
+ Suppose a sorted array is rotated at some pivot unknown to you beforehand. (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2). You are given a target value to search. If found in the array return its index, otherwise return -1. You may assume no duplicate exists in the array. What if duplicates are allowed? (SearchInRotatedSortedArray.h)
+ Given a sorted array and a target value, return the index if the target is found. If not, return the index where it would be if it were inserted in order. You may assume no duplicates in the array. (SearchInsertionPos.h)
+ Given a sorted array of strings which is interspersed with empty strings, write a method to find the location of a given string. For example, ["at","","","","ball","","","car","","","dad","",""], find "ball" will return 4, and find "ballcar" will return -1. (SearchInterspersedSortedStrArray.h)
}
MultiSortedArrays{
2dHeap{
+ An m x n Young tableau is an m x n matrix such that the entries of each row are in sorted order from left to right and the entries of each column are in sorted order from top to bottom. Implement the ExtractMin and Insert methods. Implement the sorting algorithm using a Young tableau. (YoungTableau.h)
[ExtractMin: update INT_MAX at (0,0), then bubble down.][Insert: update value at (m-1,n-1), then bubble up.][Sort: Insert all elements to a sqrt(N)*sqrt(N) young tableau. Then ExtractMin for N times from young tableau.]
}
Merge{
+ Given two arrays of length m and n with digits 0-9 representing two numbers. Create the maximum number of length k <= m + n from digits of the two. The relative order of the digits from the same array must be preserved. Return an array of the k digits. (CreateMaxNumberFrom2Arrays.h)
[Enumerate all possible cases to split k into nums1 and nums2: k1 in [max(0,k-len2),min(k,len1)], k2=k-k1. Compute 2 sorted stacks in decending order (max number) from nums1 with k1 and nums2 with k2. Merge the 2 sorted stacks in decending order with greedy algorithm. Keep track of the max decending order number of the merged sorted stacks. Be careful on the greedy merge routine where the comparison to get next large element is based on the comparison of the nums array from current index to end.]
+ Given k sorted arrays with each size of n. Merge the k sorted arrays. (KwayMergeSort.h)
[Keep a minHeap<val,<val's list's index, val's index in list>> with size K]
+ Given two sorted integer arrays A and B, merge B into A as one sorted array. What if in place is required? (Merge2SortedArrays.h)
[InPlace: start from back.]
+ Given 2 sorted arrays. Compute the union and intersection of the 2 sorted arrays, respectively. (UnionIntersection2SortedArrays.h)
}
MinRange{
+ Given 2 sorted arrays of integer. Find a pair of integers, one from each array, such that the absolute difference between the 2 integers is minimum. (MinPairDiff2SortedArrays.h)
[Keep track of the smallest element from each array and their difference. Advance the smaller one to its next right.]
+ You have K lists of sorted integers. Find the smallest range that includes at least one number from each of the K lists. (MinRangeOverKSortedLists.h)
[Use a minHeap<val,<val's list's index,val's index in list>> to keep track of K smallest elements with each from a different list. Also keep track of the max element among the K elements.]
}
SearchMatrix{
+ Given a 2d matrix that is sorted in row-wise and column-wise in non-descending order. The first integer of each row is NOT necessarily greater than the last integer of the previous row. Search for a given value in the matrix. (SaddlebackSearchSortedMatrix.h)
[UpperRightLinearSearch: can find all occurrences on the left side of cur row]
+ Given a 2d matrix that is sorted in row-wise in non-descending order. The first integer of each row is greater than the last integer of the previous row. (Search2dSortedMatrix.h)
[1DBinarySearch, which only works for the condition "each row's first element is greater than prev row's last element".][UpperRightLinearSearch][2DBinarySearchUpperLowerRows: binary search col on mid row, if not found, need to search both upper rows and lower rows.][2DBinarySearchLowerLeftQuadUpperRightQuad: binary search row lower bound on mid col, if not found, need to search both lower left quad and upper right quad.]
}
Select{
BinarySearch{
# Given two sorted arrays A and B of lengths M and N, respectively, and a positive integer K in [1, M+N]. Find the K-th smallest element in array formed by merging A and B. (KthSmallestElement2SortedArrays.h)
[Binary search the 2 sorted array.]
+ Given two sorted arrays A and B of size m and n respectively. Find the median of the two sorted arrays. (Median2SortedArrays.h)
[Keep track of cur min in A and cur min in B to find the (m+n)/2-th and (m+n)/2-1-th elements from the 2 sorted array. For odd (m+n), it is (m+n)/2-th. Otherwise, avg of (m+n)/2-th and (m+n)/2-1-th.][Use binary search of KthSmallestElement2SortedArrays to find both the (m+n)/2-th and (m+n)/2-1-th elements.]
}
MinHeap{
+ Given a matrix that is sorted in row-wise and column-wise. Search for the K-th smallest element in the matrix. (KthSmallestSortedMatrix.h)
[Use a minHeap<val,<rowY,colX>> to do BFS for K times. Keep track of (x,y) indices that have been visited. When popping out the top element, push both its next right and next lower elements if haven't been visited.][Use the ExtractMin method of YoungTableau for K times.]
+ Given 2 sorted array of numbers, a and b, with size of N and M where N > M. Find Kth smallest pair sum a[i]+b[j]. (KthSmallestPairSum2SortedArrays.h)
[Use a minHeap<sum,<aIdx,bIdx>> to do BFS for K times. Keep track of (i,j) indices that have been visited. When popping out the top element, push both (cur element in a, next right of b) and (cur element in b, next right of a) elements if the pair combination haven't been visited.]
}
+ Given an unsorted matrix. Search for the K-th smallest element in the matrix. (KthSmallestElementInMatrix.h)
[1D QuickSelect. To1D: rowY*numCol+colX. To2D: (idx/numCol, idx%numCol).]
}
+ Given 2 string arrays A and B containing names in ascending order. Find the names that appear only once from the 2 arrays. (SinglesFrom2SortedStrArr.h)
[Greedy: keep 2 ptrs i and j to A and B. Compare A[i] with B[j], if non-equal, record the smaller one and advance, else, advance both i and j, until either i or j out of bound. Then record the remainings in A and in B.]
+ An array A of n integers is said to be k-increasing-decreasing if elements repeatedly increase up to a certain index after which they decrease, then again increase, a total of k times. Sort a k-increasing-decreasing array. (SortKIncrDecrArray.h)
[Construct a 2D array of k subarrays in increasing order. Do KWayMergeSort.]
}
Partition{
+ Given an unsorted array and a pivot element. Rearrange the array such that elements smaller equal to the pivot elements on the left. (Partition.h)
[2Way: while (i=first <= j=last)][3Way: curFrontCount, curBackCount, while (i=first <= curBackCount)][4Way: curFrontCount, curBackCount, while (i2=first <= i3=last)]
+ Given an array with positive and negative numbers. Rearrange the array so that all the negative numbers are in the front and all the positive numbers are in the back. The relative order of each group should be preserved. (StablePartition.h)
[Modify MergeSort. In postorder, find the pivots from both left and right results (L1L2R1R2), then reverse the subarray between the 2 pivots (L1R1'L2'R2), then reverse R1' and L2', respectively (L1R1L2R2).]
}
PermutationOrder{
+ Given an unsorted array and an integer array that is a permutation of [1...n]. Move each element in the first array to its target index specified in the second array. v[Idx[i]-1] <- v[i] (move cur element to remote). (ApplyPermutationOrder.h)
[For each element from begin, if not visited or is DFS leftmost, perform DFS to repeatedly find next target index and move cur element to its target index until target index goes back to the current index.]
+ An inverse permutation is a permutation in which each number and the number of the place which it occupies are exchanged. Given an integer array that is a permutation of [1...n], compute its inverse permutation. (InversePermutationArray.h)
[Perform a DFS from begin to repeatedly find next target index which is "current value - 1", then move "current index + 1" to target index, and so on until target index goes back to begin.]
+ Given an unsorted array and an integer array that is a permutation of [1...n]. For each position in the first array, move the element associated with the index in the second array to the current position. v[i] <- v[Idx[i]-1] (move remote element to cur). (SortByPermutationOrder.h)
[For each element from begin, save a copy in the permutation array. Copy all elements from the permutation array.][For each element from begin, if target index is on right side of cur index, swap; if equal, skip; if on left side, repeated find a next target index until it is on right side or equal to cur index, then swap.]
}
Select{
Median{
+ Given an unsorted integer array. Compute the first K elements that are closest to the median of the array. (FirstKClosestToMedianElements.h)
[QuickSelect find the median. Keep a maxHeap of K elements with smallest abs distance from the median and loop through the array.][QuickSelect find the median. Modify QuickSelect to repeatedly partition the array based on abs distance from median.]
+ Given an unsorted integer array. Find the median. (MedianElement.h)
[QuickSelect find the N/2-th element for odd array, or the avg of the N/2-th and (N/2-1)-th for even array.]
+ Design an algorithm for computing the running median of a sequence. (MedianOfIntegerStream.h)
[Keep both a maxHeap and a minHeap. Make sure the size difference of the 2 heaps is no larger than 1. The avg of the 2 top elements will be the running avg.]
+ Find the median of medians. (MedianOfMedians.h)
[]
* Given an array of (number of resident, apartment distance from begin) pairs. Compute a distance m from the beginning of the street to place a mailbox that minimizes the total distance, that residents travel to get to the mailbox. (WeightedMedianElement.h)
[Sort the array based on distance from begin. Compute the total number of residents. Compute a prefix sum of number of residents from begin and stop until the prefix sum is larger than half of the total.][Compute total number of residents. QuickSelect the (number of resident,distance from begin) pairs array to repeatedly partition by distance from begin, compute pivot's left resident sum and right resident sum after partition: if left sum is greater than half of total, next search left side and add right sum to the rightmost element of left side; else if right sum is greater than half of total, next search right side and add left sum to the leftmost element on right side; else found.]
}
* Given an integer array and a target threshold. Find all distinct pairs in the array whose sum is smaller equal than the target threshold. (AllPairsWSmallerEqualSum.h)
[QuickSelect repeatedly find the min element in the subarray as the pivot, partition the subarray to move element whose value plus the min element that is <= the target threshold to the left of pivot, others to the right, record elements on the left side, next search the left side, find the min element as pivot and so on, until pivot locates at 0.]
+ Given a very large array of distances of stars to earth. How would you compute the first K stars which are closest to the earth? (FirstKClosestStars.h)
[Keep a maxHeap of K elements with smallest distances and loop through the array.][QuickSelect to find the Kth element and all its smaller elements.]
# (KthSmallestElement.h)
[]
+ Find the k-th smallest element in a sequence of elements where the length of the sequence is unknown. (KthSmallestElementUnknownLength.h)
[Keep a maxHeap of size K.][Keep an array with size 2*K. Whenever the array size is full, run QuickSelect to find Kth smallest element, then resize it to K to keep only the smallest K elements.]
* Given an unsorted array of integers with size of N. Find the maximum possible integer n from the array such that the array consists at least n values greater than or equal to n. (MaxNumWLeastGreaterEqualCount.h)
[Sort the array in ascending order. Iterate from back to find first element whose value is smaller equal to element count from it to back.][QuickSelect to repeatedly move elements whose value greater than v[pivot] to the left side (so that left side count is pivot+1). If pivot+1 >= v[pivot], v[pivot] is a potential answer, record it and next search the left side for bigger numbers. Otherwise, next search the right side for smaller numbers.]
+ Given a non-empty array of integers, return the k most frequent elements. (TopKFrequentElements.h)
[Heap: Use a map<entry,count> to keep track of frequency of each entry. Use a maxHeap<count,entry> to insert all pairs from map. Return the top k pairs from maxHeap.]
[Selection: Use a map<entry,count> to keep track of frequency of each entry. Copy all pairs into an array<count,entry>, then use nth_element to move the (k-1)th count to its correct position after sorted based on count. (k: 1-based, k-1: 0-based) Return the first k pairs from the array.]
}
Sort{
BucketSort{
# (BucketSort.h)
[Range=max-min. AvgBucketRange=Range/N+1. BucketCount=Range/AvgBucketRange+1. Sort each bucket then concatenate.]
# (CountingSort.h)
[]
* (CountingSort2.h)
[]
+ Given an array of citations, compute the h-index. A scientist has index h if h of his/her N papers have at least h citations each, and the other N-h papers have no more than h citations each. What if the citation array is sorted? (HIndex.h)
[Sort the citation array in ascending order. We want to find the max count of papers whose citations are >= paper count: find the first i such that "sortedCitations[i] >= N-i" from left. If not found, return 0.]
[Use a cnt array with size=N+1 where index represents citation number from 0~N to record the number of papers for each citation number. For citation number greater than N: count in at cnt[N]. Accumulate number of papers from highest citation. Find the first i such that "numPapers >= N-i" from left. If not found, return 0.]
[SortedCitationArray: we want to find the first i such that "sortedCitations[i] >= N-i" from left: find the lower bound.]
* Given an unsorted array, find the maximum difference between the successive elements in its sorted form. (MaxGapOfSortedSuccessiveNum.h)
[Use BucketSort to keep track of the min and max of each bucket. Loop through all buckets and keep track of the max gap, which is equal to curNonEmptyBucketMin - prevNonEmptyBucketMax.]
}
IndirectSort{
}
InsertionSort{
+ (InsertionSort.h)
[For each element A[i], insert A[i] into a sorted range [0,i-1] by right shifting all greater elements.]
+ (ShellSort.h)
[For each gap N/=2, for each element A[i], insert A[i] into a sorted range [gap,i-gap] by right shifting all greater elements a gap.]
}
KAway{
+ Given an array A and a positive integer k, rearrange the elements so that no two equal elements are k or less apart. (equal entries should be at least K away from each other) (RearrangeArrWEqualEntriesKAway.h)
[Use a hashMap<entry,count> to record count for each entry. Use a maxHeap<count,entry> to keep a sorted (count,entry) pair list. Fill out the original array starting with the entries that have max count at first available empty position and next k away positions.]
+ (SortNearlySortedArray.h)
}
MergeSort{
}
QuickSort{
}
# Stable sort. (BubbleSort.h)
[]
# (HeapSort.h)
[1. Make the input array a max heap (perform max heapify from middle to begin in a bottom-up manner from prev level of leaves) 2. Repeat popping out the top element from the max heap and insert to the running end, and insert the element from running end to top of the heap then do max heapify in the unsorted range.]
# (SelectionSort.h)
[For each element A[i], find the min element in [i,n-1] and move to current start i, without affecting already sorted elements in the front.]
}
+ Given an array of strings, return all groups of strings that are anagrams. (Anagrams.h)
[Use a hash table with (sortedStr,vector of anagrams) pairs.]
- Given an array of strings, sort the array so that all the anagrams are next to each other.
[Sort with a comparator that takes two strings and returns the comparison of sorted copies of the two strings.]
- Determine if any anagram of string T is a substring of string S.
[Construct a hash table with (char,count) pairs of T. Slide a window with S's size on T and user another hash table to keep track of matched (char,count) in the window. Use a variable to keep track of the total matched char count in the window.]
- Determine if two given strings are anagrams.
[Construct 2 hash tables with (char,count) pairs and compare one by one.]
+ Given a list of strings which contains only lowercase alphabets, group all strings that belong to the same shifting sequence. (GroupShiftedStrings)
[Use a hashMap<leftShiftString,vector<entryString>> to group entry strings with same left shifted string format. Compute left shifted string format: compute the distance to shift the first char to 'a', then left shift all chars with the distance, if the result char < 'a', add 26.]
+ Write a function which takes as input the name of the file containing n test scores and outputs the student who has the max average score across his top three tests. If the student has fewer than three test scores, discard that student. Return "no such student" if no student has three or more test scores. (MaxTop3AvgScoreStudent.h)
[]
+ Given n ropes of different lengths, we need to connect these ropes into one rope. The cost to connect two ropes is equal to sum of their lengths. Connect the ropes with minimum cost. (MinCostConnectRopes.h)
[Sort by length and connect prev with cur from begin.][Insert all lengths to a minHeap and connect the top two lengths then insert it back until left one.]
+ Given a sorted array. Remove duplicates in place such that each element appear only once. What if duplicates are allowed at most twice? (RemoveDuplicatesFromSortedArray.h)
[Iterate and keep track of newBegin. Update and advance newBegin when meeting a different element from prev.][Also keep track of the duplcate count when meeting a duplicate.]
+ Given an unsorted array. Find the minimum length subarray such that sorting this subarray makes the whole array sorted. (ShortestUnsortedSubarr.h)
[Find end of ascendings from left. Find end of descendings from right. Find min and max in the subarray between the 2 ends. Move left end to left to cover min. Move right end to right to cover max.]
* Given an array of heights, an array of number of tallers standing in front of that person. Sort the heights array in a way such that each height will have exactly the same number of tallers (greater heights) that appear in front of it. (SortHeightsWFrontTallers.h)
[Sort (height,tallerCount) pairs by height in ascending order. For each pair from begin, insert it to the lower bound of its tallerCount in a BST.]
+ Given a sorted array of integers nums and integer values a, b and c. Apply a function of the form f(x) = ax^2 + bx + c to each element x in the array. The returned array must be in sorted order. (SortTransformedArray.h)
[UseMinHeap: O(nlogn) time. Greedy: O(n) time. a>0: U shape: the 2 ends i, j are from large to small, so use greedy to fill res from back to front. a<0: n shape: the 2 ends i, j are from small to large, so use greedy to fill res from front to back. a==0, linear shape: can be either from small to large or from large to small for the case from i to j, here we combine it into the U shape case.]
*/
/*=====================================================================*/
/*
StackQueue
EvalExpr{
+ Implement a basic calculator to evaluate a simple expression string. The expression string may contain open '(' and closing parentheses ')', the plus '+' or minus sign '-', non-negative integers and empty spaces ' '. (BasicCalculator.h)
- What if '*' and '/' are included?
[Convert the expression to RPN. Then evaluate RPN.]
+ Evaluate a Polish Notation expression. (EvalPolishNotation.h)
[For each token, push it to a stk if it is an operator, otherwise (numR), keep popping (numL, operator) pairs as top and next top tokens and evaluate "numR = numL operator numR", then push numR to stk.]
+ Evalueate a Reverse Polish Notation (RPN) expression. (EvalReversePolishNotation.h)
[For each token, push it to a numStk if it is a num, otherwise (operator), pop out the top two nums from numStk as right and left operands, evaluate "left operator right" and push it back to numStk.]
}
ImplBy{
+ Implement a circular queue using an array. (CircularQueueByArray.h)
[Keep track of the current head, tail, and element count in the array. When the capacity is full, left rotate the range "from begin to head" to the end of array (to make head at begin) and resize. Otherwise, just advance tail or head circularly for enqueue or dequeue.]
+ Implement K stacks with size S using an array. (MultiStacksByAnArray.h)
[Use both a curMaxSize and a minHeap<idx> to keep track of next available space index. Keep an array of each stack's top element's index in buffer. Use a buffer array<prevIdx,val>, where prevIdx is to keep track of top element's next element index, and val is a top element of a particular stack.]
+ Implement a queue using 2 stacks. (QueueBy2Stacks.h)
[Keep a reversed stack to push new elements. When popping, return the top element of a non-reversed stack if it is non-empty, otherwise, move all elements from reversed stack to non-reversed stack and return the top of the non-reversed stack.]
+ Implement a queue using a heap. (QueueByHeap.h)
[Use a maxHeap<order,val> where order is decremented when pushing a new element.]
+ Implement a stack using a list of small stacks with fixed capacity. (SetOfStacks.h)
+ Implement a stack using 2 queues. (StackBy2Queues.h)
[Keep a reversed queue to push new elements. When popping, move all elements in reversed queue from front to prev back to a tmp queue, then return the back and swap tmp with reversed queue.]
+ Implement a stack using a heap. (StackByHeap.h)
[Use a maxHeap<order,val> where order is incremented when pushing a new element.]
}
WithMin{
+ Implement a queue with GetMin method. (QueueWithMin.h)
[Use a regular queue and keep a sortedQue<minVal,count> that is sorted in ascending order from front to back.]
+ Implement a stack with GetMin method. (StackWithMin.h)
[Use a regular stack and keep a sortedStk<minVal,count> that is sorted in ascending order from top to bottom.]
}
+ Given a stream of integers and a window size, calculate the moving average of all integers in the sliding window. (MovingAvgFromDataStream.h)
[Keep a queue with the specified window size, a sum of all integers in the queue. When taking a new val, remove the oldest integer from queue and subtrack it from sum if queue's size is full, then enqueue the new val and add to sum, return sum / queue.size().]
+ Remove the minimum number of invalid parentheses in order to make the input string valid. Return all possible results. (RemoveInvalidParentheses.h)
[BFS: each time we remove a parenthese, the string becomes a new state. Use a queue<string> and keep track of visited strings. Enumerate all possible next states by removing each parenthese, skip visited states and put next states in queue. One we found the first valid string, it must be the valid string with removing least parentheses, stop BFS down at that level.]
+ Given an absolute path for a file (Unix-style), simplify/normalize it. (SimplifyPath.h)
[]
+ Sort a stack in ascending order from bottom to top. (SortStack.h)
[]
+ Implement Tower of Hanoi. (TowerOfHanoi.h)
[]
+ Given a string containing just the characters '(', ')', '{', '}', '[' and ']', determine if the input string is valid. (ValidParentheses.h)
[]
*/
/*=====================================================================*/
/*
TextLines
+ (NeatPrintWordWrap.h)
[]
+ (NeatPrintWordWrap2.h)
[]
+ (ReadNCharsGivenRead4.h)
[]
+ (TextJustification.h)
[]
+ (UnixTailCommand.h)
[]
*/
/*=====================================================================*/
/*
ThreadSafe
+ (ImplementAsyncCallback.h)
[]
+ (RealTimeCountHitsInLastSecMinHr.h)
[]
+ (Semaphore.h)
[]
+ (Sync2InterleavingThreads.h)
[]
+ (SyncCigaretteSmokers.h)
[]
+ (SyncDiningPhilosophers.h)
[]
+ (SyncProducersConsumers.h)
[]
+ (SyncReadersWriters.h)
[]
+ (ThreadMgr.h)
[]
+ (ThreadPool.h)
[]
+ (ThreadSafeQueue.h)
[]
+ (ThreadTimer.h)
[]
*/
/*=====================================================================*/
/*
TrieSuffixTreeArray
+ (FirstUniqueURL.h)
[]
+ (Rope.h)
[]
+ (SuffixArray.h)
[]
+ (TrieST.h)
[]
+ (TST.h)
[]
*/
/*=====================================================================*/

#endif
