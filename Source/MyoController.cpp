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

void MyoController::onEmgData(myo::Myo* myo, uint64_t timestamp, const int8_t* emg)
{

    //emgFile << timestamp;
    for (size_t i = 0; i < 8; i++) {
        /* emgFile << ',' << static_cast<int>(emg[i]);*/


        averageEMG[i] += abs(static_cast<int>(emg[i]));
        if (count == 99) {
            averageEMG[i] = averageEMG[i] / 100;

           // std::cout << "emg " << i << ": " << averageEMG[i] << " ";


        }
    }
    if (count == 99) {

        float up = averageEMG[4] / (1 + averageEMG[1]);
        float right = averageEMG[3] / (1 + averageEMG[7]);
        float left = (averageEMG[0] + averageEMG[7]) / (averageEMG[5] + 1);
        float down = (0.5f * (averageEMG[0] + averageEMG[1] + averageEMG[2])) / (1 + averageEMG[5] + averageEMG[6]);
        float rest = (averageEMG[4] + averageEMG[5] + averageEMG[6] + averageEMG[7]) / 20;
        if (up + right + left + down <= 5) {
            Direction = Rest;
        }
        else if (up > right && up > left && up > down)
        {
           Direction = Up;
        }
        else if (left > right && left > up && left > down)
        {
            Direction = Left;
        }
        else if (right > left && right > up && right > down)
        {
            Direction = Right;
        }
        else if (down > right && down > left && down > up)
        {
            Direction = Down;
        }

        
        count = 0;
        std::cout << std::endl;
    }
    count++;


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
