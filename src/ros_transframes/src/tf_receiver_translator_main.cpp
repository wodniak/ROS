#include "tf_receiver_translator.hpp"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tf_receiver_translator");
    ReceiverTranslator * translator = new ReceiverTranslator();
    translator->publishTranslatedFrames();

    return 0;
};