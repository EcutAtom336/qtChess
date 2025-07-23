#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include "chessboard.h"
#include <QPainter>
#include <QWidget>
#include <QtSvgWidgets/QtSvgWidgets>
#include <memory>
#include <qcontainerfwd.h>
#include <qimage.h>

class chessboardWidget : public QWidget, private chessboard
{
  public:
    enum class boardStyle
    {
        BLUE = 0,
        BLUE2,
        BLUE3,
        BLUE_MARBLLE,
        BROWN,
        CANVAS2,
        GREEN,
        GREEN_PLASTIC,
        GREY,
        HORSEY,
        IC,
        LEATHER,
        MAPLE,
        MAPLE2,
        MARBLE,
        METAL,
        OLIVE,
        PINK_PYRAMID,
        PURPLE,
        PURPLE_DIAG,
        WOOD,
        WOOD2,
        WOOD3,
        WOOD4,
        COUNT,
    };

    enum class chessStyle
    {
        ALPHA = 0,
        ANARCANDY,
        CALIENTE,
        CALIFORNIA,
        CARDINAL,
        CBURNETT,
        CELTIC,
        CHESS7,
        CHESSNUT,
        COMPANION,
        COOKE,
        DUBROVNY,
        FANTASY,
        FIRI,
        FRESCA,
        GIOCO,
        GOVERNOR,
        HORSEY,
        ICPIECES,
        KIWEN_SUWI,
        KOSAL,
        LEIPZIG,
        LETTER,
        MAESTRO,
        MERIDA,
        MONARCHY,
        MPCHESS,
        PIROUETTI,
        PIXEL,
        REILLYCRAIG,
        RHOSGFX,
        RIOHACHA,
        SHAPES,
        SPATIAL,
        STAUNTY,
        TATIANA,
        XKCDM,
        COUNT,
    };

    chessboardWidget(QWidget *parent = nullptr, boardStyle board_style = boardStyle::BLUE,
                     chessStyle chess_style = chessStyle::ALPHA);

    void setBoardStyle(chessboardWidget::boardStyle style);
    void setPieceStyle(chessboardWidget::chessStyle style);
    void clear() override;
    bool addChess(enum chessboard::cell cell, enum chess::type type) override;
    bool removeChess(enum cell cell) override;
    void init(enum mode mode) override;
    void setRollback(bool new_state);

  private:
    // 棋盘样式相关
    static const std::array<QString, static_cast<size_t>(boardStyle::COUNT)> BOARD_STYLE_FILE_NAMES;

    QImage board_img = QImage();

    // 棋子样式相关
    static const std::array<QString, static_cast<size_t>(chessStyle::COUNT)> PIECE_STYLE_FLODER_NAMES;
    // 棋子svg图像，用于生成棋子image
    std::array<QSvgRenderer, 12> piece_svg_array;
    // 棋子image，用于绘制
    std::array<std::unique_ptr<QImage>, 12> piece_img_array;

    // 棋盘显示相关
    bool rollback = true;

    void reloadPieceSvg(QString path);
    void renderPieceImg();

  protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
};

#endif // CHESSBOARDWIDGET_H
