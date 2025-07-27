#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QPainter>
#include <QWidget>
#include <QtSvgWidgets/QtSvgWidgets>

#include <qcontainerfwd.h>
#include <qimage.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qsize.h>
#include <qtypes.h>

#include "chessboard.h"

namespace qtchess
{

class ChessboardWidget : public QWidget, private Chessboard
{
  public:
    enum class BoardStyle
    {
        kBlue = 0,
        kBlue2,
        kBlue3,
        kBlueMarblle,
        kBrown,
        kCanvas2,
        kGreen,
        kGreenPlastic,
        kGrey,
        kHorsey,
        kIc,
        kLeather,
        kMaple,
        kMaple2,
        kMarble,
        kMetal,
        kOlive,
        kPinkPyramid,
        kPurple,
        kPurpleDiag,
        kWood,
        kWood2,
        kWood3,
        kWood4,
        kCount,
    };

    enum class ChessStyle
    {
        kAlpha = 0,
        kAnarcandy,
        kCaliente,
        kCalifornia,
        kCardinal,
        kCburnett,
        kCeltic,
        kChess7,
        kChessnut,
        kCompanion,
        kCooke,
        kDubrovny,
        kFantasy,
        kFiri,
        kFresca,
        kGioco,
        kGovernor,
        kHorsey,
        kIcpieces,
        kKiwenSuwi,
        kKosal,
        kLeipzig,
        kLetter,
        kMaestro,
        kMerida,
        kMonarchy,
        kMpchess,
        kPirouetti,
        kPixel,
        kReillycraig,
        kRhosgfx,
        kRiohacha,
        kShapes,
        kSpatial,
        kStaunty,
        kTatiana,
        kXkcdm,
        kCount,
    };

    enum class Direction
    {
        kForward,
        kBackword,
    };

    ChessboardWidget(QWidget *parent = nullptr, BoardStyle board_style = BoardStyle::kBlue,
                     ChessStyle chess_style = ChessStyle::kAlpha);

    void init(const enum Mode mode) override;
    void clear() override;

    void setBoardStyle(ChessboardWidget::BoardStyle style);
    void setPieceStyle(ChessboardWidget::ChessStyle style);
    void setDirection(Direction direction);

    void addChess(const Coordinate &coor, const enum Chess::Type t) override;
    void addChess(const quint8 row, const quint8 col, const enum Chess::Type type) override;

    void removeChess(const Coordinate &coor) override;
    void removeChess(const quint8 row, const quint8 col) override;

  protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

  private:
    // 棋盘样式文件名
    static const std::array<QString, static_cast<size_t>(BoardStyle::kCount)> kBoardStyleFileNames;

    // 棋子样式文件夹名
    static const std::array<QString, static_cast<size_t>(ChessStyle::kCount)> kPieceStyleFloderNames;

    // 棋盘image
    QImage board_img_ = QImage();

    // 棋子svg图像，用于生成棋子image
    std::array<QSvgRenderer, 12> piece_svgs_;

    // 棋子image，用于绘制
    std::array<std::unique_ptr<QImage>, 12> piece_imgs_;

    // 棋盘视角
    Direction direction_ = ChessboardWidget::Direction::kForward;

    // 处理鼠标点击事件相关
    Chessboard::Coordinate mouse_press_coordinate_ = Chessboard::Coordinate(1, 1);
    bool selected_ = false;
    Chessboard::Coordinate selected_coordinate_ = Chessboard::Coordinate(1, 1);
    QList<Chessboard::Coordinate> reachable_coordinates_ = QList<Chessboard::Coordinate>();

    void reloadPieceSvg(QString path);
    void renderPieceImg();
    Chessboard::Coordinate getCoordinate(const QPoint pos);
    QRectF getCellRectF(Chessboard::Coordinate coor);
};

} // namespace qtchess

#endif // CHESSBOARDWIDGET_H
