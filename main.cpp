#include <memory>
#include "Runner.h"

int main(int argc, char* argv[]){
    std::shared_ptr<Runner> runner = std::make_shared<Runner>();

    runner->run();

}
