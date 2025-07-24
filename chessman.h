#ifndef CHESSMAN_H
#define CHESSMAN_H

class Chessman
{
  public:
    typedef enum
    {
        EMPTY,

        WHITE_KING,   // 白王
        WHITE_QUEEN,  // 白后
        WHITE_ROOK,   // 白车
        WHITE_BISHOP, // 白象
        WHITE_KNIGHT, // 白马
        WHITE_PAWN,   // 白兵

        BLACK_KING,   // 黑王
        BLACK_QUEEN,  // 黑后
        BLACK_ROOK,   // 黑车
        BLACK_BISHOP, // 黑象
        BLACK_KNIGHT, // 黑马
        BLACK_PAWN,   // 黑兵

    } chessType_t; // 棋子类型

    Chessman(chessType_t type);

    chessType_t getChess_type() const;

  private:
    chessType_t chess_type;
};

#endif // CHESSMAN_H
