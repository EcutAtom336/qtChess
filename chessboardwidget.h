#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include "chessboard.h"
#include <QPainter>
#include <QWidget>
#include <QtSvgWidgets/QtSvgWidgets>
#include <memory>
#include <qcontainerfwd.h>
#include <qimage.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtypes.h>

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

    void init(const enum mode mode) override;
    void clear() override;

    void setBoardStyle(chessboardWidget::boardStyle style);
    void setPieceStyle(chessboardWidget::chessStyle style);
    void setRollback(const bool new_state);

    void addChess(const coordinate &coor, const enum chess::type t) override;
    void addChess(const quint8 row, const quint8 col, const enum chess::type type) override;

    void removeChess(const coordinate &coor) override;
    void removeChess(const quint8 row, const quint8 col) override;

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

    chessboard::coordinate mouse_press_coordinate = chessboard::coordinate(1, 1);
    bool selected = false;
    chessboard::coordinate selected_coor = chessboard::coordinate(1, 1);
    QList<chessboard::coordinate> dest_list = QList<chessboard::coordinate>();

    void reloadPieceSvg(QString path);
    void renderPieceImg();

    chessboard::coordinate getCoordinate(const QPoint pos);
    QRectF getCellRectF(chessboard::coordinate coor);

  protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // CHESSBOARDWIDGET_H
