#ifndef DESIGN_DECK_OF_CARDS_H
#define DESIGN_DECK_OF_CARDS_H
#include "Debug.h"
/*

*/
namespace DesignDeckOfCards
{
	enum Suit
	{
		SPADES = 0,
		CLUBS = 1,
		HEARTS = 2,
		DIAMONDS = 3
	};
	enum Face
	{
		ACE = 0,
		TWO = 1,
		THREE = 2,
		FOUR = 3,
		FIVE = 4,
		SIX = 5,
		SEVEN = 6,
		EIGHT = 7,
		NINE = 8,
		TEN = 9,
		JACK = 10,
		QUEEN = 11,
		KING = 12
	};
	Suit GetSuit(int card)
	{
		return static_cast<Suit>(card / 13);
	}
	Face GetFace(int card)
	{
		return static_cast<Face>(card % 13);
	}

	class Player 
	{
		std::unordered_set<int> m_cards;
	public:
		Player() {}
		void TakeCard(int card)
		{
			m_cards.insert(card);
		}

	};
	class Deck
	{
		std::vector<Player*> m_cardToPlayer;//Suit*13+Face (Suit=idx/13, Face=idx%13)
		std::unordered_map<Player*, std::unordered_set<int>> m_playerToCards;//Suit*13+Face
		std::vector<int> m_cards;//52 cards with values Suit*13+Face
		int m_count;//num of cards in deck
	public:
		Deck() : m_cardToPlayer(52, NULL), m_playerToCards(), m_cards(), m_count(52) 
		{
			for (int i = 0; i < 4; ++i)
				for (int j = 0; j < 13; ++j)
					m_cards.push_back(i * 13 + j);
		}
		void Shuffle()
		{
			for (int i = 0; i < m_count; ++i)//offline sampling
			{
				int j = rand() % (m_count - i) + i;
				std::swap(m_cards[i], m_cards[j]);
			}
		}
		bool Deal(Player * p)
		{
			if (m_count == 0 || p == NULL) return false;
			int card = m_cards[m_count - 1];
			--m_count;
			m_cardToPlayer[card] = p;
			m_playerToCards[p].insert(card);
			p->TakeCard(card);
			return true;
		}
		bool Receive(Player * p, int card)
		{
			if (m_count == 52 || p == NULL) return false;
			m_cardToPlayer[card] = NULL;
			m_playerToCards[p].erase(card);
			if (m_playerToCards[p].empty())
				m_playerToCards.erase(p);
			m_cards[m_count - 1] = card;
			++m_count;
			return true;
		}
	};
}
#endif
