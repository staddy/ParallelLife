#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QObject>
#include <QVariant>

class GameField : public QObject {
    Q_OBJECT
    Q_PROPERTY(QVariant cells READ cells NOTIFY cellsChanged)
    Q_PROPERTY(unsigned long long width MEMBER m_width CONSTANT)
    Q_PROPERTY(unsigned long long height MEMBER m_height CONSTANT)
public:
    explicit GameField(uint64_t width_, uint64_t height_, QObject *parent = nullptr);
    QVariant cells() const;
    Q_INVOKABLE void set(int x_, int y_, bool value_ = true);
    Q_INVOKABLE bool get(int x_, int y_);
    Q_INVOKABLE void tick();
    unsigned int countNeighbors(int x_, int y_);

signals:
    void cellsChanged();
private:
    QVector<QVector<bool> > m_cells;
    uint64_t m_width;
    uint64_t m_height;
};

#endif // GAMEFIELD_H
