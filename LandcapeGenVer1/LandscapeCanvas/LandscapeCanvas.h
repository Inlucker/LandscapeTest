#ifndef LANDSCAPECANVAS_H
#define LANDSCAPECANVAS_H

#include <memory>
#include <iostream>

using namespace std;

#define MULT getMult()

#include "HeightsMap/HeightsMap.h"
#include "HeightsMap/HeightsMapPoints.h"
#include "Triangles/TriPolArray.h"
#include "Triangles/TriangularPolygon.h"
#include "ZBuffer/ZBufferAlg.h"

class LandscapeCanvas
{
public:
    LandscapeCanvas();
    virtual ~LandscapeCanvas();

    void generateNewLandscape(int size);
    void readFromFile(string file_name);
    void writeToFile(string file_name);
    //virtual void drawLandscape() = 0;
    shared_ptr<FrameBuffer> getFrameBuffer();
    void cleanCanvas();
    void resetHeightsMap();
    void updateResolution();

    //Resolution setters
    void setWidth(int new_width);
    void setHeight(int new_height);

    //generating seters
    void setRange(float new_range);
    void setSmoothing(bool new_smoothing);

    //drawing seters
    void setMult(int new_mult);
    void setLandscapeColor(int r, int g, int b);

    //transforming
    void transform(const Point& move, const Point& scale, const Point& rotate);
    void move(const Point& move);
    void scale(const Point& scale);
    void rotate(const Point& rotate);

    void getColor(int& r, int& g, int& b) noexcept;

    shared_ptr<HeightsMapPoints> getHeightsMapPoints() const;
    shared_ptr<TriPolArray> getTriPolArray() const;
    shared_ptr<ZBufferAlg> getZBufferAlg() const;
    int getMult() const;
    int getImgWidth() const;
    int getImgHeight() const;

private:
    //Resolution parametres
    int img_width = 720;
    int img_height = 405;

    //generating parametres
    float range = 24.75;
    bool smoothing = false;

    //drawing parametres
    int mult = 1;
    int red = 20;
    int green = 150;
    int blue = 20;

    unique_ptr<HeightsMap> heights_map;
    shared_ptr<HeightsMapPoints> heights_map_points;

    shared_ptr<TriPolArray> tri_pol_mas;
    shared_ptr<ZBufferAlg> zbuffer_alg;
    shared_ptr<FrameBuffer> frame_buffer;
};

#endif // LANDSCAPECANVAS_H