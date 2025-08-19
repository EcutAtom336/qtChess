#ifndef CHESSBOARDWIDGET_H
#define CHESSBOARDWIDGET_H

#include <QPainter>
#include <QWidget>
#include <QtSvgWidgets/QtSvgWidgets>

#include <qcontainerfwd.h>
#include <qdir.h>
#include <qhash.h>
#include <qhashfunctions.h>
#include <qimage.h>
#include <qlist.h>
#include <qpainter.h>
#include <qpoint.h>
#include <qsharedpointer.h>
#include <qsize.h>
#include <qsvgrenderer.h>
#include <qtypes.h>

#include "chess.h"
#include "chessboard.h"
#include "coordinate.h"

namespace qtchess
{

class ChessboardWidget : public QWidget
{
  public:
    enum class Direction
    {
        kForward,
        kBackword,
    };

    ChessboardWidget(QWidget *parent = nullptr, const QString &board_style_name = QString(),
                     const QString &chess_style_name = QString());

    void init(const Chessboard::Mode mode);
    void clear();

    void setBoardStyle(const QString style_name);
    void setPieceStyle(const QString style_name);
    void setDirection(Direction direction);

    static QStringList getBoardStyleNames();
    static QStringList getPieceStyleNames();

    static QImage getBoardStylePreviewImage(const QString &style_name);
    static QImage getPieceStylePreviewImage(const QString &style_name, quint32 size);

    void addChess(const Coordinate &coor, const Chess::Side side, const Chess::Type t);
    void addChess(const quint8 row, const quint8 col, const Chess::Side side, const Chess::Type type);

    void removeChess(const Coordinate &coor);
    void removeChess(const quint8 row, const quint8 col);

  protected:
    void paintEvent(QPaintEvent *) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void showEvent(QShowEvent *event) override;

  private:
    // 棋盘image
    QImage board_img_ = QImage();

    // 棋子svg图像，用于生成棋子image
    QHash<QString, QSharedPointer<QSvgRenderer>> piece_svgs_;

    // 棋子image，用于绘制
    QHash<QString, QImage> piece_imgs_;

    // 棋盘视角
    Direction direction_ = ChessboardWidget::Direction::kForward;

    Chessboard chessboard_;

    // 处理鼠标点击事件相关
    Coordinate mouse_press_coordinate_;
    Coordinate selected_coordinate_;
    Coordinates reachable_coordinates_;

    void renderPieceImg();
    Coordinate getCoordinate(const QPoint pos);
    QRectF getCellRectF(Coordinate coor);
};

} // namespace qtchess

#endif // CHESSBOARDWIDGET_H
