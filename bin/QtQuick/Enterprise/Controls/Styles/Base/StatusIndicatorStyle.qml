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
import QtGraphicalEffects 1.0
import QtQuick.Controls.Private 1.0
import QtQuick.Enterprise.Controls 1.2

/*!
    \qmltype StatusIndicatorStyle
    \inqmlmodule QtQuick.Enterprise.Controls.Styles
    \since QtQuick.Enterprise.Controls.Styles 1.1
    \ingroup enterprisecontrolsstyles
    \brief Provides custom styling for StatusIndicatorStyle.

    You can create a custom status indicator by defining the \l indicator
    component.
*/

Style {
    id: pieMenuStyle

    /*!
        This defines the indicator in both its on and off status.
    */
    property Component indicator: Item {
        readonly property real shineStep: 0.05
        readonly property real smallestAxis: Math.min(control.width, control.height)
        readonly property real shadowRadius: smallestAxis * 0.4
        readonly property real outerRecessPercentage: 0.11
        readonly property color offColor: Qt.rgba(0.13, 0.13, 0.13)
        readonly property color baseColor: control.active ? control.color : offColor

        Canvas {
            id: backgroundCanvas
            anchors.fill: parent

            Connections {
                target: control
                onActiveChanged: backgroundCanvas.requestPaint()
                onColorChanged: backgroundCanvas.requestPaint()
            }

            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                // Draw the semi-transparent background.
                ctx.beginPath();
                var gradient = ctx.createLinearGradient(width / 2, 0, width / 2, height * 0.75);
                gradient.addColorStop(0.0, Qt.rgba(0, 0, 0, control.active ? 0.1 : 0.25));
                gradient.addColorStop(1.0, control.active ? Qt.rgba(0, 0, 0, 0.1) : Qt.rgba(0.74, 0.74, 0.74, 0.25));

                ctx.fillStyle = gradient;
                ctx.ellipse(0, 0, width, height);
                ctx.fill();
            }
        }

        Item {
            id: shadowGuard
            anchors.fill: parent
            anchors.margins: -shadowRadius

            Canvas {
                id: colorCanvas
                anchors.fill: parent
                anchors.margins: shadowRadius

                Connections {
                    target: control
                    onActiveChanged: colorCanvas.requestPaint()
                    onColorChanged: colorCanvas.requestPaint()
                }

                onPaint: {
                    var ctx = getContext("2d");
                    ctx.reset();

                    // Draw the actual color within the circle.
                    ctx.beginPath();
                    ctx.fillStyle = baseColor;
                    var recess = smallestAxis * outerRecessPercentage;
                    ctx.ellipse(recess, recess, width - recess * 2, height - recess * 2);
                    ctx.fill();
                }
            }
        }

        DropShadow {
            id: shadow
            source: shadowGuard
            color: control.color
            // Don't set fast here because Qt < 5.3 will run into QTBUG-36931
            radius: shadowRadius
            samples: Math.min(32, radius)
            // Don't set cached to true here or anywhere else
            // if QTBUG-40967 is not fixed by next (1.3/2.0) release
            cached: true
            anchors.fill: shadowGuard
            visible: control.active
        }

        Canvas {
            id: foregroundCanvas
            anchors.fill: parent

            Connections {
                target: control
                onActiveChanged: foregroundCanvas.requestPaint()
                onColorChanged: foregroundCanvas.requestPaint()
            }

            onPaint: {
                var ctx = getContext("2d");
                ctx.reset();

                // Draw the first shine.
                ctx.beginPath();
                ctx.fillStyle = Qt.rgba(1, 1, 1, 0.03);
                var recessPercentage = outerRecessPercentage + shineStep * 0.65;
                var recess = smallestAxis * recessPercentage;
                ctx.ellipse(recess, recess, width - recess * 2, height - recess * 2);
                ctx.fill();

                // Draw the second, inner shine.
                ctx.beginPath();
                ctx.fillStyle = Qt.rgba(1, 1, 1, 0.06);
                recessPercentage += shineStep;
                recess = smallestAxis * recessPercentage;
                ctx.ellipse(recess, recess, width - recess * 2, height - recess * 2);
                ctx.fill();

                // Now draw the final arced shine that goes over the first and second shines.
                // First, clip the entire shine area.
                ctx.beginPath();
                recessPercentage -= shineStep;
                recess = smallestAxis * recessPercentage;
                ctx.ellipse(recess, recess, width - recess * 2, height - recess * 2);
                ctx.clip();

                if (!control.active) {
                    // Then, clip the bottom area out of the shine.
                    ctx.ellipse(recess, height * 0.425, width - recess * 2, height - recess * 2);
                    ctx.clip();
                }

                ctx.beginPath();
                var gradient;
                if (!control.active) {
                    // Draw the shine arc.
                    gradient = ctx.createLinearGradient(width / 2, height * 0.2, width / 2, height * 0.65);
                    gradient.addColorStop(0.0, Qt.rgba(1, 1, 1, 0.05));
                    gradient.addColorStop(1.0, "transparent");
                } else {
                    // Draw the radial shine.
                    gradient = ctx.createRadialGradient(width / 2, height / 2, width * 0.25, width / 2, height / 2, width * 0.25);
                    gradient.addColorStop(0.0, Qt.lighter(baseColor, 1.4));
                    gradient.addColorStop(1.0, "transparent");
                }

                ctx.fillStyle = gradient;
                ctx.ellipse(recess, recess, width - recess * 2, height - recess * 2);
                ctx.fill();
            }
        }
    }

    /*! \internal */
    property Component panel: Item {
        implicitWidth: 32
        implicitHeight: 32

        Loader {
            id: indicatorLoader
            width: Math.max(1, Math.min(parent.width, parent.height))
            height: width
            anchors.centerIn: parent
            sourceComponent: indicator
        }
    }
}
