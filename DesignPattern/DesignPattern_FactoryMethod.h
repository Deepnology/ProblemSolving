#ifndef _DESIGN_PATTERN_FACTORY_METHOD_H
#define _DESIGN_PATTERN_FACTORY_METHOD_H
#include "Debug.h"
namespace DesignPattern_FactoryMethod
{
    enum PieceEnum
    {
        pawn = 0,
        knight = 1,
        bishop = 2,
        rook = 3,
        queen = 4,
        king = 5,
    };
    class Piece
    {
    public:
        Piece(){}
        virtual ~Piece() = 0;
        virtual bool IsValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<Piece*>> & board) = 0;
        static Piece * NewPiece(PieceEnum p);
    };
    Piece::~Piece() {}
    class Pawn : public Piece
    {
    public:
        Pawn(){}
        ~Pawn(){}
        bool IsValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<Piece*>> & board)
        {
            return true;
        }
    };
    class Knight : public Piece
    {
    public:
        Knight(){}
        ~Knight(){}
        bool IsValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<Piece*>> & board)
        {
            return true;
        }
    };
    class Bishop : public Piece
    {
    public:
        Bishop(){}
        ~Bishop(){}
        bool IsValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<Piece*>> & board)
        {
            return true;
        }
    };
    class Rook : public Piece
    {
    public:
        Rook(){}
        ~Rook(){}
        bool IsValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<Piece*>> & board)
        {
            return true;
        }
    };
    class Queen : public Piece
    {
    public:
        Queen(){}
        ~Queen(){}
        bool IsValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<Piece*>> & board)
        {
            return true;
        }
    };
    class King : public Piece
    {
    public:
        King(){}
        ~King(){}
        bool IsValidMove(int fromX, int fromY, int toX, int toY, const std::vector<std::vector<Piece*>> & board)
        {
            return true;
        }
    };
    Piece* Piece::NewPiece(PieceEnum p)
    {
        switch (p)
        {
            case pawn: return new Pawn;
            case knight: return new Knight;
            case bishop: return new Bishop;
            case rook: return new Rook;
            case queen: return new Queen;
            case king: return new King;
            default: return new Pawn;
        }
    }

    void Test()
    {
        std::vector<std::vector<Piece*>> board(8, std::vector<Piece*>(8, NULL));

        board[0][0] = Piece::NewPiece(rook);
        board[0][1] = Piece::NewPiece(knight);
        board[0][2] = Piece::NewPiece(bishop);
        board[0][3] = Piece::NewPiece(queen);
        board[0][4] = Piece::NewPiece(king);
        board[0][5] = Piece::NewPiece(bishop);
        board[0][6] = Piece::NewPiece(knight);
        board[0][7] = Piece::NewPiece(rook);
        for (int i = 0; i < 8; ++i) board[1][i] = Piece::NewPiece(pawn);

        board[7][0] = Piece::NewPiece(rook);
        board[7][1] = Piece::NewPiece(knight);
        board[7][2] = Piece::NewPiece(bishop);
        board[7][3] = Piece::NewPiece(queen);
        board[7][4] = Piece::NewPiece(king);
        board[7][5] = Piece::NewPiece(bishop);
        board[7][6] = Piece::NewPiece(knight);
        board[7][7] = Piece::NewPiece(rook);
        for (int i = 0; i < 8; ++i) board[6][i] = Piece::NewPiece(pawn);

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < 8; ++j)
                if (board[i][j])
                    delete board[i][j];
    }
}
/*

 */
#endif
