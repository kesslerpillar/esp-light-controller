#ifndef GOOGLE_TEST_EXAMPLE_LIGHTSWITCH_H
#define GOOGLE_TEST_EXAMPLE_LIGHTSWITCH_H

class LightSwitch {
private:

    public:
        virtual bool isPressed() = 0;
        bool isResponded = 0;

        virtual void updateRespondedStatus(bool status);
};

#endif