#include "../src/qbl-pipe.h"
#include <vector>
#include <string>
std::string result;

class ResultListener : public QblPipeListener {
    public:
        virtual ~ResultListener(){

        }

        void onData(const std::vector<char>&data) {
            result = std::string(data.begin(), data.end());
        }

        void onFinish() {

        }
};
