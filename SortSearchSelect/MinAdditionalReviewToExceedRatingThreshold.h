#ifndef _MIN_ADDITIONAL_REVIEW_TO_EXCEED_RATING_THRESHOLD_H
#define _MIN_ADDITIONAL_REVIEW_TO_EXCEED_RATING_THRESHOLD_H
#include "Debug.h"
/*
Amazon OA
Given the number of five-star and total reviews for each product a company sells, as well as the threshold percentage, what is the minimum number of additional five-star reviews the company needs to become five star seller.
For ex, there are 3 products (n=3) with productRatings =[[4,4],[1,2],[3,6]], percentage rating threshold = 77.
[1,2] indicates => [1 (five star reviews) ,2 (total reviews)].
We need to get the seller reach the threshold with minimum number of additional five star reviews.
Before we add more five star reviews, the percentage for this seller is ((4/4) + (1/2) + (3/6))/3 = 66.66%
If we add a five star review to 2nd product, ((4/4) + (2/3) + (3/6))/3 = 72.22%
If we add another five star review to 2nd product, ((4/4) + (3/4) + (3/6))/3 = 75%
If we add a five star review to 3rd product, ((4/4) + (3/4) + (4/7))/3 = 77.38%
At this point, 77% (threshold) is met. Therefore, answer is 3 (because that is the minimum five star reviews we need to add, to get the seller reach the threshold).
public static int fiveStarReviews(List<List<Integer>> productRatings, int ratingsThreshold){
}
Constraints:
1<= productRatings.size() <=200
In product ratings, [fivestar, total], fivestar <=100, total<=100
1<=ratingsThreshold< 100
productRatings contains only non negative integers.
 */
class MinAdditionalReviewToExceedRatingThreshold
{
    struct Less
    {
        bool operator()(const std::vector<int> & a, const std::vector<int> & b) const
        {
            int diff1 = diff(a);
            int diff2 = diff(b);
            return diff1 < diff2;
        }
        double diff(const std::vector<int> & a) const
        {
            double curRating = 100.0 * (double)a[0] / (double)a[1];
            double nxtRating = 100.0 * (double)(a[0]+1) / (double)(a[1]+1);
            return (nxtRating - curRating);
        }
    };
public:
    int UseMaxHeap(const std::vector<std::vector<int>> & ratings, int threshold)//ratings: <numOf5StarReview,numOfTotalReview>
    {
        int N = ratings.size();
        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, Less> maxHeap;
        for (auto & v : ratings)
            maxHeap.push(v);

        double curRatingSum = 0;
        for (auto & v : ratings)
            curRatingSum += 100.0 * (double)v[0] / (double)v[1];

        int res = 0;
        while (curRatingSum < (double)threshold*N)
        {
            auto v = maxHeap.top();
            maxHeap.pop();
            curRatingSum += 100.0 * (double)(v[0]+1) / (double)(v[1]+1) - 100.0 * (double)v[0]/(double)v[1];
            maxHeap.push({v[0]+1,v[1]+1});
            ++res;
        }

        std::cout << "MinAdditionalReviewToExceedRatingThreshold for ratings=[" << Debug::ToStr1D<int>()(ratings) << "], threshold=" << threshold << ": " << res << std::endl;
        return res;
    }
};
/*
MinAdditionalReviewToExceedRatingThreshold for ratings=[[4,4], [1,2], [3,6]], threshold=77: 3
 */
#endif
