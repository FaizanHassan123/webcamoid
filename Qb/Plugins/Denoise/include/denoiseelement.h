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

#ifndef DENOISEELEMENT_H
#define DENOISEELEMENT_H

#include <cmath>
#include <QQmlComponent>
#include <QQmlContext>
#include <qb.h>
#include <qbutils.h>

class DenoiseElement: public QbElement
{
    Q_OBJECT
    Q_PROPERTY(int radius
               READ radius
               WRITE setRadius
               RESET resetRadius
               NOTIFY radiusChanged)
    Q_PROPERTY(int factor
               READ factor
               WRITE setFactor
               RESET resetFactor
               NOTIFY factorChanged)
    Q_PROPERTY(int mu
               READ mu
               WRITE setMu
               RESET resetMu
               NOTIFY muChanged)
    Q_PROPERTY(int sigma
               READ sigma
               WRITE setSigma
               RESET resetSigma
               NOTIFY sigmaChanged)

    public:
        explicit DenoiseElement();

        Q_INVOKABLE QObject *controlInterface(QQmlEngine *engine,
                                              const QString &controlId) const;

        Q_INVOKABLE int radius() const;
        Q_INVOKABLE int factor() const;
        Q_INVOKABLE int mu() const;
        Q_INVOKABLE int sigma() const;

    private:
        int m_radius;
        int m_factor;
        int m_mu;
        int m_sigma;
        int m_weight[256][128][256];

        QbElementPtr m_convert;

        inline void makeTable(int factor)
        {
            for (int s = 0; s < 128; s++) {
                int h = -2 * s * s;

                for (int m = 0; m < 256; m++)
                    for (int c = 0; c < 256; c++) {
                        if (s == 0) {
                            this->m_weight[m][s][c] = 0;

                            continue;
                        }

                        int d = c - m;
                        d *= d;

                        this->m_weight[m][s][c] = factor * exp(qreal(d) / h);
                    }
            }
        }

    signals:
        void radiusChanged();
        void factorChanged();
        void muChanged();
        void sigmaChanged();

    public slots:
        void setRadius(int radius);
        void setFactor(int factor);
        void setMu(int mu);
        void setSigma(int sigma);
        void resetRadius();
        void resetFactor();
        void resetMu();
        void resetSigma();
        QbPacket iStream(const QbPacket &packet);
};

#endif // DENOISEELEMENT_H
