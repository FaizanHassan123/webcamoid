/* Webcamoid, webcam capture application.
 * Copyright (C) 2011-2015  Gonzalo Exequiel Pedone
 *
 * Webcamod is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Webcamod is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Webcamod. If not, see <http://www.gnu.org/licenses/>.
 *
 * Email     : hipersayan DOT x AT gmail DOT com
 * Web-Site 1: http://github.com/hipersayanX/Webcamoid
 * Web-Site 2: http://opendesktop.org/content/show.php/Webcamoid?content=144796
 */

#ifndef QBCAPS_H
#define QBCAPS_H

#include <QObject>
#include <QDebug>

class QbCapsPrivate;

class QbCaps: public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool isValid
               READ isValid)
    Q_PROPERTY(QString mimeType
               READ mimeType
               WRITE setMimeType
               RESET resetMimeType
               NOTIFY mimeTypeChanged)

    public:
        explicit QbCaps(QObject *parent=NULL);
        QbCaps(const QVariantMap &caps);
        QbCaps(const QString &caps);
        QbCaps(const QbCaps &other);
        virtual ~QbCaps();
        QbCaps &operator =(const QbCaps &other);
        bool operator ==(const QbCaps &other) const;
        bool operator !=(const QbCaps &other) const;
        operator bool() const;

        Q_INVOKABLE bool isValid() const;
        Q_INVOKABLE QString mimeType() const;
        Q_INVOKABLE QbCaps &fromMap(const QVariantMap &caps);
        Q_INVOKABLE QbCaps &fromString(const QString &caps);
        Q_INVOKABLE QVariantMap toMap() const;
        Q_INVOKABLE QString toString() const;
        Q_INVOKABLE QbCaps &update(const QbCaps &other);
        Q_INVOKABLE bool isCompatible(const QbCaps &other) const;
        Q_INVOKABLE bool contains(const QString &property) const;

    private:
        QbCapsPrivate *d;

    signals:
        void mimeTypeChanged();

    public slots:
        void setMimeType(const QString &mimeType);
        void resetMimeType();
        void clear();

    friend QDebug operator <<(QDebug debug, const QbCaps &caps);
    friend QDataStream &operator >>(QDataStream &istream, QbCaps &caps);
    friend QDataStream &operator <<(QDataStream &ostream, const QbCaps &caps);
};

QDebug operator <<(QDebug debug, const QbCaps &caps);
QDataStream &operator >>(QDataStream &istream, QbCaps &caps);
QDataStream &operator <<(QDataStream &ostream, const QbCaps &caps);

Q_DECLARE_METATYPE(QbCaps)

#endif // QBCAPS_H
