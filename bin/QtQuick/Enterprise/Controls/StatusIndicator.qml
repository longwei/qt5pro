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
import QtQuick.Controls.Private 1.0
import QtQuick.Enterprise.Controls 1.2
import QtQuick.Enterprise.Controls.Styles 1.2
import QtQuick.Enterprise.Controls.Private 1.0

/*!
    \qmltype StatusIndicator
    \inqmlmodule QtQuick.Enterprise.Controls
    \since QtQuick.Enterprise.Controls 1.1
    \ingroup enterprisecontrols
    \ingroup enterprisecontrols-non-interactive
    \brief An indicator that displays active or inactive states.

    \image statusindicator-active.png A StatusIndicator in the active state
    A StatusIndicator in the active state.
    \image statusindicator-inactive.png A StatusIndicator in the inactive state
    A StatusIndicator in the inactive state.

    The StatusIndicator displays active or inactive states. By using different
    colors via the \l color property, StatusIndicator can provide extra
    context to these states. For example:

    \table
    \row
        \li QML
        \li Result
    \row
        \li
            \code
                import QtQuick 2.2
                import QtQuick.Enterprise.Controls 1.2

                Rectangle {
                    width: 100
                    height: 100
                    color: "#cccccc"

                    StatusIndicator {
                        anchors.centerIn: parent
                        color: "green"
                    }
                }
            \endcode
        \li \image statusindicator-green.png "Green StatusIndicator"
    \endtable

    You can create a custom appearance for a StatusIndicator by assigning a
    \l {QtQuick.Enterprise.Controls.Styles::}{StatusIndicatorStyle}.
*/

Control {
    id: statusIndicator

    style: Qt.createComponent(StyleSettings.style + "/StatusIndicatorStyle.qml", statusIndicator)

    /*!
        This property specifies whether the indicator is active or inactive.

        The default value is \c false (off).

        \deprecated Use active instead.
    */
    property alias on: statusIndicator.active

    /*!
        \since QtQuick.Enterprise.Controls 1.2

        This property specifies whether the indicator is active or inactive.

        The default value is \c false (inactive).
    */
    property bool active: false

    /*!
        This property specifies the color of the indicator when it is active.

        The default value is \c "red".
    */
    property color color: "red"
}
