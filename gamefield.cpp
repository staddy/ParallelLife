#include "gamefield.h"

#include <vector>
#include <QDebug>

GameField::GameField(uint64_t width_, uint64_t height_, QObject *parent)
    : QObject(parent), m_width{width_}, m_height{height_} {
    for (uint64_t i = 0; i < height_; ++i) {
        m_cells.push_back(QVector<bool>(width_, false));
    }
}

QVariant GameField::cells() const {
    return QVariant::fromValue(m_cells);
}

bool GameField::get(int x_, int y_) {
    while (x_ < 0) x_ += m_width;
    while (y_ < 0) y_ += m_height;
    x_ %= m_width;
    y_ %= m_height;
    return m_cells[x_][y_];
}

void GameField::tick() {
    std::vector<std::pair<int, int> > changes;
    for (int i = 0; i < m_height; ++i) {
        for (int j = 0; j < m_width; ++j) {
            auto neighbors = countNeighbors(i, j);
            if (get(i, j)) {
                // Any live cell with fewer than two live neighbours dies, as if by underpopulation.
                // Any live cell with more than three live neighbours dies, as if by overpopulation.
                if (neighbors < 2 || neighbors > 3) {
                    changes.emplace_back(i, j);
                }

            } else {
                // Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.
                if (neighbors == 3) {
                    changes.emplace_back(i, j);
                }
            }
        }
    }
    for (const auto& change : changes) {
        set(change.first, change.second, !get(change.first, change.second));
    }
    emit cellsChanged();
}

unsigned int GameField::countNeighbors(int x_, int y_) {
    unsigned int retVal{0};
    for (int i = x_ - 1; i < x_ + 2; ++i) {
        for (int j = y_ - 1; j < y_ + 2; ++j) {
            if (get(i, j)) {
                ++retVal;
            }
        }
    }
    return retVal - (get(x_, y_) ? 1 : 0);
}

void GameField::set(int x_, int y_, bool value_) {
    while (x_ < 0) x_ += m_width;
    while (y_ < 0) y_ += m_height;
    x_ %= m_width;
    y_ %= m_height;
    m_cells[x_][y_] = value_;
    emit cellsChanged();
}
