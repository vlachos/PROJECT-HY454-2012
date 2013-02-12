#ifndef INPUTMANAGE_H
#define INPUTMANAGE_H

namespace InputManageHandling{

extern bool OnKeyUp(void);
extern bool OnKeyDown(void);
extern bool OnKeyLeft(void);
extern bool OnKeyRight(void);
extern bool OnKeySpace(void);
extern bool OnKeySelect(void);
extern bool OnKeyP(void);
extern bool OnKeyUp();
extern bool OnKeyDown();
extern bool OnKeySpace();
extern bool OnKeySelect();

extern bool OnBubKeyUp();
extern bool OnBubKeyLeft();
extern bool OnBubKeyRight();
extern bool OnBubKeySpace();

extern bool OnBobKeyUp();
extern bool OnBobKeyLeft();
extern bool OnBobKeyRight();
extern bool OnBobKeySpace();

}

#endif