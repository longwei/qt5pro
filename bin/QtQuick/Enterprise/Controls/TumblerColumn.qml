/****************************************************************************
**
** Copyright (C) 2014 Digia Plc
** All rights reserved.
** For any questions to Digia, please use contact form at http://qt.digia.com
**
** This file is part of the QtQuick Enterprise Controls Add-on.
**
** $QT_BEGIN_LICENSE$
** Licensees holding valid Qt Commercial licenses may use this file in
** accordance with the Qt Commercial License Agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.
**
** If you have questions regarding the use of this file, please use
** contact form at http://qt.digia.com
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Private 1.0

/*!
    \qmltype TumblerColumn
    \inqmlmodule QtQuick.Enterprise.Controls
    \since QtQuick.Enterprise.Controls 1.2
    \ingroup enterprisecontrols
    \brief A column within a tumbler.

    \note TumblerColumn requires Qt 5.3.2 or later.

    TumblerColumn represents a column within a tumbler, providing the interface
    to define the items and width of each column.

    \code
    Tumbler {
        TumblerColumn {
            model: [1, 2, 3]
        }

        TumblerColumn {
            model: ["A", "B", "C"]
            visible: false
        }
    }
    \endcode

    You can create a custom appearance for a Tumbler by assigning a
    \l TumblerStyle.
*/

QtObject {
    id: tumblerColumn

    /*! \internal */
    property Item __tumbler: null

    /*!
        \internal

        The index of this column within the tumbler.
    */
    property int __index: -1

    /*!
        \internal

        The index of the current item, if the PathView has items instantiated,
        or the last current index if it doesn't.
    */
    property int __currentIndex: -1

    Accessible.role: Accessible.ColumnHeader

    /*!
        \qmlproperty readonly int TumblerColumn::currentIndex

        This read-only property holds the index of the current item for this
        column. If the model count is reduced, the current index will be
        reduced to the new count minus one.

        \sa {Tumbler::currentIndexAt}, {Tumbler::setCurrentIndexAt}
    */
    readonly property alias currentIndex: tumblerColumn.__currentIndex

    /*!
        This property holds the model that provides data for this column.
    */
    property var model: null

    /*!
        This property holds the model role of this column.
    */
    property string role: ""

    /*!
        The item delegate for this column.

        If set, this delegate will be used to display items in this column,
        instead of the
        \l {QtQuick.Enterprise.Controls.Styles::TumblerStyle::delegate}{delegate}
        property in \l {QtQuick.Enterprise.Controls.Styles::}{TumblerStyle}.

        The \l {Item::implicitHeight}{implicitHeight} property must be set,
        and it must be the same for each delegate.
    */
    property Component delegate

    /*!
        The highlight delegate for this column.

        If set, this highlight will be used to display the highlight in this
        column, instead of the
        \l {QtQuick.Enterprise.Controls.Styles::TumblerStyle::highlight}{highlight}
        property in \l {QtQuick.Enterprise.Controls.Styles::}{TumblerStyle}.
    */
    property Component highlight

    /*!
        This property holds the visibility of this column.
    */
    property bool visible: true

    /*!
        This read-only property indicates whether the item has active focus.

        See Item's \l {Item::activeFocus}{activeFocus} property for more
        information.
    */
    readonly property bool activeFocus: {
        if (__tumbler === null)
            return null;

        var view = __tumbler.__viewAt(__index);
        return view && view.activeFocus ? true : false;
    }

    /*!
        This property holds the width of this column.
    */
    property real width: {
        if (!__tumbler || __tumbler.columnCount === 0 || __tumbler.width == __tumbler.implicitWidth)
            return TextSingleton.implicitHeight * 4;

        // We have a tumbler, it has at least one column, and it's not depending on us for its sizing,
        // as someone else gave it a size; we can base our size off of it.
        var oneColumnWidth = __tumbler.width / __tumbler.columnCount;
        return oneColumnWidth - __tumbler.__style.__separatorWidth/* / (__tumbler.columnCount - 1)*/;
    }
}
