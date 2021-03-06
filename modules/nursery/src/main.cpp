#include <cstdlib>

#include <iostream>

#include <boost/program_options.hpp>

#include "nursery/nursery.hpp"

namespace {

    const auto options = [] {
        auto opts = boost::program_options::options_description{};

        opts.add_options()("help", "produce help message");

        return opts;
    }();

}

int main(int argc, char** argv) {
    const auto varmap = [=] {
        auto varmap = boost::program_options::variables_map{};

        boost::program_options::store(
            boost::program_options::parse_command_line(argc, argv, options),
            varmap);
        boost::program_options::notify(varmap);

        return varmap;
    }();

    if(varmap.contains("help")) {
        std::cout << options << '\n';
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
