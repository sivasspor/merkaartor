
#include "MapView.h"
#include "Document.h"

#include <QtGui/QPainter>
#include <QtGui/QDockWidget>
#include <QtGui/QMouseEvent>
#include <QtGui/QShortcut>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>


#define WARNING(title, message) { \
    if (QMessageBox::warning(this, title, message.arg(file), \
     QMessageBox::Ignore | QMessageBox::Cancel, QMessageBox::Ignore) == QMessageBox::Ignore) \
        continue; \
    else { \
        theView->invalidate(true, true, false); \
        return; \
    } \
}

#define QUESTION(title, message, always) { \
    if (always == 0) { \
        int replyButton = QMessageBox::question(this, title, message, \
         QMessageBox::Yes | QMessageBox::YesToAll | QMessageBox::No | QMessageBox::NoToAll | QMessageBox::Abort, QMessageBox::Yes ); \
        if (replyButton == QMessageBox::No) \
            continue; \
        else if (replyButton == QMessageBox::Abort) { \
            theView->invalidate(true, true, false); \
            return; \
        } \
        else if (replyButton != QMessageBox::Yes) \
            always = replyButton; \
    } \
    if (always == QMessageBox::NoToAll) \
        continue; \
}

class ImageView;

class GeoImageDock : public MDockAncestor
{
    Q_OBJECT

public:
    GeoImageDock();
    ~GeoImageDock(void);

    void clear();
    void loadImage(QString fileName, Coord pos);
    void loadImages(QStringList fileNames);
    void setImage(Node *Pt);
    void setImage(int ImageId);

    static void addGeoDataToImage(Coord pos, const QString & file);
    static Coord getGeoDataFromImage(const QString & file);

private slots:
    void removeImages(void);
    void toClipboard(void);
    void selectNext(void);
    void selectPrevious(void);
    void centerMap(void);
    void saveImage(void);

private:

    QAction *centerAction;
    QAction *remImagesAction;
    QAction *toClipboardAction;
    QAction *nextImageAction;
    QAction *previousImageAction;
    QAction *saveImageAction;


    QStringList Images;
    int curImage, lastImage;
    bool updateByMe;
    QPointer<TrackLayer> photoLayer;

    ImageView *Image;

    struct NodeData {
        NodeData(Node* mNode, const QString & mFilename, const QDateTime & mTimestamp, bool mInserted)
         : node(mNode), filename(mFilename), inserted(mInserted), timestamp(mTimestamp) { }
        bool operator<(const NodeData & other) const { return timestamp < other.timestamp; }
        Node* node;
        QString filename;
        bool inserted;
        QDateTime timestamp;
    };
    QList<NodeData> usedTrackPoints;

    void addUsedTrackpoint(NodeData data);
    bool getWalkingPapersDetails(const QUrl& reqUrl, double &lat, double &lon, bool& positionValid) const;
    bool askAndgetWalkingPapersDetails(double &lat, double &lon, bool& positionValid) const;

public:
    void changeEvent(QEvent*);
    void retranslateUi();
};

class ImageView : public QWidget
{
public:
    ImageView(QWidget *parent);
    ~ImageView();

    void setImage(QString filename, bool movable=true);
    void setMovable(bool movable=true);

protected:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void resizeEvent(QResizeEvent *e);

private:
    bool Movable;
    QImage image;
    QString name;
    QPoint mousePos;
    QRect rect;
    QRectF area;

    double zoomLevel; // zoom in percent

    void zoom(double levelStep); // zoom levelStep steps

};
