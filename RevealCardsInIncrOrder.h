#ifndef _REVEAL_CARDS_IN_INCR_ORDER_H
#define _REVEAL_CARDS_IN_INCR_ORDER_H
#include "Debug.h"
/*
Leetcode: Reveal Cards In Increasing Order
In a deck of cards, every card has a unique integer.  You can order the deck in any order you want.
Initially, all the cards start face down (unrevealed) in one deck.
Now, you do the following steps repeatedly, until all cards are revealed:
Take the top card of the deck, reveal it, and take it out of the deck.
If there are still cards in the deck, put the next top card of the deck at the bottom of the deck.
If there are still unrevealed cards, go back to step 1.  Otherwise, stop.
Return an ordering of the deck that would reveal the cards in increasing order.
The first entry in the answer is considered to be the top of the deck.
Example 1:
Input: [17,13,11,2,3,5,7]
Output: [2,13,3,11,5,17,7]
Explanation:
We get the deck in the order [17,13,11,2,3,5,7] (this order doesn't matter), and reorder it.
After reordering, the deck starts as [2,13,3,11,5,17,7], where 2 is the top of the deck.
We reveal 2, and move 13 to the bottom.  The deck is now [3,11,5,17,7,13].
We reveal 3, and move 11 to the bottom.  The deck is now [5,17,7,13,11].
We reveal 5, and move 17 to the bottom.  The deck is now [7,13,11,17].
We reveal 7, and move 13 to the bottom.  The deck is now [11,17,13].
We reveal 11, and move 17 to the bottom.  The deck is now [13,17].
We reveal 13, and move 17 to the bottom.  The deck is now [17].
We reveal 17.
Since all the cards revealed are in increasing order, the answer is correct.
 */
class RevealCardsInIncrOrder
{
public:
    RevealCardsInIncrOrder(){}
    ~RevealCardsInIncrOrder(){}

    //reorder the deck such that when popping front will result in incr numbers
    //after popping front, need to move next front to back of deck
    std::vector<int> ReverseProcessUseQueue(std::vector<int> && deck)
    {
        std::sort(deck.begin(), deck.end(), std::greater<int>());//in decr order
        int N = deck.size();
        std::deque<int> que;
        //reverse engineering:
        que.push_front(deck[0]);
        for (int i = 1; i < N; ++i)
        {
            //1. move back to front
            que.push_front(que.back());
            que.pop_back();
            //2. push front
            que.push_front(deck[i]);
        }
        std::vector<int> res(que.begin(), que.end());

        std::cout << "RevealCardsInIncrOrder ReverseProcessUseQueue for [" << Debug::ToStr1D<int>()(deck) << "]: " << Debug::ToStr1D<int>()(res) << std::endl;
        return res;
    }
};
/*
RevealCardsInIncrOrder ReverseProcessUseQueue for [17, 13, 11, 7, 5, 3, 2]: 2, 13, 3, 11, 5, 17, 7
 */
#endif
