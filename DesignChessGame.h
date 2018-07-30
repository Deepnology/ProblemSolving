#ifndef _DESIGN_CHESS_GAME_H
#define _DESIGN_CHESS_GAME_H
#include "Debug.h"
/*

 */
namespace DesignChessGame
{
    enum PieceType
    {
        PawnType, KnightType, BishopType, RookType, QueenType, KingType
    };
    enum PieceColor
    {
        White, Black
    };
    class Player
    {
    public:
        Player(){}
    };
    class PieceBase
    {
        enum PieceType m_type;
        Player * m_player;
    public:
        PieceBase(PieceType t, Player * p):m_type(t),m_player(p){}
        PieceType GetType() const {return m_type;}
        Player * GetPlayer() const {return m_player;}
        virtual bool IsValidMove(int srcX, int srcY, int dstX, int dstY, const std::vector<std::vector<PieceBase *>> & board) = 0;
    };
    class Pawn : public PieceBase
    {
    public:
        Pawn(Player * p):PieceBase(PawnType, p){}
        bool IsValidMove(int srcX, int srcY, int dxtX, int dxtY, const std::vector<std::vector<PieceBase *>> & board)
        {

        }
    };
    class Knight : public PieceBase
    {
    public:
        Knight(Player * p):PieceBase(KnightType, p){}
        bool IsValidMove(int srcX, int srcY, int dxtX, int dxtY, const std::vector<std::vector<PieceBase *>> & board)
        {

        }
    };
    class Bishop : public PieceBase
    {
    public:
        Bishop(Player * p):PieceBase(BishopType, p){}
        bool IsValidMove(int srcX, int srcY, int dxtX, int dxtY, const std::vector<std::vector<PieceBase *>> & board)
        {

        }
    };
    class Rook : public PieceBase
    {
    public:
        Rook(Player * p):PieceBase(RookType, p){}
        bool IsValidMove(int srcX, int srcY, int dxtX, int dxtY, const std::vector<std::vector<PieceBase *>> & board)
        {

        }
    };
    class Queen : public PieceBase
    {
    public:
        Queen(Player * p):PieceBase(QueenType, p){}
        bool IsValidMove(int srcX, int srcY, int dxtX, int dxtY, const std::vector<std::vector<PieceBase *>> & board)
        {

        }
    };
    class King : public PieceBase
    {
    public:
        King(Player * p):PieceBase(KingType, p){}
        bool IsValidMove(int srcX, int srcY, int dxtX, int dxtY, const std::vector<std::vector<PieceBase *>> & board)
        {

        }
    };
    enum Status
    {
        InvalidMove,
        ValidMove,
        WhiteWin,
        BlackWin
    };
    class ChessGame
    {
        std::vector<Player*> m_players;
        int m_curPlayer;
        std::vector<std::vector<PieceBase *>> m_board;
        std::unordered_set<PieceBase *> m_killed;
    public:
        ChessGame(Player * white, Player * black):m_players({white,black}),m_curPlayer(0),m_board(8,std::vector<PieceBase *>(8,NULL)),m_killed()
        {
            m_board[0][0] = new Rook(white);
            m_board[0][1] = new Knight(white);
            m_board[0][2] = new Bishop(white);
            m_board[0][3] = new Queen(white);
            m_board[0][4] = new King(white);
            m_board[0][5] = new Bishop(white);
            m_board[0][6] = new Knight(white);
            m_board[0][7] = new Rook(white);
            for (int i = 0; i < 8; ++i) m_board[1][i] = new Pawn(white);

            m_board[7][0] = new Rook(black);
            m_board[7][1] = new Knight(black);
            m_board[7][2] = new Bishop(black);
            m_board[7][3] = new Queen(black);
            m_board[7][4] = new King(black);
            m_board[7][5] = new Bishop(black);
            m_board[7][6] = new Knight(black);
            m_board[7][7] = new Rook(black);
            for (int i = 0; i < 8; ++i) m_board[6][i] = new Pawn(black);
        }
        
        Status Move(int srcX, int srcY, int dstX, int dstY, Player * p)
        {
            if (m_players[m_curPlayer] != p) return InvalidMove;
            PieceBase * curPiece = m_board[srcX][srcY];
            if (curPiece == NULL) return InvalidMove;
            if (curPiece->GetPlayer() != p) return InvalidMove;
            if (!curPiece->IsValidMove(srcX, srcY, dstX, dstY, m_board)) return InvalidMove;
            m_board[srcX][srcY] = NULL;
            PieceBase * tgtPiece = m_board[dstX][dxtY];
            m_board[dstX][dstY] = curPiece;
            m_killed.insert(tgtPiece);
            if (tgtPiece->GetType() == KingType) return m_curPlayer == 0 ? WhiteWin : BlackWin;
            m_curPlayer ^= 1;
            return ValidMove;
        }

    };

};
#endif
