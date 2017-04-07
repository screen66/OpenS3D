//
// Created by bedh2102 on 06/04/17.
//

#ifndef PROJECT_SIZE_H
#define PROJECT_SIZE_H

class Size {
public:
    constexpr Size() noexcept : width_{}, height_{} {}
    constexpr Size(int width, int height) noexcept : width_(width), height_(height) {}

    constexpr int setWidth(int width) noexcept { height_ = width; }
    constexpr int setHeight(int height) noexcept { height_ = height; }
    constexpr int getWidth() const noexcept { return height_; }
    constexpr int getHeight() const noexcept { return height_; }

    void setSize(int width, int height) noexcept {
        setWidth(width);
        setHeight(height);
    }

    int getArea() const noexcept { return width_ * height_; }

private:
    int width_;
    int height_;
};

#endif //PROJECT_SIZE_H
