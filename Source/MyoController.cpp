#include "MyoController.h"

void MyoController::onPose(myo::Myo* myo, uint64_t timestamp, myo::Pose pose)
{
    currentPose = pose;
    if (pose != myo::Pose::unknown && pose != myo::Pose::rest) {
        // Tell the Myo to stay unlocked until told otherwise. We do that here so you can hold the poses without the
        // Myo becoming locked.
        myo->unlock(myo::Myo::unlockHold);
        // Notify the Myo that the pose has resulted in an action, in this case changing
        // the text on the screen. The Myo will vibrate.
        myo->notifyUserAction();
    }
    else {
        // Tell the Myo to stay unlocked only for a short period. This allows the Myo to stay unlocked while poses
        // are being performed, but lock after inactivity.
        myo->unlock(myo::Myo::unlockTimed);
    }
}

void MyoController::onLock(myo::Myo* myo, uint64_t timestamp)
{
    
    isUnlocked = false;
}

void MyoController::onUnlock(myo::Myo* myo, uint64_t timestamp)
{
    isUnlocked = true;
}

void MyoController::onArmUnsync(myo::Myo* myo, uint64_t timestamp)
{
    onArm = false;
}

void MyoController::onArmSync(myo::Myo* myo, uint64_t timestamp, myo::Arm arm, myo::XDirection xDirection, float rotation, myo::WarmupState warmupState)
{
    onArm = true;
    whichArm = arm;
}

void MyoController::onUnpair(myo::Myo* myo, uint64_t timestamp)
{
    onArm = false;
    isUnlocked = false;
}
