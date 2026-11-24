//
// Created by Oier Universidad on 24/11/2026.
//

#ifndef PRACTICA3_UTM_H
#define PRACTICA3_UTM_H

class UTM {
private:
    double X;
    double Y;

public:
    // Constructores
    UTM() : X(0.0), Y(0.0) {}
    UTM(double x, double y) : X(x), Y(y) {}

    // Getters y Setters
    double getX() const { return X; }
    double getY() const { return Y; }
    void setX(double x) { X = x; }
    void setY(double y) { Y = y; }

    // Fórmula del guión: (X1 - X2)^2 + (Y1 - Y2)^2
    double distancia2(const UTM& otra) const {
        double dx = X - otra.X;
        double dy = Y - otra.Y;
        return (dx * dx) + (dy * dy);
    }
};

#endif //PRACTICA3_UTM_H