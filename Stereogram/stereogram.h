#pragma once

#include <stdlib.h>
#include <vector>
#include <numeric>
#include <wx/image.h>

#include "Thread.h"

using namespace std;

class StereoGram {
  public:
    StereoGram() {}

    /* sample usage


            wxImage*stereogram = Stereogram.generateTexturedSIRD( depthMap,
       texturePattern, 640, 480, 14f, 2.5f, 12f, 0f, 72, 72);
     */



    wxImage generateTexturedSIRD(const wxImage& _depthMap,
                                 const wxImage& _texturePattern, int width,
                                 int height, float observationDistanceInches,
                                 float eyeSeparationInches, float maxDepthInches,
                                 float minDepthInches, int horizontalPPI,
                                 int verticalPPI) {

        wxImage depthMap = _depthMap;
        depthMap.Rescale(width, height);
        wxImage stereogram(width, height);

        int observationDistance =
            convertoToPixels(observationDistanceInches, horizontalPPI);
        int eyeSeparation = convertoToPixels(eyeSeparationInches, horizontalPPI);
        int maxDepth = getMaxDepth(convertoToPixels(maxDepthInches, horizontalPPI),
                                   observationDistance);
        int minDepth = getMinDepth(0.55f, maxDepth, observationDistance,
                                   convertoToPixels(minDepthInches, horizontalPPI));
        int verticalShift = verticalPPI / 16;
        int maxSeparation = getSeparation(observationDistance, eyeSeparation, maxDepth);

        wxImage texturePattern = _texturePattern;
        texturePattern.Rescale(maxSeparation, maxSeparation);

        vector <int>seq0_width(width); //0..width vector
        iota (seq0_width.begin(), seq0_width.end(), 0);

        Thread(height).run([&](int l)  { // multithreaded 0..height

            auto linksL=seq0_width, linksR=seq0_width;

            for (int c = 0; c < width; c++) {
                int depth = obtainDepth(depthMap.GetRed(c, l), maxDepth, minDepth);
                int separation =
                    getSeparation(observationDistance, eyeSeparation, depth);
                int left = c - (separation / 2);
                int right = left + separation;

                if (left >= 0 && right < width) {
                    bool visible = true;

                    if (linksL[right] != right) {
                        if (linksL[right] < left) {
                            linksR[linksL[right]] = linksL[right];
                            linksL[right] = right;
                        } else {
                            visible = false;
                        }
                    }
                    if (linksR[left] != left) {
                        if (linksR[left] > right) {
                            linksL[linksR[left]] = linksR[left];
                            linksR[left] = left;
                        } else {
                            visible = false;
                        }
                    }

                    if (visible) {
                        linksL[right] = left;
                        linksR[left] = right;
                    }
                }
            }

            int lastLinked = -10;
            for (int c = 0; c < width; c++) {
                if (linksL[c] == c) {
                    if (lastLinked == c - 1) {
                        setPixel(stereogram, c,l, c-1,l);
                    } else {
                        setPixel(stereogram, c,l,  texturePattern, c % maxSeparation, (l + ((c / maxSeparation) * verticalShift)) % texturePattern.GetHeight());
                    }
                } else {
                    setPixel(stereogram, c,l, linksL[c], l);
                    lastLinked = c;
                }
            }
        });

        return stereogram;
    }

  private:
    inline int getMinDepth(float separationFactor, int maxdepth,
                           int observationDistance, int suppliedMinDepth) {
        int computedMinDepth =
            (int)((separationFactor * maxdepth * observationDistance) /
                  (((1. - separationFactor) * maxdepth) + observationDistance));
        return min(max(computedMinDepth, suppliedMinDepth), maxdepth);
    }

    inline int getMaxDepth(int suppliedMaxDepth, int observationDistance) {
        return max(min(suppliedMaxDepth, observationDistance), 0);
    }

    inline int convertoToPixels(float valueInches, int ppi) {
        return (int)(valueInches * ppi);
    }

    inline int getRed(int color) {
        color &= 0x00ffffff;
        return (color >> 16) & 0xff;
    }

    inline int obtainDepth(int red, int maxDepth, int minDepth) {
        return maxDepth - (red * (maxDepth - minDepth) / 255);
    }

    inline int getSeparation(int observationDistance, int eyeSeparation,
                             int depth) {
        return (eyeSeparation * depth) / (depth + observationDistance);
    }

    inline void setPixel(wxImage&img, int x0, int y0, int x1, int y1) {
        auto r=img.GetRed(x1,y1), g=img.GetGreen(x1,y1), b=img.GetBlue(x1,y1);
        img.SetRGB(x0,y0, r,g,b);
    }
    inline void setPixel(wxImage&img, int x0, int y0, wxImage&imgfrom, int x1, int y1) {
        auto r=imgfrom.GetRed(x1,y1), g=imgfrom.GetGreen(x1,y1), b=imgfrom.GetBlue(x1,y1);
        img.SetRGB(x0,y0, r,g,b);
    }
};

