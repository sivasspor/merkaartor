/***************************************************************************
 *   Copyright (C) 2007 by Kai Winter   *
 *   kaiwinter@gmx.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef TILEMAPADAPTER_H
#define TILEMAPADAPTER_H

#include "mapadapter.h"
#include "TmsServersList.h"

//! MapAdapter for servers with image tiles
/*!
 * Use this derived MapAdapter to display maps from OpenStreetMap
 *	@author Kai Winter <kaiwinter@gmx.de>
*/
class TileMapAdapter : public MapAdapter
{
public:
    //! constructor
    /*!
     * Sample of a correct initialization of a MapAdapter:<br/>
     * TileMapAdapter* ta = new TileMapAdapter("192.168.8.1", "/img/img_cache.php/%1/%2/%3.png", 256, 0,17);<br/>
     * The placeholders %1, %2, %3 stands for x, y, z<br/>
     * The minZoom is 0 (means the whole world is visible). The maxZoom is 17 (means it is zoomed in to the max)
     * @param host The servers URL
     * @param serverPath The path to the tiles with placeholders
     * @param tilesize the size of the tiles
     * @param minZoom the minimum zoom level
     * @param maxZoom the maximum zoom level
     */
    TileMapAdapter(const TmsServer& ts);

    virtual ~TileMapAdapter();

    //! returns the unique identifier (Uuid) of this MapAdapter
    /*!
     * @return  the unique identifier (Uuid) of this MapAdapter
     */
    virtual QUuid	getId		() const;

    //! returns the type of this MapAdapter
    /*!
     * @return  the type of this MapAdapter
     */
    virtual IMapAdapter::Type	getType		() const;

    //! returns the size of the tiles
    /*!
     * @return the size of the tiles
     */
    virtual int		getTileSizeW	() const;
    virtual int		getTileSizeH	() const;

    //! returns the source tag to be applied when drawing over this map
    /*!
     * @return the source tag
     */
    virtual QString	getSourceTag() const;
    virtual void setSourceTag (const QString& ) {};

    //! returns the Url of the usage license
    /*!
     * @return the Url of the usage license
     */
    virtual QString	getLicenseUrl() const;

    virtual void zoom_in();
    virtual void zoom_out();

    virtual bool isValid(int x, int y, int z) const;
    virtual QString getQuery(int x, int y, int z) const;
    virtual QString getQuery(const QRectF& , const QRectF& , const QRect& ) const { return ""; }
    virtual QPixmap getPixmap(const QRectF& /* wgs84Bbox */, const QRectF& /* projBbox */, const QRect& /* size */) const { return QPixmap(); }

    virtual QRectF	getBoundingbox() const;

    virtual bool isTiled() const { return true; }
    virtual int getTilesWE(int zoomlevel) const;
    virtual int getTilesNS(int zoomlevel) const;

    virtual void cleanup() {}

    virtual bool toXML(QXmlStreamWriter& /*stream*/) { return true; }
    virtual void fromXML(QXmlStreamReader& /*xParent*/) {}
    virtual QString toPropertiesHtml() {return "";}

    virtual void setSettings(QSettings* /*aSet*/) {}

protected:
    TmsServer theServer;
    int	tilesize;
    bool BlOrigin;
    bool isProj4326;

};

#endif
