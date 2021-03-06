#ifndef	ANIMATIONFILM_H
#define	ANIMATIONFILM_H

#include "Metrics.h"
#include "utilities.h"
#include <string>
#include <vector>



class AnimationFilm{
	std::vector<Rect> boxes;
    Bitmap bitmap;
    std::string	id;

public:
	AnimationFilm();
	AnimationFilm (Bitmap _bitmap, const std::vector<Rect> _boxes, const std::string& _id);
	~AnimationFilm();
    byte GetTotalFrames (void) 	const;
    Bitmap GetBitmap (void) const;
    const std::string 	GetId (void) const;
    const Rect GetFrameBox (byte frameNo) const;
    void DisplayFrame (Bitmap dest, const Point& at, byte frameNo) const;
};

#endif