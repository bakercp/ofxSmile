#pragma once


#include "SimpleCV.h"
#include "smile.h"
#include "rimage.h"


class ofxSmile
{
public:
	static bool getSmile(ofImage img, float& amount)
    {
		img.setImageType(OF_IMAGE_GRAYSCALE);

        ofFloatPixels floatPixels = img.getPixelsRef();

		MPSmile smileFinder;

		VisualObject faces;

        RImage<float> rimage(floatPixels.getPixels(),
                             floatPixels.getWidth(),
                             floatPixels.getHeight());

        bool smileFound = false;

        amount = 0;

		if (!smileFinder.findSmiles(rimage, faces))
        {
			if (faces.size() == 1)
            {
				FaceObject* face = static_cast<FaceObject*>(*(faces.begin()));
				amount = face->activation;
				smileFound = true;
			}
		}

		return smileFound;
	}
};
